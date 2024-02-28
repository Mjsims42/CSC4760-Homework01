
int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and create values
  int n = 16;
  int m = 16;
  Kokkos::View<int**>A("A",n,m);
  Kokkos::View<int**>B("B",n,m);
  Kokkos::Timer timer;
        Kokkos::parallel_for("Loop1", A.extent(0), KOKKOS_LAMBDA (const int i) {
                Kokkos::parallel_for("Loop2", A.extent(1), KOKKOS_LAMBDA (const int j) {
                  A(i, j) = i*j;
                });
            });
  Kokkos::fence();
  double time = timer.seconds();
  timer.reset();
  // sum loops 
  for (int i = 0; i < B.extent(0);i++)
  {
        for (int j = 0; j < B.extent(1);j++)
        {
                B(i,j) = i*j;
        }
  }
  // Output times
  double time1 = timer.seconds();
  std::cout << "Time For Parallel: " << time << std::endl;
  std::cout << "Time For Normal: " << time1 << std::endl;
  }
  Kokkos::finalize();
}
