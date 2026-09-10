#ifndef SYSTEMCHECK_H
#define SYSTEMCHECK_H
    
    #include <time.h>
    #include <stdbool.h>

    /* true si el sistema es inferior a un 486 (ej. 386, 286...) */
    extern bool g_isLowEndSystem;

    int systemCheck(void);

#endif