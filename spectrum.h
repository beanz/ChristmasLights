//Definitions for this pattern
  unsigned int spectrum_mode;
  unsigned int spectrum_dir;
  unsigned int spectrum_index;

//functions for this pattern

//init function
void spectrum_init(void) {
  spectrum_index = 0;
  spectrum_mode = 0;
  spectrum_dir = 1;
  return;
}

//frame function
void spectrum_frame(void) {
  spectrum_index += spectrum_dir;
  if (spectrum_index >= 9 || spectrum_index <= 0) {
    spectrum_dir = -spectrum_dir;
    spectrum_mode++;
  }
  return;
}

//getled function
unsigned long spectrum_getled(unsigned char led) {
  led += spectrum_index/2;
  char col1 = BLUE;
  unsigned char col2 = YELLOW;
  if ((spectrum_mode % 20) < 5) {
    led = led >> 1;
    col1 = RED;
    col2 = CYAN;
  }
  if (led % 2) {
    return(colour(col1,99));
  } else {
    return(colour(col2,99));
  }
}
