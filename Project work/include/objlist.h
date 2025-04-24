#ifndef OBJLIST_H
#define OBJLIST_H

#include "addons.h"

typedef struct ObjNode 
{
    Object3D object;
    struct ObjNode* next;
} ObjNode;

typedef struct ObjList 
{
    ObjNode* head;
    int count;
} ObjList;

ObjNode* create_obj_node(Object3D object);

ObjList* create_obj_list();

void add_object(ObjList* obj_list, Object3D object);

void delete_last_object(ObjList* obj_list);

#endif