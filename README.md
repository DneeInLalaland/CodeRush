# 🏎️ CodeRush

A competitive racing game where players answer C programming questions to move forward!

---

## 📖 About

**CodeRush** is an educational racing game where you compete against 3 AI opponents by answering C programming questions. Answer correctly to move your car forward, build combos for speed boosts, and race to the finish line!

### 🎮 Game Features

- **Question-Based Racing**: Answer C programming questions to move forward
- **Combo System**: Answer consecutively correct for speed boosts
- **AI Opponents**: Race against 3 computer-controlled cars
- **Difficulty Levels**: Questions from level 1 (easy) to 5 (hard)
- **Save System**: Track your progress and high scores

---

## 👥 Team Structure

This project is divided into 5 main components:

| Person | Component | Responsibility |
|--------|-----------|----------------|
| **Person 1** | Backend & Question System | Manage questions, load from files, check answers |
| **Person 2** | Game Logic & Race System | Handle race mechanics, AI, scoring, combos |
| **Person 3** | Input System | Get player input, validate answers, menu system |
| **Person 4** | UI Display | Display race track, questions, animations |
| **Person 5** | Save/Load System | Save game results, load previous scores |

---

## 📁 Project Structure
```
CodeRush/
|-- data/                    # Person 1 - Question System
|   |-- question.h
|   |-- question.c
|   |-- backup/              # Backup files
|   |-- questions/
|   |   +-- questions.txt    # Question database (15 KB)
|   +-- save/                # Save data
|       |-- leaderboard
|       |-- player_TestPlayer
|       +-- savegame_TestPlayer
|
|-- game/                    # Person 2 - Game Logic
|   |-- game.h
|   +-- game.c
|
|-- input/                   # Person 3 - Input System
|   |-- input.h
|   +-- input.c
|
|-- ui/                      # Person 4 - UI Display
|   |-- ui.h
|   |-- ui.c
|   |-- graphics.h
|   |-- graphics.c
|   |-- animation.h
|   |-- animation.c
|   |-- colors.h
|   +-- symbols.h
|
|-- save/                    # Person 5 - Save/Load System
|   |-- save.h
|   +-- save.c
|
|-- tests/                   # Test files
|   |-- test_adaptive.c
|   |-- test_person1.c
|   |-- test_person2.c
|   |-- test_person3.c
|   |-- test_person4.c
|   |-- test_person5.c
|   +-- test_progress        # Test results
|
|-- docs/                    # Documentation
|   |-- README_Person1.md
|   |-- README_Person2.md
|   |-- README_Person3.md
|   |-- README_Person4.md
|   +-- README_Person5.md
|
|-- test_bin/                # Compiled test executables
|-- main.c                   # Main game file
|-- Makefile                 # Build system
|-- run_all_tests.sh         # Test runner script
+-- README.md                # This file
```


## 🚀 Getting Started

### Prerequisites

- **GCC Compiler** (or any C compiler)
- **Make** (optional, but recommended)
- Terminal/Command Prompt

### Installation

1. **Clone or download** this repository

2. **Navigate to the project directory:**
```bash
   cd CodeRush
```

---

## 🔨 Building the Project

### **Linux/Mac:**
```bash
make          # Build the complete game
make debug    # Build with debug symbols (if available)
make release  # Build optimized version (if available)
```

### **Windows:**

**Option 1: Using Make (if installed)**
```bash
make
./CodeRush.exe
```

**Option 2: Direct compilation (recommended)**
```bash
gcc -Wall -Wextra -g3 -o CodeRush.exe main.c data/question.c game/game.c input/input.c ui/ui.c ui/graphics.c ui/animation.c save/save.c -lm
./CodeRush.exe
```

**To install Make on Windows:**
```powershell
# Open PowerShell as Administrator
choco install make -y
```

---

## 🧪 Testing Individual Components

Each person can test their component independently (requires Makefile support):
```bash
# Test Person 1 - Question System
make test1

# Test Person 2 - Game Logic
make test2

# Test Person 3 - Input System
make test3

# Test Person 4 - UI Display
make test4

# Test Person 5 - Save/Load System
make test5

# Run all tests
make test-all
```

