#!/usr/bin/python

import random, sys, string, argparse
from optparse import OptionParser

class randline:
    def __init__(self, filename, i):
        if((filename == "blank" or filename == "-") and i == "Null"):
            self.fileLines = sys.stdin.readlines()
            if(len(self.fileLines) <= 0):
                return 0
        elif(i == "Null"):
            f = open(filename, 'r')
            self.fileLines = f.readlines()
            f.close()

    def chooseline(self, i, n, r, input):
        output = []
        
        if n is int and n < 0:
            parser.error("negative count: {0}".
                         format(n))

        if(i != "Null"):
            if(input != "blank"):
                parser = OptionParser()
                parser.error("extra operand " + input)
            min = int(i.split('-')[0])
            max = int(i.split('-')[1])
            arr = [j for j in range(min, max + 1)]

            if(r and n == "null"):
                while(True):
                    sys.stdout.write(str(random.choice(range(min, max + 1))) + '\n')
            else:
                if(n == "null"):
                    while(len(arr) >= 1):
                        k = random.choice(range(len(arr)))
                        output.append(str(arr[k]) + '\n')
                        del(arr[k])
                    return output
                else:
                    for c in range(n):
                        if(len(arr) == 0):
                            return output
                        elif(not r):
                            k = random.choice(range(len(arr)))
                            output.append(str(arr[k]) + '\n')
                            del(arr[k])
                        else:
                            k = random.choice(range(len(arr)))
                            output.append(str(arr[k]) + '\n')
                    return output

        lines = self.fileLines[:]
        
        if(r and n == "null"):
            while(True):
                sys.stdout.write(lines[random.choice(range(len(lines)))])
        else:
            if(n == "null"):
                n = len(self.fileLines)
            for c in range(n):
                if(r):
                    output.append(lines[random.choice(range(len(lines)))])
                else:
                    k = random.choice(range(len(lines)))
                    output.append(lines[k])
                    del lines[k]
                    if(len(lines) == 0):
                        return output
        return output

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog {OPTION]... FILE

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--head-count",
                      action="store", dest="n",
                      help="output at most COUNT lines")
    parser.add_option("-i", "--input-range",
                      action="store", dest="i", default="Null",
                      help="treat each number LO through HI as an input line")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="r", default=False,
                      help="output NUMLINES lines (default 1)")

    options, args = parser.parse_args(sys.argv[1:])
    
    try:
        n = int(options.n)
    except:
        n = "null"

    if n is int and n < 0:
        parser.error("negative count: {0}".
                     format(n))
    r = bool(options.r)
    i = str(options.i)

    try:
        input = args[0]
    except:
        input = "blank"
    try:
        generator = randline(input, i)
        result = generator.chooseline(i, n, r, input)
        for obj in result:
            sys.stdout.write(obj)
    except IOError as err:
        parser.error("I/0 error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
