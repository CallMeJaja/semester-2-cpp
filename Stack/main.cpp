#include "iostream"
#include "string"
#include "windows.h"
#define MAX_STACK 10

using namespace std;

struct stack {
    int top;
    string data[MAX_STACK];
} tumpuk;

void inisiasi() { tumpuk.top = -1; }

int isFull() {
    if (tumpuk.top == MAX_STACK - 1) {
        return 1;
    } else {
        return 0;
    }
}

int isEmpty() {
    if (tumpuk.top == -1) {
        return 1;
    } else {
        return 0;
    }
}

void push(string a) {
    if (!isFull()) {
        tumpuk.top += 1;
        tumpuk.data[tumpuk.top] = a;
    } else {
        cout << "Tumpukkan dalam stack sudah penuh." << endl;
        Sleep(1000);
    }
}

void pop() {
    if (!isEmpty()) {
        cout << "Data " << tumpuk.data[tumpuk.top] << " diambil dari stack."
             << endl;
        tumpuk.top--;
    } else {
        cout << "Stack sudah kosong, tidak ada data yang bisa diambil." << endl;
    }
}

void clear() {
    tumpuk.top = -1;
    cout << "Stack berhasil dikosongkan." << endl;
}

int main() {
    inisiasi();

    int pilihan;
    string a;

    while (true) {
        system("cls");
        cout << "===== Program Stack =====\n";
        cout << "\t1. Push\n\t2. Pop\n\t3. Clear\n\t4. Exit" << endl;
        cout << "--------------------------------" << endl;

        if (!isEmpty()) {
            for (int i = tumpuk.top; i >= 0; i--) {
                cout << "[" << tumpuk.data[i] << "]" << endl;
            }
        } else {
            cout << "Stack dalam keadaan kosong." << endl;
        }

        cout << "Masukkan Pilihan: ", cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1, '\n');
        }

        switch (pilihan) {
        case 1: {
            cout << "Masukkan Data: ";
            cin.ignore();
            getline(cin, a);
            push(a);
            break;
        }
        case 2:
            pop();
            break;
        case 3:
            clear();
            break;
        case 4:
            cout << "Keluar dari program." << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid." << endl;
            break;
        }
    }

    return 0;
}