#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0 || lists == NULL) {
        return NULL;
    }
    
    struct ListNode * dummy = malloc(sizeof(struct ListNode));
    dummy->val=0;
    dummy->next = NULL;
    struct ListNode * current = dummy;


    while(1){
        int minVal = 10001;
        int minIndex = -1;
        int allNull = 1;

        for(int i = 0; i < listsSize; ++i) {
            if(lists[i] != NULL){
                allNull=0;
                if(lists[i]->val < minVal){
                    minVal=lists[i]->val;
                    minIndex = i;
                }
            }
        }
        if(allNull) break;


        current->next = lists[minIndex];
        current = current->next;
        lists[minIndex] = lists[minIndex]->next;
    }
    struct ListNode* ans = dummy->next;
    free(dummy);
    return ans;


}

struct ListNode* createList(int arr[], int n) {
    if (n == 0) return NULL;
    struct ListNode* head = malloc(sizeof(struct ListNode));
    head->val = arr[0];
    head->next = NULL;
    struct ListNode* current = head;
    for (int i = 1; i < n; i++) {
        struct ListNode* newNode = malloc(sizeof(struct ListNode));
        newNode->val = arr[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
    return head;
}


void printList(struct ListNode* head) {
    while (head) {
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
        struct ListNode* merged = mergeKLists(lists, 3);
        printList(merged); // 1 1 2 3 4 4 5 6 


        struct ListNode* lists2_empty[0];
        struct ListNode* merged2 = mergeKLists(lists2_empty, 0);
        printList(merged2);


        struct ListNode* list3_null = NULL;
        struct ListNode* lists3_null_array[] = {list3_null};

        struct ListNode* merged3 = mergeKLists(lists3_null_array,1);
        printList(merged3); //


        int arr4[] = {};
        struct ListNode* list4 = createList(arr4, sizeof(arr4) / sizeof(arr4[0]));
        struct ListNode* lists4_empty[] = {list4};
        struct ListNode* merged4 = mergeKLists(lists4_empty, 1);
        printList(merged4); // 



        int arr5_1[] = {-2, -1, -1, -1};
        int arr5_2[] = {-2};
        int arr5_3[] = {-1, 0, 1};
        struct ListNode* list5_1 = createList(arr5_1, sizeof(arr5_1) / sizeof(arr5_1[0]));
        struct ListNode* list5_2 = createList(arr5_2, sizeof(arr5_2) / sizeof(arr5_2[0]));
        struct ListNode* list5_3 = createList(arr5_3, sizeof(arr5_3) / sizeof(arr5_3[0]));
        struct ListNode* lists5[] = {list5_1, list5_2, list5_3};
        struct ListNode* merged5 = mergeKLists(lists5, 3);
        printList(merged5); // -2 -2 -1 -1 -1 -1 0 1

    return 0;
}