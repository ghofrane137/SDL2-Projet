#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
int MOVE_SPEED = 2;
void drawbar(SDL_Renderer *Renderer, buttons button, TTF_Font *font, const char *buttonText, SDL_Color textColor) {
    SDL_Rect bar;

    bar = (SDL_Rect){0, 0, 1000, 50};
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
