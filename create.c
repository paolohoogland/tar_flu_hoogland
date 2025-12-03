/**
 * @file create.c
 * @brief Implementation of archive creation for the ctar application.
 *
 * This module allows to create tar archives from specified files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#include "typedef.h"
#include "create.h"

 /**
  * @brief Write the POSIX header for a file into the archive.
  *
  * @param fd File descriptor of the archive.
  * @param filename Name of the file to add.
  * @param filesize Size of the file to add.
  */
static void write_header(int fd, const char *filename, long filesize) {
    posix_header_t header;
    memset(&header, 0, sizeof(posix_header_t)); // initialize header to zero

    // fill header fields with snprintf, for proper formatting and buffer safety
    snprintf(header.name, sizeof(header.name), "%s", filename); 
    snprintf(header.mode, sizeof(header.mode), "%07o", 0644);
    snprintf(header.uid, sizeof(header.uid), "%07o", getuid());
    snprintf(header.gid, sizeof(header.gid), "%07o", getgid());
    snprintf(header.size, sizeof(header.size), "%011lo", filesize);
    snprintf(header.mtime, sizeof(header.mtime), "%011lo", time(NULL));
    header.typeflag = '0';
    snprintf(header.magic, sizeof(header.magic), "ustar");
    snprintf(header.version, sizeof(header.version), "00");
    snprintf(header.uname, sizeof(header.uname), "%s", "user");
    snprintf(header.gname, sizeof(header.gname), "%s", "group");

    memset(header.chksum, ' ', sizeof(header.chksum)); // fill with spaces
    unsigned int chksum = 0;
    for (size_t i = 0; i < sizeof(posix_header_t); i++) {
        chksum += ((unsigned char*)&header)[i]; // sum all bytes
    }
    snprintf(header.chksum, sizeof(header.chksum), "%06o", chksum);

    write(fd, &header, sizeof(posix_header_t));
}

 /**
  * @brief Create a tar archive from specified files.
  *
  * @param archive_file Name of the archive file to create.
  * @param files Array of file names to include in the archive.
  * @param file_count Number of files to include.
  */
void create_archive(const char *archive_file, char **files, int file_count) {
    int archive_fd = open(archive_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (archive_fd < 0) {
        perror("Error opening archive file");
        return;
    }

    for(int i = 0; i < file_count; i++){
        const char *filename = files[i];
        int file_fd = open(filename, O_RDONLY);
        if (file_fd < 0) {
            perror("Error opening input file");
            continue; // skip this file and continue with the next
        }

        struct stat st;
        if (fstat(file_fd, &st) < 0) {
            perror("Error getting file size");
            close(file_fd);
            continue; // skip this file and continue with the next
        }

        write_header(archive_fd, filename, st.st_size);

        // write file content to archive
        char buffer[512];
        ssize_t bytes_read;
        while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) {
            write(archive_fd, buffer, bytes_read);
        }

        // pad to 512-byte boundary
        off_t padding = 512 - (st.st_size % 512);
        if (padding < 512) {
            memset(buffer, 0, padding);
            write(archive_fd, buffer, padding);
        }

        close(file_fd);
    }

    // write two 512-byte blocks of zeros to mark end of archive
    char end_block[512] = {0};
    write(archive_fd, end_block, sizeof(end_block));
    write(archive_fd, end_block, sizeof(end_block));
    close(archive_fd);
}