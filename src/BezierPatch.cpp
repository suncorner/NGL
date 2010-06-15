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
#include "BezierPatch.h"
#include "VBOPrimitives.h"
namespace ngl{


BezierPatch::BezierPatch()
{
  numU=0;
  numV=0;
  std::cerr << "this not quite working yet"<<std::endl;
}

BezierPatch::~BezierPatch()
{
  u.clear();
  v.clear();

}
void BezierPatch::AddUCurve(const BezierCurve &b)
{
  u.push_back(b);
  ++numU;
}
void BezierPatch::AddVCurve(const BezierCurve &b)
{
  v.push_back(b);
  ++numV;
}
void BezierPatch::DrawCP() const
{
for(unsigned int i=0; i<numU; ++i)
  u[i].DrawCP();
for(unsigned int i=0; i<numV; ++i)
v[i].DrawCP();

}
void BezierPatch::DrawCurve() const
{
  for(unsigned int i=0; i<numU; ++i)
    u[i].Draw();
  for(unsigned int i=0; i<numV; ++i)
    v[i].Draw();

}
void BezierPatch::DrawHull() const
{
  for(unsigned int i=0; i<numU; ++i)
    u[i].DrawHull();
  for(unsigned int i=0; i<numV; ++i)
    v[i].DrawHull();



}
void BezierPatch::Draw()const
{
VBOPrimitives *prim = VBOPrimitives::Instance();
  Vector p;
  for(unsigned int uu=0; uu<numU; ++uu)
    for(unsigned int vv=0; vv<numV; ++vv)
      {
      p=u[uu].GetPointOnCurve(0.5);
//      p+=v[vv].GetPointOnCurve(0.5);
      //p.Vertex();
      glPushMatrix();
        p.Translate();
        //WireCube(1.0);
        prim->DrawVBO("cube");
      glPopMatrix();
    std::cout << p<<std::endl;
    }
}

}; // end namespce ngl

