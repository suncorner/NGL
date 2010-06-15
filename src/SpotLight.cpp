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
//---------------------------------------------------------------------------
#include "SpotLight.h"
#include "Material.h"
#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif


namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
SpotLight::SpotLight(
                     const Vector& _pos,
                     const Vector& _aim,
                     const Colour& _col
                    ):
                    	Light(
                    				_pos,
                    				_col,
                    				LIGHTLOCAL
                    			 )
{
	// set up m_direction and default values
	Vector dir=_aim-_pos;
	dir.Normalize();
	// set some good default values
	m_cutoffAngle = 45.0f;
	m_spotExponent = 0.0f;

	m_constantAtten = 1.5f;
	m_linearAtten = 0.0f;
	m_quadraticAtten = 0.0f;
	m_pos=_pos;
	m_aim=_aim;
	m_dir=dir;
}

//----------------------------------------------------------------------------------------------------------------------
/// \todo #warning "don't forget to implement the aim functionality "

void SpotLight::Set(
                    const Vector& _pos,
                    const Vector& _dir,
                    const Colour& _col
                    )
{
	// set up m_direction and default values
	m_dir = _dir;
	m_dir.Normalize();
	m_colour=_col;
	m_pos=_pos;
	// set some good default values
	m_cutoffAngle    = 45.0f;
	m_spotExponent   = 0.0f;
	m_constantAtten  = 1.5f;
	m_linearAtten    = 0.0f;
	m_quadraticAtten = 0.0f;
}

//----------------------------------------------------------------------------------------------------------------------
void SpotLight::Show()
{
	// call superclass show method
	Light::Show();
	this->Enable();
	glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
			m_pos.Vertex();
			m_aim.Vertex();
		glEnd();
	glEnable(GL_LIGHTING);
	// change spot light m_direction
	glLightfv(GL_LIGHT0+m_lightNo, GL_SPOT_DIRECTION, m_dir.OpenGL());

}

//----------------------------------------------------------------------------------------------------------------------
void SpotLight::Aim(
                    const Vector& _pos
                   )
{
	Vector dir= _pos-m_pos;
	dir.Normalize();
	m_aim=_pos;
	m_dir=dir;

	glLightfv(GL_LIGHT0+m_lightNo, GL_SPOT_DIRECTION,m_dir.OpenGL());
}



//----------------------------------------------------------------------------------------------------------------------
bool SpotLight::Enable()
{
	if(!Light::Enable())
	{
		return false;
	}
	GLint lightNo=GetLightNum();
	//std::cout <<lightNo<<std::endl;
	glLightf(lightNo, GL_CONSTANT_ATTENUATION, m_constantAtten);
	glLightf(lightNo, GL_LINEAR_ATTENUATION, m_linearAtten);
	glLightf(lightNo, GL_QUADRATIC_ATTENUATION, m_quadraticAtten);
	glLightf(lightNo, GL_SPOT_CUTOFF, m_cutoffAngle);
	glLightfv(lightNo,GL_SPOT_DIRECTION, m_dir.OpenGL());
	glLightf(lightNo, GL_SPOT_EXPONENT, m_spotExponent);
	return true;

}

//----------------------------------------------------------------------------------------------------------------------
void SpotLight::SetParams(
                          const Real _cutoff,
                          const Real _exponent,
                          const Real _constant,
                          const Real _linear,
                          const Real _quadratic
                          )
{
	m_cutoffAngle=_cutoff;
	m_spotExponent=_exponent;
	m_constantAtten=_constant;
	m_linearAtten=_linear;
	m_quadraticAtten=_quadratic;
}

}; // end ngl namespace

