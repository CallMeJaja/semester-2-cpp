#include "algorithm"
#include "iomanip"
#include "iostream"
#include "limits"
#include "string"

#define MAKS_MAHASISWA 24
#define MAKS_ANTRIAN 10

using namespace std;

struct Mahasiswa;
struct Statistik;
struct Queue;

void clearScreen() { system("cls"); }

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    clearScreen();
}

string potong(string name, int length = 20) {
    if (name.length() > length) {
        return name.substr(0, length - 3) + "...";
    } else {
        return name;
    }
}

int getRandomNumber(int minVal, int maxVal) {
    if (minVal > maxVal) {
        swap(minVal, maxVal);
    }
    if (minVal == maxVal) {
        return minVal;
    }
    return minVal + (rand() % (maxVal - minVal + 1));
}

struct Mahasiswa {
    string nama = "";
    string nim = "";
    string keperluan = "";
    int estimasi_waktu = 0;
    int prioritas = 0;
};

Mahasiswa dataMahasiswa[MAKS_MAHASISWA] = {
    {"Al Amani Abas", "202404020", "", 0},
    {"Dhafi Ebsan Yurizal", "202404018", "", 0},
    {"Diva Oryza Sativa", "202404025", "", 0},
    {"Dyan Putri Agustin", "202404002", "", 0},
    {"Fikri Ramdani", "202404001", "", 0},
    {"Helgi Nur Allamsyah", "202404010", "", 0},
    {"Intan Sri Dayanti", "202404007", "", 0},
    {"Jerry Sutisno", "202404026", "", 0},
    {"Josh Winston Imanuel", "202404005", "", 0},
    {"Keisya Febri Sabila", "202404017", "", 0},
    {"Khaikal Iksanuddin", "202404011", "", 0},
    {"Kirana Larasati Dewi", "202404009", "", 0},
    {"Muhamad Gilang Ramadan", "202404008", "", 0},
    {"Muhamad Sarwan Al Barizy", "202404013", "", 0},
    {"Muhammad Apiransyah Ramdhani", "202404012", "", 0},
    {"Reza Asriano Maulana", "202404021", "", 0},
    {"Salman Alfaridzi", "202404004", "", 0},
    {"Satrio Ilham Syahputra", "202404022", "", 0},
    {"Shevadina Aulia Rahma", "202404024", "", 0},
    {"Siti Fatimatuzzahro", "202404014", "", 0},
    {"Siti Romlah", "202404027", "", 0},
    {"Subani Maulana", "202404023", "", 0},
    {"Umar Maulana Sidiq", "202404016", "", 0},
    {"Zahra Ayu Trisna", "202404019", "", 0},
};

struct Konsultasi {
    string keperluan;
    int jumlah_konsultasi;
    int total_waktu_layanan;
};

struct StatistikMahasiswa {
    string nama;
    string nim;
    Konsultasi konsultasi[10];
    int jumlah_keperluan;
};

struct Statistik {
    StatistikMahasiswa data[MAKS_MAHASISWA];
    int jumlah_mahasiswa;
    int total_mahasiswa_terdaftar;
    int total_mahasiswa_selesai;
    int total_waktu;
    int max_waktu;
    int min_waktu;
    int count_skripsi;
    int count_tugas_akhir;
    int count_konsultasi_mk;
    int count_lainnya;
};

struct Queue {
    int head;
    int tail;
    Mahasiswa data[MAKS_ANTRIAN];
};

void initializeQueue(Queue *q) {
    q->head = -1;
    q->tail = -1;
}

bool isEmpty(Queue *q) { return q->head == -1 || q->head > q->tail; }
bool isFull(Queue *q) { return q->tail >= MAKS_ANTRIAN - 1; }

void enqueue(Queue *q, Mahasiswa mhs) {
    if (isFull(q)) {
        cout << "Antrian penuh!" << endl;
        pause();
        return;
    }
    if (isEmpty(q)) {
        q->head = 0;
        q->tail = 0;
        q->data[0] = mhs;
    } else {
        int prioritas = q->head;
        while (prioritas <= q->tail &&
               q->data[prioritas].prioritas <= mhs.prioritas) {
            prioritas++;
        }
        for (int i = q->tail; i >= prioritas; i--) {
            q->data[i + 1] = q->data[i];
        }

        q->data[prioritas] = mhs;
        q->tail++;
    }
    cout << "\nMahasiswa " << mhs.nama << " (" << mhs.nim
         << ") telah ditambahkan ke antrian dengan prioritas " << mhs.prioritas
         << endl;
}

