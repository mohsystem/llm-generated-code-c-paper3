#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode** children;
    int child_count;
} TreeNode;

TreeNode* create_node(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

void add_child(TreeNode* parent, TreeNode* child) {
    parent->children = (TreeNode**)realloc(parent->children, sizeof(TreeNode*) * (parent->child_count + 1));
    parent->children[parent->child_count++] = child;
}

void build_node_map(TreeNode* node, TreeNode* parent, TreeNode** node_map, int size) {
    node_map[node->value] = node;
    if (parent != NULL) {
        for (int i = 0; i < parent->child_count; ++i) {
            if (parent->children[i] == node) {
                for (int j = i; j < parent->child_count - 1; ++j) {
                    parent->children[j] = parent->children[j + 1];
                }
                --parent->child_count;
                break;
            }
        }
    }
    for (int i = 0; i < node->child_count; ++i) {
        build_node_map(node->children[i], node, node_map, size);
    }
}

void rebuild_tree(TreeNode* node, TreeNode* parent) {
    if (parent != NULL) {
        add_child(node, parent);
    }
    for (int i = 0; i < node->child_count; ++i) {
        rebuild_tree(node->children[i], node);
    }
}

TreeNode* reparent(TreeNode* root, int new_root_value, int size) {
    TreeNode** node_map = (TreeNode**)calloc(size, sizeof(TreeNode*));
    build_node_map(root, NULL, node_map, size);
    TreeNode* new_root = node_map[new_root_value];
    rebuild_tree(new_root, NULL);
    free(node_map);
    return new_root;
}

void print_tree(TreeNode* node, const char* indent) {
    printf("%s%d\n", indent, node->value);
    for (int i = 0; i < node->child_count; ++i) {
        char new_indent[100];
        snprintf(new_indent, sizeof(new_indent), "%s  ", indent);
        print_tree(node->children[i], new_indent);
    }
}

int main() {
    TreeNode* root = create_node(0);
    TreeNode* node1 = create_node(1);
    TreeNode* node2 = create_node(2);
    TreeNode* node3 = create_node(3);
    TreeNode* node4 = create_node(4);
    TreeNode* node5 = create_node(5);
    TreeNode* node6 = create_node(6);
    TreeNode* node7 = create_node(7);
    TreeNode* node8 = create_node(8);
    TreeNode* node9 = create_node(9);

    add_child(root, node1);
    add_child(root, node2);
    add_child(root, node3);
    add_child(node1, node4);
    add_child(node1, node5);
    add_child(node2, node6);
    add_child(node2, node7);
    add_child(node3, node8);
    add_child(node3, node9);

    TreeNode* new_root = reparent(root, 6, 10);
    print_tree(new_root, "");

    // Free memory
    free(root);
    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);
    free(node6);
    free(node7);
    free(node8);
    free(node9);

    return 0;
}