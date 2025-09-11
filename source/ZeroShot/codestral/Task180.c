// This C solution uses a linked list instead of ArrayList for children and doesn't include the test cases
typedef struct Node {
    int data;
    struct Node* parent;
    struct Node* child;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->next = NULL;
    return newNode;
}

void addChild(Node* parent, Node* child) {
    child->parent = parent;
    child->next = parent->child;
    parent->child = child;
}

void reparent(Node* node) {
    Node* parent = node->parent;
    node->parent = NULL;
    if (parent != NULL) {
        if (parent->child == node) {
            parent->child = node->next;
        } else {
            Node* temp = parent->child;
            while (temp->next != node) {
                temp = temp->next;
            }
            temp->next = node->next;
        }
        addChild(node, parent);
    }
    Node* temp = node->child;
    while (temp != NULL) {
        reparent(temp);
        temp = temp->next;
    }
}