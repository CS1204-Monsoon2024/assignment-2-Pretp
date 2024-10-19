#include <iostream>

using namespace std;

class HashTable {
private:
    int* table;
    int size;
    int capacity;
    const int EMPTY = -1;
    const int DELETED = -2;

    int hashFunction(int key) {
        return key % capacity;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }
    
    

    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    void resize() {
        int oldCapacity = capacity;
        capacity = nextPrime(2 * capacity);
        int* oldTable = table;
        table = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = EMPTY;
        }
        size = 0;

        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                insert(oldTable[i]);
            }
        }
        delete[] oldTable;
    }

public:
    HashTable(int initialCapacity) : capacity(initialCapacity), size(0) {
        table = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = EMPTY;
        }
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(int key) {
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed\n";
            return;
        }

        if (size >= 0.8 * capacity) {
            resize();
        }
        
        int index = hashFunction(key);
        int i = 0;

        while (i < capacity) {
            int probeIndex = (index + i * i) % capacity;
            if (table[probeIndex] == EMPTY || table[probeIndex] == DELETED) {
                table[probeIndex] = key;
                size++;
                return;
            }
            i++;
        }

        cout << "Max probing limit reached!\n";
    }

    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            cout << "Element not found\n";
            return;
        }

        table[index] = DELETED;
        size--;
    }

    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (i < capacity) {
            int probeIndex = (index + i * i) % capacity;
            if (table[probeIndex] == EMPTY) {
                return -1;
            }
            if (table[probeIndex] == key) {
                return probeIndex;
            }
            i++;
        }

        return -1;
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == EMPTY) {
                cout << "- ";
            } else if (table[i] == DELETED) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};
