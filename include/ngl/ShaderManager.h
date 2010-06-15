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
#ifndef __SHADERMANAGER__
#define __SHADERMANAGER__
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include "Singleton.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include "Matrix.h"
#include "Vector.h"
namespace ngl
{

///  \author Jonathan Macey
///  \version 2.0
///  \date Last Revision 16/03/10 - removed the name attrib as using Maop in shader manager now
///  \class ShaderObject  "include/ShaderManager.h"
///   \brief A class to hold each of the shaders loaded into the shader manager


class ShaderObject
{
public :
  /// \brief ctor
  /// @param[in] _name the name of the shader
  /// @param[in] _id the actual shader id
  ShaderObject(
               const GLhandleARB _id
              ) :
                m_shaderID(_id){;};

  /// \brief  method to use this shader as the current shader object
  inline void UseShader()
                         {
                         glUseProgramObjectARB(m_shaderID);
                         };

  /// \brief  get the current shader id
  /// \returns the id for the shader
  inline GLhandleARB GetShaderID()
                                 {
                                 return m_shaderID;
                                 };


protected :
  /// the shader id used by OpenGL to identifiy which shader to use
  GLhandleARB m_shaderID;
};

///  \author Jonathan Macey
///  \version 3.0
///  \date Last Revision 20/04/10 used templated singleton
///  \class ShaderManager  "include/ShaderManager.h"
///  \brief Singleton Class to init and Use GLSL Shaders
///  the class stores the shaders as a map of shader objects and they can be found by name
/// Updated to use templated singleton
/// Updated to use a map to store the shaders by name and hence removed the name from the ShaderObject Class
/// Also Added methods to adjust shader parameters by shader / param name, at present use only 1-4 Floats and
/// a few others need to think of a better way of doing this

///  \todo make the whole thing neater and possibly work along the line of shaderX etc


class ShaderManager : public  Singleton<ShaderManager>
{
  friend class Singleton<ShaderManager>;

public :
  /// \brief method to get the current instance of the ShaderManager
///  static ShaderManager* Instance();

  /// method to load shaders
  /// @param[in] _shaderName the name of the shader to be stored in the Manager
  /// @param[in] _vert the vertex shader to load
  /// @param[in] _frag the fragment shader to load
  /// @param[in] _geo an optional geo shader to load
  void LoadShader(
                  const std::string &_shaderName,
                  const std::string &_vert,
                  const std::string &_frag,
                  const std::string &_geo=""
                 );

  /// \brief Not yet implemented but this will eventuall load shader pairs in a given directory
  /// @param[in] _dir the directory to scan for shaders
  void LoadDir(
               const std::string &_dir
              );

  /// \brief se the shader passed in by name
  /// @param[in] _name the name of the shader to load
  void UseShader(
                 const std::string &_name
                );

  /// \brief Toggle debug mode on
  inline void DebugOn()
                      {
                      m_debugState=true;
                      };

  /// \brief Toggle debug mode off
  inline void DebugOff()
                       {
                       m_debugState=false;
                       };

  /// get shader handle by index
  GLhandleARB operator[](
                         const ShaderManager&
                        );

  /// \brief get the number of shaders stored
  /// \returns the number of shaders
  unsigned int getNumShaders()
                             {
                             return m_shaders.size();
                             };


  /// \brief set a shader param by name for 1 int param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _shaderName the name of the shader to set the param for
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the matrix to set from (float 16) value of the parameter to set

  void SetShaderParamFromMatrix(
                                const std::string &_shaderName,
                                const std::string &_paramName,
                                ngl::Matrix _p1
                               );

  /// \brief set a shader param by name for 1 int param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _shaderName the name of the shader to set the param for
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the vector to set from (float 4) value of the parameter to set

  void SetShaderParamFromVector(
                                const std::string &_shaderName,
                                const std::string &_paramName,
                                ngl::Vector _p1
                               );

  /// \brief set a shader param by name for 1 int param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _shaderName the name of the shader to set the param for
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set

  void SetShaderParam1i(
                        const std::string &_shaderName,
                        const std::string &_paramName,
                        int _p1
                        );



  /// \brief set a shader param by name for 1 float param note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _shaderName the name of the shader to set the param for
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set

  void SetShaderParam1f(
                        const std::string &_shaderName,
                        const std::string &_paramName,
                        float _p1
                        );

  /// \brief set a shader param by name for 2 float params note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _shaderName the name of the shader to set the param for
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  /// @param[in] _p2 the float value of the parameter to set

  void SetShaderParam2f(
                        const std::string &_shaderName,
                        const std::string &_paramName,
                        float _p1,
                        float _p2
                        );

  /// \brief set a shader param by name for 3 float params note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _shaderName the name of the shader to set the param for
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  /// @param[in] _p2 the float value of the parameter to set
  /// @param[in] _p3 the float value of the parameter to set

  void SetShaderParam3f(
                        const std::string &_shaderName,
                        const std::string &_paramName,
                        float _p1,
                        float _p2,
                        float _p3
                        );



  /// \brief set a shader param by name for 4 float params note that the shader
  /// must be the currently active shader of else this will fail
  /// @param[in] _shaderName the name of the shader to set the param for
  /// @param[in] _paramName the name of the parameter in the shader to set
  /// @param[in] _p1 the float value of the parameter to set
  /// @param[in] _p2 the float value of the parameter to set
  /// @param[in] _p3 the float value of the parameter to set
  /// @param[in] _p4 the float value of the parameter to set

  void SetShaderParam4f(
                        const std::string &_shaderName,
                        const std::string &_paramName,
                        float _p1,
                        float _p2,
                        float _p3,
                        float _p4
                        );
protected:

  /// flag to indicate the debug state
  bool m_debugState;
  /// container for the shader objects will replace with a map at some stage
  //std::vector <ShaderObject> m_shaders;
  std::map <std::string,ShaderObject *> m_shaders;




  /// the nunmber of shaders loaded
  unsigned int m_numShaders;
  ////// pointer to the single instance of the class
  ///static ShaderManager* s_pinstance;

  /// \brief default ctor private as a singleton
  ShaderManager();
  /// \brief  copy ctor private as singleton
  ShaderManager(
               const ShaderManager&
               );
  ///  \brief  assignment operator private as singleton
  ///ShaderManager& operator=(
     ///                      const ShaderManager&
        ///                  );

  /// \brief method to load the shader source (basically modified from the orange book
  /// @param[in] _vert the vertex shader
  /// @param[in] _frag the fragment shader
  GLhandleARB LoadShaderSource(
                               const std::string &_vert,
                               const std::string &_frag,
                               const std::string &_geo
                              );

  /// \brief read the shader file and return an array of character data modified from the orange book
  /// @param[in] _fName the name of the shader file to load
  char *ReadShaderSource(
                         const std::string &_fName
                        );
  /// \brief print out the shader info log
  /// @param _obj the shader object to get the info for
  void PrintInfoLog(
                    const GLhandleARB _obj
                   );


  GLint GetUniLoc(
                   const GLhandleARB &_program,
                   const GLcharARB *_name
                 );

  int PrintOpenGLError();

}; // end of class

} // end ngl Namespace





#endif

