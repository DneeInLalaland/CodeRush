#include "../input/input.h"
#include <stdio.h>

// ─────────────────────────────────────────────
// Test 1: Validate Choice
// ─────────────────────────────────────────────
void test_validate_choice() {
    printf("\n=== Test 1: Validate Choice ===\n");

    char validChoices[] = {'A', 'B', 'C', 'D', 'a', 'b', 'c', 'd'};
    char invalidChoices[] = {'E', 'F', '1', '2', '@', '#'};
    int passCount = 0;

    // ทดสอบตัวเลือกที่ถูกต้อง
    for (int i = 0; i < 8; i++) {
        if (validateChoice(validChoices[i])) {
            passCount++;
        }
    }

    if (passCount == 8) {
        printf("PASS: All valid choices accepted\n"); // เปลี่ยน ✅ เป็น PASS
    } else {
        printf("FAIL: Some valid choices rejected (%d/8)\n", passCount); // เปลี่ยน ❌ เป็น FAIL
    }

    // ทดสอบตัวเลือกที่ไม่ถูกต้อง
    int rejectCount = 0;
    for (int i = 0; i < 6; i++) {
        if (!validateChoice(invalidChoices[i])) {
            rejectCount++;
        }
    }

    if (rejectCount == 6) {
        printf("PASS: All invalid choices rejected\n"); // เปลี่ยน ✅ เป็น PASS
    } else {
        printf("FAIL: Some invalid choices accepted (%d/6)\n", 6 - rejectCount); // เปลี่ยน ❌ เป็น FAIL
    }
}

// ─────────────────────────────────────────────
// Test 2: Get Number Input (Manual)
// ─────────────────────────────────────────────
void test_get_number_input() {
    printf("\n=== Test 2: Get Number Input (Manual) ===\n");
    printf("Please enter a number between 1 and 5:\n");

    int choice = getNumberInput(1, 5);
    if (choice >= 1 && choice <= 5) {
        printf("PASS: Valid number accepted: %d\n", choice); // เปลี่ยน ✅ เป็น PASS
    } else {
        printf("FAIL: Invalid number: %d\n", choice); // เปลี่ยน ❌ เป็น FAIL
    }
}

// ─────────────────────────────────────────────
// Test 3: Menu Display (Manual)
// ─────────────────────────────────────────────
void test_menu_display() {
    printf("\n=== Test 3: Menu Display (Manual) ===\n");
    printf("Testing menu system...\n\n");

    int choice = showMainMenu();
    if (choice >= 1 && choice <= 5) {
        printf("PASS: Menu displayed and choice made: %d\n", choice); // เปลี่ยน ✅ เป็น PASS
    } else {
        printf("FAIL: Invalid menu choice: %d\n", choice); // เปลี่ยน ❌ เป็น FAIL
    }
}

// ─────────────────────────────────────────────
// Test 4: Difficulty Selection (Manual)
// ─────────────────────────────────────────────
void test_difficulty_selection() {
    printf("\n=== Test 4: Difficulty Selection (Manual) ===\n");
    printf("Testing difficulty selection...\n\n");

    int diff = selectDifficulty();
    if (diff >= 1 && diff <= 5) {
        printf("PASS: Difficulty selected: %d\n", diff); // เปลี่ยน ✅ เป็น PASS
    } else {
        printf("FAIL: Invalid difficulty: %d\n", diff); // เปลี่ยน ❌ เป็น FAIL
    }
}

// ─────────────────────────────────────────────
// Test 5: Confirmation (Manual)
// ─────────────────────────────────────────────
void test_confirmation() {
    printf("\n=== Test 5: Confirmation (Manual) ===\n");

    int result = confirmAction("Do you want to continue testing?");
    if (result == 0 || result == 1) {
        printf("PASS: Confirmation returned: %s\n", result ? "Yes" : "No"); // เปลี่ยน ✅ เป็น PASS
    } else {
        printf("FAIL: Invalid confirmation result: %d\n", result); // เปลี่ยน ❌ เป็น FAIL
    }
}

// ─────────────────────────────────────────────
// Main Test Runner
// ─────────────────────────────────────────────
int main() {
    printf("===========================================\n"); // เปลี่ยนกรอบ ╔═ เป็น =
    printf("        PERSON 3: Input System Tests       \n"); // ปรับระยะห่าง
    printf("===========================================\n"); // เปลี่ยนกรอบ ╚═ เป็น =
    printf("\nNote: Some tests require manual input.\n");

    test_validate_choice();

    printf("\n--- IMPORTANT: Manual Input Required ---\n"); // เปลี่ยน ⚠️ เป็น --- IMPORTANT: Manual Input Required ---
    printf("Press Enter to continue or Ctrl+C to skip...\n");
    getchar();

    test_get_number_input();
    test_menu_display();
    test_difficulty_selection();
    test_confirmation();

    printf("\n===========================================\n"); // เปลี่ยนกรอบ ╔═ เป็น =
    printf("          All Tests Completed!             \n"); // ปรับระยะห่างและเปลี่ยน ❗ เป็น !
    printf("===========================================\n\n"); // เปลี่ยนกรอบ ╚═ เป็น =

    return 0;
}
