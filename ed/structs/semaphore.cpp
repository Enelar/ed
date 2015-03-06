#include "semaphore.h"
#include <thread>
using namespace std;

semaphore_strict::semaphore_strict(bool init)
{
  // Initial state of spinlock unspecified. And we cant use ATOMIC_FLAG_INIT on flag member :((
  if (init)
    TurnOn();
  else
    TurnOff();
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
  lock();
  return{ *this };
}

void semaphore_strict::lock()
{
  while (spinlock.test_and_set())
    std::this_thread::sleep_for(10us);
}

void semaphore_strict::unlock()
{
  // If there was no lock, wait for it >_<
  while (try_lock())
  { // thread unsafe ship
    TurnOff();
    std::this_thread::sleep_for(10us);
  }

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
