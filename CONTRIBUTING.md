# Contributing to GitPulse

First off — thank you. GitPulse is a small project, and every contribution is
welcome: bug reports, feature ideas, documentation fixes, or code.

By participating here you agree to keep the project friendly and follow the
guidelines below.

## Code of Conduct

This project follows the [Contributor Covenant](https://www.contributor-covenant.org/version/2/1/code_of_conduct/).
Be respectful, assume good intent, and critique the code rather than the
author. Harassment and abuse of any kind are not tolerated.

## Reporting Bugs

Please check the [existing issues](https://github.com/ghb-n/git-pulse/issues)
first so we don't end up with duplicates. A useful bug report includes:

1. **Summary** — one line describing what breaks.
2. **Steps to reproduce** — the exact command and directory tree you used.
3. **Expected vs. actual** — what you thought would happen, what did happen.
4. **Environment** — distro/version, `g++ --version`, `cmake --version`, and
   the commit you tested.
5. **Output** — paste the full crash text or terminal output in a fenced code
   block.

Bugs with a reproducible command are fixed fastest.

## Suggesting Enhancements

Open an issue tagged `enhancement` that describes the problem you hit, not just
the solution you have in mind — *"I have 300 repos and scanning feels slow"*
leads to better changes than *"add a cache"*. Include a concrete scenario and,
if you can, what you'd expect the output to look like.

## Development Setup

| Requirement    | Version                                  |
| -------------- | ---------------------------------------- |
| C++ compiler   | GCC 9+ or Clang 10+ (C++17 support)      |
| CMake          | ≥ 3.15                                   |
| Linux          | any modern distro                        |
| `git`          | for cloning and testing                  |

```bash
git clone https://github.com/ghb-n/git-pulse.git
cd git-pulse

mkdir -p build && cd build
cmake ..
make
```

Run it against any directory — no arguments scans the current one:

```bash
./git_pulse /path/to/your/workspace
```

## Style Guide

GitPulse is C++17 with **zero external dependencies** — the standard library is
all you get, so please don't add Boost, libgit2, or other requirements without
discussing it in an issue first.

Match the code that's already there:

| Aspect            | Rule                                              |
| ----------------- | ------------------------------------------------- |
| Indentation       | 2 spaces, never tabs                              |
| Column limit      | 80 characters                                     |
| Braces            | attached — `if (x) {` (not Allman)                |
| Function head     | return type on its own line                       |
| Namespaces        | contents not indented                             |
| File names        | `snake_case.cpp` / `snake_case.h`                 |
| Types & namespaces| `PascalCase` (`Scanner`, `FileInfo`, `GitPulse`)  |
| Struct members    | `PascalCase` (`RepoName`, `RepoPath`)             |
| Functions         | `lowerCamelCase` (`scanfiles`)                    |
| Error handling    | `throw`/`catch` `fs::filesystem_error`; no `exit()` mid-scan |

Guidelines that matter more than the table:

- **Prefer `'\n'` over `std::endl`.** No implicit flushes in hot output loops.
- **Never let one unreadable entry kill the scan.** Catch per-entry, report to
  `std::cerr`, and continue — this is what
  `fs::directory_options::skip_permission_denied` and the existing
  `try`/`catch` in `scanner.cpp` are for.
- **Headers stay self-contained** — they must compile on their own.

If you use clang-format to double-check your work, the
`Google` base style with `IndentWidth: 2`, `ColumnLimit: 80`, and
`BreakBeforeBraces: Attach` reproduces this layout.

## Testing

There is no automated suite yet — see the roadmap. Until there is, verify your
change manually against a known directory tree:

```bash
# Build a fixture: two repositories and one plain directory
mkdir -p /tmp/gitpulse-fixtures/{repo-a,repo-b,plain-dir}
for r in repo-a repo-b; do (cd /tmp/gitpulse-fixtures/$r && git init -q); done
echo "hello" > /tmp/gitpulse-fixtures/repo-a/file.txt

# Run the scanner
./build/git_pulse /tmp/gitpulse-fixtures
```

Both repositories must be reported with their paths, and `plain-dir` must not
appear. Also confirm the two failure paths behave: a nonexistent path prints an
error and returns an empty result set instead of crashing (`git_pulse /nope`).

Before opening a PR, make sure the build is clean from scratch:

```bash
rm -rf build && mkdir -p build && cd build && cmake .. && make
```

## Commit Messages

Use a short, imperative subject line with a Conventional Commits prefix:

```
feat: detect repositories with bare .git files
fix: skip unreadable entries instead of aborting the scan
docs: add CONTRIBUTING.md
```

- Prefixes: `feat`, `fix`, `docs`, `refactor`, `test`, `chore`, `build`, `ci`
- Subject ≤ 72 characters, capitalized-less, no trailing period
- Reference issues in the body (`Closes #12`)

## Pull Requests

1. **Branch off `main`** with a descriptive name: `feat/bare-git-detect`,
   `fix/nested-repos`.
2. **One concern per PR** — don't bundle a refactor with a bug fix.
3. **Describe what and why** in the PR body, plus the exact steps you ran to
   test it. Link the issue it resolves.
4. **Update `README.md`** if user-visible behavior changes (new flags, output
   format, requirements).
5. **Don't reformat unrelated code** — it hides your actual diff.
6. **No new dependencies** without prior agreement.

All contributions are made under the project's
[GPL-3.0](LICENSE) license — derivative works must stay GPL-3.0.

## Good First Issues

Looking for a place to start? These are on the roadmap in
[`README.md`](README.md#roadmap) and are self-contained:

- Per-repository dirty/staged/clean status detection
- Ahead/behind commit counts against the tracking remote
- JSON output for scripting
- A test target with the fixture above wired up

Questions? Open an issue and ask — happy to help you get started.
