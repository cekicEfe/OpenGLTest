#include "FBO.h"

FBO::FBO ()
{
  glGenFramebuffers (1, &this->id);
}
FBO::~FBO ()
{
  this->Delete ();
}
void
FBO::Bind ()
{
  glBindFramebuffer (GL_FRAMEBUFFER, this->id);
}
void
FBO::Unbind ()
{
  glBindFramebuffer (GL_FRAMEBUFFER, 0);
}
void
FBO::Delete ()
{
  glDeleteFramebuffers (1, &this->id);
}
