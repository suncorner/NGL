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
/*! Last updated: 16-03-05 : RB >> made light ID assignment automatic */
#include "Light.h"
#include <iostream>


namespace ngl
{

/// all possible light ID's. Wheh lights are enabled, they simply take
/// the last first available light ID. When they get disabled, the light
/// ID gets written back into this array.
///
unsigned char Light::s_freeLights[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
unsigned int Light::s_numEnabledLights=0;

//----------------------------------------------------------------------------------------------------------------------
Light::Light(
             const Vector& _pos,
             const Colour& _col,
             const LIGHTMODES _lightMode
            )
{
	// zero now means un-assigned
	m_lightNo=0x00;
	m_pos.Set(_pos);
	m_colour.Set(_col);
	m_specColour.Set(_col);
	m_lightMode = _lightMode;
}

//----------------------------------------------------------------------------------------------------------------------
Light::Light(
             const Vector& _pos,
             const Colour& _col,
             const Colour& _specColour,
             const LIGHTMODES _lightMode)
{
	// zero now means un-assigned
	m_lightNo=0x00;
	m_pos.Set(_pos);
	m_colour.Set(_col);
	m_specColour.Set(_specColour);
	m_lightMode=_lightMode;
}

//----------------------------------------------------------------------------------------------------------------------
void Light::Show()
{
	glPushMatrix();
		m_pos.Translate();
		m_colour.Use();
		VBOPrimitives *prim=VBOPrimitives::Instance();
		glScalef(0.2,0.2,0.2);
		prim->DrawVBO("cube");
	glPopMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
bool Light::Enable()
{
	if (m_lightNo==0)
	{
		// if all 8 lights enabled, ignore request
		if (s_numEnabledLights==8)
		{
			std::cerr << "[WARNING] trying to enable more than 8 lights at once!" << std::endl;
			return false;
		}
		// set light num
		m_lightNo = s_freeLights[s_numEnabledLights++];
	}
	// set GL params
	Real zero[] = {0.0f,0.0f,0.0f,0.0f};

	GLint light=GL_LIGHT0+(m_lightNo-1);
	glLightfv(light,GL_DIFFUSE,m_colour.OpenGL()); // tell openGL diffuse light color
	glLightfv(light,GL_SPECULAR,m_specColour.OpenGL()); // tell openGl specular light color
	glLightfv(light,GL_AMBIENT,zero);
	// opengl wants a homogenous point for the light so we build one
	m_pos.m_w=(Real)m_lightMode;
	glLightfv(light,GL_POSITION,m_pos.OpenGL());
	glEnable(light);

	return true;
}

//----------------------------------------------------------------------------------------------------------------------
void Light::Disable()
{
	if (m_lightNo!=0)
	{
		glDisable( GetLightNum() );
		s_freeLights[--s_numEnabledLights] = m_lightNo;
		m_lightNo = 0x00;
	}
}

}; // end ngl namespacee
