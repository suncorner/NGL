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
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>

#include "VBOPrimitives.h"
#include "Util.h"
#include "Texture.h"


#include "Football.h"
#include "Cube.h"
#include "Teapot.h"
#include "Octahedron.h"
#include "Dodecahedron.h"
#include "Icosahedron.h"
#include "Tetrahedron.h"
#include <pthread.h>
namespace ngl
{


//----------------------------------------------------------------------------------------------------------------------
VBOPrimitives::VBOPrimitives()
{
	m_vertices=0;
	CreateDefaultVBOs();
	m_vboMapped=false;
 // m_cs_mutex=PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_init( &m_cs_mutex,NULL);
}


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateDefaultVBOs()
{
	// load into the vbo list some basic primitives (these are created in .h file arrays from Obj2VBO)
	// Obj2VBO and the original models may be found in the Models directory

  CreateVBOFromHeader("teapot",teapot,teapotSIZE);
	CreateVBOFromHeader("octahedron",Octahedron,OctahedronSIZE);
	CreateVBOFromHeader("dodecahedron",dodecahedron,dodecahedronSIZE);
	CreateVBOFromHeader("icosahedron",icosahedron,icosahedronSIZE);
	CreateVBOFromHeader("tetrahedron",tetrahedron,tetrahedronSIZE);
	CreateVBOFromHeader("football",football,footballSIZE);
	CreateVBOFromHeader("cube",cube,cubeSIZE);

}


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::ClearVBOs()
{
	// create an iterator for our map.
	// not the iterator gives us two components .first .second which lets us access the key,object elements
	std::map<std::string,VBOObject *>::iterator it;
	// grab an iterator to the end to make loop quicker
	std::map<std::string,VBOObject *>::iterator end=m_createdVBOs.end();

	//std::cout<<"Buffer size = "<<GetTotalBufferSize()<<"\n";

	// loop through the map and delete the VBO's allocated
	// note glDeleteBuffers needs a const GLUint * so we need to de-reference the map object
	for( it=m_createdVBOs.begin() ; it != end; ++it )
	{
		glDeleteBuffers(1,&((*it).second->m_vbo));
	}
	m_createdVBOs.erase(m_createdVBOs.begin(),m_createdVBOs.end());
}


//----------------------------------------------------------------------------------------------------------------------
VBOData * VBOPrimitives::MapVBO(
                                const std::string &_name,
                                GLint &_size
                               )
{
	VBOObject *vbo=m_createdVBOs[_name];
	Real* ptr=0;
	_size=0;
	// make sure we have a valid vbo
	if(vbo!=0)
	{
		// enable the correct client states for VBO's
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		// bind our VBO data
		glBindBuffer(GL_ARRAY_BUFFER, vbo->m_vbo);
		glInterleavedArrays(GL_T2F_N3F_V3F, 0, (char *) NULL);

		ptr = (float*)glMapBufferARB(GL_ARRAY_BUFFER, GL_READ_WRITE);
		glGetBufferParameteriv(GL_ARRAY_BUFFER,GL_BUFFER_SIZE,&_size);
		_size/=(sizeof(VBOData));
		m_vboMapped=true;
  }
// map it to our VBOData class from a raw pointer
return reinterpret_cast<VBOData *>(ptr);
}


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::UnMapVBO(
                             const std::string &_name
                            )
{
	if(m_vboMapped)
	{
		VBOObject *vbo=m_createdVBOs[_name];
		if(vbo!=0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vbo->m_vbo);
			glUnmapBufferARB(GL_ARRAY_BUFFER); // unmap it after use
			// enable the correct client states for VBO's
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			m_vboMapped=false;
		} // end if vbo
	}// end if mapped
}



//----------------------------------------------------------------------------------------------------------------------
unsigned int VBOPrimitives::GetTotalBufferSize()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	unsigned int size=0;
	// create an iterator for our map.
	// not the iterator gives us two components .first .second which lets us access the key,object elements
	std::map<std::string,VBOObject *>::iterator it;
	// grab an iterator to the end to make loop quicker
	std::map<std::string,VBOObject *>::iterator end=m_createdVBOs.end();
	int t=0;
	for( it=m_createdVBOs.begin() ; it != end; ++it )
	{
		// bind each vbo in turn
		glBindBuffer(GL_ARRAY_BUFFER,(*it).second->m_vbo);
		// grab the buffer
		glGetBufferParameteriv(GL_ARRAY_BUFFER,GL_BUFFER_SIZE,&t);
		size+=t;
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	return size/(sizeof(VBOData));
}


