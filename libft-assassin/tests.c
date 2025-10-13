#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

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
	print_test_header("ft_memcpy");
	char src[] = "Hello, World!";
	char dst1[20] = {0};
	char dst2[20] = {0};
	ft_memcpy(dst1, src, strlen(src) + 1);
	memcpy(dst2, src, strlen(src) + 1);
	print_result("Test basic memcpy", strcmp(dst1, dst2) == 0);
	ft_memcpy(dst1, "42", 2);
	print_result("Test partial copy", dst1[0] == '4' && dst1[1] == '2');
}

void test_ft_memmove(void)
{
	print_test_header("ft_memmove");
	char str1[] = "Hello, World!";
	char str2[] = "Hello, World!";
	ft_memmove(str1 + 2, str1, 5);
	memmove(str2 + 2, str2, 5);
	print_result("Test overlapping forward", strcmp(str1, str2) == 0);
	strcpy(str1, "Hello, World!");
	strcpy(str2, "Hello, World!");
	ft_memmove(str1, str1 + 2, 5);
	memmove(str2, str2 + 2, 5);
	print_result("Test overlapping backward", strcmp(str1, str2) == 0);
}

void test_ft_strlcpy(void)
{
	print_test_header("ft_strlcpy");
	char dst[20];
	size_t len = ft_strlcpy(dst, "Hello", 20);
	print_result("Test basic copy", strcmp(dst, "Hello") == 0 && len == 5);
	len = ft_strlcpy(dst, "Hello, World!", 6);
	print_result("Test truncation", strcmp(dst, "Hello") == 0 && len == 13);
	len = ft_strlcpy(dst, "42", 0);
	print_result("Test size 0", len == 2);
}

void test_ft_strlcat(void)
{
	print_test_header("ft_strlcat");
	char dst[20] = "Hello";
	size_t len = ft_strlcat(dst, " World", 20);
	print_result("Test basic concat", strcmp(dst, "Hello World") == 0 && len == 11);
	strcpy(dst, "Hello");
	len = ft_strlcat(dst, " World!", 10);
	print_result("Test truncation", strcmp(dst, "Hello Wor") == 0);
}

void test_ft_toupper(void)
{
	print_test_header("ft_toupper");
	print_result("Test 'a'", ft_toupper('a') == 'A');
	print_result("Test 'z'", ft_toupper('z') == 'Z');
	print_result("Test 'A'", ft_toupper('A') == 'A');
	print_result("Test '0'", ft_toupper('0') == '0');
}

void test_ft_tolower(void)
{
	print_test_header("ft_tolower");
	print_result("Test 'A'", ft_tolower('A') == 'a');
	print_result("Test 'Z'", ft_tolower('Z') == 'z');
	print_result("Test 'a'", ft_tolower('a') == 'a');
	print_result("Test '0'", ft_tolower('0') == '0');
}

void test_ft_strchr(void)
{
	print_test_header("ft_strchr");
	const char *str = "Hello, World!";
	print_result("Test find 'o'", ft_strchr(str, 'o') == strchr(str, 'o'));
	print_result("Test find 'W'", ft_strchr(str, 'W') == strchr(str, 'W'));
	print_result("Test find '\\0'", ft_strchr(str, '\0') == strchr(str, '\0'));
	print_result("Test not found 'x'", ft_strchr(str, 'x') == NULL);
}

void test_ft_strrchr(void)
{
	print_test_header("ft_strrchr");
	const char *str = "Hello, World!";
	print_result("Test find last 'o'", ft_strrchr(str, 'o') == strrchr(str, 'o'));
	print_result("Test find 'W'", ft_strrchr(str, 'W') == strrchr(str, 'W'));
	print_result("Test find '\\0'", ft_strrchr(str, '\0') == strrchr(str, '\0'));
	print_result("Test not found 'x'", ft_strrchr(str, 'x') == NULL);
}

void test_ft_strncmp(void)
{
	print_test_header("ft_strncmp");
	print_result("Test equal strings", ft_strncmp("Hello", "Hello", 5) == 0);
	print_result("Test different strings", ft_strncmp("Hello", "World", 5) != 0);
	print_result("Test partial compare", ft_strncmp("Hello", "Help", 3) == 0);
	print_result("Test n=0", ft_strncmp("Hello", "World", 0) == 0);
	print_result("Test with \\0", ft_strncmp("Hello", "Hello\0test", 10) == 0);
}

