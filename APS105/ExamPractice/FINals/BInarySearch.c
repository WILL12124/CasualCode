#include <stdio.h>
#include <string.h>
#include <math.h>

// wrong ver
int *BinarySearch(int arr[], int len, int num)
{
    int tempMid = (len / 2); // midpoint error, if on larger section
    for (; 1;)               ///
    {
        if (arr[tempMid] == num)
        {
            return arr + tempMid;
        }
        if (arr[tempMid] > num)
        {
            tempMid = round(((float)tempMid) / 2); // could lead to OVERFLOW!!!
        }
        else if (arr[tempMid] < num)
        {
            tempMid = tempMid + round(((float)tempMid) / 2);
        }
    }
}

int *BinarySearch(int *arr, int len, int num)
{
    int left = 0;
    int right = len - 1;

    while (left <=  right) // 包含等号是因为最后三个元素会第二次循环才搜索middle的（int truncate）
    {
        int mid = left + (right - left) / 2; // 放在loop里面
        if (arr[mid] == num)
        {
            return arr + mid;
        }
        if (arr[mid] < num)
        {
            left = mid + 1;
        }
        else if (arr[mid] > num)
        {
            right = mid - 1; // 中间已经不是了
        }
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    int arr[] = {1, 5, 7, 8, 11, 17, 19, 32};
    int len = sizeof(arr) / sizeof(arr[0]);
    int *ptr = BinarySearch(arr, len, 8);
    printf("%d", *ptr);
    return 0;
}
