#include "types.h"
#include "user.h"

#define CRCT(x) 4096 - x

int numGenerator(int num){
	int smallNum = num%10;
	return (5*smallNum + 11*smallNum*smallNum + 17*smallNum*smallNum*smallNum + 43*smallNum*smallNum*smallNum*smallNum);
}

void validator(int ind, int num, int* correct){
	if (numGenerator(ind) == num) *correct+=4;
	return;
}

int main(int argc, char *argv[])
{    
    for (int i=1; i<=20; i++)
        if (fork() == 0){
            int *ptr[10];
			printf(1, "Child ID: %d\n", i);
			for (int j=0; j<10; j++) {
				ptr[j] = (int *)malloc(4096);
				for (int k=0; k<1024; k++)
					ptr[j][k] = numGenerator(k);
			}
			
			for (int j=0; j<10; j++){ 
				int correctBytes=0;
				for (int k=0; k<1024; k++){
					validator(k,ptr[j][k],&correctBytes);
				}
				printf(1,"Iteration Numebr : %d,     Incorrect Bytes: %d\n",j+1,CRCT(correctBytes));
			}
			printf(1,"\n");
			exit();
		}
    
    for (int i=0; i<20; i++){
        wait();
	}
    exit();
}