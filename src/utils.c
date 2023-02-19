#include <utils.h>
#include <stdio.h>

void remove_newline(char* s) {
	while (*s) {
		if (*s == '\n') *s = '\0';
		s++;
  	}
}

void help_page(char* app_name) {
	fprintf(stderr, "cblight help page\n");
	fprintf(stderr, "%s%5s%25s\n", app_name, "-h", "Show this page");
	fprintf(stderr, "%s%5s%27s\n", app_name, "-l", "List all devices");
	fprintf(stderr, "%s%15s%16s\n", app_name, "-d [devname]", "Select a device");
	fprintf(stderr, "%s%11s%29s\n", app_name, "-s [num]", "Set the screen backlight");
	fprintf(stderr, "%s%5s%32s\n", app_name, "-a", "Show the actual value");
	fprintf(stderr, "%s%5s%32s\n", app_name, "-f", "Set the value to all devices");
}

