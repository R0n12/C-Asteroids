

/* what are the x and Y values inside the border? */
int al_min_X();
int al_min_Y();

int al_max_X();
int al_max_Y();

/* we draw squares with this one */
void al_square(int x, int y, int size);

/* check the return value on init before drawing */
int al_initialize();
/* just before our program exits, return the terminal to normal */
void al_teardown();

/* if init gave us a good drawing canvas, clear it before drawing */
void al_clear();
/* to commit all drawings to the screen, call al_refresh */
void al_refresh();


/* not required for Version 1 */
void al_status(const char *statstr);
int al_version();

