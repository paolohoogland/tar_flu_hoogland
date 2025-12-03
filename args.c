/**
 * @file args.c
 * @brief Argument parsing for the ctar application.
 *
 * This module handles the parsing of command-line arguments using getopt_long.
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "args.h"

/**
 * @brief Print help message.
 * 
 * This function displays the usage information for the ctar application. 
 * The options include listing, extracting, and creating tar archives,
 * as well as additional flags for compressing, verbose, and help.
 */
static void print_help() {
    printf("Usage: ctar [OPTIONS]\n");
    printf("  -l, --list      ARCHIVE_FILE\n");
    printf("  -e, --extract   ARCHIVE_FILE\n");
    printf("  -c, --create    ARCHIVE_FILE\n");
    printf("  -d, --directory DIRECTORY\n");
    printf("  -z, --compress\n");
    printf("  -v, --verbose\n");
    printf("  -h, --help\n");
}

/**
  * @brief Parse command-line arguments.
  *
  * @param argc Number of arguments.
  * @param argv Array of argument strings.
  * @param options Structure where parsed options will be stored.
  * @return 0 on success, -1 on invalid arguments.
  */
int parse_arguments(int argc, char *argv[], options_t *options){
    optind = 1; // reset getopt's external index -> otherwise it misbehaves if called multiple times

    static struct option available_options[] = {
        {"list",     required_argument, 0, 'l'},
        {"extract",  required_argument, 0, 'e'},
        {"create",   required_argument, 0, 'c'}, 
        {"directory", required_argument, 0, 'd'},
        {"compress", no_argument,       0, 'z'}, 
        {"verbose",  no_argument,       0, 'v'},
        {"help",     no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "l:e:c:d:zvh", available_options, NULL)) != -1) { // z for compress, v for verbose, h for help
        switch(opt){
            case 'l': options->list = 1; options->archive_file = optarg; break;
            case 'e': options->extract = 1; options->archive_file = optarg; break;
            case 'c': options->create = 1; options->archive_file = optarg; break;
            case 'd': options->directory = optarg; break;
            case 'z': options->compress = 1; break;
            case 'v': options->verbose = 1; break;
            case 'h': print_help(); exit(0); break; // exit for no error
            case '?': // unknown option
            default: return -1;
        }
    }

    // getopt_long places the index of the next element of argv to be processed in optind
    if (options->create) {
        options->file_count = argc - optind; // optind is defined in #include <getopt.h>
        options->files = &argv[optind];
    }

    return 0;
}