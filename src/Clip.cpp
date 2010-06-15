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
#include "Clip.h"
#include <stdlib.h>
#include <cstring>
#include <boost/foreach.hpp>
namespace ngl{

//----------------------------------------------------------------------------------------------------------------------

Clip::Clip()
{
	m_nFrames=0;
	m_currFrame=0;
	m_nVerts=0;
	m_obj=NULL;
	m_texture = false;
}

//----------------------------------------------------------------------------------------------------------------------
Clip::~Clip()
{
	// get the size of the clip m_data
	unsigned int size = m_data.size();
	// clean out the individual lists first
	for(unsigned int i=0; i<size; ++i)
	{
		// get an itor to the individual Vector elements for the current list
		// begin and end
		std::vector<ngl::Vector>::iterator begin = m_data[i].begin();
		std::vector<ngl::Vector>::iterator end =m_data[i].end();
		// now free up this m_data
		m_data[i].erase(begin,end);
	}
	// now free the base list
	m_data.erase(m_data.begin(),m_data.end());
	// delete the m_obj
	delete m_obj;
}
// as the m_obj class re-orders the vertices to pack them for the VBO
// we need to do the same for the clip
//----------------------------------------------------------------------------------------------------------------------
void Clip::ReorderVerts()
{
	// grab the re-ordered indices from the m_obj
	std::vector<IndexRef>outIndices=m_obj->GetIndices();
	// resize our m_data to the correct size
	unsigned int size=outIndices.size();
	m_vertOrder.resize(size);
	// now copy the indices from the vbo
	for(unsigned int i=0; i<size; ++i)
	{
		m_vertOrder[i]=outIndices[i].m_v;
	}
}

//----------------------------------------------------------------------------------------------------------------------
Clip::Clip(
           const std::string &_clipName,
           const std::string &_objName
          )
{
	m_obj = new Obj(_objName);
	LoadClip(_clipName);
	m_obj->CreateVBO(GL_DYNAMIC_DRAW);
	ReorderVerts();
}

//----------------------------------------------------------------------------------------------------------------------
Clip::Clip(
           const std::string &_clipName,
           const std::string &_objName,
           const std::string &_texName
          )
{
	m_obj = new Obj(_objName,_texName);
	LoadClip(_clipName);
	m_obj->CreateVBO(GL_DYNAMIC_DRAW);
	ReorderVerts();
}

//----------------------------------------------------------------------------------------------------------------------
Clip::Clip(
           const std::string &_clipName
          )
{
	LoadClip(_clipName);
	m_texture = false;
}
//----------------------------------------------------------------------------------------------------------------------
void Clip::SetObj(
                  ngl::Obj *_obj
                 )
{
	m_obj=_obj;
}

//----------------------------------------------------------------------------------------------------------------------
void Clip::UpdateVerts(
                       const unsigned int Frame
                      )
{
	// map the m_obj's vbo dat
	Real *ptr=m_obj->MapVBOVerts();
	unsigned int step=0;
	unsigned int index;
	unsigned int size=m_vertOrder.size();
	// loop for all the verts and set the new vert value
	for(unsigned int i=0; i<size; ++i)
	{
		// grab the re-ordered index value
		index=m_vertOrder[i];
		// set it in the vbo pointer m_data
		ptr[step]=m_data[index][Frame].m_x;
		ptr[step+1]=m_data[index][Frame].m_y;
		ptr[step+2]=m_data[index][Frame].m_z;
		// skip to the next set of 3 vert values
		step+=3;
	}
	// unmap the vbo as we have finished updating
	m_obj->UnMapVBO();
	m_currFrame=Frame;
}

//----------------------------------------------------------------------------------------------------------------------
void Clip::Draw() const
{
	m_obj->DrawVBO();
}

//----------------------------------------------------------------------------------------------------------------------
void Clip::Draw(
                const unsigned int Frame
               )
{
	// finally draw
	UpdateVerts(Frame);
	m_obj->DrawVBO();
}

//----------------------------------------------------------------------------------------------------------------------
void Clip::SetFrame(
                    const unsigned int frame
                    )
{
	m_currFrame=frame;
}

/// \todo ok this is taken from the original C version should be re-written at some stage using C++ and boost

//----------------------------------------------------------------------------------------------------------------------
void Clip::LoadClip(
                    const std::string &_clipName
                    )
{
	const static char sep[]=" \n\t\r\n";
	// file pointer
	FILE *ip;
	// the line of the file to read m_data
	char line[5000];
	char *token;
	int start=0;
	int tracklength=0;
	int tracks=0;
	Vector p;
	char *name;
	char tmp[100];
	int which=TX;
	int vertIndex;
	// general loop index
	unsigned int i,x;
	// first pass we run throught the list and count the different elements
	// so we can allocate memory for them
	//printf("building clip\n");
	if ((ip = fopen(_clipName.c_str(), "rt")) == NULL)
	{
		std::cerr<<"File not found or unable to read "<<_clipName.c_str()<<std::endl;
		exit(EXIT_FAILURE);
	}
	// read all lines
	// ok lets read the header info and get the m_data we need
	while( fgets(line,5000,ip) !=NULL)
	{
		token=strtok(line," \t\n");
		do
		{
		if(strcmp(token,"start")==0)
		{
			// get rid of =
			strtok(NULL,sep);
			start=atoi(strtok(NULL,sep));
		}
		else if(strcmp(token,"tracklength")==0)
		{
			// get rid of =
			strtok(NULL," \t\n");
			tracklength=atoi(strtok(NULL,sep));
		}
		else if(strcmp(token,"tracks")==0)
		{
			// get rid of =
			strtok(NULL,sep);
			tracks=atoi(strtok(NULL,sep));
		}

		token=strtok(NULL,sep);

		}while (token !=NULL);
	}// end while fgets;

	m_nFrames=(tracklength-start);
	m_nVerts=tracks/3;

	//TOCHECK
	//first allocate base pointer [vertex]
	m_data.resize(m_nVerts);
	//cout <<"Size is now"<<m_data.size()<<endl;
	//now for each of these we need to allocate more space
	for(i=0; i<m_nVerts; ++i)
	{
		m_data[i].resize(m_nFrames);
	}

	// now we rewind the file and load the tx m_data
	rewind(ip);
	// time to re-parse
	// we need to look for name = t[xyz] n
	// followed by m_data = 0 - [tracks]

	while( fgets(line,1024,ip) !=NULL)
	{
		token=strtok(line,sep);
		if(strcmp(token,"name")==0)
		{
			// found a name
			// extract it
			// lets get the m_data token to skip =
			strtok(NULL,sep);
			name=strtok(NULL,sep);
			//printf("found name %s\n",name);
			// so we now need to split things we have a string like
			// tx123 or ty123 or tz123 so we can extract which vert 1st
			// so enum TX=0 TY=1 TZ=2 which we can use later;
			switch (name[1])
			{
				case 'x' : { which=TX; break; }
				case 'y' : { which=TY; break; }
				case 'z' : { which=TZ; break; }
			}
			// now we extract the vert we are using
			x=0;
			// loop the rest of the string
			for(i=2; i<strlen(name); ++i)
			{
				tmp[x++]=name[i];
			}
			// null terminate
			tmp[x]='\n';
			// convert it to an int
			vertIndex=atoi(tmp);
			// now we know where to put the m_data we need to get it from the next line
			// format is m_data = x1 x2 x3 ... xn
			// so first grab the next line
			fgets(line,5000,ip);
			// we can skip the 1st two elements
			strtok(line,sep);
			token=strtok(NULL,sep);
			// now loop for the other m_data
			//printf("1st token %s ",token);
			for(i=0; i<m_nFrames; ++i)
			{
				token=strtok(NULL,sep);
				//printf("next %d %s\n",i,token);
				//now allocate it
				switch (which)
				{
					case TX : { m_data[vertIndex][i].m_x=atof(token); break; }
					case TY : { m_data[vertIndex][i].m_y=atof(token); break; }
					case TZ : { m_data[vertIndex][i].m_z=atof(token); break; }
				} // end switch
			} // end for frames
		}// end if "name = "
	}// end while


	fclose(ip);

} // end func
//----------------------------------------------------------------------------------------------------------------------

}; // end namespace ngl;

