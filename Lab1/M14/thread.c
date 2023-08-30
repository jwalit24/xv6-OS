#include "types.h"
#include "stat.h"
#include "thread.h"
// #include "user.h"
// #include "x86.h"

struct balance {
    char name[32];
    int amount;
};

volatile int total_balance = 0;

struct thread_spinlock lock;
struct mutex_lock m_lock;

volatile unsigned int delay (unsigned int d) {
   unsigned int i;
   for (i = 0; i < d; i++) {
       __asm volatile( "nop" ::: );
   }

   return i;
}



void do_work(void *arg){
    int i;
    int old;

    struct balance *b = (struct balance*) arg;
    thread_spin_lock(&lock);
    printf(1, "Starting do_work: s:%s\n", b->name);
     thread_spin_unlock(&lock);

    for (i = 0; i < b->amount; i++) {
        //  thread_spin_lock(&lock);
         mutex_lock(&m_lock);
         old = total_balance;
         delay(100000);
         total_balance = old + 1;
        //  thread_spin_unlock(&lock);
         mutex_unlock(&m_lock);
    }
    
    thread_spin_lock(&lock);
    printf(1, "Done s:%s\n", b->name);
    thread_spin_unlock(&lock);

    thread_exit();
    return;
}

int main(int argc, char *argv[]) {

  struct balance b1 = {"b1", 3200};
  struct balance b2 = {"b2", 2800};

  void *s1, *s2;
  int t1, t2, r1, r2;

  s1 = malloc(4096);
  s2 = malloc(4096);

  // Initialize thread_spin_lock
  thread_initlock(&lock,"do work");
  mutex_initlock(&m_lock);

  t1 = thread_create(do_work, (void*)&b1, s1);
  t2 = thread_create(do_work, (void*)&b2, s2);

  r1 = thread_join();
  r2 = thread_join();

  printf(1, "Threads finished: (%d):%d, (%d):%d, shared balance:%d\n",
      t1, r1, t2, r2, total_balance);

  exit();
}
