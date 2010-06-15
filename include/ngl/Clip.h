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
#ifndef __CLIP_H__
#define __CLIP_H__
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"

#include <iostream>
#include <vector>

#include "Vector.h"
#include "Obj.h"


namespace ngl
{
///  \author Jonathan Macey
/// \version 2.0
/// \date Last Revision 12/03/09
/// \class Clip  "include/Clip.h"
///\brief Class to load and manipulate a Houdini Clip file for vertex change data only at present
/** \verbatim
 The clip file has the following format
{
  rate = The frame rate of the exported clip
  start = The start frame
  tracklength = how many frames of data are stored in the file
  tracks = How many tracks (usually these will corrispond to vertices
  then for each track  the following data
  {
  name = tx0 in this case this is the translation data for x on vert 0
  data = the actuall data offset values for each frame for the above value
  }
  .....
  {
  name =tz[tracks]
  data =[]
  }
}
\endverbatim
 **/
class Clip
{
/// \brief an enum to indicate  which type of vertex we have parsed
enum VTYPE
     {
        TX, ///< Indicates a translate in the x for a vertex
        TY, ///< Indicates a translate in the y for a vertex
        TZ  ///< Indicates a translate in the z for a vertex
     };

public :
  ///  \brief ctor for the clip
  Clip();
  ///  \brief the dtor erases all clip data allocated and also destroys the Obj reference held in the clip
  ~Clip();
  /// \brief   ctor using a clip and an obj
  /// @param[in] _clipName the name of the clup to load
  /// @param[in] _objName the name of the obj to use
  Clip(
       const std::string &_clipName,
       const std::string &_objName
      );
  ///   \brief  ctor using just a clip
  /// @param[in] _clipName the name of the clip to load
  Clip(
       const std::string &_clipName
      );
  ///  \brief  load a clip and an obj mesh to animate with texture
  /// @param[in] _clipName the name of the clip to load.
  /// @param[in] _objName the name of the obj file to load
  /// @param[in] _texName the name of a texture file for the obj

  Clip(
       const std::string &_clipName,
       const std::string &_objName,
       const std::string &_texName
      );
  ///   \brief  method to pass in an obj
  /// @param[in] _obj the obj file reference
  void SetObj(
              ngl::Obj *_obj
             );
  /// \brief  method to draw the obj at the current frame
  /// @param[in] Frame the frame to draw. note this method maps the obj vbo so if using multiple instances
  /// it is quicker to use the UpdateVerts method once then the Draw method for each instance
  void Draw(
            const unsigned int Frame
           );
  /// \brief  method to draw the obj at the current frame
  void Draw() const;
  /// \brief  Set the current Frame and map the clip for that frame to the obj
  /// @param[in] frame the frame to set
  void SetFrame(
                const unsigned int frame
               );
  /// \brief  method to load a clip
  /// @param[in] _clipName the clip to load
  void LoadClip(
                const std::string &_clipName
               );
  /// \brief the number of frames in the clip file
  unsigned int m_nFrames;
  /// \brief Current active frame when animating
  unsigned int m_currFrame;
  /// \brief  this method updates the Obj verts for the current frame
  /// @param[in] Frame the frame to set
  void UpdateVerts(
                   const unsigned int Frame
                  );

protected :
  ///\brief  Obj to be used in animation
  ngl::Obj *m_obj;
  ///\brief  The actual data of the clip stored per vertex in sequence v0 - vn and then per frame frame
  /// index is always frame 0- endframe despite the start / end values in the clip file
  std::vector < std::vector<ngl::Vector> > m_data;
  /// \brief  the actual vertex order used in the obj as the data is re-ordered when loading into the vbo
  /// as part of the loading of the obj file to reduce redundant vertices.
  std::vector<int> m_vertOrder;
  /// \brief  Number of verts in the actual clip
  unsigned int m_nVerts;
  /// \brief flag to indicate if a texture was loaded if set to true the obj texture will be applied
  /// in the drawing method
  bool m_texture;
  ///  \brief method to create the vertorder container with the correct vertex order in place to match
  /// that of the obj file
  void ReorderVerts();
}; // end class

} // end namespace ngl


#endif // end include guard


