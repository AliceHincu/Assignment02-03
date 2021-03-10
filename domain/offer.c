//
// Created by Sakura on 3/8/2021.
//

#include "offer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Offer* create_offer(char* type, char* destination, char* departure_date, int price){
    Offer* offer = (Offer*)malloc(sizeof(Offer));
    offer -> price = price;

    //make a copy in case type it's local and add +1 for \0. If you don't do that => error.
    //you need to make it.
    offer->type = malloc(sizeof(char)*(strlen(type)+1));
    strcpy(offer->type, type);

    offer->destination = malloc(sizeof(char)*(strlen(destination)+1));
    strcpy(offer->destination, destination);

    offer->departure_date = malloc(sizeof(char)*(strlen(departure_date)+1));
    strcpy(offer->departure_date, departure_date);

    return offer;
}


Offer* copy_offer(Offer* offer){
    create_offer(offer->type, offer->destination, offer->departure_date, offer->price);
}


char* get_type_offer(Offer* offer){
    char* type = (char*)malloc(strlen(offer->type)+1);
    strcpy(type, offer->type);
    type[strlen(offer->type)] = '\0'; // nul terminate the array, so it can be a string
    return type;
}


char* get_destination_offer(Offer* offer){
    char* dest = (char*)malloc(strlen(offer->destination)+1);
    strcpy(dest, offer->destination);
    dest[strlen(offer->destination)] = '\0'; // nul terminate the array, so it can be a string
    return dest;
}


char* get_departure_date_offer(Offer* offer){
    char* dep = (char*)malloc(strlen(offer->departure_date)+1);
    strcpy(dep, offer->departure_date);
    dep[strlen(offer->departure_date)] = '\0'; // nul terminate the array, so it can be a string
    return dep;
}


int get_price_offer(Offer* offer){
    return offer->price;
}


void change_type(Offer *offer, char* new_type){
    free(offer->type);
    offer->type = (char*)malloc(strlen(new_type)+1);
    strcpy(offer->type, new_type);
    offer->type[strlen(new_type)] = '\0'; // nul terminate the array, so it can be a string

}


void change_destination(Offer *offer, char* new_dest){
    free(offer->destination);
    offer->destination = (char*)malloc(strlen(new_dest)+1);
    strcpy(offer->destination, new_dest);
    offer->destination[strlen(new_dest)] = '\0'; // nul terminate the array, so it can be a string

}


void change_date(Offer *offer, char* new_date){
    free(offer->departure_date);
    offer->departure_date = (char*)malloc(strlen(new_date)+1);
    strcpy(offer->departure_date, new_date);
    offer->departure_date[strlen(new_date)] = '\0'; // nul terminate the array, so it can be a string

}


void change_price(Offer *offer, int new_price){
    offer->price = new_price;

}


void destroy_offer(Offer* offer){
    free(offer->type);
    free(offer);
}