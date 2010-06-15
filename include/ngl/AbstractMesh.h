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
#ifndef __ABSTRACT_MESH_H__
#define __ABSTRACT_MESH_H__

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"

#include <vector>
#include "Texture.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "Vector.h"
#include "BBox.h"
#include "RibExport.h"
#include <cmath>
#include <boost/tokenizer.hpp>

namespace ngl
{

enum MeshFormat{TRIANGLE,QUAD,POLY};
/// pre-define the boost tokenizer so we don't have to use the full dec
typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

/// \class ObjFace  "include/Obj.h"
/// \brief   simple class used to encapsulate a single face of an Obj file

class Face
{
public :
  /// the number of vertices in the face
  unsigned int m_numVerts;
  /// The vertices index
  std::vector<unsigned long int> m_vert;
  /// The texture co-ord index
  std::vector<unsigned long int> m_tex;
  /// the normal index
  std::vector<unsigned long int> m_norm;
  /// debug flag to turn face on and off
  bool m_textureCoord;
};

/// \class IndexRef
/// \brief a class to hold the index into vert / norm and tex list for creating the VBO data structure

class IndexRef
{
public :

  /// index into the vert list
  unsigned m_v;
  /// index into the nornmal list
  unsigned m_n;
  /// index into the texture list
  unsigned m_t;
  /// ctor to set the data
  /// @param[in] _v the vert index
  /// @param[in] _n the normal index
  /// @param[in] _t the texture index

  inline IndexRef(
                  unsigned _v,
                  unsigned _n,
                  unsigned _t
                 ):m_v(_v),m_n(_n),m_t(_t){;}
};

/// \class AbstractMesh "include/AbstractMesh.h"
///  \author Jonathan Macey
///    \version 1.0
///    \date 24/09/09 Last Revision 24/09/09
///  \brief an abstract base mesh used to build specific meshes such
/// as Obj

class AbstractMesh
{

public :

  /// Method to load the file in
  /// @param[in]  &_fname the name of the obj file to load
  virtual bool Load(const std::string &_fname)=0;
  /// \brief default ctor must be called from the child class so our dtor is called
  AbstractMesh(){;};
  /// \brief destructor this will clear out all the vert data and the vbo if created
  virtual ~AbstractMesh();
  /// \brief method to draw the bounding box
  void DrawBBox() const;
  /// \brief draw method to draw the obj as a VBO. The VBO first needs to be created using the CreateVBO method
  void DrawVBO() const;

  /// \brief load int a texture and set it as the active texture of the Obj
  /// @param[in] &_fname the name of the file to load
  void LoadTexture(
                   const std::string& _fname
                  );

  /// \brief scale the obj by dividing the actual vertex values by sx,sy and sz
  /// @param[in] _sx the scale value in x
  /// @param[in] _sy the scale value in y
  /// @param[in] _sz the scale value in z
  void Scale(
             const Real _sx,
             const Real _sy,
             const Real _sz
            );

 /// \brief a method to set the BBox and center
  void CalcDimensions();
  /// method to write out the obj mesh to a renderman sub div
  /// @param[in] _ribFile the instance of the RibExport class
  void WriteToRibSubdiv(
                        ngl::RibExport& _ribFile
                       ) const;
  /// create a VBO from the mesh data must be called before drawing
  /// @param[in] _mode The mode in wich to create the VBO can be any of
  ///   \verbatim
  /// STREAM_DRAW
  /// STREAM_READ
  /// STREAM_COPY
  /// STATIC_DRAW
  /// STATIC_READ
  /// STATIC_COPY
  /// DYNAMIC_DRAW
  /// DYNAMIC_READ
  /// DYNAMIC_COPY
  /// \endverbatim
    void CreateVBO(
                   const GLint _mode
                  );
 
  /// get the texture id
  /// \returns the texture id

  unsigned int GetTextureID() const { return m_textureID; } ;

  /// map the VBO vertex data
  /// \returns a pointer to the VBO vertex data
  Real *MapVBOVerts();

