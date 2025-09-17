#!/usr/bin/python3
# -*- coding: utf-8 -*-

# How this should work:
# The first paremeter to the script is the name of the file that has C-code and PIO assembler mixed in.
# this scripts reads the file and extracts the pio asm code and writes it to  the *.inl.pio files.
# The pio assembler starts after a line that contains "PIO inline ASM".
# The pio assembly end before a line that contains "PIO inline ASM".
# There can be one or more PIO assembly blocks in the file.
# It creates a pio file for each block of PIO assembly.
# Each block can have a name. The name is given in the same line after the "PIO inline ASM".
# The name will be put into the name of the pio file like so: *.name.inl.pio
# If no name is given to the blocks then the blocks will be numbered. 
# The first pio file will not have a number, 
# the second will have the number 1 attached (*.1.inl.pio),...
# It then copiles the pio file into hex codes.
# It then creates a *.c file that has the code from the input file (script parameter) 
# but replaced the pio asm code by the hex codes.
# The input file must end with ".pio.c".
# The output file will end with ".binpio.c".

import subprocess
import sys

def compile(pioCode, pioFileName):
    # create pio file for RaspberryPi pioasm tool.
    print('compiling ' + pioFileName)
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
        if 0 < len(completed.stdout):
            print('Have {} bytes in stdout: {!r}'. format(len(completed.stdout), completed.stdout.decode('utf-8')))
        if 0 < len(completed.stderr):
            print('Have {} bytes in stderr: {!r}'. format(len(completed.stderr), completed.stderr.decode('utf-8')))
        print('PIO compile : Failed')
        sys.exit(2)
    else:
        print('PIO compile : OK')
        log = completed.stdout.decode('utf-8')
        lines = log.splitlines()
        res = []
        for line in lines:
            line = '    0x' + line + ',\n'
            res = res + [line]
        return res

def getName(line):
    name = ''
    parts = line.split('PIO inline ASM')
    if len(parts) < 2:
        name = parts[1]
        name = name.strip()
    return name

#main:
if __name__ == '__main__':
    # check parameter
    fileName = sys.argv[1];
    if False == fileName.endswith('.pio.c'):
        print("ERROR: invalid parameter (" + fileName + ") ! Must end with .pio.c !")
        sys.exit(1)
    # calculate file names
    resultFileName = fileName[:-6] + '.binpio.c'
    pioFileName = ''
    # open result c file
    resultFile = open(resultFileName, 'w')
    # go through source line by line
    inlineFile = open(fileName, 'r')
    inLines = inlineFile.readlines()
    in_pio = False
    block_num = 0
    pioCode = []
    for line in inLines:
        if 'PIO inline ASM' in line :
            if False == in_pio :
                # a new PIO block starts
                in_pio = True
                name = getName(line)
                if len(name) < 1:
                    # no name given
                    if 0 == block_num:
                        pioFileName = fileName[:-6] + '.inl.pio'
                    else:
                        pioFileName = fileName[:-6] + '.' + str(block_num) + '.inl.pio'
                    block_num = block_num + 1;
                else:
                    # name given
                    pioFileName = fileName[:-6] + name + '.inl.pio'
            else:
                # end of the PIO block
                in_pio = False
                # compile PIO
                compiled = []
                if 0 < len(pioCode):
                    compiled = compile(pioCode, pioFileName)
                    pioCode = []
                    for compiledLine in compiled:
                        resultFile.write(compiledLine)
        else:
            if False == in_pio :
                resultFile.write(line)
            else:
                pioCode = pioCode + [line]
    # we are done here
    resultFile.close()