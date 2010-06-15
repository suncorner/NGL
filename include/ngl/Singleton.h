/*
  Copyright (C) 2009 Vincent Bonnet

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
#ifndef __SINGLETON_H__
#define __SINGLETON_H__
// must include types.h first for ngl::Real and GLEW if required
#include "Types.h"

namespace ngl
{
/// \class Singleton "include/ngl/Singleton.h"
/// \author Vincent Bonnet
/// \version 1.0
/// \date 14/03/10 Last Revision 14/03/10
/// \brief Singleton template
/// added to NGL framework 20/04/10 by jmacey

template <class T>

class Singleton
{
public:

  /// \brief Get the instance
  /// \returns the unique instance
  static T* Instance();

protected:

  /// \brief Constructor
  Singleton();

  /// \brief Destructor
  virtual ~Singleton();

  /// unique instance of the singleton
  static T* m_instance;
};


template<class T> T*  Singleton<T>::m_instance = 0;


// Constructor -------------------------------------------------------------------------------------------------------------
template<class T> Singleton<T>::Singleton()
{}

// Destructor ---------------------------------------------------------------------------------------------------------------
template<class T> Singleton<T>::~Singleton()
{
    if (m_instance)
    {
        delete m_instance;
    }
}
// Get instance --------------------------------------------------------------------------------------------------------------
template<class T> T* Singleton<T>::Instance()
{
    if (m_instance == 0)
    {
      m_instance = new T();
    }
    return static_cast<T*>(m_instance);
}



} // end ngl namespace

#endif // __SINGLETON_H__

