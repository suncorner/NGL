#include "Transformation.h"
#include "ShaderManager.h"

namespace ngl
{

// Constructor -------------------------------------------------------------------------------------------------------------------
Transformation::Transformation()
{
  m_position = ngl::Vector(0,0,0);
  m_scale = ngl::Vector(1,1,1);
  m_rotation = ngl::Vector(0,0,0);
  m_isMatrixComputed = false;
  m_matrix=1.0;
  m_transposeMatrix=1.0;
  m_inverseMatrix=1.0;
  ComputeMatrices();
}

// Set scale ---------------------------------------------------------------------------------------------------------------------
void Transformation::SetScale(
                                const ngl::Vector& _scale
                              )
{
  m_scale = _scale;
  m_isMatrixComputed = false;
  ComputeMatrices();
}


void Transformation::SetScale(
                              ngl::Real _x,
                              ngl::Real _y,
                              ngl::Real _z
                              )
{
  m_scale.Set(_x,_y,_z);
  m_isMatrixComputed = false;
  ComputeMatrices();
}

// Set position --------------------------------------------------------------------------------------------------------------------
void Transformation::SetPosition(
                                  const ngl::Vector& _position
                                 )
{
  m_position = _position;
  m_isMatrixComputed = false;
  ComputeMatrices();
}
void Transformation::SetPosition(
                                ngl::Real _x,
                                ngl::Real _y,
                                ngl::Real _z
                                )
{
  m_position.Set(_x,_y,_z);
  m_isMatrixComputed = false;
  ComputeMatrices();
}
// set rotation -------------------------------------------------------------------------------------------------------------------
void Transformation::SetRotation(
                                  const ngl::Vector& _rotation
                                 )
{
  m_rotation = _rotation;
  m_isMatrixComputed = false;
  ComputeMatrices();
}
void Transformation::SetRotation(
                                  ngl::Real _x,
                                  ngl::Real _y,
                                  ngl::Real _z
                                 )
{
  m_rotation.Set(_x,_y,_z);
  m_isMatrixComputed = false;
  ComputeMatrices();
}
// reset matrix ---------------------------------------------------------------------------------------------------------------------
void Transformation::Reset()
{
  m_position = ngl::Vector(0,0,0);
  m_scale = ngl::Vector(1,1,1);
  m_rotation = ngl::Vector(0,0,0);
  m_isMatrixComputed = false;
  m_matrix=1.0;
  m_transposeMatrix=1.0;
  m_inverseMatrix=1.0;
  ComputeMatrices();
}

// comptue matrix ---------------------------------------------------------------------------------------------------------------------
void Transformation::ComputeMatrices()
{
  if (!m_isMatrixComputed)       // need to recalculate
  {
    ngl::Matrix mScale;
    ngl::Matrix mRotationX;
    ngl::Matrix mRotationY;
    ngl::Matrix mRotationZ;
    ngl::Matrix mTranslate;

    // rotation/scale matrix
    ngl::Matrix mRotationScale;
    mScale.Scale(m_scale.m_x, m_scale.m_y, m_scale.m_z);

    mRotationX.Identity();
    mRotationX.RotateX(m_rotation.m_x);
    mRotationY.Identity();
    mRotationY.RotateY(m_rotation.m_y);
    mRotationZ.Identity();
    mRotationZ.RotateZ(m_rotation.m_z);
    mRotationScale = mScale * mRotationX * mRotationY * mRotationZ;

    // transform matrix
    m_matrix = mRotationScale;
    m_matrix.m_m[0][3] = m_position.m_x;
    m_matrix.m_m[1][3] = m_position.m_y;
    m_matrix.m_m[2][3] = m_position.m_z;
    m_matrix.m_m[3][3] = 1;

    // tranpose matrix
    m_transposeMatrix = mRotationScale;
    m_transposeMatrix.Transpose();
    m_transposeMatrix.m_m[3][0] = m_position.m_x;
    m_transposeMatrix.m_m[3][1] = m_position.m_y;
    m_transposeMatrix.m_m[3][2] = m_position.m_z;
    m_transposeMatrix.m_m[3][3] = 1;

    // inverse matrix
    mTranslate.Translate(-m_position.m_x, -m_position.m_y, -m_position.m_z);
    mScale.Scale(1.0f / m_scale.m_x, 1.0f / m_scale.m_y, 1.0f / m_scale.m_z);
    mRotationX.Identity();
    mRotationX.RotateX(-m_rotation.m_x);
    mRotationY.Identity();
    mRotationY.RotateY(-m_rotation.m_y);
    mRotationZ.Identity();
    mRotationZ.RotateZ(-m_rotation.m_z);
    m_inverseMatrix = mTranslate * mRotationZ * mRotationY * mRotationX * mScale  ;

    m_isMatrixComputed = true;

  }
}

void Transformation::operator*= (
                                  const Transformation &_m
                                 )

{
  ComputeMatrices();
  m_matrix*=_m.m_matrix;

  /// transpose matrix transformation
  m_transposeMatrix*=_m.m_transposeMatrix;

  /// inverse matrix transformation
  m_inverseMatrix*=_m.m_inverseMatrix;
}

Transformation Transformation::operator*(
                                         const Transformation &_m
                                        ) const

{
  Transformation t;
  t.m_matrix=this->m_matrix*_m.m_matrix;
  t.m_transposeMatrix=this->m_transposeMatrix*_m.m_transposeMatrix;
  t.m_inverseMatrix=this->m_inverseMatrix*_m.m_inverseMatrix;

  return t;
}
void Transformation::LoadMatrixToShader(
                                        std::string _shader,
                                        std::string _param,
                                        ACTIVEMATRIX _which
                                       )
{
  ComputeMatrices();
  ShaderManager *shader=ngl::ShaderManager::Instance();
  switch (_which)
  {
    case NORMAL :
    {
      shader->SetShaderParamFromMatrix(_shader,_param,m_matrix);
    }
    break;
    case TRANSPOSE :
    {
      shader->SetShaderParamFromMatrix(_shader,_param,m_transposeMatrix);
    }
    break;
    case INVERSE :
    {
      shader->SetShaderParamFromMatrix(_shader,_param,m_inverseMatrix);
    }
    break;

  }


}

void Transformation::LoadGlobalAndCurrentMatrixToShader(
                                                        std::string _shader,
                                                        std::string _param,
                                                        ngl::Transformation _global,
                                                        ACTIVEMATRIX _which
                                                       )
{
  ComputeMatrices();
  ShaderManager *shader=ngl::ShaderManager::Instance();
  switch (_which)
  {
    case NORMAL :
    {
      ngl::Matrix tx=_global.GetMatrix()*this->GetMatrix();
      shader->SetShaderParamFromMatrix(_shader,_param,tx);
    }
    break;
    case TRANSPOSE :
    {
      ngl::Matrix tx=_global.GetTransposeMatrix()*this->GetTransposeMatrix();
      shader->SetShaderParamFromMatrix(_shader,_param,tx);
    }
    break;
    case INVERSE :
    {
      ngl::Matrix tx=_global.GetInverseMatrix()*this->GetInverseMatrix();
      shader->SetShaderParamFromMatrix(_shader,_param,tx);
    }
    break;

  }

}

}; // end ngl
