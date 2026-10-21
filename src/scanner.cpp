#include "../include/scanner.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace GitPulse {

    std::unordered_map<std::string, FileInfo> Scanner::scanfiles(const fs::path& path) {
        std::unordered_map<std::string, FileInfo> repo_map;

        if (!fs::exists(path) || !fs::is_directory(path)) {
            std::cerr << "❌ Error: Invalid path: " << path << '\n';
            return repo_map;
        }

        try {
            for (auto it = fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied);
                 it != fs::recursive_directory_iterator(); ++it) {
                
                // Use a try-catch for individual entries so one bad file doesn't kill the whole scan
                try {
                    const auto& entry = *it;

                    // Safely check if it's a directory
                    if (entry.is_directory()) {
                        // Print path directly using path's stream operator (no string conversion risk)
                        // std::cout << "Checking: " << entry.path() << '\n';

                        if (entry.path().filename() == ".git") {
                            fs::path repo_path = entry.path().parent_path();
                            
                            // Convert safely only when we know it's a valid repo path
                            std::string repo_name = repo_path.filename().string();
                            std::string path_str = repo_path.string();

                            if (!repo_name.empty() && !path_str.empty()) {
                                std::cout << "🎯 Found Git Repo: " << repo_name << " at " << path_str << '\n';
                                repo_map[repo_name] = FileInfo{path_str, 0};
                            }

                            it.disable_recursion_pending();
                        }
                    }
                } catch (const std::exception& inner_e) {
                    // Suppress or log individual file hiccups without crashing
                    // std::cerr << "Skipped a problematic entry: " << inner_e.what() << '\n';
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "⚠️ Filesystem error: " << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cerr << "⚠️ Standard exception during scan: " << e.what() << '\n';
        }

        return repo_map;
    }

} // namespace GitPulse