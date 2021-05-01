#include <SysInfo.h>

#include <sstream>



SysInfo &SysInfo::get_instance() {
  // The sysinfo variable is initialized once with a move assignment of a sysinfo
  // object build with the private constructor.
  static auto &&sysinfo = SysInfo();
  return (sysinfo);
}

