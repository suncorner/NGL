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
#include <string>
#include <fstream>
#include <cstdlib>

#include "ShaderManager.h"


namespace ngl
{

ShaderManager::ShaderManager()
{
	#ifndef DARWIN
	glewInit();
	if (glewIsSupported("GL_ARB_vertex_shader  GL_ARB_fragment_shader"))
	{
		std::cout<<"Ready for GLSL\n";
	}
	else
	{
		std::cerr<<"No GLSL support\n";
		exit(EXIT_FAILURE);
	}
	#endif
	m_debugState=true;
	m_numShaders=0;
}

GLint ShaderManager::GetUniLoc(
                               const GLhandleARB &_program,
                               const GLcharARB *_name
                              )
{
    GLint loc;
    loc = glGetUniformLocationARB(_program, _name);
    if (loc == -1)
    {
      std::cerr<<"No such uniform named "<<_name<<std::endl;
    }
    PrintOpenGLError();  // Check for OpenGL errors
    return loc;
}


int ShaderManager::PrintOpenGLError()
{
	//
	// Returns 1 if an OpenGL error occurred, 0 otherwise.
	//
	GLenum glErr;
	int    retCode = 0;
	glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		std::cerr<<gluErrorString(glErr)<<std::endl;
		retCode = 1;
		glErr = glGetError();
	}
	return retCode;
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::SetShaderParamFromMatrix(
                              const std::string &_shaderName,
                              const std::string &_paramName,
                              ngl::Matrix _p1
                             )
{

	ShaderObject *shader=m_shaders[_shaderName];
	// make sure we have a valid vbo
	if(shader!=0)
  {
   	glUniformMatrix4fvARB(GetUniLoc(shader->GetShaderID(),_paramName.c_str()),1,GL_FALSE,_p1.OpenGL());
  }
}



//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::SetShaderParamFromVector(
                              const std::string &_shaderName,
                              const std::string &_paramName,
                              ngl::Vector _p1
                             )
{
	ShaderObject *shader=m_shaders[_shaderName];
	// make sure we have a valid vbo
	if(shader!=0)
  {
   glUniform4fvARB(GetUniLoc(shader->GetShaderID(),_paramName.c_str()),1,_p1.OpenGL());
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::SetShaderParam4f(
                                      const std::string &_shaderName,
                                      const std::string &_paramName,
                                      float _p1,
                                      float _p2,
                                      float _p3,
                                      float _p4

                                      )
{
	ShaderObject *shader=m_shaders[_shaderName];
	// make sure we have a valid vbo
	if(shader!=0)
  {
   glUniform4fARB(GetUniLoc(shader->GetShaderID(),_paramName.c_str()),_p1,_p2,_p3,_p4);
  }
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::SetShaderParam3f(
                                      const std::string &_shaderName,
                                      const std::string &_paramName,
                                      float _p1,
                                      float _p2,
                                      float _p3
                                    )
{
	ShaderObject *shader=m_shaders[_shaderName];
	// make sure we have a valid vbo
	if(shader!=0)
  {
   glUniform3fARB(GetUniLoc(shader->GetShaderID(),_paramName.c_str()),_p1,_p2,_p3);
  }
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::SetShaderParam2f(
                                      const std::string &_shaderName,
                                      const std::string &_paramName,
                                      float _p1,
                                      float _p2
                                    )
{
	ShaderObject *shader=m_shaders[_shaderName];
	// make sure we have a valid vbo
	if(shader!=0)
  {
   glUniform2fARB(GetUniLoc(shader->GetShaderID(),_paramName.c_str()),_p1,_p2);
  }
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::SetShaderParam1i(
                                      const std::string &_shaderName,
                                      const std::string &_paramName,
                                      int _p1
                                    )
{
	ShaderObject *shader=m_shaders[_shaderName];
	// make sure we have a valid vbo
	if(shader!=0)
  {
   glUniform1iARB(GetUniLoc(shader->GetShaderID(),_paramName.c_str()),_p1);
  }
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::SetShaderParam1f(
                                      const std::string &_shaderName,
                                      const std::string &_paramName,
                                      float _p1
                                    )
{
	ShaderObject *shader=m_shaders[_shaderName];
	// make sure we have a valid vbo
	if(shader!=0)
  {
   glUniform1fARB(GetUniLoc(shader->GetShaderID(),_paramName.c_str()),_p1);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::UseShader(
                              const std::string &_name
                             )
{

	ShaderObject *shader=m_shaders[_name];
	// make sure we have a valid vbo
	if(shader!=0)
  {
    shader->UseShader();
    std::cout<<"Calling Use shader on "<<_name<<std::endl;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::LoadShader(
                               const std::string &_shaderName,
                               const std::string &_vert,
                               const std::string &_frag,
                               const std::string &_geo
                              )
{
	GLhandleARB p=LoadShaderSource(_vert,_frag,_geo);
	//std::cout <<"Shader Name"<<ShaderName<<std::endl;
	m_shaders[_shaderName] = new ShaderObject(p);
}

//----------------------------------------------------------------------------------------------------------------------
GLhandleARB ShaderManager::LoadShaderSource(
                                            const std::string &_vert,
                                            const std::string &_frag,
                                            const std::string &_geo
                                           )
{
	char *vs = 0;
  char *fs = 0;
  char *gs = 0;
	GLhandleARB v,f,g,p;
	v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	vs = ReadShaderSource(_vert);
	fs = ReadShaderSource(_frag);
	const char *vv = vs;
	const char *ff = fs;
	const char *gg = gs;


	glShaderSourceARB(v, 1, &vv,NULL);
	glShaderSourceARB(f, 1, &ff,NULL);	

	glCompileShaderARB(v);
	glCompileShaderARB(f);
	if(m_debugState)
	{
		PrintInfoLog(v);
		PrintInfoLog(f);
		//exit(EXIT_FAILURE);
	}


  if(!_geo.empty())
  {
    std::cerr<<"Loading in experimental Geo Shader code\n";
    g = glCreateShaderObjectARB(GL_GEOMETRY_SHADER_EXT);
    gg = ReadShaderSource(_geo);
    glShaderSourceARB(g, 1, &gg,NULL);
    glCompileShaderARB(g);
    if(m_debugState)
    {
      PrintInfoLog(g);
    }
  }



	p = glCreateProgramObjectARB();
	glAttachObjectARB(p,v);
	glAttachObjectARB(p,f);

  if(!_geo.empty())
  {
    glAttachObjectARB(p,g);
  }
	glLinkProgramARB(p);
	delete [] vs;
	delete [] fs;

  if(!_geo.empty())
  {
    delete [] gs;
  }

	if(m_debugState)
	{
		PrintInfoLog(p);
		//exit(EXIT_FAILURE);

	}
	return p;
}

//----------------------------------------------------------------------------------------------------------------------
char *ShaderManager::ReadShaderSource(
                                      const std::string &_fName
                                     )
{
	std::fstream fileIn;
	fileIn.open(_fName.c_str(),std::ios::in);
	if (!fileIn.is_open())
	{
		std::cout <<"File : "<<_fName<<" Not founds "<<std::endl;
		exit(EXIT_FAILURE);
	}
	// get file length and then rewind for a read
	fileIn.seekg (0, std::ios::end);
	int length = fileIn.tellg();
	fileIn.seekg (0, std::ios::beg);

	// allocate memory: and add space for null termination
	char *sourcebuffer = new char [length+1];

	// read data as a block:
	fileIn.read (sourcebuffer,length);
	// null terminate the string as read removes it.
	sourcebuffer[length]='\0';
	fileIn.close();

	return sourcebuffer;
}


//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::PrintInfoLog(
                                 const GLhandleARB _obj
                                )
{
	GLint infologLength = 0;
	GLint charsWritten  = 0;
	char *infoLog;

	glGetObjectParameterivARB(_obj, GL_OBJECT_INFO_LOG_LENGTH_ARB,&infologLength);

	if(infologLength > 0)
	{
		infoLog = new char[infologLength];
		glGetInfoLogARB(_obj, infologLength, &charsWritten, infoLog);
		std::cerr<<infoLog<<std::endl;
		delete [] infoLog;
	}
}

}; // end ngl namespace




