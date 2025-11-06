#include "libft_fairy.h"
#include <stdlib.h>

static char	mapi_func(unsigned int i, char c) {
	return c + i;
}

static void	leak_test_ft_calloc(void) {
	void	*ptr = ft_calloc(10, sizeof(int));

	free(ptr);
}

static void	leak_test_ft_strdup(void) {
	char	*dup = ft_strdup("Hello World");

	free(dup);
}

static void	leak_test_ft_substr(void) {
	char	*sub1 = ft_substr("Hello World", 0, 5);
	//char	*sub2 = ft_substr("hola", ~(unsigned int)0, ~(size_t)0);

	free(sub1);
	//free(sub2);
}

static void	leak_test_ft_strjoin(void) {
	char	*joined = ft_strjoin("Hello", " World");

	free(joined);
}

static void	leak_test_ft_strtrim(void) {
	char	*trimmed = ft_strtrim("   Hello World   ", " ");

	free(trimmed);
}

static void	ft_split_malloc_fail_test(void) {
	g_malloc_count = 0;
	++g_malloc_fail_at;
	ft_split("Hello World Test", ' ');
}

static void	leak_test_ft_split(void) {
	char	**arr = ft_split("Hello World Test 42", ' ');

	safe_free_arr(&arr);
	g_malloc_wrap_enabled = 1;
	g_malloc_fail_at = 0;
	for (int i = 0; i < 4; i++)
		ft_split_malloc_fail_test();
	g_malloc_wrap_enabled = 0;
}

static void	leak_test_ft_itoa(void) {
	char	*num1 = ft_itoa(42);
	char	*num2 = ft_itoa(-2147483648);

	free(num1);
	free(num2);
}

static void	leak_test_ft_strmapi(void) {
	char	*mapped = ft_strmapi("abc", mapi_func);

	free(mapped);
}

int	main(void) {
	leak_test_ft_calloc();
	leak_test_ft_strdup();
	leak_test_ft_substr();
	leak_test_ft_strjoin();
	leak_test_ft_strtrim();
	leak_test_ft_split();
	leak_test_ft_itoa();
	leak_test_ft_strmapi();
	return 0;
}
