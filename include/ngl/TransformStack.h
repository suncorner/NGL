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
#ifndef __TRANSFORMSTACK_H__
#define __TRANSFORMSTACK_H__

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include <deque>
#include <vector>
#include <cmath>
#include "Transformation.h"
namespace ngl
{

/// \author Jonathan Macey
/// \version 1.0
/// \date 24/03/10 Initial build
/// \class TransformStack "include/ngl/TransformStack.h"
/// \brief TransformStack Class to replicate basic Affine Transfors ala
/// OpenGL and Renderman but using the Transformation object


  class TransformStack
  {
    /// \brief  insertion operator to write matrix to stream
    /// @param[in] _output the stream to write to
    /// @param[in] _m the matrix-stack to write
    friend std::ostream& operator<<(std::ostream& _output,  TransformStack& _m);

  public:
      /// \brief ctor will always create an identity matrix as top of stack
      TransformStack();
      /// \brief copy ctor with reference object
      /// @param[in] _m the stack to copy
      TransformStack(
                      const TransformStack& _m
                 );
      /// @brief push the current matrix onto the stack
      /// make the new matrix the identity matrix
      void PushTransform();
      /// @brief push the current matrix onto the stack and place a copy
      /// of the pushed matrix as the current one
      void PushTransformAndCopy();
      /// @brief pop the previous top of stack
      void PopTransform();


      /// @brief return the current active matrix
     /// @returns the current top of stack
      //inline const Transformation & GetCurrentTransform(){return m_current;}
      inline Transformation  & GetCurrentTransform(){return m_current;}

      Transformation GetCurrAndGlobal();

      /// @brief Set the current top of the stack matrix to _m
      /// @param[in] _m the value to set the current matrix
      inline void SetCurrent(
                             const ngl::Transformation &_m
                            )
                             {m_current=_m;}

      /// @brief Set the current top of the stack matrix to _m
      /// @param[in] _m the value to set the current matrix
      inline void SetGlobal(
                             const ngl::Transformation &_m
                            )
                             {m_global=_m;}

      void LoadMatrixToShader(
                              std::string _shader,
                              std::string _param,
                              ACTIVEMATRIX _which=TRANSPOSE
                             );

      void LoadGlobalAndCurrentMatrixToShader(
                                              std::string _shader,
                                              std::string _param,
                                              ACTIVEMATRIX _which=TRANSPOSE
                                             );
   protected :
       /// @brief the current active transfom
       ngl::Transformation m_current;
       /// @brief a global transformation useful for adding global TRS to
       /// all transforms, to use this use the GloabAndCurrent methods
       ngl::Transformation m_global;
       /// @brief the stack containing the other Transforms
       std::vector<Transformation> m_stack;
      /// @brief the max stack size this just put this in
      /// to be in line with OpenGL but could overiddedn
      const static int MAXNGLTRANSFORMSTACKSIZE=40;
      unsigned int m_index;
 };
}

#endif
