# IFVG - Ionflux' Volumetric Graphics Library
Copyright © 2014-2024 • Jörn Meier <webmaster@ionflux.org>

## README

### What is it?

IFVG (Ionflux' Volumetric Graphics Library) is a library that provides various classes and functions to support volumetric graphics.

Using SWIG, bindings for a large variety of programming languages can be created for the C++ library. The package currently supports Python, but it should not be too hard to generate bindings for other languages as well.

### Documentation

This project includes the following additional documentation files in the `docs` directory:

| Name | Description|
|---|---|
| node_data | data types used by the NodeImpl octree nodes |
| serialization | binary serialization formats used by the library |
| notes | implementation notes |

### Licensing

IFVG is free software released under the [GNU General Public License version 3](docs/gpl-3.0.md).

**Please note that this program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.**

### Dependencies

IFVG depends on the following packages:

+ [Ionflux Object Base System](https://github.com/TehFlux/iftools)
+ [Ionflux Template Processor](https://github.com/TehFlux/iftools)
+ [IFMapping - Ionflux Mapping Library](https://github.com/TehFlux/ifcg)
+ [Altjira - Ionflux' Image Processing Library](https://github.com/TehFlux/ifcg)
+ [GeoUtils - Ionflux' Geometry Library](https://github.com/TehFlux/ifcg)

Make sure you get a recent Git version of Ionflux Object Base System and Ionflux Template Processor. Older packages will most likely not work.

You can checkout the recent source code from GitHub like this:

`git clone git@github.com:TehFlux/iftools.git`

### Building

Build all of the dependencies before you try to build IFVG. There are build instructions included with the individual projects.

Note that all of the code is created using the Ionflux Template Processor.

However, the completed build of IFVG will not depend on Ionflux Template Processor.

IFVG uses [SCons](http://www.scons.org/) as the build system.

If you want to use custom configuration for the build process (for example, Python and ibrary paths), copy `site_scons/local_config.py.default` to `site_scons/local_config.py` and adjust the settings as required.

It is recommended to use a [virtualenv](https://virtualenv.pypa.io/en/latest/) for the Python components of IFVG.

You can easily create a virtualenv with e.g. `virtualenv ifcg_env` in a directory of your choice and then configure the build process to use this virtualenv for installation in `site_scons/local_config.py`.

Enable the virtualenv using `source <path to virtualenv>/bin/activate`.

When not installing to a system location (which is highly recommended), it is also ecommended to set up an environment with all of the required paths for development in `scripts/profile-local.sh`. You can use one of the provided templates to get started.

This environment can then be used with `source scripts/profile-local.sh`.

If everything is set up correctly, you can build the project by running 

`scons`

Install with

`scons install prefix=<installation base directory>`

where <installation base directory> ist the directory where GeoUtils should be installed.

### WARNING
 
 It is not recommended at this point to install IFVG in a system directory, since this is an alpha version under development. (No harm should be done even if you decide otherwise, but there is no guarantee.)

 **This software is not intended for use in production environments! Ignore this warning at your own peril.**

### Using

This library is intended for developers, so you should be able to derive how it is meant to be used from the source code documentation and the scripts in the `test` directory. If you have any questions, you can still contact me by mail (mail@ionflux.org).

**Enjoy!**