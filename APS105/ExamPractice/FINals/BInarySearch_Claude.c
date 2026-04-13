#include <stdio.h>

int *BinarySearch(int arr[], int len, int num)
{
    int left = 0;
    int right = len - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // avoids overflow vs (left+right)/2

        if (arr[mid] == num)
            return arr + mid;
        else if (arr[mid] > num)
            right = mid - 1; // search left half
        else
            left = mid + 1; // search right half
    }

    return NULL; // not found
}

int main()
{
    int arr[] = {1, 5, 7, 8, 11, 17, 19, 32};
    int len = sizeof(arr) / sizeof(arr[0]);

    int *ptr = BinarySearch(arr, len, 8);

    if (ptr != NULL)
        printf("Found: %d\n", *ptr);
    else
        printf("Not found\n");

    return 0;
}