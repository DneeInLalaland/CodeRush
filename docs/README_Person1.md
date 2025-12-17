# 🎮 CodeRush - Person 1: Backend & Question System

**Developer:** Rinrada Dejsuwannachai 68070503490 
**Component:** Question Management System  
**Status:** ✅ Complete

---

## 📋 Overview

This folder contains **Person 1's work** - the Backend & Question System for CodeRush racing game.

### Responsibilities:
- ✅ Manage all game questions
- ✅ Load questions from text file
- ✅ Randomly select questions by difficulty
- ✅ Check if answers are correct/wrong
- ✅ Memory management for question bank

---

## 📁 Files Included

```
Person1_Files/
├── data/
│   ├── question.h          # Header file with structs & function declarations
│   ├── question.c          # Implementation of all functions
│   └── questions/
│       └── questions.txt   # 20 C programming questions
│
├── test_person1.c          # Test file to verify functionality
├── Makefile                # Build system (for testing)
├── main.c                  # Integration file (placeholder - needs Person 2-5)
└── README.md               # This file
```

---

## 🔧 Functions Implemented

### 1. `createQuestionBank()`
Creates an empty question bank with initial capacity of 50 questions.

### 2. `loadQuestionsFromFile(bank, filename)`
Loads questions from `questions.txt` file.

### 3. `getRandomQuestion(bank, difficulty)`
Returns a random question matching the specified difficulty level (1-5).

### 4. `checkAnswer(question, answer)`
Checks if the player's answer (A/B/C/D) is correct.

### 5. `freeQuestionBank(bank)`
Frees all memory allocated for the question bank.

---

## 🧪 Testing

### Test Person 1 functionality:

```bash
make test1
```

Expected output:
```
===========================================
   PERSON 1 - QUESTION SYSTEM TEST
===========================================

TEST 1: Creating question bank...
PASSED: Question bank created!

TEST 2: Loading questions from file...
PASSED: 20 questions loaded!

TEST 3: Displaying all questions...
[Shows all 20 questions]

TEST 4: Getting random questions by difficulty...
PASSED: Random question selection works!

TEST 5: Testing answer checking...
PASSED: Answer checking works correctly!

TEST 6: Freeing question bank...
PASSED: Memory freed successfully!

===========================================
   ALL TESTS PASSED! ✓
===========================================
```

---

## 📊 Question Format

Questions are stored in `data/questions/questions.txt` with this format:

```
Question text here?
A) First choice
B) Second choice
C) Third choice
D) Fourth choice
B
Explanation of the correct answer
2
```

**7 lines per question:**
1. Question text
2. Choice A
3. Choice B
4. Choice C
5. Choice D
6. Correct answer (A/B/C/D)
7. Explanation
8. Difficulty level (1-5)

---

## 🔗 Integration with Other Components

### Person 2 (Game Logic) will use:
```c
#include "data/question.h"

QuestionBank* bank = createQuestionBank();
loadQuestionsFromFile(bank, "data/questions/questions.txt");

// Get question for current round
Question* q = getRandomQuestion(bank, difficulty);

// Check player's answer
if (checkAnswer(q, playerAnswer)) {
    // Player answered correctly - move car forward
}
```

### Person 3 (Input System) will use:
```c
// Get player answer (A/B/C/D)
char answer = getPlayerInput();

// Person 1's function checks the answer
int correct = checkAnswer(question, answer);
```

### Person 4 (UI Display) will use:
```c
// Display the question
printf("%s\n", question->question);
printf("A) %s\n", question->choices[0]);
printf("B) %s\n", question->choices[1]);
// etc...
```

---

## ✅ Deliverables

To integrate with the full game, provide these files to the team:

```
✓ data/question.h
✓ data/question.c
✓ data/questions/questions.txt
```

**That's it!** These 3 files contain everything needed for the question system.

---

## 🚀 Next Steps

1. ✅ **Person 1 Complete** - All tests passing
2. ⏳ Wait for Person 2-5 to complete their components
3. ⏳ Team integration - combine all components
4. ⏳ Final testing of complete game

---

## 📝 Notes for Team Integration

- **No dependencies:** Person 1 can work independently
- **Used by:** Person 2, 3, 4 (all need questions)
- **File location:** Keep `data/` folder structure intact
- **Question file path:** Always `data/questions/questions.txt`
- **Memory management:** Remember to call `freeQuestionBank()` at end of game

---

## 🐛 Known Issues

None! All tests passing. ✅

---

## 📞 Contact

**Developer:** Rinrada Dejsuwannachai 68070504390
**Component:** Person 1 - Backend & Question System  
**Status:** Complete and tested

For questions about integration, see the main project README.md or contact the team lead.

---

**Ready for integration! 🎉**