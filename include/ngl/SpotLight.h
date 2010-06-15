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


#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__
// must include types.h first for ngl::Real and GLEW if required

#include "Vector.h"
#include "Light.h"
#include <cmath>


namespace ngl
{

/// \class SpotLight "include/SpotLight.h"
/// \file SpotLight.h
/// \author Jonathan Macey
/// \version 2.0
///\date 24/11/04

/// @example SpotLight/SpotLight.cpp

/// \brief Encapsulation of OpenGL spotlight inherits from the Light class

class SpotLight : public Light
{
public:
  SpotLight(){;}
  /// \brief  ctor
  /// @param[in]  _pos    -  the spot position
  /// @param[in]  _dir    -  the spot direction
  ///  @param[in]  _col    -  the spot colour
  ///
  SpotLight(
            const Vector& _pos,
            const Vector& _dir,
            const Colour& _col
           );

  /// \brief a method to set the spotlight parameters
  /// @param [in] _pos the position of the Light
  /// @param [in] _dir the direction of the light
  /// @param [in] _col the colour of the light
  void Set(
           const Vector& _pos,
           const Vector& _dir,
           const Colour& _col
           );

  //--------------------------------------------------------------------------
  /// \brief  Displays the light in the scene
  ///
  void Show();
  //--------------------------------------------------------------------------
  /// \brief  enables the spot light
  ///
  bool Enable();
  //--------------------------------------------------------------------------
  /// \brief  sets the various spot light params
  /// @param[in] _cutoff the spot cutoff value
  /// @param[in] _exponent the spot exponent vlaue
  /// @param[in] _constant constant attenuation value
  /// @param[in] _linear linear attenuation value
  /// @param[in] _quadratic quadratic attenuation value
  void SetParams(
                 const Real _cutoff,
                 const Real _exponent,
                 const Real _constant,
                 const Real _linear,
                 const Real _quadratic
                );
  //--------------------------------------------------------------------------
  /// \brief  This function sets the light to aim at the specified point
  /// @param[in]  _pos  -  the aim position
  ///
  void Aim(
           const Vector& _pos
          );


protected :
  /// the spot cutoff angle
  Real m_cutoffAngle;
  /// the SpotExponent value
  Real m_spotExponent;
  /// attenuation value for constant falloff
  Real m_constantAtten;
  /// attenuation value for linear falloff
  Real m_linearAtten;
  /// attenuation value for Quadratic falloff
  Real m_quadraticAtten;
  /// where the spot is to be aimed
  Vector m_aim;
  /// the spot light direction vector
  Vector m_dir;

  }; // end of class SpotLight
}// end of namespace
#endif


