
#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
// Do simple parallel reduce to output the maximum element in a View
int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and create values
        int n = 8;
        int test = 0;
        double result = 0;
        Kokkos::View<int*> A("A",n);
        Kokkos::parallel_for("Loop1", n, KOKKOS_LAMBDA (const int i) {
                A(i) = i*i;
        });
  // Do a parallel reduction
        Kokkos::parallel_reduce("max",n, KOKKOS_LAMBDA (const int& i, double& max) {
                std::cout << A(i) << std::endl;  
                if(A(i) > max)
                {
                max = A(i);
                }
        },result); 
        Kokkos::fence();
        std::cout << "Max output is: " << result << std::endl;
  }
  Kokkos::finalize();
}   
