#include <cblight.h>

int main(int argc, char **argv) {
	if (optind >= argc) {
		fprintf(stderr, "No arguments provided, run -h for help\n");
		exit(EXIT_FAILURE);
	}

	config_t config;
	strcpy(config.devices_file, "devices.cb");
	strcpy(config.config_file, "config.cb");

	FILE* fDevices = NULL;
	FILE* fConfig = NULL;

	open_devices(&config, fDevices, fConfig);
	parse_args(argc, argv, &config, fDevices, fConfig);

	fclose(fDevices);
	fclose(fConfig);

	exit(EXIT_SUCCESS);
}

