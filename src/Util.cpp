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

#ifdef __USINGWINDOWS__
  #include <windows.h>
#endif

#ifdef LINUX
  #include <GL/glew.h>
  #include <GL/gl.h>
  #include <cstdlib>
#endif
#ifdef DARWIN
  #include <unistd.h>
  #include <OpenGL/gl.h>
#endif
#include "Vector.h"
#include <ctime>

#include "VBOPrimitives.h"

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
Vector CalcNormal (
                   const ngl::Vector _p1,
                   const ngl::Vector _p2,
                   const ngl::Vector _p3
                  )
{
	ngl::Real coa, cob, coc ;
	ngl::Real px1, py1, pz1 ;
	ngl::Real px2, py2, pz2 ;
	ngl::Real px3, py3, pz3 ;
	ngl::Real absvec;
	ngl::Vector norm;
	px1 = _p1.m_x; py1 = _p1.m_y; pz1 = _p1.m_z;
	px2 = _p2.m_x; py2 = _p2.m_y; pz2 = _p2.m_z;
	px3 = _p3.m_x; py3 = _p3.m_y; pz3 = _p3.m_z;

	// generate cross product

	coa = -(py1 * (pz2-pz3) + py2*(pz3-pz1) + py3*(pz1-pz2)) ;
	cob = -(pz1 * (px2-px3) + pz2*(px3-px1) + pz3*(px1-px2)) ;
	coc = -(px1 * (py2-py3) + px2*(py3-py1) + px3*(py1-py2)) ;

	// normalise the results to get unit length normal
  absvec = sqrtf ( ((coa*coa) + (cob*cob) + (coc*coc))) ;

	norm.m_x = coa/absvec ;
	norm.m_y = cob/absvec ;
	norm.m_z = coc/absvec ;
	norm.m_w=0.0f;
	return norm;
}

//----------------------------------------------------------------------------------------------------------------------
void CreateAxis()
{
	ngl::VBOPrimitives *prim=VBOPrimitives::Instance();
	prim->CreateVBOCylinder("nglAXISCylinder",0.02,2,60,60);
	prim->CreateVBOCone("nglAXISCone",0.05,0.2,30,30);
}


//----------------------------------------------------------------------------------------------------------------------
void DrawAxis(
             const float _size
             )
{
	ngl::VBOPrimitives *prim=VBOPrimitives::Instance();
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glPushMatrix();
		glScalef(_size,_size,_size);

		// draw X axis
		glColor3f(1,0,0);
		glPushMatrix();
			glTranslatef(0,0,-1);
			prim->DrawVBO("nglAXISCylinder");
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,1);
			prim->DrawVBO("nglAXISCone");
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,-1);
			glRotatef(180,0,1,0);
			prim->DrawVBO("nglAXISCone");
		glPopMatrix();

		// Y axis
		glColor3f(0,1,0);
		glPushMatrix();
			glRotatef(90,0,1,0);
			glTranslatef(0,0,-1);
			prim->DrawVBO("nglAXISCylinder");
		glPopMatrix();
		glPushMatrix();
			glRotatef(90,0,1,0);
			glTranslatef(0,0,1);
			prim->DrawVBO("nglAXISCone");
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90,0,1,0);
			glTranslatef(0,0,1);
			prim->DrawVBO("nglAXISCone");
		glPopMatrix();
		// Z axis
		glPushMatrix();
			glColor3f(0,0,1);
			glRotatef(90,1,0,0);
			glTranslatef(0,0,-1);
			prim->DrawVBO("nglAXISCylinder");
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90,1,0,0);
			glTranslatef(0,0,1);
			prim->DrawVBO("nglAXISCone");
		glPopMatrix();
		glPushMatrix();
			glRotatef(90,1,0,0);
			glTranslatef(0,0,1);
			prim->DrawVBO("nglAXISCone");
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

}
//----------------------------------------------------------------------------------------------------------------------
void CreateAxisSimple()
{
	glPushMatrix();
		glBegin(GL_LINES); //x
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(-0.8f,0.0f,0.0f);
			glVertex3f(0.8f,0.0f,0.0f);
			glColor3f(0.0f,1.0f,0.0f); //y
			glVertex3f(0.0f,-0.8f,0.0f);
			glVertex3f(0.0f,0.8f,0.0f);
			glColor3f(0.0f,0.0f,1.0f); //z
			glVertex3f(0.0f,0.0f,-0.8f);
			glVertex3f(0.0f,0.0f,0.8f);
		glEnd();
	glPopMatrix();
}


//----------------------------------------------------------------------------------------------------------------------
void DrawAxisSimple(
                    const ngl::Real _size
                   )
{
	glPushMatrix();
		glScalef(_size,_size,_size);
		CreateAxisSimple();
	glPopMatrix();
}


Real DegtoRad(
              const ngl::Real _deg
              )
{
	return (_deg/180.0f) * M_PI;
}

//----------------------------------------------------------------------------------------------------------------------
Real RadtoDeg(
              const Real _rad
             )
{
	return (_rad / M_PI) * 180.0f;
}




} // end of namespace




