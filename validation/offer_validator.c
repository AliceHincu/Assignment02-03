//
// Created by Sakura on 3/9/2021.
//

#include "offer_validator.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int validate_offer(Offer *offer){
    int rez = 1;

    // validate type - must be seaside, mountain or city break
    char *type = get_type_offer(offer);
    if(!(strcmp(type, "mountain")==0 || strcmp(type, "seaside")==0 || strcmp(type, "city break")==0)) rez*=3;
    free(type);

    // validate destination - everything works except ""
    char *destination = get_destination_offer(offer);
    if(strcmp(destination, "")==0) rez*=5;
    free(destination);

    /* validate departure date
     * Year can’t be less than 1800 and more than 2100
     * */
    char *date = get_departure_date_offer(offer);

    // pointer to current split section
    char * pch;
    // info needed
    int day = -1, month = -1, year = -1;
    // split the date from beginning to the first occurrence of -
    pch = strtok(date,"-");
    // while we have more / chars
    while (pch != NULL)
    {
        // set the variables
        char* num = pch;
        int nr = atoi(pch);
        if(day == -1) day = nr;
        else if(month == -1) month = nr;
        else if(year == -1) year = nr;

        // continue splitting the string
        pch = strtok (NULL, "-");
    }
    printf("%d %d %d", day, month, year);


    if(year < 1800 || year > 2100)
        rez*=7;
    if(month < 1 || month > 12)
        rez*=7;
    if(day < 1 || day > 31)
        rez*=7;
    //Now we will check date according to month
    if( month == 2 ) {
        if((year % 4 == 0) && (year % 100 != 0) && (year % 400 == 0)) {
            if(day > 29)
                rez *= 7;
        }
    }
    //April, June, September and November are with 30 days
    if ( month == 4 || month == 6 || month == 9 || month == 11 )
        if(day > 30)
            rez*=7;

    return rez;
}