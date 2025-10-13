#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <fcntl.h>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

int g_tests_passed = 0;
int g_tests_failed = 0;

void print_test_header(const char *function_name)
{
	printf("\n========================================\n");
	printf("Testing: %s\n", function_name);
	printf("========================================\n");
}

void print_result(const char *test_name, int passed)
{
	if (passed)
	{
		printf(GREEN "✓ " RESET "%s\n", test_name);
		g_tests_passed++;
	}
	else
	{
		printf(RED "✗ " RESET "%s\n", test_name);
		g_tests_failed++;
	}
}

void test_ft_isalpha(void)
{
	const int	passed[5] = {
		ft_isalpha('a'),
		ft_isalpha('Z'),
		!ft_isalpha('0'),
		!ft_isalpha(' '),
		!ft_isalpha('@')
	};

	for (int i = 0, all_passed = 1; i < 5; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 4)
			return;
	print_test_header("ft_isalpha");
	print_result("Test 'a'", passed[0]);
	print_result("Test 'Z'", passed[1]);
	print_result("Test '0'", passed[2]);
	print_result("Test ' '", passed[3]);
	print_result("Test '@'", passed[4]);
}

void test_ft_isdigit(void)
{
	const int	passed[4] = {
		ft_isdigit('0'),
		ft_isdigit('9'),
		!ft_isdigit('a'),
		!ft_isdigit(' ')
	};

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_isdigit");
	print_result("Test '0'", passed[0]);
	print_result("Test '9'", passed[1]);
	print_result("Test 'a'", passed[2]);
	print_result("Test ' '", passed[3]);
}

void test_ft_isalnum(void)
{
	const int	passed[5] = {
		ft_isalnum('a'),
		ft_isalnum('Z'),
		ft_isalnum('5'),
		!ft_isalnum(' '),
		!ft_isalnum('@')
	};

	for (int i = 0, all_passed = 1; i < 5; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 4)
			return;
	print_test_header("ft_isalnum");
	print_result("Test 'a'", passed[0]);
	print_result("Test 'Z'", passed[1]);
	print_result("Test '5'", passed[2]);
	print_result("Test ' '", passed[3]);
	print_result("Test '@'", passed[4]);
}

void test_ft_isascii(void)
{
	const int	passed[5] = {
		ft_isascii(0),
		ft_isascii(127),
		!ft_isascii(128),
		!ft_isascii(-1),
		ft_isascii('a')
	};

	for (int i = 0, all_passed = 1; i < 5; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 4)
			return;
	print_test_header("ft_isascii");
	print_result("Test 0", passed[0]);
	print_result("Test 127", passed[1]);
	print_result("Test 128", passed[2]);
	print_result("Test -1", passed[3]);
	print_result("Test 'a'", passed[4]);
}

void test_ft_isprint(void)
{
	const int	passed[5] = {
		ft_isprint(' '),
		ft_isprint('~'),
		!ft_isprint(31),
		!ft_isprint(127),
		ft_isprint('a')
	};

	for (int i = 0, all_passed = 1; i < 5; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 4)
			return;
	print_test_header("ft_isprint");
	print_result("Test ' '", passed[0]);
	print_result("Test '~'", passed[1]);
	print_result("Test 31", passed[2]);
	print_result("Test 127", passed[3]);
	print_result("Test 'a'", passed[4]);
}

void test_ft_strlen(void)
{
	const int	passed[4] = {
		ft_strlen("") == 0,
		ft_strlen("hello") == 5,
		ft_strlen("42") == 2,
		ft_strlen("Hello, World!") == 13
	};

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_strlen");
	print_result("Test empty string", passed[0]);
	print_result("Test 'hello'", passed[1]);
	print_result("Test '42'", passed[2]);
	print_result("Test long string", passed[3]);
}

void test_ft_memset(void)
{
	int		passed[2];
	char	str1[10] = {0};
	char	str2[10] = {0};
	void	*ret;

	ret = ft_memset(str1, 'A', 5);
	memset(str2, 'A', 5);
	passed[0] = !memcmp(str1, str2, 10) && ret == str1;
	ret = ft_memset(str1, 0, 10);
	passed[1] = !str1[0] && !str1[9] && ret == str1;
	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_memset");
	print_result("Test basic memset", passed[0]);
	print_result("Test memset with 0", passed[1]);
}

