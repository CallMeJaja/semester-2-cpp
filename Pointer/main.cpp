#include "iostream"

using namespace std;

int main() {
    int n, i, jumlah = 0;

    cout << "Input N: ", cin >> n;
    int nilai[n], *p;
    p = &nilai[0];

    for (i = 0; i < n; i++) {
        cout << "Input Nilai: ", cin >> nilai[i];
    }

    cout << endl;

    for (i = 0; i < n; i++) {
        jumlah += nilai[i];
        cout << "Nilai: " << *(p + i) << " ada di alamat: " << p + i << endl;
    }

    cout << "Jumlah: " << jumlah << endl;

    return 0;
}