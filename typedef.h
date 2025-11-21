#ifndef TYPEDEF_H
#define TYPEDEF_H

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