#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "typedef.h"
#include "list.h"

void list_archive(const char *archive)
{
    int fd = open(archive, O_RDONLY); // open the .tar file
    if (fd < 0) {
        perror("open");
        return;
    }

    posix_header_t header; 
    ssize_t bytes;

    while(1){
        bytes = read(fd, &header, sizeof(posix_header_t)); // 512 bytes

        if (bytes < 0) { perror("read"); break; }
        if (bytes == 0) break; // end of file
        if (header.name[0] == '\0') break;  // two consecutive zero blocks indicate the end of the archive

        // convert to octal 
        long size = strtol(header.size, NULL, 8);

        printf("%s (%ld bytes)\n", header.name, size);

        long skip = size;
        long padding = 512 - (size % 512);
        if (padding == 512) padding = 0;

        lseek(fd, skip + padding, SEEK_CUR); // skip file content and padding
    }

    close(fd);
}