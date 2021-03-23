//
// Created by Sakura on 3/10/2021.
//

#ifndef A23_913ALICEHINCU_DYNAMIC_ARRAY_H
#define A23_913ALICEHINCU_DYNAMIC_ARRAY_H
#pragma once
#include "../domain/offer.h"


/// ------ Define types -------
typedef void * TElement;
typedef void (*DestroyElementFunctionType)(void*);
typedef TElement (*CopyElementFunctionType)(TElement);

typedef struct
{
    TElement* elements; // the elements of the array
    int length;			// actual length of the array
    int capacity;       // capacity
    DestroyElementFunctionType destroyElementFunction; // pointer to function to destroy the element
    CopyElementFunctionType copyElementFunction; // pointer to function to copy the element
} DynamicArray;



/// ------ Functions -------
/// Creates a dynamic array of generic elements, with a given capacity.
/// Returns a pointer the the created dynamic array.
DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElementFunction, CopyElementFunctionType copyElementFunction);

/// Copy the dynamic array
DynamicArray* copyDynamicArray(DynamicArray*arr);

void copyFromToDynamicArrayUndo(DynamicArray*da, DynamicArray*undo);


/// Destroys the dynamic array.
void destroyDynamicArray(DynamicArray* arr);


/// Adds a generic element to the dynamic array.
void addElementToDynamicArray(DynamicArray* arr, TElement t);


/// Delete an element from a position from the dynamic array
void deleteElementFromPosition(DynamicArray *arr, int position);

TElement getElementOnPosition(DynamicArray *arr, int position);


/// Resize the dynamic array
void resizeDynamicArray(DynamicArray* arr, int new_capacity);


/// Returns the elements of the dynamic array
TElement *get_all(DynamicArray* arr);
int get_length(DynamicArray * arr);

// Tests
void testsDynamicArray();

#endif //A23_913ALICEHINCU_DYNAMIC_ARRAY_H