  /// \brief unmap the VBO based
  void UnMapVBO();

  /// get a pointer to the indices used to represent the VBO data, this is used in the clip
  /// class when re-ordering the clip data values
  /// \returns the array of indices
  inline const std::vector<IndexRef> & GetIndices() { return m_indices; };
  /// @brief save the mesh as NCCA Binary VBO format
  /// basically this format is the processed binary vbo mesh data as 
  /// as packed by the CreateVBO() method is called.
  void SaveNCCABinaryMesh(
                          const std::string _fname
                         );
  /// @brief a method to get the current bounding box of the mesh
  /// @returns the bounding box for the loaded mesh;
  inline BBox *GetBBox()
                        {
                          return m_ext;
                        }

protected :

  /// The number of vertices in the object
  unsigned long int m_nVerts;
  /// The number of normals in the object
  unsigned long int m_nNorm;
  /// the number of texture co-ordinates in the object
  unsigned long int m_nTex;
  /// the number of faces in the object
  unsigned long int m_nFaces;
  /// Pointer to the Vertex list
  std::vector<Vector> m_verts;
  /// Pointer to the Normal List
  std::vector<Vector> m_norm;
  /// Pointer to the Textur co-ord list (note that only x and y are used)
  std::vector<Vector> m_tex;
  /// Pointer to the Face list
  std::vector<Face> m_face;
  /// Center of the object
  Vector m_center;
    /// a vector of indices used to pass the index into the Data arrays to the VBO
  std::vector<IndexRef> m_indices;
  /// a vectr of indices without duplicates which are actually passed to the VBO when creating
  std::vector<GLuint> m_outIndices;
  /// the size of the index array
  unsigned int m_indexSize;
  // buffers for the VBO in order Vert, Tex, Norm
  GLuint m_vboBuffers;
  /// flag to indicate if a VBO has been created
  bool m_vbo;
  /// flag to indicate if the VBO vertex data has been mapped
  bool m_vboMapped;
  /// flag to indicate if texture assigned
  bool m_texture;
  /// The openGL id  of the texture for the texture generation
  unsigned int m_textureID;
  /// The Maximum X value in the obj file used to calculate the extents bbox
  Real m_maxX;
  /// The Min X value in the obj file used to calculate the extents bbox
  Real m_minX;
  /// The Max Y value in the obj file used to calculate the extents bbox
  Real m_maxY;
  /// The Min Y value in the obj file used to calculate the extents bbox
  Real m_minY;
  /// The Max Z value in the obj file used to calculate the extents bbox
  Real m_maxZ;
  /// The Min Z value in the obj file used to calculate the extents bbox
  Real m_minZ;
  ///  Create a bounding box of the object to store it's extents
  BBox *m_ext;
 	/// determines if the data is Packed as either TRI or QUAD
	GLuint m_dataPackType;
  /// the size of the buffer pack we use this for the saving of bin vbo
  /// but it actually holds the size of the data (3 for just verts 5 verts norms etc)
  int  m_bufferPackSize;

  /// which type of VBO are we going to draw
  GLenum m_vboDrawType;

  /// \brief method used to add an index to the indices array as we need to re-order the data
  /// @param[in] _v the vertex index
  /// @param[in] _n the normal index
  /// @param[in] _t the texture index
  /// @param[in] io_indices the index list stored
  /// @param[in] io_outIndices the re-orderd list
  bool AddIndex(
                const unsigned _v,
                const unsigned _n,
                const unsigned _t,
                std::vector<IndexRef>& io_indices,
                std::vector<GLuint>& io_outIndices
               );


  /// \brief check to see if obj is triangulated as we only support tri or quad objs at the moment
  /// \returns true or false
  bool CheckTriangular();
  /// \brief check to see if obj is all quads
  bool CheckQuad();

  /// flag to indicate if anything loaded for dtor
  bool m_loaded;

};

}; // end of namespace ngl


#endif // end of the class

