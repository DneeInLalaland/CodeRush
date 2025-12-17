//Warattaya Lekma (Aomsin)
//68070503480

#ifndef SYMBOLS_H //continue reading the code below
#define SYMBOLS_H //defind SYMBOLS_H

#ifdef _WIN32 //check OS => Windows
    // Windows fallback - using ASCII instead of emoji
    #define SYM_CAR_PLAYER  ">"
    #define SYM_CAR_AI      "@"
    #define SYM_CHECK       "[OK]"
    #define SYM_CROSS       "[X]"
    #define SYM_STAR_FULL   "*"
    #define SYM_STAR_EMPTY  "."
    #define SYM_LIGHTNING   "!"
    #define SYM_TROPHY      "[TROPHY]"
    #define SYM_FLAG        "[FLAG]"
    #define SYM_MEDAL_GOLD  "[1st]"
    #define SYM_MEDAL_SILVER "[2nd]"
    #define SYM_MEDAL_BRONZE "[3rd]"
    #define SYM_FIRE        "~"
    #define SYM_SPARKLE     "+"
    #define SYM_QUESTION    "[Q]"
    #define SYM_STATS       "[i]"
    #define SYM_TIMER       "[T]"
    #define SYM_TARGET      "(o)"
    #define SYM_SAVE        "[S]"
    #define SYM_PLAY        "[>]"
    #define SYM_BOOK        "[B]"
    #define SYM_EXIT        "[X]"
    #define SYM_COMBO       "x"
#else
    // Mac/Linux - using emoji
    #define SYM_CAR_PLAYER  "🏎 "
    #define SYM_CAR_AI      "🤖"
    #define SYM_CHECK       "✅"
    #define SYM_CROSS       "❌"
    #define SYM_STAR_FULL   "⭐"
    #define SYM_STAR_EMPTY  "☆"
    #define SYM_LIGHTNING   "⚡"
    #define SYM_TROPHY      "🏆"
    #define SYM_FLAG        "🏁"
    #define SYM_MEDAL_GOLD  "🥇"
    #define SYM_MEDAL_SILVER "🥈"
    #define SYM_MEDAL_BRONZE "🥉"
    #define SYM_FIRE        "🔥"
    #define SYM_SPARKLE     "✨"
    #define SYM_QUESTION    "📝"
    #define SYM_STATS       "📊"
    #define SYM_TIMER       "⏱"
    #define SYM_TARGET      "🎯"
    #define SYM_SAVE        "💾"
    #define SYM_PLAY        "🎮"
    #define SYM_BOOK        "📖"
    #define SYM_EXIT        "🚪"
    #define SYM_COMBO       "⚡x"
#endif

#endif
