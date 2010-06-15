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
#ifndef __VBOPRIMITIVES_H_
#define __VBOPRIMITIVES_H_

#include "Singleton.h"
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Vector.h"
#include <cmath>
#include <map>
#include <pthread.h>

namespace ngl
{

/// \class VBOData "include/VBOPrimitives.h"
/// \author Jonathan Macey
/// \version 1.2
/// \date Last Revision 30/08/09 Updated to NCCA coding standard
/// \brief data structure for VBO data stored in GL_T2_N2_V2 format
/// \todo could add multi texture support here and pad too 64 for (ATI cards)
#pragma pack(push,1)

struct VBOData
{
    /// the u texture cord
    GLfloat m_tu;
    /// the v texture cord
     GLfloat m_tv;
    /// x vertex normal value (normalize before passing for best results)
    GLfloat m_nx;
    /// y vertex normal value (normalize before passing for best results)
    GLfloat m_ny;
    /// z vertex normal value (normalize before passing for best results)
    GLfloat m_nz;
    /// the vertex x position
    GLfloat m_vx;
    /// the vertex y position
    GLfloat m_vy;
    /// the vertex z position
    GLfloat m_vz;
};
#pragma pack(pop)

/// \class VBOObject
/// \author Jonathan Macey
/// \version 1.2
/// \date Last Revision 30/08/09 Updated to NCCA coding standard
/// \brief used to store the data for the different VBO's created in a std::map
/// for each object we store the draw mode number of verts to draw and the VBO  buffer value.

class VBOObject
{

public :
    /// the number of verts stored in the vbo data structure
  unsigned int m_nv;
    /// VBO index created from genBuffers
  GLuint m_vbo;
    /// Draw mode (e.g. GL_TRIANGLE_STRIP)
  GLenum m_mode;
  /// \brief ctor
  /// @param[in] _n number of verts
  /// @param[in] _v vbo pointer
  /// @param[in] _m draw mode
  inline VBOObject(
                   const int _n,
                   const GLuint _v,
                   const GLenum _m
                  ):
                    m_nv(_n),
                    m_vbo(_v),
                    m_mode(_m){;}
    /// \brief copy ctor
  inline VBOObject(
                   const VBOObject &_c
                  ):
                    m_nv(_c.m_nv),
                    m_vbo(_c.m_vbo),
                    m_mode(_c.m_mode){;}
};


/// @example VBOPrimitives/Primitives.cpp
/// \class VBOPrimitives "include/VBOPrimitives.h"
/// \author Jonathan Macey
/// \version 1.2
/// \date Last Revision 30/08/09 Updated to NCCA coding standard
/// \brief VBO based object primitives used for fast openGL drawing this is a singelton class
/// this is a singleton class so we use this method to get access and construct the only instance

class VBOPrimitives : public  Singleton<VBOPrimitives>
{

friend class Singleton<VBOPrimitives>;
public :

 /// \brief destructor
    ~VBOPrimitives();
/// Draw modes for VBO used in a call to glPolygonMode
    enum DrawModes
        {
        SOLID, ///< Solid drawmode
        WIREFRAME ///< wirefame draw mode
        };

  /// \brief create a triangulated Sphere as a vbo with auto generated texture cords
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _radius the sphere radius
  /// @param[in] _precision the number of triange subdivisions to use
  void CreateVBOSphere(
                       const std::string &_name,
                       Real _radius,
                       int _precision
                      );

  /// \brief create a triangulated plane as a vbo with auto generated texture cords
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _width the width of the plane based on the center of the plane being at 0,0,0
  /// @param[in] _depth the height of the plane based on the center of the plane being at 0,0,0
  /// @param[in] _wP the precision of the width, this is basically the steps (per quad) which will be
  ///    triangulated for each (wP == 1 will give 1 quad mad of 2 tris)
  /// @param[in] _dP the precision of the Depth, this is basically the steps (per quad) which will be
  ///    triangulated for each (wP == 1 will give 1 quad mad of 2 tris)
  /// @param[in] _vN The Vertex normal (used for each vertex)

  void CreateVBOTrianglePlane(
                              const std::string &_name,
                              const Real _width,
                              const Real _depth,
                              const int _wP,
                              const int _dP,
                              const Vector &_vN
                             );


