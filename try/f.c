#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 1000
#define HEIGHT 600
#define SIZE 500

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;
int quit = 0;

void GenerateArray(int arr[SIZE]);
void Swap(int arr[SIZE], int i, int j);
void SelectionSort(int arr[SIZE]);
void PrintArray(int arr[SIZE]);
void draw(int arr[SIZE], int i, int j);

void setup() {
    window = SDL_CreateWindow("Selection Sort", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_UpdateWindowSurface(window);
}

int processEvent() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_WINDOWEVENT_CLOSE:
            if (window) {
                SDL_DestroyWindow(window);
                window = NULL;
                quit = 1;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                quit = 1;
                break;
            }
            break;
        case SDL_QUIT:
            quit = 1;
            break;
        }
    }
    return quit;
}

void GenerateArray(int arr[SIZE]) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = 1 + rand() % HEIGHT;
    }
}

void Swap(int arr[SIZE], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void SelectionSort(int arr[SIZE]) {
    int i, j, index;
    for (i = 0; i < SIZE - 1; i++) {
        index = i;
        for (j = i + 1; j < SIZE; j++) {
            if (arr[j] < arr[index]) {
                index = j;
            }
        }
        draw(arr, i, index);
        Swap(arr, i, index);
        SDL_Delay(5);
    }
    SDL_Rect rect;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    rect =(SDL_Rect) { (SIZE - 1) * (WIDTH / SIZE), HEIGHT - arr[SIZE - 1], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void PrintArray(int arr[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
}

void draw(int arr[SIZE], int i, int j) {
    SDL_Rect rect;

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    rect = (SDL_Rect) { j * WIDTH / SIZE, HEIGHT - arr[j], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    rect = (SDL_Rect) { i * WIDTH / SIZE, HEIGHT - arr[i], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    rect = (SDL_Rect){ j * WIDTH / SIZE, HEIGHT - arr[j], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    rect = (SDL_Rect){ j * WIDTH / SIZE, HEIGHT - arr[i], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    rect = (SDL_Rect){ i * WIDTH / SIZE, HEIGHT - arr[i], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    rect =(SDL_Rect) { i * WIDTH / SIZE, HEIGHT - arr[j], WIDTH / SIZE, HEIGHT };
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
    time_t start, end;
    int arr[SIZE];
    GenerateArray(arr);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    setup();

    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    for (int i = 0; i < SIZE; i++) {
        SDL_Rect rect = { i * WIDTH / SIZE, HEIGHT - arr[i], WIDTH / SIZE, HEIGHT };
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }

    time(&start);
    SelectionSort(arr);
    time(&end);

    double time_taken = difftime(end, start);
    printf("Array size: %d\n", SIZE);
    printf("Time taken by program is: %.5f sec\n", time_taken);

    while (!quit) {
        quit = processEvent();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
