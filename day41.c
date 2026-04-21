/* Problem Statement:
Implement a Queue using a linked list supporting enqueue and dequeue operations.

Input Format:
- First line contains integer N
- Next N lines contain queue operations

Output Format:
- Print dequeued elements
- Print -1 if dequeue is attempted on an empty queue
*/

#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the Max Heap property
void heapify(int arr[], int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left child
    int right = 2 * i + 2; // right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // 1. Build Max Heap (rearrange array)
    // Start from the last non-leaf node and move up to the root
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 2. One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root (largest) to the end
        swap(&arr[0], &arr[i]);

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : " ");
    }
    printf("\n");
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    heapSort(arr, n);
    printArray(arr, n);

    return 0;
}