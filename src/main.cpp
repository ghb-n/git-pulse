#include "../include/scanner.h"
#include <filesystem>
#include <iostream>
#ifndef GITPULSE_VERSION
#define GITPULSE_VERSION "dev"
#endif

int main(int argc, char *argv[]) {
  // If you pass a path when running the program, use it. Otherwise, use the
  // current directory (".")
  std::filesystem::path target_path = (argc > 1) ? argv[1] : ".";

  std::cout << "🚀 GitPulse Scanner Initialized\n";
  std::cout << "Scanning path: " << target_path << "\n\n";

  // Call our static scanner function inside the GitPulse namespace
  auto file_map = GitPulse::Scanner::scanfiles(target_path);

  std::cout << "Successfully mapped " << file_map.size() << " files:\n";
  std::cout << "--------------------------------------------------\n";

  // Loop through the unordered_map using modern C++ structured bindings
  for (const auto &[repo_name, info] : file_map) {
    std::cout << "📄 Name: " << repo_name << '\n'
              << "   Path: " << info.RepoPath << '\n'
              << "--------------------------------------------------\n";
  }

  return 0;
}
