//
// Created by Sakura on 3/8/2021.
//

#include "offer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Offer* create_offer(char* type, char* destination, char* departure_date, double price){

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


    offer->detailed_date = get_detailed_date(departure_date);

    return offer;
}


Offer* copy_offer(Offer* offer){
    create_offer(offer->type, offer->destination, offer->departure_date, offer->price);
}


char* get_type_offer(Offer* offer){
    if (offer == NULL)
        return NULL;
    return offer -> type;
}


char* get_destination_offer(Offer* offer){
    if (offer == NULL)
        return NULL;
    return offer -> destination;
}


char* get_departure_date_offer(Offer* offer){
    if (offer == NULL)
        return NULL;
    return offer -> departure_date;
}


Date get_detailed_date(char* departure_date){
    // pointer to current split section
    char *pch;
    Date final_date;
    // info needed
    int day = -1, month = -1, year = -1;
    // split the date from beginning to the first occurrence of -
    pch = strtok(departure_date,"-");

    // while we have more / chars
    while (pch != NULL){
        // set the variables
        char* num = pch;
        int nr = atoi(pch);
        if(day == -1) day = nr;
        else if(month == -1) month = nr;
        else if(year == -1) year = nr;

        // continue splitting the string
        pch = strtok (NULL, "-");
    }
    final_date.day = day;
    final_date.month = month;
    final_date.year = year;
    return final_date;
}


double get_price_offer(Offer* offer){
    if (offer == NULL)
        return 0;
    return offer -> price;
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

    offer->detailed_date = get_detailed_date(new_date);
}


void change_price(Offer *offer, double new_price){
    offer->price = new_price;
}


void destroy_offer(Offer* offer){
    free(offer->departure_date);
    free(offer->type);
    free(offer->destination);
    free(offer);
}