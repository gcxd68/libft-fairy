#include "libft_fairy.h"
#include <stdio.h>

static void leak_test_ft_lstnew(void) {
	int	*content = malloc(sizeof(int));

	if (!content) {
		perror("libft-fairy: malloc failed");
		exit(EXIT_FAILURE);
	}
	*content = 42;
	t_list *node = ft_lstnew(content);
	safe_lstdelone(node, free);
}

static void leak_test_ft_lstdelone(void) {
	int		*content = malloc(sizeof(int));
	t_list	*node;

	if (!content) {
		perror("libft-fairy: malloc failed");
		exit(EXIT_FAILURE);
	}
	*content = 42;
	node = safe_lstnew(content);
	ft_lstdelone(node, free);
}

static void leak_test_ft_lstclear(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	ft_lstclear(&lst, free);
}

static void ft_lstmap_malloc_fail_test(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	g_malloc_count = 0;
	++g_malloc_fail_at;
	g_malloc_fail_enabled = 1;
	t_list *new_lst = ft_lstmap(lst, map_func, free);
	g_malloc_fail_enabled = 0;
	(void)new_lst;
	safe_lstclear(&lst, free);
}

static void leak_test_ft_lstmap(void) {
	t_list	*lst = create_test_list(1, 2, 3);
	t_list	*new_lst = ft_lstmap(lst, map_func, free);

	safe_lstclear(&new_lst, free);
	safe_lstclear(&lst, free);
	g_malloc_fail_at = 0;
	for (int i = 0; i < 6; i++)
		ft_lstmap_malloc_fail_test();
}

int main(void) {
	leak_test_ft_lstnew();
	leak_test_ft_lstdelone();
	leak_test_ft_lstclear();
	leak_test_ft_lstmap();
	return 0;
}
