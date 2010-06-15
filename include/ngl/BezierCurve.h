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
#ifndef __BEZIER_CURVE_H__
#define __BEZIER_CURVE_H__
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"



#include "Vector.h"
#include <vector>

namespace ngl
{
///
/// \author Jonathan Macey
/// \version 2.0
/// \date Last Revision 27/09/09 Updated to NCCA Coding standard and V2.0
/// \n Revision History :
///  \n 18/06/08 Initial class written
/// \class BezierCurve  "include/BezierCurve.h"
/// \brief Generic Bezier Curve Class allowing the user to generate basic curves using a number of different
/// constriction methods, such as array of Vectors, array of numbers etc
/// The class can automatically generate knot vectors as well or the user can specify their own
/// \todo update this class to run the CoxDeBoor algo once and then store the points in a dynamic
/// array based on the LOD value passed in. This will speed up the execution for static curves as at
/// present we calculate each time. Also this array can then be used to draw with VertexArrays and we
/// will not need to create the DisplayLists
class BezierCurve
{
public :
	/// \brief default ctor sets initial values for Curve to be used with AddPoint , AddKnot etc
	BezierCurve();
	/// \brief Ctor passing in an Array of CP's and and Array of knots
	///  @param[in] _p an array of Vector objects which are the control
	///  @param[in] _nPoints the size of the Point Array
	///  @param[in] _k and array of knot values
	///  @param[in] _nKnots the size of the knot array
	///
	BezierCurve(
							Vector const *_p,
							const int &_nPoints,
							Real const *_k,
							const int &_nKnots
						 );

	/// \brief ctor passing in an array of points, note the knot vector will be automatically
	/// calculated as an open vector using a call to create knots
	/// @param[in] _p the array of CP values expressed as groups of 3 float x,y,z values
	/// @param[in] _nPoints the size of the array *p (note this is the total size of the array)
	BezierCurve(
							Real const *_p,
							const unsigned int _nPoints
						 );
	/// \brief copy ctor
	BezierCurve(
							const BezierCurve &_c
						 );
	/// \brief destructor
	~BezierCurve();
	/// \brief Draw method to draw the curve Note this will be slow as it calls the CoxDeBoor function to calculate each time
	/// it is much quicker to create a display list and use this.
	/// \todo Modify this to use faster method than display lists
	void Draw() const;
	/*! \brief draw the control points  */
	void DrawCP() const;
	/*! \brief Draw the control hull */
	void DrawHull() const;

	/// \brief get a point on the curve in the range of 0 - 1 based on the control points
	/// @param[in] _value the point to evaluate between 0 and 1
	/// \returns the value of the point at t
	Vector GetPointOnCurve(
												 const Real _value
												) const;

	/// \brief add a control point to the Curve
	/// @param[in] *_p the point to add
	void AddPoint(
								Vector const *_p
								);
	/// \brief add a control point to the Curve
	/// @param[in] &_p the point to add
	void AddPoint(
								const Vector &_p
							 );

	/// \brief add a point to the curve using x,y,z values
	/// @param[in] _x x value of point
	/// @param[in] _y y value of point
	/// @param[in] _z z value of point
	void AddPoint(
								const Real _x,
								const Real _y,
								const Real _z
							 );

	/// \brief add a knot value to the curve
	/// @param[in] _k the value of the knot (note this is added to the end of the curve
	void AddKnot(
								const Real _k
							);
	/// \brief create a knot vector array based as an Open Vector (half 0.0 half 1.0)
	void CreateKnots();


	/// \brief implementation of the CoxDeBoor algorithm for Bezier Curves borrowed from Rob Bateman's example and
	/// modified to make it work with the class. NOTE, this is a recursive function
	/// \returns Real the evaluation of the weight at the current value
	/// @param[in] _u
	/// @param[in] _i
	/// @param[in] _k
	/// @param[in] _knots the array of knots for the curve
	Real CoxDeBoor(
								 const Real _u,
								 const int _i,
								 const int _k,
								 const std::vector <Real> _knots
								) const;
	/// \brief create a display list for faster visualisation
	void CreateDisplayList();
	/// \brief Use the DisplayList to draw
	void DrawDisplayList() const;
	/// \brief set the Level of Detail for Drawing Note this will have no Effect if the CreateDisplayList has
	///been called before
	/// @param[in] _lod the level of detail to use when creating the display list for drawing the higher the number
	/// the finer the drawing
	void inline SetLOD(int _lod){m_lod=_lod;};

protected :

  /// \brief the display list index created from glCreateLists
  GLuint m_listIndex;
  /// \brief The Order of the Curve = Degree +1
  unsigned int m_order;
  /// \brief The level of detail used to calculate how much detail to draw
  unsigned int m_lod;
  /// \brief The ammount of Control Points in the Curve
  unsigned int m_numCP;
  /// \brief The degree of the curve, Calculated from the Number of Control Points
  unsigned int m_degree;
  /// \brief The knot vector always has as many values as the numer of verts (cp) + the degree
  unsigned int m_numKnots;
  /// \brief \brief the contol points for the curve
  std::vector <Vector> m_cp;
  /// \brief \brief the knot vector for the curve
  std::vector <Real> m_knots;


}; // end class BezierCurve
} // end Graphics Lib namespace
#endif // end header file

