#ifndef MATCH_H
#define MATCH_H


typedef enum
{
    DIALOG_INTRO,
    DIALOG_HANDRESULT,
    DIALOG_DECISION,
    DIALOG_ENDING
} DialogId;


void match(GameContext *game);

#endif