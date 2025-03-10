#include "iomanip"
#include "iostream"

using namespace std;

struct Nilai {
    float tugas;
    float uts;
    float uas;
    float absen;
};

struct Mahasiswa {
    char nim[15];
    char nama[100];
    Nilai dataNilai;
    float nilaiAkhir;
    char indeks;
};

int main() {
    int n, i;
    float na;
    cout << "Masukkan Jumlah Mahasiswa \t: ", cin >> n;
    Mahasiswa mhs[n];

    for (i = 0; i < n; i++) {
        cout << "\nMasukkan NIM \t\t: ", cin >> mhs[i].nim;
        cout << "Masukkan Nama \t\t: ", cin >> mhs[i].nama;
        cout << "Masukkan Nilai Absen \t: ", cin >> mhs[i].dataNilai.absen;
        cout << "Masukkan Nilai Tugas \t: ", cin >> mhs[i].dataNilai.tugas;
        cout << "Masukkan Nilai UTS \t: ", cin >> mhs[i].dataNilai.uts;
        cout << "Masukkan Nilai UAS \t: ", cin >> mhs[i].dataNilai.uas;

        mhs[i].nilaiAkhir =
            (0.4 * mhs[i].dataNilai.tugas) + (0.1 * mhs[i].dataNilai.absen) +
            (0.3 * mhs[i].dataNilai.uts) + (0.2 * mhs[i].dataNilai.uas);

        if (mhs[i].nilaiAkhir >= 85 && mhs[i].nilaiAkhir <= 100) {
            mhs[i].indeks = 'A';
        } else if (mhs[i].nilaiAkhir >= 70 && mhs[i].nilaiAkhir < 85) {
            mhs[i].indeks = 'B';
        } else if (mhs[i].nilaiAkhir >= 55 && mhs[i].nilaiAkhir < 70) {
            mhs[i].indeks = 'C';
        } else if (mhs[i].nilaiAkhir >= 40 && mhs[i].nilaiAkhir < 55) {
            mhs[i].indeks = 'D';
        } else {
            mhs[i].indeks = 'E';
        }
    }

    cout << endl;

    cout << setw(10) << left << "NIM" << setw(25) << left << "Nama" << setw(6)
         << left << "NA" << setw(5) << left << "Index" << endl;

    for (i = 0; i < n; i++) {
        cout << setw(10) << left << mhs[i].nim << setw(25) << left
             << mhs[i].nama << setw(6) << left << mhs[i].nilaiAkhir << setw(5)
             << left << mhs[i].indeks << endl;
    }

    return 0;
}