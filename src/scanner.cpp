#include "../include/scanner.h"
#include <cstdint>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

using namespace GitPulse::Scanner;
struct GitPulse::Scanner::FileInfo {
  string FileName;
  string FilePath;
  uintmax_t FileSize;
};

std::unordered_map<std::string, FileInfo>
GitPulse::Scanner::scanfiles(const fs::path &path) {
  std::unordered_map<std::string, FileInfo> file_map;

  if (!fs::exists(path) || !fs::is_directory(path)) {
    cerr << "Error: Path does not exists or is not a directory.\n";
    return file_map;
  }

  for (const auto &entry : fs::recursive_directory_iterator(path)) {
    if (entry.is_regular_file()) {
      string file_name = entry.path().filename().string();
      string path_str = entry.path().string();

      uintmax_t file_size = 0;
      try {
        file_size = entry.file_size();
      } catch (const fs::filesystem_error &e) {
        cerr << "Could not read size for " << file_name << " : " << e.what()
             << "\n";
      }

      file_map[file_name] = FileInfo{file_name, path_str, file_size};
    }
  }
  return file_map;
} // namespace GitPulse::Scanner