//----------------------------------------------------------------------------------------------------------------------
VBOPrimitives::~VBOPrimitives()
{
	ClearVBOs();
}


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::AllocVertMemory(
                                    const unsigned int _buffSize
                                   )
{
	if( m_vertices != 0 )
	{
		delete []m_vertices;
	}
	m_vertices = new VBOData[_buffSize];
}


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::FreeVertMemory()
{
	if(m_vertices !=0)
	{
		delete []m_vertices;
	}
}


//----------------------------------------------------------------------------------------------------------------------
/// \todo write code to put VBO type into the file and use the type param
void VBOPrimitives::LoadBinaryVBO(
                                  const std::string &_name,
                                  const std::string &_fName,
                                  const GLenum _type=GL_TRIANGLES
                                 )
{
	std::fstream binfile;
	binfile.open(_fName.c_str(),std::ios::in|std::ios::binary);
	if(!binfile.is_open())
	{
		std::cerr<<"problems Opening File "<<_fName<<std::endl;
		return;
	}
	unsigned int size;
	binfile>>size;
	unsigned int indexSize;
	binfile>>indexSize;

	//std::cout <<"Loading "<<size<<" bytes "<<IndexSize<<std::endl;
	Real *data = new Real[size];

	for(unsigned int i=0; i<size; ++i)
	{
		binfile>>data[i];
	}
	GLuint VBOBuffers;

	// now create the VBO
	glGenBuffers(1, &VBOBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, VBOBuffers);


	glInterleavedArrays(GL_T2F_N3F_V3F, 0, (char *) NULL);
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

  m_createdVBOs[_name]= new VBOObject(indexSize,VBOBuffers,_type);
}


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateVBO(
                              const std::string &_name,
                              unsigned int _nVerts,
                              const GLenum _mode
                             )
{
	GLuint VBOBuffers;
	// now create the VBO
	glGenBuffers(1, &VBOBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, VBOBuffers);
	glInterleavedArrays(GL_T2F_N3F_V3F, 0, (char *) NULL);
	glBufferData(GL_ARRAY_BUFFER, _nVerts*sizeof(VBOData), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _nVerts*sizeof(VBOData), m_vertices);
	FreeVertMemory();
	m_vertices=0;
	m_createdVBOs[_name]= new VBOObject(_nVerts,VBOBuffers,_mode);
}



//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::SetVertData(
                                const int _index,
                                const Real _tu,
                                const Real _tv,
                                const Real _nx,
                                const Real _ny,
                                const Real _nz,
                                const Real _vx,
                                const Real _vy,
                                const Real _vz
                               )
{
	(m_vertices+_index)->m_tu = _tu;
	(m_vertices+_index)->m_tv = _tv;
	(m_vertices+_index)->m_nx = _nx;
	(m_vertices+_index)->m_ny = _ny;
	(m_vertices+_index)->m_nz = _nz;
	(m_vertices+_index)->m_vx = _vx;
	(m_vertices+_index)->m_vy = _vy;
	(m_vertices+_index)->m_vz = _vz;
}




//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateVBOFromHeader(
                                        const std::string &_name,
                                        const Real *_data,
                                        const unsigned int _size
                                       )
{
	GLuint VBOBuffers;
	// now create the VBO
	glGenBuffers(1, &VBOBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, VBOBuffers);

	glInterleavedArrays(GL_T2F_N3F_V3F, 0,  (char *) NULL);
	glBufferData(GL_ARRAY_BUFFER, (_size)*sizeof(GLfloat), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, (_size)*sizeof(GLfloat), _data);
	// the data size is based on the VBOData structure, if we add more data we need to change
	// the size so calculate it based on VBOData / float (should be 8 at present)
	m_createdVBOs[_name]= new VBOObject(_size/(sizeof(VBOData)/sizeof(GLfloat)),VBOBuffers,GL_TRIANGLES);
}


