//
// Created by Sakura on 3/8/2021.
//
#ifndef A23_913ALICEHINCU_REPO_OFFER_H
#define A23_913ALICEHINCU_REPO_OFFER_H

#include "../dynamic_array/dynamic_array.h"
#include "../undo/Undo-MementoApproach.h"

void add_offer_repo(DynamicArray *da, Offer* of);
void delete_offer_repo(DynamicArray *da, long int nr);
void update_offer_repo(DynamicArray *da, long int position, char* type, char* destination, char * departure_date, double price);
void setNewArray(DynamicArray *da, DynamicArray* undoArray);

TElement *get_offers(DynamicArray *da);


#endif //A23_913ALICEHINCU_REPO_OFFER_H