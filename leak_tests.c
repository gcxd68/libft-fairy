#include "libft.h"

static void ft_free_split(char **arr) {
	if (!arr)
		return;
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

static char mapi_func(unsigned int i, char c) {
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
	char	*sub = ft_substr("Hello World", 0, 5);

	free(sub);
}

static void leak_test_ft_strjoin(void) {
	char	*joined = ft_strjoin("Hello", " World");

	free(joined);
}

static void leak_test_ft_strtrim(void) {
	char	*trimmed = ft_strtrim("   Hello World   ", " ");

	free(trimmed);
}

static void leak_test_ft_split(void) {
	char	**arr = ft_split("Hello World Test 42", ' ');

	ft_free_split(arr);
}

static void leak_test_ft_itoa(void) {
	char	*num1 = ft_itoa(42);
	char	*num2 = ft_itoa(-2147483648);

	free(num1);
	free(num2);
}

static void leak_test_ft_strmapi(void) {
	char	*mapped = ft_strmapi("abc", mapi_func);

	free(mapped);
}

int main(void) {
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
