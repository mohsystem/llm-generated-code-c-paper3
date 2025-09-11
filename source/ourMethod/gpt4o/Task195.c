#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} MedianFinder;

void initMedianFinder(MedianFinder* mf) {
    mf->size = 0;
    mf->capacity = 10;
    mf->data = (int*)malloc(mf->capacity * sizeof(int));
}

void addNum(MedianFinder* mf, int num) {
    if (mf->size == mf->capacity) {
        mf->capacity *= 2;
        mf->data = (int*)realloc(mf->data, mf->capacity * sizeof(int));
    }
    mf->data[mf->size++] = num;
    for (int i = 0; i < mf->size - 1; ++i) {
        for (int j = 0; j < mf->size - i - 1; ++j) {
            if (mf->data[j] > mf->data[j + 1]) {
                int temp = mf->data[j];
                mf->data[j] = mf->data[j + 1];
                mf->data[j + 1] = temp;
            }
        }
    }
}

double findMedian(MedianFinder* mf) {
    if (mf->size % 2 == 1) {
        return mf->data[mf->size / 2];
    } else {
        return (mf->data[mf->size / 2 - 1] + mf->data[mf->size / 2]) / 2.0;
    }
}

int main() {
    MedianFinder mf;
    initMedianFinder(&mf);
    addNum(&mf, 1);
    addNum(&mf, 2);
    printf("%f\n", findMedian(&mf));  // 1.5
    addNum(&mf, 3);
    printf("%f\n", findMedian(&mf));  // 2.0
    addNum(&mf, 4);
    addNum(&mf, 5);
    printf("%f\n", findMedian(&mf));  // 3.0
    free(mf.data);
    return 0;
}