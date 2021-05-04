#include <SysInfo.h>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <utility>
#include "MacSystemInfo.h"

SysInfo &SysInfo::get_instance() {
  // The sysinfo variable is initialized once with a move assignment of a sysinfo
  // object build with the private constructor.
  static auto &&sysinfo = SysInfo();
  return (sysinfo);
}

std::pair<double, double> SysInfo::fetchMemory() {
  long pages = sysconf(_SC_PHYS_PAGES);
  long page_size = sysconf(_SC_PAGE_SIZE);
  double memory = pages* page_size/1073741824.0;
  double used = 0;
  struct rusage usage;
  if(0 == getrusage(RUSAGE_SELF, &usage))
    used = usage.ru_maxrss/1073741824.0;

  std::cout << "Total system memory: " << memory << " GB " << used << " GB " << std::endl;
  return std::pair<double,double>(memory,used);
}

void SysInfo::loadSystemFeatures() {
    os = operating_system::mac;
    osVersion = mac_version();
}
