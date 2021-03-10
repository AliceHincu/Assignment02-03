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

TElement * get_offers_service(DynamicArray *da){
    return get_offers(da);
}
