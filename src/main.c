#include <stdio.h>
#include "testy/TF-IDFMetric.h"
#include <assert.h>

int main(int argc, char *argv[])
{
    printf("%d %s\n", argc, argv[0]);
    assert(argc == 2);
    printTopFiveTFIDFMetric(argv[1]);
    return 0;
}