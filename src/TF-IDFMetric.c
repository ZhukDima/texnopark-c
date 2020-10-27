#include "testy/TF-IDFMetric.h"
#include <assert.h>
#include <glib-2.0/glib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <math.h>

#define ld long double

gboolean g_tree_elem_print_sf(gpointer key, gpointer value, gpointer data)
{
    printf("Key: %15s\t Value: %Lf\n", (char *)key, *(ld *)value);
    return FALSE;
}

void g_tree_print_sf(GTree *tree)
{
    g_tree_foreach(tree, g_tree_elem_print_sf, NULL);
}

gboolean g_tree_elem_calc_unic_word(gpointer key, gpointer value, gpointer tree_unic_word)
{
    int *p;
    if ((p = g_tree_lookup((GTree *)tree_unic_word, key)) != NULL)
        (*p)++;
    else
    {
        char *copy_key = malloc(sizeof(char) * (strlen((char *)key)));
        strcpy(copy_key, key);
        int *new_data = malloc(sizeof(int));
        *new_data = 1;
        g_tree_insert((GTree *)tree_unic_word, copy_key, new_data);
    }
    return FALSE;
}

GTree *g_tree_calc_unic_word(struct TFData **arrIFData, int numFile)
{
    GTree *tree_unic_word = g_tree_new_full(CompareNames, NULL, free, free);
    for (int i = 0; i < numFile; i++)
    {
        g_tree_foreach(arrIFData[i]->tree, g_tree_elem_calc_unic_word, tree_unic_word);
    }
    return tree_unic_word;
}

struct SpecialData
{
    GTree *tree_TFIDF;
    struct TFData *tf_data;
    GTree *tree_unic_word;
    int numFile;
};

gboolean g_tree_elem_calc_TFIDF_metric(gpointer key, gpointer value, gpointer data)
{
    char *new_key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(new_key, key);
    ld *new_data = malloc(sizeof(ld));
    *new_data = (ld) * (int *)value / ((struct SpecialData *)data)->tf_data->numWords;
    *new_data *= 100*log10l((ld)((struct SpecialData *)data)->numFile 
        / *(int *)g_tree_lookup(((struct SpecialData *)data)->tree_unic_word, key));
    g_tree_insert(((struct SpecialData *)data)->tree_TFIDF, new_key, new_data);
    return FALSE;
}

GTree *g_tree_calc_TFIDF_metric(struct TFData *tf_data, GTree *tree_unic_word, int numFile)
{
    GTree *tree_TFIDF = g_tree_new_full(CompareNames, NULL, free, free);
    struct SpecialData *data = malloc(sizeof(struct SpecialData));
    data->tree_TFIDF = tree_TFIDF;
    data->tf_data = tf_data;
    data->tree_unic_word = tree_unic_word;
    data->numFile = numFile;
    for (int i = 0; i < numFile; i++)
    {
        g_tree_foreach(tf_data->tree, g_tree_elem_calc_TFIDF_metric, data);
    }
    free(data);
    return tree_TFIDF;
}

struct TFIDFData **findTFIDFMetric(const char *pathToDir)
{
    DIR *dir;
    struct dirent *entry;

    assert((dir = opendir(pathToDir)) != NULL);
    int numFile = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type != DT_REG)
            continue;
        numFile++;
    }
    closedir(dir);

    struct TFData **arrIFData = malloc(sizeof(struct TFData *) * numFile);
    int lenPath = strlen(pathToDir);

    assert((dir = opendir(pathToDir)) != NULL);
    for (int ind = 0; (entry = readdir(dir)) != NULL;)
    {
        if (entry->d_type != DT_REG)
            continue;
        char *pathToFile = (char *)malloc(sizeof(char) * (lenPath + strlen(entry->d_name) + 2));
        strcpy(pathToFile, pathToDir);
        pathToFile[lenPath] = '/';
        strcpy(pathToFile + lenPath + 1, entry->d_name);

        arrIFData[ind++] = findTFMetric(pathToFile);

        free(pathToFile);
    }
    closedir(dir);

    GTree *tree_unic_word = g_tree_calc_unic_word(arrIFData, numFile);

    struct TFIDFData **arrTFIDFData = malloc(sizeof(struct TFIDFData *) * (numFile + 1));
    arrTFIDFData[numFile] = NULL;

    for (int i = 0; i < numFile; i++)
    {
        arrTFIDFData[i] = malloc(sizeof(struct TFIDFData));
        arrTFIDFData[i]->fileName = arrIFData[i]->fileName;
        arrTFIDFData[i]->tree = g_tree_calc_TFIDF_metric(arrIFData[i], tree_unic_word, numFile);
    }

    // for (int i = 0; i < numFile; i++) {
    //     printf("\n%s %d\n", arrIFData[i]->fileName, arrIFData[i]->numWords);
    //     g_tree_print(arrIFData[i]->tree);

    //     free(arrIFData[i]->fileName);
    //     g_tree_destroy(arrIFData[i]->tree);
    // }
    // free(arrIFData);

    return arrTFIDFData;
}