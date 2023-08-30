#include "types.h"
#include "stat.h"
#include "user.h"
#include "processInfo.h"

// CPU bound
void delay()
{
    int* data = (int*)malloc(1000*sizeof(int));

    for(int i=0;i<100000000;++i)
        data[i % 1000] = 0;

    for(int j=0;j<100000000;j++)
        data[j % 1000] = 0;
}


int main(int argc, char *argv[])    
{
    if (argc < 2)
    {
        printf(1, "Incorrect Format\n\nInput Format : test<test-case-number> <number-of-child-processes>\nE.g. : test1 10\n");
        exit();
    }
    int N = atoi(argv[1]);

    int pids[N];
    int return_order_of_procs[N];
    int burstTimes[N];
    set_burst_time(2);
    printf(1,"Test Case #1 : Random burst times of Child Processes\n");
    printf(1, "Burst times of parent process = %d\n\n", get_burst_time());
    int x0 = 3,a = 5,b = 4,m = 17;
    int first_child_process_pid;
    for (int i = 0; i < N; i++)
    {
        x0 = (a*x0+b)%m;

        int newProcPID = fork();
        if (newProcPID == 0)
        {
            struct processInfo info;
	        getProcInfo(getpid(),&info);
	        printf(1,"Before Execution starts : pid = %d  context-switches=%d \n",getpid(),info.numberContextSwitches);
            
            set_burst_time(x0+3);
            delay();
            getProcInfo(getpid(),&info);
	        printf(1,"After Execution ends : pid = %d  context-switches=%d \n",getpid(),info.numberContextSwitches); 
            exit();
        }
        else if (newProcPID > 0)
        {
            if(i == 0){
                first_child_process_pid = newProcPID;
            }
            pids[i] = newProcPID;
            burstTimes[i] = x0+3;
        }
        else
        {
            printf(1, "Error occured while forking \n");
            exit();
        }
    }
    
    for (int i = 0; i < N; i++)
    {
        return_order_of_procs[i] = wait();
    }

    printf(1, "\nAll children executed successfully\n");
    for (int i = 0; i < N; i++)
        printf(1, "Child %d    pid %d    burst time = %d\n", i, pids[i],burstTimes[i]);

    
    printf(1, "\nChild Proceses Exit order \n");
    for (int i = 0; i < N; i++)
        printf(1, "pid %d     burst time = %d\n", return_order_of_procs[i], burstTimes[return_order_of_procs[i]-first_child_process_pid]);

    exit();
}
