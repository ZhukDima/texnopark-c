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
    WordTFIDF **arr = topFiveTFIDFMetric(pathToDir);
    for (int i = 0; arr[i] != NULL; i++) {
        printf("\n%s\n", arr[i]->fileName);
        for (int j = 0; j < 5; j++) {
            printf("[%Lf, %s]\n", arr[i]->arrIFIDF[j], arr[i]->arrWords[j]);
            free(arr[i]->arrWords[j]);
        }
        
        free(arr[i]->arrWords);
        free(arr[i]->arrIFIDF);
        free(arr[i]->fileName);
        free(arr[i]);
    }
    free(arr);
}
