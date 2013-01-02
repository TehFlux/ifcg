#!/bin/bash
# The source files which belong to the library.
SOURCE_FILES="src/tinystr.cpp src/tinyxml.cpp src/tinyxmlerror.cpp src/tinyxmlparser.cpp"

# Really quick and dirty build script.
echo "Building library..."
g++ -fPIC -shared -g -o lib/libtinyxml.so \
    -Iinclude $SOURCE_FILES
echo "All done."
