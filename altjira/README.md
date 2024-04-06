# Altjira - Ionflux' Image Processing Library
Copyright © 2009-2024 • Jörn Meier <webmaster@ionflux.org>

## README

### What is it?

Altjira (Ionflux' Image Processing Library) is an image processing library written in C++. It is designed to be used with Python and uses the well known GDK-PixBuf library for the low-level image handling.

I decided to write this to have native implementations for some image processing tasks I use in my Python applications, which were too slow when implemented in Python. Therefore, there is no immediate goal for Altjira to be "complete" or generic. However, it does provide a nice way of adding native image processing features to Python.

Using SWIG, bindings for a large variety of programming languages can be created. The package currently supports Python, but it should not be too hard to generate bindings for other languages as well.

### Features

+ Colors (RGBA)
+ Color space conversion (HSV, HSL, RGB)
+ Color bands to quickly generate ranges of colors
+ Image loading, PNG writing
+ Image pixel manipulation
+ Image processing (filters, compositing, normal map generation, …)
+ Blend modes
+ Gradients
+ Drawing (using cairo)
+ libnoise support

### Licensing

Altjira is free software released under the [GNU General Public License version 3](docs/gpl-3.0.md).

**Please note that this program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.**

### Dependencies

Altjira depends on the following packages:

+ [Ionflux Object Base System](https://github.com/TehFlux/iftools)
+ [Ionflux Template Processor](https://github.com/TehFlux/iftools)
+ [IFMapping - Ionflux Mapping Library](https://github.com/TehFlux/iftools)
+ [GDK-PixBuf](https://docs.gtk.org/gdk-pixbuf/) (available on most Linux distributions)

The following dependencies are optional, but highly recommended:

+ [Python](https://www.python.org/) >= 3.3  
  required for the Python bindings

If you want to build the AltjiraNoise library, which provides image noise generation capabilities, you will also need to provide the following dependencies:

+ [libnoise](http://libnoise.sourceforge.net)  
  Required for noise generation. A version suitable for use with Altjira, including Scons build scripts for a dynamic library, is included in the IFMapping repository.
+ [pynoise](http://home.gna.org/pynoise/)  
  Required for the Python bindings for noise mappings. There is no need to install this separately if libnoise from the IFMapping repository is used.

If you want to build the AltjiraDraw library, which provides text and vector graphics drawing capabilities, you will also need to provide the following dependencies:

+ [librsvg](https://gitlab.gnome.org/GNOME/librsvg)  
  Required for SVG rendering, available on most Linux distributions.
+ [pangocairo](https://docs.gtk.org/PangoCairo/)  
  Required for text rendering, available on most Linux distributions.

Make sure you get a recent Git version of Ionflux Object Base System and Ionflux Template Processor. Older packages will most likely not work.

You can checkout the recent source code from GitHub like this:

`git clone git@github.com:TehFlux/iftools.git`

### Building

Build all of the dependencies before you try to build Altjira. There are build instructions included with the individual projects.

Note that all of the code is created using the Ionflux Template Processor.

However, the completed build of Altjira will not depend on Ionflux Template Processor.

Altjira uses [SCons](http://www.scons.org/) as the build system.

If you want to use custom configuration for the build process (for example, Python and ibrary paths), copy `site_scons/local_config.py.default` to `site_scons/local_config.py` and adjust the settings as required.

It is recommended to use a [virtualenv](https://virtualenv.pypa.io/en/latest/) for the Python components of IFTemplate.

You can easily create a virtualenv with e.g. `virtualenv ifcg_env` in a directory of your choice and then configure the build process to use this virtualenv for installation in `site_scons/local_config.py`.

Enable the virtualenv using `source <path to virtualenv>/bin/activate`.

When not installing to a system location (which is highly recommended), it is also ecommended to set up an environment with all of the required paths for development in `scripts/profile-local.sh`. You can use one of the provided templates to get started.

This environment can then be used with `source scripts/profile-local.sh`.

If everything is set up correctly, you can build the project by running 

`scons`

Install with

`scons install prefix=<installation base directory>`

where <installation base directory> ist the directory where the Ionflux Object Base System should be installed.

### WARNING
 
 It is not recommended at this point to install Altjira in a system directory, since this is an alpha version under development. (No harm should be done even if you decide otherwise, but there is no guarantee.)

 **This software is not intended for use in production environments! Ignore this warning at your own peril.**

### Using

This library is intended for developers, so you should be able to derive how it is meant to be used from the source code documentation and the scripts in the 'test' directory. If you have any questions, you can still contact me by mail.

**Enjoy!**