/* Problem Statement
Implement a hash table using quadratic probing with formula:

h(k, i) = (h(k) + i*i) % m

Input Format
Same as previous.

Output Format
Result of SEARCH operations.

Sample Input
7
4
INSERT 49
INSERT 56
SEARCH 49
SEARCH 15

Sample Output
FOUND
NOT FOUND

Explanation
Collisions resolved using i² jumps.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1

struct HashTable {
    int size;
    int* table;
};

struct HashTable* createTable(int m) {
    struct HashTable* ht = malloc(sizeof(struct HashTable));
    ht->size = m;
    ht->table = malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) ht->table[i] = EMPTY;
    return ht;
}

void insert(struct HashTable* ht, int key) {
    int h_k = key % ht->size;
    for (int i = 0; i < ht->size; i++) {
        int index = (h_k + i * i) % ht->size;
        if (ht->table[index] == EMPTY) {
            ht->table[index] = key;
            return;
        }
    }
}

int search(struct HashTable* ht, int key) {
    int h_k = key % ht->size;
    for (int i = 0; i < ht->size; i++) {
        int index = (h_k + i * i) % ht->size;
        if (ht->table[index] == key) return 1;
        if (ht->table[index] == EMPTY) return 0;
    }
    return 0;
}

int main() {
    int m, q;
    if (scanf("%d %d", &m, &q) != 2) return 0;

    struct HashTable* ht = createTable(m);
    char command[10];
    int key;

    for (int i = 0; i < q; i++) {
        scanf("%s %d", command, &key);
        if (strcmp(command, "INSERT") == 0) {
            insert(ht, key);
        } else if (strcmp(command, "SEARCH") == 0) {
            if (search(ht, key)) printf("FOUND\n");
            else printf("NOT FOUND\n");
        }
    }

    free(ht->table);
    free(ht);
    return 0;
}