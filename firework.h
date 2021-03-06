/* Global definitions for this pattern, must be unique, it
is a good idea to prefix the pattern name. */
unsigned char firework_pos;
unsigned char firework_exp_pos;
unsigned char firework_col;
unsigned long firework_exp_col;
unsigned char firework_size;
enum firework_states {
  LAUNCHED = 1,
  EXPLODED = 2
};
enum firework_states firework_state;

/* Private functions for this pattern, if you need any.
Make the names unique. */

/* init function for this pattern, called when beginning
this pattern before the first call of x_frame(). Prefixed
with the pattern name. */
void firework_init(void) {
  firework_pos = 0;
  firework_state = LAUNCHED;
  firework_exp_pos = random((NUM_LEDS>>1), NUM_LEDS-10);
  return;
}

unsigned char percent(unsigned int n, unsigned char d) {
  unsigned char r = 0;
  n *= 100;
  while (n >= d) {
    n -= d;
    r++;
  }
  return r;
}

/* frame function for this pattern, called 25 times per
second while displaying this pattern. It should be fairly
efficient, if it takes too long P1.0 output will be set
to 1 (red LED on launchpad). Prefixed with pattern name. */
void firework_frame(void) {
  /* colour(colour, brightness) is a useful helper function,
    it will retrun the 24 bit RGB value as unsigned long for
    a colour defined in ../colours.h and brightness from 0
    to 99 as unsigned char. */
  if (firework_state == LAUNCHED) {
    if (firework_pos >= firework_exp_pos) {
      firework_state = EXPLODED;
      firework_pos = 0; // size of explosion
      firework_col = random(1,NUM_COLOURS); //max argument on random is exclusive, min is inclusive
      firework_size = random(10,20);
      firework_exp_col =
        colour(firework_col, percent(firework_size-firework_pos,firework_size));
    } else {
      firework_pos++;
    }
  } else {
    if (firework_pos == firework_size) {
      firework_init();
    } else {
      firework_pos++;
      firework_exp_col =
        colour(firework_col, percent(firework_size-firework_pos,firework_size));
    }
  }
  return;
}

/* getled function for this pattern called many times in no
guarented order, but always after the frame function has
finished.
Will be passed and unsigned char representing an LED index,
you must return the 24bit RGB value as unsigned long for that
LED. Your pattern should handle as many LEDs as are defined by
NUM_LEDS, that's up to 255.
Prefixed with pattern name. */
unsigned long firework_getled(unsigned char led) {
  if (firework_state == LAUNCHED) {
    return firework_pos == led ? 0xff7f7f : 0x000000;
  } else {
    for (unsigned char i = 0; i < 3; i++) {
      unsigned char offset = firework_pos >> i;
      if (led == firework_exp_pos+offset || led+offset == firework_exp_pos) {
        return firework_exp_col;
      }
    }
  }
  return 0x000000;
}
