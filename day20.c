/* Problem: Given an array of integers, count the number of subarrays whose sum is equal to zero.

Input:
- First line: integer n
- Second line: n integers

Output:
- Print the count of subarrays having sum zero

Example:
Input:
6
1 -1 2 -2 3 -3

Output:
6

Explanation: A subarray is a continuous part of the array. For the input array 1 -1 2 -2 3 -3, the following subarrays have sum zero: [1, -1], [2, -2], [3, -3], [1, -1, 2, -2], [2, -2, 3, -3], and [1, -1, 2, -2, 3, -3]. Since there are 6 such subarrays, the output is 6.
*/

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];

    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int count = 0;
    int prefix_sum = 0;

    // Simple frequency array (adjust size if needed)
    int freq[20001] = {0};  
    int offset = 10000; // to handle negative sums

    // Initialize: prefix sum = 0 occurs once
    freq[offset] = 1;

    for(int i = 0; i < n; i++) {
        prefix_sum += arr[i];

        // If same prefix sum seen before
        count += freq[prefix_sum + offset];

        // Increase frequency
        freq[prefix_sum + offset]++;
    }

    printf("%d", count);

    return 0;
}