#include "libft.h"
#include <stdio.h>
#include <string.h>

static void ft_free_split(char **arr)
{
	if (!arr)
		return;
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

static void *map_func(void *content)
{
	int *new = malloc(sizeof(int));
	if (!new)
		return NULL;
	*new = *(int *)content * 2;
	return new;
}

static void del_content(void *content)
{
	free(content);
}

static char mapi_func(unsigned int i, char c)
{
	return c + i;
}

static void	leak_test_ft_calloc(void)
{
	void *ptr = ft_calloc(10, sizeof(int));
	free(ptr);
	ptr = ft_calloc(0, 5);
	free(ptr);
	ptr = ft_calloc(5, 0);
	free(ptr);
}

static void	leak_test_ft_strdup(void)
{
	char *dup = ft_strdup("Hello World");
	free(dup);
	dup = ft_strdup("");
	free(dup);
}

static void	leak_test_ft_substr(void)
{
	char *sub = ft_substr("Hello World", 0, 5);
	free(sub);
	sub = ft_substr("Hello", 10, 5);
	free(sub);
	sub = ft_substr("Hello", 2, 100);
	free(sub);
	sub = ft_substr("Test", 0, 0);
	free(sub);
}

static void leak_test_ft_strjoin(void)
{
	char *joined = ft_strjoin("Hello", " World");
	free(joined);
	joined = ft_strjoin("", "Test");
	free(joined);
	joined = ft_strjoin("Test", "");
	free(joined);
}

static void leak_test_ft_strtrim(void)
{
	char *trimmed = ft_strtrim("   Hello World   ", " ");
	free(trimmed);
	trimmed = ft_strtrim("xxxHelloxxx", "x");
	free(trimmed);
	trimmed = ft_strtrim("xxxxx", "x");
	free(trimmed);
}

static void leak_test_ft_split(void)
{
	char **arr = ft_split("Hello World Test 42", ' ');
	ft_free_split(arr);
	arr = ft_split("   Hello   World   ", ' ');
	ft_free_split(arr);
	arr = ft_split("", ' ');
	ft_free_split(arr);
	arr = ft_split("xxxxx", 'x');
	ft_free_split(arr);
}

static void leak_test_ft_itoa(void)
{
	char *num = ft_itoa(42);
	free(num);
	num = ft_itoa(-42);
	free(num);
	num = ft_itoa(0);
	free(num);
	num = ft_itoa(INT_MAX);
	free(num);
	num = ft_itoa(INT_MIN);
	free(num);
}

static void leak_test_ft_strmapi(void)
{
	char *mapped = ft_strmapi("abc", mapi_func);
	free(mapped);
	mapped = ft_strmapi("", mapi_func);
	free(mapped);
}

static void leak_test_ft_lstnew(void)
{
	int content = 42;
	t_list *node = ft_lstnew(&content);
	free(node);
}

static void leak_test_ft_lstadd_front_back(void)
{
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *lst = NULL;
	ft_lstadd_front(&lst, ft_lstnew(&c1));
	ft_lstadd_back(&lst, ft_lstnew(&c2));
	ft_lstadd_front(&lst, ft_lstnew(&c3));
	t_list *tmp;
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

static void leak_test_ft_lstdelone(void)
{
	int *val = malloc(sizeof(int));
	*val = 42;
	t_list *node = ft_lstnew(val);
	ft_lstdelone(node, del_content);
}

static void leak_test_ft_lstclear(void)
{
	int *v1 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	int *v3 = malloc(sizeof(int));
	*v1 = 1; *v2 = 2; *v3 = 3;
	t_list *n1 = ft_lstnew(v1);
	t_list *n2 = ft_lstnew(v2);
	t_list *n3 = ft_lstnew(v3);
	n1->next = n2;
	n2->next = n3;
	ft_lstclear(&n1, del_content);
}

static void leak_test_ft_lstiter(void)
{
	int c1 = 1, c2 = 2, c3 = 3;
	t_list *n1 = ft_lstnew(&c1);
	t_list *n2 = ft_lstnew(&c2);
	t_list *n3 = ft_lstnew(&c3);
	n1->next = n2;
	n2->next = n3;
	ft_lstiter(n1, NULL);
	t_list *tmp;
	while (n1)
	{
		tmp = n1->next;
		free(n1);
		n1 = tmp;
	}
}

static void leak_test_ft_lstmap(void)
{
	int *v1 = malloc(sizeof(int));
	int *v2 = malloc(sizeof(int));
	int *v3 = malloc(sizeof(int));
	*v1 = 1; *v2 = 2; *v3 = 3;
	t_list *n1 = ft_lstnew(v1);
	t_list *n2 = ft_lstnew(v2);
	t_list *n3 = ft_lstnew(v3);
	n1->next = n2;
	n2->next = n3;
	t_list *new_lst = ft_lstmap(n1, map_func, del_content);
	ft_lstclear(&new_lst, del_content);
	ft_lstclear(&n1, del_content);
}

int main(void)
{
	leak_test_ft_calloc();
	leak_test_ft_strdup();
	leak_test_ft_substr();
	leak_test_ft_strjoin();
	leak_test_ft_strtrim();
	leak_test_ft_split();
	leak_test_ft_itoa();
	leak_test_ft_strmapi();
	leak_test_ft_lstnew();
	leak_test_ft_lstadd_front_back();
	leak_test_ft_lstdelone();
	leak_test_ft_lstclear();
	leak_test_ft_lstiter();
	leak_test_ft_lstmap();
	return 0;
}