  /// \brief create a triangulated plane as a vbo with auto generated texture cords
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _width the width of the plane based on the center of the plane being at 0,0,0
  /// @param[in] _depth the height of the plane based on the center of the plane being at 0,0,0
  /// @param[in] _wP the precision of the width, this is basically the steps (per quad) which will be
  ///    triangulated for each (wP == 1 will give 1 quad mad of 2 tris)
  /// @param[in] _dP the precision of the Depth, this is basically the steps (per quad) which will be
  ///    triangulated for each (wP == 1 will give 1 quad mad of 2 tris)
  /// @param[in] _vN The Vertex normal (used for each vertex)

  void CreateVBOQuadPlane(
                          const std::string &_name,
                          const Real _width,
                          const Real _depth,
                          const int _wP,
                          const int _dP,
                          const Vector &_vN
                         );
  /// \brief create a Quad Cone as a vbo with auto generated texture cords
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _base the base radius of the cone
  /// @param[in] _height the height of the cone
  /// @param[in] _slices the number of quad elements around the cone
  /// @param[in] _stacks the number of quad elements along the centeral axis
  void CreateVBOCone(
                     const std::string &_name,
                     const Real _base,
                     const Real _height,
                     const int _slices,
                     const int _stacks
                    );

  /// \brief create a Quad Cylinder as a vbo with auto generated texture cords
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _radius the base radius of the Cylinder
  /// @param[in] _height the height of the Cylinder
  /// @param[in] _slices the number of quad elements around the Cylinder
  /// @param[in] _stacks the number of quad elements along the centeral axis
  void CreateVBOCylinder(
                         const std::string &_name,
                         const Real _radius,
                         const Real _height,
                         const int _slices,
                         const int _stacks
                        );

  /// \brief create a trinagle fan disk (use as end caps for Cylinder etc)
  /// @param[in] _name the name of the object created used when drawing
  /// @param[in] _radius the disk radius
  /// @param[in] _slices the number of triangles to form the disk
  void CreateVBODisk(
                     const std::string &_name,
                     const Real _radius,
                     const int _slices
                     );

  /// \brief create a VBO based torus from rings of quads.
  /// @param[in] _name the name of the VBO created for calling with the draw method
  /// @param[in] _minorRadius the inner radius of the torus
  /// @param[in] _majorRadius the outer radius of the torus.
  /// @param[in] _nSides the precision (number of quads) for the majorRadius
  /// @param[in] _nRings the precision (number of quads) for the minor Radius
  /// @param[in] _flipTX flip the texture co-ord generation default false.
  void CreateVBOTorus(
                      const std::string &_name,
                      const Real _minorRadius,
                      const Real _majorRadius,
                      int _nSides,
                      int _nRings,
                      const bool _flipTX=false
                      );
  /// \brief Draw one of the VBO's created via a name lookup
  /// @param[in] _name the name of the VBO to lookup in the VBO map
  /// \todo add support for different VBO draw modes

  void DrawVBO(
               const std::string &_name
              );

  /// \brief allow us to remove a VBO from the map and also destroy the VBO on the GPU
  /// @param[in] _name the name of the VBO to remove
  void RemoveVBO(
                 const std::string &_name
                );

  /// \brief load a VBO from a binary file created from Obj2VBO program
  /// @param[in] _name the name of the VBO to be stored as ref to this object
  /// @param[in] _fName the name of the file to load.
  /// @param[in] _type the draw mode type
  void LoadBinaryVBO(
                     const std::string &_name,
                     const std::string &_fName,
                     const GLenum _type
                     );

  /// \brief create a VBO from a static header file of data in the TNV format
  /// this will usually be created from the Obj2VBO program in the Models directory
  /// @param[in] _name the name reference for the VBO lookup
  /// @param[in] _data a pointer to the data to load
  /// @param[in] _Size the size of the array of data to load

  void CreateVBOFromHeader(
                           const std::string &_name,
                           Real const *_data,
                           const unsigned int _Size
                          );

  /// \brief get the size of the VBO buffer
  /// \returns the total allocated VBO buffer size for all the VBO's
  unsigned int GetTotalBufferSize();

