//
// Created by Sakura on 3/21/2021.
//

#ifndef A23_913ALICEHINCU_UNDO_MEMENTOAPPROACH_H
#define A23_913ALICEHINCU_UNDO_MEMENTOAPPROACH_H


// Memento Approach -> save the last states of the game
// The memento pattern allows one to capture the internal state of an object without violating encapsulation such that later one can
// undo/revert the changes if required

#include "../dynamic_array/dynamic_array.h"

typedef struct{
    DynamicArray* savedStates;
    int undoMaximum;
    int undoCurrent;
}UndoRedoMemento;


/// ------- Functions -------
/// Create a new UndoRedo mechanism using the memento pattern approach
UndoRedoMemento *createUndoRedoMemento();

void destroyUndoRedoMemento(UndoRedoMemento *undoRedo);

void addState(UndoRedoMemento *undoRedo, DynamicArray *state);

void clearRedoNew(UndoRedoMemento *undoRedo);

DynamicArray *Undo(UndoRedoMemento *undoRedo);

DynamicArray *Redo(UndoRedoMemento *undoRedo);



#endif //A23_913ALICEHINCU_UNDO_MEMENTOAPPROACH_H
