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
#include "NGLInit.h"
#ifdef LINUX
  #include <cstdlib>
#endif
namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------

void NGLInit::InitVBOandImageLib()
{
  m_prim = VBOPrimitives::Instance();
}

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
void NGLInit::InitGlew()
{
	// we only need glew on linux mac ok (should add a windows ref as well)
  #if defined(LINUX) || defined(WIN32)
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			std::cerr<< "Error: "<<glewGetErrorString(err)<<std::endl;
			exit(EXIT_FAILURE);
		}
		std::cerr<<"Status: Using GLEW "<<glewGetString(GLEW_VERSION)<<std::endl;
	}
	#endif
}

//----------------------------------------------------------------------------------------------------------------------
NGLInit::~NGLInit()
{
	// remove the VBO's from GPU Memory
	delete m_prim;
}


}; // end of ngl namespace




