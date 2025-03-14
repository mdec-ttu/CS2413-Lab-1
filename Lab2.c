//FIFO code 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a queue node
struct QueueNode {
    int data;
    struct QueueNode* next;
};

// Define the structure for a queue
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Define the structure for a FIFO queue using two queues
struct FIFOQueue {
    struct Queue* q1;
};

// Function to create a new queue node
struct QueueNode* createQueueNode(int data) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (queue == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to create a new FIFO queue
struct FIFOQueue* createFIFOQueue() {
    struct FIFOQueue* fifoQueue = (struct FIFOQueue*)malloc(sizeof(struct FIFOQueue));
    if (fifoQueue == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    fifoQueue->q1 = createQueue();
    return fifoQueue;
}

// Function to check if a queue is empty
bool isQueueEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue an element into a queue
void queueEnqueue(struct Queue* queue, int data) {
    struct QueueNode* newNode = createQueueNode(data);
    if (isQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue an element from a queue
int queueDequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        exit(1);
    }

    struct QueueNode* temp = queue->front;
    int data = temp->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

// Function to enqueue an element into the FIFO queue
void enqueue(struct FIFOQueue* fifoQueue, int data) {
    queueEnqueue(fifoQueue->q1, data);
}

// Function to dequeue an element from the FIFO queue
int dequeue(struct FIFOQueue* fifoQueue) {
    if (isQueueEmpty(fifoQueue->q1)) {
        printf("FIFO Queue is empty\n");
        exit(1);
    }
    return queueDequeue(fifoQueue->q1);
}

// Function to check if the FIFO queue is empty
bool isFIFOQueueEmpty(struct FIFOQueue* fifoQueue) {
    return isQueueEmpty(fifoQueue->q1);
}

// Function to print the contents of the FIFO queue
void printFIFOQueue(struct FIFOQueue* fifoQueue) {
    struct Queue* tempQueue = createQueue();

    printf("FIFO Queue contents (front to back): ");
    while (!isQueueEmpty(fifoQueue->q1)) {
        int value = queueDequeue(fifoQueue->q1);
        printf("%d ", value);
        queueEnqueue(tempQueue, value);
    }

    while (!isQueueEmpty(tempQueue)) {
        queueEnqueue(fifoQueue->q1, queueDequeue(tempQueue));
    }

    printf("\n");
}

// Function to free memory for the FIFO queue
void freeFIFOQueue(struct FIFOQueue* fifoQueue) {
    while (!isQueueEmpty(fifoQueue->q1)) {
        queueDequeue(fifoQueue->q1);
    }
    free(fifoQueue->q1);
    free(fifoQueue);
}

// Main function to test the FIFO queue
int main() {
    struct FIFOQueue* fifoQueue = createFIFOQueue();

    printf("\n=== First Test Case ===\n");
    printf("Enqueuing elements: 1, 2, 3, 4, 5\n");
    enqueue(fifoQueue, 1);
    enqueue(fifoQueue, 2);
    enqueue(fifoQueue, 3);
    enqueue(fifoQueue, 4);
    enqueue(fifoQueue, 5);

    printFIFOQueue(fifoQueue);

    printf("Dequeued elements: ");
    while (!isFIFOQueueEmpty(fifoQueue)) {
        printf("%d ", dequeue(fifoQueue));
    }
    printf("\n");

    printf("\n=== Second Test Case ===\n");
    printf("Enqueuing new elements: 10, 20, 30\n");
    enqueue(fifoQueue, 10);
    enqueue(fifoQueue, 20);
    enqueue(fifoQueue, 30);

    printFIFOQueue(fifoQueue);

    printf("Dequeued elements: ");
    while (!isFIFOQueueEmpty(fifoQueue)) {
        printf("%d ", dequeue(fifoQueue));
    }
    printf("\n");

    // Free the memory
    freeFIFOQueue(fifoQueue);

    return 0;
}


//LIFO code 

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a stack node
struct StackNode {
    int data;
    struct StackNode* next;
};

// Define the structure for a stack
struct Stack {
    struct StackNode* top;
};

// Define the structure for a queue using two stacks
struct Queue {
    struct Stack* stack1; // For enqueue
    struct Stack* stack2; // For dequeue
};

// Function to create a new stack node
struct StackNode* createStackNode(int data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    stack->top = NULL;
    return stack;
}

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (queue == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    queue->stack1 = createStack();
    queue->stack2 = createStack();
    return queue;
}

// Function to check if a stack is empty
int isStackEmpty(struct Stack* stack) {
    return (stack->top == NULL);
}

// Function to push an element onto a stack
void push(struct Stack* stack, int data) {
    struct StackNode* newNode = createStackNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop an element from a stack
int pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    struct StackNode* temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

// Function to enqueue an element into the queue
void enqueue(struct Queue* queue, int data) {
    push(queue->stack1, data);
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* queue) {
    // If both stacks are empty, the queue is empty
    if (isStackEmpty(queue->stack1) && isStackEmpty(queue->stack2)) {
        printf("Queue is empty\n");
        exit(1);
    }
    
    // If stack2 is empty, transfer all elements from stack1 to stack2
    if (isStackEmpty(queue->stack2)) {
        while (!isStackEmpty(queue->stack1)) {
            push(queue->stack2, pop(queue->stack1));
        }
    }
    
    // Pop and return the top element from stack2
    return pop(queue->stack2);
}

// Function to peek at the front element of the queue without removing it
int peek(struct Queue* queue) {
    // If both stacks are empty, the queue is empty
    if (isStackEmpty(queue->stack1) && isStackEmpty(queue->stack2)) {
        printf("Queue is empty\n");
        exit(1);
    }
    
    // If stack2 is empty, transfer all elements from stack1 to stack2
    if (isStackEmpty(queue->stack2)) {
        while (!isStackEmpty(queue->stack1)) {
            push(queue->stack2, pop(queue->stack1));
        }
    }
    
    // Return the top element from stack2 without popping it
    return queue->stack2->top->data;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return (isStackEmpty(queue->stack1) && isStackEmpty(queue->stack2));
}

// Function to print the contents of the queue
void printQueue(struct Queue* queue) {
    // Create temporary stacks to not disturb the original queue
    struct Stack* tempStack1 = createStack();
    struct Stack* tempStack2 = createStack();
    struct Stack* tempStack3 = createStack();
    
    printf("Queue contents (front to back): ");
    
    // First handle elements in stack2 (these are at the front of the queue)
    struct StackNode* current = queue->stack2->top;
    while (current != NULL) {
        push(tempStack1, current->data);
        current = current->next;
    }
    
    // Reverse to get original order
    while (!isStackEmpty(tempStack1)) {
        push(tempStack2, pop(tempStack1));
    }
    
    // Print elements from tempStack2
    while (!isStackEmpty(tempStack2)) {
        int value = pop(tempStack2);
        printf("%d ", value);
    }
    
    // Now handle elements in stack1 (these are at the back of the queue)
    current = queue->stack1->top;
    while (current != NULL) {
        push(tempStack1, current->data);
        current = current->next;
    }
    
    // Elements in stack1 need two reversals to get the correct queue order
    while (!isStackEmpty(tempStack1)) {
        push(tempStack2, pop(tempStack1));
    }
    
    while (!isStackEmpty(tempStack2)) {
        push(tempStack3, pop(tempStack2));
    }
    
    // Print elements from tempStack3
    while (!isStackEmpty(tempStack3)) {
        int value = pop(tempStack3);
        printf("%d ", value);
    }
    
    printf("\n");
    
    // Free temporary stacks
    // Make sure all nodes are freed first
    while(!isStackEmpty(tempStack1)) {
        pop(tempStack1);
    }
    while(!isStackEmpty(tempStack2)) {
        pop(tempStack2);
    }
    while(!isStackEmpty(tempStack3)) {
        pop(tempStack3);
    }
    
    free(tempStack1);
    free(tempStack2);
    free(tempStack3);
}

// Function to free the memory allocated for a queue
void freeQueue(struct Queue* queue) {
    // Free all nodes in stack1
    while (!isStackEmpty(queue->stack1)) {
        pop(queue->stack1);
    }
    
    // Free all nodes in stack2
    while (!isStackEmpty(queue->stack2)) {
        pop(queue->stack2);
    }
    
    // Free the stack structures
    free(queue->stack1);
    free(queue->stack2);
    
    // Free the queue structure
    free(queue);
}

// Main function to test the queue implementation
int main() {
    struct Queue* queue = createQueue();
    
    printf("\n=== First Test Case ===\n");
    // Enqueue elements
    printf("Enqueuing elements: 1, 2, 3, 4, 5\n");
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    
    printf("Front element: %d\n", peek(queue));
    
    // Print queue contents before dequeuing
    printQueue(queue);
    
    printf("Dequeued elements: ");
    while (!isQueueEmpty(queue)) {
        printf("%d ", dequeue(queue));
    }
    printf("\n\n");
    
    printf("=== Second Test Case ===\n");
    // Enqueue more elements after emptying the queue
    printf("Enqueuing new elements: 10, 20, 30\n");
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    
    // Print queue contents before dequeuing
    printQueue(queue);
    
    printf("Dequeued elements: ");
    while (!isQueueEmpty(queue)) {
        printf("%d ", dequeue(queue));
    }
    printf("\n");
    
    // Free the memory
    freeQueue(queue);
    
    return 0;
}
