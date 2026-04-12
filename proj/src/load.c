#include "../include/load.h"


void TextureLoad(LoadTextures *tex_to_load[])
{
    int success_count = 0;
    int total_count = 0;
    for (int i = 0; tex_to_load[i] != NULL; i++)
    {
        total_count++;
        if (tex_to_load[i]->path == NULL || tex_to_load[i]->name == NULL)
        {
            printf("\nError: %d has a NULL pointer \n",i);
            continue;
        }
        
        Image image = LoadImage(tex_to_load[i]->path);
         if (image.data == NULL) {
            printf("\nError: Can't load '%s'\n", tex_to_load[i]->path);
            continue;
        }

        
        *tex_to_load[i]->name = LoadTextureFromImage(image);
        UnloadImage(image);
        
        if (tex_to_load[i]->name->id != 0) {
            success_count++;
            printf("\n%s Loaded succesfully\n", tex_to_load[i]->path);
        }
    }
    printf("\nLoaded %d textures of %d \n", success_count, total_count);
    fflush(stdout);
}

void SoundLoad(LoadSounds *sound_to_load[])
{
    int success_count = 0;
    int total_count = 0;
    for (int i = 0; sound_to_load[i] != NULL; i++)
    {
        total_count++;
        if (sound_to_load[i]->path == NULL || sound_to_load[i]->name == NULL)
        {
            printf("Error: Tem %d has a NULL pointer \n",i);
            continue;
        }
        
        *sound_to_load[i]->name = LoadSound(sound_to_load[i]->path);

         if (sound_to_load[i]->name->frameCount == 0) {
            printf("Error: Can't load '%s'\n", sound_to_load[i]->path);
            continue;
        }

        if (sound_to_load[i]->name->frameCount != 0) {
            success_count++;
            printf("%s Loaded succesfully \n", sound_to_load[i]->path);
        }
    }
    printf("Loaded %d sounds of %d \n", success_count, total_count);
}
void SoundFont(LoadFonts *fonts_to_load[])
{
    int success_count = 0;
    int total_count = 0;
    for (int i = 0; fonts_to_load[i] != NULL; i++)
    {
        total_count++;
        if (fonts_to_load[i]->path == NULL || fonts_to_load[i]->name == NULL)
        {
            printf("\nError: Tem %d has a NULL pointer \n",i);
            continue;
        }
        
        *fonts_to_load[i]->name = LoadFont(fonts_to_load[i]->path);

         if (fonts_to_load[i]->name->baseSize == 0) {
            printf("\nError: Can't load '%s'\n", fonts_to_load[i]->path);
            continue;
        }

        if (fonts_to_load[i]->name->baseSize != 0) {
            success_count++;
            printf("\n%s Loaded succesfully \n", fonts_to_load[i]->path);
        }
    }
    printf("\nLoaded %d fonts of %d \n", success_count, total_count);
    fflush(stdout);
}

void TexturesUnload(LoadTextures *tex_to_unload[])
{
    int unload_count = 0;
    
    for (int i = 0; tex_to_unload[i] != NULL; i++)
    {
        if (tex_to_unload[i]->path == NULL || tex_to_unload[i]->name == NULL)
        {
            printf("\nError: %d has a NULL pointer\n", i);
            continue;
        }
        
        if (tex_to_unload[i]->name->id != 0)
        {
            UnloadTexture(*tex_to_unload[i]->name);
            unload_count++;
            printf("\nUnloaded texture: %s\n", tex_to_unload[i]->path);
        }
        else
        {
            printf("\nWarning: Texture %s already unloaded or invalid\n", tex_to_unload[i]->path);
        }
        fflush(stdout);
    }
    
    printf("\nTextures Unloaded: %d textures successfully unloaded\n", unload_count);
    fflush(stdout);
}