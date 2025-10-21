#include "libft_fairy.h"
#include "stdio.h"

int g_tests_failed = 0;

int	all_tests_passed(const int *passed, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (passed[i] == 0)
			return 0;
	}
	return 1;
}

void	print_test_header(const char *function_name) {
	printf("\n========================================\n");
	printf("%s\n", function_name);
	printf("========================================\n");
}

void	print_result(const char *test_name, int passed) {
	printf("%s" RESET "%s\n", passed ? GREEN "✓ " : RED "✗ ", test_name);
	if (!passed)
		g_tests_failed++;
}

void	safe_free_arr(char **arr) {
	if (arr) {
		for (int i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
	}
}

t_list	*safe_lstnew(void *content) {
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

static t_list	*safe_lstlast(t_list *lst) {
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	safe_lstadd_back(t_list **lst, t_list *new) {
	if (!lst || !new)
		return ;
	if (*lst)
		safe_lstlast(*lst)->next = new;
	else
		*lst = new;
}

static void	safe_lstdelone(t_list *lst, void (*del)(void*)) {
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	safe_lstclear(t_list **lst, void (*del)(void*)) {
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		safe_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}
