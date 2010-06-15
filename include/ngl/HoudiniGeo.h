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
#ifndef __HOUDINI_GEO_H__
#define __HOUDINI_GEO_H__
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"

#include "AbstractMesh.h"
#include <map>
namespace ngl
{

/// class HouDictionaryEntry "include/HoudiniGeo"
/// \author Jon Macey
/// \version 1.0
/// \fata Last Revision 12/10/09 First version
/// \brief a class to hold the dictionary entries for the houdini geo header
/// this will be put into a map for easy lookup of the data when parsing
class HouDictionaryEntry
{
  public :
      /// the name of the entry will be used for the lookup
      std::string m_name;
      /// this determines how many elements the entry has i.e. 3 = x,y,z etc
      int m_size;
      /// the data type as a string float / string int etc used to determine which lexical cast
      /// to used
      std::string m_type;
      /// the relative index into the data stream for this data
      int m_relIndex;
      HouDictionaryEntry(
                         std::string _name,
                         int _size,
                         std::string _type,
                         int _relIndex
                        ):
                          m_name(_name),
                          m_size(_size),
                          m_type(_type),
                          m_relIndex(_relIndex){;}
      inline void Print(){
        std::cerr<<m_name<<" "<<m_size<<" "<<m_type<<" "<<m_relIndex<<std::endl;
      }



 };


///  \class HoudiniGeo "include/HoudiniGeo.h"
///  \author Jon Macey
///  \version 1.0
///  \date Last Revision 12/10/09 First version

/// \brief a class to load in the ASCII houdini .geo files for poly data
/// the spec for the format can be found here
/// http://www.sidefx.com/docs/houdini9.5/io/formats/geo

class HoudiniGeo : public AbstractMesh
{
public:
    /// \brief ctor passing in the file name to load
    /// @param[in] _fName the name of the file to load
    HoudiniGeo(
               const std::string& _fName
              );

    /// \brief ctor passing in the file name to load and a texture
    /// @param[in] _fName the name of the file to load
    /// @param[in] _texName the name of the texture file to load
    HoudiniGeo(
               const std::string& _fName,
               const std::string& _texName
              );
    void DrawDebugPoints(void);

protected :
     /// the number of point attributes
    int m_nPointAttrib;
    /// the number of vertex attributes
    int m_nVertAttrib;
    /// normal token index used when parsing the geo file
    int m_normalTokenIndex;
    /// uv token index used when paring the geo file
    int m_uvTokenIndex;
    /// map used when parsing the Attribute Data
    std::map <std::string,HouDictionaryEntry *> m_dictionary;


    /// \brief method to check the header and see if we have a valid geo file it also
    /// reads in the ammount of Points ammount of prims and the basic attribute counts
    /// @param[in] the open file stream from the Load method
    /// \returns true if a valid geo file
    bool LoadHeader(
                    std::ifstream& _stream
                   );
    /// \brief method to load the attribute dictionary from the geo file.
    /// At present we are only worried about Normals and UV but this class will
    /// be written to be extendable.
    /// The main problem is the dictionary can be in any order so we need to find
    /// the index into our data for each ones and store it.
    /// the dictionary format is as follows
    /// Name Size Type Default
    /// valid dictionary values are.
    /// N a normal
    /// uv a uv
    void LoadPointAttribDictionary(
                                    std::ifstream& _stream
                                  );


    /// \brief the main loader for the geo we will have other methods called from this
    /// @param _fName the name of the file to load
    bool Load(
              const std::string &_fName
             );
    /// \brief a method to load the points from the geo file
    /// @param _fName the name of the file to load

    void LoadPoints(
                    std::ifstream& _stream
                   );

};

}// end namespace
#endif // HOUDINIGEO_H
