#include "Windows.h"
#include "iostream"
#include "string"
#define MAKS_DATA 5

using namespace std;

struct Produk {
    string kode_produk;
    string nama_produk;
    long harga_produk;
    int jumlah_produk;
    int total_harga;
};

struct Transaksi {
    string nama_pembeli;
    int jumlah_produk;
    Produk daftar_produk[10];
};

typedef struct Antrian {
    int head;
    int tail;
    Transaksi data[MAKS_DATA];
} Antrian;

Antrian antrian;

void inisialisasi() {
    antrian.tail = -1;
    antrian.head = -1;
}

int isEmpty() {
    if (antrian.tail == -1) {
        antrian.head = -1;
        return 1;
    } else {
        return 0;
    }
}

int isFull() { return antrian.tail == MAKS_DATA - 1; }

void enQueue(Transaksi trx) {
    if (isFull()) {
        printf("Antrian sudah penuh.\n");
        Sleep(1500);
    } else {
        antrian.head = 0;
        antrian.tail += 1;
        antrian.data[antrian.tail] = trx;
    }
}

void deQueue() {
    if (isEmpty()) {
        printf("\nAntrian kosong, tidak ada data yang bisa diambil.\n");
    } else {
        printf("\nData %s telah diproses dan dihapus dari antrian.\n",
               antrian.data[antrian.head].nama_pembeli.c_str());

        for (int i = antrian.head; i < antrian.tail; i++) {
            antrian.data[i] = antrian.data[i + 1];
        }
        antrian.tail--;
    }
}

void clearQueue() {
    antrian.head = -1;
    antrian.tail = -1;
    printf("\nSemua data antrian telah dihapus.\n");
    Sleep(2000);
}

void prosesPenjualan() {
    if (isEmpty()) {
        printf("\nMaaf, tidak ada antrian yang tersedia.\n");
        return;
    }

    int total_belanja = 0, total_pembayaran = 0, uang_dibayar;
    float diskon;
    Transaksi &trx = antrian.data[antrian.head];

    printf("\nMemproses Antrian: %s\n", trx.nama_pembeli.c_str());

    printf("Masukkan banyak produk: "), cin >> trx.jumlah_produk;
    for (int i = 0; i < trx.jumlah_produk; i++) {
        Produk &produk = trx.daftar_produk[i];
        cin.ignore();
        printf("\nProduk ke-%d:\n", i + 1);

        printf("Kode Produk\t: ");
        getline(cin, produk.kode_produk);

        printf("Nama Produk\t: ");
        getline(cin, produk.nama_produk);

        printf("Harga Produk\t: ");
        cin >> produk.harga_produk;

        printf("Jumlah Produk\t: ");
        cin >> produk.jumlah_produk;

        produk.total_harga = produk.harga_produk * produk.jumlah_produk;
    }

    printf("\n%s\n", string(55, '=').c_str());
    printf("%-10s %-15s %-10s %-10s %-10s\n", "Kode", "Nama", "Harga", "Jumlah",
           "Total");
    printf("%s\n", string(55, '=').c_str());

    for (int i = 0; i < trx.jumlah_produk; i++) {
        Produk &produk = trx.daftar_produk[i];
        printf("%-10s %-15s %-10ld %-10d %-10d\n", produk.kode_produk.c_str(),
               produk.nama_produk.c_str(), produk.harga_produk,
               produk.jumlah_produk, produk.total_harga);

        total_belanja += produk.total_harga;
    }

    printf("%s\n", string(55, '=').c_str());
    printf("%-20s%34d\n", "Total Belanja", total_belanja);
    printf("%s", string(55, '=').c_str());

    if (total_belanja > 10000) {
        diskon = 0.07 * total_belanja;
    } else if (total_belanja >= 5000) {
        diskon = 0.05 * total_belanja;
    } else {
        diskon = 0;
    }

    total_pembayaran = total_belanja - diskon;

    printf("\n\nDiskon \t\t\t: Rp.%.0f", diskon);
    printf("\nTotal Pembayaran \t: Rp.%d", total_pembayaran);

input_uang:
    printf("\nUang Pembeli \t\t: Rp."), cin >> uang_dibayar;

    if (uang_dibayar >= total_pembayaran) {
        printf("Kembalian \t\t: Rp.%d\n", uang_dibayar - total_pembayaran);
    } else {
        printf("Uang Kurang \t\t: Rp.%d\n", total_pembayaran - uang_dibayar);
        goto input_uang;
    }

    deQueue();
}

int main() {
    inisialisasi();
    int pilihan;
    Transaksi transaksi;

    while (true) {
        system("cls");
        printf("====== Program Antrian Penjualan ======\nMENU\n");
        printf("[1] Tambah Antrian\n[2] Proses Antrian\n[3] Hapus Semua "
               "Antrian\n[4] Keluar\n");

        if (isEmpty()) {
            printf("\nBelum ada antrian.\n");
        } else {
            printf("\nDaftar Antrian:\n");
            for (int i = 0; i <= antrian.tail; i++) {
                printf("[%d] %s\n", i + 1,
                       antrian.data[i].nama_pembeli.c_str());
            }
        }

        printf("\nPilih Menu: ");
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            printf("\nMasukkan Nama Pembeli: ");
            cin.ignore();
            getline(cin, transaksi.nama_pembeli);
            enQueue(transaksi);
            system("pause");
            break;
        case 2:
            prosesPenjualan();
            system("pause");
            break;
        case 3:
            clearQueue();
            break;
        case 4:
            printf("\nTerima kasih telah menggunakan program.\n");
            Sleep(1000);
            return 0;
        default:
            printf("\nPilihan menu tidak valid.\n");
            Sleep(1000);
            break;
        }
    }

    return 0;
}
