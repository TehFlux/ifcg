#ifndef IONFLUX_ALTJIRA_MATRIXSOURCE
#define IONFLUX_ALTJIRA_MATRIXSOURCE
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2024 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MatrixSource.hpp                Matrix pixel source (header).
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

#include "ifmapping/Matrix.hpp"
#include "altjira/PixelSource.hpp"

namespace Ionflux
{

namespace Altjira
{

/// Class information for class MatrixSource.
class MatrixSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		MatrixSourceClassInfo();
		/// Destructor.
		virtual ~MatrixSourceClassInfo();
};

/** Matrix pixel source.
 * \ingroup altjira
 *
 * A source for pixels that takes pixel values from a set of matrices, with
 * one matrix per channel. Default values can be configured for all 
 * channels. A color space can be set, which is used for interpreting the 
 * channel values.
 */
class MatrixSource
: public Ionflux::Altjira::PixelSource
{
	private:
		
	protected:
		/// Default color.
		Ionflux::Altjira::FloatColor defaultColor;
		/// Matrix (component 0).
		Ionflux::Mapping::Matrix* matrixC0;
		/// Matrix (component 1).
		Ionflux::Mapping::Matrix* matrixC1;
		/// Matrix (component 2).
		Ionflux::Mapping::Matrix* matrixC2;
		/// Matrix (alpha).
		Ionflux::Mapping::Matrix* matrixAlpha;
		/// Width.
		unsigned int width;
		/// Height.
		unsigned int height;
		
	public:
		/// Class information instance.
		static const MatrixSourceClassInfo matrixSourceClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new MatrixSource object.
		 */
		MatrixSource();
		
		/** Constructor.
		 *
		 * Construct new MatrixSource object.
		 *
		 * \param other Other object.
		 */
		MatrixSource(const Ionflux::Altjira::MatrixSource& other);
		
		/** Constructor.
		 *
		 * Construct new MatrixSource object.
		 *
		 * \param initWidth Width.
		 * \param initHeight Height.
		 * \param initMatrixC0 Matrix (component 0).
		 * \param initMatrixC1 Matrix (component 1).
		 * \param initMatrixC2 Matrix (component 2).
		 * \param initMatrixAlpha Matrix (alpha).
		 * \param initDefaultColor Default color.
		 * \param initColorSpace Color space.
		 */
		MatrixSource(unsigned int initWidth, unsigned int initHeight, 
		Ionflux::Mapping::Matrix* initMatrixC0 = nullptr, 
		Ionflux::Mapping::Matrix* initMatrixC1 = nullptr, 
		Ionflux::Mapping::Matrix* initMatrixC2 = nullptr, 
		Ionflux::Mapping::Matrix* initMatrixAlpha = nullptr, const 
		Ionflux::Altjira::Color& initDefaultColor = 
		Ionflux::Altjira::Color::BLACK, Ionflux::Altjira::ColorSpace 
		initColorSpace = Ionflux::Altjira::Color::SPACE_HSV);
		
		/** Destructor.
		 *
		 * Destruct MatrixSource object.
		 */
		virtual ~MatrixSource();
		
		/** Set default color.
		 *
		 * Set the default color and color space.
		 *
		 * \param color Color.
		 * \param newColorSpace Color space.
		 */
		virtual void setDefaultColor(const Ionflux::Altjira::Color& color, 
		Ionflux::Altjira::ColorSpace newColorSpace = 
		Ionflux::Altjira::Color::SPACE_UNDEFINED);
		
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
		 * Get pixel color for the specified indices.
		 * 
		 * A default color component is used if a matrix for a component is 
		 * undefined or any of the indices is out of bounds for that matrix.
		 * 
		 * If any of the indices are out of bounds for the pixel source and 
		 * the extent for that index is not infinite, an out of bounds 
		 * exception will be thrown.
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
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Altjira::MatrixSource& operator=(const 
		Ionflux::Altjira::MatrixSource& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Altjira::MatrixSource* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Altjira::MatrixSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
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
		static Ionflux::Altjira::MatrixSource* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new MatrixSource object.
		 *
		 * \param initWidth Width.
		 * \param initHeight Height.
		 * \param initMatrixC0 Matrix (component 0).
		 * \param initMatrixC1 Matrix (component 1).
		 * \param initMatrixC2 Matrix (component 2).
		 * \param initMatrixAlpha Matrix (alpha).
		 * \param initDefaultColor Default color.
		 * \param initColorSpace Color space.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Altjira::MatrixSource* create(unsigned int initWidth, 
		unsigned int initHeight, Ionflux::Mapping::Matrix* initMatrixC0 = 
		nullptr, Ionflux::Mapping::Matrix* initMatrixC1 = nullptr, 
		Ionflux::Mapping::Matrix* initMatrixC2 = nullptr, 
		Ionflux::Mapping::Matrix* initMatrixAlpha = nullptr, const 
		Ionflux::Altjira::Color& initDefaultColor = 
		Ionflux::Altjira::Color::BLACK, Ionflux::Altjira::ColorSpace 
		initColorSpace = Ionflux::Altjira::Color::SPACE_HSV, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get default color.
		 *
		 * \return Current value of default color.
		 */
		virtual Ionflux::Altjira::FloatColor getDefaultColor() const;
		
		/** Set default color.
		 *
		 * Set new value of default color.
		 *
		 * \param newDefaultColor New value of default color.
		 */
		virtual void setDefaultColor(const Ionflux::Altjira::FloatColor& 
		newDefaultColor);
		
		/** Get color space.
		 *
		 * \return Current value of color space.
		 */
		virtual Ionflux::Altjira::ColorSpace getColorSpace() const;
		
		/** Set color space.
		 *
		 * Set new value of color space.
		 *
		 * \param newColorSpace New value of color space.
		 */
		virtual void setColorSpace(Ionflux::Altjira::ColorSpace newColorSpace);
		
		/** Get matrix (component 0).
		 *
		 * \return Current value of matrix (component 0).
		 */
		virtual Ionflux::Mapping::Matrix* getMatrixC0() const;
		
		/** Set matrix (component 0).
		 *
		 * Set new value of matrix (component 0).
		 *
		 * \param newMatrixC0 New value of matrix (component 0).
		 */
		virtual void setMatrixC0(Ionflux::Mapping::Matrix* newMatrixC0);
		
		/** Get matrix (component 1).
		 *
		 * \return Current value of matrix (component 1).
		 */
		virtual Ionflux::Mapping::Matrix* getMatrixC1() const;
		
		/** Set matrix (component 1).
		 *
		 * Set new value of matrix (component 1).
		 *
		 * \param newMatrixC1 New value of matrix (component 1).
		 */
		virtual void setMatrixC1(Ionflux::Mapping::Matrix* newMatrixC1);
		
		/** Get matrix (component 2).
		 *
		 * \return Current value of matrix (component 2).
		 */
		virtual Ionflux::Mapping::Matrix* getMatrixC2() const;
		
		/** Set matrix (component 2).
		 *
		 * Set new value of matrix (component 2).
		 *
		 * \param newMatrixC2 New value of matrix (component 2).
		 */
		virtual void setMatrixC2(Ionflux::Mapping::Matrix* newMatrixC2);
		
		/** Get matrix (alpha).
		 *
		 * \return Current value of matrix (alpha).
		 */
		virtual Ionflux::Mapping::Matrix* getMatrixAlpha() const;
		
		/** Set matrix (alpha).
		 *
		 * Set new value of matrix (alpha).
		 *
		 * \param newMatrixAlpha New value of matrix (alpha).
		 */
		virtual void setMatrixAlpha(Ionflux::Mapping::Matrix* newMatrixAlpha);
		
		/** Get width.
		 *
		 * \return Current value of width.
		 */
		virtual unsigned int getWidth() const;
		
		/** Set width.
		 *
		 * Set new value of width.
		 *
		 * \param newWidth New value of width.
		 */
		virtual void setWidth(unsigned int newWidth);
		
		/** Get height.
		 *
		 * \return Current value of height.
		 */
		virtual unsigned int getHeight() const;
		
		/** Set height.
		 *
		 * Set new value of height.
		 *
		 * \param newHeight New value of height.
		 */
		virtual void setHeight(unsigned int newHeight);
};

}

}

/** \file MatrixSource.hpp
 * \brief Matrix pixel source (header).
 */
#endif
