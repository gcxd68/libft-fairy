## Quick orientation for AI coding agents

This repo is a test harness for 42's libft project. The tester is a single binary driven by `run.sh` and several C test suites. Use this file to quickly find the important files, common workflows, and project-specific rules the human maintainers expect.

- Primary entry points
  - `run.sh` — orchestrates the whole validation pipeline (norminette, prototype checks, Makefile checks, build, external function checks, test compilation, running tests, Valgrind leak checks). See the top-level script for exact behaviour and flags.
  - `basic_tests.c`, `basic_tests_bonus.c` — mandatory and bonus functional tests. These compile into `.basic_tests` / `.basic_tests_bonus`.
  - `leak_tests.c`, `leak_tests_bonus.c` — Valgrind leak verification programs.
  - `utils.c`, `libft_fairy.h` — helper functions (malloc wrapper, safe list helpers, forked test harness, printing). `__wrap_malloc` and global flags are used for malloc-failure simulation.

- High-level flow (what `run.sh` does)
  1. norminette across the libft directory (exits or prints errors if norm reports problems).
 2. Prototype verification: `run.sh` greps `../libft.h` with a list of regexes — missing or malformed prototypes are reported. Example regex used:
     - `'int\\t+ft_atoi\\(const char \\\*nptr\\);'` (see script for full list).
 3. Makefile validation: expects `cc` as compiler, `-Wall -Wextra -Werror`, and rules `all, clean, fclean, re` and a `$(NAME)` rule. Wildcard patterns like `*.c`/`*.o` are considered forbidden.
 4. Build the libft (optionally `bonus`) via `make -C ..`.
 5. External symbol checks using `nm -u` on object files to ensure only allowed externals are used per function (e.g. some functions must have no externals, others are allowed `malloc` or `write`).
 6. Compile tests with flags: `-Wall -Wextra -Werror -no-pie` and link with the libft via `-L.. -lft -I..`, and importantly pass `-Wl,--wrap=malloc` to enable the malloc wrapper.
 7. Run basic tests and run Valgrind for leak tests. Tests that can crash run in child processes via `fork()` to avoid bringing down the tester.

- Developer workflows (commands to run)
  - Run full tester: `./run.sh`
  - Verbose mode (show all tests): `./run.sh -v` or `./run.sh --verbose`
  - To reproduce how a tester binary is compiled (from `run.sh`):
    - gcc compile flags used in script: `-Wall -Wextra -Werror -no-pie` plus `-DVERBOSE` when requested and `-Wl,--wrap=malloc` for malloc simulation.

- Project-specific conventions and patterns for changes
  - Prototypes in `libft.h` must exactly match the regexes embedded in `run.sh`. If you add or rename functions, update both `libft.h` and the regex list in `run.sh` if appropriate.
  - The tester expects the tester directory to be placed inside the student's libft directory (default `LIBFT_DIR=".."`). Don't change that path unless you also update `run.sh`.
  - Do not rely on tests running in the same process: many tests intentionally fork. When adding tests, wrap crash-prone checks in `forked_test()` to avoid hangs/crashes.
  - Memory-failure simulation: tests set `g_malloc_wrap_enabled` and `g_malloc_fail_at` and rely on `__wrap_malloc`. When adding allocation tests, ensure you reset wrapper flags to avoid cross-test contamination.

- Key heuristics for modifications
  - If you change message formats printed by `print_test_results`, keep the exit/return behaviour identical — some scripts parse `.results` output.
  - When adding new test files, follow the naming pattern `*_tests.c` and update `run.sh` compile calls only if new files must be compiled separately.
  - When fixing a failing test locally, run `./run.sh -v` and inspect `.results` and temporary valgrind log (look in `/tmp/libft_fairy_*` during the run) to reproduce leak traces.

- Platform / environment
  - The tester assumes Linux (uses `fork`, `nm`, `valgrind`, `stat`). Keep portability changes separate and document them in README.

If any of the above is unclear or you want more examples (e.g. a short template for adding a new function test including fork/valgrind-safe patterns), tell me which section to expand and I'll iterate.
