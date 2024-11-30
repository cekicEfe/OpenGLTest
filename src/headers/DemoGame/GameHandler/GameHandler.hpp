#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

namespace testgame
{
class GameHandler
{
private:
  GameHandler ();
  ~GameHandler ();

  static GameHandler *instance;

  GameHandler (GameHandler &other) = delete;
  void operator= (const GameHandler &) = delete;

public:
  static GameHandler *createInstance ();
  void deleteInstance ();
};
}

#endif
