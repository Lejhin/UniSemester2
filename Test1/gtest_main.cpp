// gtest_main.cpp
// Lesen Sie diesen Code nicht, ändern Sie ihn nicht.
// Vor dem Test Ihrer Anwendung wird dieser Code wiederhergestellt.
#include <iostream>
#include <iomanip>
#include "gtest/gtest.h"
#include "alltest.h"

// the main program running all unit tests
GTEST_API_ int main(int argc, char** argv) {
  std::cout << "Running main() from gtest_main.cpp" << std::endl;
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
// for all tests this is the maximum number of allocations for *all* unit tests
const int SMAX_ALLOCS = 65536;
const int AMAX_ALLOCS = 65536;

// extern declared in alltest.h
std::atomic<size_t> scurrent_alloc(0);
std::atomic<size_t> acurrent_alloc(0);
std::atomic<size_t> scurrent_freed(0);
std::atomic<size_t> acurrent_freed(0);
bool we_are_testing {false};
std::vector<int> sdouble_freed;
std::vector<int> adouble_freed;
std::vector<void*> sfreed_notalloc;
std::vector<void*> afreed_notalloc;

// part of the fixture class
int AllTest::scall;
int AllTest::acall;
int AllTest::sfreed;
int AllTest::afreed;

static void* smemory[SMAX_ALLOCS]; // pointers to allocated single chunks
static void* amemory[AMAX_ALLOCS]; // pointers to allocated array chunks
static std::size_t smem_size[SMAX_ALLOCS]; // size of allocated single chunks
static std::size_t amem_size[AMAX_ALLOCS]; // size of allocated array chunks
static bool smem_freed[SMAX_ALLOCS] = { 0 }; // whether single alloc has been freed
static bool amem_freed[AMAX_ALLOCS] = { 0 }; // whether array alloc has been freed
static int double_freed = 0; // count the double freed allocations
static int freed_not_allocated = 0; // count the freed but not allocated ptrs

/* allocate memory and store reference in observation area [sa]memory:
 * - for both single and array allocations
 * - but only if we are in a unit test and have not suspending memchecking
 * - check during delete whether that was correct
 */
void* operator new(std::size_t s) {
    if (!we_are_testing) {
        return malloc(s);
    }
    if (s == 0) {
        std::cout << "warning: new of size 0" << std::endl;
    }
    size_t current = scurrent_alloc++;
    smemory[current] = malloc(s);
    smem_size[current] = s;
    void* ret = smemory[current];
#ifdef MEM_VERBOSE
    std::cout << std::setw(4) << current << ": ";
    std::cout << "new:      size=" << std::setw(4) << s;
    std::cout << " p=" << ret << std::endl;
#endif
    return ret;
}

void* operator new[](std::size_t s) {
    if (!we_are_testing) {
        return malloc(s);
    }
    if (s == 0) {
        std::cout << "warning: new[] of size 0" << std::endl;
    }
    size_t current = acurrent_alloc++;
    amemory[current] = malloc(s);
    amem_size[current] = s;
    void* ret = amemory[current];
#ifdef MEM_VERBOSE
    std::cout << std::setw(4) << current << ": ";
    std::cout << "new[]:    size=" << std::setw(4) << s;
    std::cout << " p=" << ret << std::endl;
#endif
    return ret;
}

/* free memory and check whether it has been freed once only in the
 * observation area, if we are in a unit test */
void operator delete(void* p) throw() {
    if (p == nullptr) { // that is always ok, per C++ spec no effect
        return;
    }
    if (!we_are_testing) { // if not memchecking or memchecking suspended
        free(p); // plain free for plain malloc
        return;
    }
    // try to find counterpart during allocation, run through
    // all allocation slots
    size_t current = scurrent_alloc;
    for (size_t i=0; i < current; i+=1) {
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
        std::cout << "delete:   size=" << std::setw(4) << smem_size[i];
        std::cout << " p=" << p << std::endl;
#endif
        // free(p); // WE DO NOT FREE! -> avoid reuse for analysis
        smem_freed[i] = true;
        scurrent_freed += 1;
        return;
    }
    // found a memory error: this address has not been allocated but freed
    sfreed_notalloc.push_back(p);
    freed_not_allocated += 1;
}

void operator delete[](void* p) throw() {
    if (p == nullptr) { // that is always ok, per C++ spec no effect
        return;
    }
    if (!we_are_testing) {
        free(p);
        return;
    }
    size_t current = acurrent_alloc;
    for (size_t i=0; i < current; i+=1) {
        if (amemory[i] != p) {
            continue;
        }
        // found the slot
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
        std::cout << "delete[]: size=" << std::setw(4) << amem_size[i];
        std::cout << " p=" << p << std::endl;
#endif
        // free(p); // WE DO NOT FREE! -> avoid reuse
        amem_freed[i] = true;
        acurrent_freed += 1;
        return;
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
void check_memory(size_t scall, size_t acall) { // params, where to start
    // std::cout << "check_memory" << std::endl;
    int not_freed = 0;
    int freed = 0;
    // count
    size_t scurrent = scurrent_alloc;
    for (size_t i=scall; i < scurrent; i+=1) {
        if (smem_freed[i]) { freed += 1; } else {
            not_freed += 1;
            ADD_FAILURE() << " leak=" << smemory[i]
                          << " size=" << smem_size[i];
        }
    }
    size_t acurrent = acurrent_alloc;
    for (size_t i=acall; i < acurrent; i+=1) {
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
    for (void* p : sfreed_notalloc) {
        ADD_FAILURE() << " freed_not_alloc=" << p;
    }
    for (void* p : afreed_notalloc) {
        ADD_FAILURE() << " freed_not_alloc[]=" << p;
    }
    bool error = false;
    int allocs = (scurrent-scall) + (acurrent-acall);
    if (allocs != freed) {
        if (error == false) { std::cout << "Speicherprüfung:"; }
        error = true;
        ADD_FAILURE() << " allokiert=" << allocs << 
            " freigegeben=" << freed << 
            " leak=" << (allocs-freed);
    }
    if (double_freed > 0) {
        if (error == false) { std::cout << "Speicherprüfung:"; }
        error = true;
        ADD_FAILURE() << " double_freed=" << double_freed;
    }
    if (freed_not_allocated > 0) {
        if (error == false) { std::cout << "Speicherprüfung:"; }
        error = true;
        ADD_FAILURE() << " freed_not_allocated=" << freed_not_allocated;
    }
    if (error == true) { std::cout << std::endl; }
    // if (errors == 0) {
    //     std::cout << "Keine Speicherfehler, alles gut" << std::endl;
    // } else {
    //     std::cout << "Speicherfehler: " << errors << std::endl;
    // }
    // Here, we can try to free...
    for (size_t i=scall; i < scurrent; i+=1) {
        if (smem_freed[i]) {
            free(smemory[i]);
        } // // keep the leaks (for valgrind)
        smemory[i] = nullptr; // but not a reference to the leaked area
    }
    for (size_t i=acall; i < acurrent; i+=1) {
        if (amem_freed[i]) {
            free(amemory[i]);
        }
        amemory[i] = nullptr;
    }
    // reset global ones already reported
    double_freed = 0;
    freed_not_allocated = 0;
}

