#include "ReferenceHandler.hpp"

template <class T> testgame::Referee<T>::Referee () : T ()
{
}

template <class T>
template <typename... Args>
testgame::Referee<T>::Referee (Args &&...args) : T (args...)
{
}

template <class T> testgame::Referee<T>::~Referee ()
{
  for (size_t i = 0; i < this->references.size (); i++)
    {
      this->references.at (i);
    }
}
