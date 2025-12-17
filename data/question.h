/**
 * @file question.h
 * @brief Question System - Data structures and function declarations
 * @author Rinrada Dejsuwannachai (68070503490)
 * @date December 2025
 * 
 * This module manages C programming questions for CodeRush game.
 * Provides structures for Question and QuestionBank,
 * and declares functions for loading, selecting, and validating questions.
 */

 #ifndef QUESTION_H
#define QUESTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure for a single question
typedef struct {
    char question[256];      // Question text
    char choices[4][100];    // 4 choices (A, B, C, D)
    char correctAnswer;      // Correct answer (A/B/C/D)
    char explanation[256];   // Explanation
    int difficulty;          // Difficulty level (1-5)
    int isUsed;              // NEW! Flag ว่าคำถามนี้ถูกใช้ไปแล้วหรือยัง (0 = ยังไม่ใช้, 1 = ใช้แล้ว)
} Question;

// Structure for question bank
typedef struct {
    Question* questions;     // Array of questions
    int count;              // Current number of questions
    int capacity;           // Maximum capacity
} QuestionBank;

// Function declarations
QuestionBank* createQuestionBank();
void loadQuestionsFromFile(QuestionBank* bank, const char* filename);
Question* getRandomQuestion(QuestionBank* bank, int difficulty);
int checkAnswer(Question* q, char answer);
void freeQuestionBank(QuestionBank* bank);

// NEW! Reset คำถามทั้งหมดให้กลับมาใช้ได้อีกครั้ง (เรียกตอนเริ่มเกมใหม่)
void resetUsedQuestions(QuestionBank* bank);

#endif