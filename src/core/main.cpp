#include "global.h"
#include "graphics/graphics.h"
#include "logsystem/log.h"
#include <GL/gl.h>
#include <SDL3/SDL.h>
#include <cstdio>
#include <cstring>

int main (int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_Window* window =
        SDL_CreateWindow(screen_title, 800, 600, SDL_WINDOW_OPENGL);
    if (!window) {
        panic("SDL_CreateWindow failed", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface* icon = loadSurfaceFromPNG("resources/images/icon.png");
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_DestroySurface(icon);
    } else {
        printf("Failed to load icon.png\n");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        panic("SDL_GL_CreateContext failed", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int winW, winH;
    SDL_GetWindowSize(window, &winW, &winH);
    float windowAspect = (float) winH / (float) winW;

    SDL_Surface* logoSurf = loadSurfaceFromPNG("resources/images/logo.png");
    GLuint       logoTex  = 0;
    int          logoW = 0, logoH = 0;
    if (logoSurf) {
        logoW   = logoSurf->w;
        logoH   = logoSurf->h;
        logoTex = createTextureFromSurface(logoSurf);
        SDL_DestroySurface(logoSurf);
    } else {
        printf("Failed to load logo.png\n");
    }

    bool      running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        glClearColorHex("#CACAD0");
        glClear(GL_COLOR_BUFFER_BIT);

        if (logoTex) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, logoTex);

            float aspect = (float) logoW / (float) logoH * windowAspect;
            float hnorm  = 0.3f;
            float wnorm  = hnorm * aspect;
            float margin = 0.08f;

            float x1 = 1.0f - margin;
            float x0 = x1 - wnorm;
            float y0 = 1.0f - margin;
            float y1 = y0 - hnorm;

            glColor3f(1, 1, 1);
            glBegin(GL_QUADS);
            glTexCoord2f(0, 1);
            glVertex2f(x0, y1);
            glTexCoord2f(1, 1);
            glVertex2f(x1, y1);
            glTexCoord2f(1, 0);
            glVertex2f(x1, y0);
            glTexCoord2f(0, 0);
            glVertex2f(x0, y0);
            glEnd();

            glDisable(GL_TEXTURE_2D);
        }

        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    if (logoTex)
        glDeleteTextures(1, &logoTex);
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
