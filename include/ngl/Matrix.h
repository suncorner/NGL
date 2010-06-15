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
#ifndef __MATRIX_H_
#define __MATRIX_H_

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include <iosfwd>
#include <cmath>

namespace ngl
{
class Vector;
class Quaternion;



///  \author Jonathan Macey
/// \version 3.0
/// \date Last Revision 28/09/09 Updated to NCCA Coding standard
/// \class Matrix "include/Matrix.h"
/// @example AffineTransforms/Affine.cpp
/// @example AffineTransforms/Global.h
/// @example AffineTransforms/Global.cpp


/// \brief Matrix Class to do simple matrix operations included
///  operator overloaded functions for maths and matrix * vector type maths.


class Matrix
{
  /// \brief  insertion operator to write matrix to stream
  /// @param[in] output the stream to write to
  /// @param[in] M the matrix to write
  friend std::ostream& operator<<(std::ostream& output, const Matrix& M);

public:



  /// \brief ctor will always create an identity matrix
  Matrix();
  /// \brief copy ctor with reference object
  Matrix(
         const Matrix& _m
        );
  /// \brief copy ctor with float useful for Matrix m=1; for identity or Matrix m=3.5 for uniform scale
  Matrix(
          const float& _m
        );
  /// \brief copy ctor with double useful for Matrix m=1; for identity or Matrix m=3.5 for uniform scale
  Matrix(
          const double& _m
        );
  /// \brief copy ctor with int useful for Matrix m=1; for identity or Matrix m=3 for uniform scale
  Matrix(
          const int& _m
        );

  /// \brief set the value at m_m[_x][_y] to _equals
  /// @param[in]  _x the x index into the array
  /// @param[in]  _y the y index into the array
  /// @param[in]  _equals the value to set to

  void Mi(
          const GLint _x,
          const GLint _y,
          const Real _equals
         );

  /// \brief clear the matrix to all 0
  const Matrix& Null();

  /// make the matrix m the identity matrix \n
  /// 1 0 0 0 <BR>
  /// 0 1 0 0 <BR>
  /// 0 0 1 0 <BR>
  /// 0 0 0 1 <BR>

  const Matrix& Identity();

  ///  \brief operator for matrix multiplication
  /// @param[in] _m the matrix to multiply the current one by
  /// \returns this*_m
  Matrix operator*(
                   const Matrix &_m
                  ) const;
  ///  \brief operator to mult this matrix by value _m
  /// @param[in] _m the matrix to multiplt
  /// \returns a new matrix this*_m
  const Matrix& operator*=(
                           const Matrix &_m
                          );
  ///  \brief operator to add two matrices together
  /// @param[in] _m the matrix to add
  /// \returns this+_m
  Matrix operator+(
                    const Matrix &_m
                  ) const;
  ///  \brief += operator
  /// @param[in] _m the matrix to add
  /// \returns this+m
  const Matrix& operator+=(
                            const Matrix &_m
                          );
  ///  \brief operator to mult matrix by a scalar
  /// @param[in] _i the scalar to multiply by
  /// \returns this*_i
  Matrix operator*(
                    const Real _i
                  ) const;
  /// \brief *= operator with a scalar value
  /// @param[in] _i the scalar to multiply by
  /// \returns the matrix*i
  const Matrix& operator*=(
                            const Real _i
                          );
  ///  \brief method to transpose the matrix
  const Matrix& Transpose();
  ///  \brief load the current matrix values into OpenGL modelview matrix
  void LoadModelView() const;
  ///  \brief load the current matrix into OpenGL projection matrix
  void LoadProjection() const;
  ///  \brief set this matrix from the OpenGL ModelView matrix
  void FromModelView();
  ///  \brief set this matrix from the OpenGL projection matrix
  void FromProjection();
  ///  \brief set this matrix to a rotation matrix in the X axis for value _deg
  // note the matrix should be set to identity before doing this
  /// @param[in] _deg the value to be rotated by in degrees

  void RotateX(
                const Real _deg
              );
  ///  \brief set this matrix to a rotation matrix in the Y axis for value _deg
  // note the matrix should be set to identity before doing this
  /// @param[in] _deg the value to be rotated by in degrees

  void RotateY(
               const Real _deg
              );

