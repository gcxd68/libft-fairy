#include "libft_fairy.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#ifndef VERBOSE
# define VERBOSE 0
#endif

static void	test_ft_isalpha(void) {
	int c = -1;
	int	passed[5] = {1, 1, 1, 1, 1};

	while (passed[0] && c < 'A')
		if (ft_isalpha(c++))
			passed[0] = 0;
	while (passed[1] && c <= 'Z')
		if (!ft_isalpha(c++))
			passed[1] = 0;
	while (passed[2] && c < 'a')
		if (ft_isalpha(c++))
			passed[2] = 0;
	while (passed[3] && c <= 'z')
		if (!ft_isalpha(c++))
			passed[3] = 0;
	while (passed[4] && c < 256)
		if (ft_isalpha(c++))
			passed[4] = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isalpha");
	print_result("Tests EOF to '?'", passed[0]);
	print_result("Tests 'A' to 'Z'", passed[1]);
	print_result("Tests '[' to '`'", passed[2]);
	print_result("Tests 'a' to 'z'", passed[3]);
	print_result("Tests '{' to 255", passed[4]);
}

static void	test_ft_isdigit(void) {
	int c = -1;
	int passed[3] = {1, 1, 1};

	while (passed[0] && c < '0')
		if (ft_isdigit(c++))
			passed[0] = 0;
	while (passed[1] && c <= '9')
		if (!ft_isdigit(c++))
			passed[1] = 0;
	while (passed[2] && c < 256)
		if (ft_isdigit(c++))
			passed[2] = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isdigit");
	print_result("Tests EOF to '/'", passed[0]);
	print_result("Tests '0' to '9'", passed[1]);
	print_result("Tests ':' to 255", passed[2]);
}

static void	test_ft_isalnum(void) {
	int c = -1;
	int passed[7] = {1, 1, 1, 1, 1, 1, 1};

	while (passed[0] && c < '0')
		if (ft_isalnum(c++))
			passed[0] = 0;
	while (passed[1] && c <= '9')
		if (!ft_isalnum(c++))
			passed[1] = 0;
	while (passed[2] && c < 'A')
		if (ft_isalnum(c++))
			passed[2] = 0;
	while (passed[3] && c <= 'Z')
		if (!ft_isalnum(c++))
			passed[3] = 0;
	while (passed[4] && c < 'a')
		if (ft_isalnum(c++))
			passed[4] = 0;
	while (passed[5] && c <= 'z')
		if (!ft_isalnum(c++))
			passed[5] = 0;
	while (passed[6] && c < 256)
		if (ft_isalnum(c++))
			passed[6] = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isalnum");
	print_result("Tests EOF to '/'", passed[0]);
	print_result("Tests '0' to '9'", passed[1]);
	print_result("Tests ':' to '?'", passed[2]);
	print_result("Tests 'A' to 'Z'", passed[3]);
	print_result("Tests '[' to '`'", passed[4]);
	print_result("Tests 'a' to 'z'", passed[5]);
	print_result("Tests '{' to 255", passed[6]);
}

static void	test_ft_isascii(void) {
	int c = 0;
	int passed[3] = {1, 1, 1};

	if (ft_isascii(-1))
		passed[0] = 0;
	while (passed[1] && c < 128)
		if (!ft_isascii(c++))
			passed[1] = 0;
	while (passed[2] && c < 256)
		if (ft_isascii(c++))
			passed[2] = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isascii");
	print_result("Test EOF", passed[0]);
	print_result("Tests '\\0' to DEL", passed[1]);
	print_result("Tests 128 to 255", passed[2]);
}

static void	test_ft_isprint(void) {
	int c = -1;
	int passed[3] = {1, 1, 1};

	while (passed[0] && c < ' ')
		if (ft_isprint(c++))
			passed[0] = 0;
	while (passed[1] && c <= '~')
		if (!ft_isprint(c++))
			passed[1] = 0;
	while (passed[2] && c < 256)
		if (ft_isprint(c++))
			passed[2] = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_isprint");
	print_result("Tests EOF to US", passed[0]);
	print_result("Tests ' ' to '~'", passed[1]);
	print_result("Tests DEL to 255", passed[2]);
}

