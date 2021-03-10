//
// Created by Sakura on 3/8/2021.
//

#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../service/offer_service.h"

char *read_string(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional (dynamic array)
//star before name of function because we return a pointer
//file *fp - So the pointer doesn't change (still points to the handler structure of the file) but the data pointed by the structure does.
    char *str;
    char ch;
    size_t len = 0;

    // This function returns a pointer to the newly allocated memory, or NULL if the request fails.
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str) return str; // in case something it's wrong and str is null

    /*
    - ch = fgetc(fp) -> If a read error occurs, the error indicator for the stream shall be set, fgetc() shall return EOF
    - int fgetc(FILE *stream) gets the next character (an unsigned char) from the specified stream and advances the position
     indicator for the stream. This function returns the character read as an unsigned char cast to an int or EOF on end of file or error.
     - EOF - returns EOF when end of file is reached
    */
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++] = ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str) return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}

void print_menu(){
    printf("\nMenu:\n\t"
           "0. Exit.\n\t"
           "1. Add offer.\n\t"
           "2. Delete offer.\n\t"
           "3. Update offer.\n\t"
           "4. Display all tourism offers whose destinations contain a given string (if the string is empty, all destinations"
           "are considered), and show them sorted ascending by price.\n\t"
           "5. Display all offers of a given type, having their departure after a given date.\n\t"
           "6. Provide multiple undo and redo functionality. Each step will undo/redo the previous operation performed by the user.\n"
           "*7. List offers.\n");
}


void add_offer_ui(DynamicArray *da){
    printf("!!!Validation not complete, please enter correct input!!!\nType: ");
    char *type;
    type = read_string(stdin, 10);

    printf("Destination: ");
    char *destination;
    destination = read_string(stdin, 10);

    printf("Departure_date: ");
    char *departure_date;
    departure_date = read_string(stdin, 10);

    printf("Price: ");
    char *price;
    price = read_string(stdin, 10);
    int pr = atoi(price);
    create_offer_service(da, type, destination, departure_date, pr);
}

void delete_offer_ui(DynamicArray*da){
    printf("!!!Validation not complete, please enter correct input!!!\nWhich offer do you want to delete: ");
    char *nr;
    nr = read_string(stdin, 10);
    int num = atoi(nr);
    delete_offer_service(da, num-1);
}


void list_offers(DynamicArray *da){
    TElement *of = get_offers_service(da);
    for(int i=0;i<get_length(da);i++){
        Offer* t = of[i];
        printf("\n-- Offer number %d --", i+1);
        printf("\n\tType: %s", get_type_offer(t));
        printf("\n\tDestination: %s", get_destination_offer(t));
        printf("\n\tDeparture date: %s", get_departure_date_offer(t));
        printf("\n\tPrice: %d", get_price_offer(t));
    }
    printf("\n");
}


void update_offer_ui(DynamicArray *da){
    printf("!!!Validation not complete, please enter correct input!!!\nWhich offer do you want to update: ");
    char *nr;
    nr = read_string(stdin, 10);
    int num = atoi(nr);

    printf("New type: ");
    char *type;
    type = read_string(stdin, 10);

    printf("New destination: ");
    char *destination;
    destination = read_string(stdin, 10);

    printf("New departure_date: ");
    char *departure_date;
    departure_date = read_string(stdin, 10);

    printf("New price: ");
    char *price;
    price = read_string(stdin, 10);
    int pr = atoi(price);

    update_offer_service(da,num-1, type, destination, departure_date, pr);

}


void choose_option(DynamicArray* da){
    char *choose;
    bool done = false;
    print_menu();

    while(!done) {
        printf("\nInput command : ");
        choose = read_string(stdin, 10); // stdin for standard input(keyboard)

        if (strcmp(choose, "0") == 0){
            done = true;
        }
        else if (strcmp(choose, "1") == 0){
            add_offer_ui(da);
        }
        else if (strcmp(choose, "2") == 0){
            delete_offer_ui(da);
        }
        else if (strcmp(choose, "3") == 0){
            update_offer_ui(da);
        }
        else if (strcmp(choose, "4") == 0){
            break;
        }
        else if (strcmp(choose, "5") == 0){
            break;
        }
        else if (strcmp(choose, "6") == 0){
            break;
        }
        else if (strcmp(choose, "7") == 0){
            list_offers(da);
        }
        else printf("Wrong command! Please try again!");

        free(choose);

    }

}