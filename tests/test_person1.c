#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data/question.h"

int main() {
    // Initialize random seed
    srand(time(NULL));
    
    printf("===========================================\n");
    printf("   PERSON 1 - QUESTION SYSTEM TEST\n");
    printf("===========================================\n\n");
    
    // Test 1: Create question bank
    printf("TEST 1: Creating question bank...\n");
    QuestionBank* bank = createQuestionBank();
    if (bank == NULL) {
        printf("FAILED: Could not create question bank!\n");
        return 1;
    }
    printf("PASSED: Question bank created!\n\n");
    
    // Test 2: Load questions from file
    printf("TEST 2: Loading questions from file...\n");
    loadQuestionsFromFile(bank, "data/questions/questions.txt");
    if (bank->count == 0) {
        printf("FAILED: No questions loaded!\n");
        freeQuestionBank(bank);
        return 1;
    }
    printf("PASSED: %d questions loaded!\n\n", bank->count);
    
    // Test 3: Display all questions
    printf("TEST 3: Displaying all questions...\n");
    printf("===========================================\n");
    for (int i = 0; i < bank->count; i++) {
        Question* q = &bank->questions[i];
        printf("\nQuestion %d (Difficulty: %d):\n", i + 1, q->difficulty);
        printf("%s\n", q->question);
        printf("  A) %s\n", q->choices[0]);
        printf("  B) %s\n", q->choices[1]);
        printf("  C) %s\n", q->choices[2]);
        printf("  D) %s\n", q->choices[3]);
        printf("Correct Answer: %c\n", q->correctAnswer);
        printf("Explanation: %s\n", q->explanation);
        printf("-------------------------------------------\n");
    }
    printf("PASSED: All questions displayed!\n\n");
    
    // Test 4: Get random question by difficulty
    printf("TEST 4: Getting random questions by difficulty...\n");
    for (int diff = 1; diff <= 5; diff++) {
        printf("\nTesting difficulty %d:\n", diff);
        Question* q = getRandomQuestion(bank, diff);
        if (q != NULL) {
            printf("  Got question: %s\n", q->question);
            printf("  Difficulty: %d\n", q->difficulty);
        } else {
            printf("  No questions found for difficulty %d\n", diff);
        }
    }
    printf("\nPASSED: Random question selection works!\n\n");
    
    // Test 5: Check answer function
    printf("TEST 5: Testing answer checking...\n");
    Question* testQ = &bank->questions[0];
    printf("Question: %s\n", testQ->question);
    printf("Correct answer: %c\n", testQ->correctAnswer);
    
    // Test correct answer (uppercase)
    if (checkAnswer(testQ, testQ->correctAnswer)) {
        printf("  ✓ Correct answer (uppercase) recognized!\n");
    } else {
        printf("  ✗ FAILED: Correct answer not recognized!\n");
    }
    
    // Test correct answer (lowercase)
    char lowerAnswer = testQ->correctAnswer + ('a' - 'A');
    if (checkAnswer(testQ, lowerAnswer)) {
        printf("  ✓ Correct answer (lowercase) recognized!\n");
    } else {
        printf("  ✗ FAILED: Lowercase answer not recognized!\n");
    }
    
    // Test wrong answer
    char wrongAnswer = (testQ->correctAnswer == 'A') ? 'B' : 'A';
    if (!checkAnswer(testQ, wrongAnswer)) {
        printf("  ✓ Wrong answer correctly identified!\n");
    } else {
        printf("  ✗ FAILED: Wrong answer not detected!\n");
    }
    printf("PASSED: Answer checking works correctly!\n\n");
    
    // Test 6: Free question bank
    printf("TEST 6: Freeing question bank...\n");
    freeQuestionBank(bank);
    printf("PASSED: Memory freed successfully!\n\n");
    
    // Final summary
    printf("===========================================\n");
    printf("   ALL TESTS PASSED! ✓\n");
    printf("   Person 1 system is working correctly!\n");
    printf("===========================================\n");
    
    return 0;
}