typedef unsigned int UINT8;
typedef unsigned int UINT32;

void write_psg(int reg, UINT8 val);
UINT8 read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound();
void start_music();
int update_music(UINT32 time_elapsed);
void set_noise(int tuning);
void set_envelope(int shape, unsigned int sustain);