void test_ft_memchr(void)
{
	print_test_header("ft_memchr");
	const char *str = "Hello, World!";
	print_result("Test find 'o'", ft_memchr(str, 'o', 13) == memchr(str, 'o', 13));
	print_result("Test find 'W'", ft_memchr(str, 'W', 13) == memchr(str, 'W', 13));
	print_result("Test not found", ft_memchr(str, 'x', 13) == NULL);
	print_result("Test n=0", ft_memchr(str, 'H', 0) == NULL);
}

void test_ft_memcmp(void)
{
	print_test_header("ft_memcmp");
	print_result("Test equal", ft_memcmp("Hello", "Hello", 5) == 0);
	print_result("Test different", ft_memcmp("Hello", "World", 5) != 0);
	print_result("Test n=0", ft_memcmp("Hello", "World", 0) == 0);
	char buf1[] = {1, 2, 3, 4, 5};
	char buf2[] = {1, 2, 3, 4, 6};
	print_result("Test binary data", ft_memcmp(buf1, buf2, 5) < 0);
}

void test_ft_strnstr(void)
{
	print_test_header("ft_strnstr");
	const char *haystack = "Hello, World!";
	print_result("Test find 'World'", ft_strnstr(haystack, "World", 13) != NULL);
	print_result("Test find 'o'", ft_strnstr(haystack, "o", 13) != NULL);
	print_result("Test not found", ft_strnstr(haystack, "xyz", 13) == NULL);
	print_result("Test empty needle", ft_strnstr(haystack, "", 13) == haystack);
	print_result("Test len too short", ft_strnstr(haystack, "World", 5) == NULL);
}

void test_ft_atoi(void)
{
	print_test_header("ft_atoi");
	print_result("Test '42'", ft_atoi("42") == 42);
	print_result("Test '-42'", ft_atoi("-42") == -42);
	print_result("Test '   42'", ft_atoi("   42") == 42);
	print_result("Test '+42'", ft_atoi("+42") == 42);
	print_result("Test '0'", ft_atoi("0") == 0);
	print_result("Test '  -123abc'", ft_atoi("  -123abc") == -123);
}

void test_ft_calloc(void)
{
	print_test_header("ft_calloc");
	int *arr = ft_calloc(5, sizeof(int));
	int all_zero = 1;
	for (int i = 0; i < 5; i++)
		if (arr[i] != 0)
			all_zero = 0;
	print_result("Test all zeros", all_zero);
	free(arr);
	char *str = ft_calloc(10, sizeof(char));
	print_result("Test allocated", str != NULL);
	free(str);
	void *ptr = ft_calloc(0, 10);
	print_result("Test nmemb=0", ptr != NULL || ptr == NULL);
	free(ptr);
}

void test_ft_strdup(void)
{
	print_test_header("ft_strdup");
	char *dup = ft_strdup("Hello");
	print_result("Test basic dup", strcmp(dup, "Hello") == 0);
	free(dup);
	dup = ft_strdup("");
	print_result("Test empty string", strcmp(dup, "") == 0);
	free(dup);
	dup = ft_strdup("42");
	print_result("Test short string", strcmp(dup, "42") == 0);
	free(dup);
}

void test_ft_substr(void)
{
	print_test_header("ft_substr");
	char *sub = ft_substr("Hello, World!", 7, 5);
	print_result("Test basic substr", strcmp(sub, "World") == 0);
	free(sub);
	sub = ft_substr("Hello", 0, 3);
	print_result("Test from start", strcmp(sub, "Hel") == 0);
	free(sub);
	sub = ft_substr("Hello", 10, 5);
	print_result("Test start > len", strcmp(sub, "") == 0);
	free(sub);
	sub = ft_substr("Hello", 2, 100);
	print_result("Test len too long", strcmp(sub, "llo") == 0);
	free(sub);
}

void test_ft_strjoin(void)
{
	print_test_header("ft_strjoin");
	char *joined = ft_strjoin("Hello", " World");
	print_result("Test basic join", strcmp(joined, "Hello World") == 0);
	free(joined);
	joined = ft_strjoin("", "Hello");
	print_result("Test empty s1", strcmp(joined, "Hello") == 0);
	free(joined);
	joined = ft_strjoin("Hello", "");
	print_result("Test empty s2", strcmp(joined, "Hello") == 0);
	free(joined);
	joined = ft_strjoin("42", "!");
	print_result("Test short strings", strcmp(joined, "42!") == 0);
	free(joined);
}

