#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
PURPLE='\033[0;35m'
RESET='\033[0m'

LIBFT_DIR=".."
TESTER_NAME="libft-unicorn"
TESTER_DIR=$(basename "$(pwd)")

echo_color() {
	echo -e "${2}${1}${RESET}"
}

cleanup() {
	echo -n "🧹 Cleaning up... "
	rm -f *.o $TESTER_NAME
	make -C $LIBFT_DIR fclean > /dev/null 2>&1
	echo "Done"
	echo ""
}

trap cleanup EXIT INT TERM

main() {
	echo ""
	echo_color "╔══════════════════════════╗" "$PURPLE"
	echo_color "║     LIBFT-UNICORN 🦄     ║" "$PURPLE"
	echo_color "╚══════════════════════════╝" "$PURPLE"
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

	echo -n "🔨 Compiling libft-unicorn... "
	if gcc -Wall -Wextra -Werror -no-pie tests.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $TESTER_NAME 2>&1; then
		echo "Done"
	else
		echo_color "Failed" "$RED"
		exit 1
	fi

	echo "🧪 Running tests..."
	echo ""
	./$TESTER_NAME
	TEST_RESULT=$?
	if [ $TEST_RESULT -ne 0 ]; then
		echo ""
	fi

	if [ $TEST_RESULT -eq 0 ]; then
		echo_color "╔══════════════════════════╗" "$GREEN"
		echo_color "║        NICE WORK!        ║" "$GREEN"
		echo_color "╚══════════════════════════╝" "$GREEN"
	else
		echo_color "╔══════════════════════════╗" "$RED"
		echo_color "║   OH NO... YOU FAILED!   ║" "$RED"
		echo_color "╚══════════════════════════╝" "$RED"
	fi
	echo ""

	return $TEST_RESULT
}

main
exit $?
