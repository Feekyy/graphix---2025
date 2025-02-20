#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

void push_matrix(Node node, int matrix)
{
    if (node->matrix == NULL)
    {
        node->matrix = matrix;
        return;
    }

    struct Node* next = (struct Node*)malloc(sizeof(Node));
    next->matrix = matrix;
    node->next = *node;
    *node = next;
}

void pop_matrix(Node node)
{
    if (node->matrix == NULL)
    {
        return;
    }

    node = node->next;
    free(node);
}