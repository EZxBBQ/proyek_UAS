#include <stdio.h>
#include <math.h>

// Function defining the differential equation: di/dt = (V - R*i)/L
double f(double t, double i, double V, double R, double L) {
    return (V - R * i) / L;
}

// Exact solution for the transient current in an RL circuit
double exact_solution(double t, double i0, double V, double R, double L) {
    if (R == 0.0) {
        return i0 + (V / L) * t;
    }
    return (V / R) + (i0 - V / R) * exp(-(R / L) * t);
}

// Fourth-order Runge-Kutta step
double rk4_step(double t, double y, double h, double V, double R, double L) {
    double k1 = f(t, y, V, R, L);
    double k2 = f(t + h/2, y + (h/2)*k1, V, R, L);
    double k3 = f(t + h/2, y + (h/2)*k2, V, R, L);
    double k4 = f(t + h, y + h*k3, V, R, L);
    
    double new_y = y + (h/6.0) * (k1 + 2*k2 + 2*k3 + k4);
    return new_y;
}

int main() {
    double V, R, L, i0;
    printf("Enter voltage (V): ");
    scanf("%lf", &V);
    printf("Enter resistance (ohms): ");
    scanf("%lf", &R);
    printf("Enter inductance (H): ");
    scanf("%lf", &L);
    printf("Enter initial current (A): ");
    scanf("%lf", &i0);

    if (L <= 0) {
        printf("Inductance must be positive.\n");
        return 1;
    }
    if (R < 0) {
        printf("Resistance must be non-negative.\n");
        return 1;
    }

    double tau = (R == 0) ? 1.0 : L / R;
    double t0 = 0.0;
    double tmax = 5.0 * tau;
    double h = 0.1 * tau;
    double t = t0;
    double i = i0;

    const double tolerance = 0.001; // 0.1% error tolerance
    const double safety = 0.9;
    const double min_factor = 0.1;
    const double max_factor = 5.0;
    const double h_min = 1e-6;
    const double h_max = 0.1 * tau;

    double max_local_error = 0.0;
    double atol = tolerance * (V / R);
    double rtol = tolerance;


    double print_interval = 0.1;
    double next_print = print_interval;

    while (t < tmax) {
        printf("\nTime: %.6f s\n", t);
        double y1 = rk4_step(t, i, h, V, R, L);
        printf("  Full step estimate: %.6f\n", y1);
        double y_mid = rk4_step(t, i, h/2, V, R, L);
        printf("  First half step estimate: %.6f\n", y_mid);
        double y2 = rk4_step(t + h/2, y_mid, h/2, V, R, L);
        printf("  Second half step estimate: %.6f\n", y2);
        double error_est = fabs(y2 - y1);
        printf("  Estimated local error: %.6e\n", error_est);
        double tol = atol + rtol * fabs(y2);

        if (error_est <= tol) {
            t += h;
            i = y2;
            double exact_i = exact_solution(t, i, V, R, L);
            printf(" Exact solution = %.6f\n", exact_i);
            double global_error = fabs(i - exact_i);
            printf("  Global error: %.6e\n", global_error);

            if (error_est > max_local_error) max_local_error = error_est;

            if (t >= next_print || t >= tmax) {
                printf("\n\nTime (s)\tCurrent (A)\tStep Size (s)\tLocal Error\tExact (A)\tGlobal Error\n");
                printf("%.6f\t%.6f\t%.6f\t%.6e\t%.6f\t%.6e\n", 
                       t, i, h, error_est, exact_i, global_error);
                next_print += print_interval;
            }

            double factor = safety * pow(tol / error_est, 0.2);
            factor = (factor < min_factor) ? min_factor : factor;
            factor = (factor > max_factor) ? max_factor : factor;
            h *= factor;
            if (h < h_min) h = h_min;
            if (h > h_max) h = h_max;
            if (t + h > tmax) h = tmax - t;
        } else {
            double factor = safety * pow(tol / error_est, 0.2);
            factor = (factor < min_factor) ? min_factor : factor;
            h *= factor;
            if (h < h_min) h = h_min;
        }
    }

    double exact_final = exact_solution(t, i, V, R, L);
    double global_error_final = fabs(i - exact_final);
    printf("\nSimulation Results at t = %.6f s:\n", t);
    printf("  Numerical Current: %.6f A\n", i);
    printf("  Exact Current:     %.6f A\n", exact_final);
    printf("  Absolute Global Error: %.6e A\n", global_error_final);
    printf("  Relative Global Error: %.6e\n", global_error_final / fabs(exact_final));
    printf("  Maximum Local Error Estimate: %.6e A\n", max_local_error);

    return 0;
}