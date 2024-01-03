#if defined(__APPLE__)
#include <dispatch/dispatch.h> // Import GCD on Apple devices
#else
#include <semaphore.h> // Import semaphore.h on other platforms
#endif

// Define a structure for semaphore abstraction
typedef struct {
#if defined(__APPLE__)
    dispatch_semaphore_t sem; // Semaphore using GCD
#else
    sem_t sem;
#endif
} sem_c;

// Function to initialize the semaphore
void semaphore_init(sem_c *semaphore, int initialValue) {
#if defined(__APPLE__)
    semaphore->sem = dispatch_semaphore_create(initialValue);
#else
    sem_init(&semaphore->sem, 0, initialValue);
#endif
}

// Function to wait on the semaphore
void semaphore_wait(sem_c *semaphore) {
#if defined(__APPLE__)
    dispatch_semaphore_wait(semaphore->sem, DISPATCH_TIME_FOREVER);
#else
    sem_wait(&semaphore->sem);
#endif
}

// Function to signal the semaphore
void semaphore_post(sem_c *semaphore) {
#if defined(__APPLE__)
    dispatch_semaphore_signal(semaphore->sem);
#else
    sem_post(&semaphore->sem);
#endif
}

// Function to destroy the semaphore
void semaphore_destroy(sem_c *semaphore) {
#if defined(__APPLE__)
    // GCD semaphores do not need explicit destruction
#else
    sem_destroy(&semaphore->sem);
#endif
}
