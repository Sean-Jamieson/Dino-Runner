#include <stdio.h>
#include <osbind.h>
#include "SOUND.H"
#include "SONG.H"


void write_psg(int reg, UINT8 val)
{
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write = 0xFF8802;

    long old_ssp = Super(0);
    *PSG_reg_select = reg;
    *PSG_reg_write = val;
    Super(old_ssp);
}

UINT8 read_psg(int reg)
{
    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write = 0xFF8802;
    UINT8 val;

    long old_ssp = Super(0);
    *PSG_reg_select = reg;
    val = *PSG_reg_select;
    Super(old_ssp);
    return val;
    
}

void set_tone(int channel, int tuning)
{
    if (channel == 0)
    {
        write_psg(0, tuning % 1000);
        write_psg(1, tuning / 1000);
    }
    else if (channel == 1)
    {
        write_psg(2, tuning % 1000);
        write_psg(3, tuning / 1000);
    }
    else
    {
        write_psg(4, tuning % 1000);
        write_psg(5, tuning / 1000);
    }
}

void set_volume(int channel, int volume)
{
    if (channel == 0)
    {
        write_psg(8, volume);
    }
    else if (channel == 1)
    {
        write_psg(9, volume);
    }
    else
    {
        write_psg(0xA, volume);
    }
}
/*needs condensing - also is buggy*/
void enable_channel(int channel, int tone_on, int noise_on)
{
    UINT8 en_psg;

    en_psg = read_psg(7);

    if (channel == 0){
        if (tone_on && noise_on){
            en_psg &= ~(1 << 0);
            en_psg &= ~(1 << 3);
            write_psg(7, en_psg);
        }else if (!tone_on && !noise_on){
            en_psg |= (1 << 0);
            en_psg |= (1 << 3);
            write_psg(7, en_psg);
        }else if (tone_on && !noise_on){
            en_psg &= ~(1 << 0);
            write_psg(7, en_psg);
            en_psg = read_psg(7);
            en_psg |= (1 << 3);
            write_psg(7, en_psg);
        }else{
            en_psg |= (1 << 0);
            write_psg(7, en_psg);
            en_psg = read_psg(7);
            en_psg &= ~(1 << 3);
            write_psg(7, en_psg);
        }
    }else if (channel == 1) {
        if (tone_on && noise_on){
            en_psg &= ~(1 << 1);
            en_psg &= ~(1 << 4);
            write_psg(7, en_psg);
        }else if (!tone_on && !noise_on){
            en_psg |= (1 << 1);
            en_psg |= (1 << 4);
            write_psg(7, en_psg);
        }else if (tone_on && !noise_on){
            en_psg &= ~(1 << 1);
            write_psg(7, en_psg);
            en_psg |= (1 << 4);
            write_psg(7, en_psg);
        }else{
            en_psg |= (1 << 1);
            write_psg(7, en_psg);
            en_psg &= ~(1 << 4);
            write_psg(7, en_psg);
        }
    }else{
        if (tone_on && noise_on){
            en_psg &= ~(1 << 2);
            en_psg &= ~(1 << 5);
            write_psg(7, en_psg);
        }else if (!tone_on && !noise_on){
            en_psg |= (1 << 2);
            en_psg |= (1 << 5);
            write_psg(7, en_psg);
        }else if (tone_on && !noise_on){
            en_psg &= ~(1 << 2);
            write_psg(7, en_psg);
            en_psg |= (1 << 5);
            write_psg(7, en_psg);
        }else{
            en_psg |= (1 << 2);
            write_psg(7, en_psg);
            en_psg &= ~(1 << 5);
            write_psg(7, en_psg);
        }
    }
}

void stop_sound()
{
    write_psg(7, 255);
}

void start_music(){
    enable_channel(0,1,0);
    set_tone(0, song[song_note]);
    set_volume(0, 11);
}

int update_music(UINT32 time_elapsed)
{
    if(time_elapsed >= 22)
    {
        set_tone(0, song[++song_note]);
        if(song_note >= 21)
            song_note = 0;      
        return 1;
    }
    return 0;
}

void set_noise(int tuning)
{

}

void set_envelope(int shape, unsigned int sustain)
{
}