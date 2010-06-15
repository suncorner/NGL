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
#ifndef __NGLASSERT_H__
#define __NGLASSERT_H__



/// \brief re-define the standard assert to work for ngl::
//first check to see if assert is defined and undef it
/// this file is to replace the std C++ Assert functions
/// These are turned on and off by specifying the _DEBUG flag
/// in the make file (-DNGL_DEBUG in the FLAGS line.
/// These are simmilar to the normal assert macros but don't exit
/// the program as our asserts are not usually fatal. Also can use the
/// assert in the TODO list to flag methods which have not yet been
/// implimented.


// now if we are in debug mode use these macros
#if defined(NGL_DEBUG)

#ifdef _MSC_VER
	#include <dbgcrt.h>
	#include <intrin.h>
	#include <string>
	#define NGL_ASSERT(X) \
		 { \
			 std::string str = "Assertion failed :"; \
			 str += #a; \
			 str += "\nFailure occured on line "; \
			 str += __LINE__; \
			 str += " of source file :\n \""; \
			 str += __FILE__; \
			 str += "\""; \
			 OutputDebugStringA(str.c_str()); \
			 __debugbreak(); \
		 }
#else

	// not checked this on linux or macos.
	// The __debugbreak() intrinsic should be supported,
	// it might just be hidden in another header file....
//	#include <intrin.h>
	#include <iostream>
	#define NGL_ASSERT(X) \
		 if(!(X)) \
		 { \
			 std::cerr << "Assertion failed :"<< #X \
			 << "\nFailure occured on line " \
			 << __LINE__ << " of source file :" \
			 << "\n \""<<__FILE__<<"\"" << std::endl; \
		 }
#endif




/*

#ifdef assert
  #undef assert
#endif

#ifdef ASSERT
  #undef ASSERT
#endif
// now if we are in debug mode use these macros
#if defined(NGL_DEBUG)

#define assert(a)             \
   if(!(a))                               \
   {                                   \
   std::cerr << "Assertion failed :"<< #a   \
     <<"\nFailure occured on line "    \
     << __LINE__ << " of source file :" \
     <<"\n  \""<<__FILE__<<"\"\n";     \
   }
#define ASSERT(a,str)        \
  if(!(a))              \
  {                \
   std::cerr << "Assertion failed :"<< #a   \
   << " " << #str             \
     <<"\nFailure occured on line "    \
     << __LINE__ << " of source file :" \
     <<"\n  \""<<__FILE__<<"\"\n";     \
   }

#else
// define release macros
 #define assert ;// these do nothing
 #define ASSERT(a,str) ;
*/
#endif // #if defined(NGL_DEBUG)

#endif // __NGLASSERT_H__









