//
// Created by Sakura on 3/9/2021.
//

#include "tests.h"
#include "../validation/offer_validator.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


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

    char type[] = "mountain";
    char destination[] = "Bacau";
    char departure_date[] = "19-01-2020";
    int price = 50;

    Offer* legit_offer = create_offer(type, destination, departure_date, price);
    assert(get_price_offer(legit_offer)==price);
    assert(strcmp(get_type_offer(legit_offer), "mountain")==0);
    assert(strcmp(get_destination_offer(legit_offer), "Bacau")==0);
    assert(strcmp(get_departure_date_offer(legit_offer), "19-01-2020")==0);


    int r = validate_offer(legit_offer);
    assert(r==1);
    destroy_offer(legit_offer);


    printf("Stop validation tests... \n");
}

void run_all_tests(){
    run_all_domain_tests();
    run_all_validation_tests();
}