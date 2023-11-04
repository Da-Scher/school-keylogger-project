
/* Looks at each /dev/input/deviceX on the system, and if 
 * one seems to be a keyboard, returns the path to it.
 * If none appear to be keyboards, NULL is returned.
 */
char * find_keyboard_device(void);
