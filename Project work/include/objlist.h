#ifndef OBJLIST_H
#define OBJLIST_H

#include "addons.h"

typedef struct ObjNode ObjNode;

struct ObjNode
{
    void* shape;

    ObjNode* next;
};

typedef struct ObjList
{
    ObjNode* head;
    int count;
} ObjList;

ObjNode* create_obj_node(ShapeType shapeType);

ObjList* create_obj_list();

void add_object(ObjList* obj_list, ShapeType shapeType);

void delete_last_object(ObjList* obj_list);

void switch_shapes(ObjList* obj_list, ShapeType new_shape, int overwrite);

#endif