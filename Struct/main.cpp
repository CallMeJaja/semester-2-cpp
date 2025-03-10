#include "iostream"

using namespace std;

struct Mahasiswa {
    char nim[11], nama[45];
    int nilai;
} a;

int main() {
    cout << "Masukkan NIM: ", cin >> a.nim;
    cout << "Masukkan NAMA: ", cin >> a.nama;
    cout << "Masukkan NIlAI: ", cin >> a.nilai;

    cout << "\nNIM: " << a.nim << endl;
    cout << "NAMA: " << a.nama << endl;
    cout << "NILAI: " << a.nilai << endl;
    return 0;
}