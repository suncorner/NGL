/*
  Copyright (C) 2009 Rob Bateman / Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITH ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this progra_m.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <cmath>
#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

namespace ngl
{



//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::operator *(
                                  const Quaternion& _q
                                 )const
{
	// create a var to hold the vector part of the two quaternions
	Vector v1( m_x, m_y, m_z );
	Vector v2( _q.m_x, _q.m_y, _q.m_z );

	Real scalar = m_w*_q.m_w - (v1.Dot(v2));
	Vector vector_part = (m_w * v2) + (_q.m_w * v1) + (v1.Cross(v2));

	// return the resulting normalised quaternion
	return Quaternion( vector_part.m_x, vector_part.m_y, vector_part.m_z, scalar ).Normalise();
}

//----------------------------------------------------------------------------------------------------------------------
const Quaternion& Quaternion::Normalise()
{
	Real l_inv = 1.0f/Mag();
	m_x*=l_inv;
	m_y*=l_inv;
	m_z*=l_inv;
	m_w*=l_inv;
	return (*this);
}

//----------------------------------------------------------------------------------------------------------------------
Quaternion Quaternion::Normalised()const
{
	Real l_inv = 1.0f/Mag();
	return Quaternion (m_x*l_inv,m_y*l_inv,m_z*l_inv,m_w*l_inv);
}

//----------------------------------------------------------------------------------------------------------------------
Real Quaternion::Mag()const
{
	return static_cast<Real>( sqrt(m_w*m_w + m_x*m_x + m_y*m_y + m_z*m_z) );
}

//----------------------------------------------------------------------------------------------------------------------
bool Quaternion::operator == (
                              const Quaternion& _q
                             )const
{
	return (
					FCompare(_q.m_x,m_x) &&
					FCompare(_q.m_y,m_y) &&
					FCompare(_q.m_z,m_z) &&
					FCompare(_q.m_w,m_w)
				 );
}

//----------------------------------------------------------------------------------------------------------------------
Matrix Quaternion::AsMatrix() const
{
	Matrix m;
	AsMatrix(m.m_openGL);
	return m;
}


//----------------------------------------------------------------------------------------------------------------------
void Quaternion::FromAxisAngle(
                               const Vector& _axis,
                               const float _angle)
{
	Vector axis = _axis;
	axis.Normalize();
	Real sin_a = static_cast<Real>(sin( _angle / 2.0f ));
	Real cos_a = static_cast<Real>(cos( _angle / 2.0f ));
	m_x = axis.m_x * sin_a;
	m_y = axis.m_y * sin_a;
	m_z = axis.m_z * sin_a;
	m_w = cos_a;
}

//----------------------------------------------------------------------------------------------------------------------
void Quaternion::ToAxisAngle(
                             Vector& o_axis,
                             float &o_angle
                            )
{
	Quaternion Q( this->Normalised() );
	float cos_a = m_w;
	o_angle = static_cast<float>(acos( cos_a ) * 2.0f);
	float sin_a = static_cast<Real>(sqrt( 1.0f - cos_a * cos_a ));
	if( fabs( sin_a ) < 0.0005f )
	{
		sin_a = 1.0f;
	}
	o_axis.m_x = m_x / sin_a;
	o_axis.m_y = m_y / sin_a;
	o_axis.m_z = m_z / sin_a;
}

//----------------------------------------------------------------------------------------------------------------------
void Quaternion::FromEulerAngles(
                                 const float _ax,
                                 const float _ay,
                                 const float _az
                                )
{
	Vector vx( 1, 0, 0 );
	Vector vy( 0, 1, 0 );
	Vector vz( 0, 0, 1 );

	Quaternion qx, qy, qz, qt;
	qx.FromAxisAngle( vx, _ax );
	qy.FromAxisAngle( vy, _ay );
	qz.FromAxisAngle( vz, _az );
	qt = qx * qy;
	*this = qt * qz;
}


//----------------------------------------------------------------------------------------------------------------------
void Quaternion::FromMatrix(
                            const Matrix &_mat
                           )
{
	float T = 1 + _mat.m_openGL[0] + _mat.m_openGL[5] + _mat.m_openGL[10];
	if ( T > 0.00000001f ) //to avoid large distortions!
	{
		float S = static_cast<float>(sqrt(T) * 2.0f);
		m_x = ( _mat.m_openGL[6] - _mat.m_openGL[9] ) / S;
		m_y = ( _mat.m_openGL[8] - _mat.m_openGL[2] ) / S;
		m_z = ( _mat.m_openGL[1] - _mat.m_openGL[4] ) / S;
		m_w = 0.25f * S;
	}
	else if ( _mat.m_openGL[0] > _mat.m_openGL[5] &&
						 _mat.m_openGL[0] > _mat.m_openGL[10] )
	{    // Column 0:
		float S  = static_cast<float>(sqrt( 1.0f + _mat.m_openGL[0] - _mat.m_openGL[5] - _mat.m_openGL[10] ) * 2.0f);
		m_x = 0.25f * S;
		m_y = (_mat.m_openGL[1] + _mat.m_openGL[4] ) / S;
		m_z = (_mat.m_openGL[8] + _mat.m_openGL[2] ) / S;
		m_w = (_mat.m_openGL[6] - _mat.m_openGL[9] ) / S;
	}
	else if ( _mat.m_openGL[5] > _mat.m_openGL[10] )
	{      // Column 1:
		float S  = static_cast<float>(sqrt( 1.0 + _mat.m_openGL[5] - _mat.m_openGL[0] - _mat.m_openGL[10] ) * 2.0f);
		m_x = (_mat.m_openGL[1] + _mat.m_openGL[4] ) / S;
		m_y = 0.25f * S;
		m_z = (_mat.m_openGL[6] + _mat.m_openGL[9] ) / S;
		m_w = (_mat.m_openGL[8] - _mat.m_openGL[2] ) / S;
	}
	else
	{                    // Column 2:
		float S  = static_cast<float>(sqrt( 1.0 + _mat.m_openGL[10] - _mat.m_openGL[0] - _mat.m_openGL[5] ) * 2.0f);
		m_x = (_mat.m_openGL[8] + _mat.m_openGL[2] ) / S;
		m_y = (_mat.m_openGL[6] + _mat.m_openGL[9] ) / S;
		m_z = 0.25f * S;
		m_w = (_mat.m_openGL[1] - _mat.m_openGL[4] ) / S;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void Quaternion::AsMatrix(
												  Real* _matrix
												 )const
{
	// sacrafice a few bytes to pre-calculate some values
	float xx = m_x * m_x;
	float xy = m_x * m_y;
	float xz = m_x * m_z;
	float xw = m_x * m_w;
	float yy = m_y * m_y;
	float yz = m_y * m_z;
	float yw = m_y * m_w;
	float zz = m_z * m_z;
	float zw = m_z * m_w;

	// [0] -> [3]
	*(  _matrix) = 1.0f - 2.0f * (yy+zz);
	*(++_matrix) =        2.0f * (xy+zw);
	*(++_matrix) =        2.0f * (xz-yw);
	*(++_matrix) =     0.0f;

	// [4] -> [7]
	*(++_matrix) =        2.0f * (xy-zw);
	*(++_matrix) = 1.0f - 2.0f * (xx+zz);
	*(++_matrix) =        2.0f * (yz+xw);
	*(++_matrix) =     0.0f;

	// [8] -> [11]
	*(++_matrix) =        2.0f * (xz+yw);
	*(++_matrix) =        2.0f * (yz-xw);
	*(++_matrix) = 1.0f - 2.0f * (xx+yy);
	*(++_matrix) =     0.0f;

	// [12] -> [15]
	*(++_matrix) =     0.0f;
	*(++_matrix) =     0.0f;
	*(++_matrix) =     0.0f;
	*(++_matrix) =     1.0f;
}


/// a function to spherically interpolate the two quaternions
//
//----------------------------------------------------------------------------------------------------------------------
Quaternion SLERP(
                 const Quaternion &_q1,
                 const Quaternion &_q2,
                 const float &_t
                )
{
	// for some reason, though why I don't actually know, the second quaternion
	// needs to be inverted if the angle between them is greater than 90 begrees.
	// I think it is to control the direction of the angular rotation so that the
	// bone always slerps through the shortest angle. Just guessing though so don't
	// take my word for it.... RB
	//
	Quaternion Second;

	// will hold the final position
	Quaternion Final;

	// if two quarternions are the same
	if ( _q1 == _q2 )
	{
		// no point in slerping the_m....
		return _q1;
	}

	// perform dot product
	float product = ( _q1.m_x * _q2.m_x ) +
									( _q1.m_y * _q2.m_y ) +
									( _q1.m_z * _q2.m_z ) +
									( _q1.m_w * _q2.m_w );

	// if the angle is greater than 90degress, negate quaternion and product
	if ( product < 0.001f )
	{
		Second  = Quaternion(-_q2.m_x,-_q2.m_y,-_q2.m_z,-_q2.m_w);
		product = -product;
	}
	else
	{
		Second = _q2;
	}

	// calculate the linear t values for the interpolation
	float interpolating_t    = _t;
	float interpolating_invt = 1.0f-_t;

	if(product > 1)
	{
		product=0.999999f;
	}
	if(product < -1)
	{
		product=-0.999999f;
	}
	// spherical interpolation takes place around a sphere. Therefore we use the
	// product (remeber dot product to finds angle between 2 vectors) to get the
	// angle we have to rotate to go from _q1 to _q2.
	//
	float theta    = static_cast<float>( acos(product) );

	// precalculate the sin value
	//
	float sinTheta = static_cast<float>( sin(theta) );

	if(sinTheta != 0.0f)
	{
		interpolating_invt = static_cast<float>( sin(interpolating_invt * theta) / sinTheta   );
		interpolating_t    = static_cast<float>( sin(interpolating_t    * theta) / sinTheta   );
	}

	// perform the interpolation
	Final.m_x = (interpolating_invt * _q1.m_x) + (interpolating_t * Second.m_x);
	Final.m_y = (interpolating_invt * _q1.m_y) + (interpolating_t * Second.m_y);
	Final.m_z = (interpolating_invt * _q1.m_z) + (interpolating_t * Second.m_z);
	Final.m_w = (interpolating_invt * _q1.m_w) + (interpolating_t * Second.m_w);

	Final.Normalise();

	// return the result of interpolation
	return Final;
}

//----------------------------------------------------------------------------------------------------------------------
Quaternion::Quaternion(
                       const Matrix& _m
                      )
{
	// calculate trace on _matrix
	float T = _m.m_m[0][0] + _m.m_m[1][1] + _m.m_m[2][2] + 1.0f;

	// if the trace of the _matrix is greater than zero perform an instant calculation.
	if( T > 0 )
	{
		float S = static_cast<float>(0.5f / sqrt(T));
		m_x = ( _m.m_m[1][2] - _m.m_m[2][1] ) * S;
		m_y = ( _m.m_m[2][0] - _m.m_m[0][2] ) * S;
		m_z = ( _m.m_m[0][1] - _m.m_m[1][0] ) * S;
		m_w = 0.25f / S;
	}
	else
	{
		int ind=0;
		float comp = _m.m_m[0][0];
		if(comp < _m.m_m[1][1])
		{
			comp = _m.m_m[1][1];
			ind = 1;
		}
		if(comp < _m.m_m[2][2])
		{
			comp = _m.m_m[2][2];
			ind = 2;
		}
		switch(ind)
		{
			case 0:
			{
				float _1_over_S  = static_cast<float>(0.5f/sqrt( 1.0f + _m.m_m[0][0] - _m.m_m[1][1] - _m.m_m[2][2] ));
				m_x = 0.5f * _1_over_S;
				m_y = (_m.m_m[1][0] + _m.m_m[0][1] ) * _1_over_S;
				m_z = (_m.m_m[2][0] + _m.m_m[0][2] ) * _1_over_S;
				m_w = (_m.m_m[2][1] + _m.m_m[1][2] ) * _1_over_S;
				break;
			}

			case 1:
			{
				float _1_over_S  = static_cast<float>(0.5f/sqrt( 1.0f - _m.m_m[0][0] + _m.m_m[1][1] - _m.m_m[2][2] ));

				m_x = (_m.m_m[1][0] + _m.m_m[0][1] ) * _1_over_S;
				m_y = 0.5f * _1_over_S;
				m_z = (_m.m_m[2][1] + _m.m_m[1][2] ) * _1_over_S;
				m_w = (_m.m_m[2][0] + _m.m_m[0][2] ) * _1_over_S;
				break;
			}
			case 2:
			{
				float _1_over_S  = static_cast<float>(0.5f/sqrt( 1.0f - _m.m_m[0][0] - _m.m_m[1][1] + _m.m_m[2][2] ));

				m_x = (_m.m_m[2][0] + _m.m_m[0][2] ) * _1_over_S;
				m_y = (_m.m_m[2][1] + _m.m_m[1][2] ) * _1_over_S;
				m_z = 0.5f * _1_over_S;
				m_w = (_m.m_m[1][0] + _m.m_m[0][1] ) * _1_over_S;

				break;
			}
		} //end switch
	}//end else

}

}; // end ngl namespace


