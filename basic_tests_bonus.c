#include "libft_fairy.h"

#ifndef VERBOSE
# define VERBOSE 0
#endif

static int	g_freed_count;

static void	free_count(void *content) {
	free(content);
	g_freed_count++;
}

static void	ft_lstnew_null_content_test(void) {
	t_list	*node = ft_lstnew(NULL);

	if (!node || node->content || node->next)
		abort();
}

static void	test_ft_lstnew(void) {
	const char		*tests[] = {
		"with content",
		"with NULL content"
	};
	const size_t	num_tests = sizeof(tests) / sizeof(*tests);
	int				passed[num_tests];
	int				content = 42;
	t_list			*node = ft_lstnew(&content);

	passed[0] = node && node->content == &content && !node->next;
	free(node);
	passed[1] = !forked_test(ft_lstnew_null_content_test);
	if (!all_tests_passed(passed, num_tests) || VERBOSE)
		print_test_results("ft_lstnew (bonus)", num_tests, tests, passed);
}

static void	ft_lstadd_front_null_list_test(void) {
	t_list	*node = safe_lstnew(&(int){42});

	ft_lstadd_front(NULL, node);
	free(node);
}

static void	ft_lstadd_front_null_new_test(void) {
	t_list	*lst = NULL;

	ft_lstadd_front(&lst, NULL);
}

static void	ft_lstadd_front_null_both_test(void) {
	ft_lstadd_front(NULL, NULL);
}

static void	test_ft_lstadd_front(void) {
	const char		*tests[] = {
		"add front",
		"add to empty list",
		"NULL list",
		"NULL new",
		"NULL both"
	};
	const size_t	num_tests = sizeof(tests) / sizeof(*tests);
	int				passed[num_tests];
	int				c1 = 1, c2 = 2;
	t_list			*n1 = safe_lstnew(&c1);
	t_list			*n2 = safe_lstnew(&c2);
	t_list			*lst = n1;
	t_list			*empty, *node;

	ft_lstadd_front(&lst, n2);
	passed[0] = lst == n2 && *(int *)lst->content == 2 && *(int *)lst->next->content == 1;
	free(n1);
	free(n2);
	empty = NULL;
	node = safe_lstnew(&c1);
	ft_lstadd_front(&empty, node);
	passed[1] = empty == node && empty->next == NULL;
	free(node);
	passed[2] = !forked_test(ft_lstadd_front_null_list_test);
	passed[3] = !forked_test(ft_lstadd_front_null_new_test);
	passed[4] = !forked_test(ft_lstadd_front_null_both_test);
	if (!all_tests_passed(passed, num_tests) || VERBOSE)
		print_test_results("ft_lstadd_front (bonus)", num_tests, tests, passed);
}

static void	test_ft_lstsize(void) {
	const char		*tests[] = {
		"size 3",
		"size NULL"
	};
	const size_t	num_tests = sizeof(tests) / sizeof(*tests);
	t_list	*lst = create_test_list(1, 2, 3);
	const int		passed[] = {
		ft_lstsize(lst) == 3,
		!ft_lstsize(NULL)
	};

	safe_lstclear(&lst, free);
	if (!all_tests_passed(passed, num_tests) || VERBOSE)
		print_test_results("ft_lstsize (bonus)", num_tests, tests, passed);
}

static void	test_ft_lstlast(void) {
	const char		*tests[] = {
		"last",
		"NULL"
	};
	const size_t	num_tests = sizeof(tests) / sizeof(*tests);
	t_list			*lst = create_test_list(1, 2, 3);
	const int		passed[] = {
		ft_lstlast(lst) == lst->next->next,
		!ft_lstlast(NULL)
	};

	safe_lstclear(&lst, free);
	if (!all_tests_passed(passed, num_tests) || VERBOSE)
		print_test_results("ft_lstlast (bonus)", num_tests, tests, passed);
}

