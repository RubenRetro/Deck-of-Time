#ifndef TRACKER_SONG_H
#define TRACKER_SONG_H

#define SONG_LINE_MS 40

#define PAT0_LEN 73
static const unsigned int pat0_freq[PAT0_LEN]={65,123,0,0,0,0,0,0,65,659,494,659,494,0,0,0,0,740,622,740,622,0,784,659,784,659,0,0,0,0,740,880,740,880,740,880,0,0,0,0,65,784,659,784,659,0,0,0,65,587,740,587,740,0,784,659,784,659,0,0,0,0,659,523,659,523,659,523,659,523,659,523,65};

static const int song_order[]={0};
void play_song(void);

void spk_on(unsigned int freq);
void spk_off(void);
#define SONG_ORDER_LEN 1

#endif /* TRACKER_SONG_H */
