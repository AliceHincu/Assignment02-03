//
// Created by Sakura on 3/9/2021.
//

#include "tests.h"
#include "../validation/offer_validator.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void run_all_domain_tests(){
    printf("Start domain tests ...\n");

    char type[] = "mountain";
    char destination[] = "Bacau";
    char departure_date[] = "19-01-2020";
    int price = 50;

    Offer* offer1 = create_offer(type, destination, departure_date, price);

    assert(get_price_offer(offer1)==price);
    assert(strcmp(get_type_offer(offer1), "mountain")==0);
    assert(strcmp(get_destination_offer(offer1), "Bacau")==0);
    assert(strcmp(get_departure_date_offer(offer1), "19-01-2020")==0);
    destroy_offer(offer1);

    printf("End domain tests ...\n");
}


void run_all_validation_tests(){
    printf("Start validation tests... \n");

    // test price
    char *price = "a56";
    assert (validate_price(price)==0);
    price = "56.4";
    assert (validate_price(price)==1);

    // test uniqueness
    DynamicArray* da = createDynamicArray(3, &destroy_offer, &copy_offer);
    char *type = malloc(sizeof(char)*100);
    char *dest = malloc(sizeof(char)*100);
    char *date = malloc(sizeof(char)*100);

    strcpy(type, "seaside");
    strcpy(dest, "Bacau");
    strcpy(date, "19-01-2002");
    double price_offer = 46;

    Offer *offer1 = create_offer(type, dest, date, price_offer);


    strcpy(dest, "Bucuresti");
    strcpy(date, "18-01-1900");
    Offer *offer2 = create_offer(type, dest, date, price_offer);

    strcpy(dest, "Brasov");
    strcpy(date, "18-01-1900");
    Offer *offer3 = create_offer(type, dest, date, price_offer);

    addElementToDynamicArray(da, offer1);
    addElementToDynamicArray(da, offer2);
    assert(validate_uniqueness(da, offer1)==2);
    assert(validate_uniqueness(da, offer3)==1);

    destroyDynamicArray(da);



    //test type
    assert(validate_type(offer3)==1); //seaside
    strcpy(type, "mountain");
    change_type(offer3, type);
    assert(validate_type(offer3)==1);
    strcpy(type, "city break");
    change_type(offer3, type);
    assert(validate_type(offer3)==1);
    strcpy(type, "bla bla");
    change_type(offer3, type);
    assert(validate_type(offer3)==3);
    free(type);




    //test destination
    assert(validate_destination(offer3)==1);
    //strcpy(dest, "");
    //change_destination(offer3, dest);
    //assert(validate_destination(offer3)==5);
    free(dest);




    //test date
    assert(validate_date(offer3)==1); // correct one

    strcpy(date, "12345678910"); //not 10 ch
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "11/11/1111"); //not with "-"
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "1a-11-1111"); //has a letter
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "11-11-0999"); //wrong year
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "11-13-2002"); //wrong month
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "11-00-2002"); //wrong month
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "00-12-2002"); //wrong day
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "60-12-2002"); //wrong day
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "29-02-2020"); //leap year
    change_date(offer3, date);
    assert(validate_date(offer3)==1);
    strcpy(date, "29-02-2019"); //not leap year
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "30-02-2020"); //feb doesn't have 30days
    change_date(offer3, date);
    assert(validate_date(offer3)==7);
    strcpy(date, "31-04-2020"); //April has only 30days
    change_date(offer3, date);
    assert(validate_date(offer3)==7);

    free(date);
    destroy_offer(offer3);
    printf("Stop validation tests... \n");
}

void run_all_tests(){
    run_all_domain_tests();
    run_all_validation_tests();
}