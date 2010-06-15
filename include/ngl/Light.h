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
#ifndef __LIGHT_H__
#define __LIGHT_H__

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include "VBOPrimitives.h"
#include "Colour.h"
#include "Vector.h"

namespace ngl
{
///  \enum LIGHTMODES used to flag if a light is local or remote to the scene
///
///  LIGHTREMOTE used to set the light remote
///   LIGHTLOCAL used to set the light local
///
enum LIGHTMODES
  {
  LIGHTREMOTE,
  LIGHTLOCAL
  };


///  \class Light "include/Light.h"
///  \author Jon Macey
///  \version 4.0
///  \date Last Revision 29/10/09 Updated to NCCA coding standard

/// \brief Simple class to encapsulate OpenGL Light functions
///  I've slightly changed the interface for the lights. It seems to me that
///  there is no real need to specify the OpenGL light number, we might as well
///  do that automatically when the lights are enabled/diabled. In effect I'm
///  using a static free list of 8 elements, one for each spare light number
///  16-3-05  >> RB

/// \todo this will need to be changed to work with GLSL lights for GL_VERSION > 3.x


class Light
{
public:

  /// \brief  set the light position
  /// @param[in]  _p the new light position
  inline void SetPosition(
                          const Vector& _p
                         )
                         {
                         m_pos.Set(_p);
                         }

  /// \brief set the light colour
  /// @param[in] _c the colour to set
  inline void SetColour(
                        const Colour& _c
                       )
                       {
                       m_colour.Set(_c);
                       }

  ///  \brief set the specular colour
  /// @param[in] _c the colour to set for the specular
  inline void SetSpecColour(
                            const Colour& _c
                           )
                           {
                           m_specColour.Set(_c);
                           }

  ///  \brief default constructor which sets no parameters apart from light
  ///  Number so we can use the OpenGL default light values
  ///  Which are usually quite good
  inline Light():
                m_lightNo(0x00){;}

  /// \brief ctor to create the light
  /// @param[in] _pos the light position
  /// @param[in] _col the light colour
  /// @param[in] _lightmode the mode to set the light to either local or remote
  Light(
        const Vector& _pos,
        const Colour& _col,
        const LIGHTMODES _lightmode
       );

  /// \brief ctor to create the light
  /// @param[in] _pos the light position
  /// @param[in] _col the light colour
  /// @param[in] _specColour the specular component of the light
  /// @param[in] _lightmode the mode to set the light to either local or remote
  Light(
        const Vector& _pos,
        const Colour& _col,
        const Colour& _specColour,
        const LIGHTMODES _lightmode
       );
  ///  \brief destructor when light is destroyed we turn it off
  ///   by using glDisable(GL_LIGHT0+LightNo);
  virtual inline ~Light()
                        {
                        Disable();
                        }
  ///  \brief Disable the light by calling glDisable(GL_LIGHT0+LightNo);
  void Disable();

  /// \brief  Enables the light and automatically allocates an OpenGL light ID.
  /// \return  true if there is a free openGL light ID available.

  virtual bool Enable();

  /// \brief get the number of lights created from the static identifier
  /// \return the number of created lights in the light array
  static int GetNumEnabledLights(){ return s_numEnabledLights;}

  /// \brief displays the light in the scene
  void Show();
  ///  returns the current value of the light number
  ///  \returns int LightNo

  GLint GetLightNum()
                   {
                    return GL_LIGHT0 + m_lightNo - 1;
                   }
  ///  returns the current light position as a Vector
  /// \returns Vector pos
  Vector& GetPos()
                 {
                 return m_pos;
                 }
  ///  returns the current light colour
  /// \returns Colour coloour
  Colour& GetColour()
                    {
                    return m_colour;
                    }

protected :
    ///  m_pos is used to store the light position
   Vector m_pos;
   ///  Colour used to give the light a colour
   Colour m_colour;
   ///  specular highlight colour used for the lights
   Colour m_specColour;

   ///  int LightNo used to set the light number this is a direct map to
   ///  OpenGL light number GL_LIGHT[x] where x is a number. The internal
   ///  implimentation will use GL_LIGHT0+LightNo to indicate light numbers
   int m_lightNo;
  /// used to hold the current lights mode
   LIGHTMODES m_lightMode;

private:

/*----------------------------------------------------------
 *   These variables are used to keep track of the openGL light
 *  id's currently within use. The idea is for this to be
 *  automated so that when the light gets enabled, a free light
 *  id is automatically assigned RB
 ----------------------------------------------------------*/
  /// array of max free lights used to indicate if light is free
  static unsigned char s_freeLights[8];
  /// counter to the number of available lights
  static unsigned int s_numEnabledLights;

}; // end class

}// end namespace

#endif // __LIGHT__





