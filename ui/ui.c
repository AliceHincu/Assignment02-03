//
// Created by Sakura on 3/8/2021.
//

#include "ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../service/offer_service.h"

char *read_string(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional (dynamic array)
//star before name of function because we return a pointer
//file *fp - So the pointer doesn't change (still points to the handler structure of the file) but the data pointed by the structure does.
    char *str;
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
    //printf("here now \n");
    int ch;
    ch=fgetc(fp);
    //printf("here \n");
    while(EOF!= ch && ch != '\n'){
        str[len++] = ch;

        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str) return str;
        }
        ch=fgetc(fp);
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
           "*7. List offers.\n\t"
           "*8. For a given destination, display all offers, sorted ascending by departure month.\n\t"
           "**9. Display all tourism offers whose types contain a given string (if the string is empty, all types"
           "are considered), and show them sorted ascending by departure month.\n\t"
           "10. Undo.\n\t"
           "11. Redo");
}


void add_offer_ui(DynamicArray *da, UndoRedoMemento *undoRedo){
    printf("\n~Conditions~\n  -type has to be mountain, seaside or city break\n  -the date must respect the format"
           " dd-mm-yyyy\n  -the year must be between 1000 and 9999");
    printf("\n~Add an offer~\n  Type: ");
    char *type;
    type = read_string(stdin, 10);

    printf("  Destination: ");
    char *destination;
    destination = read_string(stdin, 10);

    printf("  Departure_date: ");
    char *departure_date;
    departure_date = read_string(stdin, 10);

    printf("  Price: ");
    char *price;
    price = read_string(stdin, 10);

    create_offer_service(da, undoRedo, type, destination, departure_date, price);

    free(type);
    free(destination);
    free(departure_date);
    free(price);
}

void delete_offer_ui(DynamicArray*da, UndoRedoMemento *undoRedo){
    printf("\n~Delete offer~\n  Which offer do you want to delete: ");
    char *nr = read_string(stdin, 10);
    long int num = strtol(nr, NULL, 10);

    //validation
    if (num < 1 || num > da->length)
        printf("This offer does not exist. The interval is between 1 and %d\n", da->length);
    else
        delete_offer_service(da, undoRedo, num-1);
    free(nr);
}

void update_offer_ui(DynamicArray *da, UndoRedoMemento *undoRedo){
    printf("\n~Update an offer~\n  Which offer do you want to update: ");
    char *nr;
    nr = read_string(stdin, 10);
    long int num = strtol(nr,NULL,10);

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

    if (num < 1 || num > da->length)
        printf("This offer does not exist. The interval is between 1 and %d\n", da->length);
    else
        update_offer_service(da, undoRedo, num-1, type, destination, departure_date, price);

    free(nr);
    free(type);
    free(destination);
    free(departure_date);
    free(price);
}

void list_offers(DynamicArray *da){
    printf("\n~Offers~\n\n");
    TElement *offers = get_offers_service(da);
    for(int i=0;i<get_length(da);i++){
        Offer* offer = offers[i];
        printf("\n-- Offer number %d --", i+1);
        printf("\n\tType: %s", get_type_offer(offer));
        printf("\n\tDestination: %s", get_destination_offer(offer));
        printf("\n\tDeparture date: %s", get_departure_date_offer(offer));
        printf("\n\tPrice: %lf", get_price_offer(offer));
    }
    printf("\n");
}



void display_destination_string_ui(DynamicArray * da){
    printf("Input string: ");
    char *input;
    input = read_string(stdin, 10);

    DynamicArray * da_dest;
    DynamicArray * sorted_da;

    if(strcmp(input, "")==0)
        da_dest = copyDynamicArray(da);
    else {
        da_dest = createDynamicArray(10, &destroy_offer, &copy_offer);
        da_dest = get_destination_string_service(da, da_dest, input);
    }

    sorted_da=sort_by_price(da_dest);
    list_offers(sorted_da);

    destroyDynamicArray(da_dest);
    free(input);
}


void display_type_string_ui(DynamicArray * da){
    printf("Input string: ");
    char *input;
    input = read_string(stdin, 10);

    DynamicArray * da_dest;
    DynamicArray * sorted_da ;

    if(strcmp(input, "")==0)
        da_dest = copyDynamicArray(da);
    else {
        da_dest = createDynamicArray(10, &destroy_offer, &copy_offer);
        da_dest = get_type_string_service(da, da_dest, input);
    }


    sorted_da=sort_by_month(da);
    list_offers(sorted_da);

    destroyDynamicArray(da_dest);
    free(input);
}


void display_destination_month_ui(DynamicArray * da){
    printf("Input destination: ");
    char *input;
    input = read_string(stdin, 10);

    DynamicArray * da_dest;
    DynamicArray * sorted_da;

    if(strcmp(input, "")==0)
        da_dest = copyDynamicArray(da);
    else {
        da_dest = createDynamicArray(10, &destroy_offer, &copy_offer);
        da_dest = get_destination_string_service(da, da_dest, input);
    }

    sorted_da = sort_by_price(da_dest);
    list_offers(sorted_da);

    destroyDynamicArray(da_dest);
    free(input);

}


