Person 4: UI Display & Visualization Module
Role: UI/UX Designer & Graphics Developer
//3480 Warattaya Lekma
Responsibility: Display all visual elements including race track, questions, scores, animations, and effects

📁 Module Structure
src/ui/
├── colors.h        # ANSI color definitions
├── animation.h     # Animation function declarations
├── animation.c     # Animation implementations
├── graphics.h      # Graphics function declarations
├── graphics.c      # Race track and sprite rendering
├── ui.h           # Main UI header
└── ui.c           # UI display implementations

📄 File Descriptions
1. colors.h
Purpose: Define ANSI color codes for terminal output
Contents:

Color definitions (RED, GREEN, YELLOW, BLUE, etc.)
Text styling (BOLD, RESET)

Status: ✅ Complete (100%)
Dependencies: None

2. animation.h
Purpose: Declare animation functions
Functions:

void showCorrectAnimation() - Display "CORRECT!" animation
void showWrongAnimation() - Display "WRONG!" animation
void showComboEffect(int combo) - Display combo multiplier effects
void showLoadingAnimation(const char* message, int duration) - Loading screen
void showProgressBar(int current, int total, const char* label) - Progress bar
void showCountdown() - 3, 2, 1, GO! countdown

Status: ✅ Complete (100%)
Dependencies: None

3. animation.c
Purpose: Implement all animation functions
Key Features:

Cross-platform sleep function (Windows/Mac/Linux)
Frame-based animations
Combo tier system (x3, x5, x7+)
Color-coded feedback

Platform Support:

✅ Windows (using Sleep())
✅ Mac/Linux (using usleep())

Status: ✅ Complete (100%)
Dependencies:

animation.h
colors.h
ui.h (for clearScreen())
4. graphics.h
Purpose: Declare graphics rendering functions
Functions:

void drawCarSprite(int isPlayer) - Draw car emoji (🏎 or 🤖)
void drawRaceTrack(GameState* game) - Render complete race track

Status: ✅ Complete (100%)
Dependencies:

ui.h
../game/game.h (Person 2)

External Requirements:

GameState struct from Person 2
Racer struct from Person 2
Constants: NUM_AI_CARS, FINISH_LINE


5. graphics.c
Purpose: Implement race track visualization
Key Features:

Real-time position display
Progress percentage (0-100%)
Combo indicator
Statistics panel
Time tracking
Multi-car display (player + 3 AI)

Display Elements:
╔════════════════════════════════════════╗
║  🏁 CODE RACER - RACE VIEW 🏁           ║
╚════════════════════════════════════════╝

📝 Question 5 / 10 | ⏱ Time: 45 seconds

START ────────────────────────────── FINISH
YOU   │    │    🏎│    │    │    │   (62%) ⚡x4
Code  │    │      │ 🤖 │    │    │   (58%)
Swift │    │   🤖 │    │    │    │   (68%)
Byte  │    │      │🤖  │    │    │ (61%)

┌────────────────────────────────────────┐
│ 📊 Stats: ✅ Correct: 7 ❌ Wrong: 2     │
│ 🎯 Accuracy: 77.8%                     │
└────────────────────────────────────────┘

Status: ✅ Complete (100%)
Dependencies:

graphics.h
colors.h
../game/game.h (Person 2)

Required Fields from GameState:
game->currentQuestion
game->totalQuestions
game->startTime
game->player.position
game->player.combo
game->player.totalCorrect
game->player.totalWrong
game->aiCars[i].name
game->aiCars[i].position

6. ui.h
Purpose: Main UI header with all display functions
Functions:

Core:

void clearScreen() - Clear terminal
void drawLine(int length, char character) - Draw horizontal line
void printCentered(const char* text, int width) - Center text
void drawBox(const char* title, int width) - Draw bordered box


Display:

void displayQuestion(Question* q, int questionNum, int totalQuestions) - Show question
void displayGameStats(GameState* game) - Show final results
void displayLeaderboard() - Show top scores


Screens:

void showHowToPlay() - Instructions screen
void showTitleScreen() - Title/logo screen



Status: ✅ Complete (100%)
Dependencies:

