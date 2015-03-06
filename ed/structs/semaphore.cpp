#include "semaphore.h"
#include <thread>
using namespace std;

semaphore_strict::semaphore_strict(bool init)
{
  if (init)
    TurnOn();
}

semaphore_strict::~semaphore_strict()
{
  // Deadlock if semaphore is turned on. Wait.
  Lock();
}

void semaphore_strict::TurnOn()
{
  spinlock.test_and_set();
}

void semaphore_strict::TurnOff()
{
  spinlock.clear();
}

bool semaphore_strict::Move()
{
  return !spinlock.test_and_set();
}

bool semaphore_strict::Status()
{
  auto ret = Move();
  if (ret)
    TurnOff();
  return !ret;
}

auto semaphore_strict::Lock()->lock_guard
{
  while (spinlock.test_and_set())
    std::this_thread::sleep_for(10us);

  return{ *this };
}

void semaphore_strict::lock()
{
  return TurnOn();
}

void semaphore_strict::unlock()
{
  return TurnOff();
}

bool semaphore_strict::try_lock()
{
  return Move();
}


semaphore::semaphore(bool init)
  : semaphore_strict(init)
{

}

semaphore::~semaphore()
{
  Move();
  TurnOff();
}