  /// \brief map the VBO data by name to the client side so we can manipulate it
  /// @param[in] _name the name of the VBO to map
  /// @param[in] _size the size of the data mapped (this is the total number of Elements and not in bytes
  ///  this makes it easier to loop for all elements.
  /// \returns a pointer to the VBO data if it exist else 0
  VBOData *MapVBO(
                  const std::string &_name,
                  GLint &_size
                 );

  /// \brief unmap the VBO based on the name reference passed
  /// @param[in] _name the name of the VBO to unmap (will check to see if it has been mapped)
  void UnMapVBO(
                const std::string &_name
               );

  /// \brief clear the VBO elements created (is also called by dtor) This is usefull if you
  /// don't want the default primitives
  void ClearVBOs();

  /// \brief create the default VBO's this is done by the ctor anyway but can be called
  /// if the clear method is called. Note you will need to incude VBOHeaders in the client side
  void CreateDefaultVBOs();

  /// \brief a Method to draw vertex normals stored in the VBO usefull for debugging.
  /// Note that this uses direct mode GL so will be slow
  /// @param[in] _name the name of the VBO to access
  /// @param[in] _scalar a scale factor to make the normals a different size
  void DrawNormals(
                   const std::string &_name,
                   const Real _scalar=1.0
                  );

  /// \brief a method to draw a point at each vertex for debugging purposes (slow as uses direct mode GL)
  /// @param[in] _name the name of the VBO to access
  /// @param[in] _pointSize the size of the point to draw
  void DrawVerts(
                 const std::string &_name,
                 const Real _pointSize=4.0
                );

  /// \brief a method to draw a face normal  for debugging purposes (slow as uses direct mode GL)
  /// @param[in] _name the name of the VBO to access
  /// @param[in] _scalar the size of the point to draw

  void DrawFaceNormals(
                       const std::string _name,
                       const Real _scalar=1.0
                      );

private :
 // /// pointer to the singleton instance of this class
 // static VBOPrimitives* s_pinstance;

  ///  a map to store the VBO by name
  std::map <std::string,VBOObject *> m_createdVBOs;

  /// \brief flag to indicate if we currently have a vbo mapped
  bool m_vboMapped;

  //m_vertices is used to store the actual VBO data this is destroyed after the VBO is created
  VBOData *m_vertices;

  /// \brief default constructor
  VBOPrimitives();

	/// \brief helper function to set the individual VBO elements
	/// @param[in] _index index into the array \todo add assert to check this at some stage for debug mode
	/// @param[in] _tu the u texture cord
	/// @param[in] _tv the v texture cord
	/// @param[in] _nx x vertex normal value (normalize before passing for best results)
	/// @param[in] _ny y vertex normal value (normalize before passing for best results)
	/// @param[in] _nz z vertex normal value (normalize before passing for best results)
	/// @param[in] _vx the vertex x position
	/// @param[in] _vy the vertex y position
	/// @param[in] _vz the vertex z position

  void SetVertData(
                   const int _index,
                   const Real _tu,
                   const Real _tv,
                   const Real _nx,
                   const Real _ny,
                   const Real _nz,
                   const Real _vx,
                   const Real _vy,
                   const Real _vz
                  )  ;

  /// \brief allocate the memory for the verts into the Vertices pointer
  /// @param[in] _buffSize the ammount of memory to allocate
  void AllocVertMemory(
                       const unsigned int _buffSize
                      );

  /// \brief free the memory allocated in the Alloc Method
  void FreeVertMemory();

  /// \brief the method to actually create the VBO from the various other methods
  /// Note this is used in conjunciton with the Vertices attribute
  /// @param[in] _name the name to store in the map of the VBO
  /// @param[in] _nVerts the number of verts to store
  /// @param[in] _mode the mode to draw
  void CreateVBO(
                 const std::string &_name,
                 const unsigned int _nVerts,
                 const GLenum _mode
                );

  /// \brief create the elements of a circle this is borrowed from freeglut
  /// @param[in,out] io_sint a pointer to the sin elements of the table
  /// @param[in,out] io_cost a pointer to the cos element of the table
  /// @param[in] _n the number of points to calculate.
  void fghCircleTable(
                      double **io_sint,
                      double **io_cost,
                      const int _n
                     );
  pthread_mutex_t m_cs_mutex;
};// end class;

}; //end ngl namespace


#endif