Standard libraries: <stdio.h>, <stdlib.h>, <string.h>
Platform-specific: <windows.h> or <unistd.h>
../game/game.h (Person 2)
../data/question.h (Person 3)


7. ui.c
Purpose: Implement all UI display functions
Key Features:
Question Display:
╔════════════════════════════════════════╗
║          📝 QUESTION 05 / 10           ║
╠════════════════════════════════════════╣
║ Difficulty: ⭐⭐⭐☆☆                    ║
╠════════════════════════════════════════╣
║ Code:                                  ║
║   ┌────────────────────────────────┐   ║
║   │ int x = 5;                     │   ║
║   │ int y = ++x;                   │   ║
║   │ printf("%d %d", x, y);         │   ║
║   └────────────────────────────────┘   ║
╠════════════════════════════════════════╣
║ What will be the output?               ║
╠════════════════════════════════════════╣
║  A) 5 5                                ║
║  B) 6 6                                ║
║  C) 5 6                                ║
║  D) 6 5                                ║
╚════════════════════════════════════════╝

Game Stats Display:

Final rank with medals (🥇🥈🥉)
Player statistics
Accuracy percentage
Time used
AI opponent positions
Final score

Title Screen:

ASCII art logo
Tagline
Start prompt

Status: ✅ Complete (100%)
Dependencies:

ui.h
colors.h
../game/game.h (Person 2)
../data/question.h (Person 3)

Required from Person 2:

calculateScore(GameState* game) function

Required Fields from Question:
q->code
q->options[4]
q->difficulty

Known Issues & Solutions

Issue 1: Colors not displaying on Windows
Solution:
Enable ANSI support in Windows terminal:
#ifdef _WIN32
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
DWORD dwMode = 0;
GetConsoleMode(hOut, &dwMode);
dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
SetConsoleMode(hOut, dwMode);
#endif

Issue 2: Emojis not displaying
Solution:

•Use terminal that supports Unicode (iTerm2, Windows Terminal, etc.)
•Alternative: Replace emojis with ASCII:
#define CAR_PLAYER ">"
#define CAR_AI "@"

Issue 3: Layout misalignment
Solution:

•Ensure terminal width is at least 80 characters
•Check font is monospace
•Adjust spacing in format strings

Issue 4: Compilation errors with game.h
Solution:

•If Person 2 hasn't finished yet, use forward declarations:
typedef struct GameState GameState;
typedef struct Racer Racer;



Design Decisions
Color Scheme:

🟢 Green - Correct answers, player car
🔴 Red - Wrong answers
🟡 Yellow - Combo effects, code highlighting
🔵 Cyan - AI cars
⚪ White - Default text

Layout:

•Box borders - Use Unicode box-drawing characters
•Width - 70 characters for main content
•Alignment - Centered headers, left-aligned content
•Spacing - Consistent padding and margins

Animations:

•Duration - 300-1000ms for effects
•Frames - 2-3 frames per animation
•Smoothness - Use fflush(stdout) for immediate display

Testing
Test Animations (Standalone):
# Create test file
cat > test_animation.c << 'EOF'
#include "ui/animation.h"
int main() {
    showCorrectAnimation();
    showWrongAnimation();
    showComboEffect(5);
    showCountdown();
    return 0;
}
EOF

# Compile
gcc -o test_anim test_animation.c src/ui/animation.c -Isrc

# Run
./test_anim

Test UI Screens (Standalone):
# Create test file
cat > test_ui.c << 'EOF'
#include "ui/ui.h"
int main() {
    showTitleScreen();
    showHowToPlay();
    return 0;
}
EOF

# Compile
gcc -o test_ui test_ui.c src/ui/ui.c -Isrc

# Run
./test_ui

Test with Mock Data:
# Full test with mock GameState
gcc -o test_full test_full.c src/ui/*.c -Isrc
./test_full

Compilation
Compile UI Module Only:
gcc -c src/ui/animation.c -o animation.o -Isrc
gcc -c src/ui/graphics.c -o graphics.o -Isrc
gcc -c src/ui/ui.c -o ui.o -Isrc

Compile with Main Program:
gcc -o code_racer src/main.c \
    src/ui/animation.c \
    src/ui/graphics.c \
    src/ui/ui.c \
    src/game/game.c \
    src/data/question.c \
    -Isrc