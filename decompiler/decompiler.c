#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input.exe>\n", argv[0]);
        return 1;
    }
    const char *input_file = argv[1];

    int fd_input = open(input_file, O_RDONLY);
    if (fd_input < 0) {
        perror("Cannot open input file");
        return 1;
    }

    off_t szFile = lseek(fd_input, 0, SEEK_END);
    if (szFile < 0) {
        perror("lseek failed");
        close(fd_input);
        return 1;
    }

    // Ler os últimos 8 bytes
    uint8_t dataEnd[8];
    if (lseek(fd_input, szFile - 8, SEEK_SET) < 0) {
        perror("lseek failed");
        close(fd_input);
        return 1;
    }
    if (read(fd_input, dataEnd, 8) != 8) {
        perror("read failed");
        close(fd_input);
        return 1;
    }

    uint32_t signature = *(uint32_t*)dataEnd;
    uint32_t swf_size = *(uint32_t*)(dataEnd + 4);

    if (signature != 0xFA123456) {
        printf("This doesn't seem to be a projector bundle.\n");
        close(fd_input);
        return 1;
    }

    // Alocar buffer para o swf
    uint8_t *buffer = malloc(swf_size);
    if (!buffer) {
        perror("malloc failed");
        close(fd_input);
        return 1;
    }

    // Ler o swf que fica antes dos 8 bytes do final
    if (lseek(fd_input, szFile - 8 - swf_size, SEEK_SET) < 0) {
        perror("lseek failed");
        free(buffer);
        close(fd_input);
        return 1;
    }
    if (read(fd_input, buffer, swf_size) != swf_size) {
        perror("read failed");
        free(buffer);
        close(fd_input);
        return 1;
    }
    close(fd_input);

    // Criar o arquivo .swf
    int fd_output = open("dumped.swf", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_output < 0) {
        perror("Cannot create output file");
        free(buffer);
        return 1;
    }

    if (write(fd_output, buffer, swf_size) != swf_size) {
        perror("write failed");
        free(buffer);
        close(fd_output);
        return 1;
    }

    free(buffer);
    close(fd_output);

    printf("Done, check your shiny new dumped.swf! =)\n");
    return 0;
}