static void	ft_lstadd_back_null_list_test(void) {
	t_list	*node = safe_lstnew(&(int){42});

	ft_lstadd_back(NULL, node);
	free(node);
}

static void	ft_lstadd_back_null_new_test(void) {
	t_list	*lst = NULL;

	ft_lstadd_back(&lst, NULL);
}

static void	ft_lstadd_back_null_both_test(void) {
	ft_lstadd_back(NULL, NULL);
}

static void	test_ft_lstadd_back(void) {
	const char		*tests[] = {
		"add back",
		"add to empty list",
		"NULL list",
		"NULL new",
		"NULL both"
	};
	const size_t	num_tests = sizeof(tests) / sizeof(*tests);
	int				passed[num_tests];
	int				c1 = 1, c2 = 2;
	t_list			*lst = safe_lstnew(&c1);
	t_list			*new = safe_lstnew(&c2);
	t_list			*empty, *node;

	ft_lstadd_back(&lst, new);
	passed[0] = lst->next == new && *(int *)new->content == 2;
	free(new);
	free(lst);
	empty = NULL;
	node = safe_lstnew(&c1);
	ft_lstadd_back(&empty, node);
	passed[1] = empty == node && !empty->next;
	free(node);
	passed[2] = !forked_test(ft_lstadd_back_null_list_test);
	passed[3] = !forked_test(ft_lstadd_back_null_new_test);
	passed[4] = !forked_test(ft_lstadd_back_null_both_test);
	if (!all_tests_passed(passed, num_tests) || VERBOSE)
		print_test_results("ft_lstadd_back (bonus)", num_tests, tests, passed);
}

static void	ft_lstdelone_null_node_test(void) {
	ft_lstdelone(NULL, free);
}

static void	ft_lstdelone_null_func_test(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	ft_lstdelone(lst, NULL);
	safe_lstclear(&lst, free);
}

static void	ft_lstdelone_null_both_test(void) {
	ft_lstdelone(NULL, NULL);
}

static void	test_ft_lstdelone(void) {
	const char		*tests[] = {
		"free once",
		"correct remaining nodes",
		"NULL node",
		"NULL function",
		"NULL both"
	};
	const size_t	num_tests = sizeof(tests) / sizeof(*tests);
	int				passed[num_tests];
	t_list			*lst = create_test_list(1, 2, 3);
	t_list			*to_del = lst->next;

	lst->next = lst->next->next;
	g_freed_count = 0;
	ft_lstdelone(to_del, free_count);
	passed[0] = (g_freed_count == 1);
	int correct = (*(int *)lst->content == 1)
		&& (*(int *)lst->next->content == 3)
		&& lst->next->next == NULL;
	passed[1] = correct;
	safe_lstclear(&lst, free);
	passed[2] = !forked_test(ft_lstdelone_null_node_test);
	passed[3] = !forked_test(ft_lstdelone_null_func_test);
	passed[4] = !forked_test(ft_lstdelone_null_both_test);
	if (!all_tests_passed(passed, num_tests) || VERBOSE)
		print_test_results("ft_lstdelone (bonus)", num_tests, tests, passed);
}

static void	ft_lstclear_null_list_test(void) {
	ft_lstclear(NULL, free);
}

static void	ft_lstclear_null_func_test(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	ft_lstclear(&lst, NULL);
	safe_lstclear(&lst, free);
}

static void	ft_lstclear_null_both_test(void) {
	ft_lstclear(NULL, NULL);
}

static void	test_ft_lstclear(void) {
	const char		*tests[] = {
		"basic",
		"NULL list",
		"NULL function",
		"NULL both"
	};
	const size_t	num_tests = sizeof(tests) / sizeof(*tests);
	int				passed[num_tests];
	t_list			*lst = create_test_list(1, 2, 3);

	g_freed_count = 0;
	ft_lstclear(&lst, free_count);
	passed[0] = !lst && g_freed_count == 3;
	passed[1] = !forked_test(ft_lstclear_null_list_test);
	passed[2] = !forked_test(ft_lstclear_null_func_test);
	passed[3] = !forked_test(ft_lstclear_null_both_test);
	if (!all_tests_passed(passed, num_tests) || VERBOSE)
		print_test_results("ft_lstclear (bonus)", num_tests, tests, passed);
}

