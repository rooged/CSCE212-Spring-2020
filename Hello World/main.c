//GBA Project 1

//240x160
//ARM7tdmi 16.78 MHz
//Thumb instructions 16 bits
//0x?rrrrrgggggbbbbb (16 bit color words)
//0x00000000 -> 0x00003fff (System ROM, exe not read)
//0x02000000 -> 0x02020000 (External to the CPU RAM 256KB)
//0x03000000 -> 0x03007fff (Internal CPU RAM 32KB)
//0x04000000 -> 0x04003fff (I/O Registers)
//0x05000000 -> 0x05003fff (Color Palette)
//0x06000000 -> 0x06017fff (VRAM 96 KB)
//0x07000000 -> 0x070003ff (OAM RAM)
//0x08000000 -> 0x???????? (Game Cart ROM (up to 32MBs))
//0x0E000000 -> 0x???????? (Gamepak RAM)
#define REG_DISPLAY_VCOUNT (*(volatile unsigned short *) (0x04000006))

void sync()
{
    while(REG_DISPLAY_VCOUNT >= 160);
    while(REG_DISPLAY_VCOUNT < 160);
}

int main()
{
    volatile unsigned char *ioram = (unsigned char *) 0x04000000;
    ioram[0] = 0x03; //setting video mode 3
    ioram[1] = 0x04; //enabling video mode
    
    volatile unsigned short *vram = (unsigned short *) 0x06000000;
    
    int inc = 0;
    int clearline = 0;
    while(1)
    {
        sync();
        
        vram[clearline * 240 + 110] = 0x0000;
        vram[clearline * 240 + 120] = 0x0000;
        vram[clearline * 240 + 130] = 0x0000;
        
        vram[inc * 240 + 110] = 0x001f;
        vram[inc * 240 + 120] = 0x03e0;
        vram[inc * 240 + 130] = 0x7c00;
        
        clearline = inc;
        inc++;
        if(inc >= 160)
            inc = 0;
    }
}

















