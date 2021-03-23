//
// Created by Sakura on 3/10/2021.
//

#include "offer_service.h"
#include "../validation/offer_validator.h"
#include "../repo/repo_offer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void create_offer_service(DynamicArray *da, UndoRedoMemento *undoRedo, char* type, char* destination, char* departure_date, char* price) {
    double pr = strtod(price, NULL);
    Offer *of = create_offer(type, destination, departure_date, pr);

    int validation = validate_offer(da, of);
    if (validation == 1 && validate_price(price)) {
        add_offer_repo(da, of);
        addState(undoRedo, da);
    }

    else {
        printf("\n Errors:");
        if (validation%2==0) printf("\n\tThe offer already exists!(An offer with the same date and destination already exists!");
        if (validation%3==0) printf("\n\tThe type is not valid!");
        if (validation%5==0) printf("\n\tThe destination is not valid!");
        if (validation%7==0) printf("\n\tThe departure date is not valid!");
        if (validation%11==0) printf("\n\tThe price is not valid!");
        if (validate_price(price)==0) printf("\n\tThe price is not valid!");
        printf("\n");
        da->destroyElementFunction(of);
        //destroy_offer(of);
    }
}


void delete_offer_service(DynamicArray *da, UndoRedoMemento *undoRedo, long int nr){
    delete_offer_repo(da, nr);
    addState(undoRedo, da);
}

void update_offer_service(DynamicArray *da, UndoRedoMemento *undoRedo, long int position, char* type, char* destination, char * departure_date, char* price){
    double pr = strtod(price, NULL);
    Offer *of = create_offer(type, destination, departure_date, pr);

    int validation = validate_offer(da, of);
    if (validation == 1 && validate_price(price)) {
        update_offer_repo(da, position, type, destination, departure_date, pr);
        addState(undoRedo, da);
    }

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
    //destroy_offer(of);
    da->destroyElementFunction(of);
}

TElement * get_offers_service(DynamicArray *da){
    return get_offers(da);
}

void undoService(DynamicArray *da, UndoRedoMemento *undoRedo){

    if ((undoRedo->undoCurrent!=1 && undoRedo->savedStates->length==1) || (undoRedo->undoCurrent!=0 && undoRedo->savedStates->length>1)){
        DynamicArray* undo = copyDynamicArray(Undo(undoRedo));
        copyFromToDynamicArrayUndo(da, undo);
        destroyDynamicArray(undo);

    }
    else
        printf("No more undo!");
}

void redoService(DynamicArray *da, UndoRedoMemento *undoRedo) {
    if (undoRedo->undoCurrent+1 < undoRedo->undoMaximum){
        DynamicArray* redo = copyDynamicArray(Redo(undoRedo));
        copyFromToDynamicArrayUndo(da, redo);
        destroyDynamicArray(redo);

    }
    else
        printf("No more redo!");

}

/// Returns a dynamic array with the offers which have the same destination as the input string
DynamicArray* get_destination_string_service(DynamicArray *da, DynamicArray * da_dest, char* input){
    TElement *of = get_offers_service(da);
    for(int i=0;i<get_length(da);i++) {
        Offer *t = of[i];
        if (strcmp(get_destination_offer(t), input) == 0) addElementToDynamicArray(da_dest, da->copyElementFunction(of[i]));
    }
    return da_dest;
}


/// Returns a dynamic array with the offers which have the same type as the input string
DynamicArray* get_type_string_service(DynamicArray *da, DynamicArray * da_dest, char* input){
    TElement *of = get_offers_service(da);
    for(int i=0;i<get_length(da);i++) {
        Offer *copy = da->copyElementFunction(of[i]);
        if (strcmp(get_type_offer(copy), input) == 0)
            addElementToDynamicArray(da_dest, copy);
        else
            da->destroyElementFunction(copy);
            //destroy_offer(copy);
    }

    return da_dest;

}

DynamicArray *get_after_date_service(DynamicArray *da, DynamicArray *da_date, char* inputDate){
    TElement *of = get_offers_service(da);
    Date input_date = get_detailed_date(inputDate);
    for(int i=0;i<get_length(da);i++) {
        Offer *copy = da->copyElementFunction(of[i]);

        if (get_year_offer(copy)<input_date.year) {
            da->destroyElementFunction(copy);
            continue;
        }
        if (get_year_offer(copy)>input_date.year){
            addElementToDynamicArray(da_date, copy);
            continue;
        }
        if (get_year_offer(copy)==input_date.year){
            if (get_month_offer(copy)<input_date.month) {
                da->destroyElementFunction(copy);
                continue;
            }
            if (get_month_offer(copy)>input_date.month) {
                addElementToDynamicArray(da_date, copy);
                continue;
            }
            if (get_month_offer(copy)==input_date.month){
                printf("here");
                if(get_day_offer(copy)<=input_date.day) {
                    printf(" <= ");
                    da->destroyElementFunction(copy);
                    continue;
                }
                else {
                    printf(" > ");
                    addElementToDynamicArray(da_date, copy);
                    continue;
                }
            }
        }

    }
    return da_date;
}


DynamicArray * sort_by_price(DynamicArray *da){
    TElement *of = get_offers_service(da);
    for(int i=0;i<get_length(da)-1;i++) {
        for(int j=i+1;j<get_length(da);j++) {
            if (get_price_offer(of[i])>get_price_offer(of[j]))
            {
                Offer *aux = of[i];
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
            if (get_month_offer(of[i]) > get_month_offer(of[j])) {
                Offer *aux = of[i];
                of[i] = of[j];
                of[j] = aux;
            }
        }
    }
    return da;
}

DynamicArray * sort_by_date(DynamicArray *da, char* reverse) {
    TElement *of = get_offers_service(da);
    for (int i = 0; i < get_length(da) - 1; i++) {
        for (int j = i + 1; j < get_length(da); j++) {
            int ok = 0;
            printf("%d %d %d ", get_day_offer(of[i]), get_month_offer(of[i]), get_year_offer(of[i]));
            printf("%d %d %d\n", get_day_offer(of[j]), get_month_offer(of[j]), get_year_offer(of[j]));
            if (get_year_offer(of[i])>get_year_offer(of[j])){
                ok=1;
            }
            if (get_year_offer(of[i])==get_year_offer(of[j])){
                printf("here year");
                if (get_month_offer(of[i])>get_month_offer(of[j])) {
                    printf("here month");
                    ok=1;
                }
                if (get_month_offer(of[i])==get_month_offer(of[j]) && get_day_offer(of[i]) > get_day_offer(of[j])){
                    printf("here day");
                    ok=1;
                }
            }
            printf("%d", ok);
            if(ok==1 && strcmp(reverse, "false")==0){
                Offer *aux = of[i];
                of[i] = of[j];
                of[j] = aux;
            }
            if(ok==0 && strcmp(reverse, "true")==0){
                Offer *aux = of[i];
                of[i] = of[j];
                of[j] = aux;
            }

        }
    }
    return da;
}
