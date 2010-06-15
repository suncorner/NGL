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
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>

#include "AbstractMesh.h"
#include "Util.h"
#include "Texture.h"


namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::DrawBBox() const
{
	m_ext->Draw();
}

void AbstractMesh::Scale(
                         Real _sx,
                         Real _sy,
                         Real _sz
                        )
{
	m_center=0;
	for (unsigned long int i=0; i<m_nVerts; ++i)
	{
		m_verts[i].m_x*=_sx;
		m_verts[i].m_y*=_sy;
		m_verts[i].m_z*=_sz;
		m_center+=m_verts[i];
	}
	// calculate the center
	m_center/=m_nVerts;
  CalcDimensions();
}



//----------------------------------------------------------------------------------------------------------------------
AbstractMesh::~AbstractMesh()
{
  if(m_loaded == true)
  {
    m_verts.erase(m_verts.begin(),m_verts.end());
    m_norm.erase(m_norm.begin(),m_norm.end());
    m_tex.erase(m_tex.begin(),m_tex.end());
    m_face.erase(m_face.begin(),m_face.end());
    m_indices.erase(m_indices.begin(),m_indices.end());
    m_outIndices.erase(m_outIndices.begin(),m_outIndices.end());

    if(m_vbo)
    {
      glDeleteBuffers(1,&m_vboBuffers);

    }
    if(m_ext !=0)
    {
      delete m_ext;
    }
  }
}


//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::LoadTexture(
                               const std::string& _fName
                              )
{
	// load in the texture
	Texture  *t=new Texture(_fName);
	m_textureID=t->SetTextureGL();
	delete t;
	m_texture=true;
}

/// \todo correct the rib exporter and  add Normal information to  the export
/// \verbatim
/// The following code is adapted from an MSc project by
/// Authors: Elaine Kieran, Gavin Harrison, Luke Openshaw
/// Write the obj as a SubdivisionMesh package to the rib file
/// Renderman specification: SubdivisionMesh scheme nverts vertids tags nargs intargs floatargs parameterlist
/// \endverbatim

//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::WriteToRibSubdiv(
                                    RibExport& _ribFile
                                   )const
{
	// Declare the variables
	std::list< int > lVertLink;
	std::list< int >::iterator vertLinkItr;
	std::vector< float > vVerts;
	std::vector< float >::iterator vertsItr;

	// Check if the rib exists
  if( _ribFile.IsOpen() != 0 )
	{
		_ribFile.Comment( "OBJ AbstractMeshect" );
	// Start printing the SubdivisionPolygons tag to the rib
		_ribFile.GetStream() << "SubdivisionMesh \"catmull-clark\" [ ";

		// Loop through all the Polygons
		for (unsigned long  int I=0; I<m_nVerts; ++I)
		{
		// Print the count of vertices for the current polygon to the rib
		_ribFile.GetStream() << m_face[I].m_numVerts << " ";
		// Start building the vertids and parameterlist
		for (unsigned long int i = 0; i < m_face[I].m_numVerts; ++i)
		{
			// Set the verts vector size and testing variables
			int iVecSize = vVerts.size();
			bool bTest = false;
			int counter = 0;
			// Loop through the expanding vector checking whether
			// the current vertice exists
			for (int j = 0; j < iVecSize; j = j + 3)
			{
				// If the vertice if found in the vector, set the test
				// flag and exit the loop. Else keep going.
				if( ( FCompare(m_verts[i].m_x ,vVerts[j]) ) &&
					( FCompare(m_verts[i].m_y,vVerts[j + 1]) ) &&
					( FCompare(m_verts[i].m_y,vVerts[j + 2]) )
					 )
				{
					bTest = true;
					break;
				}
				else
				{
					counter++;
				}
			} //end for

			// Add the vertice to the vector if it is not found
			if( bTest == false )
			{
				vVerts.push_back( m_verts[m_face[I].m_vert[i]].m_x );
				vVerts.push_back( m_verts[m_face[I].m_vert[i]].m_y );
				vVerts.push_back( m_verts[m_face[I].m_vert[i]].m_z );
				lVertLink.push_back( counter );
			}
			else
			{
				lVertLink.push_back( counter );
			}

		}// end outer for

	}// end if

	_ribFile.GetStream() << "] [ ";

	// Print the vertids to the rib
	for (vertLinkItr = lVertLink.begin(); vertLinkItr != lVertLink.end(); vertLinkItr++)
	{
		_ribFile.GetStream() << *vertLinkItr << " ";
	}

	_ribFile.GetStream() << "] [\"interpolateboundary\"] [0 0] [] [] \"P\" [ ";
	// Print the parameterlist to the rib
	for (vertsItr = vVerts.begin(); vertsItr != vVerts.end(); vertsItr++)
	{
		_ribFile.GetStream() << *vertsItr << " ";
	}

	// Print new lines to the rib
	_ribFile.GetStream() << "]\n\n";
	}

}

