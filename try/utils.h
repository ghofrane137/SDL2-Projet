#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
int MOVE_SPEED = 2;

typedef struct buttons {
    SDL_Rect button;
} buttons;

Uint32 startTime;

void startTimer() {
    startTime = SDL_GetTicks();
}

Uint32 getElapsedTime() {
    return SDL_GetTicks() - startTime;
}

int timeHasPassed(Uint32 milliseconds) {
    return getElapsedTime() >= milliseconds;
}

void moveRectangle(int *x1, int *x2, int target1, int target2) {
    if (*x1 != target1) {
        if (*x1 < target1) {
            *x1 += MOVE_SPEED;
        } else {
            *x1 -= MOVE_SPEED;
        }
    }

    if (*x2 != target2) {
        if (*x2 < target2) {
            *x2 += MOVE_SPEED;
        } else {
            *x2 -= MOVE_SPEED;
        }
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

void ordreRect(SDL_Renderer *Renderer, SDL_Rect rectangles[], int tab[], int n, TTF_Font *font) {
    startTimer();
    for (int i = 0; i < (n - 1); i++) {
        SDL_Color rectColorI = {6, 127, 6, 0};
        drawone(Renderer, &rectangles[i], tab[i], rectColorI, font);
        SDL_RenderPresent(Renderer);
        int minIndex = i;
        Uint32 lastUpdateTime = SDL_GetTicks();
        while (SDL_GetTicks() - lastUpdateTime < 300) {
            SDL_PumpEvents();
        }
        startTimer();
        for (int j = i + 1; j < n; j++) {
            SDL_Color rectColorI = {6, 127, 6, 0};
            drawone(Renderer, &rectangles[i], tab[i], rectColorI, font);
            SDL_Color rectColorJ = {173, 218, 228, 0};
            SDL_Color rectColorMin = {250, 50, 50, 0};
            drawRectangles(Renderer, rectangles, tab, n, font);
            drawone(Renderer, &rectangles[j], tab[j], rectColorJ, font);
            SDL_RenderPresent(Renderer);
            Uint32 elapsedTime = SDL_GetTicks() - lastUpdateTime;
            if (elapsedTime < 200) {
                SDL_Delay(200 - elapsedTime);
            }
            startTimer();
            if (tab[j] < tab[minIndex]) {
                minIndex = j;
                drawone(Renderer, &rectangles[minIndex], tab[minIndex], rectColorMin, font);
                SDL_RenderPresent(Renderer);
                SDL_Delay(200);
                startTimer();
            }
            lastUpdateTime = SDL_GetTicks();
        }

        if (minIndex != i) {
            int tmp = tab[i];
            tab[i] = tab[minIndex];
            tab[minIndex] = tmp;
            SDL_Rect temp = rectangles[i];
            rectangles[i] = rectangles[minIndex];
            rectangles[minIndex] = temp;
            int distance = abs(rectangles[minIndex].x - rectangles[i].x);
            int steps = distance / MOVE_SPEED;
            int x1 = rectangles[i].x;
            int x2 = rectangles[minIndex].x;
            int target1 = rectangles[minIndex].x;
            int target2 = rectangles[i].x;
            for (int step = 0; step < steps; step++) {
                moveRectangle(&x1, &x2, target1, target2);
                SDL_SetRenderDrawColor(Renderer, 220, 220, 220, 220);
                SDL_RenderClear(Renderer);
                rectangles[i].x = x1;
                rectangles[minIndex].x = x2;
                drawRectangles(Renderer, rectangles, tab, n, font);
                SDL_RenderPresent(Renderer);
                Uint32 elapsedTime = SDL_GetTicks() - lastUpdateTime;
                if (elapsedTime < 10) {
                    SDL_Delay(10 - elapsedTime);
                }
                startTimer();
                lastUpdateTime = SDL_GetTicks();
            }
        }
    }
}



void Remove(SDL_Renderer *Renderer, SDL_Rect rectangles[], int tab[], int *n, TTF_Font *font) {
    int a;
    printf("Enter the value to remove: ");
    scanf("%d", &a);

    int indexToRemove = -1;

    for (int i = 0; i < *n; i++) {
        if (tab[i] == a) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove != -1) {
        (*n)--;
        for (int i = indexToRemove; i < *n; i++) {
            tab[i] = tab[i + 1];
            rectangles[i] = rectangles[i + 1];
        }
        int j = 300;
        for (int i = 0; i < *n; i++) {
            rectangles[i] = (SDL_Rect){j, 1000 - 350 - tab[i] * 50, 50, tab[i] * 50};
                         j = j + 70;
        }
        drawRectangles(Renderer, rectangles, tab, *n, font);
        SDL_RenderPresent(Renderer);
    }
}


void close(TTF_Font *font, SDL_Renderer *Renderer, SDL_Window *window){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
