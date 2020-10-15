#include "testy/customer.h"

int main() {
    printf("Введите число небоскрёбов: ");
    size_t size;
    scanf("%zu", &size);
    printf("\n");
    struct skyscraper *skyscrapers = (struct skyscraper *) malloc(size);
    input_data(skyscrapers, size);
    output_grouped_data(&skyscrapers, size);
    free(skyscrapers);
    return 0;
}
