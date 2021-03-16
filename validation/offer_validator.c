//
// Created by Sakura on 3/9/2021.
//

#include "offer_validator.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int validate_price(char* price){
    for (int index = 0; index < strlen(price); index++){
        if(isalpha(price[index]) && price[index] != '.') return 0;
    }
    return 1;
}


// validate uniqueness - An offer is uniquely identified by its destination and departure dates
int validate_uniqueness(DynamicArray *da, Offer *offer){
    TElement *of = get_all(da);
    char *offer_destination = get_destination_offer(offer);
    char *offer_departure_date = get_departure_date_offer(offer);
    for(int i=0;i<get_length(da);i++) {
        char* existing_offer_destination = get_destination_offer(of[i]);
        char* existing_offer_departure_date = get_departure_date_offer(of[i]);
        if (strcmp(existing_offer_destination, offer_destination) == 0 &&
            strcmp(existing_offer_departure_date, offer_departure_date) == 0)
                return 2;

    }
    return 1;
}


// Type has to be seaside, mountain or city break
int validate_type(Offer *offer){
    char *type = get_type_offer(offer);
    if(!(strcmp(type, "mountain")==0 || strcmp(type, "seaside")==0 || strcmp(type, "city break")==0)) return 3;
    return 1;

}


// The only condition for the destination is to not be an empty string
int validate_destination(Offer *offer){
    char *destination = get_destination_offer(offer);
    if(strcmp(destination, "")==0) return 5;
    return 1;
}


/* validate departure date
     * Year can’t be less than 1000 and more than 9999
     * Months between 01-12
     * Days between 01-31
     * Format: dd-mm-yyyy
     * */
int validate_date(Offer *offer){
    int day = offer->detailed_date.day;
    int month = offer->detailed_date.month;
    int year = offer->detailed_date.year;

    ///check format
    if (strlen(offer->departure_date)!=10)
        return 7;

    int done = 1;
    for(int index=0; index<10 && done; index++){
        char letter = offer->departure_date[index];
        if(index==2||index==5) {
            if (letter != '-')
                return 7;
        }
        else
            if (isalpha(letter))
                return 7;
    }

    ///check intervals
    if(year > 9999 || year < 1000 || month < 1 || month > 12 || day < 1 || day > 31)
        return 7;

    //Now we will check date according to month
    if( month == 2 ) {
        if((year % 4 == 0) && (year % 100 != 0) && (year % 400 == 0)) {
            if(day > 29)
                return 7;
        }
        if(day >= 30)
            return 7;
    }
    //April, June, September and November are with 30 days
    if ( month == 4 || month == 6 || month == 9 || month == 11 )
        if(day > 30)
            return 7;

   return 1;
}


int validate_offer(DynamicArray *da, Offer *offer){
    int rez = 1;

    rez *= validate_uniqueness(da, offer);

    // validate type - must be seaside, mountain or city break
    rez *= validate_type(offer);

    // validate destination - everything works except ""
    rez *= validate_destination(offer);

    // validate departure

    rez *= validate_date(offer);

    return rez;
}