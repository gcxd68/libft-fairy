#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

# Paths
LIBFT_DIR=".."
TESTER_NAME="libft-assassin"

# Function to print colored messages
print_message() {
    echo -e "${2}${1}${RESET}"
}

# Function to cleanup
cleanup() {
    print_message "🧹 Cleaning up..." "$YELLOW"
    rm -f *.o $TESTER_NAME
    make -C $LIBFT_DIR fclean > /dev/null 2>&1
    print_message "✓ Cleanup complete!" "$GREEN"
}

# Trap to ensure cleanup on exit
trap cleanup EXIT INT TERM

# Main execution
main() {
    print_message "╔═════════════════════════╗" "$BLUE"
    print_message "║     LIBFT-ASSASSIN      ║" "$BLUE"
    print_message "╚═════════════════════════╝" "$BLUE"
    echo ""

    # Step 1: Compile libft
    print_message "📦 Step 1: Compiling libft..." "$YELLOW"
    if make -C $LIBFT_DIR bonus > /dev/null 2>&1; then
        print_message "✓ Libft compiled successfully!" "$GREEN"
    else
        print_message "✗ Failed to compile libft!" "$RED"
        exit 1
    fi
    echo ""

    # Step 2: Compile tester
    print_message "🔨 Step 2: Compiling libft-assassin..." "$YELLOW"
    if gcc -Wall -Wextra -Werror tests.c -L$LIBFT_DIR -lft -I$LIBFT_DIR -o $TESTER_NAME 2>&1; then
        print_message "✓ libft-assassin compiled successfully!" "$GREEN"
    else
        print_message "✗ Failed to compile libft-assassin!" "$RED"
        exit 1
    fi
    echo ""

    # Step 3: Run tests
    print_message "🧪 Step 3: Running tests..." "$YELLOW"
    echo ""
    ./$TESTER_NAME
    TEST_RESULT=$?
    echo ""

    # Step 4: Report final result
    if [ $TEST_RESULT -eq 0 ]; then
        print_message "╔════════════════════════════════════════╗" "$GREEN"
        print_message "║    🎉 ALL TESTS PASSED! 🎉             ║" "$GREEN"
        print_message "╚════════════════════════════════════════╝" "$GREEN"
    else
        print_message "╔════════════════════════════════════════╗" "$RED"
        print_message "║    ⚠️  SOME TESTS FAILED ⚠️              ║" "$RED"
        print_message "╚════════════════════════════════════════╝" "$RED"
    fi
    echo ""

    return $TEST_RESULT
}

# Run main function
main
exit $?
