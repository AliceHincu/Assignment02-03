//
// Created by Sakura on 3/8/2021.
//

#include "repo_offer.h"
#include <stdio.h>

void add_offer_repo(DynamicArray *da, Offer* of){
    char *type = get_type_offer(of);
    printf("%s/n", type);
}

TElement* get_offers(DynamicArray *da){
    return get_all(da);

}