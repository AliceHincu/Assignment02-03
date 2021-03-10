//
// Created by Sakura on 3/9/2021.
//
#include "../dynamic_array/dynamic_array.h"

#ifndef A23_913ALICEHINCU_OFFER_VALIDATOR_H
#define A23_913ALICEHINCU_OFFER_VALIDATOR_H

/* Function that validates the type, destination, departure date and price of an offer given by its pointer as follows
 * input data: offer - a dynamically allocated offer
 * output data: rez - integer value depicting the result of the validation
 *              if rez == 1: the offer is valid
 *              else if
 *                 rez % 3 : the offer type is invalid
 *                 rez % 5 : the offer destination is invalid
 *                 rez % 5 : the offer departure date is invalid
 *                 rez % 7: the offer price is invalid
 */
int validate_offer(Offer* offer);
int good_validator(DynamicArray *da, Offer *offer);

#endif //A23_913ALICEHINCU_OFFER_VALIDATOR_H
