//Warattaya Lekma (Aomsin)
//68070503480

// animation.c - for Mac/Linux/Windows 
#include "animation.h" //import animation.h (all declarations of function)
#include "colors.h" //import  colors code
#include "symbols.h" //import sysmbol and emoji
#include "ui.h"  //import UI function
#include <stdio.h>

// for Mac/Linux using unistd.h
#ifdef _WIN32 //if compile on Wimdows _WIN32 will be defined
    #include <windows.h> //import <Windows API library>
    #define SLEEP(ms) Sleep(ms) //build macro sleep >> on the Windows call Sleep(ms)
#else //if it is not Windows (Mac/Linux)
    #include <unistd.h> //import Unix library
    #define SLEEP(ms) usleep((ms) * 1000)  //build macro sleep >> on the Mac/Linux call usleep() , at defind we have to times 1000 because usleep() obtain microsecond(1ms = 1000 microsecond)
#endif

// Animation for correct answer
void showCorrectAnimation() {
    printf("\n");
    // Frame 1
    printf("%s", COLOR_GREEN); //green color
    printf("   %s%s%s%s%s%s%s\n", SYM_CHECK, SYM_CHECK, SYM_CHECK, SYM_CHECK, SYM_CHECK,SYM_CHECK,SYM_CHECK); //print 7 correct symbols
    printf("   %s CORRECT! %s\n", SYM_CHECK, SYM_CHECK); //print correct symbols and CORRECT!
    printf("   %s%s%s%s%s%s%s\n", SYM_CHECK, SYM_CHECK, SYM_CHECK, SYM_CHECK, SYM_CHECK,SYM_CHECK,SYM_CHECK); //print 7 correct symbols
    printf("%s", COLOR_RESET); //reset to normal color
    SLEEP(300); //stop for 0.3 seconds let player see frame 1
    
    // Frame 2
    printf("\n");
    printf("%s%s", COLOR_GREEN, COLOR_BOLD); //word bold and green color
    printf("   ╔═══════════════╗\n");
    printf("   ║ %s CORRECT! %s║\n", SYM_CHECK, SYM_CHECK); //print word and correct sysmbols
    printf("   ╚═══════════════╝\n"); //print frame
    printf("%s", COLOR_RESET); //reset to normal color
    SLEEP(500); //stop for 0.5 seconds let player see frame 2
}

// Animation for wrong answer
void showWrongAnimation() {
    printf("\n");
    // Frame 1
    printf("%s", COLOR_RED); //red color
    printf("   %s%s%s%s%s%s%s\n", SYM_CROSS, SYM_CROSS, SYM_CROSS, SYM_CROSS, SYM_CROSS, SYM_CROSS, SYM_CROSS); //print 7 cross symbols
    printf("   %s  WRONG!  %s\n", SYM_CROSS, SYM_CROSS); //print cross symbols and WRONG!
    printf("   %s%s%s%s%s%s%s\n", SYM_CROSS, SYM_CROSS, SYM_CROSS, SYM_CROSS, SYM_CROSS,SYM_CROSS,SYM_CROSS); //print 7 cross symbols
    printf("%s", COLOR_RESET); //reset to normal color
    SLEEP(300); //stop for 0.3 seconds let player see frame 1
    
    // Frame 2
    printf("\n");
    printf("%s%s", COLOR_RED, COLOR_BOLD); //word bold and red color
    printf("   ╔═══════════════╗\n");
    printf("   ║ %s WRONG!  %s ║\n", SYM_CROSS, SYM_CROSS); //print word and cross sysmbols
    printf("   ╚═══════════════╝\n"); //print frame
    printf("%s", COLOR_RESET); //reset to normal color
    SLEEP(500); //stop for 0.5 seconds let player see frame 2
}

// show Combo Effect
void showComboEffect(int combo) { //obtain combo value
    printf("\n");
    if (combo >= 3 && combo < 5) { //if combo ==3 or ==4
        printf("%s", COLOR_YELLOW); //yellow color
        printf("   %s COMBO x%d! %s\n", SYM_LIGHTNING, combo, SYM_LIGHTNING); //print word and lightning symbols
        printf("   Speed Boost!\n");
        printf("%s", COLOR_RESET); //reset to normal color
    } else if (combo >= 5 && combo < 7) { //if combo ==5 or ==6
        printf("%s%s", COLOR_YELLOW, COLOR_BOLD); //word bold and yellow color
        printf("   %s%s SUPER COMBO x%d! %s%s\n", SYM_LIGHTNING, SYM_LIGHTNING, combo, SYM_LIGHTNING, SYM_LIGHTNING); //print word and lightning symbols
        printf("   MEGA SPEED!\n"); 
        printf("%s", COLOR_RESET); //reset to normal color
    } else if (combo >= 7) { //if combo more than or ==7
        printf("%s%s", COLOR_MAGENTA, COLOR_BOLD); //word bold and magenta color
        printf("   %s%s%s ULTRA COMBO x%d! %s%s%s\n", SYM_SPARKLE, SYM_LIGHTNING, SYM_LIGHTNING, combo, SYM_LIGHTNING, SYM_LIGHTNING, SYM_SPARKLE); //print word and symbols
        printf("   %s MAXIMUM OVERDRIVE! %s\n", SYM_FIRE, SYM_FIRE);
        printf("%s", COLOR_RESET); //reset to normal color
    }
    SLEEP(1000); //stop for 1 seconds
}

// Loading Animation => for someone to call it
void showLoadingAnimation(const char* message, int duration) { //duration = total time (ms)
    if (!message) { //if there is no sending message, using Loading instead
        message = "Loading";
    }
    
    printf("\n%s", message);
    int dots = duration / 300; //calculate dots, each dot take time 300 ms
    for (int i = 0; i < dots; i++) { //print . and loop (dot value)
        printf(".");
        fflush(stdout); //force to show/print immediately
        SLEEP(300); //wait 0.3 ms befor print next dot
    }
    printf("\n");
}

// Progress Bar
void showProgressBar(int current, int total, const char* label) {
    if (total <= 0) return; //prevent division by 0
    
    int barWidth = 50; // bar wide = 50 alphabets
    float progress = (float)current / total; //calculate percentage of progression, (float) = change to decimal
    int filled = (int)(progress * barWidth); //calculate filled bar length
    
    if (label) { //if there is label then show it
        printf("%s: ", label);
    }
    
    printf("[");
    
    //Show finished part
    printf("%s", COLOR_GREEN); //green color
    for (int i = 0; i < filled; i++) { //print # up to filled length
        printf("#");
    }
    printf("%s", COLOR_RESET); //reset to normal color
    
    //Show unfinished part
    for (int i = filled; i < barWidth; i++) { //print - up to unfilled length
        printf("-");
    }
    
    printf("] %.1f%%\n", progress * 100); //show progress percentage
}

// Countdown animation 
void showCountdown() {
    clearScreen();
    printf("\n\n\n\n\n"); //5 new lines
    
    for (int i = 3; i > 0; i--) { //loop 3,2,1
        printf("\r        %d... ", i); // /r = carriage return (start with the biginning of that line, not newline)
        fflush(stdout); ////force to show/print immediately
        SLEEP(1000); //wait 1 second
    }
    
    printf("\r%s%s", COLOR_GREEN, COLOR_BOLD); //word bold and green
    printf("        %s GO! %s\n", SYM_FLAG, SYM_CAR_PLAYER); //print emoji and word
    printf("%s", COLOR_RESET); //reset to normal color
    SLEEP(500); //wait 0.5 second
}
