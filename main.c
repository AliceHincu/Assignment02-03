
#include "ui/ui.h"


#include "tests/tests.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(void){
    //printf("%s %s %s %d\n", get_type_offer(of1), get_departure_date_offer(of1), get_destination_offer(of1), get_price_offer(of1));
    DynamicArray* da = createDynamicArray(2);

    run_all_tests();
    choose_option(da);
    return 0;
}