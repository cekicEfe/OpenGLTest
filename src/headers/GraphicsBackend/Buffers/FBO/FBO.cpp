#include "FBO.h"
#include <CoreBackend/ErrorHandler/ErrorHandler.hpp>

FBO::FBO() {
  glGenFramebuffers(1, &this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}
FBO::~FBO() { this->Delete(); }
void FBO::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}
void FBO::Unbind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}
void FBO::Delete() {
  glDeleteFramebuffers(1, &this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}
