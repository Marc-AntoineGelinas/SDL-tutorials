#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;
static SDL_FPoint points[500];

const static int windowHeight = 480;
const static int windowLength = 640;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Example Renderer primitives", "1.0", "potato");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("Exmaple primitives", windowLength, windowHeight, 0, &window,
                                     &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
    SDL_FRect rect;
    int index;

    for (index = 0; index < SDL_arraysize(points); index++) {
        points[index].x = (SDL_randf() * 440.0F) + 100.0F;
        points[index].y = (SDL_randf() * 280.0F) + 100.0F;
    }

    SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE); // Dark grey
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // blue
    rect.x = rect.y = 100;
    rect.w = 440;
    rect.h = 280;
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // red
    SDL_RenderPoints(renderer, points, SDL_arraysize(points));

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); // green
    rect.x += 30;
    rect.y += 30;
    rect.w -= 60;
    rect.h -= 60;
    SDL_RenderRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); // yellow
    SDL_RenderLine(renderer, 0, 0, windowLength, windowHeight);
    SDL_RenderLine(renderer, 0, windowHeight, windowLength, 0);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
