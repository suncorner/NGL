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
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Material.h"
#include "Colour.h"

namespace ngl
{


//----------------------------------------------------------------------------------------------------------------------
void Material :: SetDefault()
{
	m_transparency = 0.0;
	m_specularExponent = 1.0;
	m_surfaceRoughness = 0.0;
	m_ambient.Set(0.1f,0.1f,0.1f);
	m_diffuse.Set(0.8f,0.8f,0.8f);
	m_specular.Set(0,0,0);
	m_emissive.Set(0,0,0);
}
//----------------------------------------------------------------------------------------------------------------------
Material::Material(
                   const STDMAT _mat
                  )
{
m_specularExponent = s_materials[_mat][9];
m_ambient.Set(s_materials[_mat][0],s_materials[_mat][1],s_materials[_mat][2]);
m_diffuse.Set(s_materials[_mat][3],s_materials[_mat][4],s_materials[_mat][5]);
m_specular.Set(s_materials[_mat][6],s_materials[_mat][7],s_materials[_mat][8]);
m_emissive.Set(0,0,0);
}

//----------------------------------------------------------------------------------------------------------------------
void Material :: Change(
                        const STDMAT _mat
                       )
{
m_specularExponent = s_materials[_mat][9];
m_ambient.Set(s_materials[_mat][0],s_materials[_mat][1],s_materials[_mat][2]);
m_diffuse.Set(s_materials[_mat][3],s_materials[_mat][4],s_materials[_mat][5]);
m_specular.Set(s_materials[_mat][6],s_materials[_mat][7],s_materials[_mat][8]);
m_emissive.Set(0,0,0);
this->Use();
}

//----------------------------------------------------------------------------------------------------------------------
Material::Material(
                   const int _mat
                  )
{
m_specularExponent = s_materials[_mat][9];
m_ambient.Set(s_materials[_mat][0],s_materials[_mat][1],s_materials[_mat][2]);
m_diffuse.Set(s_materials[_mat][3],s_materials[_mat][4],s_materials[_mat][5]);
m_specular.Set(s_materials[_mat][6],s_materials[_mat][7],s_materials[_mat][8]);
m_emissive.Set(0,0,0);
}

//----------------------------------------------------------------------------------------------------------------------
void Material :: Set(
                     const Material &_m
                    )
{
m_transparency = _m.m_transparency;
m_specularExponent = _m.m_specularExponent;
m_surfaceRoughness = _m.m_surfaceRoughness;
m_ambient.Set(_m.m_ambient);
m_diffuse.Set(_m.m_diffuse);
m_specular.Set(_m.m_specular);
m_emissive.Set(_m.m_emissive);
}

//----------------------------------------------------------------------------------------------------------------------
void Material :: Set(
                     const Material *_m
                    )
{
m_transparency = _m->m_transparency;
m_specularExponent = _m->m_specularExponent;
m_surfaceRoughness = _m->m_surfaceRoughness;
m_ambient.Set(_m->m_ambient);
m_diffuse.Set(_m->m_diffuse);
m_specular.Set(_m->m_specular);
m_emissive.Set(_m->m_emissive);
}

//----------------------------------------------------------------------------------------------------------------------
void Material::Use()
{
m_ambient.m_a=m_transparency;
m_diffuse.m_a=m_transparency;
m_specular.m_a=m_transparency;
m_emissive.m_a=m_transparency;
glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m_ambient.m_openGL);
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m_diffuse.m_openGL);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m_specular.m_openGL);
glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,m_emissive.m_openGL);
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,m_specularExponent);
}


//----------------------------------------------------------------------------------------------------------------------
void Material::Use(
                   const Real _transp
                  )
{
m_ambient.m_openGL[3]=_transp;
m_diffuse.m_openGL[3]=_transp;
m_specular.m_openGL[3]=_transp;
m_emissive.m_openGL[3]=_transp;

glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m_ambient.m_openGL);
glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m_diffuse.m_openGL);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m_specular.m_openGL);
glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,m_emissive.m_openGL);
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,m_specularExponent);
}

//----------------------------------------------------------------------------------------------------------------------
Material::Material(
                   const std::string &_fName
                  )
{
std::ifstream FileIn;
FileIn.open(_fName.c_str(),std::ios::in);

if (!FileIn.is_open())
{
	std::cout << "File : "<< _fName <<" Not found Exiting "<<std::endl;
	exit(EXIT_FAILURE);
}

FileIn>>m_ambient;
FileIn>>m_diffuse;
FileIn>>m_specular;
FileIn>>m_emissive;

FileIn.close();
}

//----------------------------------------------------------------------------------------------------------------------
void Material::Load(const std::string &_fname)
{
/// \todo write some code to get this to load .mtl files
std::cout<<"Load of "<<_fname <<" not yet implemented\n";
}

}; // end ngl namespace