Mahasiswa dequeue(Queue *q, Statistik *s) {
    Mahasiswa mhs;
    if (isEmpty(q)) {
        cout << "Antrian kosong!" << endl;
        return mhs;
    }
    mhs = q->data[q->head];

    // Geser semua elemen ke depan
    for (int i = q->head; i < q->tail; i++) {
        q->data[i] = q->data[i + 1];
    }

    // Update tail
    q->tail--;

    // Jika antrian kosong setelah dequeue
    if (q->head > q->tail) {
        initializeQueue(q);
    }

    cout << "\nMahasiswa " << mhs.nama << " (" << mhs.nim
         << ") telah selesai dan keluar dari antrian." << endl;
    return mhs;
}

void updateStatistik(Statistik *s, const Mahasiswa &m, int waktu_aktual) {
    int idx_mhs = -1;
    for (int i = 0; i < s->jumlah_mahasiswa; i++) {
        if (s->data[i].nim == m.nim) {
            idx_mhs = i;
            break;
        }
    }

    if (idx_mhs == -1 && s->jumlah_mahasiswa < MAKS_MAHASISWA) {
        idx_mhs = s->jumlah_mahasiswa;
        s->data[idx_mhs].nim = m.nim;
        s->data[idx_mhs].nama = m.nama;
        s->data[idx_mhs].jumlah_keperluan = 0;
        s->jumlah_mahasiswa++;
    } else if (idx_mhs == -1) {
        cout << "Batas statistik mahasiswa tercapai, tidak dapat "
                "menambah mahasiswa baru ke statistik."
             << endl;
    }

    if (idx_mhs != -1) {
        int idx_kp = -1;
        for (int i = 0; i < s->data[idx_mhs].jumlah_keperluan; i++) {
            if (s->data[idx_mhs].konsultasi[i].keperluan == m.keperluan) {
                idx_kp = i;
                break;
            }
        }

        if (idx_kp == -1 && s->data[idx_mhs].jumlah_keperluan < 10) {
            idx_kp = s->data[idx_mhs].jumlah_keperluan;
            s->data[idx_mhs].konsultasi[idx_kp].keperluan = m.keperluan;
            s->data[idx_mhs].konsultasi[idx_kp].jumlah_konsultasi = 0;
            s->data[idx_mhs].konsultasi[idx_kp].total_waktu_layanan = 0;
            s->data[idx_mhs].jumlah_keperluan++;
        } else if (idx_kp == -1) {
            cout << "Batas statistik keperluan untuk mahasiswa "
                    "tercapai."
                 << endl;
        }

        if (idx_kp != -1) {
            s->data[idx_mhs].konsultasi[idx_kp].jumlah_konsultasi++;
            s->data[idx_mhs].konsultasi[idx_kp].total_waktu_layanan +=
                waktu_aktual;
        }
    }

    s->total_waktu += waktu_aktual;
    if (waktu_aktual > s->max_waktu) {
        s->max_waktu = waktu_aktual;
    }
    if (s->min_waktu == 0 || waktu_aktual < s->min_waktu) {
        s->min_waktu = waktu_aktual;
    }
}

