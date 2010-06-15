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
#ifndef __TYPES_H__
#define __TYPES_H__

#if defined (LINUX) || defined (WIN32)
  #include <GL/glew.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif
#ifdef DARWIN
  #include <unistd.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#endif

///
/// \file types.h
/// \brief declare a variable called Real which sets the Global Precision for the other classes (GLfloat)
/// \author Jonathan Macey
/// \version 2.0
/// \date 29/10/09 Updated to meet NCCA coding standard


/// \namespace ngl : bundled all the graphics lib code in this namespace to allow several
/// global namespace enums and variables

namespace ngl
{
/// Set the PRECISION of all data types
///  Set PRECISION to be a GLfloat so we only have to change one value to set the data type
  typedef GLfloat PRECISION;

/// create a variable called Real which is the main data type we use (GLfloat for most  cases)

typedef PRECISION Real;
/// define EPSILON for floating point comparison
#ifndef EPSILON
  const Real EPSILON = 0.001f;
#endif

/// \brief FCompare macro used for floating point comparision functions
  #define FCompare(a,b) \
      ( ((a)-EPSILON)<(b) && ((a)+EPSILON)>(b) )

}



#endif

