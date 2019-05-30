#ifndef PQ
#define PQ


// Node 
typedef struct node { 
	int data; 

	// Lower values indicate higher priority 
	int priority; 

	struct node* next; 

} Node; 

// Function to Create A New Node
Node* newNode(int d, int p);
// Return the value at head 
int peek(Node** head);
// Removes the element with the 
// highest priority form the list 
void pop(Node** head);
// Function to push according to priority
void push(Node** head, int d, int p);
int isEmpty(Node** head);

#endif
