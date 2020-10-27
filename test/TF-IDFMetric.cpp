#include "gtest/gtest.h"
#include <dirent.h>
#include <glib-2.0/glib.h>

extern "C"
{
#include "testy/TF-IDFMetric.h"
}

//All right
TEST(findTFIDFMetric1, ok)
{
    char pathToDir[100] = "../../test/testFiles";
    TFIDFData **arr = findTFIDFMetric(pathToDir);
    for (int i = 0; arr[i] != NULL; i++) {
        printf("\n%s\n", arr[i]->fileName);
        g_tree_print_sf(arr[i]->tree);

        free(arr[i]->fileName);
        g_tree_destroy(arr[i]->tree);
    }
    free(arr);
}
