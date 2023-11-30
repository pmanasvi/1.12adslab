
#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}
int getBalanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}
void updateHeight(struct Node* node) {
    if (node == NULL)
        return;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);


    return y;
}
struct AVLTree {
    struct Node* root;
};
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root; 
    updateHeight(root);
    int balance = getBalanceFactor(root);
    if (balance > 1) {    
        if (data < root->left->data)
            return rightRotate(root);
        else if (data > root->left->data) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balance < -1) {
        if (data > root->right->data)
            return leftRotate(root);
        
        else if (data < root->right->data) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}
void inOrder(struct Node* root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}
void preOrder(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}
void postOrder(struct Node* root) {
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
}
int main() {
    struct AVLTree avlTree;
    avlTree.root = NULL;
    int n, data;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements one by one:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        avlTree.root = insert(avlTree.root, data);  
    }
    printf("Final AVL Tree (Inorder traversal): ");
    inOrder(avlTree.root);
    printf("\n");
     printf("Final AVL Tree (postorder traversal): ");
    postOrder(avlTree.root);
    printf("\n");
     printf("Final AVL Tree (preorder traversal): ");
    preOrder(avlTree.root);
    printf("\n");
    return 0;
}
