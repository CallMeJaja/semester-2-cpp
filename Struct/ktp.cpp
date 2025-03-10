#include "iomanip"
#include "iostream"
#include "windows.h"

using namespace std;

void gotoxy(int x, int y) {
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = x;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

struct TTL {
    string tempat_lahir;
    int tanggal;
    int bulan;
    int tahun;
};

struct Alamat {
    char rt[3];
    char rw[3];
    string kelurahan;
    string kecamatan;
};

struct KTP {
    char nik[17];
    char nama[100];
    TTL ttl;
    string jenis_kelamin;
    Alamat alamat;
    string agama;
    char status[15];
    string pekerjaan;
    string kewarganegaraan;
    char expire[20];
};

int main() {
    KTP ktp;

    cout << "Program KTP" << endl;
    cout << "Input NIK \t\t: ", cin >> ktp.nik;
    cin.ignore();
    cout << "Input Nama \t\t: ", cin.getline(ktp.nama, 100);
    cout << "Input Tempat Lahir \t: ", cin >> ktp.ttl.tempat_lahir;
    cout << "Input Tanggal Lahir \t: ", cin >> ktp.ttl.tanggal;
    cout << "Input Bulan Lahir \t: ", cin >> ktp.ttl.bulan;
    cout << "Input Tahun Lahir \t: ", cin >> ktp.ttl.tahun;
    cout << "Jenis Kelamin \t\t: ", cin >> ktp.jenis_kelamin;
    cout << "Input RT \t\t: ", cin >> ktp.alamat.rt;
    cout << "Input RW \t\t: ", cin >> ktp.alamat.rw;
    cout << "Input Keluraha/Desa \t: ", cin >> ktp.alamat.kelurahan;
    cout << "Input Kecamatan \t: ", cin >> ktp.alamat.kecamatan;
    cout << "Input Agama \t\t: ", cin >> ktp.agama;
    cin.ignore();
    cout << "Input Status Perkawinan : ", cin.getline(ktp.status, 15);
    cout << "Input Pekerjaan \t: ", cin >> ktp.pekerjaan;
    cout << "Input Kewarganegaraan \t: ", cin >> ktp.kewarganegaraan;
    cin.ignore();
    cout << "Input Berlaku Hingga \t: ", cin.getline(ktp.expire, 20);

    cout << endl;
    cout << setw(40) << "PROVINSI JAWA BARAT" << endl;
    cout << setw(42) << "KABUPATEN PURWAKARATA" << endl;
    cout << setw(20) << "NIK \t\t\t: " << ktp.nik << endl;
    cout << setw(20) << "Nama \t\t: " << ktp.nama << endl;
    cout << setw(31) << "Tempat/Tgl Lahir \t: " << ktp.ttl.tempat_lahir << ", "
         << ktp.ttl.tanggal << "-" << ktp.ttl.bulan << "-" << ktp.ttl.tahun
         << endl;
    cout << setw(22) << "Alamat \t\t: " << ktp.ttl.tempat_lahir << endl;
    cout << setw(24) << "RT/RW \t\t: " << ktp.alamat.rt << "/" << ktp.alamat.rw
         << endl;
    cout << setw(27) << "Kel/Desa \t\t: " << ktp.alamat.kelurahan << endl;
    cout << setw(27) << "Kecamatan \t: " << ktp.alamat.kecamatan << endl;
    cout << setw(21) << "Agama \t\t: " << ktp.agama << endl;
    cout << setw(32) << "Status Perkawinan \t: " << ktp.status << endl;
    cout << setw(25) << "Pekerjaan \t\t: " << ktp.pekerjaan << endl;
    cout << setw(30) << "Kewarganegaraan \t: " << ktp.kewarganegaraan << endl;
    cout << setw(29) << "Berlaku Hingga \t: " << ktp.expire << endl;
    return 0;
}