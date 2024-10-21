#ifndef TESTFACADE_HPP
#define TESTFACADE_HPP

#include <CoreClass/CollisionController/CollisionController.h>
#include <CoreClass/EntityFactory/EntityFactory.hpp>
namespace core {

class TestFacade {
private:
  core::OctTreeNode mainTree;
  core::EntityFactory factory;
  core::CollisionController collisionController;

public:
  TestFacade();
  ~TestFacade();
  void initFacade();
  void demoFacade();
  void updateFacade(GLfloat *deltatime);
};

} // namespace core

#endif
