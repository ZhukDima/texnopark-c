#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>

#include "muscompos.h"

int randMusicArray(struct MusCompos** in_musCompos,
  int size_in, struct MusCompos*** out_musCompos) 
{
  // выбираем "случайную" область поиска
  int st = rand() % size_in;
  int mid_duration = in_musCompos[st]->duration 
    + rand() % delta_duration - delta_duration / 2;
  int mid_rhythm = in_musCompos[st]->rhythm 
    + rand() % delta_rhythm - delta_rhythm / 2;

  // считаем кол-во подходящих элементов
  int size_correct_ind = 0;
  for (int i = 0; i < size_in; i++) 
    if (2 * abs(in_musCompos[i]->duration - mid_duration) <= delta_duration 
    && 2 * abs(in_musCompos[i]->rhythm - mid_rhythm) <= delta_rhythm)
      size_correct_ind++;

  // записываем индексы подходящих элементов
  assert(size_correct_ind > 0);
  int* correct_ind = malloc(sizeof(int) * size_correct_ind);
  size_correct_ind = 0;
  for (int i = 0; i < size_in; i++) 
    if (2 * abs(in_musCompos[i]->duration - mid_duration) <= delta_duration 
    && 2 * abs(in_musCompos[i]->rhythm - mid_rhythm) <= delta_rhythm)
      correct_ind[size_correct_ind++] = i;

  // перемешивание индексы элементов
  for (int i = size_correct_ind - 1; i >= 0; i--) {
    int j = rand() % (i + 1);
    int buf = correct_ind[j];
    correct_ind[j] = correct_ind[i];
    correct_ind[i] = buf;
  }

  // создание "случайной" подборки
  int size_out = rand() % size_correct_ind + 1;
  *out_musCompos = malloc(sizeof(struct MusCompos*) * size_out);
  for (int i = 0; i < size_out; i++)
    (*out_musCompos)[i] = in_musCompos[correct_ind[i]];

  free(correct_ind);
  return size_out;
}