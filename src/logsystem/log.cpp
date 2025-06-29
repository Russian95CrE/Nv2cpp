#include "log.h"
#include <cstdio>
#include <cstdlib>

int total_messages = 0;

void error (const char* message, const char* log) {
    if (log) {
        fprintf(stderr, "[ERROR] %s: %s\n", message, log);
    } else {
        fprintf(stderr, "[ERROR] %s\n", message);
    }
    total_messages++;
}

void debug (const char* message, const char* log) {
    if (log) {
        fprintf(stderr, "[DEBUG] %s: %s\n", message, log);
    } else {
        fprintf(stderr, "[DEBUG] %s\n", message);
    }
    total_messages++;
}

void info (const char* message, const char* log) {
    if (log) {
        fprintf(stderr, "[INFO] %s: %s\n", message, log);
    } else {
        fprintf(stderr, "[INFO] %s\n", message);
    }
    total_messages++;
}

void okay (const char* message, const char* log) {
    if (log) {
        fprintf(stderr, "[OK] %s: %s\n", message, log);
    } else {
        fprintf(stderr, "[OK] %s\n", message);
    }
    total_messages++;
}

void warn (const char* message, const char* log) {
    if (log) {
        fprintf(stderr, "[WARN] %s: %s\n", message, log);
    } else {
        fprintf(stderr, "[WARN] %s\n", message);
    }
    total_messages++;
}

void panic (const char* message, const char* log) {
    if (log) {
        fprintf(stderr, "[PANIC] %s: %s\n", message, log);
    } else {
        fprintf(stderr, "[PANIC] %s\n", message);
    }
    total_messages++;
    exit(EXIT_FAILURE);
}