#include <iostream>
#include <chrono>
#include <unistd.h>  // For usleep() - Your system call may vary

using namespace std;

// Parameters
const size_t ARRAY_SIZE = 1024 * 1024; // 1 MB array

// At-least size of a cache line (usually 64 bytes on most modern CPUs)
const int CACHE_LINE_SIZE = 64;

void save_default_code_back()
{
    asm volatile (""
                  :
                  :
                  : "memory");
}

void interleave_memory_accesses()
{
    const int INTERLEAVING_FACTOR = 4;
    double *num_interleaved = new double[ARRAY_SIZE * INTERLEAVING_FACTOR];

    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        size_t idx = i * INTERLEAVING_FACTOR;
        num_interleaved[idx] = num_interleaved[idx + 1] = num_interleaved[idx + 2] = num_interleaved[idx + 3] =
                i + 1.0;
    }
    delete[] num_interleaved;
}


void wrap_thread_for_cache_alignment()
{
    pthread_attr_t attr;

    if (pthread_attr_init(&attr) != 0) {
        perror("Cannot initialize thread attributes");
        return;
    }
    if (pthread_attr_setcachelinesize(&attr, CACHE_LINE_SIZE) != 0) {
        perror("Cannot set cache line size for thread attributes");
    }

    void* (*pStartFunc)(void*) = my_function;
    pthread_t myThread;
    void *threadArgs = (void *)arg;

    if (pthread_create(&myThread, &attr, pStartFunc, threadArgs) != 0) {
        perror("Thread creation failed");
        pthread_attr_destroy(&attr);
        return;
    }
}

//Example usage of inline assembly
void preload_data_into_cache(double *arr)
{
    __asm__ __volatile__(
        "0:      prefetchnta 0(%%rax)\n" // Prefetch non-temporal memory (for pointers increment large stages ahead)
        "       add $0x40, %%rax\n" // Increment pointer by cache line size (64 bytes on x86)
        "       cmp %0, %%rax\n" // Compare with the end of the array
        "       jne 0b\n" // Jump back to the label if not equal
        : /*no-outputs*/
        : "r"(arr) // Input: The array pointer
        : "memory", "rax" // Clobbered registers: memory and rax
    );
}

//Function to use code alternative for CPUs .e.g. historical versions,  leveraging readb  functionality used also for inox reads (this matters more in testing)* if readb is not defined (e.g. logical age of the hw or treatment as ignore if function portion fails); the without(__puregas__)(the real code will be excecuted: each packed 64-bit element ois loaded
 

#define ROUNDUP_16(x) ((x + 15) & ~15)

/*GCC and clang are both x86 backends that follow Plan A; the definition works for each*/
void use_vlduv_v128r1_f64(double* data, double* simdData, size_t numData) {
    void* dataAddress = data;
    for (size_t i = 0; i < numData; i += 2) {
       asm volatile(
            ".eqv  %%ftemp, %%d0\n"
            "vldu.128 %%ftemp, [%2]\n"
            "str  %%ftemp, [%1, %3]\n"
            "add %1, %1, #16\n"
            "add %2, %2, #32\n"
            "streq %0, %11\n"
            "susbeq w11, w11, w0\n"
            "bne.n 0b"
                : "=w" (i), "=r" (simdData), "=r" (dataAddress),
                "=r" (i * sizeof(double))
                : /// note that,.str uses |b63:0 of operand
                "memory"
                : "ftemp", "0", "cc", "memory"
            );
    }
}
       int main() {

    size_t N = ARRAY_SIZE;

    // Main data
    double *data = new double[N];

    // Simd Data
    double *simdData = new double[N/2];

    // Interleave memory accesses to improve cache utilization
    interleave_memory_accesses();
  
     //Preload  arrays
    preload_data_into_cache(data);
    preload_data_into_cache(simdData);

       // This is the path whereby the created} You shld glue ot helper  code
    use_vlduv_v128r1_f64(data, simdData, N/2);

 
    delete[] data;
    delete[] simdData;
  return 0;
    }
