#ifndef _TF_IDFMETRIC_H_
#define _TF_IDFMETRIC_H_

#include <glib-2.0/glib.h>
#include "testy/TFMetric.h"
#include <stdio.h>

#define ld long double

struct TFIDFData
{
    char *fileName;
    GTree *tree;
};

gboolean g_tree_elem_calc_unic_word(gpointer key, gpointer value, gpointer tree_unic_word);

GTree *g_tree_calc_unic_word(struct TFData **arrIFData, int numFile);

gint CompareLD(gconstpointer name1, gconstpointer name2, gpointer data);

gboolean g_tree_elem_calc_TFIDF_metric(gpointer key, gpointer value, gpointer data);

GTree *g_tree_calc_TFIDF_metric(struct TFData *tf_data, GTree *tree_unic_word, int numFile);

struct TFIDFData **findTFIDFMetric(const char *pathToDir);

struct WordTFIDF
{
    char *fileName;
    char **arrWords;
    ld *arrIFIDF;
};

struct WordTFIDF **findTopFiveTFIDFMetric(const char *pathToDir);

void printTopFiveTFIDFMetric(const char *pathToDir);

#endif