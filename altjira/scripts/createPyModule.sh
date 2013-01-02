#!/bin/bash
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2009 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# createPyModule.sh              Python module creation script.
# ==========================================================================
# 
# This file is part of Altjira - Ionflux' Image Processing Library.
# 
# Altjira - Ionflux' Image Processing Library is free software; you can 
# redistribute it and/or modify it under the terms of the GNU General 
# Public  License as published by the Free Software Foundation; either 
# version 2 of the License, or (at your option) any later version.
# 
# Altjira - Ionflux' Image Processing Library is distributed in the hope 
# that it will be useful, but WITHOUT ANY WARRANTY; without even the 
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Ionflux Star Database; if not, write to the Free Software 
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# 
# ==========================================================================

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
swig -c++ -python -outdir swig/python -I$IFOBJECT_SWIG_PATH \
    -I$IFMAPPING_SWIG_PATH -I./swig \
    swig/altjira.i &&
echo "Building Python module for base library..." &&
g++ -shared -fPIC -g -o swig/python/_Altjira.so -I$PYTHON_INCLUDE_PATH \
    -I$IFOBJECT_INCLUDE_PATH -L$IFOBJECT_LIB_PATH \
    -I$IFMAPPING_INCLUDE_PATH -L$IFMAPPING_LIB_PATH \
    -Iinclude -Llib \
    $(pkg-config --cflags --libs sigc++-2.0) \
    $(pkg-config --cflags --libs gdk-pixbuf-2.0) \
    -lifobject -lifmapping -laltjira \
    swig/altjira_wrap.cxx &&
echo "All done."
