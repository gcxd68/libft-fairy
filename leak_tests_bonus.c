#include "libft_fairy.h"
#include <stdio.h>
#include <stdlib.h>

static void	leak_test_ft_lstnew(void) {
	int	*content = malloc(sizeof(int));

	if (!content) {
		perror("libft-fairy: malloc failed");
		exit(EXIT_FAILURE);
	}
	*content = 42;
	t_list *node = ft_lstnew(content);
	if (node)
	{
		free(node->content);
		free(node);
	}
}

static void	leak_test_ft_lstdelone(void) {
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

static void	leak_test_ft_lstclear(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	ft_lstclear(&lst, free);
}

static void	ft_lstmap_basic_test(void) {
	t_list	*lst = create_test_list(1, 2, 3);
	t_list	*new_lst = ft_lstmap(lst, map_func_dynamic_content, free);

	while (new_lst)
	{
		t_list *tmp = new_lst->next;
		free(new_lst->content);
		free(new_lst);
		new_lst = tmp;
	}
	while (lst)
	{
		t_list *tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

static void	*map_func_shared_content(void *content) {
	return content;
}

static void	ft_lstmap_shared_content_test(void)
{
	t_list	*lst = create_test_list(1, 2, 3);

	g_malloc_count = 0;
	++g_malloc_fail_at;
	g_malloc_wrap_enabled = 1;
	t_list *new_lst = ft_lstmap(lst, map_func_shared_content, del_func_dummy);
	g_malloc_wrap_enabled = 0;
	(void)new_lst;
	while (lst)
	{
		t_list *tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

static void	*map_func_static_content(void *content) {
	const int	value = (int)(size_t)content;

	return (void *)(size_t)(value * 10);
}

static void	ft_lstmap_static_content_test(void)
{
	t_list	*lst = safe_lstnew((void *)(size_t)1);

	safe_lstadd_back(&lst, safe_lstnew((void *)(size_t)2));
	safe_lstadd_back(&lst, safe_lstnew((void *)(size_t)3));
	g_malloc_count = 0;
	++g_malloc_fail_at;
	g_malloc_wrap_enabled = 1;
	t_list	*new_lst = ft_lstmap(lst, map_func_static_content, del_func_dummy);
	g_malloc_wrap_enabled = 0;
	(void)new_lst;
	free(lst->next->next);
	free(lst->next);
	free(lst);
}

/*static void	ft_lstmap_dynamic_content_test(void) {
	t_list	*lst = create_test_list(1, 2, 3);

	g_malloc_count = 0;
	++g_malloc_fail_at;
	g_malloc_wrap_enabled = 1;
	t_list *new_lst = ft_lstmap(lst, map_func_dynamic_content, free);
	g_malloc_wrap_enabled = 0;
	(void)new_lst;
	while (lst)
	{
		t_list *tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}*/

static void	leak_test_ft_lstmap(void) {
	ft_lstmap_basic_test();
	g_malloc_fail_at = 0;
	for (int i = 0; i < 3; i++)
		ft_lstmap_shared_content_test();
	g_malloc_fail_at = 0;
	for (int i = 0; i < 3; i++)
		ft_lstmap_static_content_test();
/*	g_malloc_fail_at = 0;
	for (int i = 0; i < 6; i++)
		ft_lstmap_dynamic_content_test();*/
}

int	main(void) {
	leak_test_ft_lstnew();
	leak_test_ft_lstdelone();
	leak_test_ft_lstclear();
	leak_test_ft_lstmap();
	return 0;
}
