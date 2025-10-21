#include "libft_fairy.h"

static void *map_func(void *content) {
	int	*new = malloc(sizeof(int));

	if (!new)
		return NULL;
	*new = *(int *)content * 2;
	return new;
}

static void del_content(void *content) {
	free(content);
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
	ft_lstdelone(node, del_content);
}

static void leak_test_ft_lstclear(void) {
	int		*v1 = malloc(sizeof(int));
	int		*v2 = malloc(sizeof(int));
	int		*v3 = malloc(sizeof(int));
	t_list	*n1, *n2, *n3;

	*v1 = 1;
	*v2 = 2;
	*v3 = 3;
	n1 = safe_lstnew(v1);
	n2 = safe_lstnew(v2);
	n3 = safe_lstnew(v3);
	n1->next = n2;
	n2->next = n3;
	ft_lstclear(&n1, del_content);
}

static void leak_test_ft_lstmap(void) {
	int		*v1 = malloc(sizeof(int));
	int		*v2 = malloc(sizeof(int));
	int		*v3 = malloc(sizeof(int));
	t_list	*n1, *n2, *n3, *new_lst;

	*v1 = 1;
	*v2 = 2;
	*v3 = 3;
	n1 = safe_lstnew(v1);
	n2 = safe_lstnew(v2);
	n3 = safe_lstnew(v3);
	n1->next = n2;
	n2->next = n3;
	new_lst = ft_lstmap(n1, map_func, del_content);
	safe_lstclear(&new_lst, del_content);
	safe_lstclear(&n1, del_content);
}

int main(void) {
	leak_test_ft_lstnew();
	leak_test_ft_lstdelone();
	leak_test_ft_lstclear();
	leak_test_ft_lstmap();
	return 0;
}
