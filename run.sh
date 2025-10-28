#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
PINK='\033[0;95m'
YELLOW='\033[1;33m'
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

echo_color() {
	echo -e "${2}${1}${RESET}"
}

cleanup() {
	echo -e -n "🧹 Cleaning up...\t"
	rm -f *.o $BASIC_TESTER_NAME $LEAK_TESTER_NAME $BONUS_BASIC_TESTER_NAME $BONUS_LEAK_TESTER_NAME .results
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
	
	echo -e -n "📝 Checking norm...\t"
	NORM_OUTPUT=$(find $LIBFT_DIR -type d -name "$TESTER_DIR" -prune -o \
		\( -name "*.c" -o -name "*.h" \) -type f -print | xargs -r norminette 2>&1)
	if echo "$NORM_OUTPUT" | grep -q "Error"; then
		NORM_TEST_RES=1
		echo_color "Failed" "$RED"
		echo ""
		echo "$NORM_OUTPUT" | grep "Error"
		echo ""
	else
		NORM_TEST_RES=0
		echo "Done"
	fi

	echo -e -n "📦 Compiling libft...\t"
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

	echo -e -n "🔨 Compiling tests...\t"
	VERBOSE_FLAG=""
	if [ $VERBOSE -eq 1 ]; then
		VERBOSE_FLAG="-DVERBOSE=1"
	fi
	gcc -Wall -Wextra -Werror -no-pie $VERBOSE_FLAG -Wl,--wrap=malloc basic_tests.c utils.c \
		-L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BASIC_TESTER_NAME #>/dev/null 2>&1
	BASIC_TESTS_COMPILATION_RES=$?
	gcc -Wall -Wextra -Werror -no-pie -Wl,--wrap=malloc leak_tests.c utils.c \
		-L$LIBFT_DIR -lft -I$LIBFT_DIR -o $LEAK_TESTER_NAME >/dev/null 2>&1
	LEAK_TESTS_COMPILATION_RES=$?
	BONUS_BASIC_TESTS_COMPILATION_RES=0
	BONUS_LEAK_TESTS_COMPILATION_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		gcc -Wall -Wextra -Werror -no-pie $VERBOSE_FLAG -Wl,--wrap=malloc basic_tests_bonus.c utils.c \
			-L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BONUS_BASIC_TESTER_NAME >/dev/null 2>&1
		BONUS_BASIC_TESTS_COMPILATION_RES=$?
		gcc -Wall -Wextra -Werror -no-pie -Wl,--wrap=malloc leak_tests_bonus.c utils.c \
			-L$LIBFT_DIR -lft -I$LIBFT_DIR -o $BONUS_LEAK_TESTER_NAME >/dev/null 2>&1
		BONUS_LEAK_TESTS_COMPILATION_RES=$?
	fi
	if [ $BASIC_TESTS_COMPILATION_RES -eq 0 ] && [ $BONUS_BASIC_TESTS_COMPILATION_RES -eq 0 ] \
		&& [ $LEAK_TESTS_COMPILATION_RES -eq 0 ] && [ $BONUS_LEAK_TESTS_COMPILATION_RES -eq 0 ]; then
		echo "Done"
	else
		echo_color "Failed" "$RED"
		exit 1
	fi

	echo -e -n "🧪 Running tests...\t"
	./$BASIC_TESTER_NAME > .results 2>&1
	BASIC_TESTS_RES=$?
	BONUS_BASIC_TESTS_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		./$BONUS_BASIC_TESTER_NAME >> .results 2>&1
		BONUS_BASIC_TESTS_RES=$?
	fi
	valgrind --leak-check=full --show-leak-kinds=all \
		--errors-for-leak-kinds=all --error-exitcode=1 --track-origins=yes \
		--log-file=/tmp/valgrind_output.log ./$LEAK_TESTER_NAME > /dev/null 2>&1
	LEAK_TESTS_RES=$?
	BONUS_LEAK_TESTS_RES=0
	if [ $BONUS_VERSION -eq 1 ]; then
		valgrind --leak-check=full --show-leak-kinds=all \
			--errors-for-leak-kinds=all --error-exitcode=1 --track-origins=yes \
			--log-file=/tmp/bonus_valgrind_output.log ./$BONUS_LEAK_TESTER_NAME > /dev/null 2>&1
		BONUS_LEAK_TESTS_RES=$?
	fi
	if [ $LEAK_TESTS_RES -ne 0 ] || [ $VERBOSE -eq 1 ]; then
		echo "" >> .results
		echo "════════════════════════════════════════" >> .results
		echo "VALGRIND OUTPUT (mandatory)" >> .results
		echo "════════════════════════════════════════" >> .results
		cat /tmp/valgrind_output.log >> .results
	fi
	if [ $BONUS_LEAK_TESTS_RES -ne 0 ] || [ $VERBOSE -eq 1 ]; then
		echo "" >> .results
		echo "════════════════════════════════════════" >> .results
		echo "VALGRIND OUTPUT (bonus)" >> .results
		echo "════════════════════════════════════════" >> .results
		cat /tmp/bonus_valgrind_output.log >> .results
	fi
	if [ $BASIC_TESTS_RES -eq 0 ] && [ $BONUS_BASIC_TESTS_RES -eq 0 ] && \
	   [ $LEAK_TESTS_RES -eq 0 ] && [ $BONUS_LEAK_TESTS_RES -eq 0 ]; then
		echo "Done"
	else
		echo_color "Failed" "$RED"
	fi

	cat .results
	echo ""

	[ $NORM_TEST_RES -eq 0 ] && [ $BASIC_TESTS_RES -eq 0 ] && \
	[ $BONUS_BASIC_TESTS_RES -eq 0 ] && [ $LEAK_TESTS_RES -eq 0 ] && \
	[ $BONUS_LEAK_TESTS_RES -eq 0 ]
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
