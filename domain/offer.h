//
// Created by Sakura on 3/8/2021.
//

typedef struct {
    char* type;
    char* destination;
    char* departure_date;
    double price;
}Offer;

Offer* create_offer(char*, char*, char*, int);
Offer* copy_offer(Offer*);

char* get_type_offer(Offer*);
char* get_destination_offer(Offer*);
char* get_departure_date_offer(Offer*);
int get_price_offer(Offer*);

void change_type(Offer *offer, char* new_type);
void change_destination(Offer *offer, char* new_dest);
void change_date(Offer *offer, char* new_date);
void change_price(Offer *offer, int new_price);

void destroy_offer(Offer*);
