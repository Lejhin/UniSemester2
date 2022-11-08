// gtest_main.cpp
// Lesen Sie diesen Code nicht, ändern Sie ihn nicht.
// Vor dem Test Ihrer Anwendung wird dieser Code wiederhergestellt.
#include <iostream>
#include <iomanip>
#include "gtest/gtest.h"
#include "alltest.h"

GTEST_API_ int main(int argc, char **argv) {
  std::cout << "Running main() from gtest_main.cpp\n" << std::endl;
  testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  return ret;
}

/// Memory checks
// Override new [] and delete [] as well as new and delete for tracing.
// Use two different stores for single (s) and array (a) allocations
// to catch some memory errors

// #define MEM_VERBOSE

#include <cstdlib>
// for these small tests this is the max number of overall allocations
const int SMAX_ALLOCS = 8192;  
const int AMAX_ALLOCS = 8192; 

// extern declared in alltest.h
int scurrent_alloc = 0;  
int acurrent_alloc = 0; 
int scurrent_freed = 0; 
int acurrent_freed = 0; 
bool we_are_testing = false; 
std::vector<int> sdouble_freed;
std::vector<int> adouble_freed;
std::vector<void *> sfreed_notalloc;
std::vector<void *> afreed_notalloc;

// part of the fixture class
int AllTest::scall;  
int AllTest::acall; 
int AllTest::sfreed;
int AllTest::afreed; 

static void *smemory[SMAX_ALLOCS];
static void *amemory[AMAX_ALLOCS];
static std::size_t smem_size[SMAX_ALLOCS];
static std::size_t amem_size[AMAX_ALLOCS];
static bool smem_freed[SMAX_ALLOCS] = { 0 };
static bool amem_freed[AMAX_ALLOCS] = { 0 };
static int double_freed = 0;
static int freed_not_allocated = 0;

/* allocate memory and store reference in observation area:
 * - for both single and array allocations
 * - but only if we are in a unit test  
 * - check during delete whether that was correct
 */
void *operator new(std::size_t s) {
    if (!we_are_testing) { 
        return malloc(s);
    }
    if (s == 0) {
        std::cout << "warning: new of size 0" << std::endl;
    }
    smemory[scurrent_alloc] = malloc(s);
    smem_size[scurrent_alloc] = s;
    void *ret = smemory[scurrent_alloc];
#ifdef MEM_VERBOSE
    std::cout << std::setw(4) << scurrent_alloc << ": ";
    std::cout << "new:      size=" << s;
    std::cout << " p=" << ret << std::endl;
#endif    
    scurrent_alloc += 1;
    return ret;
}

void *operator new[](std::size_t s) {
    if (!we_are_testing) {
        return malloc(s);
    }
    if (s == 0) {
        std::cout << "warning: new[] of size 0" << std::endl;
    }
    amemory[acurrent_alloc] = malloc(s);
    amem_size[acurrent_alloc] = s;
    void *ret = amemory[acurrent_alloc];
#ifdef MEM_VERBOSE
    std::cout << std::setw(4) << acurrent_alloc << ": ";
    std::cout << "new[]:    size=" << s;
    std::cout << " p=" << ret << std::endl;
#endif
    acurrent_alloc += 1;
    return ret;
}

/* free memory and check whether it has been freed once only in the
 * observation area, if we are in a unit test */
void operator delete(void *p) throw() {
    if (p == nullptr) { // ok, no effect
        return;
    }
    if (!we_are_testing) {
        free(p);
        return;
    }
    // try to find counterpart during allocation, run through
    // all allocation slots
    for (int i=0; i < scurrent_alloc; i+=1) {
        if (smemory[i] != p) {
            continue;
        }
        // found the slot
        if (smem_freed[i]) { // already deleted
            sdouble_freed.push_back(i);
            double_freed += 1;
        }
#ifdef MEM_VERBOSE
        std::cout << std::setw(4) << i << ": ";
        std::cout << "delete:   size=" << smem_size[i];
        std::cout << " p=" << p << std::endl;
#endif
        // free(p); // WE DO NOT FREE! -> avoid reuse
        smem_freed[i] = true;
        scurrent_freed += 1;
        return;
    }
    sfreed_notalloc.push_back(p);
    freed_not_allocated += 1;
}

