//
// Created by Sakura on 3/10/2021.
//

#include "dynamic_array.h"
#include <stdlib.h>
#include <assert.h>


DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElementFunction, CopyElementFunctionType copyElementFunction)
{
    DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
    // make sure that the space was allocated
    if (da == NULL)
        return NULL;

    da->capacity = capacity;
    da->length = 0;
    da->elements = (TElement*)malloc(capacity * sizeof(TElement));
    if (da->elements == NULL)
        return NULL;

    da->destroyElementFunction = destroyElementFunction;
    da->copyElementFunction = copyElementFunction;
    return da;
}


void destroyDynamicArray(DynamicArray* arr)
{
    if (arr == NULL)
        return;

    // free the space allocated for the elements
    for(int index = 0; index < arr->length; index++) {
        if (arr->elements[index] != NULL) {
            arr->destroyElementFunction(arr->elements[index]);
        }
    }
    free(arr->elements);
    arr->elements = NULL;

    // free the space allocated for the dynamic array
    free(arr);
}


DynamicArray* copyDynamicArray(DynamicArray*arr)
{
    DynamicArray *new_array = (DynamicArray*)malloc(sizeof(DynamicArray));
    new_array->capacity = arr->capacity;
    new_array->length = arr->length;

    new_array->elements = (TElement*)malloc((arr->capacity*sizeof(TElement)));
    new_array->copyElementFunction = arr->copyElementFunction;
    new_array->destroyElementFunction = arr->destroyElementFunction;
    for(int index=0; index<arr->length;index++){
        new_array->elements[index] = arr->copyElementFunction(arr->elements[index]);
    }
    return new_array;

}

void copyFromToDynamicArrayUndo(DynamicArray*da, DynamicArray*undo){
   for(int index = 0; index < da->length; index++) {
        if (da->elements[index] != NULL) {
            da->destroyElementFunction(da->elements[index]);
        }
    }
    free(da->elements);
    da->elements = NULL;

    da->copyElementFunction = undo->copyElementFunction;
    da->destroyElementFunction = undo->destroyElementFunction;
    da->capacity = undo->length;
    da->length = 0;
    da->elements = (TElement*)malloc( (undo->length)*sizeof(TElement));

    for(int index=0; index<undo->length;index++){
        Offer* of = create_offer(get_type_offer(undo->elements[index]), get_destination_offer(undo->elements[index]),
                                 get_departure_date_offer(undo->elements[index]), get_price_offer(undo->elements[index]));
        addElementToDynamicArray(da, of);
    }

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

    arr->destroyElementFunction(arr->elements[position]);
    for(int i = position; i< arr->length-1;++i)
        arr -> elements[i] = arr -> elements[i+1];

    arr -> length--;
}

TElement getElementOnPosition(DynamicArray *arr, int position) {
    if (position >= arr->length) {
        return NULL;
    }
    return arr->elements[position];
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
    DynamicArray* da = createDynamicArray(2, &destroy_offer, &copy_offer);
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