#include <stdio.h>
#include <time.h>

int binarySearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int x = 10;
    clock_t start = clock();
    int result = binarySearch(arr, 0, 5, x);
    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC * 1e9;
    FILE *fp = fopen("execution_time.txt", "w");
    fprintf(fp, "Execution time: %f nanoseconds", duration);
    fclose(fp);
    return 0;
}