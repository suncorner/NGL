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
#ifndef __UTIL_H__
#define __UTIL_H__
// must include types.h first for ngl::Real and GLEW if required
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include <cmath>
#include <vector>
#include "Vector.h"


namespace ngl
{
///
/// \file Util.h
/// \author Jonathan Macey
/// \version 1.2
/// \date 24/11/04

/// \brief lots of usful functions for ngl

/// pre-compute the value for value for 2*PI
const ngl::Real TWO_PI= 2*M_PI; //6.28318530717958647692   //360
/// pre-compute the value for value for PI based on system M_PI
const ngl::Real PI=M_PI; //3.14159265358979323846       //180
/// pre-compute the value for value for PI/2.0
const ngl::Real PI2=M_PI/2.0; //1.57079632679489661923      //90
/// pre-compute the value for value for PI/4.0
const ngl::Real PI4=M_PI/4.0; //0.785398163397448309615     //45


/// \brief calculates the normal from 3 points and return the new normal as a Vector
/// @param[in]  _p1 the first point
/// @param[in]  _p2 the second point
/// @param[in]  _p3 the third point
/// \returns  the normal of the 3 points

extern ngl::Vector CalcNormal(
                              const Vector _p1,
                              const Vector _p2,
                              const Vector _p3
                             );

/// \brief converts Degrees to Radians
/// @param[in]  _deg the angle to convert
/// \returns the angle in Radians
extern ngl::Real DegtoRad(
                          const Real _deg
                         );

/// \brief converts Radians to Degrees
/// @param[in]  _rad the angle in radians
/// \returns the angle in Degrees
extern ngl::Real RadtoDeg(
                          const Real _rad
                         );

/// \brief draws a simple axis with no cones
/// \param  _size the size of the axis to draw
extern void DrawAxisSimple(
                           const Real _size
                          );



/// \brief create an Axis for drawing This creates a VBO based axis and need only be called once
extern void CreateAxis();

/// \brief draw the axis created with the CreateAxis function
/// \param _size the size of the axis to draw (axis is created as a unit size)

extern void DrawAxis(
                     const Real _size
                    );

/// \brief a simple template function for Linear Interpolation requires that any classes have
///    + - and * scalar (i.e. Real) overloaded operators
///    In the graphics lib this will work  for Vector and Colour
/// @param [in] _a the template value for the first parameter
/// @param [in] _b the template value for the first parameter
/// @param [in] _t the value for the blend between _a and _b must be between 0 - 1
template <class T> T Lerp(
                          T _a,
                          T _b,
                          ngl::Real _t
                          )
{
T p;
p=_a+(_b-_a)*_t;
return p;
}


}
#endif

