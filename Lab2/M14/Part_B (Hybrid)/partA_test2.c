#include "types.h"
#include "stat.h"
#include "user.h"
#include "processInfo.h"

int main(void){
    struct processInfo procInfo;
    printf(1, "PID    ParentPID    SIZE    Number of Context Switches\n");

    for(int pid=1; pid<=getMaxPid(); pid++){
        if(getProcInfo(pid, &procInfo) == 0){ 
	        printf(1, "%d      %d      %d    %d\n", pid, procInfo.ppid, procInfo.psize, procInfo.numberContextSwitches);
        }
    }
    exit();
}