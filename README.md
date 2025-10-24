# 🧚 libft-fairy

A comprehensive tester for 42's **libft** project, featuring memory leak detection and edge case testing.

## ✨ Features

- ✅ Complete tests for all functions (mandatory + bonus)
- 🔍 Automatic verification with **norminette**
- 💧 Memory leak detection with **Valgrind**
- 🚨 Edge case testing (NULL, overflow, boundary cases)
- 🧪 Malloc failure simulation
- 📊 Clear and colorful output
- 🔇 Optional verbose mode for detailed results

## 📋 Prerequisites

Before using libft-fairy, make sure you have installed:

- `gcc`
- `make`
- `valgrind`
- `norminette`
- `bash`

## 🚀 Installation

1. Clone the repository inside your libft directory:

```bash
git clone https://github.com/gcxd68/libft-fairy.git
```

2. Navigate to the tester folder:

```bash
cd libft-fairy
```

3. Make the script executable:

```bash
chmod +x run.sh
```

## 🎯 Usage

### Run all tests

```bash
./run.sh
```

### Verbose mode (displays all tests, even passing ones)

```bash
./run.sh --verbose
# or
./run.sh -v
```

## 📊 Output

The tester displays:

```
╔════════════════════════════╗
║       LIBFT-FAIRY 🧚       ║
╚════════════════════════════╝

📝 Checking norm...     Done
📦 Compiling libft...   Done (bonus)
🔨 Compiling tests...   Done
🧪 Running tests...     Done

========================================
ft_isalpha
========================================
[OK]  Tests EOF to '?'
[OK]  Tests 'A' to 'Z'
...

╔════════════════════════════╗
║     OH MY, YOU PASSED!     ║
╚════════════════════════════╝
```

On failure, details of failed tests will be displayed, along with Valgrind logs if memory leaks are detected.

## 🧪 Tests Covered

### Mandatory functions

- Character checks: `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`
- String manipulation: `ft_strlen`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_strlcpy`, `ft_strlcat`
- Memory operations: `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`
- Conversion: `ft_atoi`, `ft_toupper`, `ft_tolower`
- Allocation: `ft_calloc`, `ft_strdup`
- String creation: `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`
- Iteration: `ft_strmapi`, `ft_striteri`
- File descriptors: `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`

### Bonus functions

- `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`
- `ft_lstsize`, `ft_lstlast`
- `ft_lstdelone`, `ft_lstclear`
- `ft_lstiter`, `ft_lstmap`

### Edge cases tested

- ❌ NULL pointers
- 🔢 Boundary values (`INT_MIN`, `INT_MAX`, `UINT_MAX`)
- 🔤 Non-ASCII characters (200, 255, -1)
- 📏 Empty strings and zero sizes
- 🔄 Memory overlaps (`ft_memmove`)
- 💥 Simulated malloc failures
- 💧 Memory leaks (Valgrind)

## 📁 Project Structure

```
libft-fairy/
├── run.sh                    # Main script
├── basic_tests.c             # Mandatory function tests
├── basic_tests_bonus.c       # Bonus function tests
├── leak_tests.c              # Leak tests (mandatory)
├── leak_tests_bonus.c        # Leak tests (bonus)
├── utils.c                   # Utility functions
├── libft_fairy.h             # Header file
└── README.md                 # This file
```

## 🐛 Debugging

If a test fails:

1. **Verbose mode**: Run `./run.sh -v` to see all details
2. **Valgrind**: Complete logs are displayed if leaks are detected
3. **Norminette**: Norm errors are shown directly

## ⚠️ Limitations

- Tested only on Linux (uses `fork` and Valgrind)
- Requires specific directory structure (tester in libft subfolder)
- Assumes your `libft.h` contains standard prototypes

## 🤝 Contributing

Contributions are welcome! Feel free to:

- Open an issue to report a bug
- Suggest new tests
- Improve documentation

## 📜 License

This project is free to use.

## 💖 Credits

Created with ✨ by **gcxd68**.

---

*If libft-fairy helped you, don't forget to leave a ⭐ on the repo!*