void test_ft_bzero(void)
{
	int		passed[2];
	char	str1[10];

	memset(str1, 'A', 10);
	ft_bzero(str1, 5);
	passed[0] = !str1[0] && !str1[4] && str1[5] == 'A';
	ft_bzero(str1, 10);
	passed[1] = !str1[0] && !str1[9];
	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_bzero");
	print_result("Test bzero 5 bytes", passed[0]);
	print_result("Test bzero all", passed[1]);
}

void test_ft_memcpy(void)
{
	char src[] = "Hello, World!";
	char dst1[20] = {0};
	char dst2[20] = {0};
	int passed[2];

	ft_memcpy(dst1, src, strlen(src) + 1);
	memcpy(dst2, src, strlen(src) + 1);
	passed[0] = strcmp(dst1, dst2) == 0;
	ft_memcpy(dst1, "42", 2);
	passed[1] = dst1[0] == '4' && dst1[1] == '2';

	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_memcpy");
	print_result("Test basic memcpy", passed[0]);
	print_result("Test partial copy", passed[1]);
}

void test_ft_memmove(void)
{
	char str1[] = "Hello, World!";
	char str2[] = "Hello, World!";
	int passed[2];

	ft_memmove(str1 + 2, str1, 5);
	memmove(str2 + 2, str2, 5);
	passed[0] = strcmp(str1, str2) == 0;
	strcpy(str1, "Hello, World!");
	strcpy(str2, "Hello, World!");
	ft_memmove(str1, str1 + 2, 5);
	memmove(str2, str2 + 2, 5);
	passed[1] = strcmp(str1, str2) == 0;

	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_memmove");
	print_result("Test overlapping forward", passed[0]);
	print_result("Test overlapping backward", passed[1]);
}

void test_ft_strlcpy(void)
{
	char dst[20];
	size_t len;
	int passed[3];

	len = ft_strlcpy(dst, "Hello", 20);
	passed[0] = strcmp(dst, "Hello") == 0 && len == 5;
	len = ft_strlcpy(dst, "Hello, World!", 6);
	passed[1] = strcmp(dst, "Hello") == 0 && len == 13;
	len = ft_strlcpy(dst, "42", 0);
	passed[2] = len == 2;

	for (int i = 0, all_passed = 1; i < 3; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 2)
			return;
	print_test_header("ft_strlcpy");
	print_result("Test basic copy", passed[0]);
	print_result("Test truncation", passed[1]);
	print_result("Test size 0", passed[2]);
}

void test_ft_strlcat(void)
{
	char dst[20] = "Hello";
	size_t len;
	int passed[2];

	len = ft_strlcat(dst, " World", 20);
	passed[0] = strcmp(dst, "Hello World") == 0 && len == 11;
	strcpy(dst, "Hello");
	len = ft_strlcat(dst, " World!", 10);
	passed[1] = strcmp(dst, "Hello Wor") == 0;

	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_strlcat");
	print_result("Test basic concat", passed[0]);
	print_result("Test truncation", passed[1]);
}

void test_ft_toupper(void)
{
	const int passed[4] = {
		ft_toupper('a') == 'A',
		ft_toupper('z') == 'Z',
		ft_toupper('A') == 'A',
		ft_toupper('0') == '0'
	};

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_toupper");
	print_result("Test 'a'", passed[0]);
	print_result("Test 'z'", passed[1]);
	print_result("Test 'A'", passed[2]);
	print_result("Test '0'", passed[3]);
}

void test_ft_tolower(void)
{
	const int passed[4] = {
		ft_tolower('A') == 'a',
		ft_tolower('Z') == 'z',
		ft_tolower('a') == 'a',
		ft_tolower('0') == '0'
	};

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_tolower");
	print_result("Test 'A'", passed[0]);
	print_result("Test 'Z'", passed[1]);
	print_result("Test 'a'", passed[2]);
	print_result("Test '0'", passed[3]);
}

void test_ft_strchr(void)
{
	const char *str = "Hello, World!";
	const int passed[4] = {
		ft_strchr(str, 'o') == strchr(str, 'o'),
		ft_strchr(str, 'W') == strchr(str, 'W'),
		ft_strchr(str, '\0') == strchr(str, '\0'),
		ft_strchr(str, 'x') == NULL
	};

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_strchr");
	print_result("Test find 'o'", passed[0]);
	print_result("Test find 'W'", passed[1]);
	print_result("Test find '\\0'", passed[2]);
	print_result("Test not found 'x'", passed[3]);
}

