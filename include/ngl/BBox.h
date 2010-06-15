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
#ifndef __BBOX_H_
#define __BBOX_H_

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"

#include "Vector.h"
#include <iostream>


namespace ngl
{
/*!  \author Jonathan Macey
    \version 4.0
    \date Last Revision 31/09/09 Updated to draw with vertex arrays \n

    Revision History : \n
    14/02/03 Removed redundant data types \n
    16/02/03 Added destructor just in case \n
    17/02/03 Added Comments to source using doxygen tags \n
  17/02/03 Updated revision to 3.0 \n
  27/09/09 Updated to NCCA Coding standard updated to V4.0 \n
*/
/*! \class BBox  "include/BBox.h"
    \brief Simple Bounding box class used in various parts of ngl and other example programs
*/
class BBox
{
public :

  /// \brief Bounding Box ctor using a Center and the 3 dimensions of the BBox
  //!  @param[in]  _center the center of the BBox.
  //!  @param[in]  _width the width of the BBox (== X coord).
  //!  @param[in]  _height the height of the BBox (== Y coord).
  //!  @param[in]  _depth the Depth of the BBox (== Z coord).

  BBox(
       const Vector& _center,
       const Real& _width,
       const Real& _height,
       const Real& _depth
      );

  ///  \brief ctor using +/- x,y,z dimensions
  /// @param[in]  _minX the x position of the min x extent
  /// @param[in]  _maxX the x position of the max x extent
  /// @param[in]  _minY the y position of the min y extent
  /// @param[in]  _maxY the y position of the max y extent
  /// @param[in]  _minZ the z position of the min z extent
  /// @param[in]  _maxZ the z position of the max z extent
  BBox(
       const Real& _minX,
       const Real& _maxX,
       const Real& _minY,
       const Real& _maxY,
       const Real& _minZ,
       const Real& _maxZ
      );
   /// \brief Default constructor will create a BBox centered at point 0,0,0
   /// With Unit length width and height (== 1)
  BBox();
   /// \brief Draw Method draws the BBox using OpenGL
   void Draw() const;
   /// \brief reset the draw mode for the BBox
   /// @param[in] _mode the mode to draw
   void ResetDrawMode(
                       const GLenum& _mode
                      );
   /*! \brief dtor no dynamic memory so empty */
   ~BBox();

   // accesors
   /// \brief the min x value of the bbox
   Real MinX(){ return m_minX;}
   /// \brief the max x value of the bbox
   Real MaxX(){ return m_maxX;}
   /// \brief the min y value of the bbox
   Real MinY(){ return m_minY;}
   /// \brief the max y value of the bbox
   Real MaxY(){ return m_maxY;}
   /// \brief the min z value of the bbox
   Real MinZ(){ return m_minZ;}
   /// \brief the max z value of the bbox
   Real MaxZ(){ return m_maxZ;}
    /// \brief This is the center of the BBox stored for caluculations in other classes s
   Vector Center(){ return m_center; }
   /// \brief Width of the BBox
   Real Width(){ return m_width; }
   /// \brief Height of the BBox
   Real Height(){ return m_height;}
   /// \brief Depth of the BBox
   Real Depth(){ return m_depth;}





protected :
    /// \brief Contains the   8 vertices for the BBox aranged from v[0] = Left-top-Max Z
    ///and then rotating clock wise for the top of the BBox
    ///The Bottom Square is a mirror of the 1st verts with the Y value changed
    ///See constructor code for caluculations
    Vector m_vert[8];
    /// \brief the min x value of the bbox
    Real m_minX;
    /// \brief the max x value of the bbox
    Real m_maxX;
    /// \brief the min y value of the bbox
    Real m_minY;
    /// \brief the max y value of the bbox
    Real m_maxY;
    /// \brief the min z value of the bbox
    Real m_minZ;
    /// \brief the max z value of the bbox
    Real m_maxZ;
     /// \brief This is the center of the BBox stored for caluculations in other classes s
    Vector m_center;
    /// \brief used to store the 6 Normal faces for the BBox used for calculating BBox  collisions if needed
    Vector m_norm[6];
    /// \brief Width of the BBox
    Real m_width;
    /// \brief Height of the BBox
    Real m_height;
    /// \brief Depth of the BBox
    Real m_depth;

  /// \brief a pointer to the VBO buffer used for drawing the bbox
  GLuint m_VBOBuffer;
  /// \brief sets the draw mode for the BBox Faces,  set to GL_LINE for
  ///  line faces and GL_FILL for filled
   GLuint m_drawMode;

}; // end class
} // end namespace

#endif

