#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef struct Data {
	char* text;
	int priority;
}Data;
// Node
typedef struct node {
	struct Data* data;
	struct node* next;
} Node;

// Function to Create A New Node 
Node* newNode(char* d, int p)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = (Data*)malloc(sizeof(Data)*strlen(d));
	temp->data->text = (char*)malloc(sizeof(char) * strlen(d));
	strcpy(temp->data->text, d);
	temp->data->priority = p;
	temp->next = NULL;

	return temp;
}

// Return the value at head 
char* show(Node** head)
{
	return (*head)->data->text;
}

// Removes the element with the 
// highest priority form the list 
void pop(Node** head)
{
	Node* temp = *head;
	(*head) = (*head)->next;
	free(temp);
}



// Function to push according to priority 
void push(Node** head, char* d, int p)
{
	Node* start = (*head);

	// Create new Node 
	Node* temp = newNode(d, p);

	// Special Case: The head of list has lesser 
	// priority than new node. So insert new 
	// node before head node and change head node. 
	if ((*head)->data->priority > p) {

		// Insert New Node before head 
		temp->next = *head;
		(*head) = temp;
	}
	else {

		// Traverse the list and find a 
		// position to insert new node 
		while (start->next != NULL && start->next->data->priority < p) {
			start = start->next;
		}

		// Either at the ends of the list 
		// or at required position 
		temp->next = start->next;
		start->next = temp;
	}
}

// Function to check is list is empty 
int isEmpty(Node** head)
{
	return (*head) == NULL;
}


void del(Node** head) {
	while ((*head)->next)
	{
		free((*head)->data->text);
		(*head)->data->priority = 0;
	}
	free(*head);
}

void print(Node** head) {
	Node* tmp;
	tmp = *head;
	while (tmp->next != NULL && tmp)
	{
		printf("prior = %d, text: %s\n", (*tmp).data->priority, (*tmp).data->text);
		tmp = tmp->next;
	}
	printf("prior = %d, text: %s\n", (*tmp).data->priority, (*tmp).data->text);
	//del(&tmp);
}

void push_not_prior(Node** head, char* d, int p) {
	Node* start = (*head);
	Node* temp = newNode(d, p);
	while (start->next != NULL) {
		start = start->next;
		//print(&start);
	}
	temp->next = start->next;
	start->next = temp;
}