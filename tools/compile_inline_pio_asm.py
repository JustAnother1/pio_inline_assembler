#!/usr/bin/python3
# -*- coding: utf-8 -*-

# How this should work:
# The first paremeter to the script is the file that has C-code and PIO assembler mixed in.
# this scripts reads the file and extracts the pio asm code and writes it to  the *.pio file.
# The pio assembler starts after a line that contains "PIO inline ASM".
# The pio assembly end before a line that contains "PIO inline ASM".
# There can only be one PIO block in the file!
# It then copiles the pio file into hex codes.
# It then creates a *.c file that has the code from the script parameter file 
# but replaced the pio asm code by the hex codes.
# the input file must end with ".pio.c".
# the output file will end with ".binpio.c"

import subprocess
import sys

def compile(pioCode, pioFileName):
    # create pio file for RaspberryPi pioasm tool.
    codeFile = open(pioFileName, 'w')
    for line in pioCode:
        codeFile.write(line)
    codeFile.close()
    
    cmd = ['pioasm -o hex '  + pioFileName]
    #print(str(cmd))
    #run pioasm
    completed = subprocess.run(cmd,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE,
                               shell=True,
                               )

    if 0 != completed.returncode:
        print('returncode: ', completed.returncode)
        print('PIO compile : Failed')
        sys.exit(2)
    else:
        print('PIO compile : OK')
        #print('Have {} bytes in stdout: {!r}'. format(len(completed.stdout), completed.stdout.decode('utf-8')))
        #print('Have {} bytes in stderr: {!r}'. format(len(completed.stderr), completed.stderr.decode('utf-8')))
        log = completed.stdout.decode('utf-8')
        lines = log.splitlines()
        res = []
        for line in lines:
            line = '    0x' + line + ',\n'
            res = res + [line]
        return res

#main:
if __name__ == '__main__':
    # check parameter
    fileName = sys.argv[1];
    if False == fileName.endswith('.pio.c'):
        print("ERROR: invalid parameter (" + fileName + ") ! Must end with .pio.c !")
        sys.exit(1)
    # calculate file names
    resultFileName = fileName[:-6] + '.binpio.c'
    pioFileName = fileName[:-6] + '.inl.pio'
    # split surce file into parts
    inlineFile = open(fileName, 'r')
    inLines = inlineFile.readlines()
    pretext = []
    postText = []
    pioCode = []
    phase = 0
    for line in inLines:
        if 'PIO inline ASM' in line :
            if 0 == phase :
                phase = 1
            else:
                phase = 2
        else:
            if 0 == phase :
                pretext = pretext + [line]
            if 1 == phase :
                pioCode = pioCode + [line]
            if 2 == phase :
                postText = postText + [line]
    # compile PIO
    compiled = []
    if 0 < len(pioCode):
        compiled = compile(pioCode, pioFileName)
    # combine to result c file
    resultFile = open(resultFileName, 'w')
    
    for line in pretext:
        resultFile.write(line)
    for line in compiled:
        resultFile.write(line)
    for line in postText:
        resultFile.write(line)
    resultFile.close()