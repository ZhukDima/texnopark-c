#include "testy/customer.h"

void input_data(struct skyscraper *skyscrapers, size_t size) {
    printf("Введите данные о небоскрёбах\n");
    for (size_t i = 0; i < size; ++i) {
        printf("Небоскрёб №%zu\n", i + 1);
        printf("Введите число этажей: ");
        scanf("%zu", &skyscrapers[i].number_floors);
        printf("Введите общую высоту: ");
        scanf("%zu", &skyscrapers[i].height);
        printf("Введите высоту шпиля: ");
        scanf("%zu", &skyscrapers[i].spire_height);
        printf("Введите назначение здания: ");
        scanf("%s", skyscrapers[i].purpose);
        printf("Введите регион расположения: ");
        scanf("%s", skyscrapers[i].location_region);
        printf("\n");
    }
}

int comp_purpose(const void *a, const void *b) {
    return strcmp(((const struct skyscraper *) a)->purpose, ((const struct skyscraper *) b)->purpose) > 0;
}

void output_on_purpose(struct skyscraper **skyscrapers, size_t size) {
    qsort(*skyscrapers, size, sizeof(struct skyscraper *), comp_purpose);
    for (size_t i = 0; i < size; ++i) {
        printf("Небоскрёб №%zu \n", i + 1);
        printf("Число этажей: %zu \n", (*skyscrapers)[i].number_floors);
        printf("Общая высота: %zu \n", (*skyscrapers)[i].height);
        printf("Высота шпиля: %zu \n", (*skyscrapers)[i].spire_height);
        printf("Назначение здания: %s \n", (*skyscrapers)[i].purpose);
        printf("Регион расположения: %s \n", (*skyscrapers)[i].location_region);
    }
    printf("\n");
}

int comp_location_region(const void *a, const void *b) {
    return strcmp(((const struct skyscraper *) a)->location_region, ((const struct skyscraper *) b)->location_region) >
           0;
}

void output_on_location_region(struct skyscraper **skyscrapers, size_t size) {
    qsort(*skyscrapers, size, sizeof(struct skyscraper *), comp_location_region);
    for (size_t i = 0; i < size; ++i) {
        printf("Небоскрёб №%zu \n", i + 1);
        printf("Число этажей: %zu \n", (*skyscrapers)[i].number_floors);
        printf("Общая высота: %zu \n", (*skyscrapers)[i].height);
        printf("Высота шпиля: %zu \n", (*skyscrapers)[i].spire_height);
        printf("Назначение здания: %s \n", (*skyscrapers)[i].purpose);
        printf("Регион расположения: %s \n", (*skyscrapers)[i].location_region);
        printf("\n");
    }
    printf("\n");
}

void output_grouped_data(struct skyscraper **skyscrapers, size_t size) {
    printf("Небоскрёбы по назначению: \n");
    output_on_purpose(skyscrapers, size);
    printf("Небоскрёбы по региону расположения: \n");
    output_on_location_region(skyscrapers, size);
}
