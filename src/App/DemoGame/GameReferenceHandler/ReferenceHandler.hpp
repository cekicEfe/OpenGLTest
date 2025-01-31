#ifndef REFERENCEHANDLER_HPP
#define REFERENCEHANDLER_HPP

#include <vector>
namespace testgame
{
template <class T> class Referee;
template <class T> class Reference;

template <class T> class Reference
{
private:
  Referee<T> *referee;

public:
  Reference (Referee<T> *referee);
  ~Reference ();
};

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
