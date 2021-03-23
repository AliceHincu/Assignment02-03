//
// Created by Sakura on 3/8/2021.
//


typedef struct {
    int day;
    int month;
    int year;
}Date;

typedef struct {
    char* type;
    char* destination;
    char* departure_date;
    Date detailed_date;
    double price;
}Offer;

Offer* create_offer(char*, char*, char*, double);
Offer* copy_offer(Offer*);

char* get_type_offer(Offer*);
char* get_destination_offer(Offer*);
char* get_departure_date_offer(Offer*);
double get_price_offer(Offer*);
int get_month_offer(Offer* offer);
int get_day_offer(Offer* offer);
int get_year_offer(Offer* offer);
Date get_detailed_date(char* departure_date);

void change_type(Offer *offer, char* new_type);
void change_destination(Offer *offer, char* new_dest);
void change_date(Offer *offer, char* new_date);
void change_price(Offer *offer, double new_price);

void destroy_offer(Offer*);
