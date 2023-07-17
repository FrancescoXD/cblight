#include <cblight.h>

int main(int argc, char **argv) {
	if (optind >= argc) {
		fprintf(stderr, "No arguments provided, run -h for help\n");
		exit(EXIT_FAILURE);
	}
	
	config_t config;

	make_config_directory();
	char *config_dir = get_config_dir();
	strcpy(config.devices_file, config_dir);
	strncat(config.devices_file, "devices.cb", 11);
	strcpy(config.config_file, config_dir);
	strncat(config.config_file, "config.cb", 10);

	FILE *fDevices = NULL;
	FILE *fConfig = NULL;

	open_devices(&config, &fDevices, &fConfig);
	parse_args(argc, argv, &config, &fDevices, &fConfig);

	fclose(fDevices);
	fclose(fConfig);

	exit(EXIT_SUCCESS);
}

