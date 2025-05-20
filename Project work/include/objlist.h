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

// Function to create a new node for the object list
ObjNode* create_obj_node(Object3D object);

// Function to create an empty object list
ObjList* create_obj_list();

// Function to add an object to the list
void add_object(ObjList* obj_list, Object3D object);

// Function to delete the last object from the list
void delete_last_object(ObjList* obj_list);

#endif