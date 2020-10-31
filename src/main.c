#include <stdio.h>
#include <stdlib.h>

#include "muscompos.h"

// 10 Белые_розы 240 100 фАина-фаИна 245 101 Влидимирский_централ 250 99 Костёр 230 102 Выпьем_за_любовь 220 103 Императрица 225 10 Милион_алых_роз 235 102 Пачка_сигарет 240 101 Группа_крови 235 101 Перемен 245 99

int main() {
  printf(" > Это программа, предлагающую случайную подборку из заданного числа композиций,\n");
  printf("\tскорость (ритм) которых во всей подборке отличается не более чем на 2 уд./мин,\n");
  printf("\tа продолжительность — равна с точностью до 10 сек.\n");
  printf(" > Введите количество музыкальных композиций на вход:\n");
  printf(" < ");

  int size_in;
  if (scanf("%d", &size_in) != 1 || size_in <= 0) {
    printf(" > Что-то пошло не так.\n");
    return 1;
  }

  printf(" > Введите данные по композициям в формате:\n");
  printf("\t - название (без пробелов, не больше 100 символов);\n");
  printf("\t - продолжительность (в секундах);\n");
  printf("\t - ритм (удары в минуту);\n");

  struct MusCompos** in_arr = malloc(sizeof(struct MusCompos*) * size_in);
  for (int i = 0; i < size_in; i++) {
    printf(" > Композиция №%d\n", i + 1);
    printf(" < ");

    in_arr[i] = malloc(sizeof(struct MusCompos) * size_in);
    in_arr[i]->name = malloc(sizeof(char) * 101);
    if (scanf("%100s%d%d", in_arr[i]->name, &in_arr[i]->duration, &in_arr[i]->rhythm) != 3) {
      printf(" > Что-то пошло не так.\n");
      return 1;
    }
  }

  while (1)
  {
    struct MusCompos** out_arr;
    int size_out = randMusicArray(in_arr, size_in, &out_arr);
    printf(" > Новая случайная композиция:\n");
    for (int i = 0; i < size_out; i++) {
      printf("\t - %s (%d|%d)\n", out_arr[i]->name, out_arr[i]->duration, out_arr[i]->rhythm);
    }
    free(out_arr);
    printf(" > Повторить запуск? (Y/N)\n");
    printf(" < ");
    scanf("%*[^\n]");
    char c = '\0';
    scanf("%*[^yYnN]%c", &c);
    if (c == 'n' || c == 'N') break;
  }

  for (int i = 0; i < size_in; i++) {
    free(in_arr[i]->name);
    free(in_arr[i]);
  }
  free(in_arr);

  printf(" > Спасибо что пользовались =D\n");
  return 0;
}