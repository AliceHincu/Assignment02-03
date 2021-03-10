//
// Created by Sakura on 3/8/2021.
//

#include "repo_offer.h"
#include <stdio.h>

void add_offer_repo(DynamicArray *da, Offer* of){
    char *type = get_type_offer(of);
}

void delete_offer_repo(DynamicArray *da, int nr){
    delete_from_position(da, nr);
}

void update_offer_repo(DynamicArray *da, int position, char* type, char* destination, char * departure_date, int price){
    Offer* t = da->elems[position];
    change_type(t, type);
    change_destination(t, destination);
    change_date(t,departure_date);
    change_price(t,price);
}

TElement* get_offers(DynamicArray *da){
    return get_all(da);

}