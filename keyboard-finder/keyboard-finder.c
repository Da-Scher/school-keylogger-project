#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Looks at each /dev/input/deviceX on the system, and if 
 * one seems to be a keyboard, returns the path to it.
 * If none appear to be keyboards, NULL is returned.
 *
 * The returned path string needs to be freed by the user.
 */
char * find_keyboard_device(int verbose)
{
	FILE * fp;
	int numEventDevices;
	char command[256];
	char buffer[256];
	char * keyboard_dev = malloc(sizeof(char) * 256);

	// step 1: find number of devices matching /dev/input/event*.
	snprintf(command, sizeof(command), "ls /dev/input/event* | wc -l");
	fp = popen(command, "r");
	if (fp == NULL) {
		perror("popen");
		exit(1);
	}
	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		sscanf(buffer, "%d", &numEventDevices);
	}
	fclose(fp);
	if (verbose)
		printf("Detected %d event devices on the system.\n", numEventDevices);

	// step 2: check which are keyboard devices.
	// we will naively just grab the first we see.
	strcpy(keyboard_dev, "");
	int foundKB = 0;
	for (int i = 0; i < numEventDevices; i++) {
		snprintf(command, sizeof(command),
				"udevadm info --query=all --name=/dev/input/event%d "\
				"| grep -i keyboard", i);
		fp = popen(command, "r");
		if (fp == NULL) {
			perror("popen");
			exit(1);
		}
		while(fgets(buffer, sizeof(buffer), fp) != NULL) {
			if (strlen(buffer) != 0) {
				foundKB = 1;
				break;
			}
		}
		if (foundKB) {
			snprintf(keyboard_dev, 256, "/dev/input/event%d", i);
			break;
		}
	}
	if (strcmp(keyboard_dev, "") == 0) {
		if (verbose) printf("Could not find keyboard device.\n");
		return NULL;
	}
	else {
		if (verbose) printf("%s seems to be the keyboard device.\n", keyboard_dev);
		return keyboard_dev;
	}
}
