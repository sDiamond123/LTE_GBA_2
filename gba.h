//graphics
unsigned short    *VRAM; 
#define VRAM_F         (unsigned short*)0x6000000 
#define VRAM_B         (unsigned short*)0x600A000
#define DISPCNT        *(unsigned int*)0x4000000
#define BACKB   	   0x10 
#define REG_BG2PA *(volatile unsigned short *)0x4000020
#define REG_BG2PD *(volatile unsigned short *)0x4000026

//keys
#define KEY_STATE      (*(volatile unsigned short*)0x4000130) 
#define KEY_A          !(KEY_STATE &   1)
#define KEY_B          !(KEY_STATE &   2)
#define KEY_SL         !(KEY_STATE &   4)
#define KEY_ST         !(KEY_STATE &   8)
#define KEY_R          !(KEY_STATE &  16)
#define KEY_L          !(KEY_STATE &  32)
#define KEY_U          !(KEY_STATE &  64)
#define KEY_D          !(KEY_STATE & 128)
#define KEY_RS         !(KEY_STATE & 256)
#define KEY_LS         !(KEY_STATE & 512)

//ram
#define IN_IWRAM       __attribute__ ((section (".iwram")))
#define IN_EWRAM       __attribute__ ((section (".ewram")))

//timer
#define REG_TM2D       *(volatile unsigned short*)0x4000108

//sound
#define REG_SOUNDCNT_X  *(volatile unsigned short*)0x4000084 //Extended sound control
#define REG_SOUNDCNT_L  *(volatile unsigned short*)0x4000080 //DMG sound control
#define REG_SOUNDCNT_H  *(volatile unsigned short*)0x4000082 //Direct sound control
#define REG_SOUND3CNT_L *(volatile unsigned short*)0x4000070
#define SOUND3BANK32    0x0000	                  //Use two banks of 32 steps each
#define SOUND3SETBANK1  0x0040
#define REG_WAVE_RAM0   *(volatile unsigned int*)0x4000090 
#define REG_WAVE_RAM1   *(volatile unsigned int*)0x4000094 
#define REG_WAVE_RAM2   *(volatile unsigned int*)0x4000098 
#define REG_WAVE_RAM3   *(volatile unsigned int*)0x400009C 
#define SOUND3SETBANK0  0x0000	                  //Bank to play 0 or 1 (non set bank is written to)
#define SOUND3PLAY	    0x0080	                  //Output sound
#define REG_SOUND3CNT_H *(volatile unsigned short*)0x4000072 
#define SOUND3OUTPUT1   0x2000	                  //Output unmodified
#define REG_SOUND3CNT_X *(volatile unsigned short*)0x4000074 
#define SOUND3INIT	    0x8000	                  //Makes the sound restart
#define SOUND3PLAYONCE  0x4000	                  //Play sound once
