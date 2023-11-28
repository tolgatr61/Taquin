#ifndef TIMER_H
#define TIMER_H

#include <time.h>

// Structure pour gérer le chronométrage du jeu.
typedef struct {
    time_t start_time;
    time_t end_time;
} Timer;

void startTimer(Timer *timer);
void stopTimer(Timer *timer);
double getElapsedTime(const Timer *timer);

#endif // TIMER_H