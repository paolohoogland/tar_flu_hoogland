/**
 * @file list.h
 * @brief Header file for listing contents of a tar archive.
 *
 * This module provides the function declarations for listing the contents
 * of a tar archive.
 */

#ifndef LIST_H
#define LIST_H

#include <errno.h>

/**
 * @brief List the contents of a tar archive.
 * @param archive The path to the tar archive file.
 * 
 * @return 0 on success, error code on failure.
 */
int list_archive(const char *archive);

#endif