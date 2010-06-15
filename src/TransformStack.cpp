#include <Transformation.h>

#include "TransformStack.h"
#include "NGLassert.h"

namespace ngl
{

//----------------------------------------------------------------------------------------------------------------------
TransformStack::TransformStack()
{
  
  m_current.Reset();
  m_global.Reset();
  m_stack.resize(MAXNGLTRANSFORMSTACKSIZE,m_current);
  m_index=0;
}

//----------------------------------------------------------------------------------------------------------------------
TransformStack::TransformStack(
                                const TransformStack& _m
                              )
{
  #warning "this has not yet been tested fully"
  m_current=_m.m_current;
  m_global=_m.m_global;
  m_index=_m.m_index;
  m_stack.resize(MAXNGLTRANSFORMSTACKSIZE,m_current);
  int stackSize=_m.m_stack.size();
  for(int i=0; i<stackSize; ++i)
  {
    m_stack[i]=_m.m_stack[i];
  }
}

Transformation TransformStack::GetCurrAndGlobal()
{
  return m_global*m_current;
}

//----------------------------------------------------------------------------------------------------------------------
void TransformStack::PushTransform()
{
  m_stack[m_index++]=m_current;
  m_current.Reset();
  //
}

//----------------------------------------------------------------------------------------------------------------------
void TransformStack::PushTransformAndCopy()
{
  m_stack[m_index++]=m_current;
}

//----------------------------------------------------------------------------------------------------------------------
void TransformStack::PopTransform()
{
  m_current=m_stack[--m_index];
}

std::ostream& operator<<(std::ostream& _output,  TransformStack& _m)
{
  return _output<<_m.m_current.GetMatrix()<<"\n"<<
            _m.m_current.GetTransposeMatrix()<<"\n";
}

void TransformStack::LoadMatrixToShader(
                                        std::string _shader,
                                        std::string _param,
                                        ACTIVEMATRIX _which
                                       )
{
  m_current.LoadMatrixToShader(_shader,_param,_which);
}

void TransformStack::LoadGlobalAndCurrentMatrixToShader(
                                                        std::string _shader,
                                                        std::string _param,
                                                        ACTIVEMATRIX _which
                                                       )
{
  m_current.LoadGlobalAndCurrentMatrixToShader(_shader,_param,m_global,_which);
}


}; // end of namespace ngl
