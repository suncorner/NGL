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
#include "PathCamera.h"
#include <fstream>
#include <cstdlib>

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
PathCamera::PathCamera(
                       const Vector &_up,
                       const BezierCurve &_eyePath,
                       const BezierCurve &_lookPath,
                       Real _step,
                       CAMERAPROJECTION _proj
                      )
{
	m_dir=CAMFWD;
	m_eyeCurvePoint=0.0;
	m_lookCurvePoint=0.0;
	m_eyePath=_eyePath;
	m_lookPath=_lookPath;
	m_eyePath.CreateDisplayList();
	m_lookPath.CreateDisplayList();
	m_step=_step;
	m_up=_up;
  m_projection=_proj;
}

//----------------------------------------------------------------------------------------------------------------------
PathCamera::PathCamera(
                       const Vector &_up,
                       Vector const *_eyePoints,
                       int _nEyePoints,
                       Vector const  *_lookPoints,
                       int _nLookPoints,
                       Real _step,
                       CAMERAPROJECTION _proj)
{
	m_dir=CAMFWD;
	m_eyeCurvePoint=0.0;
	m_lookCurvePoint=0.0;
	for(int i=0; i<_nEyePoints; ++i)
	{
		m_eyePath.AddPoint(_eyePoints[i]);
	}
	m_eyePath.CreateKnots();
	m_eyePath.CreateDisplayList();

	for(int i=0; i<_nLookPoints; ++i)
	{
		m_lookPath.AddPoint(_lookPoints[i]);
	}
	m_lookPath.CreateKnots();
	m_lookPath.CreateDisplayList();
  m_projection=_proj;
	m_step=_step;
	m_up=_up;
}



//----------------------------------------------------------------------------------------------------------------------
PathCamera::PathCamera(
                       const Vector &_up,
                       const std::string &_fName,
                       Real _step,
                       CAMERAPROJECTION _proj
                      )
{
	m_dir=CAMFWD;

	std::ifstream FileIn;
	FileIn.open(_fName.c_str(),std::ios::in);

	if (!FileIn.is_open())
	{
		std::cout <<"File : "<<_fName<<" Not found Exiting "<<std::endl;
		exit(EXIT_FAILURE);
	}
	int nEye,nLook;
	FileIn >> nEye>>nLook;

	Vector *eyePoints= new Vector[nEye];
	Vector *lookPoints= new Vector[nLook];

	for(int i=0; i<nEye; ++i)
	{
		FileIn >> eyePoints[i];
	}
	for(int i=0; i<nLook; ++i)
	{
		FileIn>> lookPoints[i];
	}
	FileIn.close();

	m_eyeCurvePoint=0.0;
	m_lookCurvePoint=0.0;
	for(int i=0; i<nEye; ++i)
	{
		m_eyePath.AddPoint(eyePoints[i]);
	}
	m_eyePath.CreateKnots();
	m_eyePath.CreateDisplayList();

	for(int i=0; i<nLook; ++i)
	{
		m_lookPath.AddPoint(lookPoints[i]);
	}
	m_lookPath.CreateKnots();
	m_lookPath.CreateDisplayList();

	m_step=_step;
	m_up=_up;
  m_projection=_proj;

}

//----------------------------------------------------------------------------------------------------------------------
void PathCamera::LoadPath(
                          const std::string &_fName
                         )
{
	m_dir=CAMFWD;
	m_eyeCurvePoint=0.0;
	m_lookCurvePoint=0.0;

	std::ifstream FileIn;
	FileIn.open(_fName.c_str(),std::ios::in);

	if (!FileIn.is_open())
	{
		std::cout <<"File : "<<_fName<<" Not found Exiting "<<std::endl;
		exit(EXIT_FAILURE);
	}
	/// \todo get this working with loading from a Vector
	/*
	Vector eyePoint;
	Vector lookPoint;

	for(int i=0; i<4; i++)
		{
			FileIn >> eyePoint;
			EyePath->SetCP(i,eyePoint);
			}
	for(int i=0; i<4; i++)
		{
			FileIn>> lookPoint;
			LookPath->SetCP(i,lookPoint);
			}
	*/
	FileIn.close();


}


//----------------------------------------------------------------------------------------------------------------------
PathCamera::~PathCamera()
{

}

//----------------------------------------------------------------------------------------------------------------------
void PathCamera::Update()
{
	Vector ept=m_eyePath.GetPointOnCurve(m_eyeCurvePoint);
	Vector lpt=m_lookPath.GetPointOnCurve(m_lookCurvePoint);
	std::cout <<ept<<lpt<<std::endl;
	m_eye=ept;
	m_look=lpt;
	m_n=m_eye-m_look;
	m_u.Set(m_up.Cross(m_n));
	m_v.Set(m_n.Cross(m_u));
	m_u.Normalize(); m_v.Normalize(); m_n.Normalize();

	SetModelViewMatrix();

	m_eyeCurvePoint+=m_step;
	if(m_eyeCurvePoint>1.0)
	{
		m_eyeCurvePoint=0.0;
	}
	m_lookCurvePoint+=m_step;
	if(m_lookCurvePoint>1.0)
	{
		m_lookCurvePoint=0.0;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void PathCamera::UpdateLooped()
{
	Vector ept=m_eyePath.GetPointOnCurve(m_eyeCurvePoint);
	Vector lpt=m_lookPath.GetPointOnCurve(m_lookCurvePoint);

	m_eye=ept;
	m_look=lpt;
	m_n=m_eye-m_look;
	m_u=m_up.Cross(m_n);
	m_v=m_n.Cross(m_u);
	//u.Set(UP.Cross(n));
	//v.Set(n.Cross(u));
	m_u.Normalize(); m_v.Normalize(); m_n.Normalize();

	SetModelViewMatrix();
	if(m_dir==CAMFWD)
	{
		m_eyeCurvePoint+=m_step;
		if(m_eyeCurvePoint>=1.0)
		{
			m_dir=CAMBWD;
		}

		m_lookCurvePoint+=m_step;
		if(m_lookCurvePoint>=1.0)
		{
			m_dir=CAMBWD;
		}
	} // end if fwd

	else
	{
		m_eyeCurvePoint-=m_step;
		if(m_eyeCurvePoint<=m_step)
		{
			m_dir=CAMFWD;
		}
		m_lookCurvePoint-=m_step;
		if(m_lookCurvePoint<=m_step)
		{
			m_dir=CAMFWD;
		}
	}// end else

}

//----------------------------------------------------------------------------------------------------------------------
void PathCamera::DrawPaths()const
{

	m_eyePath.DrawDisplayList();
	m_lookPath.DrawDisplayList();
	m_eyePath.DrawHull();
	m_eyePath.DrawCP();
	m_lookPath.DrawHull();
	m_lookPath.DrawCP();
}

void PathCamera::CreateCurvesForDrawing(
														 					  int _lod
																			 )
{
	// now we set the level of detail for the curve
	m_eyePath.SetLOD(_lod);
	m_lookPath.SetLOD(_lod);
	// and create display Lists to make drawing quicker
	m_eyePath.CreateDisplayList();
	m_lookPath.CreateDisplayList();
}



}; // end namespace ngll