void test_ft_strrchr(void)
{
	const char *str = "Hello, World!";
	const int passed[4] = {
		ft_strrchr(str, 'o') == strrchr(str, 'o'),
		ft_strrchr(str, 'W') == strrchr(str, 'W'),
		ft_strrchr(str, '\0') == strrchr(str, '\0'),
		ft_strrchr(str, 'x') == NULL
	};

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_strrchr");
	print_result("Test find last 'o'", passed[0]);
	print_result("Test find 'W'", passed[1]);
	print_result("Test find '\\0'", passed[2]);
	print_result("Test not found 'x'", passed[3]);
}

void test_ft_strncmp(void)
{
	const int passed[5] = {
		ft_strncmp("Hello", "Hello", 5) == 0,
		ft_strncmp("Hello", "World", 5) != 0,
		ft_strncmp("Hello", "Help", 3) == 0,
		ft_strncmp("Hello", "World", 0) == 0,
		ft_strncmp("Hello", "Hello\0test", 10) == 0
	};

	for (int i = 0, all_passed = 1; i < 5; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 4)
			return;
	print_test_header("ft_strncmp");
	print_result("Test equal strings", passed[0]);
	print_result("Test different strings", passed[1]);
	print_result("Test partial compare", passed[2]);
	print_result("Test n=0", passed[3]);
	print_result("Test with \\0", passed[4]);
}

void test_ft_memchr(void)
{
	const char *str = "Hello, World!";
	const int passed[4] = {
		ft_memchr(str, 'o', 13) == memchr(str, 'o', 13),
		ft_memchr(str, 'W', 13) == memchr(str, 'W', 13),
		ft_memchr(str, 'x', 13) == NULL,
		ft_memchr(str, 'H', 0) == NULL
	};

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_memchr");
	print_result("Test find 'o'", passed[0]);
	print_result("Test find 'W'", passed[1]);
	print_result("Test not found", passed[2]);
	print_result("Test n=0", passed[3]);
}

void test_ft_memcmp(void)
{
	char buf1[] = {1, 2, 3, 4, 5};
	char buf2[] = {1, 2, 3, 4, 6};
	const int passed[4] = {
		ft_memcmp("Hello", "Hello", 5) == 0,
		ft_memcmp("Hello", "World", 5) != 0,
		ft_memcmp("Hello", "World", 0) == 0,
		ft_memcmp(buf1, buf2, 5) < 0
	};

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_memcmp");
	print_result("Test equal", passed[0]);
	print_result("Test different", passed[1]);
	print_result("Test n=0", passed[2]);
	print_result("Test binary data", passed[3]);
}

void test_ft_strnstr(void)
{
	const char *haystack = "Hello, World!";
	const int passed[5] = {
		ft_strnstr(haystack, "World", 13) != NULL,
		ft_strnstr(haystack, "o", 13) != NULL,
		ft_strnstr(haystack, "xyz", 13) == NULL,
		ft_strnstr(haystack, "", 13) == haystack,
		ft_strnstr(haystack, "World", 5) == NULL
	};

	for (int i = 0, all_passed = 1; i < 5; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 4)
			return;
	print_test_header("ft_strnstr");
	print_result("Test find 'World'", passed[0]);
	print_result("Test find 'o'", passed[1]);
	print_result("Test not found", passed[2]);
	print_result("Test empty needle", passed[3]);
	print_result("Test len too short", passed[4]);
}

void test_ft_atoi(void)
{
	const int passed[6] = {
		ft_atoi("42") == 42,
		ft_atoi("-42") == -42,
		ft_atoi("   42") == 42,
		ft_atoi("+42") == 42,
		ft_atoi("0") == 0,
		ft_atoi("  -123abc") == -123
	};

	for (int i = 0, all_passed = 1; i < 6; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 5)
			return;
	print_test_header("ft_atoi");
	print_result("Test '42'", passed[0]);
	print_result("Test '-42'", passed[1]);
	print_result("Test '   42'", passed[2]);
	print_result("Test '+42'", passed[3]);
	print_result("Test '0'", passed[4]);
	print_result("Test '  -123abc'", passed[5]);
}

