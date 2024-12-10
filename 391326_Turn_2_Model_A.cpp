#include <iostream>
#include <vector>
#include <chrono>
#include <cassert>

// Function to compute the dot product of two arrays using inline assembly
float dotProductAssembly(const float* a, const float* b, size_t n) {
    float result = 0.0f;
    
    // Using inline assembly to compute the dot product
    __asm__ (
        "movaps %1, %%xmm0;"     // Load a into xmm0
        "movaps %2, %%xmm1;"     // Load b into xmm1
        "xmm2, %%xmm0;"          // Load zero into xmm2
        "movaps %%xmm0, %%xmm2;" // Initialize xmm2 to 0 (result)
        "xor %%ecx, %%ecx;"      // Initialize index register ecx to 0

        "loop_start:"
        "movaps (%1, %%ecx, 4), %%xmm0;" // Load a[i] into xmm0
        "movaps (%2, %%ecx, 4), %%xmm1;" // Load b[i] into xmm1
        "mulps %%xmm1, %%xmm0;"    // Multiply xmm0 and xmm1
        "addps %%xmm0, %%xmm2;"    // Add result to xmm2

        "add $4, %%ecx;"           // Increment index by 4
        "cmp %3, %%ecx;"           // Compare ecx with n
        "jl loop_start;"           // If ecx < n, jump back to loop_start

        "movaps %%xmm2, %%xmm0;"   // Move result to xmm0
        "movhlps %%xmm0, %%xmm2;"  // Move upper half to lower half
        "addps %%xmm0, %%xmm2;"    // Add the components
        "movss %%xmm2, %0;"        // Store result in output variable
        
        : "=m" (result)            // output
        : "r" (a), "r" (b), "r" (n) // inputs
        : "%xmm0", "%xmm1", "%xmm2", "%ecx", "memory" // clobbered registers
    );

    return result;
}

// Function to fill a vector with values
void fillVector(std::vector<float>& vec, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        vec[i] = static_cast<float>(i + 1); // Fill with 1, 2, 3, ..., n
    }
}

// Unit test function
void testDotProduct() {
    const size_t N = 8; // for simplicity in testing
    std::vector<float> A(N), B(N);
    
    fillVector(A, N);
    fillVector(B, N);
    
    float expected = 1.0f * 1.0f + 2.0f * 2.0f + 3.0f * 3.0f + 4.0f * 4.0f +
                     5.0f * 5.0f + 6.0f * 6.0f + 7.0f * 7.0f + 8.0f * 8.0f;

    float result = dotProductAssembly(A.data(), B.data(), N);    
    assert(result == expected); // Ensure the computed result matches the expected value
    std::cout << "Test passed! Dot Product: " << result << std::endl;
}

// Entry point
int main() {
    testDotProduct(); // Run the unit test
    std::cout << "Dot product computed successfully!" << std::endl;
    return 0;
}
