#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
PINK='\033[0;95m'
RESET='\033[0m'

LIBFT_DIR=".."
BASIC_TESTER_NAME=".basic_tests"
LEAK_TESTER_NAME=".leak_tests"
BONUS_BASIC_TESTER_NAME=".basic_tests_bonus"
BONUS_LEAK_TESTER_NAME=".leak_tests_bonus"
TESTER_DIR=$(basename "$(pwd)")

echo_color() {
	echo -e "${2}${1}${RESET}"
}

cleanup() {
	echo -n "🧹 Cleaning up... "
	rm -f *.o $BASIC_TESTER_NAME $LEAK_TESTER_NAME $BONUS_BASIC_TESTER_NAME $BONUS_LEAK_TESTER_NAME
	make -C $LIBFT_DIR fclean > /dev/null 2>&1
	echo "Done"
	echo ""
}

trap cleanup EXIT INT TERM

main() {
	echo ""
	echo_color "╔════════════════════════════╗" "$PINK"
	echo_color "║       LIBFT-FAIRY 🧚       ║" "$PINK"
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
		BONUS_VERSION=1
		echo "Done (bonus)"
	elif make -C $LIBFT_DIR > /dev/null 2>&1; then
		BONUS_VERSION=0
		echo "Done (no bonus)"
	else
		echo_color "Failed" "$RED"
		exit 1
	fi

	echo -n "🔨 Compiling tests... "
	gcc -Wall -Wextra -Werror -no-pie basic_tests.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BASIC_TESTER_NAME >/dev/null 2>&1
	BASIC_TESTS_COMPILATION_RES=$?
	gcc -Wall -Wextra -Werror -no-pie leak_tests.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $LEAK_TESTER_NAME >/dev/null 2>&1
	LEAK_TESTS_COMPILATION_RES=$?
	BONUS_BASIC_TESTS_COMPILATION_RES=0
	BONUS_LEAK_TESTS_COMPILATION_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		gcc -Wall -Wextra -Werror -no-pie basic_tests_bonus.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BONUS_BASIC_TESTER_NAME >/dev/null 2>&1
		BONUS_BASIC_TESTS_COMPILATION_RES=$?
		gcc -Wall -Wextra -Werror -no-pie leak_tests_bonus.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BONUS_LEAK_TESTER_NAME >/dev/null 2>&1
		BONUS_LEAK_TESTS_COMPILATION_RES=$?
	fi
	if [ $BASIC_TESTS_COMPILATION_RES -eq 0 ] && [ $BONUS_BASIC_TESTS_COMPILATION_RES -eq 0 ] \
		&& [ $LEAK_TESTS_COMPILATION_RES -eq 0 ] && [ $BONUS_LEAK_TESTS_COMPILATION_RES -eq 0 ]; then
		echo "Done"
	else
		echo_color "Failed" "$RED"
		exit 1
	fi

	echo "🧪 Running tests... "
	./$BASIC_TESTER_NAME
	BASIC_TESTS_RES=$?
	BONUS_BASIC_TESTS_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		./$BONUS_BASIC_TESTER_NAME
		BONUS_BASIC_TESTS_RES=$?
	fi
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=1 --track-origins=yes \
		--log-file=/tmp/valgrind_output.log ./$LEAK_TESTER_NAME 2>&1 | tee /tmp/valgrind_output.log
	LEAK_TESTS_RES=$?
	BONUS_LEAK_TESTS_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=1 --track-origins=yes \
			--log-file=/tmp/bonus_valgrind_output.log ./$BONUS_LEAK_TESTER_NAME 2>&1 | tee /tmp/bonus_valgrind_output.log
		BONUS_LEAK_TESTS_RES=$?
	fi
	if [ $LEAK_TESTS_RES -ne 0 ]; then
		echo ""
		cat /tmp/valgrind_output.log
	fi
	if [ $BONUS_LEAK_TESTS_RES -ne 0 ]; then
		echo ""
		cat /tmp/bonus_valgrind_output.log
	fi
	echo ""

	[ $BASIC_TESTS_RES -eq 0 ] && [ $BONUS_BASIC_TESTS_RES -eq 0 ] && [ $LEAK_TESTS_RES -eq 0 ] && [ $BONUS_LEAK_TESTS_RES -eq 0 ]
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
