#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
    int data;
    struct Node* next;
};

struct HashTable {
    struct Node* table[SIZE];
};

int hashFunction(int key) {
    return key % SIZE;
}

void insert(struct HashTable* ht, int key) {
    int index = hashFunction(key);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = key;
    newNode->next = NULL;

    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        struct Node* current = ht->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void display(struct HashTable* ht) {
    printf("Hash Table:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d:", i);
        struct Node* current = ht->table[i];
        while (current != NULL) {
            printf(" %d", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    struct HashTable ht;
    for (int i = 0; i < SIZE; i++) {
        ht.table[i] = NULL;
    }

    int n;
    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        int key;
        scanf("%d", &key);
        insert(&ht, key);
    }

    display(&ht);

    return 0;
}