void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        cout << "\nAntrian kosong!" << endl;
    } else {
        clearScreen();
        cout << string(84, '=') << endl;
        cout << "|\t\t\tDAFTAR ANTRIAN MAHASISWA\t\t\t\t   |" << endl;
        cout << string(84, '=') << endl;
        cout << "| " << left << setw(3) << "No" << "| " << setw(10) << "NIM"
             << "| " << setw(20) << "Nama" << "| " << setw(25) << "Keperluan"
             << "| " << setw(15) << "Estimasi Waktu |" << endl;
        cout << string(84, '-') << endl;
        int current = q->head;
        int nomor = 1;
        while (current <= q->tail) {
            cout << "| " << left << setw(3) << nomor << "| " << setw(10)
                 << q->data[current].nim << "| " << setw(20)
                 << potong(q->data[current].nama, 18) << "| " << setw(25)
                 << potong(q->data[current].keperluan, 23) << "| " << setw(3)
                 << q->data[current].estimasi_waktu - 5 << " - " << left
                 << setw(8)
                 << (to_string(q->data[current].estimasi_waktu + 5) + " Menit")
                 << " |" << endl;
            cout << string(84, '-') << endl;
            current++;
            nomor++;
        }
    }
    pause();
}

void displayMahasiswaList() {
    cout << string(51, '=') << endl;
    cout << "|\t\tDAFTAR MAHASISWA\t\t  |" << endl;
    cout << string(51, '=') << endl;
    cout << "| " << left << setw(3) << "No" << "| " << setw(10) << "NIM" << "| "
         << setw(30) << "Nama" << " |" << endl;
    cout << string(51, '-') << endl;
    for (int i = 0; i < MAKS_MAHASISWA; i++) {
        cout << "| " << left << setw(3) << i + 1 << "| " << setw(10)
             << dataMahasiswa[i].nim << "| " << setw(30)
             << potong(dataMahasiswa[i].nama, 28) << " |" << endl;
    }
    cout << string(51, '=') << endl;
}

void statistikJumlahAntrian(Queue *q, Statistik *s) {
    clearScreen();
    int antrian_belum_diproses = 0;
    if (!isEmpty(q)) {
        antrian_belum_diproses = q->tail - q->head + 1;
    }

    cout << string(55, '=') << endl;
    cout << "           Statistik Jumlah Antrian" << endl;
    cout << string(55, '=') << endl;
    cout << left << setw(45) << "Jumlah Mahasiswa Terdaftar (Sistem)" << ": "
         << s->total_mahasiswa_terdaftar << endl;
    cout << left << setw(45) << "Jumlah Antrian Belum Diproses" << ": "
         << antrian_belum_diproses << endl;
    cout << left << setw(45) << "Total Mahasiswa yang Telah Dilayani" << ": "
         << s->jumlah_mahasiswa << endl;
    cout << left << setw(45) << "Jumlah Total Konsultasi Selesai" << ": "
         << s->total_mahasiswa_selesai << endl;
    cout << left << setw(45) << "Jumlah Antrian Belum Diproses" << ": "
         << antrian_belum_diproses << endl;
    cout << string(55, '=') << endl;
    pause();
}

void statistikKeperluanKonsultasi(Statistik *s) {
    clearScreen();
    cout << string(40, '=') << endl;
    cout << "   Statistik Keperluan Konsultasi" << endl;
    cout << string(40, '=') << endl;
    cout << left << setw(20) << "1. Skripsi" << ": " << s->count_skripsi
         << " orang" << endl;
    cout << left << setw(20) << "2. Tugas Akhir" << ": " << s->count_tugas_akhir

         << " orang" << endl;
    cout << left << setw(20) << "3. Konsultasi MK" << ": "
         << s->count_konsultasi_mk << " orang" << endl;
    cout << left << setw(20) << "4. Lainnya" << ": " << s->count_lainnya
         << " orang" << endl;
    cout << string(40, '=') << endl;
    pause();
}

void statistikWaktuLayanan(Statistik *s) {
    clearScreen();
    cout << string(55, '=') << endl;
    cout << "             Statistik Waktu Layanan" << endl;
    cout << string(55, '=') << endl;
    cout << left << setw(40) << "Total Waktu Layanan" << ": " << s->total_waktu
         << " menit" << endl;
    cout << left << setw(40) << "Rata-Rata Waktu Layanan per Mahasiswa" << ": ";
    if (s->total_mahasiswa_selesai > 0) {
        cout << fixed << setprecision(1)
             << float(s->total_waktu) / s->total_mahasiswa_selesai;
    } else {
        cout << "0.0";
    }
    cout << " menit" << endl;
    cout << left << setw(40) << "Waktu Layanan Tertinggi" << ": "
         << s->max_waktu << " menit" << endl;
    cout << left << setw(40) << "Waktu Layanan Terendah" << ": "
         << (s->min_waktu == 0 && s->total_mahasiswa_selesai == 0
                 ? 0
                 : s->min_waktu)
         << " menit" << endl;
    cout << string(55, '=') << endl;
    pause();
}

