#include <stdio.h>
#include <stdlib.h>

#include "typedef.h"
#include "args.h"
#include "list.h"
#include "extract.h"

int main(int argc, char *argv[])
{
    options_t options = {0};

    if (parse_arguments(argc, argv, &options) != 0) {
        fprintf(stderr, "Error: invalid arguments.\n");
        return 1;
    }

    // conflicting modes
    if ((options.list + options.extract + options.create) > 1) {
        fprintf(stderr, "Error: choose only ONE mode (-l, -e, or -c)\n");
        return 1;
    }

    // if no mode selected
    if (!options.list && !options.extract && !options.create) {
        fprintf(stderr, "Error: no mode selected (use -l, -e, or -c)\n");
        return 1;
    }

    if (options.verbose) {
        printf("***** Verbose mode ON *****\n");
        printf("Mode:\n");
        if (options.list) printf("  LIST\n");
        if (options.extract) printf("  EXTRACT\n");
        if (options.create) printf("  CREATE\n");

        printf("Archive: %s\n", options.archive_file);

        if (options.create) {
            printf("Files to include (%d):\n", options.file_count);
            for (int i = 0; i < options.file_count; i++) {
                printf("  %s\n", options.files[i]);
            }
        }

        printf("****************************\n\n");
    }

    if (options.list) {
        // printf("List archive: %s\n", options.archive_file);
        list_archive(options.archive_file);
    }

    if (options.extract) {
        // printf("Extract archive: %s\n", options.archive_file);
        extract_archive(options.archive_file);
    }
    if (options.create) {
        printf("Create archive: %s\n", options.archive_file);
        printf("Files to include:\n");
        for (int i = 0; i < options.file_count; i++) {
            printf("  %s\n", options.files[i]);
        }
        // create_archive(options.archive_file, options.files, options.file_count); <-- later
    }

    return 0;
}