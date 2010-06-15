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
#include "BBox.h"

namespace ngl
{
const static GLubyte indices[]=  {0,3,7,4,0,1,5,4,1,2,6,5,2,3,7,6,0,1,2,3,4,5,6,7};

//----------------------------------------------------------------------------------------------------------------------
BBox::BBox(
           const Vector& _center,
           const Real& _width,
           const Real& _height,
           const Real& _depth
          )
{

	// Calculate the Vertices based on the w,h,d params passed in the box is asumed
	// to be centered on the _center with equal w / h / d
	// -x +y -z

	m_vert[0].m_x=_center.m_x-(_width/2.0f); m_vert[0].m_y=_center.m_y+(_height/2.0f); m_vert[0].m_z=_center.m_z-(_depth/2.0f);
	// + x -y -z
	m_vert[1].m_x=_center.m_x+(_width/2.0f); m_vert[1].m_y=_center.m_y+(_height/2.0f); m_vert[1].m_z=_center.m_z-(_depth/2.0f);
	m_vert[2].m_x=_center.m_x+(_width/2.0f); m_vert[2].m_y=_center.m_y+(_height/2.0f); m_vert[2].m_z=_center.m_z+(_depth/2.0f);
	m_vert[3].m_x=_center.m_x-(_width/2.0f); m_vert[3].m_y=_center.m_y+(_height/2.0f); m_vert[3].m_z=_center.m_z+(_depth/2.0f);
	m_vert[4].m_x=_center.m_x-(_width/2.0f); m_vert[4].m_y=_center.m_y-(_height/2.0f); m_vert[4].m_z=_center.m_z-(_depth/2.0f);
	m_vert[5].m_x=_center.m_x+(_width/2.0f); m_vert[5].m_y=_center.m_y-(_height/2.0f); m_vert[5].m_z=_center.m_z-(_depth/2.0f);
	m_vert[6].m_x=_center.m_x+(_width/2.0f); m_vert[6].m_y=_center.m_y-(_height/2.0f); m_vert[6].m_z=_center.m_z+(_depth/2.0f);
	m_vert[7].m_x=_center.m_x-(_width/2.0f); m_vert[7].m_y=_center.m_y-(_height/2.0f); m_vert[7].m_z=_center.m_z+(_depth/2.0f);

	//Store the _center
	m_center=_center;
	// Setup the Plane Normals for Collision Detection
	m_norm[0].Set(0.0f,1.0f,0.0f);
	m_norm[1].Set(0.0f,-1.0f,0.0f);
	m_norm[2].Set(1.0f,0.0f,0.0f);
	m_norm[3].Set(-1.0f,0.0f,0.0f);
	m_norm[4].Set(0.0f,0.0f,1.0f);
	m_norm[5].Set(0.0f,0.0f,-1.0f);
	// store width height and depth
	m_width=_width;
	m_height=_height;
	m_depth=_depth;
	m_drawMode=GL_LINE;

}

//----------------------------------------------------------------------------------------------------------------------
BBox::BBox()
{
	//default constructor creates a unit BBox
	ngl::Vector c(0.0f,0.0f,0.0f);
	ngl::BBox(c,1.0f,1.0f,1.0f);
	m_center.m_x=m_center.m_y=m_center.m_z=0.0f;
	m_drawMode=GL_LINE;
  m_width=2.0;
  m_height=2.0;
  m_depth=2.0;

}
//----------------------------------------------------------------------------------------------------------------------
BBox::BBox(
           const Real& _minX,
           const Real& _maxX,
           const Real& _minY,
           const Real& _maxY,
           const Real& _minZ,
           const Real& _maxZ
          )
{
	m_minX=_minX;
	m_maxX=_maxX;
	m_minY=_minY;
	m_maxY=_maxY;
	m_minZ=_minZ;
	m_maxZ=_maxZ;


	m_center.Set(0,0,0);

	m_vert[0].m_x=_minX; m_vert[0].m_y=_maxY; m_vert[0].m_z=_minZ;
	m_vert[1].m_x=_maxX; m_vert[1].m_y=_maxY; m_vert[1].m_z=_minZ;
	m_vert[2].m_x=_maxX; m_vert[2].m_y=_maxY; m_vert[2].m_z=_maxZ;
	m_vert[3].m_x=_minX; m_vert[3].m_y=_maxY; m_vert[3].m_z=_maxZ;

	m_vert[4].m_x=_minX; m_vert[4].m_y=_minY; m_vert[4].m_z=_minZ;
	m_vert[5].m_x=_maxX; m_vert[5].m_y=_minY; m_vert[5].m_z=_minZ;
	m_vert[6].m_x=_maxX; m_vert[6].m_y=_minY; m_vert[6].m_z=_maxZ;
	m_vert[7].m_x=_minX; m_vert[7].m_y=_minY; m_vert[7].m_z=_maxZ;
	m_drawMode=GL_LINE;
  m_width=m_maxX-m_minX;
  m_height=m_maxY-m_minY;
  m_depth=m_maxZ-m_minZ;

}

//----------------------------------------------------------------------------------------------------------------------
void BBox::ResetDrawMode(
                         const GLenum& _mode
                        )
{
  m_drawMode=_mode;
}


//----------------------------------------------------------------------------------------------------------------------
void BBox::Draw() const
{

	glPushMatrix();
		glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_CURRENT_BIT);
			glDisable(GL_LIGHTING);
			glPolygonMode(GL_FRONT_AND_BACK,m_drawMode);
			// activate and specify pointer to vertex array
			glEnableClientState(GL_VERTEX_ARRAY);
			//std::cout<<"VBO"<<m_VBOBuffer<<std::endl;
			// now bind the buffer
			glBindBuffer(GL_ARRAY_BUFFER,0);
			// m_vert is an array of Vectors the ngl::Vector stores data in a 4 tuple of
			// x,y,z,w so we can basically use 4 as the span for the vertex pointer and it
			// will assume that the data is packed in contiguous blocks packed as 4 * GL_FLOAT
			// so we can pass this as the VertexPointer
			glVertexPointer(4, GL_FLOAT, 0,m_vert);

			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
			// draw a cube
			// deactivate vertex arrays after drawing
			glDisableClientState(GL_VERTEX_ARRAY);

		glPopAttrib();
	glPopMatrix();

}
//----------------------------------------------------------------------------------------------------------------------

BBox::~BBox()
{

}
//----------------------------------------------------------------------------------------------------------------------

}; // end namespace ngl



