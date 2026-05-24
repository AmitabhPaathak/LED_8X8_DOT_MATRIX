void outrow(char out)
{
  volatile char *o = (char *)0x22;
  *o = out;
}

void outcol(char out)
{
  volatile char *o = (char *)0x31;
  *o = out;
}


char power(char i)
 {
    return 1 << i;
}
int main()
{
  volatile char *row = (char *)0x21;
  *row = 0xFF;
  volatile char *col = (char *)0x30;
  *col = 0xFF;
   int outA[8] = {247,235,221,190,190,128,190,190};
   int outS[8] = {1,254,254,129,127,127,128,255};
   int out1[8] = {243,241,247,247,247,247,247,193};
   int outa[8] = {243,237,239,227,237,237,237,211};
   int outdollar[8] = {1,230,230,129,103,103,128,231};
   int outalpha[8] = {191,223,233,230,233,223,191,255};
   
   int AtoE[5][8] = {
  {247, 235, 221, 190, 190, 128, 190, 190}, // A
  {193, 189, 189, 193, 189, 189, 189, 193}, // B
  {195, 189, 253, 253, 253, 253, 189, 195}, // C
  {193, 189, 125, 125, 125, 125, 189, 193}, // D
  {129, 253, 253, 193, 253, 253, 253, 129}  // E
};

  int atoe[5][8] ={
  {255, 255, 195, 191, 131, 189, 131, 255}, // Mirrored a
  {254, 254, 194, 188, 190, 190, 194, 255}, // Mirrored b
  {255, 255, 195, 253, 253, 253, 195, 255}, // Mirrored c
  {127, 127, 67, 61, 125, 125, 67, 255},   // Mirrored d
  {255, 255, 195, 189, 129, 253, 195, 255}  // Mirrored e
};

  int num1to4[5][8] = {
  {195, 189, 189, 189, 189, 189, 189, 195}, // Mirrored 0
  {239, 231, 235, 239, 239, 239, 239, 195}, // Mirrored 1
  {195, 189, 191, 223, 239, 247, 251, 129}, // Mirrored 2
  {195, 189, 191, 199, 191, 189, 189, 195}, // Mirrored 3
  {189, 189, 189, 129, 191, 191, 191, 191}  // Mirrored 4
};

  int welcome[7][8] = {
  {255 ,182, 182, 182, 182, 213, 235, 255}, //  W
  {255, 255, 195, 189, 129, 253, 195, 255}, // e
  {251, 251, 251, 251, 251, 251, 243, 255}, // l
  {255, 255, 195, 253, 253, 253, 195, 255}, // c
  {255, 255, 195, 189, 189, 189, 195, 255}, // o
  {255, 255, 129, 171, 171, 171, 171, 255},  // m
  {255, 255, 195, 189, 129, 253, 195, 255} // e
};

  // int buffer[8]= {255,255,255,255,255,255,255,255};

  // A safe, functional scrolling loop
while(1)
{
    // Loop through each character in "welcome" (7 letters)
    for(char letter = 0; letter < 7; letter++)
    {
        // Step through 8 shifts per letter to move it smoothly pixel-by-pixel
        for(char shift = 0; shift < 8; shift++)
        {
            // Repeat frame 15 times so the human eye can read the animation smooth
            for(int rep = 0; rep < 15; rep++)
            {
                for(char row_idx = 0; row_idx < 8; row_idx++)
                {
                    // 1. Activate the specific row
                    outrow(1 << row_idx);
                    
                    // 2. Fetch data, shift it cleanly without destroying original source
                    char display_byte = welcome[letter][row_idx] >> shift;
                    
                    // (Optional) Blend with the NEXT letter for fluid transition
                    if (letter < 6) {
                        display_byte |= (welcome[letter + 1][row_idx] << (8 - shift));
                    }
                    
                    // 3. Output the whole byte to columns
                    outcol(display_byte);
                    
                    // 4. Persistence of vision delay
                    for(volatile long d = 0; d <= 1000; d++);
                    
                    // 5. Clear display to eliminate ghosting artifacts
                    outcol(0xFF);
                }
            }
        }
    }
}
  }
