#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    // Handle empty input
    if (listsSize == 0 || lists == NULL) {
        return NULL;
    }

    // Min-heap implementation using a simple array (could be optimized with a proper heap data structure)
    struct ListNode* heap[listsSize];  //  Fix: Use correct size for the heap array.
    int heapSize = 0;

    // Initialize heap with the first node of each list
    for (int i = 0; i < listsSize; i++) {
        if (lists[i] != NULL) {
            heap[heapSize++] = lists[i];
        }
    }

    // Build min-heap
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        // Heapify down
        int curr = i;
        while (curr < heapSize) {
            int left = 2 * curr + 1;
            int right = 2 * curr + 2;
            int smallest = curr;

            if (left < heapSize && heap[left]->val < heap[smallest]->val) {
                smallest = left;
            }
            if (right < heapSize && heap[right]->val < heap[smallest]->val) {
                smallest = right;
            }

            if (smallest != curr) {
                struct ListNode* temp = heap[curr];
                heap[curr] = heap[smallest];
                heap[smallest] = temp;
                curr = smallest;
            } else {
                break;
            }
        }
    }

    struct ListNode dummy;
    struct ListNode* tail = &dummy;

    while (heapSize > 0) {
        // Extract min from heap
        struct ListNode* minNode = heap[0];
        heap[0] = heap[heapSize - 1];
        heapSize--;

        // Heapify down
        int curr = 0;
        while (curr < heapSize) {
            int left = 2 * curr + 1;
            int right = 2 * curr + 2;
            int smallest = curr;

            if (left < heapSize && heap[left]->val < heap[smallest]->val) {
                smallest = left;
            }
            if (right < heapSize && heap[right]->val < heap[smallest]->val) {
                smallest = right;
            }
            if (smallest != curr) {
                struct ListNode* temp = heap[curr];
                heap[curr] = heap[smallest];
                heap[smallest] = temp;
                curr = smallest;
            } else {
                break;
            }
        }


        tail->next = minNode;
        tail = minNode;

        if (minNode->next != NULL) {
            heap[heapSize++] = minNode->next;
              // Heapify up
            int curr = heapSize -1;
            while(curr > 0) {
                int parent = (curr - 1)/2;
                if(heap[curr]->val < heap[parent]->val) {
                    struct ListNode* temp = heap[curr];
                    heap[curr] = heap[parent];
                    heap[parent] = temp;
                    curr = parent;
                } else {
                    break;
                }
            }
        }
        tail->next = NULL; // Add null terminator at the end.

    }

    return dummy.next;
}


struct ListNode* createList(int arr[], int n) {
    if (n == 0) return NULL;
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = arr[0];
    head->next = NULL;
    struct ListNode* current = head;
    for (int i = 1; i < n; i++) {
        current->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        current = current->next;
        current->val = arr[i];
        current->next = NULL;
    }
    return head;
}

void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main() {
    int arr1[] = {1, 4, 5};
    int arr2[] = {1, 3, 4};
    int arr3[] = {2, 6};
    struct ListNode* list1 = createList(arr1, sizeof(arr1) / sizeof(arr1[0]));
    struct ListNode* list2 = createList(arr2, sizeof(arr2) / sizeof(arr2[0]));
    struct ListNode* list3 = createList(arr3, sizeof(arr3) / sizeof(arr3[0]));
    struct ListNode* lists[] = {list1, list2, list3};
    struct ListNode* merged = mergeKLists(lists, sizeof(lists) / sizeof(lists[0]));
    printList(merged);

     int arr4[] = {};
    struct ListNode* list4 = createList(arr4, sizeof(arr4) / sizeof(arr4[0]));
    struct ListNode* lists2[] = {list4};
    merged = mergeKLists(lists2, sizeof(lists2) / sizeof(lists2[0]));
    printList(merged);



    int arr5[] = {1};
    int arr6[] = {2};

    struct ListNode* list5 = createList(arr5, sizeof(arr5) / sizeof(arr5[0]));
    struct ListNode* list6 = createList(arr6, sizeof(arr6) / sizeof(arr6[0]));

    struct ListNode* lists3[] = {list5, list6};
    merged = mergeKLists(lists3, sizeof(lists3) / sizeof(lists3[0]));
    printList(merged);


    int arr7[] = {-2,-1,-1};
    int arr8[] = {0};

    struct ListNode* list7 = createList(arr7, sizeof(arr7) / sizeof(arr7[0]));
    struct ListNode* list8 = createList(arr8, sizeof(arr8) / sizeof(arr8[0]));

    struct ListNode* lists4[] = {list7, list8};
    merged = mergeKLists(lists4, sizeof(lists4) / sizeof(lists4[0]));
    printList(merged);
    return 0;
}