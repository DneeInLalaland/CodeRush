/**
 * @file question.c
 * @brief Question System - Implementation
 * @author Rinrada Dejsuwannachai (68070503490)
 * @date December 2025
 * 
 * Implements question management functions:
 * - createQuestionBank(): Initialize empty question bank
 * - loadQuestionsFromFile(): Load questions from text file
 * - getRandomQuestion(): Select random question by difficulty
 * - checkAnswer(): Validate player answer
 * - freeQuestionBank(): Free allocated memory
 */

 #include "question.h"

// Function 1: Create an empty question bank
QuestionBank* createQuestionBank() {
    QuestionBank* bank = (QuestionBank*)malloc(sizeof(QuestionBank));
    
    if (bank == NULL) {
        printf("Error: Failed to allocate memory for question bank!\n");
        return NULL;
    }
    
    bank->capacity = 200;  // Increased capacity for more questions
    bank->count = 0;
    bank->questions = (Question*)malloc(sizeof(Question) * bank->capacity);
    
    if (bank->questions == NULL) {
        printf("Error: Failed to allocate memory for questions!\n");
        free(bank);
        return NULL;
    }
    
    printf("Question bank created successfully!\n");
    return bank;
}

// Function 2: Load questions from file
void loadQuestionsFromFile(QuestionBank* bank, const char* filename) {
    if (bank == NULL) {
        printf("Error: Question bank is NULL!\n");
        return;
    }
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'!\n", filename);
        return;
    }
    
    printf("Loading questions from '%s'...\n", filename);
    
    char line[512];
    while (fgets(line, sizeof(line), file) != NULL && bank->count < bank->capacity) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        
        // Skip empty lines
        if (strlen(line) == 0) continue;
        
        Question q;
        
        // Read question
        snprintf(q.question, sizeof(q.question), "%s", line);
        
        // Read 4 choices
        for (int i = 0; i < 4; i++) {
            if (fgets(line, sizeof(line), file) == NULL) break;
            line[strcspn(line, "\n")] = 0;
            snprintf(q.choices[i], sizeof(q.choices[i]), "%s", line);
        }
        
        // Read correct answer
        if (fgets(line, sizeof(line), file) != NULL) {
            q.correctAnswer = line[0];  // A, B, C, or D
            // แปลงเป็นตัวพิมพ์ใหญ่
            if (q.correctAnswer >= 'a' && q.correctAnswer <= 'd') {
                q.correctAnswer = q.correctAnswer - 'a' + 'A';
            }
        }
        
        // Read explanation
        if (fgets(line, sizeof(line), file) != NULL) {
            line[strcspn(line, "\n")] = 0;
            snprintf(q.explanation, sizeof(q.explanation), "%s", line);
        }
        
        // Read difficulty
        if (fgets(line, sizeof(line), file) != NULL) {
            q.difficulty = atoi(line);
        }
        
        // NEW! Initialize isUsed to 0 (not used yet)
        q.isUsed = 0;
        
        // Add question to bank
        bank->questions[bank->count] = q;
        bank->count++;
    }
    
    fclose(file);
    printf("Loaded %d questions successfully!\n", bank->count);
}

// Function 3: Get random question by difficulty (แก้ไขให้ไม่ซ้ำ!)
Question* getRandomQuestion(QuestionBank* bank, int difficulty) {
    if (bank == NULL || bank->count == 0) {
        printf("Error: Question bank is empty!\n");
        return NULL;
    }
    
    // Count questions matching the difficulty AND not used yet
    int matchCount = 0;
    int matchIndices[50];
    
    for (int i = 0; i < bank->count; i++) {
        // เช็คว่า difficulty ตรง AND ยังไม่ถูกใช้
        if (bank->questions[i].difficulty == difficulty && bank->questions[i].isUsed == 0) {
            matchIndices[matchCount] = i;
            matchCount++;
        }
    }
    
    // ถ้าไม่มีคำถามที่ตรง difficulty และยังไม่ใช้ → ลองหาจาก difficulty อื่น
    if (matchCount == 0) {
        printf("Warning: No unused questions for difficulty %d. Trying other difficulties...\n", difficulty);
        
        // หาคำถามที่ยังไม่ใช้จาก difficulty อื่น
        for (int i = 0; i < bank->count; i++) {
            if (bank->questions[i].isUsed == 0) {
                matchIndices[matchCount] = i;
                matchCount++;
            }
        }
    }
    
    // ถ้ายังไม่มีเลย (ใช้หมดแล้ว) → reset แล้วเริ่มใหม่
    if (matchCount == 0) {
        printf("All questions used! Resetting question pool...\n");
        resetUsedQuestions(bank);
        
        // หาใหม่อีกครั้ง (เอา difficulty ที่ต้องการ)
        for (int i = 0; i < bank->count; i++) {
            if (bank->questions[i].difficulty == difficulty) {
                matchIndices[matchCount] = i;
                matchCount++;
            }
        }
        
        // ถ้ายังไม่มี difficulty ที่ต้องการ เอาอะไรก็ได้
        if (matchCount == 0) {
            for (int i = 0; i < bank->count; i++) {
                matchIndices[matchCount] = i;
                matchCount++;
            }
        }
    }
    
    // Select random question from matching ones
    int randomMatch = rand() % matchCount;
    int selectedIndex = matchIndices[randomMatch];
    
    // Mark as used! 🎯
    bank->questions[selectedIndex].isUsed = 1;
    
    return &bank->questions[selectedIndex];
}

// Function 4: Check if answer is correct
int checkAnswer(Question* q, char answer) {
    if (q == NULL) {
        printf("Error: Question is NULL!\n");
        return 0;
    }
    
    // Convert to uppercase for comparison
    if (answer >= 'a' && answer <= 'd') {
        answer = answer - 'a' + 'A';
    }
    
    return (answer == q->correctAnswer);
}

// Function 5: Free question bank memory
void freeQuestionBank(QuestionBank* bank) {
    if (bank == NULL) return;
    
    if (bank->questions != NULL) {
        free(bank->questions);
    }
    
    free(bank);
    printf("Question bank freed successfully!\n");
}

// NEW! Function 6: Reset all questions to unused state
void resetUsedQuestions(QuestionBank* bank) {
    if (bank == NULL) return;
    
    for (int i = 0; i < bank->count; i++) {
        bank->questions[i].isUsed = 0;
    }
    
    printf("All questions reset to unused state!\n");
}