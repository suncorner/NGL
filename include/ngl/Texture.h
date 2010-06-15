/*
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

/*!
\file Texture.h
\brief simple OpenGL texture object, not very flexible and needs much work note that we now have
two options to use as the image loader library ImageMagick++ or libDevIL. DevIL is the only
lib supported under windows as I have a load of problems getting ImageMagick working under Windows.
To use ImageMagick set the -D USE_MAGICK flag either in the scons file or set the variable in the Qt project file
To use DevIL set the -D USE_DEVIL flag in either the scons of Qt project
For the Qt Project set the following line IMAGE_LIB=USE_DEVIL / USE_MAGICK
Also worth noting is that under Windows .bmp images are going to be flipped so textures will be wrong.
It seems to be ok under Mac and Linux and it's just windows that causes the problems. Best not use bmp.

\author Jonathan Macey
\version 2.0
\date 18/3/10 Added multi texture support
*/
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include "Colour.h"
#include <iostream>
#include <cmath>


namespace ngl
{
/// \todo make it more flexible for different types of texture operations
/// \class Texture "include/Texture.h"
/// \brief simple Texture class for OpenGL texturing uses ImageMagick to load textures.
/// \todo write save method at some stage as well this could grab info from framebuffer and replace the frame
/// writer class


class Texture
{
public :
  /// \brief Constructor using no parameters
  Texture();
  /// \brief  destructor will free m_data
  ~Texture();

  /// \brief Constructor passing the file to load
  /// @param[in] &_fName the name of the file to load
  Texture(
          const std::string  &_fName
         );

  /// \brief method to load the image file into the texture class
  /// imageMagick will determine if it can load the file
  /// return true on success else false if load fails
  bool LoadImage(
                 const std::string  &_fName
                );

  /// \brief get the pixel data from x,y cords
  /// @param[in] _x the x position of the pixel
  /// @param[in] _y the y position of the pixel */
  double GetFromXY(
                   const GLuint _x,
                   const GLuint _y
                  ) const;

  /// \brief set the image as an OpenGL texture object
  /// \returns the texture object id
  GLuint SetTextureGL() const;

  void SetMultiTexture(
                       const GLint _id
                      );

	ngl::Colour GetColourFromXY(
                              const GLuint _x,
                              const GLuint _y
                             ) const;

protected :
		/// the actual image data loaded packed in r,g,b,a format in contiguous memory

		unsigned char *m_data;
		/// @brief the size of the image in the X direction
		GLuint m_width;
		/// @brief the size of the image in the Y direction
		GLuint m_height;
		/// @brief A pointer to the start of the image data
		GLuint m_bpp;
    /// @brief the MultiTexture ID for the current texture Object
    GLint m_multiTextureID;
    /// @brief indicates if the image loaded had an alpha channel
    bool m_hasAlpha;
     GLuint m_format;

};

}
#endif

