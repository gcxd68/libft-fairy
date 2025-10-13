#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
PURPLE='\033[0;35m'
RESET='\033[0m'

LIBFT_DIR=".."
TESTER_NAME="libft-assassin"

print_message() {
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
    print_message "╔════════════════════════╗" "$PURPLE"
    print_message "║     LIBFT-ASSASSIN     ║" "$PURPLE"
    print_message "╚════════════════════════╝" "$PURPLE"
    echo ""

    echo -n "📦 Compiling libft... "
    if make -C $LIBFT_DIR bonus > /dev/null 2>&1; then
        echo "Done"
    else
        echo "Failed"
        exit 1
    fi

    echo -n "🔨 Compiling libft-assassin... "
    if gcc -Wall -Wextra -Werror tests.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $TESTER_NAME 2>&1; then
        echo "Done"
    else
        echo "Failed!"
        exit 1
    fi

    echo "🧪 Running tests..."
    echo ""
    ./$TESTER_NAME
    TEST_RESULT=$?
    if [ $TEST_RESULT -ne 0 ]; then
        echo ""
    fi

    # Step 4: Report final result
    if [ $TEST_RESULT -eq 0 ]; then
        print_message "╔════════════════════════╗" "$GREEN"
        print_message "║         PASSED         ║" "$GREEN"
        print_message "╚════════════════════════╝" "$GREEN"
    else
        print_message "╔════════════════════════╗" "$RED"
        print_message "║      ASSASSINATED      ║" "$RED"
        print_message "╚════════════════════════╝" "$RED"
    fi
    echo ""

    return $TEST_RESULT
}

# Run main function
main
exit $?
