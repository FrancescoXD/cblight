#ifndef __CBLIGHT_H__
#define __CBLIGHT_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define TRUE 1
#define FALSE 0

/**
 * @brief config_t struct
 * @param devices_file String with devices filename
 * @param config_file String with config filename
 * @param device Device name
 * @param value Device brightness value
*/
typedef struct {
  char devices_file[50];
  char config_file[50];
  char device[50];
  char value[5];
} config_t;

/**
 * @brief Remove the newline character from string
 * @param s String where to remove
*/
void remove_newline(char* s);

/**
 * @brief Print the help page
 * @param app_name Appname
*/
void help_page(char* app_name);

/**
 * @brief Open devices dir and print all devices to devices file
 * @param fDevices Devices file
 * @param config Config struct
*/
void generate_devices(FILE* fDevices, config_t* config);

/**
 * @brief Print all devices in the devices file
 * @param fDevices Devices file
*/
void print_devices(FILE* fDevices);

/**
 * @brief Return the actual brightness value
 * @param TBD TBD
 * @return Returns the actual brightness value
*/
int actual_value();

/**
 * @brief Fill the device var in config struct
 * @param config Config struct
*/
void get_device(config_t* config);

/**
 * @brief Find if devices selected is in the devices file
 * @param fDevices Devices file
 * @param device Device name (from config struct)
 * @return Returns TRUE if found, otherwise FALSE
*/
int find_device(FILE* fDevices, char* device);

/**
 * @brief Set the new device
 * @param fConfig Config file
 * @param fDevices Devices file
 * @param device Device name
*/
void set_device(FILE* fConfig, FILE* fDevices, char* device);

/**
 * @brief Set the new value to a device
 * @param device Device name
 * @param value Value to bet set
*/
void set_value(char* device, char* value);

/**
 * @brief Set value to all devices found
 * @param value Value to be set
*/
void set_value_all(char* value);

/**
 * @brief Parse the args
 * @param argc argc
 * @param argv argv
 * @param config Config struct
 * @param fDevices Devices file
 * @param fConfig Config file
*/
void parse_args(int argc, char** argv, config_t* config, FILE* fDevices, FILE* fConfig);

/**
 * @brief Open devices to check if file exists or not
 * @param config Config struct
 * @param fDevices Devices file
 * @param fConfig Config file
*/
void open_devices(config_t* config, FILE* fDevices, FILE* fConfig);

#endif
