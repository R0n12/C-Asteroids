/* Author: Lang Xu */

/*.h file including allocating asteroids, adjusting positions, applying special functions*/

struct Asteroids *allocateAsteroid(struct Asteroids *single, struct Universe *common);

void adjustPos(struct Asteroids *single);

void freeAsteroids(struct Asteroids **single,struct Universe *common);

void fission(struct Asteroids *single);

void split(struct Asteroids *single);

void exhaust(struct Asteroids *single);

void timeout(struct Asteroids *single);