//----------------------------------------------------------------------------------------------------------------------
// code modified from the elements below
// Name: createSphereGeometry()
// Desc: Creates a sphere as an array of vertex data suitable to be fed into a
//       OpenGL vertex array. The sphere will be centered at cy, cx, cz with
//       radius r, and _precision p. Based on a function Written by Paul Bourke.
//       http://astronomy.swin.edu.au/~pbourke/opengl/sphere/
//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateVBOSphere(
                                    const std::string &_name,
                                    Real _radius,
                                    int _precision
                                   )
{
	int buffSize;

	float theta1 = 0.0;
	float theta2 = 0.0;
	float theta3 = 0.0;

	float ex = 0.0f;
	float ey = 0.0f;
	float ez = 0.0f;

	float px = 0.0f;
	float py = 0.0f;
	float pz = 0.0f;

	float tu  = 0.0f;
	float tv  = 0.0f;

	buffSize = (_precision/2) * ((_precision+1)*2);
	AllocVertMemory(buffSize);
	// Disallow a negative number for radius.
	if( _radius < 0 )
	{
		_radius = -_radius;
	}
	// Disallow a negative number for _precision.
	if( _precision < 4 )
	{
		_precision = 4;
	}
	int k = -1;

	for( int i = 0; i < _precision/2; ++i )
	{
		theta1 = i * TWO_PI / _precision - PI2;
		theta2 = (i + 1) * TWO_PI / _precision - PI2;

		for( int j = 0; j <= _precision; ++j )
		{
			theta3 = j * TWO_PI / _precision;

			ex = cosf(theta2) * cosf(theta3);
			ey = sinf(theta2);
			ez = cosf(theta2) * sinf(theta3);
			px = _radius * ex;
			py = _radius * ey;
			pz = _radius * ez;
			tu  = -(j/(float)_precision);
			tv  = 2*(i+1)/(float)_precision;
			++k;
			SetVertData( k, tu, tv, ex, ey, ez, px, py, pz );

			ex = cosf(theta1) * cosf(theta3);
			ey = sinf(theta1);
			ez = cosf(theta1) * sinf(theta3);
			px = _radius * ex;
			py = _radius * ey;
			pz = _radius * ez;
			tu  = -(j/(float)_precision);
			tv  = 2*i/(float)_precision;

			++k;
			SetVertData( k, tu, tv, ex, ey, ez, px, py, pz );
		} // end inner loop
	}// end outer loop

	CreateVBO(_name,buffSize,GL_TRIANGLE_STRIP);
}


