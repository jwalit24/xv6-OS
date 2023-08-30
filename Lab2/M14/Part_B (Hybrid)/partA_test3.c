#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
    for(int i=1; i<10; i++){
        set_burst_time((3 * i + 7) % 17 + 1);
        printf(1, "Burst Time: %d\n", get_burst_time());
    }
    exit();
}