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
#include <iostream>
#include "Camera.h"
#include "Util.h"
#include "NGLassert.h"


namespace ngl
{
// a lot of this stuff is from the HILL book Computer Graphics with OpenGL 2nd Ed Prentice Hall
// a very good book

//----------------------------------------------------------------------------------------------------------------------

Camera::Camera()
{
	// Set some  default values
	m_l=-3;
	m_r=3;
	m_t=3;
	m_b=-3;
	m_nr=-1;
	m_fr=-5;
	m_zNear=1.0f;
	m_zFar=150.0f;
	m_aspect=640.0f/480.0f;
	m_fov=45.0f;
	m_projectionMode=PERSPECTIVE;
	m_width=640;
	m_height=480;
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::SetOrthoParams(
                            const Real _l,
                            const Real _r,
                            const Real _t,
                            const Real _b,
                            const Real _n,
                            const Real _f
                           )
{
	m_l=_l;
	m_r=_r;
	m_t=_t;
	m_b=_b;
	m_nr=_n;
	m_fr=_f;
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: SetDefaultCamera()
{ // make default camera
	m_l=-3;
	m_r=3;
	m_t=3;
	m_b=-3;
	m_nr=-1;
	m_fr=-5;

	SetShape(45.0f, 720/(Real)576, 0.1f, 200.0f,PERSPECTIVE); // good default values here
	Set(Vector(5.0, 5.0, 5.0),Vector( 0.0, 0.0, 0.0),Vector(0, 1, 0));
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: Set(
                   const Vector &_eye,
                   const Vector &_look,
                   const Vector &_up
                  )
{
	// make U, V, N vectors
	m_eye=_eye;
	m_look=_look;
	m_up=_up;

	m_n=m_eye-m_look;
	m_u=m_up.Cross(m_n);
	m_v=m_n.Cross(m_u);
	m_u.Normalize();
	m_v.Normalize();
	m_n.Normalize();
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
Camera::Camera(
               const Vector &_eye,
               const Vector &_look,
               const Vector &_up,
               const CAMERAPROJECTION _proj
              )
{
	m_projectionMode=_proj;
	SetDefaultCamera();
	Set(_eye,_look,_up);
}


//----------------------------------------------------------------------------------------------------------------------
void Camera::ChangeProjectionMode(
                                  const CAMERAPROJECTION _proj
                                 )
{
	m_projectionMode=_proj;
	SetProjectionMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::SetModelViewMatrix()
{
	// grab a pointer to the matrix so we can index is quickly
	Real *M=(Real *)&m_modelView.m_m;


	M[0] =  m_u.m_x; M[4] =  m_u.m_y; M[8]  =  m_u.m_z;  M[12] = -m_eye.Dot(m_u);
	M[1] =  m_v.m_x; M[5] =  m_v.m_y; M[9]  =  m_v.m_z;  M[13] = -m_eye.Dot(m_v);
	M[2] =  m_n.m_x; M[6] =  m_n.m_y; M[10] =  m_n.m_z;  M[14] = -m_eye.Dot(m_n);
	M[3] =  0;       M[7] =  0;       M[11] =  0;        M[15] = 1.0;
	// now load them GL modelview matrix
	m_modelView.LoadModelView();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::SetOrthoProjection()
{
	m_projection.Identity();

	m_projection.m_m[0][0]=2.0f /(m_r-m_l);
	m_projection.m_m[0][3]=-((m_r+m_l)/(m_r-m_l));

	m_projection.m_m[1][1]=2.0f/(m_t-m_b);
	m_projection.m_m[1][3]=-((m_t+m_b)/(m_t-m_b));

	m_projection.m_m[2][2]=2.0f / (m_fr-m_nr) ;//(m_zFar-m_zNear));
	m_projection.m_m[2][3]=-((m_fr+m_nr) /(m_fr-m_nr)) ; // (f-n) ;//(m_zFar+m_zNear)/(m_zFar-m_zNear);

	m_projection.LoadProjection();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::Set2PointProjPoints(
                                 const Vector &_p1,
                                 const Vector &_p2)
{
	m_projPoints[0]=_p1;
	m_projPoints[1]=_p2;
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::Set3PointProjPoints(
                                 const Vector &_p1,
                                 const Vector &_p2,
                                 const Vector &_p3
                                )
{
	m_projPoints[0]=_p1;
	m_projPoints[1]=_p2;
	m_projPoints[2]=_p3;
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::SetTwoPointProjection()
{
	// Work in Progress not correct as yet
	// caluculate the vectors for the 2Point proj
	Vector v1=m_eye-m_projPoints[0];
	Vector v2=m_eye-m_projPoints[1];

	double angle =v1.AngleBetween(v2);
	float c=sin(DegtoRad(angle));
	float s=cos(DegtoRad(angle));
	m_projection.Identity();
	std::cout <<m_eye<<v1<<v2<<" angle "<<angle<<std::endl;

	m_projection.m_m[0][3]=s;
	m_projection.m_m[2][3]=c;

	Real xmin, xmax, ymin, ymax;
	ymax = m_zNear * tan( m_fov * M_PI / 360.0f );
	ymin = -ymax;

	xmin = ymin * m_aspect;
	xmax = ymax * m_aspect;


	m_projection.m_m[3][0]=(-2.0f*m_zFar*m_zNear)/(m_zFar-m_zNear);

	m_projection.m_m[3][2]=-1.0f;
	m_projection.LoadProjection();

}
//----------------------------------------------------------------------------------------------------------------------
void Camera::SetThreePointProjection(){;}
//----------------------------------------------------------------------------------------------------------------------
void Camera::SetPerspProjection()
{
	// note 1/tan == cotangent
	float f= 1.0/tan((m_fov * M_PI / 360.0f)/2.0);
	m_projection.Identity();

	m_projection.m_m[0][0]=f/m_aspect;
	m_projection.m_m[1][1]=f;

	m_projection.m_m[2][2]=(m_zFar+m_zNear)/(m_zNear-m_zFar);
	m_projection.m_m[2][3]=(2*m_zFar*m_zNear)/(m_zNear-m_zFar);

	m_projection.m_m[3][2]=-1;

	// need to transpose to get the correct values
	m_projection.Transpose();
	m_projection.LoadProjection();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::SetProjectionMatrix()
{
	m_projection.Null();
	switch (m_projectionMode)
	{
		case  ORTHOGRAPHIC : { SetOrthoProjection();     break;  }
		case  PERSPECTIVE  : { SetPerspProjection();     break;  }
		case   TWOPOINT    : { SetTwoPointProjection();  break;  }
		case  THREEPOINT   : { SetThreePointProjection(); break; }
	}
}
//----------------------------------------------------------------------------------------------------------------------

void Camera ::SetShape(
                       Real _viewAngle,
                       const Real _aspect,
                       Real _near,
                       Real _far,
                       const CAMERAPROJECTION _proj
                       )

{ // load projection matrix and camera values
	m_projectionMode=_proj;
	if(_viewAngle >180.0)
	{
		_viewAngle=180.0;
	}
	NGL_ASSERT(_far>_near);
	NGL_ASSERT(_near>0.001);
	if(_near>0.0001f)
	{
		_near=0.0001f;
	}
	m_fov = _viewAngle; // viewangle in degrees - must be < 180
	m_aspect = _aspect;
	m_zNear = _near;
	m_zFar = _far;
	SetProjectionMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::SetAspect(
                       const Real _asp
                      )
{
	m_aspect = _asp;
	SetShape(m_fov,m_aspect,m_zNear,m_zFar,m_projectionMode);
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: SetViewAngle(
                            const Real _angle
                           )
{
	m_fov=_angle;
	SetShape(_angle,m_aspect,m_zNear,m_zFar,m_projectionMode);
}


//----------------------------------------------------------------------------------------------------------------------
void Camera :: Slide(
                     const Real _du,
                     const Real _dv,
                     const Real _dn
                    )
{
	// slide eye by amount du * u + dv * v + dn * n;
	m_eye.m_x += _du * m_u.m_x + _dv * m_v.m_x + _dn * m_n.m_x;
	m_eye.m_y += _du * m_u.m_y + _dv * m_v.m_y + _dn * m_n.m_y;
	m_eye.m_z += _du * m_u.m_z + _dv * m_v.m_z + _dn * m_n.m_z;
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: Move(
                    const Real _dx,
                    const Real _dy,
                    const Real _dz
                   )
{
// simply add the translation to the current eye point
	m_eye.m_x += _dx;
	m_eye.m_y += _dy;
	m_eye.m_z += _dz;
	SetModelViewMatrix();
}
//----------------------------------------------------------------------------------------------------------------------
void Camera::MoveBoth(
                      const Real _dx,
                      const Real _dy,
                      const Real _dz
                     )
{
	m_eye.m_x +=_dx;
	m_eye.m_y +=_dy;
	m_eye.m_z +=_dz;
	m_look.m_x+=_dx;
	m_look.m_y+=_dy;
	m_look.m_z+=_dz;
	m_n=m_eye-m_look;
	m_u=m_up.Cross(m_n);
	m_v.Set(m_n.Cross(m_u));
	// normalize vectors
	m_u.Normalize();
	m_v.Normalize();
	m_n.Normalize();
	// pass to OpenGL
	SetModelViewMatrix();
}
//----------------------------------------------------------------------------------------------------------------------
void Camera:: RotAxes(
                      Vector& io_a,
                      Vector& io_b,
                      const Real _angle
                     )
{
// rotate orthogonal vectors a (like x axis) and b(like y axis) through angle degrees
	// convert to radians
	Real ang = M_PI/180.0f*_angle;
	// pre-calc cos and sine
	Real c = cos(ang);
	Real s = sin(ang);
	// tmp for io_a vector
	Vector t( c * io_a.m_x + s * io_b.m_x,  c * io_a.m_y + s * io_b.m_y,  c * io_a.m_z + s * io_b.m_z);
	// now set to new rot value
	io_b.Set(-s * io_a.m_x + c * io_b.m_x, -s * io_a.m_y + c * io_b.m_y, -s * io_a.m_z + c * io_b.m_z);
	// put tmp into _a'
	io_a.Set(t.m_x, t.m_y, t.m_z);
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: Roll(
                    const Real _angle
                   )
{
	RotAxes(m_u, m_v, -_angle);
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: Pitch(
                     const Real _angle
                    )
{
	RotAxes(m_n, m_v, _angle);
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: Yaw(
                   const Real _angle
                  )
{
	RotAxes(m_u, m_n, _angle);
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::MoveEye(
                     const Real _dx,
                     const Real _dy,
                     const Real _dz
                    )
{
	m_eye.m_x+=_dx;
	m_eye.m_y+=_dy;
	m_eye.m_z+=_dz;
	m_n=m_eye-m_look;
	m_u.Set(m_up.Cross(m_n));
	m_v.Set(m_n.Cross(m_u));
	// normalize the vectors
	m_u.Normalize();
	m_v.Normalize();
	m_n.Normalize();
	// pass to OpenGL
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::MoveLook(
                      const Real _dx,
                      const Real _dy,
                      const Real _dz
                     )
{
	m_look.m_x+=_dx;
	m_look.m_y+=_dy;
	m_look.m_z+=_dz;
	m_n=m_eye-m_look;
	m_u.Set(m_up.Cross(m_n));
	m_v.Set(m_n.Cross(m_u));
	// normalise vectors
	m_u.Normalize();
	m_v.Normalize();
	m_n.Normalize();
	// pass to OpenGL
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera::Use()
{
  #warning "this function is deprecated use shader method"
	SetProjectionMatrix();
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: NormalisedYaw(
                             const Real _angle
                            )
{
	// build a rotation matrix around the y axis
	Matrix mat;
	mat.Identity();
	mat.RotateY(_angle);
	//multiply all three local coord vectors by the matrix
	m_u = m_u * mat;
	m_v = m_v * mat;
	m_n = m_n * mat;
	// reset the modelview matrix
	SetModelViewMatrix();
}
//----------------------------------------------------------------------------------------------------------------------
void Camera :: NormalisedRoll(
                              const Real _angle
                             )
{
	// build a rotation matrix around the y axis
	Matrix mat;
	mat.Identity();
	mat.RotateZ(_angle);
	//multiply all three local coord vectors by the matrix
	m_u = m_u * mat;
	m_v = m_v * mat;
	m_n = m_n * mat;
	// reset the modelview matrix
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void Camera :: NormalisedPitch(
                               const Real _angle
                              )
{
	// build a rotation matrix around the y axis
	Matrix mat;
	mat.Identity();
	mat.RotateX(_angle);
	//multiply all three local coord vectors by the matrix
	m_u = m_u * mat;
	m_v = m_v * mat;
	m_n = m_n * mat;
	// reset the modelview matrix
	SetModelViewMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(
                         std::ostream& _output,
                         const Camera &_c
                        )
{
	return _output<<"m_eye"<<_c.m_eye<<" m_look"<<_c.m_look<<" Up"<<_c.m_up;
}


//----------------------------------------------------------------------------------------------------------------------
void Camera::WriteRib(
                      RibExport &_rib
                     ) const
{
	if(_rib.IsOpen()!=0)
	{
		Real *M=(Real *)&m_modelView.m_m;
		_rib.WriteTabs();
		_rib.GetStream() <<"# Camera transform from GraphicsLib Camera\n"  ;
		_rib.GetStream() <<"# now we need to flip the Z axis\n";
		_rib.GetStream() <<"Scale 1 1 -1 \n";

		_rib.GetStream() <<"ConcatTransform [ ";
		for (int i=0; i<16; i++)
		{
			_rib.GetStream() <<M[i]<<" ";
		}
		_rib.GetStream() <<"]\n";
		_rib.GetStream() <<"# now we Set the clipping \n";
		_rib.GetStream() <<"Clipping "<<m_zNear<<" "<<m_zFar<<"\n";
		_rib.GetStream() <<"Projection \"perspective\" \"fov\" ["<<m_fov<<"]\n";
		_rib.GetStream() <<"#End of Camera from GraphicsLib\n";
	}
}
//----------------------------------------------------------------------------------------------------------------------

}; // end namespace ngl