// based on the free glut code SolidTorus


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateVBOTorus(
                                   const std::string &_name,
                                   const Real _minorRadius,
                                   const Real _majorRadius,
                                   int _nSides,
                                   int _nRings,
                                   const bool _flipTX
                                  )
{
	Real  iradius = _minorRadius, oradius = _majorRadius, phi, psi, dpsi, dphi;

	Real spsi, cpsi, sphi, cphi ;
  int k=-1;

	if ( _nSides < 1 ) { _nSides = 1; }
	if ( _nRings < 1 ) { _nRings = 1; }
	int buffSize=(4*_nRings)*_nSides;

	/* Increment the number of sides and rings to allow for one more point than surface */
	_nSides ++ ;
	_nRings ++ ;
	Real *vertex= new Real[3 * _nSides * _nRings];
	Real *normal= new Real[3 * _nSides * _nRings];
	Real *uv= new Real[2*_nSides*_nRings*2];
	AllocVertMemory(buffSize);

	dpsi =  2.0 * M_PI / (double)(_nRings - 1) ;
	dphi = -2.0 * M_PI / (double)(_nSides - 1) ;
	psi  = 0.0;
	Real uStep=1.0/_nRings;
	Real vStep=1.0/_nSides;
	Real tu=0.0;
	Real tv=0.0;
	// pre compute the values for the torus
	for(int j=0; j<_nRings; ++j )
	{
			cpsi = cos ( psi ) ;
			spsi = sin ( psi ) ;
			phi = 0.0;
			for(int i=0; i<_nSides; ++i )
			{
				int offset = 3 * ( j * _nSides + i ) ;
				cphi = cos ( phi ) ;
				sphi = sin ( phi ) ;
				*(vertex + offset + 0) = cpsi * ( oradius + cphi * iradius ) ;
				*(vertex + offset + 1) = spsi * ( oradius + cphi * iradius ) ;
				*(vertex + offset + 2) =                    sphi * iradius  ;
				*(normal + offset + 0) = cpsi * cphi ;
				*(normal + offset + 1) = spsi * cphi ;
				*(normal + offset + 2) =        sphi ;
				if (_flipTX)
				{
					*(uv+offset)=tv;
					*(uv+offset+1)=tu;
				}
				else
				{
					*(uv+offset)=tu;
					*(uv+offset+1)=tv;
				}
				tu+=uStep;
				phi += dphi;
			} // end of _nSides loop
		tu=0.0;
		tv+=vStep;
		psi += dpsi;
	}  // end of _nRings loop

	Real *n,*v,*t;
	// now generate the VBO data
	for(int i=0; i<_nSides-1; ++i )
	{
		for(int j=0; j<_nRings-1; ++j )
		{
			int offset = 3 * ( j * _nSides + i ) ;
			n=normal+offset;
			v=vertex+offset;
			t=uv+offset;
			SetVertData( ++k, *t, *(t+1), *n, *(n+1),*(n+2), *v, *(v+1), *(v+2) );

			n=normal+offset+3;
			v=vertex+offset+3;
			t=uv+offset+3;
			SetVertData( ++k, *t, *(t+1), *n, *(n+1),*(n+2), *v, *(v+1), *(v+2) );

			n=normal + offset + 3 * _nSides + 3;
			v=vertex + offset + 3 * _nSides + 3;
			t=uv+ offset+3*_nSides+3;
			SetVertData( ++k, *t, *(t+1), *n, *(n+1),*(n+2), *v, *(v+1), *(v+2) );

			n=normal + offset + 3 * _nSides;
			v= vertex + offset + 3 * _nSides;
			t= uv+offset+3*_nSides;
			SetVertData( ++k, *t, *(t+1), *n, *(n+1),*(n+2), *v, *(v+1), *(v+2) );
		} // end _nRings
	} // end _nSides
	delete [] vertex;
	delete [] normal;
	delete [] uv;

	// now create the VBO
	CreateVBO(_name,buffSize,GL_QUADS);
}



//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::DrawFaceNormals(
                                    const std::string _name,
                                    const Real _scalar
                                   )
{
	GLint size;
	glDisable(GL_LIGHTING);
	ngl::Vector pt1, pt2, pt3,pt,n;
	int v=-1;
	glColor3f(1,1,0);
	VBOData *ptr=MapVBO(_name,size);
	if(ptr !=0)
	{
		glBegin(GL_LINES);
			for(int i=0; i<size; i+=3)
			{
				++v;
				pt1.Set(ptr[v].m_vx,ptr[v].m_vy,ptr[v].m_vz);
				n.Set(ptr[v].m_nx,ptr[v].m_ny,ptr[v].m_nz);
				n=n/_scalar;
				++v;
				pt2.Set(ptr[v].m_vx,ptr[v].m_vy,ptr[v].m_vz);
				++v;

				pt3.Set(ptr[v].m_vx,ptr[v].m_vy,ptr[v].m_vz);

				pt=(pt1+pt2+pt3)/3.0;
				pt.Vertex();
				pt+=n;
				pt.Vertex();
			}
		glEnd();
	}
	UnMapVBO(_name);
	glEnable(GL_LIGHTING);
}



//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::DrawNormals(
                                const std::string &_name,
                                const Real _scalar
                               )
{
	GLint size;
	VBOData *ptr=MapVBO(_name,size);
	if(ptr !=0)
	{
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
			// loop for each element of the VBO structure
			for(int i=0; i<size; ++i)
			{
				// draw a vertex at the point
				glVertex3f(ptr[i].m_vx,ptr[i].m_vy,ptr[i].m_vz);
				// draw a vertex from the point + the normal
				glVertex3f(ptr[i].m_vx+ptr[i].m_nx/_scalar,ptr[i].m_vy+ptr[i].m_ny/_scalar,ptr[i].m_vz+ptr[i].m_nz/_scalar);
      }
		glEnd();
		glEnable(GL_LIGHTING);
	}
	UnMapVBO(_name);
}



