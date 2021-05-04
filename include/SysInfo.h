#ifndef SINGLETON_SYSINFO_H
#define SINGLETON_SYSINFO_H

#include <utility>
#include <string>

// The C++11 singleton-based system info class.
class SysInfo final {
 private:
  // Private default constructor.
  //SysInfo() = default;
  SysInfo() { loadSystemFeatures(); }
  enum operating_system {mac, windows};
  operating_system os;
  float osVersion;

 public:

  // Initialize the singleton once, and return it each time this class
  // method is called.
  static SysInfo &get_instance();

  // Default destructor. No need for virtual destructor as the
  // class cannot be inherited.
  ~SysInfo() = default;

  // Deleted copy constructor.
  // Only the get_instance class method is allowed to give a sysinfo.
  SysInfo(const SysInfo &) = delete;

  // Deleted copy assignment.
  // Only the get_instance class method is allowed to give a sysinfo.
  void operator=(const SysInfo &) = delete;

  // Default move constructor.
  SysInfo(SysInfo &&) noexcept = default;

  // Default move assignment.
  SysInfo &operator=(SysInfo &&) noexcept = default;

  std::pair<double, double> fetchMemory();

  void loadSystemFeatures();
    
  std::string mac_version();

};

#endif //SINGLETON_SYSINFO_H
