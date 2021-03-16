
#include "ui/ui.h"


#include "tests/tests.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(void){
    DynamicArray* da = createDynamicArray(2);

    run_all_tests();
    choose_option_ui(da);
    return 0;
}