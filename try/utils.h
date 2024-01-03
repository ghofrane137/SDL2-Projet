#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;


typedef struct buttons {
    SDL_Rect button;
} buttons;


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
