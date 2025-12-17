//Warattaya Lekma (Aomsin)
//68070503480

#ifndef ANIMATION_H   //continue reading the code below
   #define ANIMATION_H  //mark that ANIMATION_H now exist
   
   //declare function and parameter
   void showCorrectAnimation();
   void showWrongAnimation();
   void showComboEffect(int combo);
   void showLoadingAnimation(const char* message, int duration);
   void showProgressBar(int current, int total, const char* label);
   void showCountdown();
   
   #endif
