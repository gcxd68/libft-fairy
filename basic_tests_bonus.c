#include "libft_fairy.h"
#include <stdio.h>

#ifndef VERBOSE
# define VERBOSE 0
#endif

static void test_ft_lstnew(void) {
	int		content = 42;
	t_list	*node = ft_lstnew(&content);
	int		passed[3];
	
	passed[0] = (node != NULL);
	passed[1] = (node && node->content == &content);
	passed[2] = (node && node->next == NULL);
	free(node);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstnew (bonus)");
	print_result("Test node allocated", passed[0]);
	print_result("Test content assigned", passed[1]);
	print_result("Test next is NULL", passed[2]);
}

static void	test_ft_lstadd_front(void) {
	int c1 = 1, c2 = 2;
	t_list *lst = safe_lstnew(&c1);
	t_list *new = safe_lstnew(&c2);
	int passed[1];

	ft_lstadd_front(&lst, new);
	passed[0] = lst == new && *(int *)lst->content == 2 && 
				*(int *)lst->next->content == 1;
	free(lst->next);
	free(lst);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstadd_front (bonus)");
	print_result("Test add front", passed[0]);
}

static void	test_ft_lstsize(void) {
	int		c1 = 1, c2 = 2, c3 = 3;
	t_list	*n1 = safe_lstnew(&c1);
	t_list	*n2 = safe_lstnew(&c2);
	t_list	*n3 = safe_lstnew(&c3);
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
	print_test_header("ft_lstsize (bonus)");
	print_result("Test size 3", passed[0]);
	print_result("Test size NULL", passed[1]);
}

static void	test_ft_lstlast(void) {
	int		c1 = 1, c2 = 2, c3 = 3;
	t_list	*n1 = safe_lstnew(&c1);
	t_list	*n2 = safe_lstnew(&c2);
	t_list	*n3 = safe_lstnew(&c3);
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
	print_test_header("ft_lstlast (bonus)");
	print_result("Test last", passed[0]);
	print_result("Test NULL", passed[1]);
}

static void	test_ft_lstadd_back(void) {
	int		c1 = 1, c2 = 2;
	t_list	*lst = safe_lstnew(&c1);
	t_list	*new = safe_lstnew(&c2);
	int		passed[1];

	ft_lstadd_back(&lst, new);
	passed[0] = lst->next == new && *(int *)new->content == 2;
	free(new);
	free(lst);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstadd_back (bonus)");
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
	int		passed[2];
	t_list	*lst = NULL;
	t_list	*node1, *node2, *node3;

	if (!value1 || !value2 || !value3) {
		free(value1); free(value2); free(value3);
		perror("libft-fairy: malloc");
		exit(EXIT_FAILURE);
	}
	*value1 = 1; *value2 = 2; *value3 = 3;
	node1 = safe_lstnew(value1);
	node2 = safe_lstnew(value2);
	node3 = safe_lstnew(value3);
	safe_lstadd_back(&lst, node1);
	safe_lstadd_back(&lst, node2);
	safe_lstadd_back(&lst, node3);
	node1->next = node3;
	freed_count = 0;
	ft_lstdelone(node2, del_count);
	passed[0] = (freed_count == 1);
	int correct = (*(int *)lst->content == 1)
		&& (*(int *)lst->next->content == 3)
		&& lst->next->next == NULL;
	passed[1] = correct;
	safe_lstclear(&lst, del_count);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstdelone (bonus)");
	print_result("Test delone calls free once", passed[0]);
	print_result("Test delone leaves correct remaining nodes", passed[1]);
}

static void	test_ft_lstclear(void) {
	int 	c1 = 1, c2 = 2, c3 = 3;
	t_list	*n1 = safe_lstnew(&c1);
	t_list	*n2 = safe_lstnew(&c2);
	t_list	*n3 = safe_lstnew(&c3);
	int		passed[1];

	n1->next = n2;
	n2->next = n3;
	ft_lstclear(&n1, del_content);
	passed[0] = !n1;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstclear (bonus)");
	print_result("Test clear (no crash)", passed[0]);
}

static void	iter_func(void *content) {
	(*(int *)content)++;
}

static void	test_ft_lstiter(void) {
	int 	c1 = 1, c2 = 2, c3 = 3;
	t_list	*n1 = safe_lstnew(&c1);
	t_list	*n2 = safe_lstnew(&c2);
	t_list	*n3 = safe_lstnew(&c3);
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
	print_test_header("ft_lstiter (bonus)");
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
	t_list	*n1 = safe_lstnew(&c1);
	t_list	*n2 = safe_lstnew(&c2);
	t_list	*n3 = safe_lstnew(&c3);
	t_list	*new_lst;
	int		passed[2];

	n1->next = n2;
	n2->next = n3;
	new_lst = ft_lstmap(n1, map_func, free);
	passed[0] = new_lst && *(int *)new_lst->content == 2 &&
				*(int *)new_lst->next->content == 4 &&
				*(int *)new_lst->next->next->content == 6;
	safe_lstclear(&new_lst, free);
	new_lst = ft_lstmap(n1, map_func_fail, free);
	passed[1] = !new_lst;
	safe_lstclear(&new_lst, free);
	free(n3);
	free(n2);
	free(n1);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstmap (bonus)");
	print_result("Test map normal", passed[0]);
	print_result("Test malloc fail", passed[1]);
}

int main(void) {
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
