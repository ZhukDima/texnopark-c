#include "testy/TF-IDFMetric.h"
#include <assert.h>
#include <glib-2.0/glib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <math.h>

gboolean g_tree_elem_calc_unic_word(gpointer key, gpointer value, gpointer tree_unic_word)
{
    int *p;
    if ((p = g_tree_lookup((GTree *)tree_unic_word, key)) != NULL)
        (*p)++;
    else
    {
        char *copy_key = malloc(sizeof(char) * (strlen((char *)key) + 1));
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
    *new_data *= 100 * log10l((ld)((struct SpecialData *)data)->numFile / *(int *)g_tree_lookup(((struct SpecialData *)data)->tree_unic_word, key));
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

    for (int i = 0; i < numFile; i++)
    {
        // printf("\n%s %d\n", arrIFData[i]->fileName, arrIFData[i]->numWords);
        // g_tree_print(arrIFData[i]->tree);

        g_tree_destroy(arrIFData[i]->tree);
    }
    free(arrIFData);

    return arrTFIDFData;
}

gboolean g_tree_elem_topFiveTFIDFMetric(gpointer key, gpointer value, gpointer data)
{
    struct WordTFIDF *ans_i = (struct WordTFIDF *)data;
    if (*(ld*)value > ans_i->arrIFIDF[4])
    {
        free(ans_i->arrWords[4]);
        ans_i->arrWords[4] = malloc(sizeof(char) * (strlen((char *)key) + 1));
        strcpy(ans_i->arrWords[4], (char *)key);
        ans_i->arrIFIDF[4] = *(ld*)value;
        for (int i = 4; i > 0 && ans_i->arrIFIDF[i - 1] < ans_i->arrIFIDF[i]; i--)
        {
            ld buf_ld = ans_i->arrIFIDF[i - 1];
            ans_i->arrIFIDF[i - 1] = ans_i->arrIFIDF[i];
            ans_i->arrIFIDF[i] = buf_ld;
            char *buf_str = ans_i->arrWords[i - 1];
            ans_i->arrWords[i - 1] = ans_i->arrWords[i];
            ans_i->arrWords[i] = buf_str;
        }
    }
    return FALSE;
}

struct WordTFIDF **findTopFiveTFIDFMetric(const char *pathToDir)
{
    struct TFIDFData **arr = findTFIDFMetric(pathToDir);
    int size = 0;
    while (arr[size] != NULL)
        size++;

    struct WordTFIDF **ans = malloc(sizeof(struct WordTFIDF *) * (size + 1));
    for (int i = 0; i < size; i++)
    {
        ans[i] = malloc(sizeof(struct WordTFIDF));
        ans[i]->fileName = arr[i]->fileName;
        ans[i]->arrWords = malloc(sizeof(char *) * 5);
        for (int j = 0; j < 5; j++)
            ans[i]->arrWords[j] = malloc(sizeof(char));
        ans[i]->arrIFIDF = malloc(sizeof(ld) * 5);
        for (int j = 0; j < 5; j++)
            ans[i]->arrIFIDF[j] = 0;
        g_tree_foreach(arr[i]->tree, g_tree_elem_topFiveTFIDFMetric, ans[i]);

        g_tree_destroy(arr[i]->tree);
    }
    return ans;
}

void printTopFiveTFIDFMetric(const char *pathToDir) {
    struct WordTFIDF **arr = findTopFiveTFIDFMetric(pathToDir);
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