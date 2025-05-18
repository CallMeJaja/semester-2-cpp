#include "iomanip"
#include "iostream"
#include "string"

#define MAKS_ANTRIAN 10
#define MAKS_TIKET 10
#define MAKS_FILM 10

using namespace std;

const int HARGA_DEWASA = 40000;
const int HARGA_ANAK = 25000;
const int BATAS_USIA_ANAK = 5;

struct Film {
    string judul;
    string rating;
    int usiaMininum;
};

Film daftarFilm[MAKS_FILM] = {
    {"Jumbo", "SU", 0},
    {"Komang", "R13+", 13},
    {"Qodrat 2", "R13+", 13},
    {"Pabrik Gula", "D21+", 21},
    {"Rumah untuk Alie", "R13+", 13},
    {"Mendadak Dangdut", "R13+", 13},
    {"Pengepungan di Bukit Duri", "D17+", 17},
    {"Penjagal Iblis: Dosa Turunan", "D17+", 17},
    {"Perang Kota", "D17+", 17},
    {"Sah! Katanya...", "R13+", 13},
};

int jumlahFilmAktif = 10;

struct Tiket {
    int usia;
    int harga;
    string kategori;
};

struct Transaksi {
    string nama_pembeli;
};

struct Antrian {
    int head;
    int tail;
    Transaksi data[MAKS_ANTRIAN];
} antrian;

void inisialisasi() {
    antrian.head = -1;
    antrian.tail = -1;
}

bool isEmpty() { return antrian.tail == -1; }

bool isFull() { return antrian.tail == MAKS_ANTRIAN - 1; }

void enQueue(Transaksi data) {
    if (isFull()) {
        cout << "Antrian sudah penuh" << endl;
        system("pause");
        return;
    }

    if (isEmpty()) {
        antrian.head = 0;
    }

    antrian.tail++;
    antrian.data[antrian.tail] = data;
    cout << data.nama_pembeli << " telah ditambahkan ke antrian.\n\n";
    system("pause");
}

void deQueue() {
    if (isEmpty()) {
        return;
    }

    for (int i = antrian.head; i < antrian.tail; i++) {
        antrian.data[i] = antrian.data[i + 1];
    }
    antrian.tail--;

    if (antrian.tail < 0) {
        antrian.head = -1;
    }
}

void clearQueue() {
    antrian.head = -1;
    antrian.tail = -1;
    cout << "\nSemua data antrian telah dihapus.\n";
    system("pause");
}

