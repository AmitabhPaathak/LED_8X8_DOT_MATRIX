//Read the README file first 
//Simulated on Platform IO
// out function for port A as Row


void outrow(char out)
{
  volatile char *o = (char *)0x22;
  *o = out;
}

//out function for port F as Column
void outcol(char out)
{
  volatile char *o = (char *)0x31;
  *o = out;
}


int main()
{
  volatile char *row = (char *)0x21;            // setting up port A for row
  *row = 0xFF;
  volatile char *col = (char *)0x30;            // setting up port F for column 
  *col = 0xFF;
  

  int welcome[7][8] = {
  {255 ,182, 182, 182, 182, 213, 235, 255}, //  W
  {255, 255, 195, 189, 129, 253, 195, 255}, // e
  {251, 251, 251, 251, 251, 251, 243, 255}, // l
  {255, 255, 195, 253, 253, 253, 195, 255}, // c
  {255, 255, 195, 189, 189, 189, 195, 255}, // o
  {255, 255, 129, 171, 171, 171, 171, 255},  // m
  {255, 255, 195, 189, 129, 253, 195, 255} // e
};

while(1)
{
    // Loop through each character in "welcome" (7 letters)
    for(char letter = 0; letter < 7; letter++)
    {
        // 8 shifts per letter to move it smoothly as we have a 8x8 bit display
        for(char shift = 0; shift < 8; shift++)
        {
            // Repeat frame 15 times for humans to see
            for(int rep = 0; rep < 15; rep++)
            {
                for(char row_idx = 0; row_idx < 8; row_idx++)
                {
                    // Activate the specific row
                    outrow(1 << row_idx);
                    
                    // Fetch the row value to be displayed 
                    char display_byte = welcome[letter][row_idx] >> shift;
                    
                    // Blend with the next letter for fluid transition
                    if (letter < 6) {
                        display_byte |= (welcome[letter + 1][row_idx] << (8 - shift));
                    }
                    
                    // Output the whole byte to columns
                    outcol(display_byte);
                    
                    // Delay for the eyes to actually see the light glow
                    for(volatile long d = 0; d <= 1000; d++);
                    
                    // Clear display to eliminate ghosting artifacts
                    outcol(0xFF);
                }
            }
        }
    }
}
  }
