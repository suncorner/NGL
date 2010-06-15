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
#include "Matrix.h"
#include "Quaternion.h"
#include "Util.h"
#include <iostream>
#include <assert.h>
#ifdef LINUX
  #include <cstring> // for memset
#endif

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
Matrix::Matrix()
{
	memset(&m_m,0,sizeof(m_m));
	m_00=1.0f;
	m_11=1.0f;
	m_22=1.0f;
	m_33=1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
Matrix::Matrix(
               const Matrix& _m
              )
{
	memcpy(m_m,&_m.m_m,sizeof(m_m));
}

//----------------------------------------------------------------------------------------------------------------------
Matrix::Matrix(
               const int& _m
              )
{
	memset(m_m,0,sizeof(m_m));
	m_00=float(_m);
	m_11=float(_m);
	m_22=float(_m);
	m_33=float(_m);
}

//----------------------------------------------------------------------------------------------------------------------
Matrix::Matrix(
               const float& _m
              )
{
	memset(m_m,0,sizeof(m_m));
	m_00=_m;
	m_11=_m;
	m_22=_m;
	m_33=_m;
}

//----------------------------------------------------------------------------------------------------------------------
Matrix::Matrix(
               const double& _m
              )
{
	memset(m_m,0,sizeof(m_m));
	m_00=float(_m);
	m_11=float(_m);
	m_22=float(_m);
	m_33=float(_m);

}



//----------------------------------------------------------------------------------------------------------------------
/// \todo replace this with function operator overload ()
void Matrix::Mi(
                const GLint _x,
                const GLint _y,
                const Real _equals
               )
{
	m_m[_x][_y]=_equals;
}
//----------------------------------------------------------------------------------------------------------------------
const Matrix& Matrix::Null()
{
	memset(&m_m,0,sizeof(m_m));
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------
const Matrix&  Matrix::Identity()
{
	memset(m_m,0,sizeof(m_m));
	m_00=1.0f;
	m_11=1.0f;
	m_22=1.0f;
	m_33=1.0f;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Matrix Matrix::operator*(
                         const Matrix& _m
                        )const
{
	Matrix temp;

	// row 0
	temp.m_00  =  m_00 * _m.m_00;
	temp.m_01  =  m_01 * _m.m_00;
	temp.m_02  =  m_02 * _m.m_00;
	temp.m_03  =  m_03 * _m.m_00;

	temp.m_00 +=  m_10 * _m.m_01;
	temp.m_01 +=  m_11 * _m.m_01;
	temp.m_02 +=  m_12 * _m.m_01;
	temp.m_03 +=  m_13 * _m.m_01;

	temp.m_00 +=  m_20 * _m.m_02;
	temp.m_01 +=  m_21 * _m.m_02;
	temp.m_02 +=  m_22 * _m.m_02;
	temp.m_03 +=  m_23 * _m.m_02;

	temp.m_00 +=  m_30 * _m.m_03;
	temp.m_01 +=  m_31 * _m.m_03;
	temp.m_02 +=  m_32 * _m.m_03;
	temp.m_03 +=  m_33 * _m.m_03;


	//  row 1
	temp.m_10  =  m_00 * _m.m_10;
	temp.m_11  =  m_01 * _m.m_10;
	temp.m_12  =  m_02 * _m.m_10;
	temp.m_13  =  m_03 * _m.m_10;

	temp.m_10 +=  m_10 * _m.m_11;
	temp.m_11 +=  m_11 * _m.m_11;
	temp.m_12 +=  m_12 * _m.m_11;
	temp.m_13 +=  m_13 * _m.m_11;

	temp.m_10 +=  m_20 * _m.m_12;
	temp.m_11 +=  m_21 * _m.m_12;
	temp.m_12 +=  m_22 * _m.m_12;
	temp.m_13 +=  m_23 * _m.m_12;

	temp.m_10 +=  m_30 * _m.m_13;
	temp.m_11 +=  m_31 * _m.m_13;
	temp.m_12 +=  m_32 * _m.m_13;
	temp.m_13 +=  m_33 * _m.m_13;


	//  row 2
	temp.m_20  =  m_00 * _m.m_20;
	temp.m_21  =  m_01 * _m.m_20;
	temp.m_22  =  m_02 * _m.m_20;
	temp.m_23  =  m_03 * _m.m_20;

	temp.m_20 +=  m_10 * _m.m_21;
	temp.m_21 +=  m_11 * _m.m_21;
	temp.m_22 +=  m_12 * _m.m_21;
	temp.m_23 +=  m_13 * _m.m_21;

	temp.m_20 +=  m_20 * _m.m_22;
	temp.m_21 +=  m_21 * _m.m_22;
	temp.m_22 +=  m_22 * _m.m_22;
	temp.m_23 +=  m_23 * _m.m_22;

	temp.m_20 +=  m_30 * _m.m_23;
	temp.m_21 +=  m_31 * _m.m_23;
	temp.m_22 +=  m_32 * _m.m_23;
	temp.m_23 +=  m_33 * _m.m_23;


	//  row 3
	temp.m_30  =  m_00 * _m.m_30;
	temp.m_31  =  m_01 * _m.m_30;
	temp.m_32  =  m_02 * _m.m_30;
	temp.m_33  =  m_03 * _m.m_30;

	temp.m_30 +=  m_10 * _m.m_31;
	temp.m_31 +=  m_11 * _m.m_31;
	temp.m_32 +=  m_12 * _m.m_31;
	temp.m_33 +=  m_13 * _m.m_31;

	temp.m_30 +=  m_20 * _m.m_32;
	temp.m_31 +=  m_21 * _m.m_32;
	temp.m_32 +=  m_22 * _m.m_32;
	temp.m_33 +=  m_23 * _m.m_32;

	temp.m_30 +=  m_30 * _m.m_33;
	temp.m_31 +=  m_31 * _m.m_33;
	temp.m_32 +=  m_32 * _m.m_33;
	temp.m_33 +=  m_33 * _m.m_33;
	return temp;
}

//----------------------------------------------------------------------------------------------------------------------
const Matrix& Matrix::operator*= (
                                  const Matrix &_m
                                 )
{
	Matrix temp(*this);

	//  row 0
	m_00  =  temp.m_00 * _m.m_00;
	m_01  =  temp.m_01 * _m.m_00;
	m_02  =  temp.m_02 * _m.m_00;
	m_03  =  temp.m_03 * _m.m_00;

	m_00 +=  temp.m_10 * _m.m_01;
	m_01 +=  temp.m_11 * _m.m_01;
	m_02 +=  temp.m_12 * _m.m_01;
	m_03 +=  temp.m_13 * _m.m_01;

	m_00 +=  temp.m_20 * _m.m_02;
	m_01 +=  temp.m_21 * _m.m_02;
	m_02 +=  temp.m_22 * _m.m_02;
	m_03 +=  temp.m_23 * _m.m_02;

	m_00 +=  temp.m_30 * _m.m_03;
	m_01 +=  temp.m_31 * _m.m_03;
	m_02 +=  temp.m_32 * _m.m_03;
	m_03 +=  temp.m_33 * _m.m_03;


	//  row 1
	m_10  =  temp.m_00 * _m.m_10;
	m_11  =  temp.m_01 * _m.m_10;
	m_12  =  temp.m_02 * _m.m_10;
	m_13  =  temp.m_03 * _m.m_10;

	m_10 +=  temp.m_10 * _m.m_11;
	m_11 +=  temp.m_11 * _m.m_11;
	m_12 +=  temp.m_12 * _m.m_11;
	m_13 +=  temp.m_13 * _m.m_11;

	m_10 +=  temp.m_20 * _m.m_12;
	m_11 +=  temp.m_21 * _m.m_12;
	m_12 +=  temp.m_22 * _m.m_12;
	m_13 +=  temp.m_23 * _m.m_12;

	m_10 +=  temp.m_30 * _m.m_13;
	m_11 +=  temp.m_31 * _m.m_13;
	m_12 +=  temp.m_32 * _m.m_13;
	m_13 +=  temp.m_33 * _m.m_13;


	//  row 2
	m_20  =  temp.m_00 * _m.m_20;
	m_21  =  temp.m_01 * _m.m_20;
	m_22  =  temp.m_02 * _m.m_20;
	m_23  =  temp.m_03 * _m.m_20;

	m_20 +=  temp.m_10 * _m.m_21;
	m_21 +=  temp.m_11 * _m.m_21;
	m_22 +=  temp.m_12 * _m.m_21;
	m_23 +=  temp.m_13 * _m.m_21;

	m_20 +=  temp.m_20 * _m.m_22;
	m_21 +=  temp.m_21 * _m.m_22;
	m_22 +=  temp.m_22 * _m.m_22;
	m_23 +=  temp.m_23 * _m.m_22;

	m_20 +=  temp.m_30 * _m.m_23;
	m_21 +=  temp.m_31 * _m.m_23;
	m_22 +=  temp.m_32 * _m.m_23;
	m_23 +=  temp.m_33 * _m.m_23;


	//  row 3
	m_30  =  temp.m_00 * _m.m_30;
	m_31  =  temp.m_01 * _m.m_30;
	m_32  =  temp.m_02 * _m.m_30;
	m_33  =  temp.m_03 * _m.m_30;

	m_30 +=  temp.m_10 * _m.m_31;
	m_31 +=  temp.m_11 * _m.m_31;
	m_32 +=  temp.m_12 * _m.m_31;
	m_33 +=  temp.m_13 * _m.m_31;

	m_30 +=  temp.m_20 * _m.m_32;
	m_31 +=  temp.m_21 * _m.m_32;
	m_32 +=  temp.m_22 * _m.m_32;
	m_33 +=  temp.m_23 * _m.m_32;

	m_30 +=  temp.m_30 * _m.m_33;
	m_31 +=  temp.m_31 * _m.m_33;
	m_32 +=  temp.m_32 * _m.m_33;
	m_33 +=  temp.m_33 * _m.m_33;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Matrix Matrix::operator+(
                         const Matrix &_m
                        ) const
{
	Matrix Ret;
	const Real* iterA = m_openGL;
	const Real* iterB = _m.m_openGL;
	Real* iterR = Ret.m_openGL;
	const Real* end   = m_openGL+16;

	for( ; iterA != end; ++iterA, ++iterB, ++iterR)
	{
		*iterR = *iterA + *iterB;
	}
	return Ret;
}
//----------------------------------------------------------------------------------------------------------------------
const Matrix& Matrix::operator+=(
                                 const Matrix &_m
                                )
{
	Real* iterA =m_openGL;
	const Real* iterB = _m.m_openGL;
	const Real* end   = m_openGL+16;

	for( ; iterA != end; ++iterA, ++iterB)
	{
		*iterA += *iterB;
	}
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------
Matrix Matrix::operator*(
                         const Real _i
                        ) const
{
	Matrix ret;
	const Real* iterA = m_openGL;
	Real* iterB = ret.m_openGL;
	const Real* end   = m_openGL+16;

	for( ; iterA != end; ++iterA, ++iterB)
	{
		*iterB = (*iterA) * _i;
	}
	return ret;
}

//----------------------------------------------------------------------------------------------------------------------
const Matrix& Matrix::operator*=(
                                 const Real _i
                                )
{
	for(int y=0; y<4; y++)
	{
		for(int x=0; x<4; x++)
		{
			m_m[y][x]*=_i;
		}
	}
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
Vector Matrix::operator * (
                           const Vector &_v
                          ) const
{
	Vector temp;
	temp.m_x  = m_00 * _v.m_x;
	temp.m_x += m_01 * _v.m_y;
	temp.m_x += m_02 * _v.m_z;
	temp.m_x += m_03 * _v.m_w;

	temp.m_y  = m_10 * _v.m_x;
	temp.m_y += m_11 * _v.m_y;
	temp.m_y += m_12 * _v.m_z;
	temp.m_y += m_13 * _v.m_w;

	temp.m_z  = m_20 * _v.m_x;
	temp.m_z += m_21 * _v.m_y;
	temp.m_z += m_22 * _v.m_z;
	temp.m_z += m_23 * _v.m_w;

	return temp;
}

//----------------------------------------------------------------------------------------------------------------------
const Matrix& Matrix::Transpose()
{
	Matrix tmp(*this);

	for(int row=0; row<4; row++)
	{
		for(int col=0; col<4; col++)
		{
			m_m[row][col]=tmp.m_m[col][row];
		}
	}
	return *this;
}
//----------------------------------------------------------------------------------------------------------------------
void Matrix::LoadModelView() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_openGL);
}
//----------------------------------------------------------------------------------------------------------------------
void Matrix::LoadProjection() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_openGL);
}
//----------------------------------------------------------------------------------------------------------------------
void Matrix::FromModelView()
{
	glGetFloatv(GL_MODELVIEW_MATRIX,m_openGL);
}
//----------------------------------------------------------------------------------------------------------------------
void Matrix::FromProjection()
{
	glGetFloatv(GL_PROJECTION_MATRIX,m_openGL);
}

//----------------------------------------------------------------------------------------------------------------------
void Matrix::RotateX(
                     const Real deg
                    )
{
	Real  sr = sin( DegtoRad(deg) );
	Real  cr = cos( DegtoRad(deg) );
	m_11 =  cr;
	m_21 = -sr;
	m_12 =  sr;
	m_22 =  cr;
}

//----------------------------------------------------------------------------------------------------------------------
void Matrix::RotateY(
                     const Real deg
                    )
{
	Real  sr = sin( DegtoRad(deg) );
	Real  cr = cos( DegtoRad(deg) );

	m_00 =  cr;
	m_20 =  sr;
	m_02 = -sr;
	m_22 =  cr;
}

//----------------------------------------------------------------------------------------------------------------------
void Matrix::RotateZ(
                     const Real deg
                    )
{
	Real  sr = sin( DegtoRad(deg));
	Real  cr = cos( DegtoRad(deg));
	m_00 =  cr;
	m_10 = -sr;
	m_01 =  sr;
	m_11 =  cr;
}

//----------------------------------------------------------------------------------------------------------------------
void Matrix::Translate(
                       const Real x,
                       const Real y,
                       const Real z
                      )
{
	m_03 = x;
	m_13 = y;
	m_23 = z;
}

//----------------------------------------------------------------------------------------------------------------------
void Matrix::Scale(
                   const Real x,
                   const Real y,
                   const Real z
                  )
{
	m_00 = x;
	m_11 = y;
	m_22 = z;
}

//----------------------------------------------------------------------------------------------------------------------
void Matrix::SubMatrix3x3(
                          const int _i,
                          const int _j,
                          Real o_mat[]
                          ) const
{
	int ti, tj, idst=0, jdst=0;

	for ( ti = 0; ti != 4; ++ti )
	{
		if ( ti < _i )
		{
			idst = ti;
		}
		else
		{
			if ( ti > _i )
			{
				idst = ti-1;
			}

			for ( tj = 0; tj != 4; ++tj )
			{
				if ( tj < _j )
				{
					jdst = tj;
				}
				else if ( tj > _j )
				{
					jdst = tj-1;
				}
				if ( ti != _i && tj != _j )
				{
					o_mat[idst*3 + jdst] = m_openGL[ti*4 + tj];
				}
			}
		} // end else
	}// end for
}
//----------------------------------------------------------------------------------------------------------------------
Real Matrix::Determinant() const
{
	Real det, result = 0, i = 1;
	Real matrixSub3x3[9];

	for( int n = 0; n < 4; ++n, i *= -1 )
	{
		SubMatrix3x3( 0, n, matrixSub3x3 );

		det =   matrixSub3x3[0] * ( matrixSub3x3[4]*matrixSub3x3[8] - matrixSub3x3[7]*matrixSub3x3[5] )
			- matrixSub3x3[1] * ( matrixSub3x3[3]*matrixSub3x3[8] - matrixSub3x3[6]*matrixSub3x3[5] )
			+ matrixSub3x3[2] * ( matrixSub3x3[3]*matrixSub3x3[7] - matrixSub3x3[6]*matrixSub3x3[4] );

		result += m_openGL[n] * det * i;
	}

	return result;
}

//----------------------------------------------------------------------------------------------------------------------
bool Matrix::Inverse(
                     Matrix& o_result
                    ) const
{
	Real determinant = Determinant();
	Real matrixSub3x3[9];

	int i, j, sign;

	// if the determinant is 0 (or as near as makes no difference), we cannot
	// calculate the inverse
	if ( fabs(determinant) < 0.0005 )
	{
		return false;
	}
	for ( i = 0; i < 4; ++i)
	{
		for ( j = 0; j < 4; ++j )
		{
			sign = 1 - ( (i +j) % 2 ) * 2;
			SubMatrix3x3( i, j, matrixSub3x3 );

			Real det =    matrixSub3x3[0] * ( matrixSub3x3[4]*matrixSub3x3[8] - matrixSub3x3[7]*matrixSub3x3[5] )
						- matrixSub3x3[1] * ( matrixSub3x3[3]*matrixSub3x3[8] - matrixSub3x3[6]*matrixSub3x3[5] )
						+ matrixSub3x3[2] * ( matrixSub3x3[3]*matrixSub3x3[7] - matrixSub3x3[6]*matrixSub3x3[4] );
			o_result.m_openGL[i+j*4] = ( det * sign ) / determinant;
		}
	}
	return true;
}


//----------------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(
                         std::ostream &_output,
                         const ngl::Matrix &_m
                        )
{
/// \todo use boost::format to change this
	std::cout.setf(std::ios::fixed|std::ios::adjustfield|std::ios::showpos);
	std::cout.precision(2);
	return _output
		<<"["<<_m.m_00<<","<<_m.m_01<<","<<_m.m_02<<","<<_m.m_03<<"]"<<std::endl
		<<"["<<_m.m_10<<","<<_m.m_11<<","<<_m.m_12<<","<<_m.m_13<<"]"<<std::endl
		<<"["<<_m.m_20<<","<<_m.m_21<<","<<_m.m_22<<","<<_m.m_23<<"]"<<std::endl
		<<"["<<_m.m_30<<","<<_m.m_31<<","<<_m.m_32<<","<<_m.m_33<<"]"<<std::endl;
}


//----------------------------------------------------------------------------------------------------------------------
void Matrix::Euler(
                   const float _angle,
                   const float _x,
                   const float _y,
                   const float _z
                  )
{
	// Axis and Angle matrix rotation see
	// http://en.wikipedia.org/wiki/Rotation_matrix for more details
	float c = cos(DegtoRad(_angle));
	float s = sin(DegtoRad(_angle));
	float C=1-c;
	float xs  = _x*s;  float  ys = _y*s;  float  zs = _z*s;
	float xC  = _x*C;  float  yC = _y*C;  float  zC = _z*C;
	float xyC = _x*yC; float yzC = _y*zC; float zxC = _z*xC;

	m_m[0][0]=_x*xC+c;  m_m[0][1]= xyC-zs;  m_m[0][2]= zxC+ys;
	m_m[1][0]=xyC+zs;   m_m[1][1]=_y*yC+c;  m_m[1][2]= yzC-xs;
	m_m[2][0]=zxC-ys;   m_m[2][1]=yzC+xs;  m_m[2][2]=_z*zC+c;

}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Matrix::AsQuaternion() const
{

	// calculate trace of the matrix
	float T = m_openGL[0] + m_openGL[5] + m_openGL[10] + 1;

	// if trace is greater than 0, calculate an instant calculation
	if( T > 0 )
	{
		float S = static_cast<float>( 0.5f / sqrt(T) );
		return Quaternion(  static_cast<float>( ( m_openGL[6] - m_openGL[9] ) * S),
							static_cast<float>( ( m_openGL[8] - m_openGL[2] ) * S),
							static_cast<float>( ( m_openGL[1] - m_openGL[4] ) * S),
							static_cast<float>( 0.25f / S)
							);
	}
	float BigF = m_openGL[0];
	unsigned char check=0;
	if( m_openGL[5] > BigF )
	{
		check = 1;
		BigF = m_openGL[5];
	}
	if( m_openGL[10] > BigF )
	{
		check = 2;
		BigF = m_openGL[10];
	}
	switch(check)
	{
		case 0:
		{
			float S  = static_cast<float>( sqrt( 1.0f + m_openGL[0] - m_openGL[5] - m_openGL[10] ) * 2.0f );

			return Quaternion( 0.5f / S,
				(m_openGL[1] + m_openGL[4] ) / S,
				(m_openGL[2] + m_openGL[8] ) / S,
				(m_openGL[6] + m_openGL[9] ) / S );
		}
		case 1:
		{
			float S  = static_cast<float>( sqrt( 1.0f + m_openGL[5] - m_openGL[0] - m_openGL[10] ) * 2.0f );

			return Quaternion((m_openGL[1] + m_openGL[4] ) / S,
				0.5f / S,
				(m_openGL[6] + m_openGL[9] ) / S,
				(m_openGL[2] + m_openGL[8] ) / S );
		}
		case 2:
		{
			float S  = static_cast<float>( sqrt( 1.0f + m_openGL[10] - m_openGL[0] - m_openGL[5] ) * 2.0f );

			return Quaternion((m_openGL[2] + m_openGL[8] ) / S,
				(m_openGL[6] + m_openGL[9] ) / S,
				0.5f / S,
				(m_openGL[1] + m_openGL[4] ) / S );
		}
		default:
		{
			assert(0 && "SHOULDN'T GET HERE!!!");
			break;
		}
	}// end switch
	return Quaternion();

}
//----------------------------------------------------------------------------------------------------------------------

}; // end namespace ngl



