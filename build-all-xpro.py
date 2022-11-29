#!/usr/bin/env python

# Note: If you experience random errors running this script within
# VSCode, try running it from a regular terminal window.  Some VSCode
# extensions seem to randomly interfere with the files that platformio
# uses during compilation.

# Compile Grbl_ESP32 for each of the machines defined in Machines/ .
# Add-on files are built on top of a single base.
# This is useful for automated testing, to make sure you haven't broken something

# The output is filtered so that the only lines you see are a single
# success or failure line for each build, plus any preceding lines that
# contain the word "error".  If you need to see everything, for example to
# see the details of an errored build, include -v on the command line.

from builder import buildMachine
import os, sys

cmd = ['platformio','run']

verbose = '-v' in sys.argv

numErrors = 0
names = os.listdir('Grbl_Esp32/src/Machines')

print()

for name in names:
    if "xPRO" in name:
        exitCode = buildMachine(name, verbose=verbose)
        if exitCode != 0:
            numErrors += 1
        else:
            source = os.getcwd() + "/.pio/build/release/firmware.bin"
            destination = "firmware/" + name.replace(".h", ".bin")
            os.system(f"cp {source} {destination}")

print (f"{numErrors} errors occurred")
print()

sys.exit(numErrors)