void prosesPenjualan() {
    if (isEmpty()) {
        cout << "\nAntrian kosong, tidak ada yang bisa diproses.\n";
        system("pause");
        return;
    }

    Transaksi pembeli = antrian.data[antrian.head];
    cout << "\nSedanng Melayani Antrian: " << pembeli.nama_pembeli << endl;

    cout << "\n--- Daftar Film Aktif ---" << endl;
    for (int i = 0; i < jumlahFilmAktif; i++) {
        cout << i + 1 << ". " << daftarFilm[i].judul << " ("
             << daftarFilm[i].rating << ")" << endl;
    }

    int pilihanFilm;
    int indeksFilm;

    while (true) {
        cout << "\nPilih Nomor Film (1-" << jumlahFilmAktif << "): ",
            cin >> pilihanFilm;
        indeksFilm = pilihanFilm - 1;

        if (pilihanFilm >= 1 && pilihanFilm <= jumlahFilmAktif) {
            break;
        } else {
            cout << "Pilihan tidak valid. Silahkan coba lagi.\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }

    Film filmDipilih = daftarFilm[indeksFilm];
    cout << "\nFilm yang dipilih: " << filmDipilih.judul << endl;

    int jumlahTiket;
    while (true) {
        cout << "\nBerapa banyak tiket yang ingin dibeli? (Maks " << MAKS_TIKET
             << "): ",
            cin >> jumlahTiket;

        if (jumlahTiket > 0 && jumlahTiket <= MAKS_TIKET) {
            break;
        } else {
            cout << "Jumlah tiket tidak valid. Silahkan coba lagi.\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }

    Tiket daftarTiket[MAKS_TIKET];
    bool transaksiBatal = false;

    for (int i = 0; i < jumlahTiket; i++) {
        bool usiaValid = false;
        while (!usiaValid) {
            cout << "\nMasukkan Usia Penonton Ke-" << i + 1 << ": ";
            cin >> daftarTiket[i].usia;

            if (cin.fail() || daftarTiket[i].usia <= 0) {
                cout << "Usia tidak valid. Silahkan coba lagi.\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            cin.ignore();

            if (daftarTiket[i].usia < filmDipilih.usiaMininum) {
                cout << "Usia " << daftarTiket[i].usia
                     << " tahun tidak cukup untuk rating " << filmDipilih.rating
                     << ".\n";

                char pilihanUlang;
                while (true) {
                    cout << "Input ulang usia penonton ini? (Y/N): ";
                    cin >> pilihanUlang;
                    pilihanUlang = toupper(pilihanUlang);
                    if (pilihanUlang == 'Y') {
                        break;
                    } else if (pilihanUlang == 'N') {
                        transaksiBatal = true;
                        break;
                    } else {
                        cout << "Pilihan tidak valid (Y/N).\n";
                        cin.clear();
                        cin.ignore();
                    }
                }
                if (transaksiBatal) {
                    break; // Keluar dari loop for jumlahTiket
                }
            } else {
                usiaValid =
                    true; // Usia valid, keluar dari loop while (!usiaValid)
                if (daftarTiket[i].usia <= BATAS_USIA_ANAK) {
                    daftarTiket[i].harga = HARGA_ANAK;
                    daftarTiket[i].kategori = "Anak";
                } else {
                    daftarTiket[i].harga = HARGA_DEWASA;
                    daftarTiket[i].kategori = "Dewasa";
                }
            }
        }

        if (transaksiBatal) {
            break;
        }
    }

    if (transaksiBatal) {
        cout << "\nTransaksi dibatalkan.\n";
        system("pause");
        return;
    }

    cout << "\n--- Ringkasan Pesanan ---" << endl;
    cout << "=======================================================" << endl;
    cout << "Antrian Dilayani : " << pembeli.nama_pembeli << endl;
    cout << "Film             : " << filmDipilih.judul << " ("
         << filmDipilih.rating << ")" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << left << setw(8) << "Usia" << setw(10) << "Kategori" << setw(10)
         << "Jumlah" << setw(15) << "Harga Satuan" << setw(15) << "Subtotal"
         << endl;
    cout << "-------------------------------------------------------" << endl;

    int totalBelanja = 0;
    for (int i = 0; i < jumlahTiket; i++) {
        cout << left << setw(8) << daftarTiket[i].usia << setw(10)
             << daftarTiket[i].kategori << setw(10) << 1 << "Rp " << setw(12)
             << daftarTiket[i].harga << "Rp " << setw(12)
             << daftarTiket[i].harga << endl;
        totalBelanja += daftarTiket[i].harga;
    }
    cout << "=======================================================" << endl;

    cout << "\nTotal Belanja \t\t: Rp " << totalBelanja << endl;

    char isMember;
    float diskon = 0;
    while (true) {
        cout << "Apakah Member? (Y/N) \t: ", cin >> isMember;
        if (isMember == 'Y' || isMember == 'y') {
            diskon = 0.1f * totalBelanja;
        } else if (isMember == 'N' || isMember == 'n') {
            diskon = 0;
        } else {
            cout << "Pilihan tidak valid (Y/N).\n";
            continue;
        }
        break;
    }

    cout << "Diskon \t\t\t: Rp " << int(diskon) << endl;

    int totalBayar = totalBelanja - diskon;

    cout << "-------------------------------------------------------" << endl;
    cout << "Total Pembayaran \t: Rp " << totalBayar << endl;
    cout << "-------------------------------------------------------" << endl;

    int uangPembeli;

    while (true) {
        cout << "Masukkan Uang Pembeli \t: Rp ", cin >> uangPembeli;
        if (uangPembeli < totalBayar) {
            cout << "Uang tidak cukup (Kurang Rp " << totalBayar - uangPembeli
                 << "). Silahkan masukkan lagi.\n\n";
            continue;
        } else {
            break;
        }
    }
    cout << "Kembalian \t\t: Rp " << uangPembeli - totalBayar << endl;
    cout << "\n=======================================================" << endl;
    cout << "           Terima Kasih! Selamat Menonton!               " << endl;
    cout << "=======================================================" << endl;
    cout << "\nData " << pembeli.nama_pembeli
         << " telah diproses dan dihapus dari antrian.\n\n";
    deQueue();
    system("pause");
}

int main() {
    inisialisasi();
    int pilihan;
    Transaksi transaksi;

    while (true) {
        system("cls");
        cout << "===== Program Antrian Tiket Bioskop =====\n";
        cout << "[1] Tambah Antrian\n[2] Proses Antrian\n[3] Hapus Semua "
                "Antrian\n[4] Keluar\n";

        if (isEmpty()) {
            cout << "\nDaftar Antrian:\n(Kosong)\n";
        } else {
            cout << "\nDaftar Antrian:\n";
            for (int i = antrian.head; i <= antrian.tail; i++) {
                cout << "[" << (i - antrian.head + 1) << "] "
                     << antrian.data[i].nama_pembeli << endl;
            }
        }

        cout << "\nPilih Menu: ", cin >> pilihan;
        switch (pilihan) {
        case 1:
            cout << "\nMasukkan Nama Pembeli: ";
            cin.ignore();
            getline(cin, transaksi.nama_pembeli);
            enQueue(transaksi);
            break;
        case 2:
            prosesPenjualan();
            break;
        case 3:
            if (isEmpty()) {
                cout << "\nAntrian kosong, tidak ada yang bisa dihapus.\n";
                system("pause");
                break;
            }
            clearQueue();
            break;
        case 4:
            cout << "\nTerima kasih! Keluar dari program.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid. Silakan masukkan angka 1-4.\n";
            break;
        }
    }

    return 0;
}