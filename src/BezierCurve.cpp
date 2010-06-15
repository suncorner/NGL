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
#include "BezierCurve.h"
namespace ngl{
//----------------------------------------------------------------------------------------------------------------------
BezierCurve::BezierCurve()
{
	m_numCP=0;
	m_degree=0;
	m_order=m_degree+1;
	m_numKnots=m_numCP+m_degree;
	m_lod=20;
}
//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::CreateKnots()
{
	for(unsigned int i=0; i<m_numKnots; ++i)
	{
		m_knots.push_back( (i<(m_numKnots/2))  ? 0.0f : 1.0f);
	}
}

//----------------------------------------------------------------------------------------------------------------------
BezierCurve::BezierCurve(
                         const BezierCurve &_c
                        )
{
	m_order=_c.m_order;
	m_lod=_c.m_lod;
	m_numCP=_c.m_numCP;
	m_degree=_c.m_degree;
	m_numKnots=_c.m_numKnots;
	m_cp=_c.m_cp;
	m_knots=_c.m_knots;
}

//----------------------------------------------------------------------------------------------------------------------
BezierCurve::BezierCurve(
                         Real const *_p,
                         const unsigned int _nPoints
                        )
{
	for(unsigned int i=0; i<_nPoints; i+=3)
	{
		m_cp.push_back(Vector(_p[i],_p[i+1],_p[i+2]));
	}
	m_numCP=_nPoints/3;
	m_degree=_nPoints/3;
	m_order=m_degree+1;
	m_numKnots=m_numCP+m_order;
	m_lod=20;
	CreateKnots();
}

//----------------------------------------------------------------------------------------------------------------------
BezierCurve::BezierCurve(
                         Vector const *_p,
                         const int &_nPoints,
                         Real const *_k,
                         const int &_nKnots
                        )
{
	m_numCP=_nPoints;
	m_degree=_nPoints;
	m_order=m_degree+1;
  m_numKnots=_nKnots; //m_numCP+m_order;
	m_lod=20;
  for(unsigned int i=0; i<m_numCP; ++i)
	{
		m_cp.push_back(Vector(_p[i]));
	}
  for( int i=0; i<_nKnots; ++i)
	{
		m_knots.push_back(_k[i]);
	}
}

//----------------------------------------------------------------------------------------------------------------------
BezierCurve::~BezierCurve()
{
	m_cp.clear();
	m_knots.clear();
}

//----------------------------------------------------------------------------------------------------------------------
Real BezierCurve::CoxDeBoor(
                            const Real _u,
                            const int _i,
                            const int _k,
                            const std::vector <Real> _knots
                           ) const
{
	if(_k==1)
	{
		if( _knots[_i] <= _u && _u <= _knots[_i+1] )
		{
			return 1.0f;
		}
		return 0.0f;
	}
	Real Den1 = _knots[_i+_k-1] - _knots[_i];
	Real Den2 = _knots[_i+_k] - _knots[_i+1];
	Real Eq1=0,Eq2=0;
	if(Den1>0)
	{
		Eq1 = ((_u-_knots[_i]) / Den1) * CoxDeBoor(_u,_i,_k-1,_knots);
	}
	if(Den2>0)
	{
		Eq2 = (_knots[_i+_k]-_u) / Den2 * CoxDeBoor(_u,_i+1,_k-1,_knots);
	}
	return Eq1+Eq2;
}


//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::DrawCP()const
{
	glBegin(GL_POINTS);
		for(unsigned int i=0;i!=m_numCP;++i)
		{
			m_cp[i].Vertex();
		}
	glEnd();
}

//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::DrawHull()const
{
	glBegin(GL_LINE_STRIP);
		for(unsigned int i=0;i!=m_numCP;++i)
		{
			m_cp[i].Vertex();
		}
	glEnd();
}

//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::Draw() const
{
	Vector p;
	glBegin(GL_LINE_STRIP);
		for(unsigned int i=0;i!=m_lod;++i)
		{
			Real t  = m_knots[m_numKnots-1] * i / (Real)(m_lod-1);

			if(i==m_lod-1)
			{
				t-=0.001f;
			}
			p=GetPointOnCurve(t);
			p.Vertex();
		}
	glEnd();
}

//----------------------------------------------------------------------------------------------------------------------
Vector BezierCurve::GetPointOnCurve(
                                    const Real _value
                                   ) const
{
	Vector p;

	// sum the effect of all CV's on the curve at this point to
	// get the evaluated curve point
	//
	for(unsigned int i=0;i!=m_numCP;++i)
	{
		// calculate the effect of this point on the curve
		Real Val = CoxDeBoor(_value,i,m_degree /*was m_order */,m_knots);

		if(Val>0.001f)
		{
			// sum effect of CV on this part of the curve
			p+=Val*m_cp[i];
		}
	}

	return p;
}


//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::AddPoint(
                           Vector const *_p
                          )
{
	m_cp.push_back(*_p);
	++m_numCP;
	++m_degree;
	m_order=m_degree+1;
	m_numKnots=m_numCP+m_order;
	#ifdef DEBUG
		std::cout <<"Added "<<m_numCP<<" m_degree "<<m_degree<<" m_numKnots"<<m_numKnots<<" m_order "<<m_order<<std::endl;
	#endif
}

//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::AddPoint(
                           const Vector &_p
                          )
{
	m_cp.push_back(_p);
	++m_numCP;
	++m_degree;
	m_order=m_degree+1;
	m_numKnots=m_numCP+m_order;
	#ifdef DEBUG
		std::cout <<"Added "<<m_numCP<<" m_degree "<<m_degree<<" m_numKnots"<<m_numKnots<<" m_order "<<m_order<<std::endl;
	#endif
}

//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::AddPoint(
                           const Real _x,
                           const Real _y,
                           const Real _z
                          )
{
	m_cp.push_back(Vector(_x,_y,_z));
	++m_numCP;
	++m_degree;
	m_order=m_degree+1;

	m_numKnots=m_numCP+m_degree;
	#ifdef DEBUG
		std::cout <<"Added "<<m_numCP<<" m_degree "<<m_degree<<" m_numKnots"<<m_numKnots<<" m_order "<<m_order<<std::endl;
	#endif
}
//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::AddKnot(
                          const Real _k
                         )
{
	m_knots.push_back(_k);
	m_numKnots=m_numCP+m_order;
}

//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::DrawDisplayList() const
{
/// \todo	#warning modify this to use faster method
	// call the list
	glCallList(m_listIndex);
}


//----------------------------------------------------------------------------------------------------------------------
void BezierCurve::CreateDisplayList()
{
/// \todo	#warning modify this to use faster method
	// get a free display list
	GLuint range=glGenLists(1);
	m_listIndex=glGenLists(range);
	// create a new list in compile mode so we only create it and not draw it
	glNewList(m_listIndex,GL_COMPILE);
	// just use the standard draw method as this calls the correct commands
	glPushMatrix();
		Draw();
	glPopMatrix();
	glEndList();
	// end the list
}
//----------------------------------------------------------------------------------------------------------------------

}; // end ngl namespace