void operator delete[](void *p) throw() {
    if (p == nullptr) { // ok, no effect
        return;
    }
    if (!we_are_testing) {
        free(p);
        return;
    }
    for (int i=0; i < acurrent_alloc; i+=1) {
        if (amemory[i] != p) {
            continue;
        } else { // found
            if (amem_freed[i]) {
                // Note, that we *must not* produce a failure here,
                // as a failure allocates memory, which in turn will
                // get reported. That is why we have a capacity reserved
                // for the errors in the first place.
                adouble_freed.push_back(i);
                double_freed += 1;
            }
#ifdef MEM_VERBOSE
            std::cout << std::setw(4) << i << ": ";
            std::cout << "delete[]: size=" << amem_size[i];
            std::cout << " p=" << p << std::endl;
#endif
            // free(p); // WE DO NOT FREE! -> avoid reuse
            amem_freed[i] = true;
            acurrent_freed += 1;
            return;
        }
    }
    afreed_notalloc.push_back(p);
    freed_not_allocated += 1;
}

/* At the end of each test we go through the memory and check for errors.
 * We only check allocations that have been allocated during the test.
 * Make sure, that the special new/delete's are off during check_memory.
 * In addition we remove all pointers to allocated but not yet freed memory 
 * during the test to let tools like valgrind take their chance.
 */
void check_memory(int scall, int acall) { // params, where to start
    // std::cout << "check_memory" << std::endl;
    int not_freed = 0;
    int freed = 0;
    // count 
    for (int i=scall; i < scurrent_alloc; i+=1) {
        if (smem_freed[i]) { freed += 1; } else {
            not_freed += 1;
            ADD_FAILURE() << " leak=" << smemory[i]
                          << " size=" << smem_size[i];
        }
    }
    for (int i=acall; i < acurrent_alloc; i+=1) {
        if (amem_freed[i]) { freed += 1; } else {
            not_freed += 1;
            ADD_FAILURE() << " leak[]=" << amemory[i]
                          << " size=" << amem_size[i];
        }
    }
    for (int idx : sdouble_freed) {
        ADD_FAILURE() << " double_free=" << smemory[idx]
                      << " size=" << smem_size[idx];
    }
    for (int idx : adouble_freed) {
        ADD_FAILURE() << " double_free[]=" << amemory[idx]
                      << " size=" << amem_size[idx];
    }
    for (void *p : sfreed_notalloc) {
        ADD_FAILURE() << " freed_not_alloc=" << p;
    }
    for (void *p : afreed_notalloc) {
        ADD_FAILURE() << " freed_not_alloc[]=" << p;
    }
    bool error = false;
    int allocs = (scurrent_alloc-scall) + (acurrent_alloc-acall);
    if (allocs != freed) {
        if (error == false) { std::cout << "Speicherprüfung:"; }
        error = true;
        std::cout << " allokiert=" << allocs;
        std::cout << " freigegeben=" << freed;
        std::cout << " leak=" << (allocs-freed);
    }
    if (double_freed > 0) {
        if (error == false) { std::cout << "Speicherprüfung:"; }
        error = true;
        std::cout << " double_freed=" << double_freed;
    }
    if (freed_not_allocated > 0) {
        if (error == false) { std::cout << "Speicherprüfung:"; }
        error = true;
        std::cout << " freed_not_allocated=" << freed_not_allocated;
    }
    if (error == true) { std::cout << std::endl; }
    // if (errors == 0) {
    //     std::cout << "Keine Speicherfehler, alles gut" << std::endl;
    // } else {
    //     std::cout << "Speicherfehler: " << errors << std::endl;
    // }
    // Here, we can try to free...
    for (int i=scall; i < scurrent_alloc; i+=1) {
        if (smem_freed[i]) { 
            free(smemory[i]);
        } // // keep the leaks (for valgrind)
        smemory[i] = nullptr; // but not a reference to the leaked area
    }
    for (int i=acall; i < acurrent_alloc; i+=1) {
        if (amem_freed[i]) { 
            free(amemory[i]);
        }
        amemory[i] = nullptr; 
    }
    // reset global ones already reported
    double_freed = 0;
    freed_not_allocated = 0;
}

