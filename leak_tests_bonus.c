#include "libft_fairy.h"

static void *map_func(void *content) {
	int	*new = malloc(sizeof(int));

	if (!new)
		return NULL;
	*new = *(int *)content * 2;
	return new;
}

static void leak_test_ft_lstnew(void) {
	int		content = 42;
	t_list	*node = ft_lstnew(&content);

	free(node);
}

static void leak_test_ft_lstdelone(void) {
	int		*val = malloc(sizeof(int));
	t_list	*node;

	*val = 42;
	node = safe_lstnew(val);
	ft_lstdelone(node, free);
}

static void leak_test_ft_lstclear(void) {
	int *v1 = malloc(sizeof(int)); *v1 = 1;
	int *v2 = malloc(sizeof(int)); *v2 = 2;
	int *v3 = malloc(sizeof(int)); *v3 = 3;
	t_list *n1 = safe_lstnew(v1);
	t_list *n2 = safe_lstnew(v2);
	t_list *n3 = safe_lstnew(v3);
	n1->next = n2;
	n2->next = n3;
	ft_lstclear(&n1, free);
}

static void ft_lstmap_malloc_fail_test(void) {
	int *v1 = malloc(sizeof(int)); *v1 = 1;
	int *v2 = malloc(sizeof(int)); *v2 = 2;
	int *v3 = malloc(sizeof(int)); *v3 = 3;
	t_list *n1 = safe_lstnew(v1);
	t_list *n2 = safe_lstnew(v2);
	t_list *n3 = safe_lstnew(v3);
	n1->next = n2;
	n2->next = n3;
	g_malloc_count = 0;
	++g_malloc_fail_at;
	g_malloc_fail_enabled = 1;
	t_list *new_lst = ft_lstmap(n1, map_func, free);
	g_malloc_fail_enabled = 0;
	(void)new_lst;
	safe_lstclear(&n1, free);
}

static void leak_test_ft_lstmap(void) {
	int *v1 = malloc(sizeof(int)); *v1 = 1;
	int *v2 = malloc(sizeof(int)); *v2 = 2;
	int *v3 = malloc(sizeof(int)); *v3 = 3;
	t_list *n1 = safe_lstnew(v1);
	t_list *n2 = safe_lstnew(v2);
	t_list *n3 = safe_lstnew(v3);
	n1->next = n2;
	n2->next = n3;
	t_list *new_lst = ft_lstmap(n1, map_func, free);
	safe_lstclear(&new_lst, free);
	safe_lstclear(&n1, free);
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