**Note:** If Makefile test targets are not configured, you can compile and run test files manually:
```bash
gcc -Wall -Wextra -g3 tests/test_person1.c data/question.c -o test_person1.exe
./test_person1.exe
```

---

## 🎮 Running the Game

### **Linux/Mac:**
```bash
make run
```

Or directly:
```bash
./CodeRush
```

### **Windows:**
```bash
./CodeRush.exe
```
Or:
```bash
CodeRush.exe
```

If using Make:
```bash
make run
```

---

## 🎯 How to Play

1. **Start the game** - Choose your difficulty level (1-5)
2. **Answer questions** - Read the C programming question and choose A, B, C, or D
3. **Build combos** - Answer correctly multiple times in a row for speed boosts:
   - 3+ correct: Speed boost
   - 5+ correct: Super speed
   - 7+ correct: MEGA speed
4. **Race to the finish** - First car to reach the finish line wins!

---

## 📝 Development Workflow

### For Individual Developers:

1. **Work on your assigned component** (Person 1-5)
2. **Test your code** using `make test[1-5]`
3. **Commit your changes** to your branch
4. **Send your files** to the team lead for integration

### For Team Integration:

1. **Collect all components** from Person 1-5
2. **Place files** in correct directories
3. **Build the project**: `make`
4. **Test the integrated game**: `make run`

---

## 🗑️ Cleaning Up

### Remove compiled files:
```bash
make clean
```

### Remove everything (including save data):
```bash
make cleanall
```

### **Windows (without Make):**
```bash
del *.o *.exe
del data\*.o game\*.o input\*.o ui\*.o save\*.o
```

**Note:** The Makefile's `clean` command works on both Linux/Mac and Windows (if Make is installed).

---

## 📊 Current Status

| Component | Status | Developer |
|-----------|--------|-----------|
| Person 1 - Questions | ✅ Complete | Rinrada Dejsuwannachai 3490 |
| Person 2 - Game Logic | ✅ Complete |  Varakron Vimolgarnjana 3452 |
| Person 3 - Input | ✅ Complete | Sirapobe Parinyarat 3483 |
| Person 4 - UI | ✅ Complete | Warattaya Lekma 3480 |
| Person 5 - Save/Load | ✅ Complete | Karnsinee Nikrotamethanee 3412 |
| Integration | ✅ Complete | Rinrada Dejsuwannachai 3490 |

---

## 🐛 Troubleshooting

### Common Issues:

**Error: `gcc: command not found`**
- Install GCC compiler:
  - **Mac**: `xcode-select --install`
  - **Linux**: `sudo apt install gcc`
  - **Windows**: Install MinGW or use WSL

**Error: `Cannot open file 'data/questions/questions.txt'`**
- Make sure you're running from the CodeRush directory
- Check that the file exists: `ls data/questions/questions.txt`

**Error: Undefined reference to functions**
- Make sure all Person 1-5 files are present
- Try: `make clean` then `make`

---

## 📚 Documentation

### For Developers:

Each component has detailed documentation in the `docs/` folder:
- `docs/README_Person1.md` - Question System
- `docs/README_Person2.md` - Game Logic
- `docs/README_Person3.md` - Input System
- `docs/README_Person4.md` - UI Display
- `docs/README_Person5.md` - Save/Load System

### Question File Format:

Questions are stored in `data/questions/questions.txt` in this format:
```
Question text here
A) First choice
B) Second choice
C) Third choice
D) Fourth choice
B
Explanation of the answer
2
```
(7 lines per question: question + 4 choices + answer + explanation + difficulty)

---

## 🤝 Contributing

1. Work on your assigned component
2. Test thoroughly before submitting
3. Follow C coding standards
4. Comment your code
5. Update documentation if needed

---

## 📄 License

This is an educational project for KMUTT Computer Engineering students.

---

## 👏 Credits

Developed by Computer Engineering Students, KMUTT
- Person 1: Team - Question System
- Person 2: Team - Game Logic
- Person 3: Team - Input System
- Person 4: Team - UI Display
- Person 5: Team - Save/Load System
- Integration: Team - Main Program & Integration

---

## 📞 Contact

For questions or issues, contact the team lead or create an issue in the repository.

---

**Happy Racing! 🏁**
