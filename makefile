# ----------------------------
# Makefile Options
# ----------------------------

NAME = TRICALCB
ICON = icon.png
DESCRIPTION = "A Triangle Calculator"
COMPRESSED = YES
COMPRESSED_MODE = zx0
OUTPUT_MAP = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
