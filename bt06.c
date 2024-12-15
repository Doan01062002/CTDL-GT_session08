#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Queue {
    Node* node;
    struct Queue* next;
} Queue;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

void preOrderTraversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void inOrderTraversal(Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

void postOrderTraversal(Node* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}

void enqueue(Queue** front, Queue** rear, Node* node) {
    Queue* newElement = (Queue*)malloc(sizeof(Queue));
    newElement->node = node;
    newElement->next = NULL;
    if (*rear == NULL) {
        *front = *rear = newElement;
    } else {
        (*rear)->next = newElement;
        *rear = newElement;
    }
}

Node* dequeue(Queue** front, Queue** rear) {
    if (*front == NULL) {
        return NULL;
    }
    Queue* temp = *front;
    Node* node = temp->node;
    *front = (*front)->next;
    if (*front == NULL) {
        *rear = NULL;
    }
    free(temp);
    return node;
}

bool isCompleteBinaryTree(Node* root) {
    if (root == NULL) {
        return true;
    }

    Queue* front = NULL;
    Queue* rear = NULL;
    enqueue(&front, &rear, root);

    bool foundNullChild = false;

    while (front != NULL) {
        Node* current = dequeue(&front, &rear);

        if (current->left != NULL) {
            if (foundNullChild) {
                return false;
            }
            enqueue(&front, &rear, current->left);
        } else {
            foundNullChild = true;
        }

        if (current->right != NULL) {
            if (foundNullChild) {
                return false;
            }
            enqueue(&front, &rear, current->right);
        } else {
            foundNullChild = true;
        }
    }

    return true;
}

int search(Node* root, int key) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == key) {
        return 1;
    } else if (key < root->data) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

int calculateHeight(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main() {
    Node* root = NULL;
    int n, value, searchValue;

    printf("Nhap so luong nut trong cay: ");
    scanf("%d", &n);

    printf("Nhap gia tri cac nut: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\nDuyet Tien Thu Tu: \n");
    preOrderTraversal(root);

    printf("\n\nDuyet Trung Thu Tu: \n");
    inOrderTraversal(root);

    printf("\n\nDuyet Hau Thu Tu: \n");
    postOrderTraversal(root);

    if (isCompleteBinaryTree(root)) {
        printf("\nCay la cay nhi phan hoan chinh.\n");
    } else {
        printf("\nCay khong phai la cay nhi phan hoan chinh.\n");
    }

    printf("\nNhap gia tri can tim kiem: ");
    scanf("%d", &searchValue);
    if (search(root, searchValue)) {
        printf("Gia tri %d ton tai trong cay.\n", searchValue);
    } else {
        printf("Gia tri %d khong ton tai trong cay.\n", searchValue);
    }

    int height = calculateHeight(root);
    printf("\nChieu cao cua cay: %d\n", height);

    return 0;
}

