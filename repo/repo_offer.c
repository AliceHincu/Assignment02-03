//
// Created by Sakura on 3/8/2021.
//

#include "repo_offer.h"
#include <stdio.h>

void add_offer_repo(DynamicArray *da, Offer* of){
    addElementToDynamicArray(da, of);
}

void delete_offer_repo(DynamicArray *da, long int nr){
    deleteElementFromPosition(da, nr);
}

void update_offer_repo(DynamicArray *da, long int position, char* type, char* destination, char * departure_date, double price){
    Offer* t = da->elements[position];
    change_type(t, type);
    change_destination(t, destination);
    change_date(t,departure_date);
    change_price(t,price);
}

TElement* get_offers(DynamicArray *da){
    return get_all(da);

}

void setNewArray(DynamicArray *da, DynamicArray* undoArray){
    DynamicArray *undo;
    undo = undoArray;
    da = copyDynamicArray(undoArray);

}