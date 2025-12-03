/**
 * @file extract.c
 * @brief Extract files from a tar archive.
 *
 * This module provides functionality to extract files and directories 
 * from a tar archive based on the POSIX USTAR format.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "typedef.h"
#include "extract.h"

/**
 * @brief Extract files from a tar archive.
 *
 * @param archive_file Path to the tar archive file.
 */
void extract_archive(const char *archive_file)
{
    int fd = open(archive_file, O_RDONLY);
    if (fd < 0)
    {
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

        // directory : create directory with header.name
        if (header.typeflag == '5') {   // directory
            mkdir(header.name, 0755);
            continue;
        }

        // file : create file with header.name
        int out = open(header.name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out < 0) {
            perror("open output");
            break;
        }

        // read file content from archive and write to created file
        long remaining_bytes = size;
        char buffer[512];

        while (remaining_bytes > 0) {
            ssize_t chunk = (remaining_bytes > 512 ? 512 : remaining_bytes); // 512 byte chunk

            bytes = read(fd, buffer, chunk);
            if (bytes <= 0) { perror("read file content"); break; }

            write(out, buffer, bytes);
            remaining_bytes -= bytes;
        }
        
        close(out);

        // skip padding : align to 512 bytes
        long padding = size % 512;
        if (padding != 0) {
            long skip = 512 - padding;
            lseek(fd, skip, SEEK_CUR);
        }
    }

    close(fd);
}
