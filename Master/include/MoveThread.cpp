
#include "MoveThread.h"

MoveThread::MoveThread(vex::motor motor, float distance) : motor(motor)
{
  this->startPos = motor.rotation(vex::deg);
  this->endPos = this->startPos + distance;
  this->dir = (this->startPos < this->endPos) ? vex::directionType::fwd : vex::directionType::rev;
}

MoveThread::~MoveThread() {}

void MoveThread::start()
{
  this->motor.spin(this->dir, 80, vex::pct);
}

// Use movement phases to reduce oscillation.
//  Phase 0 : Quick move, get within 40deg of target
//  Phase 1 : Slower move, get within 2deg of target
//  Phase 2 : Slowest move, get exact on target
void MoveThread::update()
{
  if (this->movePhase == 0)
  {
    if ((this->motor.rotation(vex::deg) > this->endPos - 200 && this->startPos < this->endPos) || 
        (this->motor.rotation(vex::deg) < this->endPos + 200 && this->startPos > this->endPos))
    {
      this->movePhase = 1;

    }
  }

  if (this->movePhase == 1)
  {
    if (this->motor.rotation(vex::deg) > this->endPos + 40)
      this->motor.spin(vex::directionType::rev, 40, vex::pct);

    else if (this->motor.rotation(vex::deg) < this->endPos - 40)
      this->motor.spin(vex::directionType::fwd, 40, vex::pct);

    else
      this->movePhase = 3;
  }

  else if (this->movePhase == 2)
  {
    if (this->motor.rotation(vex::deg) > this->endPos + 2)
      this->motor.spin(vex::directionType::rev, 40, vex::pct);

    else if (this->motor.rotation(vex::deg) < this->endPos - 2)
      this->motor.spin(vex::directionType::fwd, 40, vex::pct);

    else
      this->movePhase = 3;
  }

  else if (this->movePhase == 3)
  {
    if (this->motor.rotation(vex::deg) > this->endPos + 1.2)
    {
      this->motor.spin(vex::directionType::rev, 2, vex::pct);
      this->holdDuration = 0;
    }

    else if (this->motor.rotation(vex::deg) < this->endPos - 1.2)
    {
      this->motor.spin(vex::directionType::fwd, 2, vex::pct);
      this->holdDuration = 0;
    }

    else
    {
      this->motor.spin(vex::directionType::fwd, 0, vex::pct);
      this->holdDuration++;
      if (this->holdDuration > 10)
        this->movePhase = 4;
      wait(10, vex::msec);
    }
  }

  else if (this->movePhase == 4)
  {
    this->complete = true;
    this->motor.spin(vex::directionType::fwd, 0, vex::pct);
  }
}

bool MoveThread::done()
{
  return this->complete;
}