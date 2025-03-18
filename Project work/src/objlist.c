#include "addons.h"
#include "objlist.h"
 
#include <stdio.h>
#include <stdlib.h>

ObjNode* create_obj_node(ShapeType shapeType)
{
    ObjNode* obj = malloc(sizeof(ObjNode));
    ShapeType* shape_ptr = malloc(sizeof(ShapeType));
    *shape_ptr = shapeType;
    obj->shape = shape_ptr;
    obj->next = NULL;
    return obj;
}

ObjList* create_obj_list()
{
    ObjList* obj_list = malloc(sizeof(ObjList));
    obj_list->head = NULL;
    obj_list->count = 0;

    return obj_list;
}

void add_object(ObjList* obj_list, ShapeType shapeType)
{
    ObjNode* new_node = create_obj_node(shapeType);

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
    if (obj_list->count == 0 || obj_list->head == NULL) return;

    if (obj_list->count == 1) 
    {
        free(obj_list->head->shape);
        free(obj_list->head);
        obj_list->head = NULL;
        obj_list->count = 0;
        return;
    }

    ObjNode* current = obj_list->head;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    free(current->next->shape);
    free(current->next);
    current->next = NULL;
    obj_list->count--;
}

void switch_shapes(ObjList* obj_list, ShapeType new_shape, int overwrite)
{
    if (obj_list == NULL || obj_list->head == NULL || overwrite < 0 || overwrite >= obj_list->count) 
    {
        return;
    }

    ObjNode *current = obj_list->head;
    for (int i = 0; i < overwrite && current != NULL; i++) 
    {
        current = current->next;
    }

    if (current != NULL) 
    {
        ShapeType* shape_ptr = (ShapeType*)current->shape;
        *shape_ptr = new_shape;
    }
}