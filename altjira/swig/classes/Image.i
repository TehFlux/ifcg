/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Image.i                         Image (interface).
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
%{
#include "altjira/Image.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class ImageSet;

class ImageClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageClassInfo();
        virtual ~ImageClassInfo();
};

class Image
: public Ionflux::Altjira::PixelSource
{
    public:
		static const Ionflux::Altjira::ImageType TYPE_PNG;
		static const Ionflux::Altjira::ImageType TYPE_JPEG;
		static const Ionflux::Altjira::ImageType TYPE_GBR_GRAYSCALE;
		static const Ionflux::Altjira::ImageType TYPE_GBR_RGBA;
		static const Ionflux::Altjira::ImageType TYPE_GIH_GRAYSCALE;
		static const Ionflux::Altjira::ImageType TYPE_GIH_RGBA;
		static const std::string GIH_DEFAULT_PLACEMENT;
		static const unsigned int GIH_CELL_SIZE_MAX;
		static const unsigned int GIH_DEFAULT_CELL_WIDTH;
		static const unsigned int GIH_DEFAULT_CELL_HEIGHT;
        
        Image();
		Image(const Ionflux::Altjira::Image& other);
        Image(const std::string& fileName);
        Image(unsigned int initWidth, unsigned int initHeight, bool 
        initAlpha = true, unsigned int initBitsPerSample = 8, 
        Ionflux::Altjira::ColorSpace initColorSpace = 
        Ionflux::Altjira::Color::SPACE_RGB);
        virtual ~Image();
        virtual void createNewData(unsigned int initWidth, unsigned int 
        initHeight, bool initAlpha = true, unsigned int initBitsPerSample =
        8, Ionflux::Altjira::ColorSpace initColorSpace = 
        Ionflux::Altjira::Color::SPACE_RGB);
        virtual bool loadFromFile(const std::string& fileName);
        virtual void getGIHData(std::string& target, unsigned int cellWidth
        = GIH_DEFAULT_CELL_WIDTH, unsigned int cellHeight = 
        GIH_DEFAULT_CELL_HEIGHT, const Ionflux::Altjira::GIHRankSpecVector*
        ranks = 0, const std::string& placement = 
        Ionflux::Altjira::Image::GIH_DEFAULT_PLACEMENT, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& 
        brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int 
        spacing = Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
        virtual void getGBRData(std::string& target, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& 
        brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int 
        spacing = Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
        virtual bool writeGBR(const std::string& fileName, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& 
        brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int 
        spacing = Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
        virtual bool writeGIH(const std::string& fileName, unsigned int 
        cellWidth = GIH_DEFAULT_CELL_WIDTH, unsigned int cellHeight = 
        GIH_DEFAULT_CELL_HEIGHT, const Ionflux::Altjira::GIHRankSpecVector*
        ranks = 0, const std::string& placement = 
        Ionflux::Altjira::Image::GIH_DEFAULT_PLACEMENT, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& 
        brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int 
        spacing = Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
        virtual bool writeToFile(const std::string& fileName, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_PNG, const std::string& brushName = 
        Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int spacing = 
        Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD, unsigned int 
        cellWidth = GIH_DEFAULT_CELL_WIDTH, unsigned int cellHeight = 
        GIH_DEFAULT_CELL_HEIGHT, const Ionflux::Altjira::GIHRankSpecVector*
        ranks = 0, const std::string& placement = 
        Ionflux::Altjira::Image::GIH_DEFAULT_PLACEMENT);
        virtual void clear();
        virtual bool setPixel(unsigned int x, unsigned int y, const 
        Ionflux::Altjira::ByteColor& color);
        virtual bool setPixel(unsigned int x, unsigned int y, const 
        Ionflux::Altjira::FloatColor& color);
        virtual bool setPixel(unsigned int x, unsigned int y, const 
        Ionflux::Altjira::Color& color);
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::ByteColor& color) const;
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::FloatColor& color) const;
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::Color& color) const;
        virtual bool fill(const Ionflux::Altjira::ByteColor& color);
        virtual bool fill(const Ionflux::Altjira::FloatColor& color);
        virtual bool fill(const Ionflux::Altjira::Color& color);
        virtual bool fill(const Ionflux::Altjira::PixelSource& source, 
        const Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int 
        offsetX = 0, unsigned int offsetY = 0);
        virtual bool fill(const Ionflux::Altjira::Image& other, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual bool composite(const Ionflux::Altjira::Image& other, const 
        Ionflux::Altjira::ColorBlender* blender = 0, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual void createArray(Ionflux::Altjira::ImageSet& target, 
        unsigned int cellWidth, unsigned int cellHeight) const;
        virtual void compositeArray(const Ionflux::Altjira::ImageSet& 
        source, unsigned int cellWidth, unsigned int cellHeight, unsigned 
        int numCols, unsigned int numRows, const 
        Ionflux::Altjira::ColorBlender* blender = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual bool convolveFill(const Ionflux::Altjira::Image& other, 
        const Ionflux::Mapping::Matrix& matrix, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual bool setChannel(const Ionflux::Altjira::Image& other, 
        Ionflux::Altjira::ChannelID source, Ionflux::Altjira::ChannelID 
        target, Ionflux::Mapping::Mapping* mapping = 0, 
        Ionflux::Altjira::ColorSpace sourceSpace = 
        Ionflux::Altjira::Color::SPACE_UNDEFINED, 
        Ionflux::Altjira::ColorSpace targetSpace = 
        Ionflux::Altjira::Color::SPACE_UNDEFINED, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual void setChannel(const Ionflux::Mapping::Matrix& matrix, 
        Ionflux::Altjira::ChannelID targetChannel, 
        Ionflux::Mapping::Mapping* mapping = 0, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0, Ionflux::Altjira::ColorSpace 
        targetSpace = Ionflux::Altjira::Color::SPACE_HSV);
        virtual bool mask(Ionflux::Altjira::Image& other, 
        Ionflux::Altjira::ChannelID source = Ionflux::Altjira::CH_VALUE, 
        Ionflux::Mapping::Mapping* mapping = 0, 
        Ionflux::Altjira::ColorSpace sourceSpace = 
        Ionflux::Altjira::Color::SPACE_HSV, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual void valuesToColor(Ionflux::Altjira::ColorBand& colors);
        virtual void colorToAlpha(const Ionflux::Altjira::Color& color);
        virtual void luminize(const Ionflux::Altjira::Image& source, double
        amount = 1.);
        virtual bool hasAlpha() const;
        virtual void clamp(Ionflux::Altjira::ImageRect& r0) const;
        virtual void getRandomPoints(unsigned int numPoints, 
        Ionflux::Mapping::PointSet& target, unsigned int maxIters = 100) 
        const;
        virtual void getColorDifference(const Ionflux::Altjira::Color& 
        refColor, Ionflux::Altjira::Image& targetImage, 
        Ionflux::Mapping::Mapping* mapping = 0) const;
        virtual void getChannel(Ionflux::Altjira::ChannelID channel, 
        Ionflux::Mapping::Matrix& target, Ionflux::Altjira::ColorSpace 
        colorSpace = Ionflux::Altjira::Color::SPACE_HSV) const;
        virtual Ionflux::ObjectBase::UInt64 getSize() const;
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Image* copy() const;
		static Ionflux::Altjira::Image* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Image* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Altjira::Image* create(const std::string& fileName, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Altjira::Image* create(unsigned int initWidth, unsigned 
		int initHeight, bool initAlpha = true, unsigned int initBitsPerSample = 
		8, Ionflux::Altjira::ColorSpace initColorSpace = 
		Ionflux::Altjira::Color::SPACE_RGB, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual unsigned int getNumChannels() const;
        virtual unsigned int getBitsPerSample() const;
        virtual Ionflux::Altjira::ColorSpace getColorSpace() const;
        virtual unsigned int getWidth() const;
        virtual unsigned int getHeight() const;
        virtual unsigned int getRowStride() const;
        virtual Ionflux::Altjira::PixelData getPixels() const;
};

}

}
