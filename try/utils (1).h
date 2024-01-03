#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;


typedef struct buttons {
    SDL_Rect button;
} buttons;
void drawone(SDL_Renderer *Renderer, SDL_Rect *rectangles, int tab, SDL_Color rectColor, TTF_Font *font) {
    SDL_SetRenderDrawColor(Renderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);
    SDL_RenderFillRect(Renderer, rectangles);
    char text[10];
    sprintf(text, "%d", tab);
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_Rect textRect = {rectangles->x, rectangles->y, surface->w, surface->h};
    SDL_RenderCopy(Renderer, texture, NULL, &textRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void drawRectangles(SDL_Renderer *Renderer, SDL_Rect rectangles[], int tab[], int n, TTF_Font *font) {
    for (int i = 0; i < n; i++) {
        SDL_Color rectColor = {173, 218, 228, 0};
        drawone(Renderer, &rectangles[i], tab[i], rectColor, font);
    }
}

void drawbar(SDL_Renderer *Renderer, buttons button, TTF_Font *font, const char *buttonText, SDL_Color textColor) {
    SDL_Rect bar;

    bar = (SDL_Rect){0, 0, 0, 0};
    SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(Renderer, &bar);
    SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(Renderer, &button.button);
    SDL_Surface *buttonSurface = TTF_RenderText_Solid(font, buttonText, textColor);
    SDL_Texture *buttonTexture = SDL_CreateTextureFromSurface(Renderer, buttonSurface);

    SDL_Rect buttonTextRect = {
        button.button.x + button.button.w / 4,
        button.button.y + button.button.h / 4,
        buttonSurface->w,
        buttonSurface->h};

    SDL_RenderCopy(Renderer, buttonTexture, NULL, &buttonTextRect);

    SDL_FreeSurface(buttonSurface);
    SDL_DestroyTexture(buttonTexture);
}

void drawButton(SDL_Renderer *Renderer, buttons button, TTF_Font *font, const char *buttonText, SDL_Color textColor) {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(Renderer, &button.button);

    SDL_Surface *buttonSurface = TTF_RenderText_Solid(font, buttonText, textColor);
    SDL_Texture *buttonTexture = SDL_CreateTextureFromSurface(Renderer, buttonSurface);

    SDL_Rect buttonTextRect = {
        button.button.x + button.button.w / 4,
        button.button.y + button.button.h / 4,
        buttonSurface->w,
        buttonSurface->h};

    SDL_RenderCopy(Renderer, buttonTexture, NULL, &buttonTextRect);

    SDL_FreeSurface(buttonSurface);
    SDL_DestroyTexture(buttonTexture);
}



void close(TTF_Font *font, SDL_Renderer *Renderer, SDL_Window *window){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
