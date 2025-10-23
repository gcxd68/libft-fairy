#include "libft_fairy.h"

#ifndef VERBOSE
# define VERBOSE 0
#endif

static int	freed_count;

static void	free_count(void *content) {
	free(content);
	freed_count++;
}

static void	test_ft_lstnew(void) {
	int		content = 42;
	t_list	*n1 = ft_lstnew(&content);
	int		passed[3];
	
	passed[0] = (n1 != NULL);
	passed[1] = (n1 && n1->content == &content);
	passed[2] = (n1 && n1->next == NULL);
	free(n1);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstnew (bonus)");
	print_result("Test node allocated", passed[0]);
	print_result("Test content assigned", passed[1]);
	print_result("Test next is NULL", passed[2]);
}

static void	ft_lstadd_front_null_new_test(void) {
	t_list	*lst = NULL;

	ft_lstadd_front(&lst, NULL);
}

static void	test_ft_lstadd_front(void) {
	int		c1 = 1, c2 = 2;
	t_list	*n1 = safe_lstnew(&c1);
	t_list	*n2 = safe_lstnew(&c2);
	t_list	*lst = n1;
	t_list	*empty, *node;
	int		passed[3];

	ft_lstadd_front(&lst, n2);
	passed[0] = lst == n2 && *(int *)lst->content == 2
		&& *(int *)lst->next->content == 1;
	free(n1);
	free(n2);
	empty = NULL;
	node = safe_lstnew(&c1);
	ft_lstadd_front(&empty, node);
	passed[1] = empty == node && empty->next == NULL;
	free(node);
	passed[2] = !forked_test(ft_lstadd_front_null_new_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstadd_front (bonus)");
	print_result("Test add front", passed[0]);
	print_result("Test add to empty list", passed[1]);
	print_result("Test add NULL node", passed[2]);
}

static void	test_ft_lstsize(void) {
	t_list	*lst = create_test_list(1, 2, 3);
	int		passed[2];

	passed[0] = ft_lstsize(lst) == 3;
	passed[1] = !ft_lstsize(NULL);
	safe_lstclear(&lst, free);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstsize (bonus)");
	print_result("Test size 3", passed[0]);
	print_result("Test size NULL", passed[1]);
}

static void	test_ft_lstlast(void) {
	t_list	*lst = create_test_list(1, 2, 3);
	int		passed[2];

	passed[0] = ft_lstlast(lst) == lst->next->next;
	passed[1] = !ft_lstlast(NULL);
	safe_lstclear(&lst, free);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstlast (bonus)");
	print_result("Test last", passed[0]);
	print_result("Test NULL", passed[1]);
}

static void	ft_lstadd_back_null_new_test(void) {
	t_list	*lst = NULL;

	ft_lstadd_back(&lst, NULL);
}

static void	test_ft_lstadd_back(void) {
	int		c1 = 1, c2 = 2;
	t_list	*lst = safe_lstnew(&c1);
	t_list	*new = safe_lstnew(&c2);
	t_list	*empty, *node;
	int		passed[3];

	ft_lstadd_back(&lst, new);
	passed[0] = lst->next == new && *(int *)new->content == 2;
	free(new);
	free(lst);
	empty = NULL;
	node = safe_lstnew(&c1);
	ft_lstadd_back(&empty, node);
	passed[1] = empty == node && empty->next == NULL;
	free(node);
	passed[2] = !forked_test(ft_lstadd_back_null_new_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstadd_back (bonus)");
	print_result("Test add back", passed[0]);
	print_result("Test add to empty list", passed[1]);
	print_result("Test add NULL node", passed[2]);
}

static void	test_ft_lstdelone(void) {
	t_list	*lst = create_test_list(1, 2, 3);
	t_list	*to_del = lst->next;
	int		passed[2];

	freed_count = 0;
	lst->next = lst->next->next;
	ft_lstdelone(to_del, free_count);
	passed[0] = (freed_count == 1);
	int correct = (*(int *)lst->content == 1)
		&& (*(int *)lst->next->content == 3)
		&& lst->next->next == NULL;
	passed[1] = correct;
	safe_lstclear(&lst, free);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstdelone (bonus)");
	print_result("Test delone calls free once", passed[0]);
	print_result("Test delone leaves correct remaining nodes", passed[1]);
}

static void	test_ft_lstclear(void) {
	t_list	*lst = create_test_list(1, 2, 3);
	int		passed[1];

	freed_count = 0;
	ft_lstclear(&lst, free_count);
	passed[0] = !lst && freed_count == 3;
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstclear (bonus)");
	print_result("Test clear (no crash)", passed[0]);
}

static void	iter_func(void *content) {
	(*(int *)content)++;
}

static void	test_ft_lstiter(void) {
	t_list	*lst = create_test_list(1, 2, 3);
	int		passed[1];

	ft_lstiter(lst, iter_func);
	passed[0] = *(int *)lst->content == 2
		&& *(int *)lst->next->content == 3
		&& *(int *)lst->next->next->content == 4;
	safe_lstclear(&lst, free);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstiter (bonus)");
	print_result("Test iter", passed[0]);
}

static void	ft_lstmap_null_test(void) {
	t_list *lst = ft_lstmap(NULL, map_func, free);

	if (lst)
		abort();
}

static void	ft_lstmap_malloc_fail_test(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	g_malloc_count = 0;
	++g_malloc_fail_at;
	g_malloc_fail_enabled = 1;
	t_list *new_lst = ft_lstmap(lst, map_func, free);
	g_malloc_fail_enabled = 0;
	safe_lstclear(&new_lst, free);
	safe_lstclear(&lst, free);
}

static void	test_ft_lstmap(void) {
	t_list	*lst = create_test_list(1, 2, 3);
	t_list	*new_lst = ft_lstmap(lst, map_func, free);
	int		passed[8];

	passed[0] = new_lst && *(int *)new_lst->content == 2
		&& *(int *)new_lst->next->content == 4
		&& *(int *)new_lst->next->next->content == 6;
	safe_lstclear(&new_lst, free);
	safe_lstclear(&lst, free);
	passed[1] = !forked_test(ft_lstmap_null_test);
	g_malloc_fail_at = 0;
	for (int i = 2; i < 8; i++)
		passed[i] = !forked_test(ft_lstmap_malloc_fail_test);
	if (all_tests_passed(passed, sizeof(passed) / sizeof(*passed)) && !VERBOSE)
		return;
	print_test_header("ft_lstmap (bonus)");
	print_result("Test map normal", passed[0]);
	print_result("Test NULL", passed[1]);
	print_result("Test malloc fail #1 (node 1)", passed[2]);
	print_result("Test malloc fail #2 (content 1)", passed[3]);
	print_result("Test malloc fail #3 (node 2)", passed[4]);
	print_result("Test malloc fail #4 (content 2)", passed[5]);
	print_result("Test malloc fail #5 (node 3)", passed[6]);
	print_result("Test malloc fail #6 (content 3)", passed[7]);
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
