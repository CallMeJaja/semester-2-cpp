#include "iostream"
#include "string"
#include "windows.h"
#define MAX 10

using namespace std;

typedef struct queue {
    int tail;
    int head;
    string data[MAX];
} queue;

queue antri;

void inisiasi() {
    antri.tail = -1;
    antri.head = -1;
}

int isEmpty() {
    if (antri.tail == -1) {
        antri.head = -1;
        return 1;
    } else {
        return 0;
    }
}

int isFull() {
    if (antri.tail == MAX - 1) {
        return 1;
    } else {
        return 0;
    }
}

void enqueue(string a) {
    if (!isFull()) {
        antri.head = 0;
        antri.tail = antri.tail + 1;
        antri.data[antri.tail] = a;
    } else {
        printf("Antrian sudah penuh.\n");
        Sleep(1000);
    }
}

void dequeue() {
    if (!isEmpty()) {
        printf("Data %s di ambil dari antrian.\n",
               antri.data[antri.head].c_str());

        for (int i = antri.head; i <= antri.tail; i++) {
            antri.data[i] = antri.data[i + 1];
        }

        antri.tail--;
    } else {
        printf("\nAntrian sudah kosong, tidak ada data yang bisa diambil.");
    }
    Sleep(2000);
}

void clear() {
    antri.head = -1;
    antri.tail = -1;
    printf("\nSemua data antrian sudah terhapus.");
    Sleep(2000);
}

int main() {
    inisiasi();

    int pilihan;
    string a;

    while (true) {
        system("cls");
        cout << "===== Program Queue =====\n";
        cout << "\t1. Input Queue\n\t2. Handle Queue\n\t3. Clear Queue\n\t4. "
                "Exit"
             << endl;
        cout << "--------------------------------" << endl;

        if (!isEmpty()) {
            printf("\tAntrian\nExit | ");
            for (int i = 0; i <= antri.tail; i++) {
                printf("%s <- ", antri.data[i].c_str());
            }
        } else {
            cout << "Antrian dalam keadaan kosong." << endl;
        }

        cout << "\nMasukkan Pilihan: ", cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1, '\n');
        }

        switch (pilihan) {
        case 1: {
            cout << "Masukkan Data: ";
            cin.ignore();
            getline(cin, a);
            enqueue(a);
            break;
        }
        case 2:
            dequeue();
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