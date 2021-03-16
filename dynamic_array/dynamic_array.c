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
    da->elements = (TElement*)malloc(capacity * sizeof(TElement));
    if (da->elements == NULL)
        return NULL;

    return da;
}


void destroyDynamicArray(DynamicArray* arr)
{
    if (arr == NULL)
        return;

    // free the space allocated for the elements
    for(int index = 0; index < arr->length; index++) {
        if (arr->elements[index] != NULL) {
            destroy_offer(arr->elements[index]);
            //free(arr->elements[index]);
        }
    }
    free(arr->elements);
    arr->elements = NULL;

    // free the space allocated for the dynamic array
    free(arr);
}


void resizeDynamicArray(DynamicArray* arr, int new_capacity)
{
    if (arr == NULL)
        return;

    // resize
    arr -> capacity = new_capacity;
    TElement * aux_arr = (TElement *)realloc(arr->elements, arr->capacity*sizeof(TElement));
    if(aux_arr==NULL)
        return;

    arr->elements = aux_arr;
}


void addElementToDynamicArray(DynamicArray* arr, TElement t)
{
    if (arr == NULL)
        return;
    if (arr->elements == NULL)
        return;

    // resize the array, if necessary
    if (arr->length == arr->capacity)
        resizeDynamicArray(arr, 2*(arr->capacity));
    arr->elements[arr->length] = t;
    arr->length++;
}


void deleteElementFromPosition(DynamicArray *arr, int position){
    if (position >= arr->length)
        return;
    if (arr->length == arr->capacity/4)
        resizeDynamicArray(arr, arr->capacity/2);

    destroy_offer(arr->elements[position]);
    for(int i = position; i< arr->length-1;++i)
        arr -> elements[i] = arr -> elements[i+1];

    arr -> length--;
}


TElement *get_all(DynamicArray* arr){
    if (arr == NULL)
        return NULL;

    return arr->elements;

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
    addElementToDynamicArray(da, p1);
    assert(da->length == 1);

    Offer* p2 = create_offer("Wvsd", "vsdv", "vsdds", 6);
    addElementToDynamicArray(da, p2);
    assert(da->length == 2);

    // capacity must double
    Offer* p3 = create_offer("Wvsd", "vsdv", "vsdds", 6);
    addElementToDynamicArray(da, p3);
    assert(da->length == 3);
    assert(da->capacity == 4);

    destroyDynamicArray(da);
}