//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::DrawVerts(
                              const std::string &_name,
                              const Real _pointSize
                             )
{
	GLint size;
	VBOData *ptr=MapVBO(_name,size);
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_POINT_SIZE);
		glPointSize(_pointSize);
		glBegin(GL_POINTS);
			glColor3f(1,1,1);
			// loop for each element of the VBO structure
			for(int i=0; i<size; ++i)
			{
				// draw a vertex at the point
				glVertex3f(ptr[i].m_vx,ptr[i].m_vy,ptr[i].m_vz);
			}
		glEnd();
	UnMapVBO(_name);
	glPopAttrib();
	glEnable(GL_LIGHTING);
}

//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateVBOQuadPlane(
                                   const std::string &_name,
                                   const Real _width,
                                   const Real _depth,
                                   const int _wP,
                                   const int _dP,
                                   const Vector &_vN
                                  )
{
// calculate the VBO size basically we have 2 tris per quad based on the width and depth
  // _precision.

  // as our plane is centered on 0.0 we range from Width/2.0 and Depth/2.0
  Real w2=_width/2.0;
  Real d2=_depth/2.0;
  // calculate the steps for each quad / tri
  Real wStep=_width/_wP;
  Real dStep=_depth/_dP;
  // texture co-ords start at 0,0
  // texture steps
  Real du=1.0/_wP;
  Real dv=1.0/_dP;
  int k = -1;

  Real u=0.0;
  Real v=0.0;

  int buffSize=0;//(wP*dP)*6;
  // must figure out a better way of calculating this!!!!
  for(Real d=-d2; d<d2; d+=dStep)
  {
    for(Real w=-w2; w<w2; w+=wStep)
    {
      buffSize+=4;
    }
  }
  AllocVertMemory(buffSize);
  //std::cout<<"Buff size "<<BuffSize<<" me "<<(wP*dP)*6<<std::endl;

  for(Real d=-d2; d<d2; d+=dStep)
  {
    for(Real w=-w2; w<w2; w+=wStep)
    {
      SetVertData( ++k, u,    v+dv, _vN.m_x, _vN.m_y, _vN.m_z, w,      0, d+dStep);
      SetVertData( ++k, u+du, v+dv, _vN.m_x, _vN.m_y, _vN.m_z, w+wStep,0, d+dStep);
      SetVertData( ++k, u+du, v,    _vN.m_x,_vN.m_y, _vN.m_z, w+wStep,0,d);
      SetVertData( ++k, u,    v,    _vN.m_x, _vN.m_y, _vN.m_z, w,      0, d);
      u+=du;
    } // end w loop
    u=0.0;
    v+=du;
  } // end d loop
  // now create the VBO
  CreateVBO(_name,buffSize,GL_QUADS);
}

//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateVBOTrianglePlane(
                                   const std::string &_name,
                                   const Real _width,
                                   const Real _depth,
                                   const int _wP,
                                   const int _dP,
                                   const Vector &_vN
                                  )
{
	// calculate the VBO size basically we have 2 tris per quad based on the width and depth
	// _precision.

	// as our plane is centered on 0.0 we range from Width/2.0 and Depth/2.0
	Real w2=_width/2.0;
	Real d2=_depth/2.0;
	// calculate the steps for each quad / tri
	Real wStep=_width/_wP;
	Real dStep=_depth/_dP;
	// texture co-ords start at 0,0
	// texture steps
	Real du=1.0/_wP;
	Real dv=1.0/_dP;
	int k = -1;

	Real u=0.0;
	Real v=0.0;

	int buffSize=0;//(wP*dP)*6;
	// must figure out a better way of calculating this!!!!
	for(Real d=-d2; d<d2; d+=dStep)
	{
		for(Real w=-w2; w<w2; w+=wStep)
		{
			buffSize+=6;
		}
	}

	AllocVertMemory(buffSize);
	std::cout<<"Buff size "<<buffSize<<std::endl;

	for(Real d=-d2; d<d2; d+=dStep)
	{
		for(Real w=-w2; w<w2; w+=wStep)
		{
		/* tri 1
			// counter clock wise
			3
			| \
			|  \
			|   \
			1____2
			*/
			SetVertData( ++k, u,    v+dv, _vN.m_x, _vN.m_y, _vN.m_z, w,      0, d+dStep);
			SetVertData( ++k, u+du, v+dv, _vN.m_x, _vN.m_y, _vN.m_z, w+wStep,0, d+dStep);
			SetVertData( ++k, u,    v,    _vN.m_x, _vN.m_y, _vN.m_z, w,      0, d);
			u+=du;

        /* tri 2 w,0,d
      // counter clock wise
       3_____2
        \    |
          \  |
           \ |
            \|
            1

			*/
			SetVertData( ++k, u+du, v+dv, _vN.m_x,_vN.m_y, _vN.m_z, w+wStep,0,d+dStep);
			SetVertData( ++k, u+du, v,    _vN.m_x,_vN.m_y, _vN.m_z, w+wStep,0,d);
			SetVertData( ++k, u,    v,    _vN.m_x,_vN.m_y, _vN.m_z, w,      0,d);
		} // end w loop
		u=0.0;
		v+=du;
	} // end d loop
	// now create the VBO
	CreateVBO(_name,buffSize,GL_TRIANGLES);
}


