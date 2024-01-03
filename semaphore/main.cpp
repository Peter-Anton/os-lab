#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include "comp_semaphore.h"
#define N 5
#define buffer 5
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KNRM  "\x1B[0m"
using namespace std;

queue<int> b;
int c = 0;

sem_c counter_mutex;
sem_c buffer_mutex;


void* collector(void* arg) {
    while (true) {
        sleep(random() % 30);
        semaphore_wait(&buffer_mutex);
        if (!b.empty()) {
            printf(KBLU "Collector thread: reading from buffer at position %lu\n" KNRM, b.size());
            b.pop();
        } else {
            printf(KBLU "Collector thread: buffer is empty\n" KNRM);
        }
        semaphore_post(&buffer_mutex);
    }
}

void* monitor(void* arg) {
        int count=-1;
    while (true) {
        
        sleep(random() % 30);
        printf(KGRN "Monitor thread: waiting to read\n" KNRM);
        
        if(count<0){
        semaphore_wait(&counter_mutex);
        count = c;
        c = 0;
        printf(KGRN "Monitor thread: reading a count value of %d\n" KNRM, count);
        semaphore_post(&counter_mutex);
        }
        
        

        semaphore_wait(&buffer_mutex);
        
        if (b.size() < buffer) {

            b.push(count);
            printf(KGRN "Monitor thread: writing to buffer at position %lu\n" KNRM, b.size());
            count=-1;

        } else {
            printf(KGRN "Monitor thread: buffer is full\n" KNRM);
        }
        
        semaphore_post(&buffer_mutex);
    }
}

void* counter(void* arg) {
    int thread = *(int*)arg;
    while (true) {
        sleep(random() % 30);
        printf(KRED "Counter thread %d: received a message\n" KNRM, thread);
        
        semaphore_wait(&counter_mutex);
        printf(KRED "Counter thread %d: waiting to write\n" KNRM, thread);
        c++;
        printf(KRED "Counter thread %d: now adding to counter, counter value = %d\n" KNRM, thread, c);
        semaphore_post(&counter_mutex);
    }
}


int main() {
    pthread_t mCollector, mMonitor, mCounter[N];
    
    
    pthread_create(&mCollector, NULL, collector, NULL);
    pthread_create(&mMonitor, NULL, monitor, NULL);

  
    for (int i = 0; i < N; i++) {
        int* thread_num = new int(i);
        pthread_create(&mCounter[i], NULL, counter, (void*)thread_num);
    }

    
    semaphore_init(&counter_mutex, 1);
    semaphore_init(&buffer_mutex, 1);

  
    pthread_join(mCollector, NULL);
    pthread_join(mMonitor, NULL);
    for (int i = 0; i < N; i++) {
        pthread_join(mCounter[i], NULL);
    }
    semaphore_destroy(&counter_mutex);
    semaphore_destroy(&buffer_mutex);
    printf("All threads have been joined\n");
    return 0;
}
