#!/bin/bash

# Color codes for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo "==========================================="
echo "   CODERUSH SYSTEM VERIFICATION"
echo "==========================================="

# Function to run a test
run_test() {
    test_name=$1
    command=$2
    
    echo -e "\nRunning Test: ${test_name}..."
    echo "-------------------------------------------"
    eval $command
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}PASSED: ${test_name}${NC}"
        return 0
    else
        echo -e "${RED}FAILED: ${test_name}${NC}"
        return 1
    fi
}

# Create output directory for test binaries if it doesn't exist
mkdir -p test_bin

# 1. Test Person 1: Question System
run_test "Question System" "gcc -I. tests/test_person1.c data/question.c -o test_bin/test_p1 && ./test_bin/test_p1"

# 2. Test Person 2: Game Logic (Smoke Test)
run_test "Game Logic (Smoke Test)" "gcc -I. tests/test_Noolee_p2.c game/game.c data/question.c -o test_bin/test_p2 && ./test_bin/test_p2"

# 3. Test Game Progress & Modes
run_test "Game Progress & Modes" "gcc -I. tests/Final_test/noolee_test_progress.c game/game.c data/question.c -o test_bin/test_progress && ./test_bin/test_progress"

# 4. Test Person 5: Save/Load System
run_test "Save/Load System" "gcc -I. tests/test_person5.c save/save.c -o test_bin/test_p5 && ./test_bin/test_p5"

# 5. Test Main Game Build
echo -e "\nBuilding Main Game..."
echo "-------------------------------------------"
make clean && make
if [ $? -eq 0 ]; then
    echo -e "${GREEN}PASSED: Main Game Build${NC}"
else
    echo -e "${RED}FAILED: Main Game Build${NC}"
fi

echo -e "\n==========================================="
echo "   VERIFICATION COMPLETE"
echo "==========================================="
