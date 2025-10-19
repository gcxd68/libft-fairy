#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
PINK='\033[0;95m'
RESET='\033[0m'

LIBFT_DIR=".."
BASIC_TESTER_NAME="basic_tests"
LEAK_TESTER_NAME="leak_tests"
TESTER_DIR=$(basename "$(pwd)")

echo_color() {
	echo -e "${2}${1}${RESET}"
}

cleanup() {
	echo -n "🧹 Cleaning up... "
	rm -f *.o $BASIC_TESTER_NAME $LEAK_TESTER_NAME
	make -C $LIBFT_DIR fclean > /dev/null 2>&1
	echo "Done"
	echo ""
}

trap cleanup EXIT INT TERM

main() {
	echo ""
	echo_color "╔════════════════════════════╗" "$PINK"
	echo_color "║      LIBFT-UNICORN 🦄      ║" "$PINK"
	echo_color "╚════════════════════════════╝" "$PINK"
	echo ""

	echo -n "📝 Checking Norminette... "
	NORM_OUTPUT=$(find $LIBFT_DIR -type d -name "$TESTER_DIR" -prune -o \( -name "*.c" -o -name "*.h" \) -type f -print | xargs norminette 2>&1)
	if echo "$NORM_OUTPUT" | grep -q "Error"; then
		echo_color "Failed" "$RED"
		echo ""
		echo "$NORM_OUTPUT" | grep "Error"
		echo ""
		exit 1
	else
		echo "Done"
	fi

	echo -n "📦 Compiling libft... "
	if make -C $LIBFT_DIR bonus > /dev/null 2>&1; then
		echo "Done"
	elif make -C $LIBFT_DIR > /dev/null 2>&1; then
		echo "Done"
	else
		echo_color "Failed" "$RED"
		exit 1
	fi

	echo -n "🔨 Compiling tests... "
	gcc -Wall -Wextra -Werror -no-pie basic_tests.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BASIC_TESTER_NAME >/dev/null 2>&1
	BASIC_TESTS_COMPILATION_RES=$?
	gcc -Wall -Wextra -Werror leak_tests.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $LEAK_TESTER_NAME >/dev/null 2>&1
	LEAK_TESTS_COMPILATION_RES=$?
	if [ $BASIC_TESTS_COMPILATION_RES -eq 0 ] && [ $LEAK_TESTS_COMPILATION_RES -eq 0 ]; then
		echo "Done"
	else
		echo_color "Failed" "$RED"
		exit 1
	fi

	echo "🧪 Running tests... "
	./$BASIC_TESTER_NAME
	BASIC_TESTS_RES=$?
	valgrind --leak-check=full --show-leak-kinds=all \
				--errors-for-leak-kinds=all --error-exitcode=1 \
				--track-origins=yes --log-file=/tmp/valgrind_output.log \
				./$LEAK_TESTER_NAME 2>&1 | tee /tmp/valgrind_output.log
	LEAK_TESTS_RES=$?
	if [ $LEAK_TESTS_RES -ne 0 ]; then
		echo ""
		echo_color "🔍 Valgrind output:" "$PINK"
		cat /tmp/valgrind_output.log
	fi
	echo ""

	[ $BASIC_TESTS_RES -eq 0 ] && [ $LEAK_TESTS_RES -eq 0 ]
	EXIT_CODE=$?
	if [ $EXIT_CODE -eq 0 ]; then
		echo_color "╔════════════════════════════╗" "$GREEN"
		echo_color "║     OH MY, YOU PASSED!     ║" "$GREEN"
		echo_color "╚════════════════════════════╝" "$GREEN"
	else
		echo_color "╔════════════════════════════╗" "$RED"
		echo_color "║    OH NO... YOU FAILED!    ║" "$RED"
		echo_color "╚════════════════════════════╝" "$RED"
	fi
	echo ""
	return $EXIT_CODE
}

main
exit $?
