#!/bin/bash
# You will have to set these to the correct paths yourself 
# Sorry for the inconvenience!
IFOBJECT_PREFIX=/home/flux/svn/iftools/trunk/ifobject
ALTJIRA_PREFIX=/home/flux/svn/stuff/trunk/altjira
IFMAPPING_PREFIX=/home/flux2/svn/stuff/trunk/ifmapping
PYTHON_INCLUDE_PATH=/usr/include/python2.6

# You can usually leave those as they are if the prefix is correct.
IFOBJECT_INCLUDE_PATH=$IFOBJECT_PREFIX/include
IFOBJECT_LIB_PATH=$IFOBJECT_PREFIX/lib
IFOBJECT_SWIG_PATH=$IFOBJECT_PREFIX/swig
ALTJIRA_INCLUDE_PATH=$ALTJIRA_PREFIX/include
ALTJIRA_SWIG_PATH=$ALTJIRA_PREFIX/swig
IFMAPPING_INCLUDE_PATH=$IFMAPPING_PREFIX/include
IFMAPPING_LIB_PATH=$IFMAPPING_PREFIX/lib
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
    -I$IFOBJECT_SWIG_PATH -I$IFMAPPING_SWIG_PATH -Iswig \
    swig/geoutils.i &&
echo "Creating wrapper code for Altjira/GeoUtils library..."
swig -c++ -python -outdir swig/python \
    -I$IFOBJECT_SWIG_PATH -I$IFMAPPING_SWIG_PATH -I$ALTJIRA_SWIG_PATH \
    -Iswig swig/altjirageoutils.i &&
echo "Building Python module for base library..." &&
g++ -shared -fPIC -g -o swig/python/_CGeoUtils.so \
    -I$PYTHON_INCLUDE_PATH \
    -I$IFOBJECT_INCLUDE_PATH -L$IFOBJECT_LIB_PATH \
    -I$IFMAPPING_INCLUDE_PATH -L$IFMAPPING_LIB_PATH \
    -Ideps/tinyxml/include \
    -Iinclude $(pkg-config --cflags --libs sigc++-2.0) \
    -Llib -lifobject -lgeoutils -lifmapping \
    swig/geoutils_wrap.cxx &&
echo "Building Python module for Altjira/GeoUtils library..." &&
g++ -shared -fPIC -g -o swig/python/_AltjiraGeoUtils.so \
    -I$PYTHON_INCLUDE_PATH \
    -I$IFOBJECT_INCLUDE_PATH -L$IFOBJECT_LIB_PATH \
    -I$IFMAPPING_INCLUDE_PATH -L$IFMAPPING_LIB_PATH \
    -I$ALTJIRA_INCLUDE_PATH \
    -Ideps/tinyxml/include \
    -Iinclude $(pkg-config --cflags --libs sigc++-2.0) \
    -Iinclude $(pkg-config --cflags --libs gdk-pixbuf-2.0) \
    -Iinclude $(pkg-config --cflags --libs cairo) \
    -Llib -lifobject -lgeoutils -lifmapping -laltjirageoutils \
    swig/altjirageoutils_wrap.cxx &&
echo "All done."