//----------------------------------------------------------------------------------------------------------------------
bool AbstractMesh::CheckTriangular()
{
	for(unsigned int i=0; i<m_nFaces; ++i)
	{
		if (m_face[i].m_numVerts >3)
		{
			return false;
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
bool AbstractMesh::CheckQuad()
{
	unsigned int quadCount=0;
	for(unsigned int i=0; i<m_nFaces; ++i)
	{
		if (m_face[i].m_numVerts ==4)
		{
			++quadCount;
		}
	}
	if(quadCount == m_nFaces)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// Code from Rob Bateman (www.robthebloke.org)
// checks if v/n/t exist as a combination in the indices array. If it does, re-use that
// index and insert into the out_indices array. If the v/n/t combo has not been used before,
// generate a new vertex index....
//
//----------------------------------------------------------------------------------------------------------------------
bool AbstractMesh::AddIndex(
                            const unsigned _v,
                            const unsigned _n,
                            const unsigned _t,
                            std::vector<IndexRef>& io_indices,
                            std::vector<GLuint>& io_outIndices
                           )
{
	size_t size=io_indices.size();
	for(size_t i=0;i<size;++i)
	{
		// if v/n/t already exist, re-use...
		if(io_indices[i].m_v == _v && io_indices[i].m_n == _n && io_indices[i].m_t == _t)
		{
			io_outIndices.push_back((GLuint)i);
			return true;
		}
	}

	io_outIndices.push_back( (GLuint) io_indices.size() );
	io_indices.push_back(IndexRef(_v,_n,_t));
	return false;
}



//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::CreateVBO(
                             const GLint _mode
                            )
{
  // if we have already created a VBO just return.
	if(m_vbo == true)
  {
    return;
  }

  m_dataPackType=0;
	if(CheckTriangular())
	{
		m_dataPackType=GL_TRIANGLES;
		std::cout <<"Doing Tri Data"<<std::endl;
	}
	if(CheckQuad())
	{
		m_dataPackType=GL_QUADS;
		std::cout<<"doing Quad Data"<<std::endl;
	}
	// data is mixed of > quad so exit error
	if(m_dataPackType == 0)
	{
		std::cerr<<"Can only create VBO from all Triangle or ALL Quad data at present"<<std::endl;
		exit(EXIT_FAILURE);
	}
  /// create enough space for the num verts * 3 for the x,y,z components
  /// index mapping. Goes from original v/n/t indices to vertex array indices (implied by their position
  /// in the array). In the end this will be the same size as the resulting vertex data array.
  ///
  /// the output list of triangle indices. This will be the same size as num_tris*3.
  ///
  /// get all v/n/t combo's from the triangle data
  ///
	int loopFaceCount=3;
	if(m_dataPackType == GL_QUADS)
	{
		loopFaceCount=4;
	}
	for(unsigned int i=0;i<m_nFaces;++i)
	{
		for(int j=0;j<loopFaceCount;++j)
		{
      // now we need to cope with the different face VTN combos
      // most likly case is all present
      if(m_nNorm >0 && m_nTex > 0)
      {
        AddIndex(m_face[i].m_vert[j], m_face[i].m_norm[j],m_face[i].m_tex[j],m_indices,m_outIndices);
      }
      // now if neither are present (only verts like Zbrush models)
      else if(m_nNorm ==0 && m_nTex==0)
      {
        AddIndex(m_face[i].m_vert[j], 0,0,m_indices,m_outIndices);
      }
      // here we've got norms but not tex
      else if(m_nNorm >0 && m_nTex==0)
      {
        AddIndex(m_face[i].m_vert[j], m_face[i].m_norm[j],0,m_indices,m_outIndices);
      }
      // here we've got tex but not norm least common
      else if(m_nNorm ==0 && m_nTex>0)
      {
        AddIndex(m_face[i].m_vert[j], 0,m_face[i].m_tex[j],m_indices,m_outIndices);
      }


    }
	}

	m_indexSize=m_indices.size();
	// the generate your Verts/Norms/Uvs
	GLfloat *vboVerts = new GLfloat[ 3*m_indexSize];
	GLfloat *vboNorms = new GLfloat[ 3*m_indexSize];
	GLfloat *vboUvs = new GLfloat[ 2*m_indexSize];

	size_t size=m_indices.size();
	for(size_t i=0;i<size;++i)
	{
		vboVerts[i*3+0] = m_verts[m_indices[i].m_v ].m_x;
		vboVerts[i*3+1] = m_verts[m_indices[i].m_v ].m_y;
		vboVerts[i*3+2] = m_verts[m_indices[i].m_v ].m_z;
    if(m_nNorm !=0)
    {
      vboNorms[i*3+0] = m_norm[ m_indices[i].m_n ].m_x;
      vboNorms[i*3+1] = m_norm[ m_indices[i].m_n ].m_y;
      vboNorms[i*3+2] = m_norm[ m_indices[i].m_n ].m_z;
    }
    if(m_nTex !=0)
    {
      vboUvs[i*2+0] =   m_tex[  m_indices[i].m_t ].m_x;
      vboUvs[i*2+1] =   m_tex[  m_indices[i].m_t ].m_y;
    }
   }


  glGenBuffers(1, &m_vboBuffers);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboBuffers);
  // check what size to create the buffer array for example if we didn't load
  // tex or norm infor don't bother with it.
  int bufferPackSize=3;
  if(m_nTex  !=0) { bufferPackSize+=2; }
  if(m_nNorm !=0) { bufferPackSize+=3; }
  m_bufferPackSize=bufferPackSize;
	// resize buffer
  glBufferData(GL_ARRAY_BUFFER, m_indexSize*bufferPackSize*sizeof(GLfloat), 0, _mode);
  //std::cout<<"This is the size I'm allocating for VBO "<<m_indexSize*bufferPackSize*sizeof(GLfloat)<<std::endl;
	// upload verts/norms/uvs into the same buffer (could interleave if you preffered).
	glBufferSubData(GL_ARRAY_BUFFER,0, m_indexSize*(3*sizeof(GLfloat)),vboVerts);
	if(m_nNorm !=0)
  {
    glBufferSubData(GL_ARRAY_BUFFER,m_indexSize*(3*sizeof(GLfloat)), m_indexSize*(3*sizeof(GLfloat)),vboNorms);
  }
  if(m_nTex !=0)
  {
    glBufferSubData(GL_ARRAY_BUFFER,m_indexSize*(6*sizeof(GLfloat)), m_indexSize*(2*sizeof(GLfloat)),vboUvs);
  }
  // get rid of the data
	delete [] vboVerts;
	delete [] vboNorms;
	delete [] vboUvs;
  m_vbo=true;

}

//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::DrawVBO() const
{
	#define BUFFER_OFFSET(i) ((float *)NULL + (i))
	if(m_texture==true)
	{
		glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_textureID);
	}
	glEnableClientState(GL_VERTEX_ARRAY);
  if(m_nNorm !=0)
  {
    glEnableClientState(GL_NORMAL_ARRAY);
  }
  if(m_nTex !=0)
  {
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  }
	glBindBuffer(GL_ARRAY_BUFFER, m_vboBuffers);
	glVertexPointer(3,GL_FLOAT,sizeof(float)*3,BUFFER_OFFSET(0));
  if(m_nNorm !=0)
  {
    glNormalPointer(GL_FLOAT,sizeof(float)*3,BUFFER_OFFSET(m_indexSize*3));
  }
  if(m_nTex !=0)
  {
    glTexCoordPointer(2,GL_FLOAT,sizeof(float)*2,BUFFER_OFFSET(m_indexSize*6));
  }
	glDrawElements(m_dataPackType,m_outIndices.size(),GL_UNSIGNED_INT,&m_outIndices[0]);

  glDisableClientState(GL_VERTEX_ARRAY);
  if(m_nNorm !=0)
  {
    glDisableClientState(GL_NORMAL_ARRAY);
  }
  if(m_nTex !=0)
  {
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
  if(m_texture==true)
	{
		glDisable(GL_TEXTURE_2D);
	}
}


//----------------------------------------------------------------------------------------------------------------------
Real * AbstractMesh::MapVBOVerts()
{
	Real* ptr=0;

	// make sure we have a valid vbo
	// enable the correct client states for VBO's
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glVertexPointer(3,GL_FLOAT,sizeof(float)*3,BUFFER_OFFSET(0));

	// bind our VBO data
	glBindBuffer(GL_ARRAY_BUFFER, m_vboBuffers);

	ptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
	m_vboMapped=true;
	return ptr;
}

//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::UnMapVBO()
{
	if(m_vboMapped==true)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vboBuffers);
		glUnmapBufferARB(GL_ARRAY_BUFFER); // unmap it after use
		// enable the correct client states for VBO's
		glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		m_vboMapped=false;
	}
}
//----------------------------------------------------------------------------------------------------------------------
void AbstractMesh::CalcDimensions()
{
  // Calculate the center of the object.
  m_center=0.0;
  BOOST_FOREACH(Vector v,m_verts)
  {
    m_center+=v;
  }
  m_center/=m_nVerts;
  // calculate the extents
  BOOST_FOREACH(Vector v,m_verts)
  {
    if     (v.m_x >m_maxX) { m_maxX=v.m_x; }
    else if(v.m_x <m_minX) { m_minX=v.m_x; }
    if     (v.m_y >m_maxY) { m_maxY=v.m_y; }
    else if(v.m_y <m_minY) { m_minY=v.m_y; }
    if     (v.m_z >m_maxZ) { m_maxZ=v.m_z; }
    else if(v.m_z <m_minZ) { m_minZ=v.m_z; }
  } // end BOOST_FOREACH


  // destroy the previous bounding box
  if(m_ext !=0)
  {
    delete m_ext;

  }
  // create a new bbox based on the new object size
  m_ext=new BBox(m_minX,m_maxX,m_minY,m_maxY,m_minZ,m_maxZ);

}

