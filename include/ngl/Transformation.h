#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

// Library includes
#include "Vector.h"
#include "Matrix.h"
#include "NGLassert.h"
#include "Transformation.h"

/// \class Transformation "include/ngl/Transformation.h"
/// \author Vincent Bonnet
/// \version 1.5
/// \date 14/03/10 Last Revision 14/03/10
/// \brief Transformation describes a transformation (translate, scale, rotation)
/// modifed by j macey and included into NGL

namespace ngl
{

  enum ACTIVEMATRIX{NORMAL,TRANSPOSE,INVERSE};

class Transformation
{
public:

  /// \brief Constructor
  Transformation();

  /// \brief method to set the scale
  /// @param[in] _vScale scale
  void SetScale(
                const ngl::Vector& _scale
               );
  void SetScale(
                    const Real _x,
                    const Real _y,
                    const Real _z
                  );

  /// \brief method to set the position
  /// @param[in] _vPosition position
  void SetPosition(
                    const ngl::Vector& _position
                  );
  void SetPosition(
                    const Real _x,
                    const Real _y,
                    const Real _z
                  );

  /// \brief method to set the rotation
  /// @param[in] _vRotation rotation
  void SetRotation(
                    const ngl::Vector& _rotation
                  );
  void SetRotation(
                    const Real _x,
                    const Real _y,
                    const Real _z
                  );
  /// @brief a method to set all the transforms to the identity
  void Reset();

  /// \brief function to get the scale
  /// \returns the scale
  const ngl::Vector& GetScale()  const      { return m_scale;  }

  /// \brief function to get the position
  /// \returns the position
  const ngl::Vector& GetPosition() const    { return m_position;  }

  /// \brief function to get the rotation
  /// \returns the rotation
  const ngl::Vector& GetRotation() const    { return m_rotation;  }

  /// \brief function to get the matrix when the transformation is const. it asserts when the matrix is not computed
  /// \returns the matrix
  const ngl::Matrix& GetMatrix() const { NGL_ASSERT(m_isMatrixComputed); return m_matrix; }

  /// \brief function to get the matrix. It computes the matrix if it's dirty
  /// \returns the matrix
  const ngl::Matrix& GetMatrix() { ComputeMatrices();  return m_matrix;  }

  /// \brief function to get the transpose matrix when the transformation is const. it asserts when the transpose matrix is not computed
  /// \returns the transpose matrix
  const ngl::Matrix& GetTransposeMatrix() const {  NGL_ASSERT(m_isMatrixComputed); return m_transposeMatrix; }

  /// \brief function to get the transpose matrix. It computes the transpose matrix if it's dirty
  /// \returns the transpose matrix
  const ngl::Matrix& GetTransposeMatrix() {  ComputeMatrices(); return m_transposeMatrix; }

  /// \brief function to get the inverse matrix when the transformation is const. it asserts when the inverse matrix is not computed
  /// \returns the inverse matrix
  const ngl::Matrix& GetInverseMatrix() const { NGL_ASSERT(m_isMatrixComputed); return m_inverseMatrix; }

  /// \brief function to get the inverse matrix. It computes the inverse matrix if it's dirty
  /// \returns the inverse matrix
  const ngl::Matrix& GetInverseMatrix()  {   ComputeMatrices(); return m_inverseMatrix; }

  void operator*=(
                   const Transformation &_m
                 );


  ///  \brief operator for Transform multiplication will do a matrix
  /// multiplication on each of the matrices
  /// @param[in] _m the Transform to multiply the current one by
  /// \returns all the transform matrix members * my _m members
  Transformation operator*(
                           const Transformation &_m
                          ) const;
  void LoadMatrixToShader(
                          std::string _shader,
                          std::string _param,
                          ACTIVEMATRIX _which=TRANSPOSE
                         );
  void LoadGlobalAndCurrentMatrixToShader(
                                          std::string _shader,
                                          std::string _param,
                                          ngl::Transformation _global,
                                          ACTIVEMATRIX _which=TRANSPOSE
                                         );
protected :

  /// position
  ngl::Vector m_position;

  /// scale
  ngl::Vector m_scale;

  /// rotation
  ngl::Vector m_rotation;

  /// boolean defines if the matrix is dirty or not
  bool m_isMatrixComputed;

  /// matrix transformation
  ngl::Matrix m_matrix;

  /// transpose matrix transformation
  ngl::Matrix m_transposeMatrix;

  /// inverse matrix transformation
  ngl::Matrix m_inverseMatrix;

  /// \brief method to compute the matrix, transpose and inverse matrix. set the m_bIsMatrixComputed variable to true.
  void ComputeMatrices();
};

}; // end ngl namespace
#endif