void statistikBerdasarkanMahasiswa(Statistik *s) {
    clearScreen();
    cout << string(60, '=') << endl;
    cout << "   Statistik Berdasarkan Mahasiswa" << endl;
    cout << string(60, '=') << endl;

    if (s->jumlah_mahasiswa == 0) {
        cout << "Belum ada mahasiswa yang dilayani." << endl;
    } else {
        for (int i = 0; i < s->jumlah_mahasiswa; i++) {
            cout << left << setw(20) << "Nama" << ": " << s->data[i].nama
                 << endl;
            cout << left << setw(20) << "NIM" << ": " << s->data[i].nim << endl;
            cout << string(60, '-') << endl;
            if (s->data[i].jumlah_keperluan == 0) {
                cout << "  Belum ada konsultasi tercatat untuk mahasiswa ini."
                     << endl;
            } else {
                for (int j = 0; j < s->data[i].jumlah_keperluan; j++) {
                    cout << "> Keperluan\t\t: "
                         << s->data[i].konsultasi[j].keperluan << endl;
                    cout << "> Jumlah Konsultasi\t: "
                         << s->data[i].konsultasi[j].jumlah_konsultasi
                         << " kali" << endl;
                    cout << "> Total Waktu\t\t: "
                         << s->data[i].konsultasi[j].total_waktu_layanan
                         << " menit" << endl;
                    if (j < s->data[i].jumlah_keperluan - 1)
                        cout << "  ---" << endl;
                }
            }
            cout << string(60, '-') << endl;
        }
    }
    pause();
}

void menuStatistik(Queue *q, Statistik *s) {
    int pilihan;
    do {
        clearScreen();
        cout << string(50, '=') << endl;
        cout << "\tSTATISTIK ANTRIAN KONSULTASI" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Statistik Jumlah Antrian" << endl;
        cout << "2. Statistik Keperluan Konsultasi" << endl;
        cout << "3. Statistik Waktu Layanan" << endl;
        cout << "4. Statistik Berdasarkan Mahasiswa" << endl;
        cout << "0. Kembali" << endl;
        cout << string(50, '=') << endl;
        cout << "Pilih Menu (0-4) : ";
        cin >> pilihan;

        if (cin.fail()) {
            cout << "Input tidak valid. Harap masukkan angka." << endl;
            cin.clear();
            cin.ignore();
            pilihan = -1;
            pause();
            continue;
        }

        switch (pilihan) {
        case 1:
            statistikJumlahAntrian(q, s);
            break;
        case 2:
            statistikKeperluanKonsultasi(s);
            break;
        case 3:
            statistikWaktuLayanan(s);
            break;
        case 4:
            statistikBerdasarkanMahasiswa(s);
            break;
        case 0:
            return;
        default:
            cout << "Pilihan tidak valid." << endl;
            pause();
            break;
        }
    } while (pilihan != 0);
}

void mockupAntrian(Queue *q) {
    struct MockData {
        int index_mahasiswa;
        string keperluan;
        int estimasi;
    } mockList[] = {
        {0, "Skripsi", 30},
        {
            1,
            "Tugas Akhir",
            20,
        },
        {2, "Konsultasi Mata Kuliah", 15},
        {3, "Lainnya", 25},
        {4, "Skripsi", 30},
        {5, "Tugas Akhir", 20},
        {6, "Konsultasi Mata Kuliah", 15},
        {7, "Lainnya", 25},
        {8, "Skripsi", 30},
        {9, "Tugas Akhir", 20},
    };
    for (const auto &mock : mockList) {
        if (mock.index_mahasiswa < MAKS_MAHASISWA) {
            Mahasiswa mhs = dataMahasiswa[mock.index_mahasiswa];
            mhs.keperluan = mock.keperluan;
            mhs.estimasi_waktu = mock.estimasi;

            if (mock.keperluan == "Skripsi") {
                mhs.prioritas = 1;
            } else if (mock.keperluan == "Tugas Akhir") {
                mhs.prioritas = 2;
            } else if (mock.keperluan == "Konsultasi Mata Kuliah") {
                mhs.prioritas = 3;
            } else if (mock.keperluan == "Lainnya") {
                mhs.prioritas = 4;
            }

            enqueue(q, mhs);
        }
    }
}

