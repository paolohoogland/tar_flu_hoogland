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

#endif // TYPEDEF_H