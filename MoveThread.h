
#include "vex.h"

#include <vector>

class MoveThread
{
private:
  bool complete = false;

public:
  int holdDuration = 0;
  int movePhase = 0;

  float startPos;
  float endPos;

  vex::directionType dir;
  vex::motor motor;

  MoveThread(vex::motor motor, float distance);
  ~MoveThread();

  void start();
  void update();
  bool done();
};
