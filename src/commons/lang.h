#ifndef LANG_H
#define LANG_H
    typedef enum {
        LANG_ES,
        LANG_EN
}    Language;
    extern Language currentLanguage;
    
    
    extern const char *TXT_SPLASH_ENTRY;
    
    extern const char *TXT_TEST_INTRO1;
    extern const char *TXT_TEST_INTRO2;
    
    extern const char *TXT_TEST_PASS;
    extern const char *TXT_TEST_FAIL;
    extern const char *TXT_TEST_CHEAT;
    
    extern const char *TXT_WELCOME;
    extern const char *TXT_WELCOME1;
    extern const char *TXT_WELCOME2;
    extern const char *TXT_WELCOME3;

    extern const char *TXT_NEWHAND;
    extern const char *TXT_SHUFFLE;
    extern const char *TXT_DECISION;
    
    extern const char *TXT_DARE1;
    extern const char *TXT_DARE2;
    extern const char *TXT_DARE3;
    
    extern const char *TXT_DEALERBUST;
    extern const char *TXT_BUST;
    extern const char *TXT_DEALERDRAWS;
    
    extern const char *TXT_HANDWIN;
    extern const char *TXT_HANDWIN2;
    extern const char *TXT_HANDWIN3;
    extern const char *TXT_HANDLOST;
    extern const char *TXT_HANDLOST2;
    extern const char *TXT_HANDLOST3;
    
    extern const char *TXT_HANDDRAW;

    extern const char *TXT_ROUNDRESULT;
    extern const char *TXT_ROUNDRESULT1;
    extern const char *TXT_ROUNDRESULT2;
    
    extern const char *TXT_ENDINGLOSE1; 
    extern const char *TXT_ENDINGLOSE2; 
    extern const char *TXT_ENDINGWIN1; 
    
    extern const char *TXT_ENDINGWINA; 
    extern const char *TXT_ENDINGWINB; 
    extern const char *TXT_ENDINGWINC;
    
    extern const char *TXT_ENDINGWIN2;
    extern const char *TXT_ENDINGLOSEERROR;



    extern const char *TXT_CREDITS_DEVELOPMENT;
    extern const char *TXT_CREDITS_GRAPHICS;
    extern const char *TXT_CREDITS_FONT;
    extern const char *TXT_CREDITS_MUSIC;
    extern const char *TXT_CREDITS_SOUND;
    extern const char *TXT_CREDITS_TECHNOLOGY;
    extern const char *TXT_CREDITS_SPECIAL;

    extern const char *TXT_TEST_QUESTION1;
    extern const char *TXT_TEST_QUESTION2;
    extern const char *TXT_TEST_QUESTION3;
    extern const char *TXT_TEST_QUESTION4;
    extern const char *TXT_TEST_QUESTION5;
    extern const char *TXT_TEST_QUESTION6;
    extern const char *TXT_TEST_QUESTION7;
    extern const char *TXT_TEST_QUESTION8;
    extern const char *TXT_TEST_QUESTION9;
    extern const char *TXT_TEST_QUESTION10;
    
    extern const char *TXT_MENUEXIT;
    
    void loadLanguage(Language lang);
#endif

