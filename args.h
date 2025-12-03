/**
 * @file args.h
 * @brief Argument parsing for the ctar application.
 * 
 * This module handles the declaration of the functions for the parsing of command-line arguments using getopt_long.
 */
#ifndef ARGS_H
#define ARGS_H

#include "typedef.h" // contains options_t def

/**
 * @brief Parse command-line arguments.
 *
 * @param argc Number of arguments.
 * @param argv Array of argument strings.
 * @param options Structure where parsed options will be stored.
 * @return 0 on success, -1 on invalid arguments.
 */
int parse_arguments(int argc, char *argv[], options_t *options);

#endif
