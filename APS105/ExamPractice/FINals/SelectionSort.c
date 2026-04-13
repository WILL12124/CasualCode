#include <stdio.h>
#include <string.h>

void printArr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    return;
}

void sortArr(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int cur = i;
        int min = i;
        for (; cur < len; cur++)
        {
            if (arr[min] > arr[cur])
            {
                min = cur;
            }
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
    printArr(arr, len);
    return;
}

int main(int argc, char const *argv[])
{
    int arr[] = {2, 3, 9, 4, 6, 7, 1, 3, 7, 6, 4, 2};
    int len = sizeof(arr) / sizeof(arr[0]); // 传过去就只剩pointer了，不能用sizeof！
    sortArr(arr, len);
    return 0;
}
