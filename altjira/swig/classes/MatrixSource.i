/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MatrixSource.i                  Matrix pixel source (interface).
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
#include "altjira/MatrixSource.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class MatrixSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MatrixSourceClassInfo();
        virtual ~MatrixSourceClassInfo();
};

class MatrixSource
: public Ionflux::Altjira::PixelSource
{
    public:
        
        MatrixSource();
		MatrixSource(const Ionflux::Altjira::MatrixSource& other);
        MatrixSource(unsigned int initWidth, unsigned int initHeight, 
        Ionflux::Mapping::Matrix* initMatrixC0 = nullptr, 
        Ionflux::Mapping::Matrix* initMatrixC1 = nullptr, 
        Ionflux::Mapping::Matrix* initMatrixC2 = nullptr, 
        Ionflux::Mapping::Matrix* initMatrixAlpha = nullptr, const 
        Ionflux::Altjira::Color& initDefaultColor = 
        Ionflux::Altjira::Color::BLACK, Ionflux::Altjira::ColorSpace 
        initColorSpace = Ionflux::Altjira::Color::SPACE_HSV);
        virtual ~MatrixSource();
        virtual void setDefaultColor(const Ionflux::Altjira::Color& color, 
        Ionflux::Altjira::ColorSpace newColorSpace = 
        Ionflux::Altjira::Color::SPACE_UNDEFINED);
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::ByteColor& color) const;
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::FloatColor& color) const;
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::Color& color) const;
		virtual Ionflux::Altjira::MatrixSource* copy() const;
		static Ionflux::Altjira::MatrixSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::MatrixSource* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Altjira::MatrixSource* create(unsigned int initWidth, 
		unsigned int initHeight, Ionflux::Mapping::Matrix* initMatrixC0 = 
		nullptr, Ionflux::Mapping::Matrix* initMatrixC1 = nullptr, 
		Ionflux::Mapping::Matrix* initMatrixC2 = nullptr, 
		Ionflux::Mapping::Matrix* initMatrixAlpha = nullptr, const 
		Ionflux::Altjira::Color& initDefaultColor = 
		Ionflux::Altjira::Color::BLACK, Ionflux::Altjira::ColorSpace 
		initColorSpace = Ionflux::Altjira::Color::SPACE_HSV, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setDefaultColor(const Ionflux::Altjira::FloatColor& 
        newDefaultColor);
        virtual Ionflux::Altjira::FloatColor getDefaultColor() const;
        virtual void setColorSpace(Ionflux::Altjira::ColorSpace 
        newColorSpace);
        virtual Ionflux::Altjira::ColorSpace getColorSpace() const;
        virtual void setMatrixC0(Ionflux::Mapping::Matrix* newMatrixC0);
        virtual Ionflux::Mapping::Matrix* getMatrixC0() const;
        virtual void setMatrixC1(Ionflux::Mapping::Matrix* newMatrixC1);
        virtual Ionflux::Mapping::Matrix* getMatrixC1() const;
        virtual void setMatrixC2(Ionflux::Mapping::Matrix* newMatrixC2);
        virtual Ionflux::Mapping::Matrix* getMatrixC2() const;
        virtual void setMatrixAlpha(Ionflux::Mapping::Matrix* 
        newMatrixAlpha);
        virtual Ionflux::Mapping::Matrix* getMatrixAlpha() const;
        virtual void setWidth(unsigned int newWidth);
        virtual unsigned int getWidth() const;
        virtual void setHeight(unsigned int newHeight);
        virtual unsigned int getHeight() const;
};

}

}
