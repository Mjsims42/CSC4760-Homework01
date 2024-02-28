
#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
// Declare a 5 ∗ 7 ∗ 12 ∗ n View
int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  int n = 8;
  // Make View
  Kokkos::View<int****> A("A",5,7,12,n);
  // print name
  std::cout << A.label() << "\n";
  }
  Kokkos::finalize();
}
