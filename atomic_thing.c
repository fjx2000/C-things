/*************************************************************************************************************************************
This thing is to demonstrate how to use atomic data type and atomic operations.

**************************************************************************************************************************************/


#include <stdio.h>
#include <pthread.h>  /* in c11, if the compiler and lib support threads, maybe can use <threads.h>, tested with GCC5.3.0, does not support*/
#include <stdatomic.h>
 
atomic_int acnt;
int cnt;
int fcnt;
 
void* f(void* thr_data)
{
    for(int n = 0; n < 100000; ++n) {
        ++cnt;
        ++acnt;
        // for this example, relaxed memory order is sufficient, e.g.
        atomic_fetch_add_explicit(&fcnt, 1, memory_order_relaxed);
    }
}
 
int main(void)
{
    pthread_t thr[10];
    for(int n = 0; n < 10; ++n)
        pthread_create(&thr[n], NULL, f, NULL);
    for(int n = 0; n < 10; ++n)
        pthread_join(thr[n], NULL);  /* parent thread join all child threads, until all child threads end, then start to print */
    printf("The atomic_int counter is %u\n", acnt);
    printf("The non-atomic counter is %u\n", cnt);
    printf("The atomic function counter is %u\n", fcnt);
}

/****************************************************************************************************************************
Test Result :
esekilxxen2768: ~/test_c  > gcc -pthread -o atomic atomic_test.c
esekilxxen2768: ~/test_c  > ./atomic
The atomic_int counter is 1000000
The non-atomic counter is 654428
The atomic function counter is 1000000
esekilxxen2768: ~/test_c  > ./atomic
The atomic_int counter is 1000000
The non-atomic counter is 665283
The atomic function counter is 1000000
esekilxxen2768: ~/test_c  > 

*****************************************************************************************************************************/
