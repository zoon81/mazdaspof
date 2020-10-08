#include "bl_audio_driver.h"
#include <util/delay.h>

#define CLK_PERIOD 10

#define BL_AUDIO_COMMAND_ON_BITPOS      0x00
#define BL_AUDIO_COMMAND_PLAY_BITPOS    0x01
#define BL_AUDIO_COMMAND_NEXT_BITPOS    0x02
#define BL_AUDIO_COMMAND_PREV_BITPOS    0x03
#define BL_AUDIO_COMMAND_MUTE_BITPOS    0x04
#define BL_AUDIO_COMMAND_DEFAULT        0x00    // 0b11101110

void shiftreg_sendData( uint8_t data);

void bl_audio_init(){
    // SetUp SW shift reg driver
    DDRB |= (1 << SHIFTREG_DATA) | (1 << SHIFTREG_LATCH) | (1 << SHIFTREG_SCK);
    shiftreg_sendData(BL_AUDIO_COMMAND_DEFAULT);
}

void bl_audio_deinit(){
    DDRB &= ~( 1 << SHIFTREG_DATA );
    DDRB &= ~( 1 << SHIFTREG_SCK );
}

void bl_audio_ON_OFF(){
    shiftreg_sendData( BL_AUDIO_COMMAND_DEFAULT | (1 << BL_AUDIO_COMMAND_ON_BITPOS));
    _delay_ms(2000);
    shiftreg_sendData(BL_AUDIO_COMMAND_DEFAULT);
}

void bl_audio_play_pause(){
    shiftreg_sendData( BL_AUDIO_COMMAND_DEFAULT | (1 << BL_AUDIO_COMMAND_PLAY_BITPOS));
    _delay_ms(1000);
    shiftreg_sendData(BL_AUDIO_COMMAND_DEFAULT);
}

void bl_audio_next(){
    shiftreg_sendData( BL_AUDIO_COMMAND_DEFAULT | (1 << BL_AUDIO_COMMAND_NEXT_BITPOS));
    _delay_ms(1000);
    shiftreg_sendData(BL_AUDIO_COMMAND_DEFAULT);
}

void bl_audio_prev(){
    shiftreg_sendData( BL_AUDIO_COMMAND_DEFAULT | (1 << BL_AUDIO_COMMAND_PREV_BITPOS));
    _delay_ms(1000);
    shiftreg_sendData(BL_AUDIO_COMMAND_DEFAULT);
}

void bl_audio_mute(){
    shiftreg_sendData( BL_AUDIO_COMMAND_DEFAULT | (1 << BL_AUDIO_COMMAND_MUTE_BITPOS));
}

void bl_audio_unmute(){
    shiftreg_sendData(BL_AUDIO_COMMAND_DEFAULT);
}

void shiftreg_sendData( uint8_t data){
    int8_t bitmask = 7;
    while(bitmask >= 0){
        if(data & (1 << bitmask)){
            PORTB |= ( 1 << SHIFTREG_DATA);
        } else {
            PORTB &= ~( 1 << SHIFTREG_DATA );
        }
        PORTB |= ( 1 << SHIFTREG_SCK );
        _delay_ms(CLK_PERIOD);
        PORTB &= ~( 1 << SHIFTREG_SCK );
        _delay_ms(CLK_PERIOD);
        bitmask--;
    }
    // Latch out
    PORTB |= ( 1 << SHIFTREG_LATCH );
    _delay_ms(CLK_PERIOD);
    PORTB &= ~( 1 << SHIFTREG_LATCH );
    _delay_ms(CLK_PERIOD);
}

