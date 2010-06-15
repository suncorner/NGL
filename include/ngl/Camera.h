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
#ifndef __CAMERA_H__
#define __CAMERA_H__

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"

///  \author Jonathan Macey
///  \version 4.0
///  \date Last Revision 28/09/09 Updated to NCCA Coding standard \n
/// Revision History : \n
/// 27/08/08 Added experimental projection modes
///   \todo Finish off the different projections modes at present persp and ortho work


#include "Vector.h"
#include "Matrix.h"
#include <cmath>
#include "RibExport.h"

namespace ngl
{
/// \enum CAMERAPROJECTION used to specify which camera projection to use
enum CAMERAPROJECTION{ORTHOGRAPHIC,PERSPECTIVE,TWOPOINT,THREEPOINT};
/// \class Camera
/// \brief simple camera class to allow movement in an opengl scene.
///  a lot of this stuff is from the HILL book Computer Graphics with OpenGL 2nd Ed Prentice Hall
///  a very good book

class Camera
{

public :

  /// \brief default constructor
  Camera();

  /// \brief constructor setting the  camera using eye look and up
  /// @param[in] _eye the eye position of the Camera
  /// @param[in] _look where the camera is  looking
  /// @param[in] _up the notion of upwardness for the  camers (get re-calculated from the other vectors)
  /// @param[in] _proj what projection mode to use based on CAMERAPROJECTION enum

  Camera(
         const Vector& _eye,
         const Vector& _look,
         const Vector& _up,
         const CAMERAPROJECTION _proj
        );


  /// \brief function to set the extents of the orthographic projection volume
  /// @param[in] _l left extent
  /// @param[in] _r right extent
  /// @param[in] _t top extent
  /// @param[in] _b bottom extent
  /// @param[in] _n near extent
  /// @param[in] _f far extent

  void SetOrthoParams(
                      const Real _l,
                      const Real _r,
                      const Real _t,
                      const Real _b,
                      const Real _n,
                      const Real _f
                    );

  /// \brief roll the cameara around the  Z axis
  /// @param[in] _angle the angle to roll in degrees

  void Roll(
            const Real _angle
            );
  /// \brief roll the cameara around the  x axis
  /// @param[in] _angle the angle to roll in degrees

  void Pitch(
              const Real _angle
            );
  /// \brief roll the cameara around the  y axis
  /// @param[in] _angle the angle to roll in degrees

  void Yaw(
            const Real _angle
          );

  /// \brief slide the camera around  the U V and N axis
  /// @param[in] _du ammount to slide in the U
  /// @param[in] _dv ammount to slide in the V
  /// @param[in] _dn ammount to slide in the N
  void Slide(
             const Real _du,
             const Real _dv,
             const Real _dn
            );

  /// \brief set the Camera position using eye look and up vectors
  /// @param[in] _eye the new  eye position
  /// @param[in] _look the new look position
  /// @param[in] _up the notional up direction of the Camera
  void Set(
           const Vector &_eye,
           const Vector &_look,
           const Vector &_up
          );



  /// \brief set the shape of the Camera
  /// @param[in] _viewAngle the view angle  of the camera from the eye
  /// @param[in] _aspect the aspect ratio of the camera can be  calculated from Width/height
  /// @param[in] _near the near clipping plane
  /// @param[in] _far the far clipping plane
  /// @param[in] _proj the type of projection to use
  void SetShape(
                Real _viewAngle,
                const Real _aspect,
                Real _near,
                Real _far,
                const CAMERAPROJECTION _proj
                );

  /// \brief re-set the aspect ratio of the camera
  /// @param[in] _asp the new aspect ratio
  void SetAspect(
                  const Real _asp
                );

  /// \brief sets some nice default camera values
  void SetDefaultCamera();

  /// \brief move the camera in world space (i.e. add a translation to each of the axis
  /// @param[in] _dx the translation in the x
  /// @param[in] _dy the translation in the y
  /// @param[in] _dz the translation in the z
  void Move(
            const Real _dx,
            const Real _dy,
            const Real _dz
           );

  /// \brief move both the eye and the look at the same time
  /// @param[in] _dx ammount to move in the x
  /// @param[in] _dy ammount to move in the y
  /// @param[in] _dz ammount to move in the z
  void MoveBoth(
                const Real _dx,
                const Real _dy,
                const Real _dz
               );

  /// \brief move the eye position
  /// @param[in] _dx ammount to move the eye in the x
  /// @param[in] _dy ammount to move the eye in the y
  /// @param[in] _dz ammount to move the eye in the z
  void MoveEye(
               const Real _dx,
               const Real _dy,
               const Real _dz
              );

  /// \brief move the look position
  /// @param[in] _dx ammount to move the look in the x
  /// @param[in] _dy ammount to move the look in the y
  /// @param[in] _dz ammount to move the look in the z
  void MoveLook(
                const Real _dx,
                const Real _dy,
                const Real _dz
               );

  /// \brief set the viewangle for the Camera
  /// @param[in] _angle new angle
  void SetViewAngle(
                    const Real _angle
                   );

