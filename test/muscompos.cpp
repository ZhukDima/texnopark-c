#include "gtest/gtest.h"
#include <cstring>
#include <string>
#include <iostream>


extern "C" {
#include "muscompos.h"
}

#include <set>

struct MusCompos* pointToMusCompos(const char* name, int duration, int rhythm) {
  char* c_name = new char [strlen(name)+1];
  std::strcpy(c_name, name);
  MusCompos* ans = new MusCompos();
  ans->name = c_name;
  ans->duration = duration;
  ans->rhythm = rhythm;
  return ans;
}

const int size_in = 10;
const int count_test = 1000;

TEST(testy, ok) {
  struct MusCompos** in_arr = new struct MusCompos*[size_in];
  const char* allName[size_in] = {"Белые розы", 
  "Фаина-Фаина", "Влидимирский централ", "Костёр", 
  "Выпьем за любовь", "Императрица", "Милион алых роз", 
  "Пачка сигарет", "Группа крови", "Перемен"};

  int allDuration[size_in] = {240, 
  245, 250, 230, 
  220, 225, 235, 
  240, 235, 245};

  int allRhythm[size_in] = {100, 
  101, 99, 102, 
  103, 100, 102, 
  101, 101, 99};

  for (int i = 0; i < size_in; i++)
    in_arr[i] = pointToMusCompos(allName[i], allDuration[i], allRhythm[i]);

  struct MusCompos** out_arr;
  int all_size_out = 0;
  for (int i = 0; i < count_test; i++) {
    int size_out = randMusicArray(in_arr, 10, &out_arr);
    ASSERT_TRUE(size_out > 0 && size_out <= size_in);

    std::set<std::string> s;
    for (int i = 0; i < size_in; i++) s.insert(std::string(allName[i]));

    for (int j = 0; j < size_out; j++) {
      // соблюдается условие из задачи про "отличия"
      ASSERT_TRUE(abs(out_arr[0]->duration - out_arr[j]->duration) <= delta_duration);
      ASSERT_TRUE(abs(out_arr[0]->rhythm - out_arr[j]->rhythm) <= delta_rhythm);
      // все песни входят единожды (уникальные названия песен)
      ASSERT_TRUE(s.find(out_arr[j]->name) != s.end());
      s.erase(s.find(out_arr[j]->name));
    }

    all_size_out += size_out;
    free(out_arr);
  }
  // std::cout << 1.0 * all_size_out / count_test << std::endl; => при 1000: 1,701
  ASSERT_TRUE(all_size_out > count_test * 1);

  for (int i = 0; i < size_in; i++)
    free(in_arr[i]);
  free(in_arr);
}