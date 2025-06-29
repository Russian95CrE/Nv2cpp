#pragma once

#include <GL/gl.h>
#include <SDL3/SDL.h>

SDL_Surface* loadSurfaceFromPNG (const char* filepath);
GLuint       createTextureFromSurface (SDL_Surface* surface);