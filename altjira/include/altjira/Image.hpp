#ifndef IONFLUX_ALTJIRA_IMAGE
#define IONFLUX_ALTJIRA_IMAGE
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Image.hpp                       Image (header).
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

#include "ifmapping/Mapping.hpp"
#include "ifmapping/PointSet.hpp"
#include "ifmapping/Matrix.hpp"
#include "altjira/Color.hpp"
#include "altjira/constants.hpp"
#include "altjira/ColorBlender.hpp"
#include "altjira/ColorBand.hpp"
#include <climits>
#include "altjira/PixelSource.hpp"

namespace Ionflux
{

namespace Altjira
{

class ImageSet;

/// Class information for class Image.
class ImageClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ImageClassInfo();
		/// Destructor.
		virtual ~ImageClassInfo();
};

/** Image.
 * \ingroup altjira
 *
 * An image.
 */
class Image
: public Ionflux::Altjira::PixelSource
{
	private:
		
	protected:
		/// GdkPixBuf structure for internal use.
		GdkPixbuf* pixBuf;
		/// Alpha flag.
		bool alphaFlag;
		/// Number of channels.
		unsigned int numChannels;
		/// Bits per sample.
		unsigned int bitsPerSample;
		/// Color space.
		Ionflux::Altjira::ColorSpace colorSpace;
		/// Width.
		unsigned int width;
		/// Height.
		unsigned int height;
		/// Row stride.
		unsigned int rowStride;
		/// Pixels.
		Ionflux::Altjira::PixelData pixels;
		
		/** Update image data.
		 *
		 * Update the image data.
		 */
		virtual void update();
		
	public:
		/// Image type: PNG.
		static const Ionflux::Altjira::ImageType TYPE_PNG;
		/// Image type: JPEG.
		static const Ionflux::Altjira::ImageType TYPE_JPEG;
		/// Image type: Gimp Brush (GBR, grayscale).
		static const Ionflux::Altjira::ImageType TYPE_GBR_GRAYSCALE;
		/// Image type: Gimp Brush (GBR, RGBA).
		static const Ionflux::Altjira::ImageType TYPE_GBR_RGBA;
		/// Image type: Gimp Brush Pipe (GIH, grayscale).
		static const Ionflux::Altjira::ImageType TYPE_GIH_GRAYSCALE;
		/// Image type: Gimp Brush Pipe (GIH, RGBA).
		static const Ionflux::Altjira::ImageType TYPE_GIH_RGBA;
		/// GIMP GIH default placement.
		static const std::string GIH_DEFAULT_PLACEMENT;
		/// GIMP GIH maximum cell size.
		static const unsigned int GIH_CELL_SIZE_MAX;
		/// GIMP GIH default cell width.
		static const unsigned int GIH_DEFAULT_CELL_WIDTH;
		/// GIMP GIH default cell height.
		static const unsigned int GIH_DEFAULT_CELL_HEIGHT;
		/// Class information instance.
		static const ImageClassInfo imageClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 */
		Image();
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 *
		 * \param other Other object.
		 */
		Image(const Ionflux::Altjira::Image& other);
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 *
		 * \param fileName File name of an image to be loaded.
		 */
		Image(const std::string& fileName);
		
		/** Constructor.
		 *
		 * Construct new Image object.
		 *
		 * \param initWidth Width.
		 * \param initHeight Height.
		 * \param initAlpha Create alpha channel.
		 * \param initBitsPerSample Bits pers sample.
		 * \param initColorSpace Color space.
		 */
		Image(unsigned int initWidth, unsigned int initHeight, bool initAlpha = 
		true, unsigned int initBitsPerSample = 8, Ionflux::Altjira::ColorSpace 
		initColorSpace = Ionflux::Altjira::Color::SPACE_RGB);
		
		/** Destructor.
		 *
		 * Destruct Image object.
		 */
		virtual ~Image();
		
		/** Create new image data.
		 *
		 * Create new image data.
		 *
		 * \param initWidth Width.
		 * \param initHeight Height.
		 * \param initAlpha Create alpha channel.
		 * \param initBitsPerSample Bits pers sample.
		 * \param initColorSpace Color space.
		 */
		virtual void createNewData(unsigned int initWidth, unsigned int 
		initHeight, bool initAlpha = true, unsigned int initBitsPerSample = 8, 
		Ionflux::Altjira::ColorSpace initColorSpace = 
		Ionflux::Altjira::Color::SPACE_RGB);
		
		/** Load image from file.
		 *
		 * Load an image from a file.
		 *
		 * \param fileName File name.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool loadFromFile(const std::string& fileName);
		
		/** Get GIMP brush data (GIH).
		 *
		 * Convert the image data to the GIMP brush pipe (GIH) format.
		 *
		 * \param target Where to store the GIH data.
		 * \param cellWidth Cell width.
		 * \param cellHeight Cell height.
		 * \param ranks Rank specification.
		 * \param placement Placement.
		 * \param type Image type.
		 * \param brushName Brush name.
		 * \param spacing Brush spacing.
		 * \param desaturationMethod Desaturation method (used for the GBR 
		 * grayscale format).
		 */
		virtual void getGIHData(std::string& target, unsigned int cellWidth = 
		GIH_DEFAULT_CELL_WIDTH, unsigned int cellHeight = 
		GIH_DEFAULT_CELL_HEIGHT, const Ionflux::Altjira::GIHRankSpecVector* ranks
		= 0, const std::string& placement = 
		Ionflux::Altjira::Image::GIH_DEFAULT_PLACEMENT, 
		Ionflux::Altjira::ImageType type = 
		Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& brushName
		= Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int spacing = 
		Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
		Ionflux::Altjira::DesaturationMethod desaturationMethod = 
		Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
		
		/** Get GIMP brush data (GBR).
		 *
		 * Convert the image data to the GIMP brush (GBR) format.
		 *
		 * \param target Where to store the GBR data.
		 * \param type Image type.
		 * \param brushName Brush name.
		 * \param spacing Brush spacing.
		 * \param desaturationMethod Desaturation method (used for the GBR 
		 * grayscale format).
		 */
		virtual void getGBRData(std::string& target, Ionflux::Altjira::ImageType 
		type = Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& 
		brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int spacing = 
		Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
		Ionflux::Altjira::DesaturationMethod desaturationMethod = 
		Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
		
		/** Write to gimp brush (GBR).
		 *
		 * Write the image to a gimp brush file.
		 *
		 * \param fileName File name.
		 * \param type Image type.
		 * \param brushName Brush name (used for the GBR format).
		 * \param spacing Brush spacing (used for the GBR format).
		 * \param desaturationMethod Desaturation method (used for the GBR 
		 * grayscale format).
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool writeGBR(const std::string& fileName, 
		Ionflux::Altjira::ImageType type = 
		Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& brushName
		= Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int spacing = 
		Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
		Ionflux::Altjira::DesaturationMethod desaturationMethod = 
		Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
		
		/** Write to gimp brush pipe (GIH).
		 *
		 * Write the image to a gimp brush pipe file.
		 *
		 * \param fileName File name.
		 * \param cellWidth Cell width.
		 * \param cellHeight Cell height.
		 * \param ranks Rank specification.
		 * \param placement Placement.
		 * \param type Image type.
		 * \param brushName Brush name.
		 * \param spacing Brush spacing (used for the GBR format).
		 * \param desaturationMethod Desaturation method (used for the GBR 
		 * grayscale format).
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool writeGIH(const std::string& fileName, unsigned int cellWidth
		= GIH_DEFAULT_CELL_WIDTH, unsigned int cellHeight = 
		GIH_DEFAULT_CELL_HEIGHT, const Ionflux::Altjira::GIHRankSpecVector* ranks
		= 0, const std::string& placement = 
		Ionflux::Altjira::Image::GIH_DEFAULT_PLACEMENT, 
		Ionflux::Altjira::ImageType type = 
		Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& brushName
		= Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int spacing = 
		Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
		Ionflux::Altjira::DesaturationMethod desaturationMethod = 
		Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
		
		/** Write image to file.
		 *
		 * Write the image to a file.
		 *
		 * \param fileName File name.
		 * \param type Image type.
		 * \param brushName Brush name (used for the GBR format).
		 * \param spacing Brush spacing (used for the GBR format).
		 * \param desaturationMethod Desaturation method (used for the GBR 
		 * grayscale format).
		 * \param cellWidth Cell width (used for the GIH format).
		 * \param cellHeight Cell height (used for the GIH format).
		 * \param ranks Rank specification (used for the GIH format).
		 * \param placement Placement (used for the GIH format).
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool writeToFile(const std::string& fileName, 
		Ionflux::Altjira::ImageType type = Ionflux::Altjira::Image::TYPE_PNG, 
		const std::string& brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, 
		unsigned int spacing = Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
		Ionflux::Altjira::DesaturationMethod desaturationMethod = 
		Ionflux::Altjira::DEFAULT_DESATURATION_METHOD, unsigned int cellWidth = 
		GIH_DEFAULT_CELL_WIDTH, unsigned int cellHeight = 
		GIH_DEFAULT_CELL_HEIGHT, const Ionflux::Altjira::GIHRankSpecVector* ranks
		= 0, const std::string& placement = 
		Ionflux::Altjira::Image::GIH_DEFAULT_PLACEMENT);
		
		/** Clear image.
		 *
		 * Remove all data from the image.
		 */
		virtual void clear();
		
		/** Set pixel color.
		 *
		 * Set a pixel to a color value.
		 *
		 * \param x Pixel coordinate (X).
		 * \param y Pixel coordinate (Y).
		 * \param color Color.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setPixel(unsigned int x, unsigned int y, const 
		Ionflux::Altjira::ByteColor& color);
		
		/** Set pixel color.
		 *
		 * Set a pixel to a color value.
		 *
		 * \param x Pixel coordinate (X).
		 * \param y Pixel coordinate (Y).
		 * \param color Color.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setPixel(unsigned int x, unsigned int y, const 
		Ionflux::Altjira::FloatColor& color);
		
		/** Set pixel color.
		 *
		 * Set a pixel to a color value.
		 *
		 * \param x Pixel coordinate (X).
		 * \param y Pixel coordinate (Y).
		 * \param color Color.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setPixel(unsigned int x, unsigned int y, const 
		Ionflux::Altjira::Color& color);
		
		/** Get pixel color.
		 *
		 * Get pixel color.
		 *
		 * \param x Pixel coordinate (X).
		 * \param y Pixel coordinate (Y).
		 * \param color Color.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool getPixel(unsigned int x, unsigned int y, 
		Ionflux::Altjira::ByteColor& color) const;
		
		/** Get pixel color.
		 *
		 * Get pixel color.
		 *
		 * \param x Pixel coordinate (X).
		 * \param y Pixel coordinate (Y).
		 * \param color Color.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool getPixel(unsigned int x, unsigned int y, 
		Ionflux::Altjira::FloatColor& color) const;
		
		/** Get pixel color.
		 *
		 * Get pixel color.
		 *
		 * \param x Pixel coordinate (X).
		 * \param y Pixel coordinate (Y).
		 * \param color Color.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool getPixel(unsigned int x, unsigned int y, 
		Ionflux::Altjira::Color& color) const;
		
		/** Fill.
		 *
		 * Fill the image with a color.
		 *
		 * \param color Color.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fill(const Ionflux::Altjira::ByteColor& color);
		
		/** Fill.
		 *
		 * Fill the image with a color.
		 *
		 * \param color Color.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fill(const Ionflux::Altjira::FloatColor& color);
		
		/** Fill.
		 *
		 * Fill the image with a color.
		 *
		 * \param color Color.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fill(const Ionflux::Altjira::Color& color);
		
		/** Fill.
		 *
		 * Fill the image using another image as the source.
		 *
		 * \param other Image.
		 * \param sourceRect Source rectangle.
		 * \param offsetX Target offset for filling (X).
		 * \param offsetY Target offset for filling (Y).
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fill(const Ionflux::Altjira::Image& other, const 
		Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX = 0, 
		unsigned int offsetY = 0);
		
		/** Composite.
		 *
		 * Composite another image to this image.
		 *
		 * \param other Image.
		 * \param blender Color blender.
		 * \param sourceRect Source rectangle.
		 * \param offsetX Target offset for compositing (X).
		 * \param offsetY Target offset for compositing (Y).
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool composite(const Ionflux::Altjira::Image& other, const 
		Ionflux::Altjira::ColorBlender* blender = 0, const 
		Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX = 0, 
		unsigned int offsetY = 0);
		
		/** Create image array.
		 *
		 * Create an array of images from this image. This is the inverse 
		 * operation of compositeArray().
		 *
		 * \param target Where to store the resulting images.
		 * \param cellWidth Cell width.
		 * \param cellHeight Cell height.
		 */
		virtual void createArray(Ionflux::Altjira::ImageSet& target, unsigned int
		cellWidth, unsigned int cellHeight) const;
		
		/** Composite image array.
		 *
		 * Composite an array of images onto the image. This is the inverse 
		 * operation to createArray().
		 *
		 * \param source Source images.
		 * \param cellWidth Cell width.
		 * \param cellHeight Cell height.
		 * \param numCols Number of columns.
		 * \param numRows Number of rows.
		 * \param blender Color blender.
		 * \param offsetX Target offset for compositing (X).
		 * \param offsetY Target offset for compositing (Y).
		 */
		virtual void compositeArray(const Ionflux::Altjira::ImageSet& source, 
		unsigned int cellWidth, unsigned int cellHeight, unsigned int numCols, 
		unsigned int numRows, const Ionflux::Altjira::ColorBlender* blender = 0, 
		unsigned int offsetX = 0, unsigned int offsetY = 0);
		
		/** Convolve fill.
		 *
		 * Fill the image using a convolution of the source image.
		 *
		 * \param other Image.
		 * \param matrix Convolution matrix.
		 * \param sourceRect Source rectangle.
		 * \param offsetX Target offset for filling (X).
		 * \param offsetY Target offset for filling (Y).
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool convolveFill(const Ionflux::Altjira::Image& other, const 
		Ionflux::Mapping::Matrix& matrix, const Ionflux::Altjira::ImageRect* 
		sourceRect = 0, unsigned int offsetX = 0, unsigned int offsetY = 0);
		
		/** Set channel.
		 *
		 * Set a channel of an image area to the value of a channel of another
		 * image area. The function will try to determine the source and 
		 * target color space automatically from the channels. If the channel 
		 * specification is ambiguous (such as hue and saturation, which occur
		 * in both HSV and HSL color space, or alpha, which occurs in all 
		 * color spaces), the optional source and target spaces will be used. 
		 * Otherwise, a default space will be selected.
		 *
		 * \param other Image.
		 * \param source Source Channel.
		 * \param target Target Channel.
		 * \param mapping Source channel mapping.
		 * \param sourceSpace Source color space.
		 * \param targetSpace Target color space.
		 * \param sourceRect Source rectangle.
		 * \param offsetX Target offset for filling (X).
		 * \param offsetY Target offset for filling (Y).
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setChannel(const Ionflux::Altjira::Image& other, 
		Ionflux::Altjira::ChannelID source, Ionflux::Altjira::ChannelID target, 
		Ionflux::Mapping::Mapping* mapping = 0, Ionflux::Altjira::ColorSpace 
		sourceSpace = Ionflux::Altjira::Color::SPACE_UNDEFINED, 
		Ionflux::Altjira::ColorSpace targetSpace = 
		Ionflux::Altjira::Color::SPACE_UNDEFINED, const 
		Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX = 0, 
		unsigned int offsetY = 0);
		
		/** Set channel.
		 *
		 * Set a channel of an image area to the value of a matrix area. The 
		 * function will try to determine the target color space automatically
		 * from the channel. The specified target color space will be used as 
		 * a hint.
		 *
		 * \param matrix Matrix.
		 * \param targetChannel Target Channel.
		 * \param mapping Channel mapping.
		 * \param sourceRect Source rectangle.
		 * \param offsetX Target offset for filling (X).
		 * \param offsetY Target offset for filling (Y).
		 * \param targetSpace Target color space.
		 */
		virtual void setChannel(const Ionflux::Mapping::Matrix& matrix, 
		Ionflux::Altjira::ChannelID targetChannel, Ionflux::Mapping::Mapping* 
		mapping = 0, const Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned 
		int offsetX = 0, unsigned int offsetY = 0, Ionflux::Altjira::ColorSpace 
		targetSpace = Ionflux::Altjira::Color::SPACE_HSV);
		
		/** Apply alpha mask.
		 *
		 * Apply an alpha mask, specified by the source channel of the other 
		 * image, to the image.
		 *
		 * \param other Image.
		 * \param source Source Channel.
		 * \param mapping Source channel mapping.
		 * \param sourceSpace Source color space.
		 * \param sourceRect Source rectangle.
		 * \param offsetX Target offset for filling (X).
		 * \param offsetY Target offset for filling (Y).
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool mask(Ionflux::Altjira::Image& other, 
		Ionflux::Altjira::ChannelID source = Ionflux::Altjira::CH_VALUE, 
		Ionflux::Mapping::Mapping* mapping = 0, Ionflux::Altjira::ColorSpace 
		sourceSpace = Ionflux::Altjira::Color::SPACE_HSV, const 
		Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX = 0, 
		unsigned int offsetY = 0);
		
		/** Transform values to colors.
		 *
		 * Transform the values in the image to colors set by a color band.
		 *
		 * \param colors Color band..
		 */
		virtual void valuesToColor(Ionflux::Altjira::ColorBand& colors);
		
		/** Color to alpha.
		 *
		 * Replace a reference color by transparency.
		 *
		 * \param color Color..
		 */
		virtual void colorToAlpha(const Ionflux::Altjira::Color& color);
		
		/** Luminize.
		 *
		 * Apply the luminance of the source image to the image, keeping hue 
		 * and saturation information of the original image.
		 *
		 * \param source Source image..
		 * \param amount Effect strength..
		 */
		virtual void luminize(const Ionflux::Altjira::Image& source, double 
		amount = 1.);
		
		/** Check alpha channel.
		 *
		 * Check whether the image has an alpha channel.
		 *
		 * \return \c true if the image has an alpha channel, \c false otherwise.
		 */
		virtual bool hasAlpha() const;
		
		/** Clamp rectangle.
		 *
		 * Clamp a rectangle to the image boundaries. If the rectangle lies 
		 * outside the image boundaries, its width and height will be set to 
		 * 0.
		 *
		 * \param r0 Rectangle.
		 */
		virtual void clamp(Ionflux::Altjira::ImageRect& r0) const;
		
		/** Get random points.
		 *
		 * Get random points sampled from the image. The value channel of the 
		 * image is used as a two-dimensional random distribution and the 
		 * specified number of points are sampled from this distribution and 
		 * stored in the target point set.
		 *
		 * \param numPoints Number of points.
		 * \param target Target point set.
		 * \param maxIters Average maximum number of iterations per point.
		 */
		virtual void getRandomPoints(unsigned int numPoints, 
		Ionflux::Mapping::PointSet& target, unsigned int maxIters = 100) const;
		
		/** Get color difference.
		 *
		 * Calculate the difference of image pixels compared to a reference 
		 * color and store the result in the target image.
		 *
		 * \param refColor Reference color.
		 * \param targetImage Target image.
		 * \param mapping Result mapping.
		 */
		virtual void getColorDifference(const Ionflux::Altjira::Color& refColor, 
		Ionflux::Altjira::Image& targetImage, Ionflux::Mapping::Mapping* mapping 
		= 0) const;
		
		/** Get channel.
		 *
		 * Extract an image channel. The channel data will be stored in the 
		 * target matrix.
		 * 
		 * The optional \c colorSpace parameter is used as a hint for 
		 * extracting the channel.
		 *
		 * \param channel Channel.
		 * \param target Target matrix.
		 * \param colorSpace Color space.
		 */
		virtual void getChannel(Ionflux::Altjira::ChannelID channel, 
		Ionflux::Mapping::Matrix& target, Ionflux::Altjira::ColorSpace colorSpace
		= Ionflux::Altjira::Color::SPACE_HSV) const;
		
		/** Get size.
		 *
		 * Get the size of the image (in bytes).
		 *
		 * \return Size of the image.
		 */
		virtual Ionflux::ObjectBase::UInt64 getSize() const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::Image& operator=(const Ionflux::Altjira::Image&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::Image* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::Image* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::Altjira::Image* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Image object.
		 *
		 * \param fileName File name of an image to be loaded.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::Image* create(const std::string& fileName, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Image object.
		 *
		 * \param initWidth Width.
		 * \param initHeight Height.
		 * \param initAlpha Create alpha channel.
		 * \param initBitsPerSample Bits pers sample.
		 * \param initColorSpace Color space.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::Image* create(unsigned int initWidth, unsigned 
		int initHeight, bool initAlpha = true, unsigned int initBitsPerSample = 
		8, Ionflux::Altjira::ColorSpace initColorSpace = 
		Ionflux::Altjira::Color::SPACE_RGB, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of channels.
		 *
		 * \return Current value of number of channels.
		 */
		virtual unsigned int getNumChannels() const;
		
		/** Get bits per sample.
		 *
		 * \return Current value of bits per sample.
		 */
		virtual unsigned int getBitsPerSample() const;
		
		/** Get color space.
		 *
		 * \return Current value of color space.
		 */
		virtual Ionflux::Altjira::ColorSpace getColorSpace() const;
		
		/** Get width.
		 *
		 * \return Current value of width.
		 */
		virtual unsigned int getWidth() const;
		
		/** Get height.
		 *
		 * \return Current value of height.
		 */
		virtual unsigned int getHeight() const;
		
		/** Get row stride.
		 *
		 * \return Current value of row stride.
		 */
		virtual unsigned int getRowStride() const;
		
		/** Get pixels.
		 *
		 * \return Current value of pixels.
		 */
		virtual Ionflux::Altjira::PixelData getPixels() const;
};

}

}

/** \file Image.hpp
 * \brief Image (header).
 */
#endif
