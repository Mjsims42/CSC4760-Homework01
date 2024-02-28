
#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
// Do simple parallel reduce to output the maximum element in a View
struct Foo{
  KOKKOS_INLINE_FUNCTION void operator() (const double& i, double& max) const{
    if(i > max){
            max = i;
    }
   }
 };
int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and create values
        int n = 8;
        int test = 0;
        Kokkos::View<int*> A("A",n);
        Kokkos::parallel_for("Loop1", n, KOKKOS_LAMBDA (const int i) {
                A(i) = i*i;
        });
  // Do a parallel reduction
        Foo functor;
        double result = 0;
        Kokkos::parallel_reduce(n,functor,result);
        std::cout << "Max output is: " << result << std::endl;
  } 
  Kokkos::finalize(); 
} 
