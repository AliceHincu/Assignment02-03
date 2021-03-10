//
// Created by Sakura on 3/10/2021.
//

#include "dynamic_array.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity)
{
    DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
    // make sure that the space was allocated
    if (da == NULL)
        return NULL;

    da->capacity = capacity;
    da->length = 0;

    // allocate space for the elements
    da->elems = (TElement*)malloc(capacity * sizeof(TElement));
    if (da->elems == NULL)
        return NULL;

    return da;
}

void destroy(DynamicArray* arr)
{
    if (arr == NULL)
        return;

    // free the space allocated for the planets
    free(arr->elems);
    arr->elems = NULL;

    // free the space allocated for the dynamic array
    free(arr);
    //arr = NULL; // !!!
}

// Resizes the array, allocating more space.
void resize(DynamicArray* arr, int new_capacity)
{
    if (arr == NULL)
        return;

    arr -> capacity = new_capacity;
    TElement * aux_arr = (TElement *)realloc(arr->elems, arr->capacity*sizeof(TElement));
    if(aux_arr==NULL)
        return;
    arr->elems = aux_arr;
    return;
}

void add(DynamicArray* arr, TElement t)
{
    if (arr == NULL)
        return;
    if (arr->elems == NULL)
        return;

    // resize the array, if necessary
    if (arr->length == arr->capacity)
        resize(arr, 2*(arr->capacity));
    arr->elems[arr->length] = t;
    arr->length++;
}

void delete_from_position(DynamicArray *arr, int position){
    if (position >= arr->length)
        return;
    if (arr->length == arr->capacity/4){
        resize(arr, arr->capacity/2);
    }
    destroy_offer(arr->elems[position]);
    for(int i = position; i< arr->length-1;++i){
        arr -> elems[i] = arr -> elems[i+1];
    }
    arr -> length--;
}

TElement *get_all(DynamicArray* arr){
    if (arr == NULL)
        return NULL;

    return arr->elems;

}
int get_length(DynamicArray * arr){
    return arr->length;
}
void testsDynamicArray()
{
    DynamicArray* da = createDynamicArray(2);
    if (da == NULL)
        assert(0);

    assert(da->capacity == 2);
    assert(da->length == 0);

    Offer* p1 = create_offer("Wvsd", "vsdv", "vsdds", 6);
    add(da, p1);
    assert(da->length == 1);

    Offer* p2 = create_offer("Wvsd", "vsdv", "vsdds", 6);
    add(da, p2);
    assert(da->length == 2);

    // capacity must double
    Offer* p3 = create_offer("Wvsd", "vsdv", "vsdds", 6);
    add(da, p3);
    assert(da->length == 3);
    assert(da->capacity == 4);

    destroy(da);
}