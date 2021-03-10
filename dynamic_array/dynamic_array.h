//
// Created by Sakura on 3/10/2021.
//

#ifndef A23_913ALICEHINCU_DYNAMIC_ARRAY_H
#define A23_913ALICEHINCU_DYNAMIC_ARRAY_H
#pragma once
#include "../domain/offer.h."

typedef Offer* TElement;

typedef struct
{
    TElement* elems;
    int length;			// actual length of the array
    int capacity;
} DynamicArray;

/// <summary>
/// Creates a dynamic array of generic elements, with a given capacity.
/// </summary>
/// <param name="capacity">Integer, maximum capacity for the dynamic array.</param>
/// <returns>A pointer the the created dynamic array.</returns>
DynamicArray* createDynamicArray(int capacity);

/// <summary>
/// Destroys the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array to be destoyed.</param>
/// <returns>A pointer the the created dynamic array.</returns>
void destroy(DynamicArray* arr);

/// <summary>
/// Adds a generic element to the dynamic array.
/// </summary>
/// <param name="arr">The dynamic array.</param>
/// <param name="p">The planet to be added.</param>
void add(DynamicArray* arr, TElement t);

TElement *get_all(DynamicArray* arr);
int get_length(DynamicArray * arr);

// Tests
void testsDynamicArray();
#endif //A23_913ALICEHINCU_DYNAMIC_ARRAY_H
