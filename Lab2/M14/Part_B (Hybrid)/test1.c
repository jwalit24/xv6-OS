#include "types.h"
#include "stat.h"
#include "user.h"
#include "processInfo.h"

// CPU bound
void delay(int n)
{
    int* data = (int*)malloc(1000*sizeof(int));

    for(int i=0;i<n*1000000;++i)
        data[i % 1000] = 0;

    for(int j=0;j<n*1000000;j++)
        data[j % 1000] = 0;
}


int main(int argc, char *argv[])    
{
    if (argc < 1)
    {
        printf(1, "test-case <number-of-children>\n");
        exit();
    }
    int N = 4;

    int pids[N];
    int rets[N];
    int burstTimes[N];
    set_burst_time(2);
    printf(1,"Random burst times\n");
    printf(1, "Burst times of parent process = %d\n", get_burst_time());
    int x0 = 3,a = 5,b = 4,m = 17;
    for (int i = 0; i < 4; i++)
    {
        x0 = (a*x0+b)%m;

        int ret = fork();
        if (ret == 0)
        {
            // struct processInfo info;
	        // getProcInfo(getpid(),&info);
	        // printf(1,"pid = %d  context=%d \n",getpid(),info.numberContextSwitches);
            
            if(i == 0){
                set_burst_time(10000);
            }else if(i == 1){
                set_burst_time(1000);
            }else if(i == 2){
                set_burst_time(200);
            }else if(i == 3){
                set_burst_time(2);
            }
            // set_burst_time(x0 + 3);
            delay(get_burst_time());
            // getProcInfo(getpid(),&info);
	        // printf(1,"pid = %d  context=%d \n",getpid(),info.numberContextSwitches); 
            exit();
        }
        else if (ret > 0)
        {
            pids[i] = ret;
            // burstTimes[i] = x0+3;
            if(i == 0){
                burstTimes[i] = 10000;
            }else if(i == 1){
                burstTimes[i] = 1000;
            }else if(i == 2){
                burstTimes[i] = 200;
            }else if(i == 3){
                burstTimes[i] = 2;
            }
        }
        else
        {
            printf(1, "fork error \n");
            exit();
        }
    }
    
    for (int i = 0; i < N; i++)
    {
        rets[i] = wait();
    }

    printf(1, "\nAll children executed\n");
    for (int i = 0; i < N; i++)
        printf(1, "Child %d.    pid %d    burst time = %d\n", i, pids[i],burstTimes[i]);

    
    printf(1, "\nExit order \n");
    for (int i = 0; i < N; i++)
        printf(1, "pid %d   burst time = %d\n", rets[i],burstTimes[rets[i]-4]);

    exit();
}
