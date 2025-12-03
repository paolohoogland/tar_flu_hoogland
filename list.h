/**
 * @file list.h
 * @brief Header file for listing contents of a tar archive.
 *
 * This module provides the function declarations for listing the contents
 * of a tar archive.
 */

#ifndef LIST_H
#define LIST_H

/**
 * @brief List the contents of a tar archive.
 * @param archive The path to the tar archive file.
 */
void list_archive(const char *archive);

#endif