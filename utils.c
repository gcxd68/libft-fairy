#include "libft_fairy.h"
#include <stdio.h>
#include <sys/wait.h>

int	g_malloc_count = 0;
int	g_malloc_fail_at = 0;
int	g_malloc_fail_enabled = 0;
int	g_tests_failed = 0;

int	forked_test(void (*test_func)(void)) {
	pid_t	pid;
	int		status;

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
	printf("%s" RESET "%s\n", passed ? GREEN "[OK]  " : RED "[KO]  ", test_name);
	if (!passed)
		g_tests_failed++;
}

void	*__wrap_malloc(size_t size) {
	if (g_malloc_fail_enabled && ++g_malloc_count == g_malloc_fail_at)
		return NULL;
	return __real_malloc(size);
}

void	safe_free_arr(char **arr) {
	if (arr) {
		for (int i = 0; arr[i]; i++)
			free(arr[i]);
		free(arr);
	}
}

t_list *create_test_list(int c1, int c2, int c3)
{
	int	*v1 = malloc(sizeof(int));
	int	*v2 = malloc(sizeof(int));
	int	*v3 = malloc(sizeof(int));

	if (!v1 || !v2 || !v3) {
		perror("libft-fairy: malloc failed");
		free(v1); free(v2); free(v3);
		exit(EXIT_FAILURE);
	}
	*v1 = c1; *v2 = c2; *v3 = c3;
	t_list *n1 = safe_lstnew(v1);
	t_list *n2 = safe_lstnew(v2);
	t_list *n3 = safe_lstnew(v3);
	if (!n1 || !n2 || !n3) {
		perror("libft-fairy: malloc failed");
		if (n1) free(n1); else free(v1);
		if (n2) free(n2); else free(v2);
		if (n3) free(n3); else free(v3);
		return NULL;
	}
	n1->next = n2;
	n2->next = n3;
	return n1;
}

void	*map_func(void *content) {
	int	*new = malloc(sizeof(int));

	if (!new)
		return NULL;
	*new = *(int *)content * 2;
	return new;
}

t_list	*safe_lstnew(void *content) {
	t_list	*node = malloc(sizeof(t_list));

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

void	safe_lstdelone(t_list *lst, void (*del)(void*)) {
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
