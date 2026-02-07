#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int value;
    struct Node* nextPtr;
};

struct Node* createNode(int data) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = data;
    newNode->nextPtr = NULL;
    return newNode;
}

void insertAtEnd(struct Node** headRef, int data) 
{
    struct Node* newNode = createNode(data);
    
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    
    struct Node* temp = *headRef;
    while (temp->nextPtr != NULL) {
        temp = temp->nextPtr;
    }
    temp->nextPtr = newNode;
}

void displayReverse(struct Node* currentNode) 
{
    if (currentNode == NULL)
        return;
    
    displayReverse(currentNode->nextPtr);
    printf("%d -> ", currentNode->value);
}

void displayNormal(struct Node* currentNode) 
{
    if (currentNode == NULL) {
        printf("NULL\n");
        return;
    }
    
    printf("%d -> ", currentNode->value);
    displayNormal(currentNode->nextPtr);
}

void freeList(struct Node* head) 
{
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->nextPtr;
        free(temp);
    }
}

int main() 
{
    struct Node* listHead = NULL;
    
    
    insertAtEnd(&listHead, 5);
    insertAtEnd(&listHead, 15);
    insertAtEnd(&listHead, 25);
    insertAtEnd(&listHead, 35);
    insertAtEnd(&listHead, 45);
    
    printf("Normal Order Traversal  : ");
    displayNormal(listHead);
    
    printf("Reverse Order Traversal : ");
    displayReverse(listHead);
    printf("NULL\n");
    
    freeList(listHead);
    
    return 0;
}