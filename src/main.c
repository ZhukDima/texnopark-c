#include <stdio.h>
#include "testy/TF-IDFMetric.h"
#include <assert.h>

int main(int argc, char *argv[])
{
    printf("%d %s\n", argc, argv[0]);
    assert(argc == 2);
    struct TFIDFData **arr = findTFIDFMetric(argv[1]);
    for (int i = 0; arr[i] != NULL; i++)
    {
        printf("\n%s\n", arr[i]->fileName);
        g_tree_print_sf(arr[i]->tree);
        
        free(arr[i]->fileName);
        g_tree_destroy(arr[i]->tree);
    }
    free(arr);
    return 0;
}