void AbstractMesh::SaveNCCABinaryMesh(
                                       const std::string _fname
                                     )
{
// so basically we need to save all the state data from the abstract mesh
// then map the vbo on the gpu and dump that in one go, this means we have to
// call CreateVBO first the Save
  std::fstream file;
  file.open(_fname.c_str(),std::ios::out | std::ios::binary);
  if (!file.is_open())
  {
    std::cerr<<"problems Opening File "<<_fname<<std::endl;
    return;
  }
  // lets write out our own Magic Number file ID
  const std::string header("ngl::bin");
  file.write(header.c_str(),header.length());
  /// The number of vertices in the object
  file.write(reinterpret_cast <char *>(&m_nVerts),sizeof(unsigned long int));
  /// The number of normals in the object
  file.write(reinterpret_cast <char *>(&m_nNorm),sizeof(unsigned long int));

  /// the number of texture co-ordinates in the object
  file.write(reinterpret_cast <char *>(&m_nTex),sizeof(unsigned long int));

  /// the number of faces in the object
  file.write(reinterpret_cast <char *>(&m_nFaces),sizeof(unsigned long int));
  file.write(reinterpret_cast <char *>(&m_center.m_x),sizeof(ngl::Real));
  file.write(reinterpret_cast <char *>(&m_center.m_y),sizeof(ngl::Real));
  file.write(reinterpret_cast <char *>(&m_center.m_z),sizeof(ngl::Real));

  file.write(reinterpret_cast <char *>(&m_texture),sizeof(bool));

  file.write(reinterpret_cast <char *>(&m_maxX),sizeof(ngl::Real));
  file.write(reinterpret_cast <char *>(&m_maxY),sizeof(ngl::Real));
  file.write(reinterpret_cast <char *>(&m_maxZ),sizeof(ngl::Real));
  file.write(reinterpret_cast <char *>(&m_minX),sizeof(ngl::Real));
  file.write(reinterpret_cast <char *>(&m_minY),sizeof(ngl::Real));
  file.write(reinterpret_cast <char *>(&m_minZ),sizeof(ngl::Real));

  file.write(reinterpret_cast <char *>(&  m_dataPackType),sizeof(GLuint));
  file.write(reinterpret_cast <char *>(&  m_indexSize),sizeof(unsigned int));
  file.write(reinterpret_cast <char *>(&  m_bufferPackSize),sizeof(unsigned int));
  /// now we can dump the data from the vbo
  unsigned int size=m_indexSize*m_bufferPackSize*sizeof(GLfloat);
  std::cout<<"size is"<<size<<std::endl;
  file.write(reinterpret_cast <char *>(&size),sizeof(unsigned int));


  Real *vboMem=this->MapVBOVerts();
  file.write(reinterpret_cast<char *>(vboMem),size);

  // now write the indices
  // first the size
  size=m_outIndices.size();
  std::cout<<"Size of out indices ="<<size<<std::endl;
  file.write(reinterpret_cast <char *>(&size),sizeof(unsigned int));
  for( unsigned int i=0; i<size; ++i)
  {
    file.write(reinterpret_cast <char *>(&m_outIndices[i]),sizeof(unsigned int));
    //std::cout<<m_outIndices[i]<<std::endl;
  }


  file.close();
  this->UnMapVBO();

}




}; //end ngl namespace


