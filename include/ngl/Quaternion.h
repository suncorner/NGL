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
//=========================================================================
///
///  \file  Quaternion.h
/// \author  Rob Bateman
///  \brief  Defines the class Quaternion, a class definition for a Quaternion
///  see www.robthebloke.org
//=========================================================================


//=========================================================================
//  Sentry
//=========================================================================

//  This directive is used to stop the header file from being included
//  Twice and is standard for all headers.
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"


#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

//=========================================================================
//  Includes
//=========================================================================

#include <iostream>
#include "Vector.h"

//=========================================================================
//  Class Definitions
//=========================================================================


namespace ngl
{

class Matrix;

//------------------------------------------------------------------------------
/// \class Quaternion "include/Quaternion.h"
/// \brief  The Quaternion class is used to hold rotational values for both
///      transforms and animation keyframes.
///

class Quaternion
{

public:
  //--------------------------------------------------------------------------
  /// \brief constructor
  /// @param [in]  _x  -  the x component of the quaternion
  /// @param [in]  _y  -  the y component of the quaternion
  /// @param [in]  _z  -  the z component of the quaternion
  /// @param [in]  _w  -  the w component of the quaternion
  ///
  inline Quaternion(
                    const Real _x=0,
                    const Real _y=0,
                    const Real _z=0,
                    const Real _w=1
                   ):
                     m_x(_x),
                     m_y(_y),
                     m_z(_z),
                     m_w(_w) {;}

  //--------------------------------------------------------------------------
  /// \brief copy constructor
  /// @param [in]  _q  -  the quaternion to copy
  ///
  inline Quaternion(
                    const Quaternion& _q
                   ):
                     m_x(_q.m_x),
                     m_y(_q.m_y),
                     m_z(_q.m_z),
                     m_w(_q.m_w) {;}
  /// \brief method to set the quaternion values
  /// @param[in] _x the x value
  /// @param[in] _y the y value
  /// @param[in] _z the z value
  /// @param[in] _w the w value

  inline void Set(
                 const Real& _x,const Real& _y,const Real& _z,const Real& _w
                 )
                 {
                  m_x=_x;
                  m_y=_y;
                  m_z=_z;
                  m_w=_w;
                 }




  //--------------------------------------------------------------------------
  /// \brief  returns the inverse of the quaternion (aka conjugate)
  /// \return  the conjugate of the quaternion
  ///
  inline Quaternion operator-() const
                             {
                              return Quaternion( -m_x,-m_y,-m_z,m_w );
                             }

  //--------------------------------------------------------------------------
  /// \brief  Perform a multiplication between 2 quaternions
  ///
  ///      ResultQuaternion = Q1.Q2 = ( w1.w2 - v1.v2, w1.v2 + w2.v1 + v1 x v2 )
  ///
  ///      where   v1 = (x,y,z) of Q1
  ///          w1 = (w)     of Q1
  ///          v2 = (x,y,z) of Q2
  ///          w2 = (w)     of Q2
  ///
  /// \return  the result of the mutliplication
  ///
  Quaternion operator *(
                        const Quaternion& _q
                       ) const;

  //--------------------------------------------------------------------------
  ///  \brief
  ///  \note  A rotation matrix may be converted back to a quaternion.
  /// @param [in] _m the matrix to construct from
  Quaternion(
             const Matrix& _m
            );

  //--------------------------------------------------------------------------
  /// \brief  This function normalises the quaternion
  /// \return  A constant reference to itself
  ///
  const Quaternion& Normalise();

  //--------------------------------------------------------------------------
  /// \brief  returns a normalised version of this quaternion
  /// \return  The normalised quaternion
  ///
  Quaternion Normalised() const ;

  //--------------------------------------------------------------------------
  /// \brief  this function turns the quaternion into a 4x4 rotation matrix
  /// @param [in]  o_matrix  -  the output matrix
  ///
  void AsMatrix(Real* o_matrix) const;

  //--------------------------------------------------------------------------
  /// \brief  This function returns the quaternion as a matrix
  /// \return  The rotation matrix equivalent
  ///
  Matrix AsMatrix() const;

  //--------------------------------------------------------------------------
  /// \brief  This function extracts a quaternion from the rotations
  ///     present in a matrix.
  /// @param [in]  _mat  -  the input matrix
  ///
  void FromMatrix(const Matrix &_mat);


  //--------------------------------------------------------------------------
  /// \brief  This function converts an axis angle rotation to a quaternion
  /// @param [in]  _axis  -  the axis around which the rotation occurs
  /// @param [in]  _angle  -  the amount of rotation
  ///
  void FromAxisAngle(const Vector& _axis,const float _angle) ;

  //--------------------------------------------------------------------------
  /// \brief  This function converts a quaternion to an axis angle rotation
  /// @param [out]  o_axis  -  the output axis
  /// @param [out]  o_angle  -  the output angle.
  ///
  void ToAxisAngle( Vector& o_axis, float &o_angle );

  //--------------------------------------------------------------------------
  /// \brief  This function converts a set of euler angles to a quaternion
  /// @param [in]  _ax  -  rotation in x
  /// @param [in]  _ay  -  rotation in y
  /// @param [in]  _az  -  rotation in z
  ///
  void FromEulerAngles( const float _ax, const float _ay, const float _az );


  //--------------------------------------------------------------------------
  /// \brief  returns the magnitude of the quaternion
  /// \return  The magnitude of the quaternion
  ///
  Real Mag() const ;
  /// \brief test for equality
  /// @param [in] _q the quaternion to test against
  /// \returns true if the same (based on EPSILON test range) or false
  inline bool operator == (
                           const Quaternion& _q
                          ) const;
  //--------------------------------------------------------------------------
  /// \brief  this function spherically interpolates between two quaternions with respect to t
  /// @param [in]  _q1  -  the first quaternion
  /// @param [in]  _q2  -  the second quaternion
  /// @param [in]  _t  -  the interpolating t value
  ///
  friend Quaternion SLERP(
                          const Quaternion &_q1,
                          const Quaternion &_q2,
                          const float &_t
                          );

  //--------------------------------------------------------------------------
  /// \brief  the streaming operator for the quaternion
  /// @param [in]  _ifs  -  the input stream
  /// @param [in]  _q  -  the place to read the values into
  ///
  friend std::istream& operator >> (
                                    std::istream& _ifs,
                                    Quaternion &_q
                                   )
                                   {
                                    return _ifs >> _q.m_x >> _q.m_y >> _q.m_z >> _q.m_w;
                                   }
  //--------------------------------------------------------------------------
  /// \brief  the streaming operator for the quaternion
  /// @param [in]  i_ifs  -  the input stream
  /// @param [in]  i_q  -  the place to read the values into
  ///
  friend std::ostream& operator << (
                                    std::ostream& i_ifs,
                                    Quaternion &i_q
                                   )
                                   {
                                    return i_ifs << i_q.m_x << " " << i_q.m_y << " " << i_q.m_z << " " << i_q.m_w;
                                   }

protected :
    /// the quaternion data for x
    Real m_x;
    /// the quaternion data for y
    Real m_y;
    /// the quaternion data for z
    Real m_z;
    /// the quaternion data for w
    Real m_w;
}; // end of class

/// \brief  If the original rotation was 'orig' and it got rotated to 'qnew',
///     then this function will return the quaternion that will transform
///     you from orig to qnew, ie the difference between the two rotations
///
/*  static Quaternion DIFF(const Quaternion& orig, const Quaternion& qnew) {
  Quaternion d;
  d = -orig * qnew;
  return d;
}*/
}

#include "Matrix.h"

#endif
