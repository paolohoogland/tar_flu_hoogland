/**
 * @file extract.h
 * @brief Header file for extract.c module.
 *
 * This module provides the declaration of functions to extract files and directories
 * from a tar archive based on the POSIX USTAR format.
 */

#ifndef EXTRACT_H
#define EXTRACT_H

#include <errno.h>

/**
 * @brief Extract files from a tar archive.
 *
 * @param archive_file Path to the tar archive file.
 * 
 * @return 0 on success, error code on failure.
 */
int extract_archive(const char *archive_file);

#endif