void tambahAntrian(Queue *q, Statistik *s) {
    if (isFull(q)) {
        cout << "Antrian penuh!" << endl;
        pause();
        return;
    }

    Mahasiswa mhs;
    int pilihan_mhs_idx;
    clearScreen();
    displayMahasiswaList();

    do {
        cout << "Pilih Mahasiswa (1-" << MAKS_MAHASISWA << ", 0 = Kembali): ";
        cin >> pilihan_mhs_idx;
        if (cin.fail() || pilihan_mhs_idx < 0 ||
            pilihan_mhs_idx > MAKS_MAHASISWA) {
            cout << "Input tidak valid. Harap masukkan angka yang benar.\n\n";
            cin.clear();
            cin.ignore();
            pilihan_mhs_idx = -1;
        } else if (pilihan_mhs_idx == 0) {
            return;
        }
    } while (pilihan_mhs_idx < 1 || pilihan_mhs_idx > MAKS_MAHASISWA);

    mhs = dataMahasiswa[pilihan_mhs_idx - 1];

    cout << "\nPilih keperluan konsultasi:\n";
    cout << string(50, '-') << endl;
    cout << "1. Skripsi                 (Estimasi 30 Menit)\n";
    cout << "2. Tugas Akhir             (Estimasi 20 Menit)\n";
    cout << "3. Konsultasi Mata Kuliah  (Estimasi 15 Menit)\n";
    cout << "4. Lainnya                 (Estimasi 25 Menit)\n";
    cout << string(50, '-') << endl;

    int pilihan_keperluan;
    do {
        cout << "Masukkan Pilihan (1 - 4, 0 = Kembali): ";
        cin >> pilihan_keperluan;
        if (cin.fail() || pilihan_keperluan < 0 || pilihan_keperluan > 4) {
            cout << "Pilihan tidak valid.\n\n";
            cin.clear();
            cin.ignore();
            pilihan_keperluan = -1;
        } else if (pilihan_keperluan == 0) {
            return;
        }
    } while (pilihan_keperluan < 1 || pilihan_keperluan > 4);

    switch (pilihan_keperluan) {
    case 1:
        mhs.keperluan = "Skripsi";
        mhs.estimasi_waktu = 30;
        mhs.prioritas = 1;
        break;
    case 2:
        mhs.keperluan = "Tugas Akhir";
        mhs.estimasi_waktu = 20;
        mhs.prioritas = 2;
        break;
    case 3:
        mhs.keperluan = "Konsultasi Mata Kuliah";
        mhs.estimasi_waktu = 15;
        mhs.prioritas = 3;
        break;
    case 4:
        mhs.keperluan = "Lainnya";
        mhs.estimasi_waktu = 25;
        mhs.prioritas = 4;
        break;
    }
    enqueue(q, mhs);
    pause();
}

