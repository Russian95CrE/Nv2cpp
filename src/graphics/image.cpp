#define STB_IMAGE_IMPLEMENTATION
#include "GL/gl.h"
#include "stb_image.h"
#include <SDL3/SDL.h>
#include <cstring>

SDL_Surface* loadSurfaceFromPNG (const char* filepath) {
    int            width, height, channels;
    unsigned char* data = stbi_load(filepath, &width, &height, &channels, 4);
    if (!data) {
        printf(
            "Failed to load image %s: %s\n", filepath, stbi_failure_reason());
        return nullptr;
    }

    SDL_Surface* surface =
        SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        printf("SDL_CreateSurface failed: %s\n", SDL_GetError());
        stbi_image_free(data);
        return nullptr;
    }

    std::memcpy(surface->pixels, data, static_cast<size_t>(width) * height * 4);
    stbi_image_free(data);

    return surface;
}

GLuint createTextureFromSurface (SDL_Surface* surface) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 surface->w,
                 surface->h,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 surface->pixels);
    return textureID;
}