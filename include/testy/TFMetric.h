#ifndef _TFMETRIC_H_
#define _TFMETRIC_H_

#include <glib-2.0/glib.h>
#include <stdio.h>

struct TFData {
    char* fileName;
    int numWords;
    GTree *tree;
};

gint CompareNames(gconstpointer name1, gconstpointer name2, gpointer data);

gboolean g_tree_elem_print_sd(gpointer key, gpointer value, gpointer data);

void g_tree_print_sd(GTree *tree);

struct TFData *findTFMetric(const char *fileName);

#endif