void prosesAntrian(Queue *q, Statistik *s) {
    if (isEmpty(q)) {
        cout << "\nTidak ada antrian yang perlu diproses." << endl;
        cout << "Silakan tambahkan antrian terlebih dahulu melalui menu "
                "'Tambah Antrian'."
             << endl;
        pause();
        return;
    }

    Mahasiswa mhs_diproses = q->data[q->head];
    int waktu_aktual;
    if (mhs_diproses.keperluan == "Lainnya") {
        waktu_aktual = getRandomNumber(1, 25);
    } else {
        waktu_aktual = getRandomNumber(mhs_diproses.estimasi_waktu, 5);
    }

    clearScreen();
    cout << string(50, '=') << endl;
    cout << "PROSES ANTRIAN KONSULTASI" << endl;
    cout << string(50, '=') << endl;
    cout << left << setw(25) << "Nama" << ": " << mhs_diproses.nama << endl;
    cout << left << setw(25) << "NIM" << ": " << mhs_diproses.nim << endl;
    cout << left << setw(25) << "Keperluan" << ": " << mhs_diproses.keperluan
         << endl;
    cout << string(50, '-') << endl;
    cout << left << setw(25) << "Estimasi Waktu" << ": "
         << mhs_diproses.estimasi_waktu << " Menit" << endl;
    cout << left << setw(25) << "Waktu Aktual" << ": " << waktu_aktual
         << " Menit" << endl;
    cout << string(50, '-') << endl;
    cout << left << setw(25) << "Status" << ": Konsultasi Selesai" << endl;
    cout << string(50, '-') << endl;

    updateStatistik(s, mhs_diproses, waktu_aktual);

    s->total_mahasiswa_selesai++;

    if (mhs_diproses.keperluan == "Skripsi") {
        s->count_skripsi++;
    } else if (mhs_diproses.keperluan == "Tugas Akhir") {
        s->count_tugas_akhir++;
    } else if (mhs_diproses.keperluan == "Konsultasi Mata Kuliah") {
        s->count_konsultasi_mk++;
    } else if (mhs_diproses.keperluan == "Lainnya") {
        s->count_lainnya++;
    }

    dequeue(q, s);
    if (isEmpty(q)) {
        cout << "\nSeluruh antrian telah selesai diproses." << endl;
        cout
            << "Silakan menambahkan antrian baru melalui menu 'Tambah Antrian'."
            << endl;
    } else {
        cout << "\nAntrian berikutnya adalah mahasiswa "
             << q->data[q->head].nama << " (" << q->data[q->head].nim << ")."
             << endl;
    }
    pause();
}

void resetQueue(Queue *q) {
    q->head = -1;
    q->tail = -1;
    cout << "\nAntrian telah direset." << endl;
    cout << "Silakan tambahkan antrian baru." << endl;
    pause();
}

int main() {
    Queue antrian;
    Statistik stats;

    // Inisiasi Statistik
    stats.jumlah_mahasiswa = 0;
    stats.total_mahasiswa_terdaftar = MAKS_MAHASISWA;
    stats.total_mahasiswa_selesai = 0;
    stats.total_waktu = 0;
    stats.max_waktu = 0;
    stats.min_waktu = 0;
    stats.count_skripsi = 0;
    stats.count_tugas_akhir = 0;
    stats.count_konsultasi_mk = 0;
    stats.count_lainnya = 0;
    for (int i = 0; i < MAKS_MAHASISWA; i++) {
        stats.data[i].jumlah_keperluan = 0;
    }

    // Inisiasi Antrian
    initializeQueue(&antrian);
    mockupAntrian(&antrian);

    int pilihan;
    do {
        clearScreen();
        cout << string(50, '=') << endl;
        cout << "\tSELAMAT DATANG DI PROGRAM\n";
        cout << "\tKONSULTASI DOSEN - JURUSAN TRPL\n";
        cout << string(50, '=') << endl;
        cout << "1. Tambah Antrian" << endl;
        cout << "2. Proses Antrian" << endl;
        cout << "3. Statistik Antrian" << endl;
        cout << "4. Daftar Antrian" << endl;
        cout << "5. Reset Antrian" << endl;
        cout << "6. Keluar" << endl;
        cout << string(50, '=') << endl;
        cout << "Pilih Menu (1-6) : ";
        cin >> pilihan;

        if (cin.fail()) {
            cout << "Input tidak valid. Harap masukkan angka." << endl;
            cin.clear();
            cin.ignore();
            pilihan = -1;
            pause();
            continue;
        }

        switch (pilihan) {
        case 1:
            tambahAntrian(&antrian, &stats);
            break;
        case 2:
            prosesAntrian(&antrian, &stats);
            break;
        case 3:
            menuStatistik(&antrian, &stats);
            break;
        case 4:
            displayQueue(&antrian);
            break;
        case 5:
            resetQueue(&antrian);
            break;
        case 6:
            cout << "\nTerima kasih telah menggunakan program ini. Keluar..."
                 << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            pause();
            break;
        }
    } while (pilihan != 6);
    return 0;
}