#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#define TRUE 1
#define FALSE 0

void help_page(char* app_name) {
	fprintf(stderr, "cblight help page\n");
	fprintf(stderr, "%s%5s%25s\n", app_name, "-h", "Show this page");
	fprintf(stderr, "%s%5s%27s\n", app_name, "-l", "List all devices");
	fprintf(stderr, "%s%15s%16s\n", app_name, "-d [devname]", "Select a device");
	fprintf(stderr, "%s%11s%29s\n", app_name, "-s [num]", "Set the screen backlight");
	fprintf(stderr, "%s%5s%32s\n", app_name, "-a", "Show the actual value");
	fprintf(stderr, "%s%5s%32s\n", app_name, "-f", "Set the value to all devices");
}

void generate_devices(FILE* fDevices, char* devices_file) {
	struct dirent *pDirent;
	DIR *pDIR;
	char *bldir = "/sys/class/backlight/";

	pDIR = opendir(bldir);
	if (pDIR == NULL) {
		fprintf(stderr, "Cannot open directory: %s\n", bldir);
		exit(EXIT_FAILURE);
	}

	fclose(fopen(devices_file, "w"));
	rewind(fDevices);
	while ((pDirent = readdir(pDIR)) != NULL) {
		if (!(strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)) {
			fprintf(fDevices, "%s\n", pDirent->d_name);
		}
	}
}

void print_devices(FILE* fDevices) {
	char device[50];
	fseek(fDevices, 0, SEEK_SET);
	fprintf(stdout, "Devices list:\n");
	while (fgets(device, 50, fDevices)) {
		device[strcspn(device, "\n")] = '\0';
		fprintf(stdout, "%s\n", device);
	}
}

int actual_value() {
	return 0;
}

void get_device(FILE* fConfig, char* result) {
	fgets(result, 50, fConfig);
}

int find_device(FILE* fDevices, char* device) {
	char sel_device[50];
	fseek(fDevices, 0, SEEK_SET);
	while (fgets(sel_device, 50, fDevices)) {
		sel_device[strcspn(sel_device, "\n")] = '\0';
		if (strcmp(device, sel_device) == 0) {
			return TRUE;
		}
	}

	return FALSE;
}

void set_device(FILE* fConfig, FILE* fDevices, char* device) {
	if (find_device(fDevices, device)) {
		fprintf(stdout, "Device selected: %s\n", device);
		fprintf(fConfig, "%s\n", device);
	} else {
		fprintf(stderr, "Device not found!\n");
	}
}

void set_value(char* device, char* value) {
	char path[100] = "/sys/class/backlight/";
	// /sys/class/backlight/{device}
	strcat(path, device);

	char* max_brightness = malloc(sizeof(char) * 100);
	// /sys/class/backlight/{device}
	strcpy(max_brightness, path);
	// /sys/class/backlight/{device}/max_brightness
	strcat(max_brightness, "/max_brightness");

	char* brightness = malloc(sizeof(char) * 100);
	strcpy(brightness, path);
	strcat(brightness, "/brightness");

	FILE* file = fopen(max_brightness, "r");
	char value_m[50];
	fgets(value_m, 50, file);
	int val = atoi(value);
	if (val >= 0 && val <= atoi(value_m)) {
		file = fopen(brightness, "w");
		fprintf(file, "%s", value);
		fprintf(stdout, "Brightness set to: %s\n", value);
	} else {
		fprintf(stderr, "Cannot set the brightness value!\nMin: 0\nMax: %s\n", value_m);
	}

	fclose(file);
	free(max_brightness);
	free(brightness);
}

void set_value_all(char* value) {
  fprintf(stdout, "%s\n", value);
}

int main(int argc, char** argv) {
	if (optind >= argc) {
		fprintf(stderr, "No arguments provided, run -h for help\n");
		exit(EXIT_FAILURE);
	}

	char* device = malloc(sizeof(char*) * 50);
	char* devices_file = "devices.cb";
	char* config_file = "config.cb";
	char mode[3];

	FILE* fDevices;
	FILE* fConfig;

	if (access(devices_file, F_OK) == 0) {
		strncpy(mode, "r+", 3);
	} else {
		strncpy(mode, "w+", 3);
	}
	fDevices = fopen(devices_file, mode);

	if (access(config_file, F_OK) == 0) {
		strncpy(mode, "r+", 3);
	} else {
		strncpy(mode, "w+", 3);
	}
	fConfig = fopen(config_file, mode);

	if (fDevices == NULL || fConfig == NULL) {
		fprintf(stderr, "Unable to open %s or %s\n", config_file, devices_file);
		exit(EXIT_FAILURE);
	}

	int option;
	while ((option = getopt(argc, argv, "hld:s:af:")) != -1) {
		switch (option) {
			case 'h':
				help_page(argv[0]);
				exit(EXIT_SUCCESS);
			case 'l':
				generate_devices(fDevices, devices_file);
				print_devices(fDevices);
				exit(EXIT_SUCCESS);
			case 'd':
				generate_devices(fDevices, devices_file);
				if (find_device(fDevices, optarg)) {
					set_device(fConfig, fDevices, optarg);
					exit(EXIT_SUCCESS);
				} else {
					fprintf(stderr, "Cannot find device %s!\n", optarg);
					exit(EXIT_FAILURE);
				}
			case 's':
				generate_devices(fDevices, devices_file);
				get_device(fConfig, device);
				device[strcspn(device, "\n")] = '\0';
				if (strcmp(device, "") == 0) {
					fprintf(stderr, "You must select a device first!\n");
					exit(EXIT_FAILURE);
				}

				if (find_device(fDevices, device)) {
					set_value(device, optarg);
				}

				exit(EXIT_SUCCESS);
			case 'a':
				fprintf(stdout, "%d\n", actual_value());
				exit(EXIT_SUCCESS);
			case 'f':
				exit(EXIT_SUCCESS);
			case '?':
				if (optopt == 's') {
					fprintf(stderr, "Expected one argument after -%c!\n", optopt);
					exit(EXIT_FAILURE);
				} else {
					fprintf(stderr, "Unknow option: %c\n", optopt);
					exit(EXIT_FAILURE);
				}
		}
	}

	free(device);
	fclose(fDevices);
	fclose(fConfig);

	exit(EXIT_SUCCESS);
}

