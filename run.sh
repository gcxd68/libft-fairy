#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
PINK='\033[0;95m'
YELLOW='\033[0;33m'
RESET='\033[0m'

VERBOSE=0
for arg in "$@"; do
	case $arg in
		-v|--verbose)
			VERBOSE=1
			;;
	esac
done

LIBFT_DIR=".."
BASIC_TESTER_NAME=".basic_tests"
LEAK_TESTER_NAME=".leak_tests"
BONUS_BASIC_TESTER_NAME=".basic_tests_bonus"
BONUS_LEAK_TESTER_NAME=".leak_tests_bonus"
TESTER_DIR=$(basename "$(pwd)")
TMP_DIR="/tmp/libft_fairy_$$"

mkdir -p "$TMP_DIR"

echo_color() {
	echo -e "${2}${1}${RESET}"
}

cleanup() {
	echo -e -n "🧹 Cleaning up...\t    "
	rm -rf "$TMP_DIR" *.o $BASIC_TESTER_NAME $LEAK_TESTER_NAME \
		$BONUS_BASIC_TESTER_NAME $BONUS_LEAK_TESTER_NAME .results
	make -C $LIBFT_DIR fclean > /dev/null 2>&1
	echo "Done"
	echo ""
}

trap cleanup EXIT INT TERM

check_external_functions() {
	local func=$1
	local allowed=$2
	local obj_file="$LIBFT_DIR/${func}.o"
	[ ! -f "$obj_file" ] && return 0
	local externals=$(nm -u "$obj_file" 2>/dev/null | awk '{print $2}')
	local forbidden=""
	for ext in $externals; do
		[[ "$ext" == ft_* || "$ext" == __* ]] && continue
		[[ ! " $allowed " =~ " $ext " ]] && forbidden="$forbidden $ext"
	done
	if [ -n "$forbidden" ]; then
		echo "$func: forbidden function detected:$forbidden"
		return 1
	fi
	return 0
}

check_externals_batch() {
	local funcs=$1
	local allowed=$2
	local output=""
	local failed=0
	for func in $funcs; do
		local result
		result=$(check_external_functions "$func" "$allowed" 2>&1)
		if [ $? -ne 0 ]; then
			failed=1
			output="${output}${result}\n"
		fi
	done
	echo -e "$output"
	return $failed
}

run_basic_test() {
	local tester=$1
	local out_file=$2
	local append=$3
	if [ "$append" = "1" ]; then
		$tester >> "$TMP_DIR/stdout.tmp" 2>"$TMP_DIR/stderr.tmp"
	else
		$tester > "$TMP_DIR/stdout.tmp" 2>"$TMP_DIR/stderr.tmp"
	fi
	local exit_code=$?
	cat "$TMP_DIR/stdout.tmp" >> "$out_file"
	cat "$TMP_DIR/stderr.tmp" >> "$out_file"
	grep "Segmentation fault" "$TMP_DIR/stderr.tmp" 2>/dev/null || true
	return $exit_code
}

run_valgrind_test() {
	local tester=$1
	local log_file=$2
	{ valgrind --leak-check=full --show-leak-kinds=all \
		--errors-for-leak-kinds=all --error-exitcode=1 --track-origins=yes \
		--log-file="$log_file" "$tester" > /dev/null; } 2>"$TMP_DIR/valgrind_stderr.tmp"
	local exit_code=$?
	grep "Segmentation fault" "$TMP_DIR/valgrind_stderr.tmp" 2>/dev/null || true
	return $exit_code
}

