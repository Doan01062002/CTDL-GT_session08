#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

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

void findLevel2Nodes(Node* root) {
    if (root == NULL) {
        printf("Cay rong.\n");
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        printf("Khong co dinh lop 2.\n");
        return;
    }

    printf("\nCac dinh lop 2: ");
    if (root->left) {
        if (root->left->left) printf("%d ", root->left->left->data);
        if (root->left->right) printf("%d ", root->left->right->data);
    }
    if (root->right) {
        if (root->right->left) printf("%d ", root->right->left->data);
        if (root->right->right) printf("%d ", root->right->right->data);
    }
    printf("\n");
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

    findLevel2Nodes(root);

    printf("\nNhap gia tri can tim kiem: ");
    scanf("%d", &searchValue);
    if (search(root, searchValue)) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    return 0;
}