static void	iter_func(void *content) {
	(*(int *)content)++;
}

static void	ft_lstiter_null_list_test(void) {
	ft_lstiter(NULL, iter_func);
}

static void	ft_lstiter_null_func_test(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	ft_lstiter(lst, NULL);
	safe_lstclear(&lst, free);
}

static void	ft_lstiter_null_both_test(void) {
	ft_lstiter(NULL, NULL);
}

static void	test_ft_lstiter(void) {
	const char		*tests[] = {
		"iter",
		"NULL list",
		"NULL function",
		"NULL both"
	};
	const size_t	num_tests = sizeof(tests) / sizeof(*tests);
	int				passed[num_tests];
	t_list			*lst = create_test_list(1, 2, 3);

	ft_lstiter(lst, iter_func);
	passed[0] = *(int *)lst->content == 2
		&& *(int *)lst->next->content == 3
		&& *(int *)lst->next->next->content == 4;
	safe_lstclear(&lst, free);
	passed[1] = !forked_test(ft_lstiter_null_list_test);
	passed[2] = !forked_test(ft_lstiter_null_func_test);
	passed[3] = !forked_test(ft_lstiter_null_both_test);
	if (!all_tests_passed(passed, num_tests) || VERBOSE)
		print_test_results("ft_lstiter (bonus)", num_tests, tests, passed);
}

static void	ft_lstmap_null_list_test(void) {
	t_list *lst = ft_lstmap(NULL, map_func_dynamic_content, free);

	if (lst)
		abort();
}

static void	ft_lstmap_null_func_test(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	ft_lstmap(lst, NULL, free);
	safe_lstclear(&lst, free);
}

static void	ft_lstmap_null_both_test(void) {
	ft_lstmap(NULL, NULL, free);
}

static void	ft_lstmap_malloc_fail_test(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	g_malloc_count = 0;
	++g_malloc_fail_at;
	g_malloc_wrap_enabled = 1;
	t_list *new_lst = ft_lstmap(lst, map_func_dynamic_content, free);
	g_malloc_wrap_enabled = 0;
	safe_lstclear(&new_lst, free);
	safe_lstclear(&lst, free);
}

static void	test_ft_lstmap(void) {
	const char		*tests[] = {
		"basic",
		"NULL list",
		"NULL function",
		"NULL both",
		"malloc fail #1 (node 1)",
		"malloc fail #2 (content 1)",
		"malloc fail #3 (node 2)",
		"malloc fail #4 (content 2)",
		"malloc fail #5 (node 3)",
		"malloc fail #6 (content 3)"
	};
	const size_t	num_tests = sizeof(tests) / sizeof(*tests);
	int				passed[num_tests];
	t_list			*lst = create_test_list(1, 2, 3);
	t_list			*new_lst = ft_lstmap(lst, map_func_dynamic_content, free);

	passed[0] = new_lst && *(int *)new_lst->content == 2
		&& *(int *)new_lst->next->content == 4
		&& *(int *)new_lst->next->next->content == 6;
	safe_lstclear(&new_lst, free);
	safe_lstclear(&lst, free);
	passed[1] = !forked_test(ft_lstmap_null_list_test);
	passed[2] = !forked_test(ft_lstmap_null_func_test);
	passed[3] = !forked_test(ft_lstmap_null_both_test);
	g_malloc_fail_at = 0;
	for (int i = 4; i < 10; i++)
		passed[i] = !forked_test(ft_lstmap_malloc_fail_test);
	if (!all_tests_passed(passed, num_tests) || VERBOSE)
		print_test_results("ft_lstmap (bonus)", num_tests, tests, passed);
}

int	main(void) {
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