main() {
	echo ""
	echo_color "╔══════════════════════════════╗" "$PINK"
	echo_color "║        LIBFT-FAIRY 🧚        ║" "$PINK"
	echo_color "╚══════════════════════════════╝" "$PINK"
	echo ""

	echo -e -n "📝 Checking norm..."
	NORM_OUTPUT=$(find $LIBFT_DIR -type d -name "$TESTER_DIR" -prune -o \
		\( -name "*.c" -o -name "*.h" \) -type f -print | xargs -r norminette 2>&1)
	if echo "$NORM_OUTPUT" | grep -q "Error"; then
		NORM_TEST_RES=1
		echo_color "\t  Failed" "$RED"
		echo ""
		echo "$NORM_OUTPUT" | grep "Error"
		echo ""
	else
		NORM_TEST_RES=0
		echo -e "\t    Done"
	fi

	echo -e -n "🔖 Checking version..."
	if grep -qi "bonus:" ../Makefile; then
		BONUS_VERSION=1
		echo -e "\t   Bonus"
	else
		BONUS_VERSION=0
		echo_color " Mandatory" "$YELLOW"
	fi

	echo -n "🧾 Checking prototypes..."
	errors=0
	error_messages=""
	LIBFT_H="../libft.h"
	mandatory_prototypes=(
		'int\t+ft_atoi\(const char \*nptr\);::int ft_atoi(const char *nptr);'
		'void\t+ft_bzero\(void \*s, size_t n\);::void ft_bzero(void *s, size_t n);'
		'void\t+\*ft_calloc\(size_t nmemb, size_t size\);::void *ft_calloc(size_t nmemb, size_t size);'
		'int\t+ft_isalnum\(int c\);::int ft_isalnum(int c);'
		'int\t+ft_isalpha\(int c\);::int ft_isalpha(int c);'
		'int\t+ft_isascii\(int c\);::int ft_isascii(int c);'
		'int\t+ft_isdigit\(int c\);::int ft_isdigit(int c);'
		'int\t+ft_isprint\(int c\);::int ft_isprint(int c);'
		'char\t+\*ft_itoa\(int n\);::char *ft_itoa(int n);'
		'void\t+\*ft_memchr\(const void \*s, int c, size_t n\);::void *ft_memchr(const void *s, int c, size_t n);'
		'int\t+ft_memcmp\(const void \*s1, const void \*s2, size_t n\);::int ft_memcmp(const void *s1, const void *s2, size_t n);'
		'void\t+\*ft_memcpy\(void \*dest, const void \*src, size_t n\);::void *ft_memcpy(void *dest, const void *src, size_t n);'
		'void\t+\*ft_memmove\(void \*dest, const void \*src, size_t n\);::void *ft_memmove(void *dest, const void *src, size_t n);'
		'void\t+\*ft_memset\(void \*s, int c, size_t n\);::void *ft_memset(void *s, int c, size_t n);'
		'void\t+ft_putchar_fd\(char c, int fd\);::void ft_putchar_fd(char c, int fd);'
		'void\t+ft_putendl_fd\(char \*s, int fd\);::void ft_putendl_fd(char *s, int fd);'
		'void\t+ft_putnbr_fd\(int n, int fd\);::void ft_putnbr_fd(int n, int fd);'
		'void\t+ft_putstr_fd\(char \*s, int fd\);::void ft_putstr_fd(char *s, int fd);'
		'char\t+\*\*ft_split\(char const \*s, char c\);::char **ft_split(char const *s, char c);'
		'char\t+\*ft_strchr\(const char \*s, int c\);::char *ft_strchr(const char *s, int c);'
		'char\t+\*ft_strdup\(const char \*s\);::char *ft_strdup(const char *s);'
		'void\t+ft_striteri\(char \*s, void \(\*f\)\(unsigned int, char\*\)\);::void ft_striteri(char *s, void (*f)(unsigned int, char*));'
		'char\t+\*ft_strjoin\(char const \*s1, char const \*s2\);::char *ft_strjoin(char const *s1, char const *s2);'
		'size_t\t+ft_strlcat\(char \*dst, const char \*src, size_t size\);::size_t ft_strlcat(char *dst, const char *src, size_t size);'
		'size_t\t+ft_strlcpy\(char \*dst, const char \*src, size_t size\);::size_t ft_strlcpy(char *dst, const char *src, size_t size);'
		'size_t\t+ft_strlen\(const char \*s\);::size_t ft_strlen(const char *s);'
		'char\t+\*ft_strmapi\(char const \*s, char \(\*f\)\(unsigned int, char\)\);::char *ft_strmapi(char const *s, char (*f)(unsigned int, char));'
		'int\t+ft_strncmp\(const char \*s1, const char \*s2, size_t n\);::int ft_strncmp(const char *s1, const char *s2, size_t n);'
		'char\t+\*ft_strnstr\(const char \*big, const char \*little, size_t len\);::char *ft_strnstr(const char *big, const char *little, size_t len);'
		'char\t+\*ft_strrchr\(const char \*s, int c\);::char *ft_strrchr(const char *s, int c);'
		'char\t+\*ft_strtrim\(char const \*s1, char const \*set\);::char *ft_strtrim(char const *s1, char const *set);'
		'char\t+\*ft_substr\(char const \*s, unsigned int start, size_t len\);::char *ft_substr(char const *s, unsigned int start, size_t len);'
		'int\t+ft_tolower\(int c\);::int ft_tolower(int c);'
		'int\t+ft_toupper\(int c\);::int ft_toupper(int c);'
	)
	for proto in "${mandatory_prototypes[@]}"; do
		regex="${proto%%::*}"
		display="${proto##*::}"
		if ! grep -Pq "$regex" "$LIBFT_H"; then
			((errors++))
			if [ $errors -eq 1 ]; then
				error_messages+="Missing or malformed prototype(s), expected:"$'\n'
			fi
			error_messages+="$display"$'\n'
		fi
	done
	PROTO_TEST_RES=$errors
	BONUS_PROTO_TEST_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		errors=0
		bonus_prototypes=(
		'void\t+ft_lstadd_back\(t_list \*\*lst, t_list \*new\);::void ft_lstadd_back(t_list **lst, t_list *new);'
		'void\t+ft_lstadd_front\(t_list \*\*lst, t_list \*new\);::void ft_lstadd_front(t_list **lst, t_list *new);'
		'void\t+ft_lstclear\(t_list \*\*lst, void \(\*del\)\(void \*\)\);::void ft_lstclear(t_list **lst, void (*del)(void *));'
		'void\t+ft_lstdelone\(t_list \*lst, void \(\*del\)\(void \*\)\);::void ft_lstdelone(t_list *lst, void (*del)(void *));'
		'void\t+ft_lstiter\(t_list \*lst, void \(\*f\)\(void \*\)\);::void ft_lstiter(t_list *lst, void (*f)(void *));'
		't_list\t+\*ft_lstlast\(t_list \*lst\);::t_list *ft_lstlast(t_list *lst);'
		't_list\t+\*ft_lstmap\(t_list \*lst, void \*\(\*f\)\(void \*\), void \(\*del\)\(void \*\)\);::t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));'
		't_list\t+\*ft_lstnew\(void \*content\);::t_list *ft_lstnew(void *content);'
		'int\t+ft_lstsize\(t_list \*lst\);::int ft_lstsize(t_list *lst);'
	)
		for proto in "${bonus_prototypes[@]}"; do
			regex="${proto%%::*}"
			display="${proto##*::}"
			if ! grep -Pq "$regex" "$LIBFT_H"; then
				((errors++))
				if [ $PROTO_TEST_RES -eq 0 ] && [ $errors -eq 1 ]; then
					error_messages+="Missing or malformed prototype(s), expected:"$'\n'
				fi
				error_messages+="$display"$'\n'
			fi
		done
		BONUS_PROTO_TEST_RES=$errors
	fi
	if [ $PROTO_TEST_RES -eq 0 ] && [ $BONUS_PROTO_TEST_RES -eq 0 ]; then
		echo "   Done"
	else
		echo_color " Failed" "$RED"
	fi
	if [ -n "$error_messages" ]; then
		echo ""
		echo -e "$error_messages"
	fi

	echo -e -n "🔖 Checking Makefile..."
	MAKEFILE_PATH="$LIBFT_DIR/Makefile"
	MAKE_ERRORS=0
	MAKE_ISSUES=""
	if [ ! -f "$MAKEFILE_PATH" ]; then
		echo_color "No Makefile found!" "$RED"
		exit 1
	fi
	if ! grep -Eq '(^|\s)cc(\s|$)' "$MAKEFILE_PATH"; then
		((MAKE_ERRORS++))
		MAKE_ISSUES+="Missing or incorrect compiler (should use 'cc')"$'\n'
	fi
	for flag in -Wall -Wextra -Werror; do
		if ! grep -Fq -- "$flag" "$MAKEFILE_PATH"; then
			((MAKE_ERRORS++))
			MAKE_ISSUES+="Missing compilation flag: $flag"$'\n'
		fi
	done
	for rule in all clean fclean re; do
		if ! grep -Eq "^$rule\s*:" "$MAKEFILE_PATH"; then
			((MAKE_ERRORS++))
			MAKE_ISSUES+="Missing rule: $rule"$'\n'
		fi
	done
	if ! grep -Eq '^\$\(NAME\)\s*:' "$MAKEFILE_PATH"; then
		((MAKE_ERRORS++))
		MAKE_ISSUES+="Missing rule: \$(NAME)"$'\n'
	fi
	{
		make -C "$LIBFT_DIR" > /dev/null 2>&1
		make_output=$(make -C "$LIBFT_DIR" 2>&1)
	} || true
	if echo "$make_output" | grep -qE 'gcc|cc|ar|clang'; then
		((MAKE_ERRORS++))
		MAKE_ISSUES+="Unnecessary relink detected when running make twice"$'\n'
	fi
	if [ $MAKE_ERRORS -eq 0 ]; then
		echo -e "\t    Done"
	else
		echo_color "\t  Failed" "$RED"
		echo ""
		echo -e "$MAKE_ISSUES"
	fi

	echo -ne "📦 Building libft..."
	MAKE_CMD="make -C $LIBFT_DIR"
	[ $BONUS_VERSION -eq 1 ] && MAKE_CMD="$MAKE_CMD bonus"
	if $MAKE_CMD > /dev/null 2>&1; then
		echo -e "\t    Done"
	else
		echo_color "\t  Failed" "$RED"
		exit 1
	fi

	echo -e -n "🔍 Checking externals..."
	EXTERN_TEST_RES=0
	EXTERN_OUTPUT=""
	no_extern="ft_striteri ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi"
	malloc_funcs="ft_strmapi ft_itoa ft_calloc ft_strdup ft_substr ft_strjoin ft_strtrim"
	write_funcs="ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd"
	result=$(check_externals_batch "$no_extern" "")
	[ $? -ne 0 ] && EXTERN_TEST_RES=1 && EXTERN_OUTPUT="$EXTERN_OUTPUT$result"
	result=$(check_externals_batch "$malloc_funcs" "malloc")
	[ $? -ne 0 ] && EXTERN_TEST_RES=1 && EXTERN_OUTPUT="$EXTERN_OUTPUT$result"
	result=$(check_external_functions "ft_split" "malloc free" 2>&1)
	[ $? -ne 0 ] && EXTERN_TEST_RES=1 && EXTERN_OUTPUT="${EXTERN_OUTPUT}${result}\n"
	result=$(check_externals_batch "$write_funcs" "write")
	[ $? -ne 0 ] && EXTERN_TEST_RES=1 && EXTERN_OUTPUT="$EXTERN_OUTPUT$result"
	if [ $BONUS_VERSION -eq 1 ]; then
		bonus_no_extern="ft_lstiter ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back"
		result=$(check_externals_batch "$bonus_no_extern" "")
		[ $? -ne 0 ] && EXTERN_TEST_RES=1 && EXTERN_OUTPUT="$EXTERN_OUTPUT$result"
		for func_pair in "ft_lstnew:malloc" "ft_lstdelone:free" "ft_lstclear:free" "ft_lstmap:malloc free"; do
			IFS=':' read -r func allowed <<< "$func_pair"
			result=$(check_external_functions "$func" "$allowed" 2>&1)
			[ $? -ne 0 ] && EXTERN_TEST_RES=1 && EXTERN_OUTPUT="${EXTERN_OUTPUT}${result}\n"
		done
	fi
	if [ $EXTERN_TEST_RES -eq 0 ]; then
		echo "    Done"
	else
		echo_color "  Failed" "$RED"
		echo ""
		echo -e "$EXTERN_OUTPUT"
	fi

	echo -e -n "🔨 Building tests..."
	VERBOSE_FLAG=""
	[ $VERBOSE -eq 1 ] && VERBOSE_FLAG="-DVERBOSE=1"
	COMPILE_FLAGS="-Wall -Wextra -Werror -no-pie $VERBOSE_FLAG -Wl,--wrap=malloc"
	gcc $COMPILE_FLAGS basic_tests.c utils.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BASIC_TESTER_NAME >/dev/null 2>&1
	BASIC_TESTS_COMPILATION_RES=$?
	gcc $COMPILE_FLAGS leak_tests.c utils.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $LEAK_TESTER_NAME >/dev/null 2>&1
	LEAK_TESTS_COMPILATION_RES=$?
	BONUS_BASIC_TESTS_COMPILATION_RES=0
	BONUS_LEAK_TESTS_COMPILATION_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		gcc $COMPILE_FLAGS basic_tests_bonus.c utils.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BONUS_BASIC_TESTER_NAME >/dev/null 2>&1
		BONUS_BASIC_TESTS_COMPILATION_RES=$?
		
		gcc $COMPILE_FLAGS leak_tests_bonus.c utils.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BONUS_LEAK_TESTER_NAME >/dev/null 2>&1
		BONUS_LEAK_TESTS_COMPILATION_RES=$?
	fi
	if [ $BASIC_TESTS_COMPILATION_RES -eq 0 ] && [ $BONUS_BASIC_TESTS_COMPILATION_RES -eq 0 ] \
		&& [ $LEAK_TESTS_COMPILATION_RES -eq 0 ] && [ $BONUS_LEAK_TESTS_COMPILATION_RES -eq 0 ]; then
		echo -e "\t    Done"
	else
		echo_color "\t  Failed" "$RED"
		exit 1
	fi

	echo -e -n "🧪 Running tests..."
	./$BASIC_TESTER_NAME > "$TMP_DIR/basic_output.tmp" 2>&1
	BASIC_TESTS_RES=$?
	if grep -q "Segmentation fault" "$TMP_DIR/basic_output.tmp" 2>/dev/null; then
		cat "$TMP_DIR/basic_output.tmp" | sed 's/^.*Segmentation fault/\n&/' > .results
	else
		cat "$TMP_DIR/basic_output.tmp" > .results
	fi
	BONUS_BASIC_TESTS_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		./$BONUS_BASIC_TESTER_NAME > "$TMP_DIR/bonus_basic_output.tmp" 2>&1
		BONUS_BASIC_TESTS_RES=$?
		if grep -q "Segmentation fault" "$TMP_DIR/bonus_basic_output.tmp" 2>/dev/null; then
			cat "$TMP_DIR/bonus_basic_output.tmp" | sed 's/^.*Segmentation fault/\n&/' >> .results
		else
			cat "$TMP_DIR/bonus_basic_output.tmp" >> .results
		fi
	fi
	{ valgrind --leak-check=full --show-leak-kinds=all \
		--errors-for-leak-kinds=all --error-exitcode=1 --track-origins=yes \
		--log-file="$TMP_DIR/valgrind_output.log" ./$LEAK_TESTER_NAME > /dev/null; } > "$TMP_DIR/leak_output.tmp" 2>&1
	LEAK_TESTS_RES=$?
	if grep -q "Segmentation fault" "$TMP_DIR/leak_output.tmp" 2>/dev/null; then
		cat "$TMP_DIR/leak_output.tmp" | sed 's/^.*Segmentation fault/\n&/' >> .results
	else
		cat "$TMP_DIR/leak_output.tmp" >> .results
	fi
	BONUS_LEAK_TESTS_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		{ valgrind --leak-check=full --show-leak-kinds=all \
			--errors-for-leak-kinds=all --error-exitcode=1 --track-origins=yes \
			--log-file="$TMP_DIR/bonus_valgrind_output.log" ./$BONUS_LEAK_TESTER_NAME > /dev/null; } > "$TMP_DIR/bonus_leak_output.tmp" 2>&1
		BONUS_LEAK_TESTS_RES=$?
		if grep -q "Segmentation fault" "$TMP_DIR/bonus_leak_output.tmp" 2>/dev/null; then
			cat "$TMP_DIR/bonus_leak_output.tmp" | sed 's/^.*Segmentation fault/\n&/' >> .results
		else
			cat "$TMP_DIR/bonus_leak_output.tmp" >> .results
		fi
	fi
	if [ $LEAK_TESTS_RES -ne 0 ] || [ $VERBOSE -eq 1 ]; then
		{
			echo ""
			echo "════════════════════════════════════════"
			echo "VALGRIND OUTPUT (mandatory)"
			echo "════════════════════════════════════════"
			cat "$TMP_DIR/valgrind_output.log"
		} >> .results
	fi
	if [ $BONUS_LEAK_TESTS_RES -ne 0 ] || [ $VERBOSE -eq 1 ]; then
		{
			echo ""
			echo "════════════════════════════════════════"
			echo "VALGRIND OUTPUT (bonus)"
			echo "════════════════════════════════════════"
			cat "$TMP_DIR/bonus_valgrind_output.log"
		} >> .results
	fi
	if [ $BASIC_TESTS_RES -eq 0 ] && [ $BONUS_BASIC_TESTS_RES -eq 0 ] \
		&& [ $LEAK_TESTS_RES -eq 0 ] && [ $BONUS_LEAK_TESTS_RES -eq 0 ]; then
		echo -e "\t    Done"
	else
		echo_color "\t  Failed" "$RED"
	fi
	cat .results
	echo ""

	[ $NORM_TEST_RES -eq 0 ] && [ $PROTO_TEST_RES -eq 0 ] \
	&& [ $BONUS_PROTO_TEST_RES -eq 0 ] && [ $EXTERN_TEST_RES -eq 0 ] \
	&& [ $BASIC_TESTS_RES -eq 0 ] && [ $BONUS_BASIC_TESTS_RES -eq 0 ] \
	&& [ $LEAK_TESTS_RES -eq 0 ] && [ $BONUS_LEAK_TESTS_RES -eq 0 ]
	EXIT_CODE=$?
	if [ $EXIT_CODE -eq 0 ]; then
		echo_color "╔══════════════════════════════╗" "$GREEN"
		echo_color "║      OH MY, YOU PASSED!      ║" "$GREEN"
		echo_color "╚══════════════════════════════╝" "$GREEN"
	else
		echo_color "╔══════════════════════════════╗" "$RED"
		echo_color "║     OH NO... YOU FAILED!     ║" "$RED"
		echo_color "╚══════════════════════════════╝" "$RED"
	fi
	echo ""
	return $EXIT_CODE
}

main
exit $?