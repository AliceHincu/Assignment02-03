//
// Created by Sakura on 3/10/2021.
//

#ifndef A23_913ALICEHINCU_OFFER_SERVICE_H
#define A23_913ALICEHINCU_OFFER_SERVICE_H

#include "../dynamic_array/dynamic_array.h"
#include "../undo/Undo-MementoApproach.h"

void create_offer_service(DynamicArray *da, UndoRedoMemento *undoRedo, char* type, char* destination, char* departure_date, char* price);
TElement* get_offers_service(DynamicArray *da);
void delete_offer_service(DynamicArray *da, UndoRedoMemento *undoRedo, long int nr);
void undoService(DynamicArray *da, UndoRedoMemento *undoRedo);
void redoService(DynamicArray *da, UndoRedoMemento *undoRedo);

DynamicArray *get_after_date_service(DynamicArray *da, DynamicArray *da_date, char* inputDate);

void update_offer_service(DynamicArray *da, UndoRedoMemento *undoRedo, long int position, char* type, char* destination, char * departure_date, char* price);
DynamicArray * get_destination_string_service(DynamicArray *da, DynamicArray * da_dest, char* input);
DynamicArray* get_type_string_service(DynamicArray *da, DynamicArray * da_dest, char* input);
DynamicArray * sort_by_price(DynamicArray *da);
DynamicArray * sort_by_month(DynamicArray *da);

DynamicArray * sort_by_date(DynamicArray *da, char *reverse);

#endif //A23_913ALICEHINCU_OFFER_SERVICE_H
