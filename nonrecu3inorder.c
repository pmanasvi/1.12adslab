#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};
struct StackNode {
    struct TreeNode* treeNode;
    struct StackNode* next;
};
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct StackNode* createStackNode(struct TreeNode* treeNode) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    return newNode;
}
struct Stack {
    struct StackNode* top;
};
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}
int isStackEmpty(struct Stack* stack) {
    return stack->top == NULL;
}
void push(struct Stack* stack, struct TreeNode* treeNode) {
    struct StackNode* newNode = createStackNode(treeNode);
    newNode->next = stack->top;
    stack->top = newNode;
}
struct TreeNode* pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        return NULL;
    }
    struct StackNode* temp = stack->top;
    struct TreeNode* treeNode = temp->treeNode;
    stack->top = temp->next;
    free(temp);
    return treeNode;
}
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }


    struct Stack* stack = createStack();
    struct TreeNode* current = root;
    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }
    free(stack);
}
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack = createStack();
    push(stack, root);
    while (!isStackEmpty(stack)) {
        struct TreeNode* current = pop(stack);
        printf("%d ", current->data);
        if (current->right) {
            push(stack, current->right);
        }
        if (current->left) {
            push(stack, current->left);
        }
    }
    free(stack);
}
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    struct Stack* stack1 = createStack();
    struct Stack* stack2 = createStack();
    push(stack1, root);
    while (!isStackEmpty(stack1)) {
        struct TreeNode* current = pop(stack1);
        push(stack2, current);
        if (current->left) {
            push(stack1, current->left);
        }
        if (current->right) {
            push(stack1, current->right);
        }
    }
    while (!isStackEmpty(stack2)) {
        struct TreeNode* current = pop(stack2);
        printf("%d ", current->data);
    }
    free(stack1);
    free(stack2);
}
void insert(struct TreeNode** root, int data) {
    struct TreeNode* newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
    } else {
        struct TreeNode* current = *root;
        struct TreeNode* parent = NULL;
  while (current != NULL) {
            parent = current;
            if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
}
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
int main() {
    struct TreeNode* root = NULL;
    int data;
    char choice;
    do {
        printf("Enter an element to insert into the binary tree: ");
        scanf("%d", &data);
        insert(&root, data);
        printf("Do you want to insert another element? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
    printf("\nInorder Traversal: ");
    inorderTraversal(root);
    printf("\nPreorder Traversal: ");
    preorderTraversal(root);
    printf("\nPostorder Traversal: ");
    postorderTraversal(root);
    printf("\n");
    freeTree(root);
    return 0;}
