#ifndef LIBFT_FAIRY_H
# define LIBFT_FAIRY_H

#include "libft.h"

#define GREEN	"\033[0;32m"
#define RED		"\033[0;31m"
#define RESET	"\033[0m"

extern int	g_malloc_count;
extern int	g_malloc_fail_at;
extern int	g_malloc_fail_enabled;
extern int  g_tests_failed;

int			forked_test(void (*test_func)(void));
int			all_tests_passed(const int *passed, size_t n);
void		print_test_header(const char *function_name);
void		print_result(const char *test_name, int passed);
void		*__real_malloc(size_t size);
void		*__wrap_malloc(size_t size);
void		safe_free_arr(char **arr);
t_list		*safe_lstnew(void *content);
void		safe_lstadd_back(t_list **lst, t_list *new);
void		safe_lstclear(t_list **lst, void (*del)(void*));

#endif //LIBFT_FAIRY_H
