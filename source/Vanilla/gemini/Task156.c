#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void preorder(struct Node *root, int *arr, int *index) {
    if (root != NULL) {
        arr[(*index)++] = root->data;
        preorder(root->left, arr, index);
        preorder(root->right, arr, index);
    }
}


void inorder(struct Node *root, int *arr, int *index) {
    if (root != NULL) {
        inorder(root->left, arr, index);
        arr[(*index)++] = root->data;
        inorder(root->right, arr, index);
    }
}


void postorder(struct Node *root, int *arr, int *index) {
    if (root != NULL) {
        postorder(root->left, arr, index);
        postorder(root->right, arr, index);
        arr[(*index)++] = root->data;
    }
}



int main() {

     // Test case 1
    struct Node *root1 = createNode(1);
    root1->right = createNode(2);
    root1->right->left = createNode(3);
    int preorderArr1[100]; int index1=0;
    preorder(root1, preorderArr1, &index1);
    for(int i=0; i<index1; ++i) printf("%d ", preorderArr1[i]); printf("\n"); // Output: 1 2 3


    // Test case 2
    struct Node *root2 = NULL;
    int inorderArr2[100]; int index2 = 0;
    inorder(root2, inorderArr2, &index2);
    for (int i = 0; i < index2; ++i) printf("%d ", inorderArr2[i]);
    printf("\n");  // Output: (empty)

    // Test case 3
    struct Node *root3 = createNode(1);
    int postorderArr3[100]; int index3 = 0;
    postorder(root3, postorderArr3, &index3);
    for(int i = 0; i < index3; ++i) printf("%d ", postorderArr3[i]); printf("\n"); // Output: 1


    // Test case 4
    struct Node *root4 = createNode(1);
    root4->left = createNode(2);
    root4->right = createNode(3);
    int preorderArr4[100]; int index4 = 0;
    preorder(root4, preorderArr4, &index4);
    for(int i=0; i < index4; i++) printf("%d ", preorderArr4[i]); printf("\n"); // Output : 1 2 3



    // Test case 5
    struct Node *root5 = createNode(1);
    root5->left = createNode(2);
    root5->right = createNode(3);
    root5->left->left = createNode(4);
    root5->left->right = createNode(5);
    int inorderArr5[100]; int index5=0;
    inorder(root5, inorderArr5, &index5);
    for(int i=0; i<index5; ++i) printf("%d ", inorderArr5[i]); printf("\n"); // Output : 4 2 5 1 3



    return 0;

}