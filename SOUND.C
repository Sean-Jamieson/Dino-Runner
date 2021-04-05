#include <stdio.h>
#include <osbind.h>

typedef unsigned int UINT8;
typedef unsigned int UINT32;

void write_psg(int reg, UINT8 val);
UINT8 read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
void start_music();
void update_music(UINT32 time_elapsed);
void set_noise(int tuning);
void set_envelope(int shape, unsigned int sustain);

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
    long old_ssp = Super(0);
    *PSG_reg_select = reg;
    return *PSG_reg_write;
    Super(old_ssp);
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
/*needs condensing*/
void enable_channel(int channel, int tone_on, int noise_on)
{
    UINT8 en_psg;

    en_psg = read_psg(7);

    if (channel == 0)
    {
        if (tone_on && noise_on)
        {
            en_psg &= 0x9;
            write_psg(7, en_psg);
        }
        else if (!tone_on && !noise_on)
        {
            en_psg |= 0x9;
            write_psg(7, en_psg);
        }
        else if (tone_on && !noise_on)
        {
            en_psg &= 0x1;
            write_psg(7, en_psg);
            en_psg |= 0x8;
            write_psg(7, en_psg);
        }
        else
        {
            en_psg |= 0x1;
            write_psg(7, en_psg);
            en_psg &= 0x8;
            write_psg(7, en_psg);
        }
    }
    else if (channel == 1)
    {
        if (tone_on && noise_on)
        {
            en_psg &= 0x12;
            write_psg(7, en_psg);
        }
        else if (!tone_on && !noise_on)
        {
            en_psg |= 0x12;
            write_psg(7, en_psg);
        }
        else if (tone_on && !noise_on)
        {
            en_psg &= 0x2;
            write_psg(7, en_psg);
            en_psg |= 0x10;
            write_psg(7, en_psg);
        }
        else
        {
            en_psg |= 0x2;
            write_psg(7, en_psg);
            en_psg &= 0x10;
            write_psg(7, en_psg);
        }
    }
    else
    {
        if (tone_on && noise_on)
        {
            en_psg &= 0x24;
            write_psg(7, en_psg);
        }
        else if (!tone_on && !noise_on)
        {
            en_psg |= 0x24;
            write_psg(7, en_psg);
        }
        else if (tone_on && !noise_on)
        {
            en_psg &= 0x4;
            write_psg(7, en_psg);
            en_psg |= 0x20;
            write_psg(7, en_psg);
        }
        else
        {
            en_psg |= 0x4;
            write_psg(7, en_psg);
            en_psg &= 0x20;
            write_psg(7, en_psg);
        }
    }
}

void stop_sound()
{
    write_psg(7, 255);
}

void update_music(UINT32 time_elapsed)
{

}

void set_noise(int tuning)
{

}

void set_envelope(int shape, unsigned int sustain)
{
}