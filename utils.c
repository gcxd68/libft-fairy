#include "libft_fairy.h"

int	g_malloc_wrap_enabled = 0;
int	g_malloc_zero;
int	g_malloc_count;
int	g_malloc_fail_at;
int	g_tests_failed = 0;

void	*__wrap_malloc(size_t size) {
	if (g_malloc_wrap_enabled && ++g_malloc_count == g_malloc_fail_at)
		return NULL;
	g_malloc_zero = 0;
	if (!size)
		g_malloc_zero = 1;
	return __real_malloc(size);
}

int	all_tests_passed(const int *passed, const size_t num_tests) {
	for (size_t i = 0; i < num_tests; i++) {
		if (!passed[i])
			return 0;
	}
	return 1;
}

void	del_func_dummy(void *content) {
	(void)content;
}

#include <stdlib.h>

void	*map_func_dynamic_content(void *content) {
	int	*new = malloc(sizeof(int));

	if (!new)
		return NULL;
	*new = *(int *)content * 2;
	return new;
}

void	safe_free_arr(char ***arr) {
	if (*arr) {
		for (int i = 0; (*arr)[i]; i++) {
			free((*arr)[i]);
			(*arr)[i] = NULL;
		}
		free(*arr);
		*arr = NULL;
	}
}

#include <stdio.h>

void	print_test_results(char *function_name, const size_t num_tests, const char *tests[], const int passed[]) {
	printf("\n========================================\n");
	printf("%s\n", function_name);
	printf("========================================\n");
	for (size_t i = 0; i < num_tests; i++) {
		printf("%s" RESET "  Test %s\n", passed[i] ? GREEN "[OK]" : RED "[KO]", tests[i]);
		if (!passed[i])
			g_tests_failed++;
	}
}

void	error_exit(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void	*xmalloc(size_t size) {
	void	*ptr = malloc(size);

	if (ptr)
		return ptr;
	error_exit("libft-fairy: malloc failed");
	return NULL;
}

t_list	*create_test_list(int c1, int c2, int c3, int use_static) {
	int *v1, *v2, *v3;

	if (use_static)
	{
		static int s1, s2, s3;
		s1 = c1; s2 = c2; s3 = c3;
		v1 = &s1; v2 = &s2; v3 = &s3;
	}
	else
	{
		v1 = malloc(sizeof(int));
		v2 = malloc(sizeof(int));
		v3 = malloc(sizeof(int));
		if (!v1 || !v2 || !v3)
		{
			free(v1); free(v2); free(v3);
			error_exit("libft-fairy: malloc failed");
		}
		*v1 = c1; *v2 = c2; *v3 = c3;
	}
	t_list *n1 = malloc(sizeof(t_list));
	t_list *n2 = malloc(sizeof(t_list));
	t_list *n3 = malloc(sizeof(t_list));
	if (!n1 || !n2 || !n3)
	{
		if (n1) free(n1); else if (!use_static) free(v1);
		if (n2) free(n2); else if (!use_static) free(v2);
		if (n3) free(n3); else if (!use_static) free(v3);
		error_exit("libft-fairy: malloc failed");
	}
	n1->content = v1;
	n2->content = v2;
	n3->content = v3;
	n1->next = n2;
	n2->next = n3;
	n3->next = NULL;
	return n1;
}

#include <unistd.h>
#include <sys/wait.h>

static pid_t	xwaitpid(pid_t pid, int *status, int options)
{
	pid_t    ret = waitpid(pid, status, options);
	if (ret == -1)
		error_exit("libft-fairy: waitpid failed");
	return ret;
}

int	forked_test(void (*test_func)(void)) {
	pid_t	pid;
	int		status;

	fflush(stdout);
	pid = fork();
	if (pid == -1)
		error_exit("libft-fairy: fork failed");
	if (!pid) {
		test_func();
		exit(EXIT_SUCCESS);
	}
	xwaitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return 1;
	return 0;
}
