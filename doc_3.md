# Program 3: Reverse Traversal of Linked List

## Overview
This program implements and demonstrates an algorithm for traversing a singly linked list in reverse order using recursion without permanently modifying the list structure.

## Data Structures

### Node Structure
struct Node {
    int value;              
    struct Node* nextPtr;   
};

## Functions Implemented

### Basic Linked List Operations

#### 1. `struct Node* createNode(int data)`
- **Purpose**: Dynamically allocates and initializes a new node
- **Algorithm**:
  1. Allocate memory using malloc()
  2. Set value field to provided data
  3. Initialize nextPtr to NULL
  4. Return pointer to new node

#### 2. `void insertAtEnd(struct Node** headRef, int data)`
- **Purpose**: Adds a new node at the end of the linked list
- **Algorithm**:
  1. Create new node with given data
  2. If list is empty, set new node as head
  3. Otherwise, traverse to last node
  4. Link last node's nextPtr to new node

#### 3. `void displayReverse(struct Node* currentNode)`
- **Purpose**: Traverses the list in reverse using recursion
- **Algorithm**:
  1. Base case: If currentNode is NULL, return
  2. Recursively call displayReverse for next node
  3. Print current node's value (during backtracking phase)

#### 4. `void displayNormal(struct Node* currentNode)`
- **Purpose**: Displays the linked list in forward order recursively
- **Algorithm**:
  1. Base case: If currentNode is NULL, print "NULL" and return
  2. Print current node's value
  3. Recursively call displayNormal for next node

#### 5. `void freeList(struct Node* head)`
- **Purpose**: Deallocates all memory used by the linked list
- **Algorithm**:
  1. Iterate through each node
  2. Store current node in temporary pointer
  3. Advance head to next node
  4. Free memory of temporary node
  5. Continue until all nodes are freed

## Main Method Organization

The `main()` function is structured as:

1. **List Initialization**: Creates an empty linked list by setting listHead to NULL.
2. **Header Display**: Prints program title banner.
3. **List Population**: Inserts five nodes with values (5, 15, 25, 35, 45) using insertAtEnd() to build the linked list: 5 → 15 → 25 → 35 → 45 → NULL.
4. **Normal Traversal Display**: Calls displayNormal() to show the list in forward order.
5. **Reverse Traversal Display**: Calls displayReverse() to print the list elements in reverse order (45 → 35 → 25 → 15 → 5 → NULL).
6. **Footer Display**: Prints closing banner.
7. **Memory Cleanup**: Calls freeList() to deallocate all nodes.
8. **Program Termination**: Returns 0 indicating successful execution.

##System Output
![Output_3](output/output_3.png "Program 3 output")