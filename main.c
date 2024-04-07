#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *left, *right;  // 노드라는 구조체는 값을 가지고, 자식의 주소값을 left, right에 저장한다.
};

struct node *create_node(int new_value) {
    struct node *temp_node = malloc(sizeof(struct node));
    temp_node -> value = new_value;
    temp_node -> left = NULL;
    temp_node -> right = NULL;
    return temp_node;
}

struct node *insert_node(struct node *node , int value) {
    if (node == NULL) {
        return create_node(value);
    }

    if (node -> value > value) {
        node -> left = insert_node(node -> left, value);
    } else {
        node -> right = insert_node(node -> right, value);
    }

    return node;
}

void show_tree(struct node *node) {
    if(node == NULL) {
        return;
    }

    show_tree(node -> left);
    printf("%d\n", node -> value);
    show_tree(node -> right);
}

int main() {
    struct node *root = NULL;
    root = insert_node(NULL, 30);
    insert_node(root, 40);
    insert_node(root, 50);
    insert_node(root, 10);
    insert_node(root, 60);

    show_tree(root);

    return 0;
}