#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
    printf(1, "Total Number of Active Processes, as computed by getNumProc() system call: %d\n", getNumProc());
    printf(1, "Maximum PID among those Active Processes, as computed by getMaxPid() system call: %d\n", getMaxPid());
    exit();
}