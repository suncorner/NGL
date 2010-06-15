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
#include "Vector.h"
#include "NGLassert.h"
#include "Matrix.h"
#include <cmath>

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
void Vector::Normal() const
{
	glNormal3f(m_x,m_y,m_z);
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::Vertex() const
{
	glVertex3f(m_x,m_y,m_z);
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::Translate() const
{
	glTranslatef(m_x,m_y,m_z);
}

//----------------------------------------------------------------------------------------------------------------------
Real Vector::Dot(
                 const Vector& _v
                )const
{
	return m_x * _v.m_x + m_y * _v.m_y + m_z * _v.m_z;
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::Set(
                 const Real& _x,
                 const Real& _y,
                 const Real& _z,
                 const Real& _w
                )
{
	m_x=_x;
	m_y=_y;
	m_z=_z;
	m_w=_w;
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::Set(
                 const Vector& _v
                )
{
   m_x=_v.m_x;
   m_y=_v.m_y;
   m_z=_v.m_z;
   m_w=_v.m_w;
}
//----------------------------------------------------------------------------------------------------------------------
void Vector::Set(
                 const Vector* _v
                )
{
	m_x=_v->m_x;
	m_y=_v->m_y;
	m_z=_v->m_z;
	m_w=_v->m_w;
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::Null()
{
	m_x=0.0f;
	m_y=0.0f;
	m_z=0.0f;
	m_w=1.0f;
}

//----------------------------------------------------------------------------------------------------------------------
Real& Vector::operator[](
                         const int& _i
                        )
{
	NGL_ASSERT(_i >=0 || _i<=4);
	return (&m_x)[_i];
}

//----------------------------------------------------------------------------------------------------------------------
Real Vector::Length() const
{
	return (Real)sqrt((m_x*m_x)+(m_y*m_y)+(m_z*m_z));
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::Reverse()
{
	m_x=-m_x;
	m_y=-m_y;
	m_z=-m_z;
}

//----------------------------------------------------------------------------------------------------------------------
Vector Vector::operator-() const
{
	return Vector(-m_x,-m_y,-m_z,m_w);
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::Normalize()
{
	Real len=(Real)sqrt(m_x*m_x+m_y*m_y+m_z*m_z);
	NGL_ASSERT(len!=0);
	m_x/=len;
	m_y/=len;
	m_z/=len;
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::Cross(
                   const Vector& _v1,
                   const Vector& _v2
                  )
{
	m_x=_v1.m_y*_v2.m_z-_v1.m_z*_v2.m_y;
	m_y=_v1.m_z*_v2.m_x-_v1.m_x*_v2.m_z;
	m_z=_v1.m_x*_v2.m_y-_v1.m_y*_v2.m_x;
}

//----------------------------------------------------------------------------------------------------------------------
Vector Vector::Cross(
                     const Vector& _v
                    )const
{
	return Vector(
								m_y*_v.m_z - m_z*_v.m_y,
								m_z*_v.m_x - m_x*_v.m_z,
								m_x*_v.m_y - m_y*_v.m_x,
								0.0
							 );

}

//----------------------------------------------------------------------------------------------------------------------
void Vector::operator+=(
                        const Vector& _v
                       )
{
	m_x+=_v.m_x;
	m_y+=_v.m_y;
	m_z+=_v.m_z;
	m_w=0.0;
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::operator/=(
                        const Real& _v
                       )
{
	NGL_ASSERT(_v !=0);
	m_x/=_v;
	m_y/=_v;
	m_z/=_v;
	m_w=0.0;
}

//----------------------------------------------------------------------------------------------------------------------
void Vector::operator-=(
                        const Vector& _v
                       )
{
	m_x-=_v.m_x;
	m_y-=_v.m_y;
	m_z-=_v.m_z;
	m_w=0.0;
}

//----------------------------------------------------------------------------------------------------------------------
Vector Vector::operator/(
                         const Real& _v
                        )const
{
	return Vector(
								m_x/_v,
								m_y/_v,
								m_z/_v,
								m_w
								);
}

//----------------------------------------------------------------------------------------------------------------------
Vector Vector::operator+(
                         const Vector& _v
                        )const
{
	return Vector(
							  m_x+_v.m_x,
							  m_y+_v.m_y,
							  m_z+_v.m_z,
							  m_w
							  );
}

//----------------------------------------------------------------------------------------------------------------------
Vector Vector::operator-(
                         const Vector& _v
                        )const
{
	return Vector(
								m_x-_v.m_x,
								m_y-_v.m_y,
								m_z-_v.m_z,
								m_w
							 );
}

//----------------------------------------------------------------------------------------------------------------------
bool Vector::operator==(
                        const Vector& _v
                       )const
{
	return (
					FCompare(_v.m_x,m_x)  &&
					FCompare(_v.m_y,m_y)  &&
					FCompare(_v.m_z,m_z)
				 );
}
//----------------------------------------------------------------------------------------------------------------------
bool Vector::operator!=(
                        const Vector& _v
                       )const
{
	return (
					!FCompare(_v.m_x,m_x) ||
					!FCompare(_v.m_y,m_y) ||
					!FCompare(_v.m_z,m_z)
				 );
}
//----------------------------------------------------------------------------------------------------------------------
Vector Vector::operator*(
                         const Vector& _v
                        )const
{
	return Vector(
								m_x*_v.m_x,
								m_y*_v.m_y,
								m_z*_v.m_z,
								m_w
							 );
}

//----------------------------------------------------------------------------------------------------------------------
Vector Vector::operator/(
                         const Vector& _v
                        )const
{
	return Vector(
								m_x/_v.m_x,
								m_y/_v.m_y,
								m_z/_v.m_z,
								m_w
								);
}

//----------------------------------------------------------------------------------------------------------------------
Vector Vector::operator *(
                          const Real& _i
                         )const
{
	return Vector(
								m_x*_i,
								m_y*_i,
								m_z*_i,
								m_w
							 );
}

//----------------------------------------------------------------------------------------------------------------------
GLdouble Vector::AngleBetween(
                              const Vector& _v
                             )const
{
 // uses cos(t) = |a| . |b|
// create tmp vectors so we don't have to
// normalize existing ones
	Vector v1 = _v;
	Vector v2 = *this;
	v1.Normalize();
	v2.Normalize();
	return acos(v1.Dot(v2));
}

//----------------------------------------------------------------------------------------------------------------------
double Vector::Inner(
                     const Vector& _v
                    )const
{
	return (
					(m_x * _v.m_x) +
					(m_y * _v.m_y) +
					(m_z * _v.m_z)
				 );
}

//----------------------------------------------------------------------------------------------------------------------
Vector Vector::Outer(
                     const Vector& _v
                    )  const
{
	Real x = (m_y * _v.m_z) - (m_z * _v.m_y);
	Real y = (m_z * _v.m_x) - (m_x * _v.m_z);
	Real z = (m_x * _v.m_y) - (m_y * _v.m_x);

	return Vector(x,y,z,m_w);
}


//----------------------------------------------------------------------------------------------------------------------
Vector & Vector::operator=(
                           const Vector& _v
                          )
{
	m_x = _v.m_x;
	m_y = _v.m_y;
	m_z = _v.m_z;
	m_w = _v.m_w;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(
                         std::ostream& _output,
                         const ngl::Vector& _v
                        )
{
	return _output<<"["<<_v.m_x<<","<<_v.m_y<<","<<_v.m_z<<","<<_v.m_w<<"]";
}
/// \todo warning  don't forget the nasty don't load m_w hack here
//----------------------------------------------------------------------------------------------------------------------
std::istream& operator>>(
                         std::istream& _input,
                         ngl::Vector& _s
                        )
{
	return _input >> _s.m_x >> _s.m_y >> _s.m_z;//>>s.m_w;
}

//----------------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(
                         std::ostream& _output,
                         const ngl::Vector* _s
                        )
{
	return _output<<"["<<_s->m_x<<","<<_s->m_y<<","<<_s->m_z<<","<<_s->m_w<<"]";
}
/// \todo #warning don't forget the nasty don't load m_w hack here

//----------------------------------------------------------------------------------------------------------------------
std::istream& operator>>(
                         std::istream& _input,
                         ngl::Vector *_s
                        )
{
	return _input >> _s->m_x >> _s->m_y >> _s->m_z;//>>s->m_w;
}

//----------------------------------------------------------------------------------------------------------------------
Real Vector::LengthSquared() const
{
	return m_x * m_x+m_y * m_y+ m_z*m_z;
}

//----------------------------------------------------------------------------------------------------------------------
Vector Vector::operator*(
                         const Matrix &_m
                        ) const
{
	return Vector(
								m_x*_m.m_00 + m_y*_m.m_01 + m_z*_m.m_02+ m_w*_m.m_03,
								m_x*_m.m_10 + m_y*_m.m_11 + m_z*_m.m_12+ m_w*_m.m_13,
								m_x*_m.m_20 + m_y*_m.m_21 + m_z*_m.m_22+ m_w*_m.m_23,
								m_x*_m.m_30 + m_y*_m.m_31 + m_z*_m.m_32+ m_w*_m.m_33
							 );
}

}; // end namspace ngl



