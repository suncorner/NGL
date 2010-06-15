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
#include "Texture.h"

#include <iostream>

#include <cstdlib>
#include "NGLassert.h"
#include <QImage>



namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
bool Texture::LoadImage(
                        const std::string &_fName
                       )
{
  QImage *image = new QImage();
  bool loaded=image->load(_fName.c_str());
  if(loaded == true)
  {
    m_width=image->width();
    m_height=image->height();
    m_hasAlpha=image->hasAlphaChannel();
    if(m_hasAlpha == true)
    {
      m_bpp=4;
      m_format = GL_RGBA;
    }
    else
    {
      m_bpp=3;
      m_format = GL_RGB;
    }

    m_data = new unsigned char[ m_width*m_height*m_bpp];
    unsigned int index=0;
    QRgb colour;
    for(unsigned int y=0; y<m_height; ++y)
    {
      for(unsigned int x=0; x<m_width; ++x)
      {
        colour=image->pixel(x,y);

        m_data[index++]=qRed(colour);
        m_data[index++]=qGreen(colour);
        m_data[index++]=qBlue(colour);
        if(m_hasAlpha)
        {
          m_data[index++]=qAlpha(colour);
        }
      }
    }

    std::cout<<"Image size ="<<m_width<<"x"<<m_height<<std::endl;
    std::cout<<"has alpha = "<<m_hasAlpha<<std::endl;
    std::cout<<"bpp = "<<m_bpp<<std::endl;
    return true;

  }

  else return false;
}

//----------------------------------------------------------------------------------------------------------------------
Texture::Texture()
{
	m_width=0;
	m_height=0;
	m_data=0;
  m_multiTextureID=0;
}

//----------------------------------------------------------------------------------------------------------------------
Texture::Texture(
                 const std::string &_fName
                )
{
	m_width=0;
	m_height=0;
	m_data=NULL;
  m_multiTextureID=0;
	LoadImage(_fName);
}


//----------------------------------------------------------------------------------------------------------------------
Texture::~Texture()
{
#warning "Yet to be implimented"

}

//----------------------------------------------------------------------------------------------------------------------
double Texture::GetFromXY(
                          const GLuint _x,
                          const GLuint _y
                         ) const
{
// make sure were in the image range
	NGL_ASSERT(_x<=m_width && _y<=m_height);
	if (m_data !=0)
	{
		return m_data[_x*4+((_y)*m_width*4)];
	}
	else
	{
		return 0;
	}
}
//----------------------------------------------------------------------------------------------------------------------

/*! \note this is really inflexible at the moment needs to be made more generic and give more
control over the OpenGL texture types etc
Could actually be worth creating a texture manager class at some stage along the lines of the
Shader manager class, or even a generic manager framework which we could then add items to
*/
GLuint Texture::SetTextureGL() const
{
#warning "Yet to be implimented"
  GLuint textureName;

  glGenTextures(1,&textureName);
  glActiveTexture(GL_TEXTURE0+m_multiTextureID);




  glBindTexture(GL_TEXTURE_2D,textureName);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);


  glTexImage2D(GL_TEXTURE_2D,0,m_format,m_width,m_height,0,m_format,GL_UNSIGNED_BYTE,m_data);


  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  return textureName;
}
//----------------------------------------------------------------------------------------------------------------------

void Texture::SetMultiTexture(
                              const GLint _id
                             )
{
 m_multiTextureID=_id;
}

ngl::Colour Texture::GetColourFromXY(
                                    const GLuint _x,
                                    const GLuint _y
                                   ) const
{
// make sure were in the image range
	NGL_ASSERT(_x<=m_width && _y<=m_height);
	if (m_data !=0)
	{
		int Offset=_x*4+((_y)*m_width*4);
		return ngl::Colour(m_data[Offset],m_data[Offset+1],m_data[Offset+2],m_data[Offset+3]);
	}
	else
	{
		return ngl::Colour(0,0,0,0);
	}
}

}; // end namespace ngl;


