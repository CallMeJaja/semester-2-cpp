#include "iostream"

using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    int nilai;
};

int main() {
    Mahasiswa mhs[20];
    int x, i = 0;
    char ulang;

    do {
        cout << "Masukkan NIM: ", cin >> mhs[i].nim;
        cout << "Masukkan Nama: ", cin >> mhs[i].nama;
        cout << "Masukkan Nilai: ", cin >> mhs[i].nilai;
        cout << "Apakah ingin mengulang? (y/n): ", cin >> ulang;
        i++;
    } while (ulang == 'y' || ulang == 'Y');

    cout << "\nDaftar Mahasiswa" << endl;
    cout << "==========|====================|==========" << endl;
    cout << "   NIM    |        Nama        |   Nilai  " << endl;

    for (x = 0; x < i; x++) {
        printf("%10s|%20s|%8i\n", mhs[x].nim, mhs[x].nama, mhs[x].nilai);
    }
    cout << string(20, '=') << endl;
    cout << mhs[0].nama.length();
    return 0;
}