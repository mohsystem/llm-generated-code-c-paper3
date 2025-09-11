#include <stdbool.h>

typedef struct {
    int (*get)(int index);
    int (*length)();
} MountainArray;

int findPeak(MountainArray *mountainArr, int l, int r) {
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (mountainArr->get(mid) < mountainArr->get(mid + 1))
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

int binarySearch(MountainArray *mountainArr, int l, int r, int target, bool isIncreasing) {
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (mountainArr->get(mid) == target)
            return mid;
        if (isIncreasing) {
            if (mountainArr->get(mid) < target)
                l = mid + 1;
            else
                r = mid - 1;
        } else {
            if (mountainArr->get(mid) > target)
                l = mid + 1;
            else
                r = mid - 1;
        }
    }
    return -1;
}

int findInMountainArray(int target, MountainArray *mountainArr) {
    int n = mountainArr->length();
    int peak = findPeak(mountainArr, 0, n - 1);
    int left = binarySearch(mountainArr, 0, peak, target, true);
    if (left != -1)
        return left;
    return binarySearch(mountainArr, peak + 1, n - 1, target, false);
}