#include "libft.h"
#include <stdio.h>

#define VERBOSE	0

#define GREEN	"\033[0;32m"
#define RED		"\033[0;31m"
#define RESET	"\033[0m"

int g_tests_failed = 0;

static int	all_tests_passed(const int *passed, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (passed[i] == 0)
			return 0;
	}
	return 1;
}

static void	print_test_header(const char *function_name) {
	printf("\n========================================\n");
	printf("Testing: %s\n", function_name);
	printf("========================================\n");
}

static void	print_result(const char *test_name, int passed) {
	printf("%s" RESET "%s\n", passed ? GREEN "✓ " : RED "✗ ", test_name);
	if (!passed)
		g_tests_failed++;
}

static void	test_ft_lstnew(void) {
	int		content = 42;
	t_list	*node = ft_lstnew(&content);
	int		passed[1];

	passed[0] = node != NULL && *(int *)node->content == 42 && !node->next;
	free(node);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstnew");
	print_result("Test node creation", passed[0]);
}

static void	test_ft_lstadd_front(void) {
	int c1 = 1, c2 = 2;
	t_list *lst = ft_lstnew(&c1);
	t_list *new = ft_lstnew(&c2);
	int passed[1];

	ft_lstadd_front(&lst, new);
	passed[0] = lst == new && *(int *)lst->content == 2 && 
				*(int *)lst->next->content == 1;
	free(lst->next);
	free(lst);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstadd_front");
	print_result("Test add front", passed[0]);
}

static void	test_ft_lstsize(void) {
	int		c1 = 1, c2 = 2, c3 = 3;
	t_list	*n1 = ft_lstnew(&c1);
	t_list	*n2 = ft_lstnew(&c2);
	t_list	*n3 = ft_lstnew(&c3);
	int		passed[2];

	n1->next = n2;
	n2->next = n3;
	passed[0] = ft_lstsize(n1) == 3;
	passed[1] = !ft_lstsize(NULL);
	free(n3);
	free(n2);
	free(n1);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstsize");
	print_result("Test size 3", passed[0]);
	print_result("Test size NULL", passed[1]);
}

static void	test_ft_lstlast(void) {
	int		c1 = 1, c2 = 2, c3 = 3;
	t_list	*n1 = ft_lstnew(&c1);
	t_list	*n2 = ft_lstnew(&c2);
	t_list	*n3 = ft_lstnew(&c3);
	int		passed[2];

	n1->next = n2;
	n2->next = n3;
	passed[0] = ft_lstlast(n1) == n3;
	passed[1] = !ft_lstlast(NULL);
	free(n3);
	free(n2);
	free(n1);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstlast");
	print_result("Test last", passed[0]);
	print_result("Test NULL", passed[1]);
}

static void	test_ft_lstadd_back(void) {
	int		c1 = 1, c2 = 2;
	t_list	*lst = ft_lstnew(&c1);
	t_list	*new = ft_lstnew(&c2);
	int		passed[1];

	ft_lstadd_back(&lst, new);
	passed[0] = lst->next == new && *(int *)new->content == 2;
	free(new);
	free(lst);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstadd_back");
	print_result("Test add back", passed[0]);
}

static void	del_content(void *content) {
	(void)content;
}

static int freed_count;

static void del_count(void *content) {
	free(content);
	freed_count++;
}

static void test_ft_lstdelone(void) {
	int		*value1 = malloc(sizeof(int));
	int		*value2 = malloc(sizeof(int));
	int		*value3 = malloc(sizeof(int));
	int		passed[3];
	t_list	*lst = NULL;
	t_list	*node1, *node2, *node3;

	if (!value1 || !value2 || !value3) {
		free(value1); free(value2); free(value3);
		perror("libft-fairy: malloc");
		exit(EXIT_FAILURE);
	}
	*value1 = 1; *value2 = 2; *value3 = 3;
	node1 = ft_lstnew(value1);
	node2 = ft_lstnew(value2);
	node3 = ft_lstnew(value3);
	ft_lstadd_back(&lst, node1);
	ft_lstadd_back(&lst, node2);
	ft_lstadd_back(&lst, node3);
	node1->next = node3;
	freed_count = 0;
	ft_lstdelone(node2, del_count);
	passed[0] = (freed_count == 1);
	int correct = (*(int *)lst->content == 1)
		&& (*(int *)lst->next->content == 3)
		&& lst->next->next == NULL;
	passed[1] = correct;
	freed_count = 0;
	ft_lstclear(&lst, del_count);
	passed[2] = (freed_count == 2 && !lst);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstdelone / ft_lstclear");
	print_result("Test delone calls free once", passed[0]);
	print_result("Test delone leaves correct remaining nodes", passed[1]);
	print_result("Test lstclear frees all and sets list to NULL", passed[2]);
}

static void	test_ft_lstclear(void) {
	int 	c1 = 1, c2 = 2, c3 = 3;
	t_list	*n1 = ft_lstnew(&c1);
	t_list	*n2 = ft_lstnew(&c2);
	t_list	*n3 = ft_lstnew(&c3);
	int		passed[1];

	n1->next = n2;
	n2->next = n3;
	ft_lstclear(&n1, del_content);
	passed[0] = !n1;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstclear");
	print_result("Test clear (no crash)", passed[0]);
}

static void	iter_func(void *content) {
	(*(int *)content)++;
}

static void	test_ft_lstiter(void) {
	int 	c1 = 1, c2 = 2, c3 = 3;
	t_list	*n1 = ft_lstnew(&c1);
	t_list	*n2 = ft_lstnew(&c2);
	t_list	*n3 = ft_lstnew(&c3);
	int		passed[1];

	n1->next = n2;
	n2->next = n3;
	ft_lstiter(n1, iter_func);
	passed[0] = c1 == 2 && c2 == 3 && c3 == 4;
	free(n3);
	free(n2);
	free(n1);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstiter");
	print_result("Test iter", passed[0]);
}

static void	*map_func(void *content) {
	int *new = malloc(sizeof(int));
	if (!new)
		return NULL;
	*new = *(int *)content * 2;
	return new;
}

static void	*map_func_fail(void *content) {
	(void)content;
	return NULL;
}

static void	test_ft_lstmap(void) {
	int		c1 = 1, c2 = 2, c3 = 3;
	t_list	*n1 = ft_lstnew(&c1);
	t_list	*n2 = ft_lstnew(&c2);
	t_list	*n3 = ft_lstnew(&c3);
	t_list	*new_lst;
	int		passed[2];

	n1->next = n2;
	n2->next = n3;
	new_lst = ft_lstmap(n1, map_func, free);
	passed[0] = new_lst && *(int *)new_lst->content == 2 &&
				*(int *)new_lst->next->content == 4 &&
				*(int *)new_lst->next->next->content == 6;
	ft_lstclear(&new_lst, free);
	new_lst = ft_lstmap(n1, map_func_fail, free);
	passed[1] = !new_lst;
	ft_lstclear(&new_lst, free);
	free(n3);
	free(n2);
	free(n1);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstmap");
	print_result("Test map normal", passed[0]);
	print_result("Test malloc fail", passed[1]);
}

int main(void)
{
	test_ft_lstnew();
	test_ft_lstadd_front();
	test_ft_lstsize();
	test_ft_lstlast();
	test_ft_lstadd_back();
	test_ft_lstdelone();
	test_ft_lstclear();
	test_ft_lstiter();
	test_ft_lstmap();
	return (g_tests_failed ? 1 : 0);
}
