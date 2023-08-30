#define uint unsigned int
#include "x86.h"
#include "user.h"




struct thread_spinlock {
  uint locked;       // Is the lock held?

  // For debugging
  char *name;        // Name of lock.
};

void thread_initlock(struct thread_spinlock *lk, char *name) {
  lk->name = name;
  lk->locked = 0;
}



void thread_spin_lock(struct thread_spinlock* lk) {

    // The xchg is atomic.
  while(xchg(&lk->locked, 1) != 0)
    ;
  __sync_synchronize();
}

void thread_spin_unlock(struct thread_spinlock* lk) {

  __sync_synchronize();

  asm volatile("movl $0, %0" : "+m" (lk->locked) : );
}

struct mutex_lock{
  uint locked;
};

void mutex_initlock(struct mutex_lock* lk) {
   lk->locked = 0;
}

void mutex_lock(struct mutex_lock* lk) {
  while(xchg(&lk->locked, 1) != 0)
    sleep(1);
  __sync_synchronize();
}

void mutex_unlock(struct mutex_lock* lk) {
  __sync_synchronize();

  asm volatile("movl $0, %0" : "+m" (lk->locked) : );
}