  ///  \brief set this matrix to a rotation matrix in the Z axis for value _deg
  // note the matrix should be set to identity before doing this
  /// @param[in] _deg the value to be rotated by in degrees

   void RotateZ(
                 const Real _deg
                 );
  ///  \brief set the matrix scale values
  /// @param[in] _x the scale value in the _x
  /// @param[in] _y the scale value in the _y
  /// @param[in] _z the scale value in the _z

  void Scale(
             const Real _x,
             const Real _y,
             const Real _z
            );
  ///  \brief set the matrix as a translation matrix
  /// @param[in] _x the _x translation value
  /// @param[in] _y the _y translation value
  /// @param[in] _z the _z translation value

  void Translate(
                 const Real _x,
                 const Real _y,
                 const Real _z
                );

  ///  \brief get the determinant of the matrix
  /// \returns the determinat
  Real Determinant() const;

  ///  \brief get a sub 3x3 matrix used in determinant and Inverse calculations
  /// @param[in] _i index value
  /// @param[in] _j index value
  /// @param[in] o_mat the 3x3 matrix
  void SubMatrix3x3(
                    const int _i,
                    const int _j,
                    Real o_mat[]
                   ) const;

  ///  \brief get the inverse of the matrix
  /// @param[in] o_result the matrix to copy
  /// \returns true or false depending upon if an inverse is possible

  bool Inverse(
               Matrix& o_result
              ) const;

  ///  \brief convert this matrix to a Quaternion
  /// \returns the matrix as a Quaternion
  Quaternion AsQuaternion() const;

  ///  \brief multiply this by a vector
  /// @param[in] _v the vector to multiply
  /// \returns Vector M*V
  Vector operator * (
                     const Vector &_v
                    ) const;

  ///  \brief axis / angle rotation using the Euler method
  /// @param[in] _angle the angle in degree to rotate
  /// @param[in] _x part of the axis should be normalised before call
  /// @param[in] _y part of the axis should be normalised before call
  /// @param[in] _z part of the axis  should be normalised before call
  void Euler(
             const float _angle,
             const float _x,
             const float _y,
             const float _z
            );

  inline Real * OpenGL(){return &m_openGL[0];}

protected :

 friend class Transformation;
 friend class Quaternion;
 friend class Camera;
#ifndef BUILDING_DOCS

  union
  {
#endif
    /// matrix element m_m as a 4x4 array mapped by union to m_nn elements and m_openGL
    Real m_m[4][4];
    /// The matrix in m_openGL 16 float array format usefull for OpenGL fv formats
    /// mapped to m_m[][] elements and m_xx elements
    Real m_openGL[16];

#ifndef BUILDING_DOCS

    struct {
#endif
      /// individual matrix element maps to m_m[0][0] or m_openGL[0]
      Real m_00;
      /// individual matrix element maps to m_m[0][1] or m_openGL[1]
      Real m_01;
      /// individual matrix element maps to m_m[0][2] or m_openGL[2]
      Real m_02;
      /// individual matrix element maps to m_m[0][3] or m_openGL[3]
      Real m_03;
      /// individual matrix element maps to m_m[1][0] or m_openGL[4]
      Real m_10;
      /// individual matrix element maps to m_m[1][1] or m_openGL[5]
      Real m_11;
      /// individual matrix element maps to m_m[1][2] or m_openGL[6]
      Real m_12;
      /// individual matrix element maps to m_m[1][3] or m_openGL[7]
      Real m_13;
      /// individual matrix element maps to m_m[2][0] or m_openGL[8]
      Real m_20;
      /// individual matrix element maps to m_m[2][1] or m_openGL[9]
      Real m_21;
      /// individual matrix element maps to m_m[2][2] or m_openGL[10]
      Real m_22;
      /// individual matrix element maps to m_m[2][3] or m_openGL[11]
      Real m_23;
      /// individual matrix element maps to m_m[3][0] or m_openGL[12]
      Real m_30;
      /// individual matrix element maps to m_m[3][1] or m_openGL[13]
      Real m_31;
      /// individual matrix element maps to m_m[3][2] or m_openGL[14]
      Real m_32;
      /// individual matrix element maps to m_m[3][3] or m_openGL[15]
      Real m_33;
#ifndef BUILDING_DOCS

    };
  };
#endif



};
}

#endif

