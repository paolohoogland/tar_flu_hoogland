/**
 * @file typedef.h
 * @brief Type definitions for the ctar application.
 * 
 * This module defines the data structures being used to represent
 * command-line options and tar file headers.
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <errno.h>

/**
 * @brief Structure to hold command-line options.
 * 
 * This structure captures the flags and parameters
 * specified by the user when invoking the ctar application.
 */
typedef struct {
    int list;
    int extract;
    int create;
    int verbose;
    int compress;

    char *archive_file;
    char *directory;

    char **files; // list of files to process
    int file_count; // number of files
} options_t;
 
/**
 * @brief POSIX tar file header structure.
 * 
 * This structure represents the header block of a tar file,
 * containing metadata about each file stored in the archive.
 * The structure is defined according to the POSIX 1003.1-1988
 * standard, also known as the USTAR format.
 * @see https://www.gnu.org/software/tar/manual/html_node/Standard.html
 */
typedef struct { // header block for tar files, contains metadata about each file
    char name[100]; // file name
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12]; // modification time
    char chksum[8];
    char typeflag;
    char linkname[100];
    char magic[6];
    char version[2];
    char uname[32]; // user name
    char gname[32]; // group name
    char devmajor[8];
    char devminor[8];
    char prefix[155];
    char padding[12]; // to reach 512 bytes : 512 - 500 = 12
} posix_header_t; // posix is the standard for tar files (POSIX 1003.1-1988 — called USTAR format - Unix Standard TAR)

#endif // TYPEDEF_H