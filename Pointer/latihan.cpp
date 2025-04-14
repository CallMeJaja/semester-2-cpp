#include "iostream"

using namespace std;

void tambah(int *a, int *b) { printf("Hasil: %i \n", *a + *b); }

void kurang(int *a, int *b) { printf("Hasil: %i \n", *a - *b); }

int main() {
    char ulang;
    do {
        int q;
        int nilaiA;
        int nilaiB;
        cout << "\nMENU \n1. Penjumlahan\n2. Pengurangan" << endl;
        cout << "Pilih Menu: ", cin >> q;

        cout << "\nInput Nilai A: ", cin >> nilaiA;
        cout << "Input Nilai B: ", cin >> nilaiB;

        switch (q) {
        case 1:
            tambah(&nilaiA, &nilaiB);
            break;
        case 2:
            kurang(&nilaiA, &nilaiB);
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }

        cout << "\nIngin Mengulang ? (y/n): ", cin >> ulang;
    } while (ulang == 'y' || ulang == 'Y');

    return 0;
}