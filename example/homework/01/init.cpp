
#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>
// Problem: Link and run program with Kokkos where you initialize a View and print out its name with the $.label()$ method.
int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  int n = 8;
  // Make View
  Kokkos::View<int*>A("Hello world",n);
  std::cout << A.label() << "\n";
  }
  Kokkos::finalize();
}
