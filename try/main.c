#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;


int main(int argc, char *argv[]) {
    int n = 5;
    int tab[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &tab[i]);
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *Renderer = SDL_CreateRenderer(window, -1, 0);

    if (window == NULL || Renderer == NULL) {
        printf("SDL CreateWindow or CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        printf("SDL_ttf Init Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    if (font == NULL) {
        printf("Font could not be loaded! TTF_Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

void close(TTF_Font *font, SDL_Renderer *Renderer, SDL_Window *window){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
