# PERSON 2 — Game Logic & Race System (Starter)

This folder contains a compilable baseline of the core race logic for **CodeRacer**:
- `src/game/game.h`, `src/game/game.c` — main logic
- `src/main.c` — a small simulation harness (no UI/Questions), for smoke testing
- `Makefile` — build with `make` (Linux/macOS with clang/gcc)

## Build & Run
```bash
cd coderush_person2
make
./code_racer_core
```

## Notes
- Player gets **combo-based distance** and **speed boost** (visual). AI gets combo distance **but no speed boost**.
- AI correct-probability by difficulty: D1=75%, D2=70%, D3=65%, D4=60%, D5=55%.
- Race ends when **any car finishes** or **questions are exhausted** (can be adjusted easily in `checkFinish`).

## Integration Contracts (expected from other teams)
- **Question System**: provide an interface for fetching & validating questions per difficulty
- **UI**: expose functions to render track, show combo effects, correct/wrong animations
- **Save/Leaderboard**: functions to persist score, update stats, and load leaderboard
```
