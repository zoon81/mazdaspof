#ifndef INC_Bl_AUDIO_DRIVER_H
#define INC_Bl_AUDIO_DRIVER_H

#include <avr/io.h>

#define SHIFTREG_LATCH PB3
#define SHIFTREG_SCK PB1
#define SHIFTREG_DATA PB0

void bl_audio_init();
void bl_audio_ON_OFF();
void bl_audio_play_pause();
void bl_audio_next();
void bl_audio_prev();
void bl_audio_mute();
void bl_audio_unmute();

#endif