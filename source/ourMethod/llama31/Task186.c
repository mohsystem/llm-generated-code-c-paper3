#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

void swap(ListNode** a, ListNode** b) {
    ListNode* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(ListNode** arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left]->val < arr[smallest]->val) {
        smallest = left;
    }

    if (right < n && arr[right]->val < arr[smallest]->val) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void buildHeap(ListNode** arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

ListNode* mergeKLists(ListNode** lists, int k) {
    ListNode dummy = {0, NULL};
    ListNode* current = &dummy;
    ListNode** minHeap = (ListNode**)malloc(k * sizeof(ListNode*));

    for (int i = 0; i < k; i++) {
        minHeap[i] = lists[i];
    }

    buildHeap(minHeap, k);

    while (k > 0) {
        ListNode* node = minHeap[0];
        current->next = node;
        current = current->next;

        if (node->next != NULL) {
            minHeap[0] = node->next;
            heapify(minHeap, k, 0);
        } else {
            for (int i = 0; i < k - 1; i++) {
                minHeap[i] = minHeap[i + 1];
            }
            k--;
            buildHeap(minHeap, k);
        }
    }

    free(minHeap);
    return dummy.next;
}

int main() {
    // Test cases
    ListNode* lists1[] = {
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode)),
        (ListNode*)malloc(sizeof(ListNode))
    };
    lists1[0]->val = 1; lists1[0]->next = lists1[1];
    lists1[1]->val = 4; lists1[1]->next = lists1[2];
    lists1[2]->val = 5; lists1[2]->next = NULL;
    lists1[3]->val = 1; lists1[3]->next = lists1[4];
    lists1[4]->val = 3; lists1[4]->next = lists1[5];
    lists1[5]->val = 4; lists1[5]->next = NULL;
    lists1[6]->val = 2; lists1[6]->next = lists1[7];
    lists1[7]->val = 6; lists1[7]->next = NULL;

    ListNode** lists = {lists1[0], lists1[3], lists1[6]};
    ListNode* result = mergeKLists(lists, 3);
    while (result) {
        printf("%d ", result->val);
        result = result->next;
    }
    return 0;
}