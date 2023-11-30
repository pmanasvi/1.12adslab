#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* insert(struct TreeNode* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

int height(struct TreeNode* root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return countNodes(root->left) + countNodes(root->right) + 1;
}

int countLeafNodes(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int findMin(struct TreeNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return -1; 
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

int findMax(struct TreeNode* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return -1; 
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}

void printLeafNodes(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}
void printLevelWise(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
  while (front < rear) {
        struct TreeNode* currNode = queue[front++];
        printf("%d ", currNode->data);
       if (currNode->left != NULL) {
            queue[rear++] = currNode->left;
        }
        if (currNode->right != NULL) {
            queue[rear++] = currNode->right;
        }
    }
}
void deleteTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}
int main() {
    struct TreeNode* root = NULL;

    int n;
    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        int element;
        scanf("%d", &element);
        root = insert(root, element);
    }
    int h = height(root);
    printf("Height of the BST: %d\n", h);
    int numNodes = countNodes(root);
    printf("Number of nodes in the BST: %d\n", numNodes);
    int numLeafNodes = countLeafNodes(root);
    printf("Number of leaf nodes in the BST: %d\n", numLeafNodes);
    int minNode = findMin(root);
    int maxNode = findMax(root);
    printf("Minimum node value: %d\n", minNode);
    printf("Maximum node value: %d\n", maxNode);
    printf("Leaf nodes of the BST: ");
    printLeafNodes(root);
    printf("\n");
    printf("Nodes of the BST level-wise: ");
    printLevelWise(root);
    printf("\n");
    deleteTree(root);
    return 0;
}