void test_ft_calloc(void)
{
	int *arr = ft_calloc(5, sizeof(int));
	int all_zero = 1;
	int passed[3];

	for (int i = 0; i < 5; i++)
		if (arr[i] != 0)
			all_zero = 0;
	passed[0] = all_zero;
	free(arr);
	char *str = ft_calloc(10, sizeof(char));
	passed[1] = str != NULL;
	free(str);
	void *ptr = ft_calloc(0, 10);
	passed[2] = ptr != NULL || ptr == NULL;
	free(ptr);

	for (int i = 0, all_passed = 1; i < 3; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 2)
			return;
	print_test_header("ft_calloc");
	print_result("Test all zeros", passed[0]);
	print_result("Test allocated", passed[1]);
	print_result("Test nmemb=0", passed[2]);
}

void test_ft_strdup(void)
{
	char *dup = ft_strdup("Hello");
	int passed[3];

	passed[0] = strcmp(dup, "Hello") == 0;
	free(dup);
	dup = ft_strdup("");
	passed[1] = strcmp(dup, "") == 0;
	free(dup);
	dup = ft_strdup("42");
	passed[2] = strcmp(dup, "42") == 0;
	free(dup);

	for (int i = 0, all_passed = 1; i < 3; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 2)
			return;
	print_test_header("ft_strdup");
	print_result("Test basic dup", passed[0]);
	print_result("Test empty string", passed[1]);
	print_result("Test short string", passed[2]);
}

void test_ft_substr(void)
{
	char *sub = ft_substr("Hello, World!", 7, 5);
	int passed[4];

	passed[0] = strcmp(sub, "World") == 0;
	free(sub);
	sub = ft_substr("Hello", 0, 3);
	passed[1] = strcmp(sub, "Hel") == 0;
	free(sub);
	sub = ft_substr("Hello", 10, 5);
	passed[2] = strcmp(sub, "") == 0;
	free(sub);
	sub = ft_substr("Hello", 2, 100);
	passed[3] = strcmp(sub, "llo") == 0;
	free(sub);

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_substr");
	print_result("Test basic substr", passed[0]);
	print_result("Test from start", passed[1]);
	print_result("Test start > len", passed[2]);
	print_result("Test len too long", passed[3]);
}

void test_ft_strjoin(void)
{
	char *joined = ft_strjoin("Hello", " World");
	int passed[4];

	passed[0] = strcmp(joined, "Hello World") == 0;
	free(joined);
	joined = ft_strjoin("", "Hello");
	passed[1] = strcmp(joined, "Hello") == 0;
	free(joined);
	joined = ft_strjoin("Hello", "");
	passed[2] = strcmp(joined, "Hello") == 0;
	free(joined);
	joined = ft_strjoin("42", "!");
	passed[3] = strcmp(joined, "42!") == 0;
	free(joined);

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_strjoin");
	print_result("Test basic join", passed[0]);
	print_result("Test empty s1", passed[1]);
	print_result("Test empty s2", passed[2]);
	print_result("Test short strings", passed[3]);
}

void test_ft_strtrim(void)
{
	char *trimmed = ft_strtrim("   Hello   ", " ");
	int passed[4];

	passed[0] = strcmp(trimmed, "Hello") == 0;
	free(trimmed);
	trimmed = ft_strtrim("xxxHelloxxx", "x");
	passed[1] = strcmp(trimmed, "Hello") == 0;
	free(trimmed);
	trimmed = ft_strtrim("Hello", "xyz");
	passed[2] = strcmp(trimmed, "Hello") == 0;
	free(trimmed);
	trimmed = ft_strtrim("", " ");
	passed[3] = strcmp(trimmed, "") == 0;
	free(trimmed);

	for (int i = 0, all_passed = 1; i < 4; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 3)
			return;
	print_test_header("ft_strtrim");
	print_result("Test spaces", passed[0]);
	print_result("Test custom set", passed[1]);
	print_result("Test no trim", passed[2]);
	print_result("Test empty string", passed[3]);
}

