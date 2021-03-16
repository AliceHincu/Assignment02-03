//
// Created by Sakura on 3/10/2021.
//

#include "offer_service.h"
#include "../validation/offer_validator.h"
#include "../repo/repo_offer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void create_offer_service(DynamicArray *da, char* type, char* destination, char* departure_date, char* price) {
    double pr = strtod(price, NULL);
    Offer *of = create_offer(type, destination, departure_date, pr);

    int validation = validate_offer(da, of);
    if (validation == 1 && validate_price(price))
        add_offer_repo(da, of);

    else {
        printf("\n Errors:");
        if (validation%2==0) printf("\n\tThe offer already exists!(An offer with the same date and destination already exists!");
        if (validation%3==0) printf("\n\tThe type is not valid!");
        if (validation%5==0) printf("\n\tThe destination is not valid!");
        if (validation%7==0) printf("\n\tThe departure date is not valid!");
        if (validation%11==0) printf("\n\tThe price is not valid!");
        if (validate_price(price)==0) printf("\n\tThe price is not valid!");
        printf("\n");
    }
}


void delete_offer_service(DynamicArray *da, int nr){
    //validation
    delete_offer_repo(da, nr);
}


void update_offer_service(DynamicArray *da, int position, char* type, char* destination, char * departure_date, double price){
    //validation
    update_offer_repo(da, position, type, destination, departure_date, price);
}

TElement * get_offers_service(DynamicArray *da){
    return get_offers(da);
}

DynamicArray* get_destination_string_service(DynamicArray *da, DynamicArray * da_dest, char* input){
    TElement *of = get_offers_service(da);
    for(int i=0;i<get_length(da);i++) {
        Offer *t = of[i];
        if (strcmp(get_destination_offer(t), input) == 0) addElementToDynamicArray(da_dest, copy_offer(of[i]));
    }

    return da_dest;

}

DynamicArray * sort_by_price(DynamicArray *da){
    TElement *of = get_offers_service(da);
    for(int i=0;i<get_length(da)-1;i++) {
        for(int j=i+1;j<get_length(da);j++) {
            if (get_price_offer(of[i])>get_price_offer(of[j]))
            {
                Offer *aux = copy_offer(of[i]);
                of[i] = of[j];
                of[j] = aux;
            }
        }
    }

    return da;

}


DynamicArray * sort_by_month(DynamicArray *da) {
    TElement *of = get_offers_service(da);
    for (int i = 0; i < get_length(da) - 1; i++) {
        for (int j = i + 1; j < get_length(da); j++) {
            if (of[i]->detailed_date.month > of[j]->detailed_date.month) {
                Offer *aux = copy_offer(of[i]);
                of[i] = of[j];
                of[j] = aux;
            }
        }
    }

    return da;
}
