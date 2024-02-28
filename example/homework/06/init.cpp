
#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
// Create a program that does matrix addition between a 2D View and a 1D View with at least one loop of parallelism.
// For a test case:
// a = [130, 137, 115]   b = [221]
//     [224, 158, 187]       [12]
//     [ 54, 211, 120]       [157]
// Extra credit: make a function and check for correct shape/dimensions
int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and add values
  int n = 3;
  int m = 3;
  int y = 3;
  Kokkos::View<int**> A("A",n,m);
  Kokkos::View<int*> B("B",n);
  // Do a matrix add
  Kokkos::parallel_for("Loop1", A.extent(0), KOKKOS_LAMBDA (const int i) {
                Kokkos::parallel_for("Loop2", A.extent(1), KOKKOS_LAMBDA (const int j) {
                  A(i,j) = (i+1)*(j+1);
                });
            });
  Kokkos::parallel_for("Loop3", B.extent(0), KOKKOS_LAMBDA (const int i) {
                  B(i) = (i + 1)*( i + 1);
   });
  Kokkos::fence();
  // Output addition
  Kokkos::parallel_for("col", A.extent(0), KOKKOS_LAMBDA (const int i) {
                Kokkos::parallel_for("row", A.extent(1), KOKKOS_LAMBDA (const int j) {
                  A(i, j)+= B(j);
                });
            });
  Kokkos::fence();
  for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                std::cout << A(i,j) << " ";
                }
        std::cout << std::endl;
            }
  }
  Kokkos::finalize();
}
