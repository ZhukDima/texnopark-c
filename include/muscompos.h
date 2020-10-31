#ifndef _MUSCOMPOS_H_
#define _MUSCOMPOS_H_

struct MusCompos
{
  char* name;
  int duration;
  int rhythm;
};

#define delta_duration 10
#define delta_rhythm 2

int randMusicArray(struct MusCompos** in_musCompos, 
    int size_in, struct MusCompos*** out_musCompos);

#endif