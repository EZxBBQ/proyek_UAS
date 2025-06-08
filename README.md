<h1> Metode Runge-Kutta Orde-4 Untuk Mensimulasikan Transient Current Pada Rangkaian Listrik RL </h1>

Adi Nugroho - 2306208546

<h2> Deskripsi Program </h2>

Program ini akan menyelesaikan persamaan differensial yang memodelkan perilaku Transient Current pada rangkaian listrik yang terdiri dari resistor dan induktor.
Persamaan differensial yang akan diselesaikan adalah : <br><br>

V(t) = R . i(t) + L . di(t)/dt <br><br>

Program memiliki function r4_step() yang berfungsi menghitung nilai aproksimasi dari persamaan differensial. function tersebut akan menghitung nilai k1, k2, k3 dan k4 yang mana merupakan
nilai hasil evaluasi dari persamaan differensial pada titik tertentu dalam satu step, keempat nilai tersebut lalu akan dicari nilai rata-ratanya untuk merespresentasikan nilai numerik dari persamaan
differensial tersebut untuk satu step. Perhitungan akan diulangi terus menerus hingga durasi maksimal yang telah ditentukan.

Program juga memiliki fungsi exact_solution() untuk menghitung nilai persamaan differensial pada tiap step secara manual tanpa metode numerik. nilai exact dan nilai numerik kemudian akan dibandingkan
untuk mendapat global error dari metode numerik yang digunakan. Program juga akan memiliki fungsi f() yang berfungsi mengevaluasi nilai dari persamaan differensial. fungsi f() ini akan dipanggil untuk menghitung
nilai k1 pada saat proses Runge-Kutta berlangsung.

Selain global error, program juga akan menghitung lokal error dengan cara melakukan 2 jenis evaluasi pada persamaan differensial. evaluasi pertama dilakukan untuk durasi satu step (h) sedangkan evaluasi kedua 
dilakukan dengan durasi setengah step (h/2) dan dilakukan dua kali. Evaluasi kedua akan memiliki akurasi lebih tinggi dibanding evaluasi pertama karena mengevaluasi persamaan lebih banyak dalam satu step. Perbedaan
nilai antara evaluasi full step dan evaluasi half step inilah yang disebut sebagai lokal error.

Pada setiap step, program juga akan secara dinamis mengubah nilai dari step (h) sesuai kebutuhan. Program akan menaikkan nilai step selama nilai lokal error yang dihasilkan masih berada di bawah batas toleransi.
Jika pada satu step nilai lokal error-nya melebihi toleransi, maka program akan mulai mengurangi nilai h. Hal ini dilakukan untuk memaksimalkan kecepatan perhitungan dengan tetap menjaga akurasi dari hasil perhitungan
metode numerik.
