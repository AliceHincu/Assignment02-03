//
// Created by Sakura on 3/10/2021.
//

#include "offer_service.h"
#include "../repo/repo_offer.h"
#include <stdio.h>

void create_offer_service(DynamicArray *da, char* type, char* destination, char* departure_date, int price){
    Offer* of = create_offer(type, destination, departure_date, price);
    add_offer_repo(da,of);
    add(da, of);
}

void delete_offer_service(DynamicArray *da, int nr){
    //validation
    delete_offer_repo(da, nr);
}


void update_offer_service(DynamicArray *da, int position, char* type, char* destination, char * departure_date, int price){
    //validation
    update_offer_repo(da, position, type, destination, departure_date, price);
}

TElement * get_offers_service(DynamicArray *da){
    return get_offers(da);
}
