#ifndef ALLTEST_H
#define ALLTEST_H

#include <vector>
#include <atomic>
#include <cstdlib>

// Use the class AllTest for memory sensible tests.
// All allocations and frees within the tests are run through custom code.

// indexes of the next free allocation trace slot
extern std::atomic<size_t> scurrent_alloc; // single allocations
extern std::atomic<size_t> acurrent_alloc; // array allocations
// counters of how many deletes there have been
extern std::atomic<size_t> scurrent_freed; // single deletes
extern std::atomic<size_t> acurrent_freed; // array deletes
// collect errors in these containers
extern std::vector<int> sdouble_freed;
extern std::vector<int> adouble_freed;
extern std::vector<void*> sfreed_notalloc;
extern std::vector<void*> afreed_notalloc;
// are we in a test?
extern bool we_are_testing;

void check_memory(size_t acall, size_t scall);

// if we have more errors than this, then we will see
// additional errors of the allocations for the errors, avoid!
const int RESERVE_ERRORS {1024};

/* do fixtures */
class AllTest : public ::testing::Test {
private:
    static int scall;  // single allocated at start of test
    static int acall;  // array allocated at the start of the test
    static int sfreed; // single freed at end of test
    static int afreed; // array freed at end of test
protected:
    virtual void SetUp() {
        sdouble_freed.clear();
        sdouble_freed.reserve(RESERVE_ERRORS);
        adouble_freed.clear();
        adouble_freed.reserve(RESERVE_ERRORS);
        sfreed_notalloc.clear();
        sfreed_notalloc.reserve(RESERVE_ERRORS);
        afreed_notalloc.clear();
        afreed_notalloc.reserve(RESERVE_ERRORS);
        scall = scurrent_alloc;
        acall = acurrent_alloc;
        sfreed = scurrent_freed;
        afreed = acurrent_freed;
        // std::cout << "SetUp: " << std::endl;
        // std::cout << "  single allocs=" << scurrent_alloc;
        // std::cout << ", array  aallocs=" << acurrent_alloc;
        // std::cout << std::endl;
        we_are_testing = true;
    }    
    virtual void TearDown() {
        we_are_testing = false;
        // std::cout << "TearDown: " << std::endl;
        // std::cout << "scall=" << scall << ", acall=" << acall << std::endl;
        check_memory(scall, acall);
    }
};

// {}-blocks with a variable of this type do not allocate memory
// on the checked area. Use for the actual call of the tests in order
// to avoid memory leaks during error output.
class SuspendMemCheck {
public:
    SuspendMemCheck() {
        we_are_testing = false;
    }
    ~SuspendMemCheck() {
        we_are_testing = true;
    }
};


#endif /* ALLTEST_H */
