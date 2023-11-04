#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define MAXLEN 256

char * find_keyboard_device(void)
{
	char * keyboard_dev = malloc(sizeof(char) * MAXLEN);
	FILE * fp;
	char command[MAXLEN];
	char buffer[MAXLEN];
	int numEventDevices;

	// step 1: find number of devices.
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
			snprintf(keyboard_dev, MAXLEN,
					"/dev/input/event%d", i);
			break;
		}
	}
	if (strcmp(keyboard_dev, "") == 0) {
		printf("Could not find keyboard device.\n");
		return NULL;
	}
	else {
		printf("%s seems to be the keyboard device.\n", keyboard_dev);
	}

	return keyboard_dev;
}

int main(void)
{
	char * k = find_keyboard_device();
	free(k);
	return 0;	
}
