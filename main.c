/**
 * @file main.c
 * @brief Main entry point for the ctar application.
 *
 * This module handles the main logic for the ctar application.
 * It parses command-line arguments and invokes the appropriate
 * functions for listing, extracting, or creating tar archives.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "typedef.h"
#include "args.h"
#include "list.h"
#include "extract.h"
#include "create.h"

/**
 * @brief Main entry point for the ctar application.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * 
 * @return Exit status code, 0 on success, error code on failure.
 */
int main(int argc, char *argv[])
{
    options_t options = {0};

    /* ERROR CATCHING */

    if (parse_arguments(argc, argv, &options) != 0) {
        fprintf(stderr, "Error: invalid arguments.\n");
        return EINVAL;
    }

    // conflicting modes
    if ((options.list + options.extract + options.create) > 1) {
        fprintf(stderr, "Error: choose only ONE mode (-l, -e, or -c)\n");
        return EINVAL;
    }

    // if no mode selected
    if (!options.list && !options.extract && !options.create) {
        fprintf(stderr, "Error: no mode selected (use -l, -e, or -c)\n");
        return EINVAL;
    }

    if (!options.archive_file) {
        fprintf(stderr, "Error: missing archive file\n");
        return EINVAL;
    }

    // create mode should have at least one file
    if (options.create && options.file_count == 0) {
        fprintf(stderr, "Error: no input files for create mode\n");
        return EINVAL;
    }

    for (int i = 0; i < options.file_count; i++) {
        if (strlen(options.files[i]) > 100) { // POSIX tar max filename length is 100 chars
            fprintf(stderr, "Error: file name too long: %s (max 100 characters)\n", options.files[i]);
            return ENAMETOOLONG;
        }
    }

    /* END OF ERROR CATCHING */

    if (options.directory && (options.create || options.extract))
    {
        if (chdir(options.directory) != 0) {
            perror("chdir");
            return errno;
        }
    }

    if (options.verbose) {
        printf("***** Verbose mode ON *****\n");
        printf("Mode:\n");
        if (options.list) printf("  LIST\n");
        if (options.extract) printf("  EXTRACT\n");
        if (options.create) printf("  CREATE\n");

        printf("Archive: %s\n", options.archive_file);

        if (options.directory) {
            printf("Directory: %s\n", options.directory);
        } else {
            printf("Directory: (current)\n");
        }

        if (options.create) {
            printf("Files to include (%d):\n", options.file_count);
            for (int i = 0; i < options.file_count; i++) {
                printf("  %s\n", options.files[i]);
            }
        }

        printf("****************************\n\n");
    }

    if (options.list) {
        int result = list_archive(options.archive_file);
        if (result != 0) {
            return result;
        }
    }

    if (options.extract) {
        int result = extract_archive(options.archive_file);
        if (result != 0) {
            return result;
        }
    }
    
    if (options.create) {
        int result = create_archive(options.archive_file, options.files, options.file_count);
        if (result != 0) {
            return result;
        }
    }

    return 0;
}