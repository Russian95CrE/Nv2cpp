#include "logsystem/log.h"
#include <GL/gl.h>
#include <sstream>
#include <string>

void glClearColorHex (const std::string& hex) {
    std::string cleanHex = (hex[0] == '#') ? hex.substr(1) : hex;

    if (cleanHex.length() != 6) {
        fprintf(stderr, "Invalid HEX color: %s\n", hex.c_str());
        return;
    }

    unsigned int      color = 0;
    std::stringstream ss;
    ss << std::hex << cleanHex;
    ss >> color;

    float r = ((color >> 16) & 0xFF) / 255.0f;
    float g = ((color >> 8) & 0xFF) / 255.0f;
    float b = (color & 0xFF) / 255.0f;

    glClearColor(r, g, b, 1.0f);
}