  /// \brief Use is called to make this the current camera and set the MODELVIEW and PROJECTION matrices in OpenGL
  void Use();

  /// \brief used to do a Yaw based on Euler rotation with normalised values
  /// @param[in] _angle the angle to rotate in degrees
  void NormalisedYaw(
                     const Real _angle
                    );

  /// \brief used to do a Pitch based on Euler rotation with normalised values
  /// @param[in] _angle the angle to rotate in degrees
  void NormalisedPitch(
                        const Real _angle
                      );

  /// \brief used to do a Roll based on Euler rotation with normalised values
  /// @param[in] _angle the angle to rotate in degrees
  void NormalisedRoll(
                      const Real _angle
                      );

  /// \brief write out the Camera so it may be used in Renderman, this writes a transform command in rib format  so the
  /// OpenGL camera mirrors that of the renderman one
  /// @param[in]  _rib the pointer to the RibExport class currently being used
  /// \todo make this and the rest of the Rib class work as a friend class rather than as present

  void WriteRib(
                RibExport &_rib
                )const ;

  /// \brief Set the projection matrix to a 2 point projection experimental at present
  /// @param[in] _p1 the first point for the projection
  /// @param[in] _p2 the 2nd point for the projection
  void Set2PointProjPoints(
                           const Vector &_p1,
                           const Vector &_p2
                          );

  /// \brief Set the projection matrix to a 3 point projection experimental at present
  /// @param[in] _p1 the first point for the projection
  /// @param[in] _p2 the 2nd point for the projection
  /// @param[in] _p3 the 3rd point for the projection
  void Set3PointProjPoints(
                           const Vector &_p1,
                           const Vector &_p2,
                           const Vector &_p3
                          );
  /// \brief << extraction operator to prints out the colour in the format [r,g,b,a]
  /// @param[in] _output the outstream class pointer
  /// @param[in] _c the camera to print out
  friend std::ostream& operator<<(std::ostream& _output, const Camera& _c);
  inline Matrix & GetModelView(){return m_modelView;}
  inline Matrix & GetProjection(){return m_projection;}
protected :

  /// \brief an array of points to hold the different points for the projection calculations work in progress
  ngl::Vector m_projPoints[3];
  /// \brief function used to set the perspective projection matrix values
  void SetPerspProjection();
  /// \brief function used to set the ortho projection matrix values
  void SetOrthoProjection();
  /// \brief function used to set the 2 point perspective projection matrix values
  void SetTwoPointProjection();
  /// \brief function used to set the 3 point perspective projection matrix values
  void SetThreePointProjection();

  /// \brief internal function to calculate the  new rotation vectors for the camera after a roll, pitch or yaw
  /// @param[in,out] io_a the first vector to be rotated
  /// @param[in,out] io_b the second vector to be rotated
  /// @param[in] _angle the angle to rotate

  void RotAxes(
               Vector& io_a,
               Vector& io_b,
               const Real _angle
              );


protected :

  /// \brief vector for the  Camera local cord frame
  Vector m_u;
  /// \brief vector for the  Camera local cord frame
  Vector m_v;
  /// \brief vector for the  Camera local cord frame
  Vector m_n;
  /// \brief  the position of the Camera  used to calculate the local cord frame
  Vector m_eye;
  /// \brief  where the camera is looking to,  used with Eye to calculate the Vector m_n
  Vector m_look;
  /// \brief  gives a general indication of which way up the camera is
  Vector m_up;
  /// \brief  the width of the display image used for some perspective projection calculations
  Real m_width;
  /// \brief the height of the display image used for some perspective projection calculations
  Real m_height;
  /// \brief used to store the current camera aspect ratio (can be derived from Width / Height
  Real m_aspect;
  /// \brief the near clipping plane of the camera view volume
  Real m_zNear;
  /// \brief the far clipping plane of the camera view volume
  Real m_zFar;
  /// \brief the feild of view of the camera view volume, measured from the eye
  Real m_fov;
  /// \brief l r t b nr fr used to specify the left right top bottom near far planes for an orthographic camera projection
  Real m_l,m_r,m_t,m_b,m_nr,m_fr;
  ///  \brief a Matrix to hold  the combined modelling and viewing matrix to load into OpenGL
  Matrix m_modelView;
  /// \brief Projection a Matrix to hold the perspective transfomatio matrix for the camera, this can be set to be
  /// either PERSPECTIVE (OpenGL standard gluPerspective style), ORTHOGRAPHIC for 2d ortho projection
  /// TWOPOINT for two point perspective or THREEPOINT for three point perspective
  Matrix m_projection;
  /// \brief  used to store the current projection mode for the camera
  CAMERAPROJECTION m_projectionMode;
  /// \brief method to set the modelview matrix values for the current  camera, this method load the matrix Modelview into OpenGL
  void SetModelViewMatrix();
  /// \brief change the current camera's projection mode based on the enum CAMERAPROJECTION
  /// @param[in] _proj the mode to change to

  void ChangeProjectionMode(
                            const CAMERAPROJECTION _proj
                           );

  /// \brief set the projection matrix
  void SetProjectionMatrix();

};
}
#endif // end of  class


