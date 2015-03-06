#pragma once

#include <atomic>

class semaphore_strict
{
  std::atomic_flag spinlock;
public:
  semaphore_strict(bool init = false);
  virtual ~semaphore_strict();

  void TurnOn();
  void TurnOff();

  bool try_lock();
  void lock();
  void unlock();

  bool Move();
  bool Status();

  class lock_guard
  {
    semaphore_strict &obj;
    mutable bool disabled = false;
    lock_guard(semaphore_strict &o) : obj(o) {}
  public: // Cause suddenly move semantics wont work for Lock method
    lock_guard(const lock_guard &g) : obj(g.obj)
    {
      g.disabled = true;
    }
    friend class semaphore_strict;
    ~lock_guard()
    {
      if (!disabled)
        obj.TurnOff();
    }
  };

  auto Lock()->lock_guard;
};

class semaphore : public semaphore_strict
{
public:
  semaphore(bool init = true);
  ~semaphore() override;
};