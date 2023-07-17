#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * @brief Remove the newline character from string
 * @param s String where to remove
*/
void remove_newline(char *s);

/**
 * @brief Help to print help page using the right tab
*/
void cmd_usage(char shorts, const char *longs, const char *arg, const char *desc);

/**
 * @brief Print the help page
*/
void help_page(void);

/**
 * @brief Make the config directory
*/
void make_config_directory(void);

/**
 * @brief Return the config directory
 * @return Cblight's config directory
*/
char *get_config_dir(void);

#endif

