#ifndef REFEREE_HPP
#define REFEREE_HPP

#include <vector>

namespace testgame
{

template <class T> class Referee : public T
{
private:
  std::vector<Reference<T> > references;

public:
  Referee ();
  template <class... Args> Referee (Args &&...args);
  ~Referee ();
  Reference<T> CreateReference ();
};

}

#endif
