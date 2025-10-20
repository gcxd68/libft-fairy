#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define VERBOSE	0

#define GREEN	"\033[0;32m"
#define RED		"\033[0;31m"
#define RESET	"\033[0m"

int g_tests_failed = 0;

static  int forked_test(void (*test_func)(void)) {
	pid_t pid;
	int status;

	fflush(stdout);
	if ((pid = fork()) == -1) {
		perror("libft-fairy: fork failed");
		exit(EXIT_FAILURE);
	}
	if (!pid) {
		test_func();
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return 1;
	return 0;
}

static int	all_tests_passed(const int *passed, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (passed[i] == 0)
			return 0;
	}
	return 1;
}

static void	print_test_header(const char *function_name) {
	printf("\n========================================\n");
	printf("%s\n", function_name);
	printf("========================================\n");
}

static void	print_result(const char *test_name, int passed) {
	printf("%s" RESET "%s\n", passed ? GREEN "✓ " : RED "✗ ", test_name);
	if (!passed)
		g_tests_failed++;
}

static void	test_ft_isalpha(void) {
	const int	passed[5] = {
		ft_isalpha('a'),
		ft_isalpha('Z'),
		!ft_isalpha('0'),
		!ft_isalpha(' '),
		!ft_isalpha('@')
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isalpha");
	print_result("Test 'a'", passed[0]);
	print_result("Test 'Z'", passed[1]);
	print_result("Test '0'", passed[2]);
	print_result("Test ' '", passed[3]);
	print_result("Test '@'", passed[4]);
}

static void	test_ft_isdigit(void) {
	const int	passed[4] = {
		ft_isdigit('0'),
		ft_isdigit('9'),
		!ft_isdigit('a'),
		!ft_isdigit(' ')
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isdigit");
	print_result("Test '0'", passed[0]);
	print_result("Test '9'", passed[1]);
	print_result("Test 'a'", passed[2]);
	print_result("Test ' '", passed[3]);
}

static void	test_ft_isalnum(void) {
	const int	passed[5] = {
		ft_isalnum('a'),
		ft_isalnum('Z'),
		ft_isalnum('5'),
		!ft_isalnum(' '),
		!ft_isalnum('@')
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isalnum");
	print_result("Test 'a'", passed[0]);
	print_result("Test 'Z'", passed[1]);
	print_result("Test '5'", passed[2]);
	print_result("Test ' '", passed[3]);
	print_result("Test '@'", passed[4]);
}

static void	test_ft_isascii(void) {
	const int	passed[5] = {
		ft_isascii(0),
		ft_isascii(127),
		!ft_isascii(128),
		!ft_isascii(-1),
		ft_isascii('a')
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isascii");
	print_result("Test 0", passed[0]);
	print_result("Test 127", passed[1]);
	print_result("Test 128", passed[2]);
	print_result("Test -1", passed[3]);
	print_result("Test 'a'", passed[4]);
}

static void	test_ft_isprint(void) {
	const int	passed[5] = {
		ft_isprint(' '),
		ft_isprint('~'),
		!ft_isprint(31),
		!ft_isprint(127),
		ft_isprint('a')
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isprint");
	print_result("Test ' '", passed[0]);
	print_result("Test '~'", passed[1]);
	print_result("Test 31", passed[2]);
	print_result("Test 127", passed[3]);
	print_result("Test 'a'", passed[4]);
}

static void ft_strlen_null_test(void) {
	ft_strlen(NULL);
}

static void	test_ft_strlen(void) {
	const int	passed[5] = {
		!ft_strlen(""),
		ft_strlen("hello") == 5,
		ft_strlen("42") == 2,
		ft_strlen("Hello, World!") == 13,
		forked_test(ft_strlen_null_test)
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strlen");
	print_result("Test empty string", passed[0]);
	print_result("Test 'hello'", passed[1]);
	print_result("Test '42'", passed[2]);
	print_result("Test long string", passed[3]);
	print_result("Test NULL", passed[4]);
}

static void ft_memset_null_test(void) {
	ft_memset(NULL, 0, 5);
}

static void	test_ft_memset(void) {
	char	str1[10] = {0};
	char	str2[10] = {0};
	void	*ret;
	int		passed[3];

	ret = ft_memset(str1, 'A', 5);
	memset(str2, 'A', 5);
	passed[0] = !memcmp(str1, str2, 10) && ret == str1;
	ret = ft_memset(str1, 0, 10);
	memset(str2, 0, 10);
	passed[1] = !memcmp(str1, str2, 10) && ret == str1;
	passed[2] = forked_test(ft_memset_null_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_memset");
	print_result("Test basic memset", passed[0]);
	print_result("Test memset with 0", passed[1]);
	print_result("Test memset with NULL", passed[2]);
}

static void	test_ft_bzero(void) {
	char	str[10];
	int		passed[2];

	memset(str, 'A', 10);
	ft_bzero(str, 5);

	passed[0] = 1;
	for (int i = 0; passed[0] && i < 5; i++)
		if (str[i])
			passed[0] = 0;
	for (int i = 5; passed[0] && i < 10; i++)
		if (str[i] != 'A')
			passed[0] = 0;
	ft_bzero(str, 10);
	passed[1] = 1;
	for (int i = 0; passed[0] && i < 10; i++)
		if (str[i])
			passed[0] = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_bzero");
	print_result("Test bzero 5 bytes", passed[0]);
	print_result("Test bzero all", passed[1]);
}

static void ft_memcpy_null_test(void) {
	char	buffer[10];

	ft_memcpy((void *)buffer, NULL, 5);
}

static void	test_ft_memcpy(void) {
	char	src[] = "Hello, World!";
	char	dst1[20] = {0};
	char	dst2[20] = {0};
	int		passed[3];

	ft_memcpy(dst1, src, strlen(src) + 1);
	memcpy(dst2, src, strlen(src) + 1);
	passed[0] = !strcmp(dst1, dst2);
	ft_memcpy(dst1, "42", 2);
	passed[1] = dst1[0] == '4' && dst1[1] == '2';
	passed[2] = forked_test(ft_memcpy_null_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_memcpy");
	print_result("Test basic memcpy", passed[0]);
	print_result("Test partial copy", passed[1]);
	print_result("Test NULL", passed[2]);
}

static void ft_memmove_null_test(void) {
	char	buffer[10];

	ft_memmove((void *)buffer, NULL, 5);
}

static void test_ft_memmove(void) {
	char	str1[] = "Hello, World!";
	char	str2[] = "Hello, World!";
	char	dst1[20] = {0};
	char	dst2[20] = {0};
	int		passed[7];

	ft_memmove(str1 + 2, str1, 5);
	memmove(str2 + 2, str2, 5);
	passed[0] = !strcmp(str1, str2);
	strcpy(str1, "Hello, World!");
	strcpy(str2, "Hello, World!");
	ft_memmove(str1, str1 + 2, 5);
	memmove(str2, str2 + 2, 5);
	passed[1] = !strcmp(str1, str2);
	ft_memmove(dst1, "Hello", 5);
	memmove(dst2, "Hello", 5);
	passed[2] = !memcmp(dst1, dst2, 5);
	strcpy(str1, "Hello");
	strcpy(str2, "Hello");
	ft_memmove(str1, str1, 5);
	memmove(str2, str2, 5);
	passed[3] = !strcmp(str1, str2);
	strcpy(str1, "Hello");
	strcpy(str2, "Hello");
	ft_memmove(str1 + 2, str1, 0);
	memmove(str2 + 2, str2, 0);
	passed[4] = !strcmp(str1, str2);
	strcpy(str1, "abcdef");
	strcpy(str2, "abcdef");
	ft_memmove(str1 + 1, str1, 5);
	memmove(str2 + 1, str2, 5);
	passed[5] = !strcmp(str1, str2);
	passed[6] = forked_test(ft_memmove_null_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_memmove");
	print_result("Test overlapping forward", passed[0]);
	print_result("Test overlapping backward", passed[1]);
	print_result("Test no overlap", passed[2]);
	print_result("Test dst == src", passed[3]);
	print_result("Test n = 0", passed[4]);
	print_result("Test minimal overlap", passed[5]);
	print_result("Test NULL", passed[6]);
}

static void	test_ft_strlcpy(void) {
	char	dst[10];
	size_t	len;
	int		passed[3];

	len = ft_strlcpy(dst, "Hello", 20);
	passed[0] = !strcmp(dst, "Hello") && len == 5;
	len = ft_strlcpy(dst, "Hello, World!", 6);
	passed[1] = !strcmp(dst, "Hello") && len == 13;
	len = ft_strlcpy(dst, "42", 0);
	passed[2] = len == 2;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strlcpy");
	print_result("Test basic copy", passed[0]);
	print_result("Test truncation", passed[1]);
	print_result("Test size 0", passed[2]);
}

static void	test_ft_strlcat(void) {
	char	dst[20];
	size_t	len;
	int		passed[8];
	
	strcpy(dst, "Hello");
	len = ft_strlcat(dst, " World", 20);
	passed[0] = !strcmp(dst, "Hello World") && len == 11;
	strcpy(dst, "Hello");
	len = ft_strlcat(dst, " World!", 10);
	passed[1] = !strcmp(dst, "Hello Wor") && len == 12;
	strcpy(dst, "Hello");
	len = ft_strlcat(dst, " World", 5);
	passed[2] = !strcmp(dst, "Hello") && len == 11;
	strcpy(dst, "Hello");
	len = ft_strlcat(dst, " World", 3);
	passed[3] = !strcmp(dst, "Hello") && len == 9;
	strcpy(dst, "Hello");
	len = ft_strlcat(dst, " World", 0);
	passed[4] = !strcmp(dst, "Hello") && len == 6;
	strcpy(dst, "Hello");
	len = ft_strlcat(dst, "", 20);
	passed[5] = !strcmp(dst, "Hello") && len == 5;
	dst[0] = '\0';
	len = ft_strlcat(dst, "Hello", 20);
	passed[6] = !strcmp(dst, "Hello") && len == 5;
	strcpy(dst, "Hello");
	len = ft_strlcat(dst, "X", 6);
	passed[7] = !strcmp(dst, "Hello") && len == 6;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strlcat");
	print_result("Test basic concat", passed[0]);
	print_result("Test truncation", passed[1]);
	print_result("Test dstsize = strlen(dst)", passed[2]);
	print_result("Test dstsize < strlen(dst)", passed[3]);
	print_result("Test dstsize = 0", passed[4]);
	print_result("Test empty src", passed[5]);
	print_result("Test empty dst", passed[6]);
	print_result("Test no room for concat", passed[7]);
}

static void	test_ft_toupper(void) {
	const int	passed[4] = {
		ft_toupper('a') == 'A',
		ft_toupper('z') == 'Z',
		ft_toupper('A') == 'A',
		ft_toupper('0') == '0'
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_toupper");
	print_result("Test 'a'", passed[0]);
	print_result("Test 'z'", passed[1]);
	print_result("Test 'A'", passed[2]);
	print_result("Test '0'", passed[3]);
}

static void	test_ft_tolower(void) {
	const int	passed[4] = {
		ft_tolower('A') == 'a',
		ft_tolower('Z') == 'z',
		ft_tolower('a') == 'a',
		ft_tolower('0') == '0'
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_tolower");
	print_result("Test 'A'", passed[0]);
	print_result("Test 'Z'", passed[1]);
	print_result("Test 'a'", passed[2]);
	print_result("Test '0'", passed[3]);
}

static void ft_strchr_null_test(void) {
	ft_strchr(NULL, 'a');
}

static void	test_ft_strchr(void)
{
	const char	*str = "Hello, World!";
	const int	passed[5] = {
		ft_strchr(str, 'o') == strchr(str, 'o'),
		ft_strchr(str, 'W') == strchr(str, 'W'),
		ft_strchr(str, '\0') == strchr(str, '\0'),
		!ft_strchr(str, 'x'),
		forked_test(ft_strchr_null_test)
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strchr");
	print_result("Test find 'o'", passed[0]);
	print_result("Test find 'W'", passed[1]);
	print_result("Test find '\\0'", passed[2]);
	print_result("Test not found 'x'", passed[3]);
	print_result("Test NULL", passed[4]);
}

static void ft_strrchr_null_test(void) {
	ft_strrchr(NULL, 'a');
}

static void	test_ft_strrchr(void) {
	const char	*str = "Hello, World!";
	const int	passed[5] = {
		ft_strrchr(str, 'o') == strrchr(str, 'o'),
		ft_strrchr(str, 'W') == strrchr(str, 'W'),
		ft_strrchr(str, '\0') == strrchr(str, '\0'),
		!ft_strrchr(str, 'x'),
		forked_test(ft_strrchr_null_test)
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strrchr");
	print_result("Test find last 'o'", passed[0]);
	print_result("Test find 'W'", passed[1]);
	print_result("Test find '\\0'", passed[2]);
	print_result("Test not found 'x'", passed[3]);
	print_result("Test NULL", passed[4]);
}

static void ft_strncmp_null_test(void) {
	ft_strncmp(NULL, "abc", 3);
}

static void	test_ft_strncmp(void) {
	const int	passed[8] = {
		!ft_strncmp("Hello", "Hello", 5),
		ft_strncmp("Hello", "World", 5),
		!ft_strncmp("Hello", "Help", 3),
		!ft_strncmp("Hello", "World", 0),
		!ft_strncmp("Hello", "Hello\0test", 10),
		ft_strncmp("test\200", "test\0", 6) > 0,
		ft_strncmp("abc", "abcd", 5) < 0,
		forked_test(ft_strncmp_null_test)
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strncmp");
	print_result("Test equal strings", passed[0]);
	print_result("Test different strings", passed[1]);
	print_result("Test partial compare", passed[2]);
	print_result("Test n=0", passed[3]);
	print_result("Test with \\0", passed[4]);
	print_result("Test unsigned char comparison", passed[5]);
	print_result("Test n > strlen", passed[6]);
	print_result("Test NULL", passed[7]);
}

static void	test_ft_memchr(void) {
	const char	*str = "Hello, World!";
	const int	passed[5] = {
		ft_memchr(str, 'o', 13) == memchr(str, 'o', 13),
		ft_memchr(str, 'W', 13) == memchr(str, 'W', 13),
		!ft_memchr(str, 'x', 13),
		!ft_memchr(str, 'H', 0),
		ft_memchr(str, '\0', 14) == memchr(str, '\0', 14)
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_memchr");
	print_result("Test find 'o'", passed[0]);
	print_result("Test find 'W'", passed[1]);
	print_result("Test not found", passed[2]);
	print_result("Test n=0", passed[3]);
	print_result("Test find '\\0'", passed[4]);
}

static void	test_ft_memcmp(void) {
	char	buf1[] = {1, 2, 3, 4, 5};
	char	buf2[] = {1, 2, 3, 4, 6};
	const int passed[4] = {
		!ft_memcmp("Hello", "Hello", 5),
		ft_memcmp("Hello", "World", 5),
		!ft_memcmp("Hello", "World", 0),
		ft_memcmp(buf1, buf2, 5) < 0
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_memcmp");
	print_result("Test equal", passed[0]);
	print_result("Test different", passed[1]);
	print_result("Test n=0", passed[2]);
	print_result("Test binary data", passed[3]);
}

static void	test_ft_strnstr(void) {
	const char	*haystack = "Hello, World!";
	const int	passed[5] = {
		ft_strnstr(haystack, "World", 13) != NULL,
		ft_strnstr(haystack, "o", 13) != NULL,
		!ft_strnstr(haystack, "xyz", 13),
		ft_strnstr(haystack, "", 13) == haystack,
		!ft_strnstr(haystack, "World", 5)
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strnstr");
	print_result("Test find 'World'", passed[0]);
	print_result("Test find 'o'", passed[1]);
	print_result("Test not found", passed[2]);
	print_result("Test empty needle", passed[3]);
	print_result("Test len too short", passed[4]);
}

static void ft_atoi_overflow_test(void) {
	ft_atoi("9999999999999999999");
}

static void ft_atoi_null_test(void) {
	ft_atoi(NULL);
}

static void	test_ft_atoi(void) {
	const int	passed[12] = {
		ft_atoi("  \t\n\v\f\r +42") == 42,
		ft_atoi("     -42*") == -42,
		!ft_atoi("0"),
		!ft_atoi("++2"),
		!ft_atoi("--4"),
		!ft_atoi("-+9"),
		!ft_atoi("+-8"),
		!ft_atoi(" \t-R66"),
		ft_atoi("2147483647") == 2147483647,
		ft_atoi("-2147483648") == -2147483648,
		!forked_test(ft_atoi_overflow_test),
		forked_test(ft_atoi_null_test)
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_atoi");
	print_result("Test '  \\t\\n\\v\\f\\r +42'", passed[0]);
	print_result("Test '-42*'", passed[1]);
	print_result("Test '0'", passed[2]);
	print_result("Test '++2'", passed[3]);
	print_result("Test '--4'", passed[4]);
	print_result("Test '-+9'", passed[5]);
	print_result("Test '+-8'", passed[6]);
	print_result("Test '\\t-R66'", passed[7]);
	print_result("Test INT_MAX", passed[8]);
	print_result("Test INT_MIN", passed[9]);
	print_result("Test overflow", passed[10]);
	print_result("Test NULL", passed[11]);
}

static void ft_calloc_overflow_write_test(void) {
	const size_t	size_max = ~(size_t)0;
	char			*ptr = ft_calloc(size_max >> 1, size_max >> 1);

	ptr[0] = 'x';
}

static void ft_calloc_overflow_free_test(void) {
	const size_t	size_max = ~(size_t)0;
	char			*ptr = ft_calloc(size_max >> 1, size_max >> 1);

	free(ptr);
}

static void ft_calloc_zero_count_test(void) {
	void	*ptr = ft_calloc(0, 5);

	free(ptr);
}

static void ft_calloc_zero_size_test(void) {
	void	*ptr = ft_calloc(5, 0);

	free(ptr);
}

static void	test_ft_calloc(void) {
	int	*arr = ft_calloc(5, sizeof(int));
	int	passed[6];

	passed[0] = 1;
	for (int i = 0; i < 5; i++)
		if (arr[i] != 0)
			passed[0] = 0;
	free(arr);
	char *str = ft_calloc(10, sizeof(char));
	passed[1] = str != NULL;
	free(str);
	passed[2] = forked_test(ft_calloc_overflow_write_test);
	passed[3] = !forked_test(ft_calloc_overflow_free_test);
	passed[4] = !forked_test(ft_calloc_zero_count_test);
	passed[5] = !forked_test(ft_calloc_zero_size_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_calloc");
	print_result("Test all zeros", passed[0]);
	print_result("Test allocated", passed[1]);
	print_result("Test overflow write", passed[2]);
	print_result("Test overflow free", passed[3]);
	print_result("Test count = 0", passed[4]);
	print_result("Test size = 0", passed[5]);
}

static void ft_strdup_empty_test(void) {
	char	*dup = ft_strdup("");

	dup[0] = 'a';
	free(dup);
}

static void	test_ft_strdup(void) {
	char	*dup = ft_strdup("Hello");
	int		passed[3];

	passed[0] = !strcmp(dup, "Hello");
	free(dup);
	dup = ft_strdup("42");
	passed[1] = !strcmp(dup, "42");
	free(dup);
	passed[2] = !forked_test(ft_strdup_empty_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strdup");
	print_result("Test basic dup", passed[0]);
	print_result("Test short string", passed[1]);
	print_result("Test empty string", passed[2]);
}

static void ft_substr_null_test(void) {
	ft_substr(NULL, 0, 5);
}

static void ft_substr_empty_test(void) {
	char	*sub1 = ft_substr("Hello", 10, 5);
	char	*sub2 = ft_substr("test", 0, 0);

	sub1[0] = 'a';
	free(sub1);
	sub2[0] = 'a';
	free(sub2);
}

static void	test_ft_substr(void) {
	char	*sub = ft_substr("Hello, World!", 7, 5);
	int		passed[7];

	passed[0] = !strcmp(sub, "World");
	free(sub);
	sub = ft_substr("Hello", 0, 3);
	passed[1] = !strcmp(sub, "Hel");
	free(sub);
	sub = ft_substr("Hello", 10, 5);
	passed[2] = !strcmp(sub, "");
	free(sub);
	sub = ft_substr("Hello", 2, 100);
	passed[3] = !strcmp(sub, "llo");
	free(sub);
	sub = ft_substr("test", 0, 0);
	passed[4] = !strcmp(sub, "");
	free(sub);
	passed[5] = !forked_test(ft_substr_null_test);
	passed[6] = !forked_test(ft_substr_empty_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_substr");
	print_result("Test basic substr", passed[0]);
	print_result("Test from start", passed[1]);
	print_result("Test start > len", passed[2]);
	print_result("Test len too long", passed[3]);
	print_result("Test len = 0", passed[4]);
	print_result("Test NULL", passed[5]);
	print_result("Test empty string alloc", passed[6]);
}

static void	test_ft_strjoin(void) {
	char	*joined = ft_strjoin("Hello", " World");
	int		passed[4];

	passed[0] = !strcmp(joined, "Hello World");
	free(joined);
	joined = ft_strjoin("", "Hello");
	passed[1] = !strcmp(joined, "Hello");
	free(joined);
	joined = ft_strjoin("Hello", "");
	passed[2] = !strcmp(joined, "Hello");
	free(joined);
	joined = ft_strjoin("42", "!");
	passed[3] = !strcmp(joined, "42!");
	free(joined);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strjoin");
	print_result("Test basic join", passed[0]);
	print_result("Test empty s1", passed[1]);
	print_result("Test empty s2", passed[2]);
	print_result("Test short strings", passed[3]);
}

static void ft_strtrim_empty_string_test(void) {
	ft_strtrim("", " ");
}

static void ft_strtrim_all_trim_test(void) {
	ft_strtrim("xxxxx", "x");
}

static void ft_strtrim_null_input_test(void) {
	ft_strtrim(NULL, " ");
}

static void ft_strtrim_null_set_test(void) {
	ft_strtrim("test", NULL);
}

static void	test_ft_strtrim(void) {
	char	*trimmed = ft_strtrim("   Hello   ", " ");
	int		passed[7];

	passed[0] = !strcmp(trimmed, "Hello");
	free(trimmed);
	trimmed = ft_strtrim("xxxHelloxxx", "x");
	passed[1] = !strcmp(trimmed, "Hello");
	free(trimmed);
	trimmed = ft_strtrim("Hello", "xyz");
	passed[2] = !strcmp(trimmed, "Hello");
	free(trimmed);
	passed[3] = !forked_test(ft_strtrim_empty_string_test);
	passed[4] = !forked_test(ft_strtrim_all_trim_test);
	passed[5] = !forked_test(ft_strtrim_null_input_test);
	passed[6] = !forked_test(ft_strtrim_null_set_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strtrim");
	print_result("Test spaces", passed[0]);
	print_result("Test custom set", passed[1]);
	print_result("Test no trim", passed[2]);
	print_result("Test empty string", passed[3]);
	print_result("Test all trim", passed[4]);
	print_result("Test NULL input", passed[5]);
	print_result("Test NULL set", passed[6]);
}

static void	free_arr(char **arr) {
	if (arr) {
		for (int i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
	}
}

static void	test_ft_split(void) {
	char	**arr;
	int		passed[9];

	arr = ft_split("Hello World 42", ' ');
	passed[0] = arr && !strcmp(arr[0], "Hello") && !strcmp(arr[1], "World") && !strcmp(arr[2], "42") && !arr[3];
	free_arr(arr);
	arr = ft_split("___Hello___World___", '_');
	passed[1] = arr && !strcmp(arr[0], "Hello") && !strcmp(arr[1], "World") && !arr[2];
	free_arr(arr);
	arr = ft_split("", ' ');
	passed[2] = arr && !arr[0];
	free_arr(arr);
	arr = ft_split("", 'x');
	passed[3] = arr && !arr[0];
	free_arr(arr);
	arr = ft_split("xxx", 'x');
	passed[4] = arr && !arr[0];
	free_arr(arr);
	arr = ft_split("Hello", '\0');
	passed[5] = arr && !strcmp(arr[0], "Hello") && !arr[1];
	free_arr(arr);
	arr = ft_split("   ", ' ');
	passed[6] = arr && !arr[0];
	free_arr(arr);
	arr = ft_split("HelloWorld", ' ');
	passed[7] = arr && !strcmp(arr[0], "HelloWorld") && !arr[1];
	free_arr(arr);
	arr = ft_split("Hello   World", ' ');
	passed[8] = arr && !strcmp(arr[0], "Hello") && !strcmp(arr[1], "World") && !arr[2];
	free_arr(arr);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_split");
	print_result("Test basic split", passed[0]);
	print_result("Test multiple delimiters", passed[1]);
	print_result("Test empty string", passed[2]);
	print_result("Test empty string with 'x'", passed[3]);
	print_result("Test all delimiters", passed[4]);
	print_result("Test delimiter = '\\0'", passed[5]);
	print_result("Test only spaces", passed[6]);
	print_result("Test no delimiter found", passed[7]);
	print_result("Test consecutive delimiters", passed[8]);
}

static void	test_ft_itoa(void) {
	char	*str = ft_itoa(42);
	int		passed[5];

	passed[0] = !strcmp(str, "42");
	free(str);
	str = ft_itoa(-42);
	passed[1] = !strcmp(str, "-42");
	free(str);
	str = ft_itoa(0);
	passed[2] = !strcmp(str, "0");
	free(str);
	str = ft_itoa(-2147483648);
	passed[3] = !strcmp(str, "-2147483648");
	free(str);
	str = ft_itoa(2147483647);
	passed[4] = !strcmp(str, "2147483647");
	free(str);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_itoa");
	print_result("Test 42", passed[0]);
	print_result("Test -42", passed[1]);
	print_result("Test 0", passed[2]);
	print_result("Test INT_MIN", passed[3]);
	print_result("Test INT_MAX", passed[4]);
}

static char mapi_func(unsigned int i, char c) {
	return c + i;
}

static void ft_strmapi_null_func_test(void) {
	ft_strmapi("test", NULL);
}

static void test_ft_strmapi(void) {
	char	*result = ft_strmapi("abc", mapi_func);
	int		passed[3];

	passed[0] = result && result[0] == 'a' && result[1] == 'c' && result[2] == 'e';
	free(result);
	result = ft_strmapi("", mapi_func);
	passed[1] = result && !strcmp(result, "");
	free(result);
	passed[2] = !forked_test(ft_strmapi_null_func_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strmapi");
	print_result("Test basic", passed[0]);
	print_result("Test empty string", passed[1]);
	print_result("Test f = NULL", passed[2]);
}

static void	iteri_func(unsigned int i, char *c) {
	*c = *c + i;
}

static void ft_striteri_null_func_test(void) {
	ft_striteri("test", NULL);
}

static void	test_ft_striteri(void) {
	char	str[] = "abc";
	int		passed[2];

	ft_striteri(str, iteri_func);
	passed[0] = str[0] == 'a' && str[1] == 'c' && str[2] == 'e';
	passed[1] = !forked_test(ft_striteri_null_func_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_striteri");
	print_result("Test basic striteri", passed[0]);
	print_result("Test f = NULL", passed[1]);
}

static int	test_fd_output(void (*func)(void *, int), void *input, 
							const char *expected, size_t read_len) {
	char	buf[50] = {0};
	int		fd;
	int		result;

	fd = open("/tmp/test_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	func(input, fd);
	close(fd);
	fd = open("/tmp/test_fd", O_RDONLY);
	read(fd, buf, read_len);
	buf[read_len] = '\0';
	close(fd);
	unlink("/tmp/test_fd");
	result = !strcmp(buf, expected);
	return (result);
}

static void	wrapper_putchar(void *c, int fd) {
	ft_putchar_fd(*(char *)c, fd);
}

static void	wrapper_putstr(void *s, int fd) {
	ft_putstr_fd((char *)s, fd);
}

static void	wrapper_putendl(void *s, int fd) {
	ft_putendl_fd((char *)s, fd);
}

static void	wrapper_putnbr(void *n, int fd) {
	ft_putnbr_fd(*(int *)n, fd);
}

static void	test_ft_putchar_fd(void) {
	char	c = '0';
	int		passed[2];

	char	buf[10];
	int		fd = open("/tmp/test_putchar", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putchar_fd('A', fd);
	ft_putchar_fd('B', fd);
	close(fd);
	fd = open("/tmp/test_putchar", O_RDONLY);
	read(fd, buf, 2);
	buf[2] = '\0';
	close(fd);
	unlink("/tmp/test_putchar");
	passed[0] = !strcmp(buf, "AB");
	passed[1] = test_fd_output(wrapper_putchar, &c, "0", 1);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_putchar_fd");
	print_result("Test 'A' and 'B'", passed[0]);
	print_result("Test '0'", passed[1]);
}

static void	test_ft_putstr_fd(void) {
	int	passed[2];

	passed[0] = test_fd_output(wrapper_putstr, "Hello, World!", "Hello, World!", 13);
	passed[1] = test_fd_output(wrapper_putstr, "42", "42", 2);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_putstr_fd");
	print_result("Test 'Hello, World!'", passed[0]);
	print_result("Test '42'", passed[1]);
}

static void	test_ft_putendl_fd(void) {
	int	passed[2];

	passed[0] = test_fd_output(wrapper_putendl, "Hello", "Hello\n", 6);
	passed[1] = test_fd_output(wrapper_putendl, "", "\n", 1);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_putendl_fd");
	print_result("Test 'Hello' with newline", passed[0]);
	print_result("Test empty string with newline", passed[1]);
}

static void	test_ft_putnbr_fd(void) {
	int	n1 = 42, n2 = -42, n3 = 0, n4 = -2147483648, n5 = 2147483647;
	int	passed[5];

	passed[0] = test_fd_output(wrapper_putnbr, &n1, "42", 2);
	passed[1] = test_fd_output(wrapper_putnbr, &n2, "-42", 3);
	passed[2] = test_fd_output(wrapper_putnbr, &n3, "0", 1);
	passed[3] = test_fd_output(wrapper_putnbr, &n4, "-2147483648", 11);
	passed[4] = test_fd_output(wrapper_putnbr, &n5, "2147483647", 10);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_putnbr_fd");
	print_result("Test 42", passed[0]);
	print_result("Test -42", passed[1]);
	print_result("Test 0", passed[2]);
	print_result("Test INT_MIN", passed[3]);
	print_result("Test INT_MAX", passed[4]);
}

int main(void) {
	test_ft_isalpha();
	test_ft_isdigit();
	test_ft_isalnum();
	test_ft_isascii();
	test_ft_isprint();
	test_ft_strlen();
	test_ft_memset();
	test_ft_bzero();
	test_ft_memcpy();
	test_ft_memmove();
	test_ft_strlcpy();
	test_ft_strlcat();
	test_ft_toupper();
	test_ft_tolower();
	test_ft_strchr();
	test_ft_strrchr();
	test_ft_strncmp();
	test_ft_memchr();
	test_ft_memcmp();
	test_ft_strnstr();
	test_ft_atoi();
	test_ft_calloc();
	test_ft_strdup();
	test_ft_substr();
	test_ft_strjoin();
	test_ft_strtrim();
	test_ft_split();
	test_ft_itoa();
	test_ft_strmapi();
	test_ft_striteri();
	test_ft_putchar_fd();
	test_ft_putstr_fd();
	test_ft_putendl_fd();
	test_ft_putnbr_fd();
	return (g_tests_failed ? 1 : 0);
}
