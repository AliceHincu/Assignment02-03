//
// Created by Sakura on 3/21/2021.
//

#include "Undo-MementoApproach.h"
#include <stdlib.h>

#include <stdio.h>


/// Create a new UndoRedo mechanism using the memento pattern approach
UndoRedoMemento *createUndoRedoMemento(){
    UndoRedoMemento* undoRedo = (UndoRedoMemento*)malloc(sizeof(UndoRedoMemento));
    if (undoRedo == NULL) // make sure that the space was allocated
        return NULL;

    //every state is a dynamic array
    undoRedo->savedStates = createDynamicArray(10, &destroyDynamicArray, &copyDynamicArray);
    undoRedo->undoMaximum = 0;
    undoRedo->undoCurrent = 0;

    return undoRedo;
};


void destroyUndoRedoMemento(UndoRedoMemento *undoRedo){
    if(undoRedo == NULL)
        return;

    for(int index = 0; index < undoRedo->undoMaximum; index++) {
        if (undoRedo->savedStates->elements[index] != NULL) {
            undoRedo->savedStates->destroyElementFunction(undoRedo->savedStates->elements[index]);
        }
    }
    free(undoRedo->savedStates->elements);
    free(undoRedo->savedStates);
    free(undoRedo);
};


void addState(UndoRedoMemento *undoRedo, DynamicArray *state){
    clearRedoNew(undoRedo);
    addElementToDynamicArray(undoRedo->savedStates, copyDynamicArray(state));
    undoRedo->undoMaximum+=1;
    undoRedo->undoCurrent+=1;
};


// if you undo a lot and then make an operation, you don't access the redos anymore
void clearRedoNew(UndoRedoMemento *undoRedo) {
    for (int i = undoRedo->undoMaximum -1 ; i > undoRedo->undoCurrent; i--) {
        deleteElementFromPosition(undoRedo->savedStates, i);
    }
    undoRedo->undoMaximum = undoRedo->undoCurrent;
}


DynamicArray *Undo(UndoRedoMemento *undoRedo){
    if (undoRedo->undoCurrent == 0) {
        return NULL;
    }

    if (undoRedo->undoCurrent == undoRedo->undoMaximum) { // first time you have to subtract 2 times
        undoRedo->undoCurrent --;
    }
    undoRedo->undoCurrent--;
    return (DynamicArray*)getElementOnPosition(undoRedo->savedStates, undoRedo->undoCurrent);
}

DynamicArray *Redo(UndoRedoMemento *undoRedo) {
    if (undoRedo->undoCurrent == undoRedo->undoMaximum)
        return NULL;
    undoRedo->undoCurrent++;
    return (DynamicArray*)getElementOnPosition(undoRedo->savedStates, undoRedo->undoCurrent);
}
