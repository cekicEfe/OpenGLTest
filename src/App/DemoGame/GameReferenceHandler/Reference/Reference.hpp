#ifndef REFERENCE_HPP
#define REFERENCE_HPP

#include "DemoGame/GameReferenceHandler/RefPreDec.hpp"
#include "DemoGame/GameReferenceHandler/Referee/Referee.hpp"

namespace testgame
{

template <class T> class Reference
{
private:
  Referee<T> *referee;

public:
  Reference (Referee<T> *referee);
  ~Reference ();
};

}

#endif