#define BUFFER_OFFSET(i) ((char *)NULL + (i))


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::DrawVBO(
                            const std::string &_name
                           )
{
  static pthread_mutex_t cs_mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock( &cs_mutex );

	VBOObject *vbo=m_createdVBOs[_name];
	// make sure we have a valid vbo
	if(vbo!=0)
	{
		// enable the correct client states for VBO's
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    std::cout<<"drawing \n";
		// bind our VBO data
		glBindBuffer(GL_ARRAY_BUFFER, vbo->m_vbo);
		// tell GL the data is paced in an interleaved array
		glInterleavedArrays(GL_T2F_N3F_V3F, 0, (char *) NULL);
		// draw the VBO
		glDrawArrays( vbo->m_mode, 0, vbo->m_nv );
		// now turn off the VBO client state
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
  pthread_mutex_unlock( &cs_mutex );

}


/*----------------------------------------------------------------------------------------------------------------------
 * Compute lookup table of cos and sin values forming a cirle
 * borrowed from free glut implimentation of primitive drawing
 *
 * Notes:
 *    It is the responsibility of the caller to free these tables
 *    The size of the table is (n+1) to form a connected loop
 *    The last entry is exactly the same as the first
 *    The sign of n can be flipped to get the reverse loop
 */
//----------------------------------------------------------------------------------------------------------------------

void VBOPrimitives::fghCircleTable(
                                   double **io_sint,
                                   double **io_cost,
                                   const int _n
                                  )
{
	int i;
	/* Table size, the sign of n flips the circle direction */
	const int size = abs(_n);
	/* Determine the angle between samples */
	const double angle = 2*M_PI/(double)( ( _n == 0 ) ? 1 : _n );

	/* Allocate memory for n samples, plus duplicate of first entry at the end */
	*io_sint = new double[size+1];
	*io_cost = new double[size+1];

	/* Compute cos and sin around the circle */
	(*io_sint)[0] = 0.0;
	(*io_cost)[0] = 1.0;

	for (i=1; i<size; ++i)
	{
		(*io_sint)[i] = sin(angle*i);
		(*io_cost)[i] = cos(angle*i);
	}
	/* Last sample is duplicate of the first */
	(*io_sint)[size] = (*io_sint)[0];
	(*io_cost)[size] = (*io_cost)[0];
}



//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateVBOCone(
                                  const std::string &_name,
                                  const Real _base,
                                  const Real _height,
                                  const int _slices,
                                  const int _stacks
                                 )
{
	/* Step in z and radius as stacks are drawn. */
	double z0,z1;
	double r0,r1;

	const double zStep = _height / ( ( _stacks > 0 ) ? _stacks : 1 );
	const double rStep = _base / ( ( _stacks > 0 ) ? _stacks : 1 );

	/* Scaling factors for vertex normals */

	const double cosn = ( _height / sqrt ( _height * _height + _base * _base ));
	const double sinn = ( _base   / sqrt ( _height * _height + _base * _base ));

	/* Pre-computed circle */

	double *sint,*cost;
	fghCircleTable(&sint,&cost,-_slices);
	// allocate data as we are using quads it will be 1 quad per stack / slice
	unsigned int buffSize=((_stacks)*(_slices+1))*2;
	AllocVertMemory(buffSize);
	int k = -1;
	z0 = 0.0;
	z1 = zStep;

	r0 = _base;
	r1 = r0 - rStep;
	// texture co-ords start at 0,0
	// texture steps
	Real du=1.0/_stacks;
	Real dv=1.0/_slices;
	/* Cover each stack with a quad strip, except the top stack */
	float u=1.0;
	float v=1.0;

	for(int i=0; i<_stacks; i++ )
	{
		for(int j=0; j<=_slices; j++)
		{
			SetVertData( ++k, u, v, cost[j]*sinn, sint[j]*sinn, cosn, cost[j]*r0,   sint[j]*r0,   z0);
			SetVertData( ++k, u, v, cost[j]*sinn, sint[j]*sinn, cosn, cost[j]*r1,   sint[j]*r1,   z1);
			u-=du;
		}
		v-=dv;
		u=1.0;
		z0 = z1; z1 += zStep;
		r0 = r1; r1 -= rStep;

	}
	// create VBO
	CreateVBO(_name,buffSize,GL_QUAD_STRIP);
	/* Release sin and cos tables */

	delete [] sint;
	delete [] cost;
}


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateVBOCylinder(
                                      const std::string &_name,
                                      const Real _radius,
                                      const Real _height,
                                      const int _slices,
                                      const int _stacks
                                     )
{
	/* Step in z and radius as stacks are drawn. */

	double z0,z1;
	const double zStep = _height / ( ( _stacks > 0 ) ? _stacks : 1 );

	/* Pre-computed circle */

	double *sint,*cost;

	fghCircleTable(&sint,&cost,-_slices);
	// as were using quads it will be 4 verts per stack / slice
	unsigned int buffSize=((_stacks)*(_slices+1))*2;
	AllocVertMemory(buffSize);
	int k=-1;

	/* Do the stacks */

	z0 = 0.0;
	z1 = zStep;
	// texture co-ords start at 0,0
	// texture steps
	Real du=1.0/_stacks;
	Real dv=1.0/_slices;
	/* Cover each stack with a quad strip, except the top stack */
	float u=1.0;
	float v=1.0;

	for(int i=1; i<=_stacks; ++i )
	{
		if(i==_stacks)
		{
			z1 = _height;
		}
		for(int j=0; j<=_slices; ++j)
		{
			SetVertData( ++k, u, v,cost[j],sint[j],0.0 ,cost[j]*_radius, sint[j]*_radius, z0);
			SetVertData( ++k, u, v,cost[j],sint[j],0.0 ,cost[j]*_radius, sint[j]*_radius, z1 );
			u-=du;
		}
			v-=dv;
			u=1.0;
			z0 = z1; z1 += zStep;
	}
	// create VBO
	CreateVBO(_name,buffSize,GL_QUAD_STRIP);

	/* Release sin and cos tables */

	delete [] sint;
	delete [] cost;
}


//----------------------------------------------------------------------------------------------------------------------
void VBOPrimitives::CreateVBODisk(
                                  const std::string &_name,
                                  const Real _radius,
                                  const int _slices
                                 )
{
	/* Pre-computed circle */
	double *sint,*cost;

	fghCircleTable(&sint,&cost,-_slices);
	// as were using a triangle fan its  vert at the centere then
	//
	unsigned int buffSize=_slices+2;
	AllocVertMemory(buffSize);
	int k=-1;
	// texture co-ords start at 0,0
	// texture steps
	Real du=1.0/_slices;
	/* Cover each stack with a quad strip, except the top stack */
	float u=0.0;
	float v=0.0;

	SetVertData( ++k, u, v,0.0, 0.0, -1.0 ,0,0,0);
	v=1.0;

	for (int j=0; j<=_slices; ++j)
	{
		SetVertData( ++k, u, v,0.0, 0.0, -1.0 ,cost[j]*_radius, sint[j]*_radius,0);
		u+=du;
	}
	// create VBO
	CreateVBO(_name,buffSize,GL_TRIANGLE_FAN);

	/* Release sin and cos tables */
	delete [] sint;
	delete [] cost;
}

//----------------------------------------------------------------------------------------------------------------------


}; //end ngl namespace

