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
#ifndef __NGLINIT_H__
#define __NGLINIT_H__

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include "Singleton.h"
#include <iostream>
#include "VBOPrimitives.h"

namespace ngl
{
/// \author Jonathan Macey
/// \version 4.0
/// \date Last Revision 19/11/09 changed the whole lib to be NGL not GraphicsLib so change names to reflect
///	 29/09/09 Updated to meet NCCA Coding standard
/// \class NGLInit  "include/NGLInit.h"
/// @example GraphicsLibInitExample/GraphicsLibInitExample.cpp

/// \brief a class to initialise all of the ngl elements includeing GLEW if needed as well as SDL and vbo prims
/// this class is a singletone so can only be created once
///
class   NGLInit : public  Singleton<NGLInit>
{
    friend class Singleton<NGLInit>;
public :

  /// ! \brief method to initialise GLEW if required (if linux is defined)
  void InitGlew();
	/// !\brief a method to shutdow NGL
	inline void NGLQuit(){ delete m_prim;}
  /// \brief init the VBO library and DevIL if being used
	void InitVBOandImageLib();
  /// \brief get the pointer to the VBO primitive class
  ///\returns VBOPrimitive the pointer to the instance of the primitive
  inline VBOPrimitives * GetPrim(){return m_prim;}

protected :
  /// \brief pointer to the VBOPrimitives object
  VBOPrimitives *m_prim;
/*
  /// \brief ctor protected as a singleton
  NGLInit();

  /// \brief copy ctor protected as a singleton
  /// @param[in] _g the element to be copied
  NGLInit(
          const NGLInit& _g
         );
  /// \brief assignment operator protected as singleton
  /// @param[in] _g the instance to copy
  NGLInit& operator=(
                     const NGLInit& _g
                    );
*/
///  \brief dtor
  ~NGLInit();
};
} // end GL namespace

#endif


