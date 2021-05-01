#include <iostream>
#include <thread>
#include <vector>

#include <SysInfo.h>

// An arbitrary maximum number of threads.
#define MAX_NB_THREADS 1000

// A simple test routine.
static void test_routine(int i) {
  // Getting the sysinfo instance.
  auto &sysinfo = SysInfo::get_instance();

}


int main(int argc, char const *argv[]) {
  // Initializing the program exit code, success by default.
  auto exit_code = int(EXIT_SUCCESS);
  // Using our sysinfo for ...
  auto &sysinfo = SysInfo::get_instance();
  // Syntactic sugar for first parameter.

  std::cout << "SysInfo singleton example." << std::endl;



  std::cout << "Tests completed with "
            << (exit_code == (EXIT_SUCCESS) ? "success" : "failure") << "."
            << std::endl;

  // Exiting the program with the exit code.
  return (exit_code);
}
