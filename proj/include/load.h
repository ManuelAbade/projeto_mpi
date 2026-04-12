#ifndef LOAD_H
#define LOAD_H
#include "raylib.h"
#include "stdio.h"
#include "main.h"

extern Font actual_font;

typedef struct 
{
    char *path;
    Texture2D *name;
} LoadTextures;

typedef struct 
{
    char *path;
    Sound* name;
} LoadSounds;

typedef struct 
{
    char *path;
    Font *name;
} LoadFonts;

void TextureLoad(LoadTextures *tex_to_load[]);
void SoundLoad(LoadSounds *sound_to_load[]);
void SoundFont(LoadFonts *fonts_to_load[]);
void TexturesUnload(LoadTextures *tex_to_unload[]);
#endif