void test_ft_split(void)
{
	char **arr = ft_split("Hello World 42", ' ');
	int passed[3];

	passed[0] = arr && strcmp(arr[0], "Hello") == 0 && 
				strcmp(arr[1], "World") == 0 && strcmp(arr[2], "42") == 0 && arr[3] == NULL;
	if (arr)
	{
		for (int i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
	}
	arr = ft_split("   Hello   World   ", ' ');
	passed[1] = arr && strcmp(arr[0], "Hello") == 0 && 
				strcmp(arr[1], "World") == 0 && arr[2] == NULL;
	if (arr)
	{
		for (int i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
	}
	arr = ft_split("", ' ');
	passed[2] = arr && arr[0] == NULL;
	if (arr)
		free(arr);

	for (int i = 0, all_passed = 1; i < 3; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 2)
			return;
	print_test_header("ft_split");
	print_result("Test basic split", passed[0]);
	print_result("Test multiple delimiters", passed[1]);
	print_result("Test empty string", passed[2]);
}

void test_ft_itoa(void)
{
	char *str = ft_itoa(42);
	int passed[5];

	passed[0] = strcmp(str, "42") == 0;
	free(str);
	str = ft_itoa(-42);
	passed[1] = strcmp(str, "-42") == 0;
	free(str);
	str = ft_itoa(0);
	passed[2] = strcmp(str, "0") == 0;
	free(str);
	str = ft_itoa(-2147483648);
	passed[3] = strcmp(str, "-2147483648") == 0;
	free(str);
	str = ft_itoa(2147483647);
	passed[4] = strcmp(str, "2147483647") == 0;
	free(str);

	for (int i = 0, all_passed = 1; i < 5; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 4)
			return;
	print_test_header("ft_itoa");
	print_result("Test 42", passed[0]);
	print_result("Test -42", passed[1]);
	print_result("Test 0", passed[2]);
	print_result("Test INT_MIN", passed[3]);
	print_result("Test INT_MAX", passed[4]);
}

char test_mapi_func(unsigned int i, char c)
{
	return c + i;
}

void test_ft_strmapi(void)
{
	char *result = ft_strmapi("abc", test_mapi_func);
	int passed[2];

	passed[0] = result && result[0] == 'a' && result[1] == 'c' && result[2] == 'e';
	free(result);
	result = ft_strmapi("", test_mapi_func);
	passed[1] = result && strcmp(result, "") == 0;
	free(result);

	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_strmapi");
	print_result("Test basic strmapi", passed[0]);
	print_result("Test empty string", passed[1]);
}

void test_iteri_func(unsigned int i, char *c)
{
	*c = *c + i;
}

void test_ft_striteri(void)
{
	char str[] = "abc";
	int passed[1];

	ft_striteri(str, test_iteri_func);
	passed[0] = str[0] == 'a' && str[1] == 'c' && str[2] == 'e';

	for (int i = 0, all_passed = 1; i < 1; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 0)
			return;
	print_test_header("ft_striteri");
	print_result("Test basic striteri", passed[0]);
}

void test_ft_putchar_fd(void)
{
	char buf[10];
	int fd = open("/tmp/test_putchar", O_RDWR | O_CREAT | O_TRUNC, 0644);
	int passed[2];

	ft_putchar_fd('A', fd);
	ft_putchar_fd('B', fd);
	close(fd);
	fd = open("/tmp/test_putchar", O_RDONLY);
	read(fd, buf, 2);
	buf[2] = '\0';
	close(fd);
	unlink("/tmp/test_putchar");
	passed[0] = strcmp(buf, "AB") == 0;

	fd = open("/tmp/test_putchar2", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putchar_fd('0', fd);
	close(fd);
	fd = open("/tmp/test_putchar2", O_RDONLY);
	read(fd, buf, 1);
	buf[1] = '\0';
	close(fd);
	unlink("/tmp/test_putchar2");
	passed[1] = buf[0] == '0';

	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_putchar_fd");
	print_result("Test 'A' and 'B'", passed[0]);
	print_result("Test '0'", passed[1]);
}

void test_ft_putstr_fd(void)
{
	char buf[20];
	int fd = open("/tmp/test_putstr", O_RDWR | O_CREAT | O_TRUNC, 0644);
	int passed[2];

	ft_putstr_fd("Hello, World!", fd);
	close(fd);
	fd = open("/tmp/test_putstr", O_RDONLY);
	read(fd, buf, 13);
	buf[13] = '\0';
	close(fd);
	unlink("/tmp/test_putstr");
	passed[0] = strcmp(buf, "Hello, World!") == 0;

	fd = open("/tmp/test_putstr2", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd("42", fd);
	close(fd);
	fd = open("/tmp/test_putstr2", O_RDONLY);
	read(fd, buf, 2);
	buf[2] = '\0';
	close(fd);
	unlink("/tmp/test_putstr2");
	passed[1] = strcmp(buf, "42") == 0;

	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_putstr_fd");
	print_result("Test 'Hello, World!'", passed[0]);
	print_result("Test '42'", passed[1]);
}

void test_ft_putendl_fd(void)
{
	char buf[20];
	int fd = open("/tmp/test_putendl", O_RDWR | O_CREAT | O_TRUNC, 0644);
	int passed[2];

	ft_putendl_fd("Hello", fd);
	close(fd);
	fd = open("/tmp/test_putendl", O_RDONLY);
	read(fd, buf, 6);
	buf[6] = '\0';
	close(fd);
	unlink("/tmp/test_putendl");
	passed[0] = strcmp(buf, "Hello\n") == 0;

	fd = open("/tmp/test_putendl2", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putendl_fd("", fd);
	close(fd);
	fd = open("/tmp/test_putendl2", O_RDONLY);
	read(fd, buf, 1);
	buf[1] = '\0';
	close(fd);
	unlink("/tmp/test_putendl2");
	passed[1] = buf[0] == '\n';

	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_putendl_fd");
	print_result("Test 'Hello' with newline", passed[0]);
	print_result("Test empty string with newline", passed[1]);
}

void test_ft_putnbr_fd(void)
{
	char buf[20];
	int fd = open("/tmp/test_putnbr", O_RDWR | O_CREAT | O_TRUNC, 0644);
	int passed[5];

	ft_putnbr_fd(42, fd);
	close(fd);
	fd = open("/tmp/test_putnbr", O_RDONLY);
	read(fd, buf, 2);
	buf[2] = '\0';
	close(fd);
	unlink("/tmp/test_putnbr");
	passed[0] = strcmp(buf, "42") == 0;

	fd = open("/tmp/test_putnbr2", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putnbr_fd(-42, fd);
	close(fd);
	fd = open("/tmp/test_putnbr2", O_RDONLY);
	read(fd, buf, 3);
	buf[3] = '\0';
	close(fd);
	unlink("/tmp/test_putnbr2");
	passed[1] = strcmp(buf, "-42") == 0;

	fd = open("/tmp/test_putnbr3", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putnbr_fd(0, fd);
	close(fd);
	fd = open("/tmp/test_putnbr3", O_RDONLY);
	read(fd, buf, 1);
	buf[1] = '\0';
	close(fd);
	unlink("/tmp/test_putnbr3");
	passed[2] = strcmp(buf, "0") == 0;

	fd = open("/tmp/test_putnbr4", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putnbr_fd(-2147483648, fd);
	close(fd);
	fd = open("/tmp/test_putnbr4", O_RDONLY);
	read(fd, buf, 11);
	buf[11] = '\0';
	close(fd);
	unlink("/tmp/test_putnbr4");
	passed[3] = strcmp(buf, "-2147483648") == 0;

	fd = open("/tmp/test_putnbr5", O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_putnbr_fd(2147483647, fd);
	close(fd);
	fd = open("/tmp/test_putnbr5", O_RDONLY);
	read(fd, buf, 10);
	buf[10] = '\0';
	close(fd);
	unlink("/tmp/test_putnbr5");
	passed[4] = strcmp(buf, "2147483647") == 0;

	for (int i = 0, all_passed = 1; i < 5; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 4)
			return;
	print_test_header("ft_putnbr_fd");
	print_result("Test 42", passed[0]);
	print_result("Test -42", passed[1]);
	print_result("Test 0", passed[2]);
	print_result("Test INT_MIN", passed[3]);
	print_result("Test INT_MAX", passed[4]);
}

void test_ft_lstnew(void)
{
	int content = 42;
	t_list *node = ft_lstnew(&content);
	int passed[1];

	passed[0] = node != NULL && *(int *)node->content == 42 && node->next == NULL;
	free(node);

	for (int i = 0, all_passed = 1; i < 1; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 0)
			return;
	print_test_header("ft_lstnew");
	print_result("Test node creation", passed[0]);
}

void test_ft_lstadd_front(void)
{
	int c1 = 1, c2 = 2;
	t_list *lst = ft_lstnew(&c1);
	t_list *new = ft_lstnew(&c2);
	int passed[1];

	ft_lstadd_front(&lst, new);
	passed[0] = lst == new && *(int *)lst->content == 2 && 
				*(int *)lst->next->content == 1;
	free(lst->next);
	free(lst);

	for (int i = 0, all_passed = 1; i < 1; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 0)
			return;
	print_test_header("ft_lstadd_front");
	print_result("Test add front", passed[0]);
}

void test_ft_lstsize(void)
{
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	int passed[2];

	n1->next = n2;
	n2->next = n3;
	passed[0] = ft_lstsize(n1) == 3;
	passed[1] = ft_lstsize(NULL) == 0;
	free(n3);
	free(n2);
	free(n1);

	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_lstsize");
	print_result("Test size 3", passed[0]);
	print_result("Test size NULL", passed[1]);
}

void test_ft_lstlast(void)
{
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	int passed[2];

	n1->next = n2;
	n2->next = n3;
	passed[0] = ft_lstlast(n1) == n3;
	passed[1] = ft_lstlast(NULL) == NULL;
	free(n3);
	free(n2);
	free(n1);

	for (int i = 0, all_passed = 1; i < 2; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 1)
			return;
	print_test_header("ft_lstlast");
	print_result("Test last", passed[0]);
	print_result("Test NULL", passed[1]);
}

void test_ft_lstadd_back(void)
{
	int c1 = 1, c2 = 2;
	t_list *lst = ft_lstnew(&c1);
	t_list *new = ft_lstnew(&c2);
	int passed[1];

	ft_lstadd_back(&lst, new);
	passed[0] = lst->next == new && *(int *)new->content == 2;
	free(new);
	free(lst);

	for (int i = 0, all_passed = 1; i < 1; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 0)
			return;
	print_test_header("ft_lstadd_back");
	print_result("Test add back", passed[0]);
}

void del_content(void *content)
{
	(void)content;
}

void test_ft_lstdelone(void)
{
	int c = 42;
	t_list *node = ft_lstnew(&c);

	ft_lstdelone(node, del_content);
	g_tests_passed++;
}

void test_ft_lstclear(void)
{
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	int passed[1];

	n1->next = n2;
	n2->next = n3;
	ft_lstclear(&n1, del_content);
	passed[0] = n1 == NULL;

	for (int i = 0, all_passed = 1; i < 1; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 0)
			return;
	print_test_header("ft_lstclear");
	print_result("Test clear (no crash)", passed[0]);
}

void iter_func(void *content)
{
	(*(int *)content)++;
}

void test_ft_lstiter(void)
{
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	int passed[1];

	n1->next = n2;
	n2->next = n3;
	ft_lstiter(n1, iter_func);
	passed[0] = c1 == 2 && c2 == 3 && c3 == 4;
	free(n3);
	free(n2);
	free(n1);

	for (int i = 0, all_passed = 1; i < 1; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 0)
			return;
	print_test_header("ft_lstiter");
	print_result("Test iter", passed[0]);
}

void *map_func(void *content)
{
	int *new = malloc(sizeof(int));
	if (!new)
		return NULL;
	*new = *(int *)content * 2;
	return new;
}

void test_ft_lstmap(void)
{
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	t_list *new_lst;
	int passed[1];

	n1->next = n2;
	n2->next = n3;
	new_lst = ft_lstmap(n1, map_func, free);
	passed[0] = new_lst && *(int *)new_lst->content == 2 && 
				*(int *)new_lst->next->content == 4 && *(int *)new_lst->next->next->content == 6;
	ft_lstclear(&new_lst, free);
	free(n3);
	free(n2);
	free(n1);

	for (int i = 0, all_passed = 1; i < 1; i++)
		if ((all_passed = (all_passed && passed[i])) && i == 0)
			return;
	print_test_header("ft_lstmap");
	print_result("Test map", passed[0]);
}

int main(void)
{
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
	test_ft_lstnew();
	test_ft_lstadd_front();
	test_ft_lstsize();
	test_ft_lstlast();
	test_ft_lstadd_back();
	test_ft_lstdelone();
	test_ft_lstclear();
	test_ft_lstiter();
	test_ft_lstmap();
	return (g_tests_failed == 0 ? 0 : 1);
}
