/**
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
 **/
#ifndef __COLOUR_H__
#define __COLOUR_H__

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"


#include <iostream>
/// \namespace ngl the main namespace for the NCCA Graphics Library
namespace ngl
{
/// \class Colour
/// \brief simple 4 colour class integrates into OpenGL colour calls
///  \author Jonathan Macey
/// \version 4.0
///  \date Last Revision 29/09/09 Updated to NCCA coding standard
///  \brief simple class to hold colour information and set the basic opengl colour
///    state. also has overloaded methods to do basic math on colour values.
///  \todo add code to use other colour spaces, could be done like Renderman with ctor "HSV" etc


class Colour
{
public :


  ///\brief default constructor set all values to 0
  inline Colour() :
                  m_r(0.0f),
                  m_g(0.0f),
                  m_b(0.0f),
                  m_a(1.0f){;}

  /// \brief constructor passing in r g b components
  /// @param[in]  _r red component
  /// @param[in]  _g green component
  /// @param[in]  _b blue component
  inline Colour(
                const Real _r,
                const Real _g,
                const Real _b
                ) :
                   m_r(_r),
                   m_g(_g),
                   m_b(_b),
                   m_a(1.0){;}

  /// \brief constructor passing in r g b components
  /// @param[in]  _r red component
  /// @param[in]  _g green component
  /// @param[in]  _b blue component
  /// @param[in]  _a the alpha component

  inline Colour(
                const Real _r,
                const Real _g,
                const Real _b,
                const Real _a
                ) :
                   m_r(_r),
                   m_g(_g),
                   m_b(_b),
                   m_a(_a){;}

  /// \brief constructor passing in a Colour
  /// @param[in] _c the colour to use

  inline Colour(
                const Colour  &_c
               ) :
                   m_r(_c.m_r),
                   m_g(_c.m_g),
                   m_b(_c.m_b),
                   m_a(_c.m_a){;}

  /// \brief set method to change the current values of the colour
  /// as well as the transparency
  /// @param[in]  _r red component to be set
  /// @param[in]  _g green component to be set
  /// @param[in]  _b blue component to be set
  /// @param[in]  _a alpha transparency value

  inline void Set(
                  const Real _r,
                  const Real _g,
                  const Real _b,
                  const Real _a=1.0
                  )
                  {
                   m_r=_r;
                   m_g=_g;
                   m_b=_b;
                   m_a=_a;
                  }
  /// \brief set method to set from another Colour
  /// @param[in] _c the colour
  inline void Set(
                  const Colour& _c
                 )
                 {
                  m_r = _c.m_r;
                  m_g = _c.m_g;
                  m_b= _c.m_b;
                  m_a=_c.m_a;
                 }

  /// \brief + operator to add two colours
  /// @param[in] _c the Colour to add
  /// \return this+_c
  Colour operator +(
                    const Colour &_c
                   ) const;
  /// \brief - operator to subtract colours
  /// @param[in] _c the Colour to add
  /// \return this-_c
  Colour operator -(
                    const Colour &_c
                   ) const;

  /// \brief - operator to add rhs to current colour
  /// @param[in] _c the Colour to add
  /// \return this+_c
  const Colour& operator +=(
                            const Colour &_c
                           );

  /// \brief - operator to multiply colours
  /// @param[in] _c the Colour to mult
  /// \return this*_c
  Colour operator *(
                    const Colour &_c
                   ) const;

  /// \brief * operator to multiply by a scalar
  /// @param[in] _c the scalar to multiply colour by
  /// \return this*_c
  Colour operator *(
                    const Real _c
                   ) const;

  /// \brief * operator to multiply = by a colour
  /// @param[in] _c the scalar to multiply colour by
  /// \return this*=_c
  const Colour& operator *=(
                            const Colour &_c
                           );

  /// \brief * operator to multiply by a scalar
  /// @param[in] _c the scalar to multiply colour by
  /// \return this*_c
  const Colour& operator *=(
                            const Real& _c
                           );

  /// add the product of source color and reflection coefficient
  /// @param[in] _src the source colour
  /// @param[in] _refl the reflected colour
  void add(
           const Colour& _src,
           const Colour& _refl
          );

  /// \brief << extraction operator to prints out the colour in the format [r,g,b,a]
  /// @param[in] _output the outstream class pointer
  /// @param[in] _s the colour to print out

  friend std::ostream& operator<<(
                                  std::ostream& _output,
                                  const Colour& _s
                                 )
                                 {
                                 return _output<<"["<<_s.m_r<<","<<_s.m_g<<","<<_s.m_b<<","<<_s.m_a<<"]";
                                 }


  /// \brief >> insertion operator to read in the colour data r -> g -> b -> a
  /// @param[in] _input the instream class pointer
  /// @param[in] _s the colour to read in to

  friend std::istream& operator>>(
                                  std::istream& _input,
                                  Colour& _s
                                 )
                                 {
                                 return _input >> _s.m_r >> _s.m_g >> _s.m_b>>_s.m_a;
                                 }

  /// \brief call glColor4f to set this as the current colour
  void Use() const ;
  inline Real * OpenGL(){return &m_openGL[0];}

  inline Real R(){return m_r;}
  void R(Real _r){m_r=_r;}

  inline Real G(){return m_g;}
  void G(Real _g){m_g=_g;}

  inline Real B(){return m_b;}
  void B(Real _b){m_b=_b;}

  inline Real A(){return m_a;}
  void A(Real _a){m_a=_a;}
  /// \brief clamp the colour to the given range from Eduard Zell MSc 2010
  void Clamp(
             Real _min,
             Real _max
            );

protected :
    friend class Material;
    // note the BUILDING_DOCS define is set in the doxygen Doxyfile so that we get
    // nice documents for these member attributes is must not be set in C++ build
    #ifndef BUILDING_DOCS
    union
    {
      struct
      {
    #endif
        /// red component of the colour tuple
        Real m_r;
        /// green component of the colour tuple
        Real m_g;
        /// blue component of the colour tuple
        Real m_b;
        /// alpha the transparent element
        Real m_a;
      #ifndef BUILDING_DOCS
      };
      #endif
      /// \brief The data as an array of 4 floats useful for passing to OpenGL fv data types
      /// this is mapped as a union to the following \n
      /// m_r == m_openGL[0] \n
      /// m_g == m_openGL[1] \n
      /// m_b == m_openGL[2] \n
      /// m_a == m_openGL[3] \n

      Real m_openGL[4];
    #ifndef BUILDING_DOCS
    };
    #endif




};

}

#endif // colour

