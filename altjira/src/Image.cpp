/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Image.cpp                       Image (implementation).
 * =========================================================================
 * 
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "altjira/Image.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdint.h>
#include "ifmapping/utils.hpp"
#include "altjira/utils.hpp"
#include "altjira/imageutils.hpp"
#include "ifobject/serialize.hpp"
#include "altjira/BlendSrcOver.hpp"
#include "altjira/BlendChannel.hpp"
#include "altjira/AltjiraError.hpp"
#include "altjira/ImageSet.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Altjira
{

ImageClassInfo::ImageClassInfo()
{
	name = "Image";
	desc = "Image";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ImageClassInfo::~ImageClassInfo()
{
}

// public member constants
const Ionflux::Altjira::ImageType Image::TYPE_PNG = 0;
const Ionflux::Altjira::ImageType Image::TYPE_JPEG = 1;
const Ionflux::Altjira::ImageType Image::TYPE_GBR_GRAYSCALE = 2;
const Ionflux::Altjira::ImageType Image::TYPE_GBR_RGBA = 3;
const Ionflux::Altjira::ImageType Image::TYPE_GIH_GRAYSCALE = 4;
const Ionflux::Altjira::ImageType Image::TYPE_GIH_RGBA = 5;
const std::string Image::GIH_DEFAULT_PLACEMENT = "constant";
const unsigned int Image::GIH_CELL_SIZE_MAX = UINT_MAX;
const unsigned int Image::GIH_DEFAULT_CELL_WIDTH = GIH_CELL_SIZE_MAX;
const unsigned int Image::GIH_DEFAULT_CELL_HEIGHT = GIH_CELL_SIZE_MAX;

// run-time type information instance constants
const ImageClassInfo Image::imageClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Image::CLASS_INFO = &Image::imageClassInfo;

Image::Image()
: pixBuf(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	Ionflux::Altjira::init();
}

Image::Image(const Ionflux::Altjira::Image& other)
: pixBuf(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	Ionflux::Altjira::init();
	*this = other;
}

Image::Image(const std::string& fileName)
: pixBuf(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	Ionflux::Altjira::init();
	loadFromFile(fileName);
}

Image::Image(unsigned int initWidth, unsigned int initHeight, bool 
initAlpha, unsigned int initBitsPerSample, Ionflux::Altjira::ColorSpace 
initColorSpace)
: pixBuf(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	Ionflux::Altjira::init();
	createNewData(initWidth, initHeight, initAlpha, 
	    initBitsPerSample, initColorSpace);
}

Image::~Image()
{
	clear();
}

void Image::update()
{
	if (pixBuf == 0)
	    return;
	width = static_cast<unsigned int>(gdk_pixbuf_get_width(pixBuf));
	height = static_cast<unsigned int>(gdk_pixbuf_get_height(pixBuf));
	numChannels = gdk_pixbuf_get_n_channels(pixBuf);
	GdkColorspace cs = gdk_pixbuf_get_colorspace(pixBuf);
	if (cs == GDK_COLORSPACE_RGB)
	    colorSpace = Color::SPACE_RGB;
	else
	    colorSpace = Color::SPACE_UNDEFINED;
	bitsPerSample = gdk_pixbuf_get_bits_per_sample(pixBuf);
	alphaFlag = gdk_pixbuf_get_has_alpha(pixBuf);
	rowStride = gdk_pixbuf_get_rowstride(pixBuf);
	pixels = gdk_pixbuf_get_pixels(pixBuf);
}

void Image::createNewData(unsigned int initWidth, unsigned int initHeight, 
bool initAlpha, unsigned int initBitsPerSample, 
Ionflux::Altjira::ColorSpace initColorSpace)
{
	clear();
	/* RGB is the only color space supported by Gdk-Pixbuf and 
	   hence, by the Altjira Image. */
	GdkColorspace cs = GDK_COLORSPACE_RGB;
	pixBuf = gdk_pixbuf_new(cs, initAlpha, initBitsPerSample, 
	    initWidth, initHeight);
	update();
}

bool Image::loadFromFile(const std::string& fileName)
{
	clear();
	pixBuf = gdk_pixbuf_new_from_file(fileName.c_str(), 0);
	if (pixBuf == 0)
	{
	    std::ostringstream status;
	    status << "[Image::loadFromFile] Could not load image "
	        "from file '" << fileName << "'!";
	    throw AltjiraError(status.str());
	}
	update();
	return true;
}

void Image::getGIHData(std::string& target, unsigned int cellWidth, 
unsigned int cellHeight, const Ionflux::Altjira::GIHRankSpecVector* ranks, 
const std::string& placement, Ionflux::Altjira::ImageType type, const 
std::string& brushName, unsigned int spacing, 
Ionflux::Altjira::DesaturationMethod desaturationMethod)
{
	if (cellWidth == GIH_CELL_SIZE_MAX)
	    cellWidth = width;
	if (cellHeight == GIH_CELL_SIZE_MAX)
	    cellHeight = height;
	unsigned int numCellsX = width / cellWidth;
	unsigned int numCellsY = height / cellHeight;
	unsigned int numCells = numCellsX * numCellsY;
	unsigned int numRanks = 0;
	if (ranks != 0)
	    numRanks = ranks->size();
	unsigned int dimension = 1;
	if (numRanks > 0)
	    dimension = numRanks;
	// Create the header.
	ostringstream gih;
	gih << brushName << "\n" << numCells << " ncells:" << numCells 
	    << " cellwidth:" << cellWidth << " cellheight:" << cellHeight 
	    << " step:" << spacing << " dim:" << dimension 
	    << " cols:1 rows:1 placement:" << placement;
	if (numRanks > 0)
	{
	    // Use rank specifications from the rank vector.
	    for (unsigned int i = 0; i < numRanks; i++)
	    {
	        GIHRankSpec r0 = (*ranks)[i];
	        gih << " rank" << i << ":" << r0.size << " sel" << i << ":" 
	            << r0.selection;
	    }
	} else
	{
	    // Use the default rank specification.
	    GIHRankSpec r0 = GIH_DEFAULT_RANK_SPEC;
	    gih << " rank0:" << numCells << " sel0:" << r0.selection;
	}
	/* <---- DEBUG ----- //
	ostringstream message;
	message << "Header: " << gih.str();
	log(IFLogMessage(message.str(), VL_DEBUG, this, "getGIHData"));
	// <---- DEBUG ----> */
	gih << '\n';
	// Create the brush frames.
	ImageSet frames;
	createArray(frames, cellWidth, cellHeight);
	if (frames.getNumImages() != numCells)
	{
	    ostringstream message;
	    message << "[Image::getGIHData] Unexpected number of frames "
	        "in array: " << frames.getNumImages() << " (expected: " 
	        << numCells << ")";
	    throw AltjiraError(message.str());
	}
	for (unsigned int i = 0; i < numCells; i++)
	{
	    Image* img0 = frames.getImage(i);
	    if (img0 == 0)
	        throw AltjiraError("[Image::getGIHData] Brush frame is null.");
	    ostringstream gbrName;
	    gbrName << setfill('0');
	    gbrName << brushName << " F#" << setw(8) << i;
	    std::string gbr0;
	    img0->getGBRData(gbr0, type, gbrName.str(), spacing, 
	        desaturationMethod);
	    gih << gbr0;
	}
	target = gih.str();
}

void Image::getGBRData(std::string& target, Ionflux::Altjira::ImageType 
type, const std::string& brushName, unsigned int spacing, 
Ionflux::Altjira::DesaturationMethod desaturationMethod)
{
	target.clear();
	uint32_t headerSize = 28 + brushName.size() + 1;
	uint32_t depth = 0;
	if (type == TYPE_GBR_GRAYSCALE)
	    depth = 1;
	else
	    depth = 4;
	pack(headerSize, target);
	pack(static_cast<uint32_t>(2), target);
	pack(static_cast<uint32_t>(width), target);
	pack(static_cast<uint32_t>(height), target);
	pack(static_cast<uint32_t>(depth), target);
	target.append("GIMP");
	pack(static_cast<uint32_t>(spacing), target);
	target.append(brushName);
	pack('\0', target);
	ByteColor p0;
	if (type == TYPE_GBR_GRAYSCALE)
	    if (desaturationMethod == DESATURATION_BY_LUMINANCE)
	        p0.space = Ionflux::Altjira::Color::SPACE_HSL;
	    else
	        p0.space = Ionflux::Altjira::Color::SPACE_HSV;
	else
	    p0.space = Ionflux::Altjira::Color::SPACE_RGB;
	for (unsigned int i = 0; i < height; i++)
	    for (unsigned int j = 0; j < width; j++)
	    {
	        getPixel(j, i, p0);
	        if (type == TYPE_GBR_GRAYSCALE)
	            pack(static_cast<unsigned char>(255 - p0.c2), target);
	        else
	        {
	            pack(p0.c0, target);
	            pack(p0.c1, target);
	            pack(p0.c2, target);
	            pack(p0.alpha, target);
	        }
	    }
}

bool Image::writeGBR(const std::string& fileName, 
Ionflux::Altjira::ImageType type, const std::string& brushName, unsigned 
int spacing, Ionflux::Altjira::DesaturationMethod desaturationMethod)
{
	ofstream f0;
	std::string buf;
	getGBRData(buf, type, brushName, spacing, desaturationMethod);
	f0.open(fileName.c_str(), ios_base::out);
	if (f0.fail())
	{
	    ostringstream message;
	    message << "[Image::writeGBR] Could not open file '" << fileName 
	        << "' for writing!";
	    throw AltjiraError(message.str());
	}
	f0 << buf;
	return true;
}

bool Image::writeGIH(const std::string& fileName, unsigned int cellWidth, 
unsigned int cellHeight, const Ionflux::Altjira::GIHRankSpecVector* ranks, 
const std::string& placement, Ionflux::Altjira::ImageType type, const 
std::string& brushName, unsigned int spacing, 
Ionflux::Altjira::DesaturationMethod desaturationMethod)
{
	ofstream f0;
	std::string buf;
	getGIHData(buf, cellWidth, cellHeight, ranks, placement, type, 
	    brushName, spacing, desaturationMethod);
	f0.open(fileName.c_str(), ios_base::out);
	if (f0.fail())
	{
	    ostringstream message;
	    message << "[Image::writeGIH] Could not open file '" 
	        << fileName << "' for writing!";
	    throw AltjiraError(message.str());
	}
	f0 << buf;
	return true;
}

bool Image::writeToFile(const std::string& fileName, 
Ionflux::Altjira::ImageType type, const std::string& brushName, unsigned 
int spacing, Ionflux::Altjira::DesaturationMethod desaturationMethod, 
unsigned int cellWidth, unsigned int cellHeight, const 
Ionflux::Altjira::GIHRankSpecVector* ranks, const std::string& placement)
{
	if (pixBuf == 0)
	    return false;
	std::string st;
	if (type == TYPE_PNG)
	    st = "png";
	else
	if (type == TYPE_JPEG)
	    st = "jpeg";
	else
	if ((type == TYPE_GBR_GRAYSCALE) 
	    || (type == TYPE_GBR_RGBA))
	    return writeGBR(fileName, type, brushName, spacing);
	else
	if ((type == TYPE_GIH_GRAYSCALE) 
	    || (type == TYPE_GIH_RGBA))
	    return writeGIH(fileName, cellWidth, cellHeight, ranks, 
	        placement, type, brushName, spacing);
	else
	    return false;
	bool result = gdk_pixbuf_save(pixBuf, fileName.c_str(), st.c_str(), 
	    0, NULL);
	if (!result)
	{
	    std::ostringstream status;
	    status << "[Image::writeToFile] Could not write to file '"
	        << fileName << "'!";
	    throw AltjiraError(status.str());
	}
	return result;
}

void Image::clear()
{
	if (pixBuf != 0)
	{
	    g_object_unref(pixBuf);
	    pixBuf = 0;
	}
}

bool Image::setPixel(unsigned int x, unsigned int y, const 
Ionflux::Altjira::ByteColor& color)
{
	if ((x < 0) && (x >= width))
	    return false;
	if ((y < 0) && (y >= height))
	    return false;
	if (numChannels < 3)
	    return false;
	ByteColor bc = color;
	toColorSpace(bc, colorSpace);
	PixelData p = pixels + y * rowStride + x * numChannels;
	p[0] = bc.c0;
	p[1] = bc.c1;
	p[2] = bc.c2;
	if (numChannels >= 4)
	    p[3] = bc.alpha;
	return true;
}

bool Image::setPixel(unsigned int x, unsigned int y, const 
Ionflux::Altjira::FloatColor& color)
{
	if ((x < 0) || (x >= width))
	    return false;
	if ((y < 0) || (y >= height))
	    return false;
	if (numChannels < 3)
	    return false;
	FloatColor fc = color;
	toColorSpace(fc, colorSpace);
	ByteColor bc;
	floatToByte(fc, bc);
	PixelData p = pixels + y * rowStride + x * numChannels;
	p[0] = bc.c0;
	p[1] = bc.c1;
	p[2] = bc.c2;
	if (numChannels >= 4)
	    p[3] = bc.alpha;
	return true;
}

bool Image::setPixel(unsigned int x, unsigned int y, const 
Ionflux::Altjira::Color& color)
{
	ByteColor bc;
	color.getByteColor(bc);
	setPixel(x, y, bc);
	return true;
}

bool Image::getPixel(unsigned int x, unsigned int y, 
Ionflux::Altjira::ByteColor& color)
{
	if ((x < 0) && (x >= width))
	    return false;
	if ((y < 0) || (y >= height))
	    return false;
	if (numChannels < 3)
	    return false;
	ColorSpace ts = color.space;
	PixelData p = pixels + y * rowStride + x * numChannels;
	color.c0 = p[0];
	color.c1 = p[1];
	color.c2 = p[2];
	if (numChannels >= 4)
	    color.alpha = p[3];
	else
	    color.alpha = 255;
	color.space = colorSpace;
	toColorSpace(color, ts);
	return true;
}

bool Image::getPixel(unsigned int x, unsigned int y, 
Ionflux::Altjira::FloatColor& color) const
{
	if ((x < 0) || (x >= width))
	    return false;
	if ((y < 0) || (y >= height))
	    return false;
	if (numChannels < 3)
	    return false;
	ColorSpace ts = color.space;
	PixelData p = pixels + y * rowStride + x * numChannels;
	color.c0 = byteToFloat(p[0]);
	color.c1 = byteToFloat(p[1]);
	color.c2 = byteToFloat(p[2]);
	if (numChannels >= 4)
	    color.alpha = byteToFloat(p[3]);
	else
	    color.alpha = 1.;
	color.space = colorSpace;
	toColorSpace(color, ts);
	return true;
}

bool Image::getPixel(unsigned int x, unsigned int y, 
Ionflux::Altjira::Color& color) const
{
	if ((x < 0) || (x >= width))
	    return false;
	if ((y < 0) || (y >= height))
	    return false;
	if (numChannels < 3)
	    return false;
	PixelData p = pixels + y * rowStride + x * numChannels;
	if (numChannels >= 4)
	    color.setComponents(p[0], p[1], p[2], p[3]);
	else
	    color.setComponents(p[0], p[1], p[2], 255);
	return true;
}

bool Image::fill(const Ionflux::Altjira::ByteColor& color)
{
	if (numChannels != 4)
	    throw AltjiraError("[Image::fill] "
	        "Operation requires four channels.");
	ByteColor bc = color;
	toColorSpace(bc, colorSpace);
	for (unsigned int x = 0; x < width; x++)
	    for (unsigned int y = 0; y < height; y++)
	    {
	        PixelData p = pixels + y * rowStride + x * numChannels;
	        p[0] = color.c0;
	        p[1] = color.c1;
	        p[2] = color.c2;
	        p[3] = color.alpha;
	    }
	return true;
}

bool Image::fill(const Ionflux::Altjira::FloatColor& color)
{
	ByteColor bc;
	floatToByte(color, bc);
	return fill(bc);;
}

bool Image::fill(const Ionflux::Altjira::Color& color)
{
	ByteColor bc;
	color.getByteColor(bc);
	return fill(bc);;
}

bool Image::fill(const Ionflux::Altjira::Image& other, const 
Ionflux::Altjira::ImageRect* sourceRect, unsigned int offsetX, unsigned int
offsetY)
{
	if (other.getNumChannels() != numChannels)
	{
	    std::ostringstream status;
	    status << "[Image::fill] Number of channels does not " 
	        "match in source and destination (source: " 
	        << other.getNumChannels() << ", dest = " << numChannels << ").";
	    throw AltjiraError(status.str());
	}
	ImageRect sr;
	if (sourceRect == 0)
	{
	    sr.x = 0;
	    sr.y = 0;
	    sr.width = other.getWidth();
	    sr.height = other.getHeight();
	} else
	{
	    sr = *sourceRect;
	    other.clamp(sr);
	}
	ImageRect tr;
	tr.x = offsetX;
	tr.y = offsetY;
	tr.width = sr.width;
	tr.height = sr.height;
	clamp(tr);
	/* <---- DEBUG ----- //
	cerr << "[Image.fill] DEBUG: sr = [" << sr.x << ", " << sr.y 
	    << ", " << sr.width << ", " << sr.height << "], tr = [" << tr.x 
	    << ", " << tr.y << ", " << tr.width << ", " << tr.height << "]" 
	    << endl;
	// <---- DEBUG ----- */
	unsigned int srcRowStride = other.getRowStride();
	unsigned int srcNumChannels = other.getNumChannels();
	unsigned int iMax = min(sr.width, tr.width);
	unsigned int jMax = min(sr.height, tr.height);
	PixelData sp = other.getPixels();
	PixelData tp = pixels;
	for (unsigned int i = 0; i < iMax; i++)
	    for (unsigned int j = 0; j < jMax; j++)
	    {
	        PixelData ps = sp + (sr.y + j) * srcRowStride 
	            + (sr.x + i) * srcNumChannels;
	        PixelData pt = tp + (tr.y + j) * rowStride 
	            + (tr.x + i) * numChannels;
	        pt[0] = ps[0];
	        pt[1] = ps[1];
	        pt[2] = ps[2];
	        pt[3] = ps[3];
	    }
	return true;;
}

bool Image::composite(const Ionflux::Altjira::Image& other, const 
Ionflux::Altjira::ColorBlender* blender, const Ionflux::Altjira::ImageRect*
sourceRect, unsigned int offsetX, unsigned int offsetY)
{
	if (other.getNumChannels() != numChannels)
	{
	    throw AltjiraError("[Image::composite] Number of channels does " 
	        "not match in source and destination.");
	}
	bool ownBlender = false;
	if (blender == 0)
	{
	    blender = BlendSrcOver::create();
	    ownBlender = true;
	}
	ImageRect sr;
	if (sourceRect == 0)
	{
	    sr.x = 0;
	    sr.y = 0;
	    sr.width = other.getWidth();
	    sr.height = other.getHeight();
	} else
	{
	    sr = *sourceRect;
	    other.clamp(sr);
	}
	ImageRect tr;
	tr.x = offsetX;
	tr.y = offsetY;
	tr.width = sr.width;
	tr.height = sr.height;
	clamp(tr);
	/* <---- DEBUG ----- //
	cerr << "[Image.composite] DEBUG: sr = [" << sr.x << ", " << sr.y 
	    << ", " << sr.width << ", " << sr.height << "], tr = [" << tr.x 
	    << ", " << tr.y << ", " << tr.width << ", " << tr.height << "]" 
	    << endl;
	// <---- DEBUG ----- */
	unsigned int srcRowStride = other.getRowStride();
	unsigned int srcNumChannels = other.getNumChannels();
	unsigned int iMax = min(sr.width, tr.width);
	unsigned int jMax = min(sr.height, tr.height);
	PixelData sp = other.getPixels();
	PixelData tp = pixels;
	ByteColor sc;
	ByteColor tc;
	ByteColor rc;
	sc.space = Color::SPACE_RGB;
	tc.space = Color::SPACE_RGB;
	rc.space = Color::SPACE_RGB;
	ByteColorValue so = floatToByte(blender->getSourceOpacity());
	ByteColorValue to = floatToByte(blender->getTargetOpacity());
	for (unsigned int i = 0; i < iMax; i++)
	    for (unsigned int j = 0; j < jMax; j++)
	    {
	        PixelData ps = sp + (sr.y + j) * srcRowStride 
	            + (sr.x + i) * srcNumChannels;
	        PixelData pt = tp + (tr.y + j) * rowStride 
	            + (tr.x + i) * numChannels;
	        sc.c0 = ps[0];
	        sc.c1 = ps[1];
	        sc.c2 = ps[2];
	        tc.c0 = pt[0];
	        tc.c1 = pt[1];
	        tc.c2 = pt[2];
	        if (numChannels >= 4)
	        {
	            sc.alpha = ps[3];
	            tc.alpha = pt[3];
	        } else
	        {
	            sc.alpha = 255;
	            tc.alpha = 255;
	        }
	        blender->blend(rc, sc, tc, so, to);
	        pt[0] = rc.c0;
	        pt[1] = rc.c1;
	        pt[2] = rc.c2;
	        if (numChannels >= 4)
	            pt[3] = rc.alpha;
	    }
	if (ownBlender)
	    delete blender;
	return true;;
}

void Image::createArray(Ionflux::Altjira::ImageSet& target, unsigned int 
cellWidth, unsigned int cellHeight) const
{
	unsigned int numCellsX = width / cellWidth;
	unsigned int numCellsY = height / cellHeight;
	ImageRect r0;
	r0.width = cellWidth;
	r0.height = cellHeight;
	for (unsigned int j = 0; j < numCellsY; j++)
	    for (unsigned int i = 0; i < numCellsX; i++)
	    {
	        r0.x = i * cellWidth;
	        r0.y = j * cellHeight;
	        Image* img0 = Image::create(cellWidth, cellHeight);
	        if (img0 == 0)
	            throw AltjiraError("[Image::createArray] "
	                "Could not allocate image!");
	        img0->fill(*this, &r0);
	        target.addImage(img0);
	    }
}

void Image::compositeArray(const Ionflux::Altjira::ImageSet& source, 
unsigned int cellWidth, unsigned int cellHeight, unsigned int numCols, 
unsigned int numRows, const Ionflux::Altjira::ColorBlender* blender, 
unsigned int offsetX, unsigned int offsetY)
{
	for (unsigned int j = 0; j < numRows; j++)
	    for (unsigned int i = 0; i < numCols; i++)
	    {
	        Image* img0 = source.getImage(j * numCols + i);
	        if (img0 == 0)
	            throw AltjiraError("[Image::compositeArray] "
	                "Source image is null!");
	        unsigned int x = offsetX + cellWidth * i;
	        unsigned int y = offsetY + cellHeight * j;
	        composite(*img0, blender, 0, x, y);
	    }
}

bool Image::convolveFill(const Ionflux::Altjira::Image& other, const 
Ionflux::Altjira::Matrix& matrix, const Ionflux::Altjira::ImageRect* 
sourceRect, unsigned int offsetX, unsigned int offsetY)
{
	if (other.getNumChannels() != numChannels)
	    return false;
	unsigned int sw = other.getWidth();
	unsigned int sh = other.getHeight();
	ImageRect sr;
	if (sourceRect == 0)
	{
	    sr.x = 0;
	    sr.y = 0;
	    sr.width = sw;
	    sr.height = sh;
	} else
	{
	    sr = *sourceRect;
	    other.clamp(sr);
	}
	ImageRect tr;
	tr.x = offsetX;
	tr.y = offsetY;
	tr.width = sr.width;
	tr.height = sr.height;
	clamp(tr);
	/* <---- DEBUG ----- //
	cerr << "[Image.convolveFill] DEBUG: sr = [" << sr.x << ", " << sr.y 
	    << ", " << sr.width << ", " << sr.height << "], tr = [" << tr.x 
	    << ", " << tr.y << ", " << tr.width << ", " << tr.height << "]" 
	    << endl;
	// <---- DEBUG ----- */
	unsigned int iMax = min(sr.width, tr.width);
	unsigned int jMax = min(sr.height, tr.height);
	unsigned int cols = matrix.getNumCols();
	unsigned int rows = matrix.getNumRows();
	unsigned int x0 = cols / 2;
	unsigned int y0 = rows / 2;
	FloatColor sc;
	sc.space = Color::SPACE_RGB;
	FloatColor tc;
	tc.space = Color::SPACE_RGB;
	for (unsigned int i = 0; i < iMax; i++)
	    for (unsigned int j = 0; j < jMax; j++)
	    {
	        tc.c0 = 0.;
	        tc.c1 = 0.;
	        tc.c2 = 0.;
	        tc.alpha = 0.;
	        for (unsigned int k = 0; k < rows; k++)
	            for (unsigned int l = 0; l < cols; l++)
	            {
	                int ci = sr.x + i - x0 + l;
	                int cj = sr.y + j - y0 + k;
	                if (ci < 0)
	                    ci = 0;
	                if (static_cast<unsigned int>(ci) >= sw)
	                    ci = sw - 1;
	                if (cj < 0)
	                    cj = 0;
	                if (static_cast<unsigned int>(cj) >= sh)
	                    cj = sh - 1;
	                other.getPixel(ci, cj, sc);
	                tc.c0 += (matrix.v(k, l) * sc.c0);
	                tc.c1 += (matrix.v(k, l) * sc.c1);
	                tc.c2 += (matrix.v(k, l) * sc.c2);
	                tc.alpha += (matrix.v(k, l) * sc.alpha);
	            }
	        setPixel(tr.x + i, tr.y + j, tc);
	    }
	return true;;
}

bool Image::setChannel(Ionflux::Altjira::Image& other, 
Ionflux::Altjira::ChannelID source, Ionflux::Altjira::ChannelID target, 
Ionflux::Mapping::Mapping* mapping, Ionflux::Altjira::ColorSpace 
sourceSpace, Ionflux::Altjira::ColorSpace targetSpace, const 
Ionflux::Altjira::ImageRect* sourceRect, unsigned int offsetX, unsigned int
offsetY)
{
	if (other.getNumChannels() != numChannels)
	    return false;
	unsigned int sw = other.getWidth();
	unsigned int sh = other.getHeight();
	ImageRect sr;
	if (sourceRect == 0)
	{
	    sr.x = 0;
	    sr.y = 0;
	    sr.width = sw;
	    sr.height = sh;
	} else
	{
	    sr = *sourceRect;
	    other.clamp(sr);
	}
	ImageRect tr;
	tr.x = offsetX;
	tr.y = offsetY;
	tr.width = sr.width;
	tr.height = sr.height;
	clamp(tr);
	/* <---- DEBUG ----- //
	cerr << "[Image.setChannel] DEBUG: sr = [" << sr.x << ", " << sr.y 
	    << ", " << sr.width << ", " << sr.height << "], tr = [" << tr.x 
	    << ", " << tr.y << ", " << tr.width << ", " << tr.height << "]" 
	    << endl;
	// <---- DEBUG ----- */
	unsigned int iMax = min(sr.width, tr.width);
	unsigned int jMax = min(sr.height, tr.height);
	ByteColor sc;
	sc.space = getColorSpaceForChannel(source, sourceSpace);
	ByteColor tc;
	tc.space = getColorSpaceForChannel(target, targetSpace);
	for (unsigned int i = 0; i < iMax; i++)
	    for (unsigned int j = 0; j < jMax; j++)
	    {
	        other.getPixel(sr.x + i, sr.y + j, sc);
	        getPixel(tr.x + i, tr.y + j, tc);
	        ByteColorValue v0 = getComponent(sc, source);
	        if (mapping != 0)
	            v0 = floatToByte((*mapping)(byteToFloat(v0)));
	        setComponent(tc, target, v0);
	        setPixel(tr.x + i, tr.y + j, tc);
	    }
	return true;;
}

bool Image::mask(Ionflux::Altjira::Image& other, 
Ionflux::Altjira::ChannelID source, Ionflux::Mapping::Mapping* mapping, 
Ionflux::Altjira::ColorSpace sourceSpace, const 
Ionflux::Altjira::ImageRect* sourceRect, unsigned int offsetX, unsigned int
offsetY)
{
	if (other.getNumChannels() != numChannels)
	    return false;
	unsigned int sw = other.getWidth();
	unsigned int sh = other.getHeight();
	ImageRect sr;
	if (sourceRect == 0)
	{
	    sr.x = 0;
	    sr.y = 0;
	    sr.width = sw;
	    sr.height = sh;
	} else
	{
	    sr = *sourceRect;
	    other.clamp(sr);
	}
	ImageRect tr;
	tr.x = offsetX;
	tr.y = offsetY;
	tr.width = sr.width;
	tr.height = sr.height;
	clamp(tr);
	/* <---- DEBUG ----- //
	cerr << "[Image.mask] DEBUG: sr = [" << sr.x << ", " << sr.y 
	    << ", " << sr.width << ", " << sr.height << "], tr = [" << tr.x 
	    << ", " << tr.y << ", " << tr.width << ", " << tr.height << "]" 
	    << endl;
	// <---- DEBUG ----- */
	unsigned int iMax = min(sr.width, tr.width);
	unsigned int jMax = min(sr.height, tr.height);
	ByteColor sc;
	sc.space = getColorSpaceForChannel(source, sourceSpace);
	ByteColor tc;
	tc.space = Color::SPACE_RGB;
	for (unsigned int i = 0; i < iMax; i++)
	    for (unsigned int j = 0; j < jMax; j++)
	    {
	        other.getPixel(sr.x + i, sr.y + j, sc);
	        getPixel(tr.x + i, tr.y + j, tc);
	        ByteColorValue v0 = getComponent(sc, source);
	        if (mapping != 0)
	            v0 = floatToByte((*mapping)(byteToFloat(v0)));
	        tc.alpha = lutMult(v0, tc.alpha);
	        setPixel(tr.x + i, tr.y + j, tc);
	    }
	return true;;
}

void Image::valuesToColor(Ionflux::Altjira::ColorBand& colors)
{
	if (numChannels != 4)
	    throw AltjiraError("[Image::valuesToColor] "
	        "Operation requires four channels.");
	ByteColor sc;
	ByteColor tc;
	tc.space = Ionflux::Altjira::Color::SPACE_RGB;
	for (unsigned int x = 0; x < width; x++)
	    for (unsigned int y = 0; y < height; y++)
	    {
	        PixelData p = pixels + y * rowStride + x * numChannels;
	        sc.c0 = p[0];
	        sc.c1 = p[1];
	        sc.c2 = p[2];
	        sc.alpha = p[3];
	        sc.space = Ionflux::Altjira::Color::SPACE_RGB;
	        toColorSpace(sc, Ionflux::Altjira::Color::SPACE_HSV);
	        colors.eval(byteToFloat(sc.c2), tc);
	        p[0] = tc.c0;
	        p[1] = tc.c1;
	        p[2] = tc.c2;
	        p[3] = tc.alpha;
	    }
}

void Image::colorToAlpha(const Ionflux::Altjira::Color& color)
{
	FloatColor rc;
	rc.space = Ionflux::Altjira::Color::SPACE_RGB;
	color.getFloatColor(rc);
	FloatColor sc;
	sc.space = Ionflux::Altjira::Color::SPACE_RGB;
	for (unsigned int x = 0; x < width; x++)
	    for (unsigned int y = 0; y < height; y++)
	    {
	        getPixel(x, y, sc);
	        Ionflux::Altjira::colorToAlpha(sc, rc);
	        setPixel(x, y, sc);
	    }
}

void Image::luminize(const Ionflux::Altjira::Image& source, double amount)
{
	// Luminance blender.
	BlendChannel bl0;
	bl0.setSrcChannel(CH_LUMINANCE);
	bl0.setDestChannel(CH_LUMINANCE);
	bl0.setSourceOpacity(amount);
	bl0.setTargetOpacity(1. - amount);
	/* Saturation blender.
	   Used so we get a valid saturation for high luminance areas. */
	BlendChannel bl1;
	bl1.setSrcChannel(CH_SATURATION);
	bl1.setDestChannel(CH_SATURATION);
	bl1.setSrcSpace(Color::SPACE_HSV);
	bl1.setDestSpace(Color::SPACE_HSL);
	bl1.setSourceOpacity(amount);
	bl1.setTargetOpacity(1. - amount);
	// Make a copy of the original to save the saturation information.
	Image sat(*this);
	composite(source, &bl0);
	composite(sat, &bl1);
}

bool Image::hasAlpha() const
{
	// TODO: Implementation.
	return alphaFlag;
}

void Image::clamp(Ionflux::Altjira::ImageRect& r0) const
{
	Ionflux::Mapping::Range xRange = { 0, static_cast<double>(width) };
	Ionflux::Mapping::Range yRange = { 0, static_cast<double>(height) };
	unsigned int ex = Ionflux::Mapping::clamp(r0.x + r0.width, xRange);
	unsigned int ey = Ionflux::Mapping::clamp(r0.y + r0.height, yRange);
	if (ex < r0.x)
	    r0.width = 0;
	else
	    r0.width = ex - r0.x;
	if (ey < r0.y)
	    r0.height = 0;
	else
	    r0.height = ey - r0.y;
}

void Image::getRandomPoints(unsigned int numPoints, 
Ionflux::Mapping::PointSet& target, unsigned int maxIters) const
{
	FloatColor c0;
	c0.space = Ionflux::Altjira::Color::SPACE_HSV;
	unsigned int pointsOK = 0;
	unsigned int maxItersP = maxIters * numPoints;
	unsigned int i = 0;
	while ((pointsOK < numPoints) 
	    && (i <= maxItersP))
	{
	    Ionflux::Mapping::Point p0 = Ionflux::Mapping::getRandomPointExc();
	    getPixel(static_cast<unsigned int>(p0.getX() * width), 
	        static_cast<unsigned int>(p0.getY() * height), c0);
	    if (p0.getZ() <= c0.c2)
	    {
	        p0.setZ(0.);
	        target.addPoint(p0.copy());
	        pointsOK++;
	    }
	    i++;
	}
	if (pointsOK < numPoints)
	    throw AltjiraError("[Image::getRandomPoints] "
	        "Maximum number of iterations exceeded!");
}

void Image::getColorDifference(const Ionflux::Altjira::Color& refColor, 
Ionflux::Altjira::Image& targetImage, Ionflux::Mapping::Mapping* mapping) 
const
{
	unsigned int iMax = min(width, targetImage.width);
	unsigned int jMax = min(height, targetImage.height);
	Color pixel;
	Color diffColor(Color::WHITE);
	
	for (unsigned int i = 0; i < iMax; i++)
	{
		for (unsigned int j = 0; j < jMax; j++)
		{
			getPixel(i, j, pixel);
			double diff = pixel.getMeanSquaredError(refColor);
			if (mapping != 0)
				diff = Ionflux::Mapping::clamp(mapping->call(diff));
			diffColor.setComponents(diff, diff, diff, 1.);
			targetImage.setPixel(i, j, diffColor);
		}
	}
}

void Image::getChannel(Ionflux::Altjira::ChannelID channel, 
Ionflux::Altjira::Matrix& target, Ionflux::Altjira::ColorSpace colorSpace) 
const
{
	unsigned int iMax = min(width, target.getNumCols());
	unsigned int jMax = min(height, target.getNumRows());
	FloatColor pixel;
	pixel.space = getColorSpaceForChannel(channel, colorSpace);
	for (unsigned int i = 0; i < iMax; i++)
	{
		for (unsigned int j = 0; j < jMax; j++)
		{
			getPixel(i, j, pixel);
			double chValue = getComponent(pixel, channel);
			target.setValue(j, i, chValue);
		}
	}
}

Ionflux::ObjectBase::UInt64 Image::getSize() const
{
	// TODO: Implementation.
	return width * height * bitsPerSample * numChannels / 8;
}

std::string Image::getString() const
{
	ostringstream state;
	state << getClassName() << "[" << width << " x " << height 
	    << " px, " << numChannels << " ch, " << bitsPerSample << " bps]";
	return state.str();
}

Ionflux::Altjira::Image* Image::create(unsigned int initWidth, unsigned int
initHeight, bool initAlpha, unsigned int initBitsPerSample, 
Ionflux::Altjira::ColorSpace initColorSpace)
{
	Image* result = create();
	result->createNewData(initWidth, initHeight, initAlpha, 
	    initBitsPerSample, initColorSpace);
	return result;
}

unsigned int Image::getNumChannels() const
{
    return numChannels;
}

unsigned int Image::getBitsPerSample() const
{
    return bitsPerSample;
}

Ionflux::Altjira::ColorSpace Image::getColorSpace() const
{
    return colorSpace;
}

unsigned int Image::getWidth() const
{
    return width;
}

unsigned int Image::getHeight() const
{
    return height;
}

unsigned int Image::getRowStride() const
{
    return rowStride;
}

Ionflux::Altjira::PixelData Image::getPixels() const
{
    return pixels;
}

Ionflux::Altjira::Image& Image::operator=(const Ionflux::Altjira::Image& 
other)
{
    createNewData(other.getWidth(), other.getHeight(), 
        other.hasAlpha(), other.getBitsPerSample(), other.getColorSpace());
    fill(other);
	return *this;
}

Ionflux::Altjira::Image* Image::copy() const
{
    Image* newImage = create();
    *newImage = *this;
    return newImage;
}

Ionflux::Altjira::Image* Image::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Image*>(other);
}

Ionflux::Altjira::Image* Image::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Image* newObject = new Image();
    if (newObject == 0)
    {
        throw AltjiraError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Image::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Image.cpp
 * \brief Image implementation.
 */
