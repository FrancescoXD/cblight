#include <utils.h>
#include <stdio.h>

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

