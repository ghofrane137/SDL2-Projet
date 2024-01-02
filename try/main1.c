#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

typedef struct buttons {
    SDL_Rect button;
} buttons;

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

    buttons button[4];
    button[3].button = (SDL_Rect){0, 0, 200, 50};
    button[0].button = (SDL_Rect){200, 0, 200, 50};
    button[1].button = (SDL_Rect){400, 0, 200, 50};
    button[2].button = (SDL_Rect){600, 0, 200, 50};

    SDL_Rect rectangles[n];

    int delayTime = 50;
    bool run = true;

    while (run) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (ev.button.button == SDL_BUTTON_LEFT) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);

                        if (mouseX >= button[0].button.x && mouseX < button[0].button.x + button[0].button.w &&
                            mouseY >= button[0].button.y && mouseY < button[0].button.y + button[0].button.h) {
                            printf("Button 1 clicked!\n");

                        } else if (mouseX >= button[1].button.x && mouseX < button[1].button.x + button[1].button.w &&
                                   mouseY >= button[1].button.y && mouseY < button[1].button.y + button[1].button.h) {
                            printf("Button 2 clicked!\n");
                            run = false;
                        } else if (mouseX >= button[2].button.x && mouseX < button[2].button.x + button[2].button.w &&
                                   mouseY >= button[2].button.y && mouseY < button[2].button.y + button[2].button.h) {
                            printf("Button 3 clicked!\n");


                        } else if (mouseX >= button[3].button.x && mouseX < button[3].button.x + button[3].button.w &&
                                   mouseY >= button[3].button.y && mouseY < button[3].button.y + button[3].button.h) {
                            printf("Button 4 clicked!\n");


                    }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(Renderer, 220, 220, 220, 220);
        SDL_RenderClear(Renderer);


        SDL_Color textColor = {255, 255, 255, 255};


        SDL_RenderPresent(Renderer);
    }
    close(font, Renderer, window);
    return 0;
    }
void close(TTF_Font *font, SDL_Renderer *Renderer, SDL_Window *window){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
