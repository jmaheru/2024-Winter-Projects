#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16

void print_hex(const unsigned char *buffer, ssize_t size);
void print_ascii(const unsigned char *buffer, ssize_t size);

int main(int argc, char **argv) {
    int fd = STDIN_FILENO;
    if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            return 1;
        }
    } else if (argc > 2) {
        return 1;
    }

    unsigned char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    off_t offset = 0;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        printf("%08lx: ", (unsigned long) offset);
        print_hex(buffer, bytes_read);
        printf(" ");
        print_ascii(buffer, bytes_read);
        offset += bytes_read;
    }

    close(fd);

    return 0;
}

void print_hex(const unsigned char *buffer, ssize_t size) {
    for (ssize_t i = 0; i < size; i++) {
        printf("%02x", buffer[i]);
        if (i % 2 != 0)
            printf(" ");
    }

    for (ssize_t i = size; i < BUFFER_SIZE; i++) {
        printf("  ");
        if (i % 2 != 0)
            printf(" ");
    }
}

void print_ascii(const unsigned char *buffer, ssize_t size) {
    for (ssize_t i = 0; i < size; i++) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            printf("%c", buffer[i]);
        } else {
            printf(".");
        }
    }

    printf("\n");
}
