#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list node.
struct ListNode {
    int val;
    struct ListNode *next;
};
// Function to create a new ListNode
struct ListNode* createListNode(int x) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = x;
    newNode->next = NULL;
    return newNode;
}

// Function to remove elements from the linked list
struct ListNode* removeElements(struct ListNode* head, int val) {
    // Create a dummy node that points to the head
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->val = 0; // Dummy value
    dummy->next = head;

    // Initialize current node to the dummy node
    struct ListNode* current = dummy;

    // Iterate through the linked list
    while (current->next != NULL) {
        if (current->next->val == val) {
            // Skip the node with the value equal to val
            struct ListNode* temp = current->next;
            current->next = current->next->next;
            free(temp); // Free the removed node
        } else {
            // Move to the next node
            current = current->next;
        }
    }

    // Get the new head, which is the next of the dummy node
    struct ListNode* newHead = dummy->next;
    free(dummy); // Free the dummy node
    return newHead;
}

// Helper function to create a linked list from an array
struct ListNode* createLinkedList(int* arr, int size) {
    struct ListNode* head = NULL;
    struct ListNode* tail = NULL;

    for (int i = 0; i < size; i++) {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = arr[i];
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode; // First node
            tail = newNode;
        } else {
            tail->next = newNode; // Append to the end
            tail = newNode;
        }
    }
    return head;
}

// Function to reverse the linked list
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL; // Previous node starts as NULL
    struct ListNode* current = head; // Current node starts as head
    struct ListNode* next = NULL; // Next node

    while (current != NULL) {
        next = current->next; // Store the next node
        current->next = prev; // Reverse the current node's pointer
        prev = current; // Move prev to current
        current = next; // Move to the next node
    }

    return prev; // New head of the reversed list
}

// Helper function to print the linked list
void printLinkedList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

// Helper function to free the linked list
void freeLinkedList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        struct ListNode* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    /* Test case 1
    int arr1[] = {1, 2, 6, 3, 4, 5, 6};
    struct ListNode* head1 = createLinkedList(arr1, 7);
    head1 = removeElements(head1, 6);
    printLinkedList(head1); // Output: 1 2 3 4 5

     //Free the linked list
    freeLinkedList(head1);

    // Test case 2
    struct ListNode* head2 = NULL; // Empty list
    head2 = removeElements(head2, 1);
    printLinkedList(head2); // Output: (nothing)

    // Test case 3
    int arr3[] = {7, 7, 7,6,4, 7};
    struct ListNode* head3 = createLinkedList(arr3, 6);
    head3 = removeElements(head3, 7);
    printLinkedList(head3); // Output: (nothing)

    // Free the linked list
    freeLinkedList(head3);

    return 0;

    */

  int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
  struct ListNode* head = createLinkedList(arr, 36);
  printf("Original list: ");
  printLinkedList(head);

  head = reverseList(head);
  printf("Reversed list: ");
  printLinkedList(head);

  // Free the linked list
  freeLinkedList(head);

  return 0;

}
