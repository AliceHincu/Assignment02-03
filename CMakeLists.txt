cmake_minimum_required(VERSION 3.17)
project(a23_913AliceHincu C)

set(CMAKE_C_STANDARD 11)

add_executable(a23_913AliceHincu main.c ui/ui.c domain/offer.c repo/repo_offer.c tests/tests.c tests/tests.h validation/offer_validator.c validation/offer_validator.h service/offer_service.c service/offer_service.h dynamic_array/dynamic_array.c dynamic_array/dynamic_array.h)