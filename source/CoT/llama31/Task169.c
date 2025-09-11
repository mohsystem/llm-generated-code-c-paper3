#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    int count;
} Node;

typedef struct MergeSortTree {
    Node* root;
} MergeSortTree;

MergeSortTree* createMergeSortTree(int* nums, int n) {
    MergeSortTree* mst = (MergeSortTree*)malloc(sizeof(MergeSortTree));
    mst->root = NULL;
    for (int i = 0; i < n; ++i) {
        mst->root = insert(mst->root, nums[i]);
    }
    return mst;
}

Node* insert(Node* node, int val) {
    if (node == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->val = val;
        newNode->left = newNode->right = NULL;
        newNode->count = 1;
        return newNode;
    }
    if (val <= node->val) {
        node->left = insert(node->left, val);
        node->count++;
    } else {
        node->right = insert(node->right, val);
    }
    return node;
}

int query(Node* node, int val) {
    if (node == NULL) return 0;
    if (val <= node->val) {
        return query(node->left, val);
    } else {
        return node->count + query(node->right, val);
    }
}

Node* remove(Node* node, int val) {
    if (node == NULL) return NULL;
    if (val < node->val) {
        node->left = remove(node->left, val);
        node->count--;
    } else if (val > node->val) {
        node->right = remove(node->right, val);
    } else {
        if (node->left == NULL) return node->right;
        if (node->right == NULL) return node->left;
        Node* min_node = find_min(node->right);
        node->val = min_node->val;
        node->right = remove(node->right, min_node->val);
    }
    return node;
}

Node* find_min(Node* node) {
    while (node->left != NULL) node = node->left;
    return node;
}

void countSmaller(int* nums, int n, int* counts) {
    MergeSortTree* mst = createMergeSortTree(nums, n);
    for (int i = n - 1; i >= 0; --i) {
        counts[i] = query(mst->root, nums[i]);
        mst->root = remove(mst->root, nums[i]);
    }
    free(mst);
}

int main() {
    int test_cases[][4] = {
        {5, 2, 6, 1},
        {-1},
        {-1, -1},
        {10, 5, 11, 10, 5},
        {0, 0, 0, 0}
    };
    int test_case_lens[] = {4, 1, 2, 5, 4};

    for (int i = 0; i < 5; ++i) {
        int* counts = (int*)malloc(test_case_lens[i] * sizeof(int));
        countSmaller(test_cases[i], test_case_lens[i], counts);
        for (int j = 0; j < test_case_lens[i]; ++j) {
            printf("%d ", counts[j]);
        }
        printf("\n");
        free(counts);
    }

    return 0;
}