#!/bin/bash
# You will have to set these to the correct paths yourself 
# Sorry for the inconvenience!
IFOBJECT_PREFIX=/home/flux2/svn/iftools/trunk/ifobject
IFMAPPING_PREFIX=/home/flux2/svn/stuff/trunk/ifmapping
PYTHON_INCLUDE_PATH=/usr/include/python2.6

# You can usually leave those as they are if the prefix is correct.
IFOBJECT_INCLUDE_PATH=$IFOBJECT_PREFIX/include
IFOBJECT_LIB_PATH=$IFOBJECT_PREFIX/lib
IFOBJECT_SWIG_PATH=$IFOBJECT_PREFIX/swig
IFMAPPING_INCLUDE_PATH=$IFMAPPING_PREFIX/include
IFMAPPING_SWIG_PATH=$IFMAPPING_PREFIX/swig

if [[ ! -d $PYTHON_INCLUDE_PATH ]]; then
    echo "Python include path '$PYTHON_INCLUDE_PATH' does not exist. " \
        "Please set it to the correct path in createPyModule.sh."
fi
if [[ ! -d $IFOBJECT_INCLUDE_PATH ]]; then
    echo "IFObject include path '$IFOBJECT_INCLUDE_PATH' does not exist. " \
        "Please set it to the correct path in createPyModule.sh."
fi
if [[ ! -d $IFOBJECT_LIB_PATH ]]; then
    echo "IFObject library path '$IFOBJECT_LIB_PATH' does not exist. " \
        "Please set it to the correct path in createPyModule.sh."
fi
if [[ ! -d $IFOBJECT_SWIG_PATH ]]; then
    echo "IFObject SWIG path '$IFOBJECT_SWIG_PATH' does not exist. " \
        "Please set it to the correct path in createPyModule.sh."
fi

echo "Creating wrapper code for base library..."
swig -c++ -python -outdir swig/python \
    -I$IFOBJECT_SWIG_PATH -Iswig \
    swig/ifmapping.i &&
echo "Building Python module for base library..." &&
g++ -shared -fPIC -g -o swig/python/_IFMapping.so \
    -I$PYTHON_INCLUDE_PATH \
    -I$IFOBJECT_INCLUDE_PATH \
    -Ideps/tinyxml/include \
    -Iinclude $(pkg-config --cflags --libs sigc++-2.0) \
    -Llib -lifmapping \
    swig/ifmapping_wrap.cxx &&
echo "All done."