void display_type_sort_date_ui(DynamicArray * da){
    printf("Input type: ");
    char *input;
    input = read_string(stdin, 10);

    printf("Input date: ");
    char *inputDate;
    inputDate = read_string(stdin, 10);

    printf("reverse= ");
    char *inputReverse;
    inputReverse = read_string(stdin, 10);

    DynamicArray * da_dest;
    DynamicArray * da_date;
    DynamicArray * sorted_da;

    da_dest = createDynamicArray(10, &destroy_offer, &copy_offer);
    da_dest = get_type_string_service(da, da_dest, input);

    da_date = createDynamicArray(10, &destroy_offer, &copy_offer);
    da_date = get_after_date_service(da_dest, da_date, inputDate);

    sorted_da = sort_by_date(da_date, inputReverse);
    list_offers(sorted_da);

    destroyDynamicArray(da_dest);
    destroyDynamicArray(da_date);
    free(input);
    free(inputDate);
    free(inputReverse);

}

void undo_ui(DynamicArray* da, UndoRedoMemento *undoRedo)
{
    undoService(da, undoRedo);
}

void redo_ui(DynamicArray* da, UndoRedoMemento *undoRedo)
{
    redoService(da, undoRedo);
}

void startup_offers_ui(DynamicArray* da){
    char *type = malloc(sizeof(char)*100);
    char *dest = malloc(sizeof(char)*100);
    char *date = malloc(sizeof(char)*100);

    strcpy(type, "seaside");
    strcpy(dest, "Mamaia");
    strcpy(date, "19-04-2020");
    double price_offer = 460;
    Offer *offer1 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer1);

    strcpy(type, "seaside");
    strcpy(dest, "Neptun");
    strcpy(date, "29-05-2020");
    price_offer = 560;
    Offer *offer2 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer2);

    strcpy(type, "seaside");
    strcpy(dest, "Eforie sud");
    strcpy(date, "11-04-2020");
    price_offer = 340;
    Offer *offer3 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer3);

    strcpy(type, "seaside");
    strcpy(dest, "Jupiter");
    strcpy(date, "03-08-2020");
    price_offer = 288;
    Offer *offer4 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer4);

    strcpy(type, "city break");
    strcpy(dest, "New York");
    strcpy(date, "11-01-2020");
    price_offer = 1100;
    Offer *offer5 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer5);

    strcpy(type, "city break");
    strcpy(dest, "Paris");
    strcpy(date, "19-09-2020");
    price_offer = 1800;
    Offer *offer6 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer6);

    strcpy(type, "city break");
    strcpy(dest, "London");
    strcpy(date, "15-06-2020");
    price_offer = 1050;
    Offer *offer7 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer7);

    strcpy(type, "mountain");
    strcpy(dest, "Brasov");
    strcpy(date, "15-09-2020");
    price_offer = 650;
    Offer *offer8 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer8);

    strcpy(type, "mountain");
    strcpy(dest, "Everest");
    strcpy(date, "15-10-2020");
    price_offer = 2650;
    Offer *offer9 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer9);

    strcpy(type, "mountain");
    strcpy(dest, "Sibiu");
    strcpy(date, "15-09-2020");
    price_offer = 250;
    Offer *offer10 = create_offer(type, dest, date, price_offer);
    addElementToDynamicArray(da, offer10);

    free(type);
    free(dest);
    free(date);

}

void choose_option_ui(){
    char *choose;

    bool done = false;
    DynamicArray* da = createDynamicArray(2, &destroy_offer, &copy_offer);
    UndoRedoMemento * undoRedo = createUndoRedoMemento();
    addState(undoRedo, da);
    startup_offers_ui(da);
    addState(undoRedo, da);
    print_menu();

    while(!done) {
        printf("\nInput command : ");
        choose = read_string(stdin, 10); // stdin for standard input(keyboard)

        if (strcmp(choose, "0") == 0){
            done = true;
            destroyDynamicArray(da);
            destroyUndoRedoMemento(undoRedo);
        }
        else if (strcmp(choose, "1") == 0){
            add_offer_ui(da, undoRedo);
        }
        else if (strcmp(choose, "2") == 0){
            delete_offer_ui(da, undoRedo);
        }
        else if (strcmp(choose, "3") == 0){
            update_offer_ui(da, undoRedo);
        }
        else if (strcmp(choose, "4") == 0){
            display_destination_string_ui(da);
        }
        else if (strcmp(choose, "5") == 0){
            display_type_sort_date_ui(da);
        }

        else if (strcmp(choose, "7") == 0){
            list_offers(da);
        }
        else if (strcmp(choose, "8") == 0){
            display_destination_month_ui(da);
        }
        else if (strcmp(choose, "9") == 0){
            display_type_string_ui(da);
        }
        else if (strcmp(choose, "10") == 0){
            undo_ui(da, undoRedo);
        }
        else if (strcmp(choose, "11") == 0){
            redo_ui(da, undoRedo);
        }
        else printf("Wrong command! Please try again!");
        free(choose);


    }

}