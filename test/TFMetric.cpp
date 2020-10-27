#include "gtest/gtest.h"
#include <dirent.h>

extern "C"
{
#include "testy/TFMetric.h"
}

//All right
TEST(findTFMetric1, ok)
{
    // GTree *tree;
    // tree = findTFMetric("../../test/testFiles/test1.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");

    // tree = findTFMetric("../../test/testFiles/test2.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");

    // tree = findTFMetric("../../test/testFiles/test3.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");

    // tree = findTFMetric("../../test/testFiles/test4.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");

    // tree = findTFMetric("../../test/testFiles/test5.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");

    // tree = findTFMetric("../../test/testFiles/test6.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");

    // tree = findTFMetric("../../test/testFiles/test7.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");

    // tree = findTFMetric("../../test/testFiles/test8.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");

    // tree = findTFMetric("../../test/testFiles/test9.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");

    // tree = findTFMetric("../../test/testFiles/test10.txt");
    // g_tree_print(tree);
    // g_tree_destroy(tree);
    // printf("\n");
    char pathToDir[100] = "../../test/testFiles";
    int lenPath = strlen(pathToDir);

    DIR *dir;
    dirent *entry;

    assert((dir = opendir(pathToDir)) != NULL);
    int numFile = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type != DT_REG)
            continue;
        numFile++;
    }
    closedir(dir);

    TFData **arrIFData = new TFData *[numFile];

    assert((dir = opendir(pathToDir)) != NULL);
    for (int ind = 0; (entry = readdir(dir)) != NULL;)
    {
        if (entry->d_type != DT_REG)
            continue;
        char *pathToFile = (char *)malloc(sizeof(char) * (lenPath + strlen(entry->d_name) + 2));
        strcpy(pathToFile, pathToDir);
        pathToFile[lenPath] = '/';
        strcpy(pathToFile + lenPath + 1, entry->d_name);

        printf("\t%s\n", pathToFile);
        arrIFData[ind++] = findTFMetric(pathToFile);
        
        printf("%d\n", arrIFData[ind - 1]->numWords);
        g_tree_print_sd(arrIFData[ind - 1]->tree);

        free(pathToFile);
        printf("\n");
    }

    for (int i = 0; i < numFile; i++)
        g_tree_destroy(arrIFData[i]->tree);
    delete[] arrIFData;
    closedir(dir);
}
