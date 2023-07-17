#include <utils.h>

void remove_newline(char* s) {
	while (*s) {
		if (*s == '\n') *s = '\0';
		s++;
  	}
}

void cmd_usage(char shorts, const char *longs, const char *arg, const char *desc) {
	putchar('\t');
	if (shorts) printf("-%c ", shorts);
	if (longs) printf("--%s ", longs);
	if (arg) printf("<%s>", arg);
	printf("\n\t\t%s\n", desc);
}

void help_page(void) {
	fprintf(stdout, "cblight help page\n");
	cmd_usage('h', NULL, NULL, "Show this page");
	cmd_usage('l', NULL, NULL, "List all devices");
	cmd_usage('d', NULL, "device", "Select a device");
	cmd_usage('s', NULL, "num", "Set the screen backlight");
	cmd_usage('a', NULL, NULL, "Show the value");
}

char *get_config_dir(void) {
	char *home_env = getenv("HOME");
	if (home_env == NULL) {
		fprintf(stderr, "[error] $HOME not set!\n");
		exit(EXIT_FAILURE);
	}
	//fprintf(stdout, "[debug] $HOME=%s\n", home_env);

	char *config_dir = (char *)malloc(sizeof(char) * 100);
	strcat(config_dir, home_env);
	strncat(config_dir, "/.config/cblight/", 18);
	//fprintf(stdout, "[debug] config dir: %s\n", config_dir);

	return config_dir;
}

void make_config_directory(void) {
	char *config_dir = get_config_dir();

	struct stat stat_info;
	int ret_stat = stat(config_dir, &stat_info);
	if (!(ret_stat == 0 && S_ISDIR(stat_info.st_mode))) {
		fprintf(stdout, "[info] creating the config directory...\n");
		int mkdir_ret = mkdir(config_dir, 0755);
		if (mkdir_ret == -1) {
			fprintf(stderr, "[error] unable to create config dir!\n");
			exit(EXIT_FAILURE);
		}
	}
}

