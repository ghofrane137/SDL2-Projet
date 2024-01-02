#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void drawRectangles(SDL_Renderer *Renderer, SDL_Rect rectangles[], int tab[], int n, TTF_Font *font) {
    for (int i = 0; i < n; i++) {
        SDL_Color rectColor = {173, 218, 228, 0};
        drawone(Renderer, &rectangles[i], tab[i], rectColor, font);
    }
}
