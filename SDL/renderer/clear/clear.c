#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *Window = nullptr;
static SDL_Renderer *Renderer = nullptr;

const static int WindowWidth = 800;
const static int WindowHeight = 600;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {

  SDL_SetAppMetadata("Clear", "1.0", "com.mag.renderer-clear");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  /* Create the window */
  if (!SDL_CreateWindowAndRenderer("Clear renderer", WindowWidth, WindowHeight, 0, &Window,
                                   &Renderer)) {
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
  const double now = ((double)SDL_GetTicks()) / 1000.0;

  const auto red = (float)(0.5 + (0.5 * SDL_sin(now)));
  const auto green = (float)(0.5 + (0.5 * SDL_sin(now + SDL_PI_D * 2 / 3)));
  const auto blue = (float)(0.5 + (0.5 * SDL_sin(now + SDL_PI_D * 4 / 3)));

  SDL_SetRenderDrawColorFloat(Renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);

  SDL_RenderClear(Renderer);
  SDL_RenderPresent(Renderer);

  return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