void test_ft_strtrim(void)
{
	print_test_header("ft_strtrim");
	char *trimmed = ft_strtrim("   Hello   ", " ");
	print_result("Test spaces", strcmp(trimmed, "Hello") == 0);
	free(trimmed);
	trimmed = ft_strtrim("xxxHelloxxx", "x");
	print_result("Test custom set", strcmp(trimmed, "Hello") == 0);
	free(trimmed);
	trimmed = ft_strtrim("Hello", "xyz");
	print_result("Test no trim", strcmp(trimmed, "Hello") == 0);
	free(trimmed);
	trimmed = ft_strtrim("", " ");
	print_result("Test empty string", strcmp(trimmed, "") == 0);
	free(trimmed);
}

void test_ft_split(void)
{
	print_test_header("ft_split");
	char **arr = ft_split("Hello World 42", ' ');
	print_result("Test basic split", arr && strcmp(arr[0], "Hello") == 0 && 
				strcmp(arr[1], "World") == 0 && strcmp(arr[2], "42") == 0 && arr[3] == NULL);
	if (arr)
	{
		for (int i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
	}
	arr = ft_split("   Hello   World   ", ' ');
	print_result("Test multiple delimiters", arr && strcmp(arr[0], "Hello") == 0 && 
				strcmp(arr[1], "World") == 0 && arr[2] == NULL);
	if (arr)
	{
		for (int i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
	}
	arr = ft_split("", ' ');
	print_result("Test empty string", arr && arr[0] == NULL);
	if (arr)
		free(arr);
}

void test_ft_itoa(void)
{
	print_test_header("ft_itoa");
	char *str = ft_itoa(42);
	print_result("Test 42", strcmp(str, "42") == 0);
	free(str);
	str = ft_itoa(-42);
	print_result("Test -42", strcmp(str, "-42") == 0);
	free(str);
	str = ft_itoa(0);
	print_result("Test 0", strcmp(str, "0") == 0);
	free(str);
	str = ft_itoa(-2147483648);
	print_result("Test INT_MIN", strcmp(str, "-2147483648") == 0);
	free(str);
	str = ft_itoa(2147483647);
	print_result("Test INT_MAX", strcmp(str, "2147483647") == 0);
	free(str);
}

char test_mapi_func(unsigned int i, char c)
{
	return c + i;
}

void test_ft_strmapi(void)
{
	print_test_header("ft_strmapi");
	char *result = ft_strmapi("abc", test_mapi_func);
	print_result("Test basic strmapi", result && result[0] == 'a' && 
				result[1] == 'c' && result[2] == 'e');
	free(result);
	result = ft_strmapi("", test_mapi_func);
	print_result("Test empty string", result && strcmp(result, "") == 0);
	free(result);
}

void test_iteri_func(unsigned int i, char *c)
{
	*c = *c + i;
}

void test_ft_striteri(void)
{
	print_test_header("ft_striteri");
	char str[] = "abc";
	ft_striteri(str, test_iteri_func);
	print_result("Test basic striteri", str[0] == 'a' && str[1] == 'c' && str[2] == 'e');
}

void test_ft_putchar_fd(void)
{
	print_test_header("ft_putchar_fd");
	printf("Testing ft_putchar_fd: ");
	ft_putchar_fd('A', 1);
	printf("\n");
	print_result("Visual check", 1);
}

void test_ft_putstr_fd(void)
{
	print_test_header("ft_putstr_fd");
	printf("Testing ft_putstr_fd: ");
	ft_putstr_fd("Hello, World!", 1);
	printf("\n");
	print_result("Visual check", 1);
}

void test_ft_putendl_fd(void)
{
	print_test_header("ft_putendl_fd");
	printf("Testing ft_putendl_fd: ");
	ft_putendl_fd("Hello, World!", 1);
	print_result("Visual check (with newline)", 1);
}

void test_ft_putnbr_fd(void)
{
	print_test_header("ft_putnbr_fd");
	printf("Testing ft_putnbr_fd: ");
	ft_putnbr_fd(42, 1);
	printf(", ");
	ft_putnbr_fd(-42, 1);
	printf(", ");
	ft_putnbr_fd(0, 1);
	printf("\n");
	print_result("Visual check", 1);
}

void test_ft_lstnew(void)
{
	print_test_header("ft_lstnew");
	
	int content = 42;
	t_list *node = ft_lstnew(&content);
	print_result("Test node creation", node != NULL && *(int *)node->content == 42 && node->next == NULL);
	free(node);
}

void test_ft_lstadd_front(void)
{
	print_test_header("ft_lstadd_front");
	int c1 = 1, c2 = 2;
	t_list *lst = ft_lstnew(&c1);
	t_list *new = ft_lstnew(&c2);
	ft_lstadd_front(&lst, new);
	print_result("Test add front", lst == new && *(int *)lst->content == 2 && 
				*(int *)lst->next->content == 1);
	free(lst->next);
	free(lst);
}

void test_ft_lstsize(void)
{
	print_test_header("ft_lstsize");
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	n1->next = n2;
	n2->next = n3;
	print_result("Test size 3", ft_lstsize(n1) == 3);
	print_result("Test size NULL", ft_lstsize(NULL) == 0);
	free(n3);
	free(n2);
	free(n1);
}

void test_ft_lstlast(void)
{
	print_test_header("ft_lstlast");
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	n1->next = n2;
	n2->next = n3;
	print_result("Test last", ft_lstlast(n1) == n3);
	print_result("Test NULL", ft_lstlast(NULL) == NULL);
	free(n3);
	free(n2);
	free(n1);
}

void test_ft_lstadd_back(void)
{
	print_test_header("ft_lstadd_back");
	int c1 = 1, c2 = 2;
	t_list *lst = ft_lstnew(&c1);
	t_list *new = ft_lstnew(&c2);
	ft_lstadd_back(&lst, new);
	print_result("Test add back", lst->next == new && *(int *)new->content == 2);
	free(new);
	free(lst);
}

void del_content(void *content)
{
	(void)content;
}

void test_ft_lstdelone(void)
{
	print_test_header("ft_lstdelone");
	int c = 42;
	t_list *node = ft_lstnew(&c);
	ft_lstdelone(node, del_content);
	print_result("Test delone (no crash)", 1);
}

void test_ft_lstclear(void)
{
	print_test_header("ft_lstclear");
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	n1->next = n2;
	n2->next = n3;
	ft_lstclear(&n1, del_content);
	print_result("Test clear (no crash)", n1 == NULL);
}

void iter_func(void *content)
{
	(*(int *)content)++;
}

void test_ft_lstiter(void)
{
	print_test_header("ft_lstiter");
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	n1->next = n2;
	n2->next = n3;
	ft_lstiter(n1, iter_func);
	print_result("Test iter", c1 == 2 && c2 == 3 && c3 == 4);
	free(n3);
	free(n2);
	free(n1);
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
	print_test_header("ft_lstmap");
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	n1->next = n2;
	n2->next = n3;
	t_list *new_lst = ft_lstmap(n1, map_func, free);
	print_result("Test map", new_lst && *(int *)new_lst->content == 2 && 
				*(int *)new_lst->next->content == 4 && *(int *)new_lst->next->next->content == 6);
	ft_lstclear(&new_lst, free);
	free(n3);
	free(n2);
	free(n1);
}

int main(void)
{
	printf("\n╔════════════════════════════════════════╗\n");
	printf("║       LIBFT COMPREHENSIVE TESTER       ║\n");
	printf("╚════════════════════════════════════════╝\n");
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
	printf("\n╔════════════════════════════════════════╗\n");
	printf("║            TEST SUMMARY                ║\n");
	printf("╚════════════════════════════════════════╝\n");
	printf(GREEN "Tests passed: %d\n" RESET, g_tests_passed);
	printf(RED "Tests failed: %d\n" RESET, g_tests_failed);
	if (!g_tests_failed)
		printf(GREEN "\n🎉 All tests passed! Your libft is working perfectly!\n" RESET);
	else
		printf(RED "\n⚠️  Some tests failed. Please review your implementation.\n" RESET);
	if (g_tests_passed + g_tests_failed)
	{
		printf("\nTotal: %d/%d (%.1f%%)\n", g_tests_passed, 
			   g_tests_passed + g_tests_failed,
			   (float)g_tests_passed / (g_tests_passed + g_tests_failed) * 100);
	}
	return (g_tests_failed == 0 ? 0 : 1);
}
