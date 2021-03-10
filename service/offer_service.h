//
// Created by Sakura on 3/10/2021.
//

#ifndef A23_913ALICEHINCU_OFFER_SERVICE_H
#define A23_913ALICEHINCU_OFFER_SERVICE_H

#include "../dynamic_array/dynamic_array.h"

void create_offer_service(DynamicArray *da, char* type, char* destination, char* departure_date, int price);
TElement* get_offers_service(DynamicArray *da);
void delete_offer_service(DynamicArray *da, int nr);

void update_offer_service(DynamicArray *da, int position, char* type, char* destination, char * departure_date, int price);

#endif //A23_913ALICEHINCU_OFFER_SERVICE_H
