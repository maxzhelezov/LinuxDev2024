#include <check.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <sys/resource.h>
#include <stdlib.h>
#include "roman.h"

char *buf=0;
void roman_setup(void){
    ;
}

void roman_teardown(void){
    if (buf != NULL){
        free(buf);
    }
}

START_TEST(roman_from_to_number){
    char *buf = 0;
    to_roman(from_roman("IV"), &buf);
    assert(strcmp("IV", buf) == 0);
    to_roman(from_roman("ix"), &buf);
    fprintf(stderr, "%d", from_roman("ix"));
    assert(strcmp("IX", buf) == 0);
} END_TEST

START_TEST(roman_to_from_number){
    char *buf = 0;
    for(int i =1; i < 4999; i++){
        to_roman(i, &buf);
        int val = from_roman(buf);
        assert(val == i);
    }
} END_TEST

START_TEST(roman_to_edge_cases){
    char *buf = 0;

    assert(to_roman(0, &buf) == -1);
    assert(to_roman(-1, &buf) == -1);
    assert(to_roman(-2, &buf) == -1);
    assert(to_roman(5000, &buf) == -1);
    assert(to_roman(5001, &buf) == -1);

} END_TEST

START_TEST(roman_from_edge_cases){
    char *buf = 0;

    assert(from_roman("abc") == -1);
    assert(from_roman("ixi") == -1);
    assert(from_roman("IIIII") == -1);
    assert(from_roman("LLL") == -1);
    assert(from_roman("") == -1);
    assert(from_roman(NULL) == -1);

} END_TEST

int main(int argc, char *argv[]){
    Suite *suite = suite_create("tests");
    TCase *c_roman = tcase_create("roman");
    SRunner *runner = srunner_create(suite);
    int ret;

    // roman suite
    suite_add_tcase(suite, c_roman);
    tcase_add_checked_fixture(c_roman, roman_setup, roman_teardown);
    tcase_add_test(c_roman, roman_from_to_number);
    tcase_add_test(c_roman, roman_to_from_number);
    tcase_add_test(c_roman, roman_to_edge_cases);
    tcase_add_test(c_roman, roman_from_edge_cases);

    srunner_run_all(runner, CK_ENV);
    ret = srunner_ntests_failed(runner);
    srunner_free(runner);
    return ret != 0;
} 

