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
#ifndef __BEZIERPATCH_H__
#define __BEZIERPATCH_H__

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include "Vector.h"
#include "BezierCurve.h"
#include <vector>


namespace ngl{
  /*!
  \author Jonathan Macey
  \version 1.0
  \date Last Revision 18/06/08 \n
  \class BezierPatch  "include/BezierPatch.h"
  \brief A Bezier Patch class based on the use of the BezierCurve class this is not finished!!
  \todo Finish this class off at some stage!
  
`*/
  class BezierPatch
  {
  public :
    /*! \brief default ctor sets initial values for Curve to be used with AddPoint , AddKnot etc */
    BezierPatch();
    void AddUCurve(const BezierCurve &b);
    void AddVCurve(const BezierCurve &b);
    void DrawCP() const;
    void DrawCurve() const;
    void DrawHull() const;
    void Draw() const;
    ~BezierPatch();
  private :
    std::vector <BezierCurve> u;
    std::vector <BezierCurve> v;
    unsigned int numU;
    unsigned int numV;



  }; // end of class
} // end of namespace


#endif // end of include guard

