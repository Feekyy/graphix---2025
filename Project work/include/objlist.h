#ifndef OBJLIST_H
#define OBJLIST_H

#include "addons.h"

typedef struct ObjNode ObjNode;

typedef struct ObjNode
{
    Shapes shape;
    ObjNode* next;
} ObjNode;

typedef struct ObjList
{
    ObjNode* head;
    int count;
} ObjList;

ObjNode* create_obj_node(Shapes shape);

ObjList* create_obj_list();

void add_object(ObjList* obj_list, Shapes shape);

void delete_last_object(ObjList* obj_list);

void switch_shapes(ObjList* obj_list, Shapes Shape, int overwrite);

#endif