#include <stdio.h>
#include <stdlib.h>

// 이진 트리의 노드를 정의합니다.
struct node {
    int value;          // 노드가 저장하는 값
    struct node *left;  // 왼쪽 자식 노드를 가리키는 포인터
    struct node *right; // 오른쪽 자식 노드를 가리키는 포인터
};

// 새로운 노드를 생성하여 반환하는 함수입니다.
struct node *create_node(int new_value) {
    // 동적 메모리 할당을 통해 새로운 노드를 생성합니다.
    struct node *temp_node = malloc(sizeof(struct node));
    temp_node -> value = new_value;  // 노드의 값 설정
    temp_node -> left = NULL;        // 왼쪽 자식 노드 초기화
    temp_node -> right = NULL;       // 오른쪽 자식 노드 초기화
    return temp_node;                // 새로 생성된 노드의 포인터 반환
}

// 이진 트리에 노드를 삽입하는 함수입니다.
struct node *insert_node(struct node *node, int value) {
    // 노드가 비어있는 경우 새로운 노드를 생성하여 반환합니다.
    if (node == NULL) {
        return create_node(value);
    }

    // 삽입할 값이 현재 노드의 값보다 작은 경우 왼쪽 서브트리로 이동하여 삽입합니다.
    if (node -> value > value) {
        node -> left = insert_node(node -> left, value);
    }
        // 삽입할 값이 현재 노드의 값보다 크거나 같은 경우 오른쪽 서브트리로 이동하여 삽입합니다.
    else {
        node -> right = insert_node(node -> right, value);
    }

    return node; // 삽입된 노드의 포인터를 반환합니다.
}

// 트리에서 가장 작은 값을 가진 노드를 찾는 함수입니다.
struct node* find_min_node(struct node* node) {
    struct node* current = node; // 현재 노드를 가리키는 포인터를 설정합니다.
    // 왼쪽 자식 노드가 있는 한 계속해서 왼쪽 자식 노드로 이동합니다.
    while (current && current->left != NULL)
        current = current->left;
    return current; // 가장 작은 값을 가진 노드의 포인터를 반환합니다.
}

// 트리에서 값을 삭제하는 함수입니다.
struct node* delete_node(struct node* node, int value) {
    if (node == NULL) {
        return NULL;
    }

    // 삭제할 값이 현재 노드의 값보다 작은 경우 왼쪽 서브트리에서 삭제를 시도합니다.
    if (value < node -> value) {
        node -> left = delete_node(node -> left, value);
    }
        // 삭제할 값이 현재 노드의 값보다 큰 경우 오른쪽 서브트리에서 삭제를 시도합니다.
    else if (value > node -> value) {
        node -> right = delete_node(node -> right, value);
    }
        // 삭제할 값이 현재 노드의 값과 같은 경우
    else {
        // 자식 노드가 하나 또는 없는 경우
        if (node -> left == NULL) {
            struct node* temp = node -> right; // 오른쪽 자식 노드를 임시 변수에 저장합니다.
            free(node); // 현재 노드를 해제합니다.
            return temp; // 삭제된 노드의 자식 노드를 반환합니다.
        }
        else if (node -> right == NULL) {
            struct node* temp = node -> left; // 왼쪽 자식 노드를 임시 변수에 저장합니다.
            free(node); // 현재 노드를 해제합니다.
            return temp; // 삭제된 노드의 자식 노드를 반환합니다.
        }

        // 자식 노드가 둘인 경우
        struct node* temp = find_min_node(node -> right); // 오른쪽 서브트리에서 가장 작은 값을 가진 노드를 찾습니다.
        node -> value = temp -> value; // 삭제할 노드의 값을 찾은 노드의 값으로 대체합니다.
        node -> right = delete_node(node -> right, temp -> value); // 오른쪽 서브트리에서 찾은 노드를 삭제합니다.
    }
    return node; // 수정된 트리의 루트 노드를 반환합니다.
}

// 특정 값을 가진 노드를 찾는 함수입니다.
struct node *find_node(struct node *node, int value) {
    if(node == NULL) {
        return NULL; // 노드가 비어있는 경우 NULL을 반환합니다.
    }

    if(node -> value == value) {
        return node; // 값을 찾았을 때 해당 노드의 포인터를 반환합니다.
    }

    // 값을 찾을 때까지 왼쪽 또는 오른쪽 자식 노드로 이동하여 탐색합니다.
    if (node->value > value) {
        return find_node(node->left, value); // 왼쪽 서브트리에서 탐색합니다.
    } else {
        return find_node(node->right, value); // 오른쪽 서브트리에서 탐색합니다.
    }
}

// 트리의 모든 값을 중위 순회하여 출력하는 함수입니다.
void show_tree(struct node *node) {
    if(node == NULL) {
        return; // 노드가 비어있는 경우 종료합니다.
    }

    show_tree(node -> left); // 왼쪽 서브트리를 중위 순회합니다.
    printf("%d\n", node -> value); // 현재 노드의 값을 출력합니다.
    show_tree(node -> right); // 오른쪽 서브트리를 중위 순회합니다.
}

int main() {
    struct node *root = NULL; // 트리의 루트 노드를 초기화합니다.
    root = insert_node(NULL, 30); // 루트 노드에 값을 삽입합니다.
    insert_node(root, 40); // 트리에 값을 삽입합니다.
    insert_node(root, 50); // 트리에 값을 삽입합니다.
    insert_node(root, 10); // 트리에 값을 삽입합니다.
    insert_node(root, 60); // 트리에 값을 삽입합니다.

    printf("삭제 전 트리:\n");
    show_tree(root); // 삭제 전 트리를 출력합니다.

    // 삭제할 값을 지정합니다.
    int delete_value = 40;

    // 삭제 연산을 수행합니다.
    root = delete_node(root, delete_value);
    printf("\n값 %d 삭제 후 트리:\n", delete_value);
    show_tree(root); // 삭제 후 트리를 출력합니다.

    return 0;
}
