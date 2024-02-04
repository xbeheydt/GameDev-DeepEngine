# Copyright Xavier Beheydt. All rights reserved.
import re
import sys


def main():
    with open(sys.argv[1], "r") as f:
        makefile = f.read()
        for line in makefile.splitlines():
            match = re.match(r'^([a-zA-Z0-9_\-\/]+):.*?## (.*)$$', line)
            if match:
                target, help = match.groups()
                print("\t%-45s %s" % (target, help))


if __name__ == "__main__":
    sys.exit(main())
