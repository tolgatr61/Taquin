#include "timer.h"
#include <stdio.h>

void startTimer(Timer *timer) {
    if (timer != NULL) {
        timer->start_time = time(NULL);
        timer->end_time = 0; // On s'assure que end_time est réinitialisé
    }
}

double getElapsedTime(const Timer *timer) {
    if (timer != NULL && timer->start_time != 0) {
        time_t current_time = time(NULL);
        return difftime(current_time, timer->start_time);
    }
    return 0.0;
}

void stopTimer(Timer *timer) {
    if (timer == NULL) {
        printf("Timer non initialise.\n");
        return;
    }
    timer->end_time = time(NULL);  // Enregistre l'heure actuelle
}