#include "objlist.h"
#include <stdlib.h>

ObjNode* create_obj_node(Object3D object)
{
    ObjNode* new_node = (ObjNode*)malloc(sizeof(ObjNode));
    if (new_node == NULL) 
    {
        return NULL;
    }
    new_node->object = object;
    new_node->next = NULL;
    return new_node;
}

ObjList* create_obj_list()
{
    ObjList* new_list = (ObjList*)malloc(sizeof(ObjList));
    if (new_list == NULL) 
    {
        return NULL;
    }
    new_list->head = NULL;
    new_list->count = 0;
    return new_list;
}

void add_object(ObjList* obj_list, Object3D object)
{
    ObjNode* new_node = create_obj_node(object);
    if (new_node == NULL) 
    {
        return;
    }

    if (obj_list->head == NULL) 
    {
        obj_list->head = new_node;
    }
    else
    {
        ObjNode* current = obj_list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    obj_list->count++;
}

void delete_last_object(ObjList* obj_list)
{
    if (obj_list->head == NULL) 
    {
        return;
    }

    if (obj_list->head->next == NULL) 
    {
        free(obj_list->head);
        obj_list->head = NULL;
        obj_list->count = 0;
        return;
    }

    ObjNode* current = obj_list->head;
    ObjNode* previous = NULL;

    while (current->next != NULL) 
    {
        previous = current;
        current = current->next;
    }

    free(current);
    previous->next = NULL;
    obj_list->count--;
}