static void	ft_strlen_null_test(void) {
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

static void	ft_memset_null_test(void) {
	ft_memset(NULL, 0, 5);
}

static void	test_ft_memset(void) {
	char	str1[10] = {0};
	char	str2[10] = {0};
	void	*ret;
	int		passed[4];

	ret = ft_memset(str1, 'A', 5);
	memset(str2, 'A', 5);
	passed[0] = !memcmp(str1, str2, 10) && ret == str1;
	ret = ft_memset(str1, 0, 10);
	memset(str2, 0, 10);
	passed[1] = !memcmp(str1, str2, 10) && ret == str1;
	memset(str1, 200, 10);
	ft_memset(str2, 200, 10);
	passed[2] = !memcmp(str1, str2, 10);
	passed[3] = forked_test(ft_memset_null_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_memset");
	print_result("Test basic memset", passed[0]);
	print_result("Test memset with 0", passed[1]);
	print_result("Test unsigned char fill (200)", passed[2]);
	print_result("Test NULL", passed[3]);
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
	for (int i = 0; passed[1] && i < 10; i++)
		if (str[i])
			passed[1] = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_bzero");
	print_result("Test bzero 5 bytes", passed[0]);
	print_result("Test bzero all", passed[1]);
}

static void	ft_memcpy_null_test(void) {
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

static void	ft_memmove_null_test(void) {
	char	buffer[10];

	ft_memmove((void *)buffer, NULL, 5);
}

static void	test_ft_memmove(void) {
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
	int c = -2;
	int	passed[3] = {1, 1, 1};

	while (passed[0] && ++c < 'a')
		if (ft_toupper(c) != c)
			passed[0] = 0;
	while (passed[1] && ++c <= 'z')
		if (ft_toupper(c) != c - 32)
			passed[1] = 0;
	while (passed[2] && ++c < 256)
		if (ft_toupper(c) != c)
			passed[2] = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_toupper");
	print_result("Tests EOF to '`'", passed[0]);
	print_result("Tests 'a' to 'z'", passed[1]);
	print_result("Tests '{' to 255", passed[2]);
}

static void	test_ft_tolower(void) {
	int c = -2;
	int	passed[3] = {1, 1, 1};

	while (passed[0] && ++c < 'A')
		if (ft_tolower(c) != c)
			passed[0] = 0;
	while (passed[1] && ++c <= 'Z')
		if (ft_tolower(c) != c + 32)
			passed[1] = 0;
	while (passed[2] && ++c < 256)
		if (ft_tolower(c) != c)
			passed[2] = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_tolower");
	print_result("Tests EOF to '@'", passed[0]);
	print_result("Tests 'A' to 'Z'", passed[1]);
	print_result("Tests '[' to 255", passed[2]);
}

static void	ft_strchr_null_test(void) {
	ft_strchr(NULL, 'a');
}

static void	test_ft_strchr(void) {
	const char	str[] = "Hello\xC8World";
	const int	passed[6] = {
		ft_strchr(str, 'o') == strchr(str, 'o'),
		ft_strchr(str, 'W') == strchr(str, 'W'),
		ft_strchr(str, '\0') == strchr(str, '\0'),
		!ft_strchr(str, 'x'),
		ft_strchr(str, 200) == strchr(str, 200),
		forked_test(ft_strchr_null_test)
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strchr");
	print_result("Test find 'o'", passed[0]);
	print_result("Test find 'W'", passed[1]);
	print_result("Test find '\\0'", passed[2]);
	print_result("Test not found 'x'", passed[3]);
	print_result("Test unsigned char comparison (200)", passed[4]);
	print_result("Test NULL", passed[5]);
}

static void	ft_strrchr_null_test(void) {
	ft_strrchr(NULL, 'a');
}

static void	test_ft_strrchr(void) {
	const char	str[] = "Hello\xC8World\xC8!";
	const int	passed[6] = {
		ft_strrchr(str, 'o') == strrchr(str, 'o'),
		ft_strrchr(str, 'W') == strrchr(str, 'W'),
		ft_strrchr(str, '\0') == strrchr(str, '\0'),
		!ft_strrchr(str, 'x'),
		ft_strrchr(str, 200) == strrchr(str, 200),
		forked_test(ft_strrchr_null_test)
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strrchr");
	print_result("Test find last 'o'", passed[0]);
	print_result("Test find 'W'", passed[1]);
	print_result("Test find '\\0'", passed[2]);
	print_result("Test not found 'x'", passed[3]);
	print_result("Test unsigned char comparison (200)", passed[4]);
	print_result("Test NULL", passed[5]);
}

static void	ft_strncmp_size_max_test(void) {
	const size_t	size_max = ~(size_t)0;

	if (ft_strncmp("abc", "abc", size_max))
		abort();
}

static void	ft_strncmp_null_test(void) {
	ft_strncmp(NULL, "abc", 3);
}

static void	test_ft_strncmp(void) {
	const int	passed[10] = {
		!ft_strncmp("Hello", "Hello", 5),
		ft_strncmp("Hello", "World", 5),
		!ft_strncmp("Hello", "Help", 3),
		!ft_strncmp("Hello", "World", 0),
		!ft_strncmp("Hello", "Hello\0test", 10),
		ft_strncmp("abc", "abcd", 5) < 0,
		ft_strncmp("test\200", "test\0", 6) > 0,
		ft_strncmp("test\xff", "test\x7f", 6) > 0,
		!forked_test(ft_strncmp_size_max_test),
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
	print_result("Test n > strlen", passed[5]);
	print_result("Test unsigned char comparison", passed[6]);
	print_result("Test unsigned char 255 vs 127", passed[7]);
	print_result("Test SIZE_MAX", passed[8]);
	print_result("Test NULL", passed[9]);
}

static void	ft_memchr_nullchar_test(void) {
	if (ft_memchr("Hello, World!", '\0', 14) != memchr("Hello, World!", '\0', 14))
		abort();
}

static void	test_ft_memchr(void) {
	const char			*str = "Hello, World!";
	const unsigned char	bin[] = {0, 128, 255, 42};
	const int			passed[6] = {
		ft_memchr(str, 'o', 13) == memchr(str, 'o', 13),
		ft_memchr(str, 'W', 13) == memchr(str, 'W', 13),
		!ft_memchr(str, 'x', 13),
		!ft_memchr(str, 'H', 0),
		!forked_test(ft_memchr_nullchar_test),
		ft_memchr(bin, 255, sizeof(bin)) == memchr(bin, 255, sizeof(bin))
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_memchr");
	print_result("Test find 'o'", passed[0]);
	print_result("Test find 'W'", passed[1]);
	print_result("Test not found", passed[2]);
	print_result("Test n=0", passed[3]);
	print_result("Test find '\\0'", passed[4]);
	print_result("Test unsigned char comparison (255)", passed[5]);
}


static void	test_ft_memcmp(void) {
	char		buf1[] = {1, 2, 3, 4, 5};
	char		buf2[] = {1, 2, 3, 4, 6};
	char		high1[] = {'A', '\200', 0};
	char		high2[] = {'A', '\0', 0};
	const int	passed[6] = {
		!ft_memcmp("Hello", "Hello", 5),
		ft_memcmp("Hello", "World", 5),
		!ft_memcmp("Hello", "World", 0),
		ft_memcmp(buf1, buf2, 5) < 0,
		ft_memcmp(high1, high2, 2) > 0,
		ft_memcmp(high2, high1, 2) < 0
	};

	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_memcmp");
	print_result("Test equal", passed[0]);
	print_result("Test different", passed[1]);
	print_result("Test n=0", passed[2]);
	print_result("Test binary data", passed[3]);
	print_result("Test unsigned char >127 (\\200 vs \\0)", passed[4]);
	print_result("Test unsigned char symmetry", passed[5]);
}

static void	ft_strnstr_len_too_short(void) {
	ft_strnstr("Hello, World!", "World", 5);
}

static void	test_ft_strnstr(void) {
	const char	*haystack = "Hello, World!";
	const int	passed[5] = {
		ft_strnstr(haystack, "World", 13) != NULL,
		ft_strnstr(haystack, "o", 13) != NULL,
		!ft_strnstr(haystack, "xyz", 13),
		ft_strnstr(haystack, "", 13) == haystack,
		!forked_test(ft_strnstr_len_too_short)
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

static void	ft_atoi_null_test(void) {
	ft_atoi(NULL);
}

static void	test_ft_atoi(void) {
	const int	passed[11] = {
		ft_atoi("  \t\n\v\f\r +42   $") == 42,
		ft_atoi("\v \t\r  \n    \f-42   *") == -42,
		!ft_atoi("0"),
		!ft_atoi("++2"),
		!ft_atoi("--4"),
		!ft_atoi("-+9"),
		!ft_atoi("+-8"),
		!ft_atoi(" \t-R66"),
		ft_atoi("2147483647") == 2147483647,
		ft_atoi("-2147483648") == -2147483648,
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
	print_result("Test NULL", passed[10]);
}

static void	ft_calloc_overflow_write_test(void) {
	const size_t	size_max = ~(size_t)0;
	char			*ptr = ft_calloc(size_max >> 1, size_max >> 1);

	ptr[0] = 'x';
}

static void	ft_calloc_overflow_free_test(void) {
	const size_t	size_max = ~(size_t)0;
	char			*ptr = ft_calloc(size_max >> 1, size_max >> 1);

	free(ptr);
}

static void	ft_calloc_zero_count_test(void) {
	void	*ptr = ft_calloc(0, 5);

	free(ptr);
}

static void	ft_calloc_zero_size_test(void) {
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

static void	ft_strdup_empty_test(void) {
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

static void	ft_substr_null_test(void) {
	ft_substr(NULL, 0, 5);
}

static void	ft_substr_empty_test(void) {
	char	*sub1 = ft_substr("Hello", 10, 5);
	char	*sub2 = ft_substr("test", 0, 0);

	sub1[0] = 'a';
	free(sub1);
	sub2[0] = 'a';
	free(sub2);
}

static void	ft_substr_start_past_end_test(void) {
	char	*res = ft_substr("", 1, 1);

	if (!res || res[0] != '\0')
		abort();
	free(res);
	res = ft_substr("abc", 5, 2);
	if (!res || res[0] != '\0')
		abort();
	free(res);
}

static void	ft_substr_start_max_test(void) {
	char *res = ft_substr("abc", ~(unsigned int)0, 1);
	if (!res || res[0] != '\0')
		abort();
	free(res);
}

static void	test_ft_substr(void) {
	char	*sub = ft_substr("Hello, World!", 7, 5);
	int		passed[9];

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
	passed[7] = !forked_test(ft_substr_start_past_end_test);
	passed[8] = !forked_test(ft_substr_start_max_test);
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
	print_result("Test start past end", passed[7]);
	print_result("Test start = UINT_MAX", passed[8]);
}

static void	ft_strjoin_null_s1_test(void) {
	ft_strjoin(NULL, "test");
}

static void	ft_strjoin_null_s2_test(void) {
	ft_strjoin("test", NULL);
}

static void	ft_strjoin_null_both_test(void) {
	ft_strjoin(NULL, NULL);
}

static void	test_ft_strjoin(void) {
	char	*joined;
	int		passed[7];

	joined = ft_strjoin("Hello", " World");
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
	passed[4] = !forked_test(ft_strjoin_null_s1_test);
	passed[5] = !forked_test(ft_strjoin_null_s2_test);
	passed[6] = !forked_test(ft_strjoin_null_both_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strjoin");
	print_result("Test basic join", passed[0]);
	print_result("Test empty s1", passed[1]);
	print_result("Test empty s2", passed[2]);
	print_result("Test short strings", passed[3]);
	print_result("Test NULL s1", passed[4]);
	print_result("Test NULL s2", passed[5]);
	print_result("Test both NULL", passed[6]);
}

static void	ft_strtrim_empty_string_test(void) {
	ft_strtrim("", " ");
}

static void	ft_strtrim_all_trim_test(void) {
	ft_strtrim("xxxxx", "x");
}

static void	ft_strtrim_null_input_test(void) {
	ft_strtrim(NULL, " ");
}

static void	ft_strtrim_null_set_test(void) {
	ft_strtrim("test", NULL);
}

static void	ft_strtrim_null_both_test(void) {
	ft_strtrim(NULL, NULL);
}

static void	test_ft_strtrim(void) {
	char	*trimmed = ft_strtrim("   Hello   ", " ");
	int		passed[10];

	passed[0] = !strcmp(trimmed, "Hello");
	free(trimmed);
	trimmed = ft_strtrim("xxxHelloxxx", "x");
	passed[1] = !strcmp(trimmed, "Hello");
	free(trimmed);
	trimmed = ft_strtrim("Hello", "xyz");
	passed[2] = !strcmp(trimmed, "Hello");
	free(trimmed);
	trimmed = ft_strtrim("abcdcba", "abc");
	passed[3] = !strcmp(trimmed, "d");
	free(trimmed);
	trimmed = ft_strtrim("Hello", "");
	passed[4] = !strcmp(trimmed, "Hello");
	free(trimmed);
	passed[5] = !forked_test(ft_strtrim_empty_string_test);
	passed[6] = !forked_test(ft_strtrim_all_trim_test);
	passed[7] = !forked_test(ft_strtrim_null_input_test);
	passed[8] = !forked_test(ft_strtrim_null_set_test);
	passed[9] = !forked_test(ft_strtrim_null_both_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strtrim");
	print_result("Test spaces", passed[0]);
	print_result("Test custom set", passed[1]);
	print_result("Test no trim", passed[2]);
	print_result("Test multiple occurrences", passed[3]);
	print_result("Test no set", passed[4]);
	print_result("Test empty string", passed[5]);
	print_result("Test all trim", passed[6]);
	print_result("Test NULL input", passed[7]);
	print_result("Test NULL set", passed[8]);
	print_result("Test both NULL", passed[9]);
}

static void	ft_split_null_test(void) {
	ft_split(NULL, ' ');
}

static void	ft_split_malloc_fail_test(void) {
	g_malloc_count = 0;
	++g_malloc_fail_at;
	char **result = ft_split("Hello World Test", ' ');
	(void)result;
}

static void	test_ft_split(void) {
	char	**arr;
	int		passed[18];

	arr = ft_split("Hello World 42", ' ');
	passed[0] = arr && !strcmp(arr[0], "Hello") && !strcmp(arr[1], "World") && !strcmp(arr[2], "42") && !arr[3];
	safe_free_arr(arr);
	arr = ft_split("___Hello___World___", '_');
	passed[1] = arr && !strcmp(arr[0], "Hello") && !strcmp(arr[1], "World") && !arr[2];
	safe_free_arr(arr);
	arr = ft_split("", ' ');
	passed[2] = arr && !arr[0];
	safe_free_arr(arr);
	arr = ft_split("", 'x');
	passed[3] = arr && !arr[0];
	safe_free_arr(arr);
	arr = ft_split("xxx", 'x');
	passed[4] = arr && !arr[0];
	safe_free_arr(arr);
	arr = ft_split("Hello", '\0');
	passed[5] = arr && !strcmp(arr[0], "Hello") && !arr[1];
	safe_free_arr(arr);
	arr = ft_split("", '\0');
	passed[6] = (arr && !arr[0]);
	safe_free_arr(arr);
	arr = ft_split("   ", ' ');
	passed[7] = arr && !arr[0];
	safe_free_arr(arr);
	arr = ft_split("HelloWorld", ' ');
	passed[8] = arr && !strcmp(arr[0], "HelloWorld") && !arr[1];
	safe_free_arr(arr);
	arr = ft_split("Hello   World", ' ');
	passed[9] = arr && !strcmp(arr[0], "Hello") && !strcmp(arr[1], "World") && !arr[2];
	safe_free_arr(arr);
	arr = ft_split("Hello\xFFWorld", (char)255);
	passed[10] = arr && !strcmp(arr[0], "Hello") && !strcmp(arr[1], "World") && !arr[2];
	safe_free_arr(arr);
	arr = ft_split("Hello\xFFWorld", (char)-1);
	passed[11] = arr && !strcmp(arr[0], "Hello") && !strcmp(arr[1], "World") && !arr[2];
	safe_free_arr(arr);
	passed[12] = !forked_test(ft_split_null_test);
	g_malloc_fail_enabled = 1;
	g_malloc_fail_at = 0;
	for (int i = 13; i < 18; i++)
		passed[i] = !forked_test(ft_split_malloc_fail_test);
	g_malloc_fail_enabled = 0;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_split");
	print_result("Test basic split", passed[0]);
	print_result("Test multiple delimiters", passed[1]);
	print_result("Test empty string", passed[2]);
	print_result("Test empty string with 'x'", passed[3]);
	print_result("Test all delimiters", passed[4]);
	print_result("Test delimiter = '\\0'", passed[5]);
	print_result("Test empty string with '\\0'", passed[6]);
	print_result("Test only spaces", passed[7]);
	print_result("Test no delimiter found", passed[8]);
	print_result("Test consecutive delimiters", passed[9]);
	print_result("Test delimiter = 255 (\\xFF)", passed[10]);
	print_result("Test delimiter = -1", passed[11]);
	print_result("Test NULL", passed[12]);
	print_result("Test malloc fail #1 (array)", passed[13]);
	print_result("Test malloc fail #2 (word 1)", passed[14]);
	print_result("Test malloc fail #3 (word 2)", passed[15]);
	print_result("Test malloc fail #4 (word 3)", passed[16]);
	print_result("Test malloc fail #5 (other)", passed[17]);
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

static char	mapi_func(unsigned int i, char c) {
	return c + i;
}

static void	ft_strmapi_null_input_test(void) {
	ft_strmapi(NULL, mapi_func);
}

static void	ft_strmapi_null_func_test(void) {
	ft_strmapi("test", NULL);
}

static void	ft_strmapi_null_both_test(void) {
	ft_strmapi(NULL, NULL);
}

static void	test_ft_strmapi(void) {
	char	*result = ft_strmapi("abc", mapi_func);
	int		passed[5];

	passed[0] = result && result[0] == 'a' && result[1] == 'c' && result[2] == 'e';
	free(result);
	result = ft_strmapi("", mapi_func);
	passed[1] = result && !strcmp(result, "");
	free(result);
	passed[2] = !forked_test(ft_strmapi_null_input_test);
	passed[3] = !forked_test(ft_strmapi_null_func_test);
	passed[4] = !forked_test(ft_strmapi_null_both_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_strmapi");
	print_result("Test basic", passed[0]);
	print_result("Test empty string", passed[1]);
	print_result("Test NULL input", passed[2]);
	print_result("Test f = NULL", passed[3]);
	print_result("Test both NULL", passed[4]);
}

static void	iteri_func(unsigned int i, char *c) {
	*c = *c + i;
}

static void	ft_striteri_null_input_test(void) {
	ft_striteri(NULL, iteri_func);
}

static void	ft_striteri_null_func_test(void) {
	ft_striteri("test", NULL);
}

static void	ft_striteri_null_both_test(void) {
	ft_striteri(NULL, NULL);
}

static void	test_ft_striteri(void) {
	char	str[] = "abc";
	int		passed[4];

	ft_striteri(str, iteri_func);
	passed[0] = str[0] == 'a' && str[1] == 'c' && str[2] == 'e';
	passed[1] = !forked_test(ft_striteri_null_input_test);
	passed[2] = !forked_test(ft_striteri_null_func_test);
	passed[3] = !forked_test(ft_striteri_null_both_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_striteri");
	print_result("Test basic striteri", passed[0]);
	print_result("Test NULL input", passed[1]);
	print_result("Test f = NULL", passed[2]);
	print_result("Test both NULL", passed[3]);
}

static int	test_fd_output(void (*func)(void *, int), void *input, 
							const char *expected, size_t read_len) {
	char	buf[50] = {0};
	char	tmp[] = "/tmp/test_fd_XXXXXX";
	int		fd = mkstemp(tmp);
	int		result;

	if (fd == -1) {
		perror("libft-fairy: mkstemp failed");
		exit(EXIT_FAILURE);
	}
	func(input, fd);
	close(fd);
	fd = open(tmp, O_RDONLY);
	if (fd == -1) {
		perror("libft-fairy: open failed");
		exit(EXIT_FAILURE);
	}
	read(fd, buf, read_len);
	buf[read_len] = '\0';
	close(fd);
	unlink(tmp);
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

static void	wrapper_putchar_str(void *s, int fd) {
	char *str = (char *)s;
	for (int i = 0; str[i]; i++)
		ft_putchar_fd(str[i], fd);
}

static void	test_ft_putchar_fd(void) {
	char	c = '0';
	int		passed[2];

	passed[0] = test_fd_output(wrapper_putchar_str, "AB", "AB", 2);
	passed[1] = test_fd_output(wrapper_putchar, &c, "0", 1);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_putchar_fd");
	print_result("Test 'A' and 'B'", passed[0]);
	print_result("Test '0'", passed[1]);
}

static void	putstr_fd_null_test(void) {
	ft_putstr_fd(NULL, 1);
}

static void	test_ft_putstr_fd(void) {
	int	passed[3];

	passed[0] = test_fd_output(wrapper_putstr, "Hello, World!", "Hello, World!", 13);
	passed[1] = test_fd_output(wrapper_putstr, "42", "42", 2);
	passed[2] = !forked_test(putstr_fd_null_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_putstr_fd");
	print_result("Test 'Hello, World!'", passed[0]);
	print_result("Test '42'", passed[1]);
	print_result("Test NULL", passed[2]);
}

static void	putendl_fd_null_test(void) {
	ft_putendl_fd(NULL, 1);
}

static void	test_ft_putendl_fd(void) {
	int	passed[3];

	passed[0] = test_fd_output(wrapper_putendl, "Hello", "Hello\n", 6);
	passed[1] = test_fd_output(wrapper_putendl, "", "\n", 1);
	passed[2] = !forked_test(putendl_fd_null_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_putendl_fd");
	print_result("Test 'Hello' with newline", passed[0]);
	print_result("Test empty string with newline", passed[1]);
	print_result("Test NULL", passed[2]);
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

int	main(void) {
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
