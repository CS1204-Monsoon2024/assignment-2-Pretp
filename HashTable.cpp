#include <iostream>

using namespace std;

#include <iostream>

using namespace std;

struct HashNode {
    int key;
    bool isActive; // True if the slot is actively holding a value, false if empty or deleted
};

class HashTable {
private:
    HashNode* table;
    int size;
    int capacity;

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
        HashNode* oldTable = table;
        table = new HashNode[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i].isActive = false;
        }
        size = 0;

        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i].isActive) {
                insert(oldTable[i].key);
            }
        }
        delete[] oldTable;
    }

public:
    HashTable(int initialCapacity) : capacity(initialCapacity), size(0) {
        table = new HashNode[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i].isActive = false;
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
            if (!table[probeIndex].isActive) {
                table[probeIndex].key = key;
                table[probeIndex].isActive = true;
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

        table[index].isActive = false;
        size--;
    }

    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (i < capacity) {
            int probeIndex = (index + i * i) % capacity;
            if (!table[probeIndex].isActive) {
                return -1;
            }
            if (table[probeIndex].key == key) {
                return probeIndex;
            }
            i++;
        }

        return -1;
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (!table[i].isActive) {
                cout << "- ";
            } else {
                cout << table[i].key << " ";
            }
        }
        cout << endl;
    }
};
