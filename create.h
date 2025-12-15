/**
 * @file create.h
 * @brief Interface for archive creation in the ctar application.
 *
 * This module contains the declaration of the functions to create 
 * tar archives from specified files.
 */

#ifndef CREATE_H
#define CREATE_H

#include <errno.h>

/**
  * @brief Create a tar archive from specified files.
  *
  * @param archive_file Name of the archive file to create.
  * @param files Array of file names to include in the archive.
  * @param file_count Number of files to include.
  * 
  * @return 0 on success, error code on failure.
  */
int create_archive(const char *archive_file, char **files, int file_count);

#endif
