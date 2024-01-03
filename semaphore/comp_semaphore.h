#ifndef CROSS_PLATFORM_SEMAPHORE_H
#define CROSS_PLATFORM_SEMAPHORE_H

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

// Function prototypes
void semaphore_init(sem_c *semaphore, int initialValue);
void semaphore_wait(sem_c *semaphore);
void semaphore_post(sem_c *semaphore);
void semaphore_destroy(sem_c *semaphore);

#endif /* CROSS_PLATFORM_SEMAPHORE_H */
