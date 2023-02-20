#include <cblight.h>
#include <utils.h>

void generate_devices(FILE *fDevices) {
	struct dirent *pDirent;
	DIR *pDIR;
	char *bldir = "/sys/class/backlight/";

	pDIR = opendir(bldir);
	if (pDIR == NULL) {
		fprintf(stderr, "Cannot open directory: %s\n", bldir);
		exit(EXIT_FAILURE);
	}

	fseek(fDevices, 0L, SEEK_SET);
	if (fDevices == NULL) {
		perror("fDevices is NULL");
		exit(EXIT_FAILURE);
	}
	while ((pDirent = readdir(pDIR)) != NULL) {
		if (!(strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)) {
			fprintf(fDevices, "%s\n", pDirent->d_name);
		}
	}
}

void print_devices(FILE *fDevices) {
	char device[50];
	fseek(fDevices, 0, SEEK_SET);
	fprintf(stdout, "Devices list:\n");
	while (fgets(device, 50, fDevices)) {
		remove_newline(device);
		fprintf(stdout, "%s\n", device);
	}
}

int brightness_value(config_t *config) {
	char value[20];
	char dev[100] = "/sys/class/backlight/";
	strcat(dev, config->device);
	strcat(dev, "/actual_brightness");

	FILE *dvalue = fopen(dev, "r");
	fgets(value, 20, dvalue);
	remove_newline(value);

	return atoi(value);
}

void get_device(config_t *config) {
	FILE *fConfig = fopen(config->devices_file, "r");
	fgets(config->device, 50, fConfig);
	remove_newline(config->device);
}

int find_device(FILE *fDevices, char *device) {
	char sel_device[50];
	fseek(fDevices, 0, SEEK_SET);
	while (fgets(sel_device, 50, fDevices)) {
		remove_newline(sel_device);
		if (strcmp(device, sel_device) == 0) {
			return TRUE;
		}
	}

	return FALSE;
}

void set_device(FILE *fConfig, FILE *fDevices, char *device) {
	if (find_device(fDevices, device)) {
		fprintf(stdout, "Device selected: %s\n", device);
		fprintf(fConfig, "%s\n", device);
	} else {
		fprintf(stderr, "Device not found!\n");
	}
}

void set_value(char *device, char *value) {
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

void parse_args(int argc, char **argv, config_t *config, FILE **fDevices, FILE **fConfig) {
	int option;
	while ((option = getopt(argc, argv, "hld:s:a")) != -1) {
		switch (option) {
			case 'h':
				help_page();
				exit(EXIT_SUCCESS);
			case 'l':
				generate_devices(*fDevices);
				print_devices(*fDevices);
				exit(EXIT_SUCCESS);
			case 'd':
				generate_devices(*fDevices);
				if (find_device(*fDevices, optarg)) {
					set_device(*fConfig, *fDevices, optarg);
					exit(EXIT_SUCCESS);
				} else {
					fprintf(stderr, "Cannot find device %s!\n", optarg);
					exit(EXIT_FAILURE);
				}
			case 's':
				generate_devices(*fDevices);
				get_device(config);
				remove_newline(config->device);
				if (strcmp(config->device, "") == 0) {
					fprintf(stderr, "You must select a device first!\n");
					exit(EXIT_FAILURE);
				}

				if (find_device(*fDevices, config->device)) {
					set_value(config->device, optarg);
				}

				exit(EXIT_SUCCESS);
			case 'a':
				get_device(config);
				fprintf(stdout, "%d\n", brightness_value(config));
				exit(EXIT_SUCCESS);
			case '?':
				if (optopt == 's' || optopt == 'd') {
					fprintf(stderr, "Expected one argument after -%c!\n", optopt);
					exit(EXIT_FAILURE);
				} else {
					fprintf(stderr, "Unknow option: %c\n", optopt);
					exit(EXIT_FAILURE);
				}
		}
	}
}

void open_devices(config_t *config, FILE **fDevices, FILE **fConfig) {
	char mode[3];

	if (access(config->devices_file, F_OK) == 0) {
		strncpy(mode, "r+", 3);
	} else {
		strncpy(mode, "w+", 3);
		fprintf(stdout, "[info] creating devices.cb...");
	}
	*fDevices = fopen(config->devices_file, mode);

	if (access(config->config_file, F_OK) == 0) {
		strncpy(mode, "r+", 3);
	} else {
		strncpy(mode, "w+", 3);
		fprintf(stdout, "[info] creating config.cb...");
	}
	*fConfig = fopen(config->config_file, mode);

	if (fDevices == NULL || fConfig == NULL) {
		fprintf(stderr, "Unable to open %s or %s\n", config->config_file, config->devices_file);
		exit(EXIT_FAILURE);
	}
}

