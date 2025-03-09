#include "iomanip"
#include "iostream"

using namespace std;

struct Buku {
    string kode, judul;
    int harga, jumlah, total;
} buku;

int main() {
    int n, i, pembayaran, total_belanja = 0;
    float diskon;
    cout << "Masukkan Jumlah Buku: ", cin >> n;
    Buku book[n];

    for (i = 0; i < n; i++) {
        cout << "\nINPUT BUKU #" << i + 1 << endl;
        cout << "Masukkan Kode Buku: ", cin >> book[i].kode;
        cin.ignore(1000, '\n');
        cout << "Masukkan Judul Buku: ";
        getline(cin, book[i].judul);
        cout << "Masukkan Harga Buku: ", cin >> book[i].harga;
        cout << "Masukkan Jumlah Buku: ", cin >> book[i].jumlah;

        book[i].total = book[i].jumlah * book[i].harga;
        total_belanja = total_belanja + book[i].total;
    }

    cout << setw(10) << left << "\nKode" << setw(25) << left << "Judul"
         << setw(15) << left << "Harga" << setw(10) << left << "Jumlah"
         << setw(10) << left << "Total" << endl;

    for (i = 0; i < n; i++) {
        cout << setw(9) << left << book[i].kode << setw(25) << left
             << book[i].judul << setw(15) << left << book[i].harga << setw(10)
             << left << book[i].jumlah << setw(10) << left
             << book[i].harga * book[i].jumlah << endl;
    }
    cout << setw(60) << left << "\nTotal Belanja" << total_belanja << endl;

    if (total_belanja >= 500000) {
        diskon = 0.2;
    } else if (total_belanja >= 250000 && total_belanja < 500000) {
        diskon = 0.15;
    } else if (total_belanja >= 100000 && total_belanja < 250000) {
        diskon = 0.1;
    } else {
        diskon = 0;
    }

    cout << "\nDiskon \t\t: " << diskon * total_belanja << endl;
    cout << "Total Pembayaran \t\t: " << total_belanja - diskon << endl;
    cout << "Input Pembayaran \t: ", cin >> pembayaran;
    cout << "Kembalian \t\t: " << pembayaran - (total_belanja - diskon) << endl;

    return 0;
}