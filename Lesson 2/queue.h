#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node
{
	int matrix[3][3];

    struct Node* next;
} Node;

void push_matrix(Node node, int matrix);

void pop_matrix(Node node);

#endif