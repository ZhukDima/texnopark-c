#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct skyscraper {
    size_t number_floors;
    size_t height;
    size_t spire_height;
    char purpose[100];
    char location_region[100];
};

void input_data(struct skyscraper *skyscrapers, size_t size);

void output_on_purpose(struct skyscraper **skyscrapers, size_t size);

int comp_purpose(const void *a, const void *b);

void output_on_location_region(struct skyscraper **skyscrapers, size_t size);

int comp_location_region(const void *a, const void *b);

void output_grouped_data(struct skyscraper **skyscrapers, size_t size);

#endif
