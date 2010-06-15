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
#ifndef __NCCABINMESH_H_
#define __NCCABINMESH_H_

// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"
#include <vector>
#include "Texture.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "Vector.h"
#include "AbstractMesh.h"
#include "BBox.h"
#include "RibExport.h"
#include <cmath>
#include <boost/tokenizer.hpp>

namespace ngl
{



/// \class NCCABinMesh "include/NCCABinMesh.h"
/// \author Jonathan Macey
/// \version 1.0
/// \date 6/05/10 initial development
/// \brief basically this class Loads the contents of the current VBO to file,
/// this is basically the AbstractMesh packed Vert, Texture cord and Normal data
/// Which are stored in contiguous blocks from the Parent Save method.
/// this will then create a VBO which can be mapped and drawn etc.


class NCCABinMesh : public  AbstractMesh
{

public :

  /// default constructor
  NCCABinMesh();
  /// constructor to load an objfile as a parameter
  /// @param[in]  &_fname the name of the obj file to load
  NCCABinMesh(
              const std::string& _fname
             );
  /// \brief constructor to load an objfile as a parameter
  /// @param[in]  &_fname the name of the obj file to load
  /// @param[in]  &_texName the name of the texture file

  NCCABinMesh(
              const std::string& _fname,
              const std::string& _texName
             );


  /// Method to load the file in
  /// @param[in]  _fname the name of the obj file to load
  bool Load(
            const std::string& _fname
           );

  /// method to save the obj
  /// @param[in] _fname the name of the file to save
  void Save(
            const std::string& _fname
           );

protected :


};

}


#endif

