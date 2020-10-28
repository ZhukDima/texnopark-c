#include "testy/TFMetric.h"
#include <assert.h>
#include <glib-2.0/glib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

gint CompareNames(gconstpointer name1, gconstpointer name2, gpointer data)
{
    return (strcmp(name1, name2));
}

gboolean g_tree_elem_print_sd(gpointer key, gpointer value, gpointer data)
{
    printf("Key: %15s\t Value: %3d\n",
           (const char *)key, *(int *)value);
    return FALSE;
}

void g_tree_print_sd(GTree *tree)
{
    g_tree_foreach(tree, g_tree_elem_print_sd, NULL);
}

int specialSymbol(char c)
{
    return !('a' <= c && c <= 'z');
}

void StrToWord(char *s)
{
    int l = strlen(s);
    for (int i = 0; i < l; i++)
        s[i] = tolower(s[i]);
    for (; l > 0 && specialSymbol(s[l - 1]); l--)
        s[l - 1] = '\0';
    int del = 0;
    for (; del < l && specialSymbol(s[del]); del++)
        ;
    if (del != 0)
    {
        char buf[100];
        strcpy(buf, s + del);
        strcpy(s, buf);
    }
}

struct TFData *findTFMetric(const char *fileName)
{
    FILE *file;
    assert((file = fopen(fileName, "r")) != NULL);
    struct TFData *ans = malloc(sizeof(struct TFData));
    ans->fileName = malloc(sizeof(char) * (strlen(fileName) + 1));
    strcpy(ans->fileName, fileName);
    ans->numWords = 0;
    ans->tree = g_tree_new_full(CompareNames, NULL, free, free);
    char *s = malloc(sizeof(char) * 100);
    while (fscanf(file, "%s", s) != EOF)
    {
        StrToWord(s);
        if (strlen(s) == 0)
            continue;
        int *p;
        if ((p = g_tree_lookup(ans->tree, s)) != NULL)
        {
            ans->numWords++;
            (*p)++;
        }
        else
        {
            int *a = malloc(sizeof(int));
            *a = 1;
            g_tree_insert(ans->tree, s, a);
        }
        s = malloc(sizeof(char) * 100);
    }
    free(s);
    fclose(file);
    return ans;
}