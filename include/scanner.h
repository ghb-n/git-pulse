#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#ifndef SCANNER_H
#define SCANNER_H

using namespace std;
namespace GitPulse {
struct FileInfo {
  string FileName;
  string FilePath;
  uintmax_t FileSize;
};

class Scanner {
public:
  static std::unordered_map<std::string, FileInfo>
  scanfiles(const std::filesystem::path &path);
};
} // namespace GitPulse

#endif
