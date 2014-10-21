#include "sys_os.h"

volatile unsigned int timers[MAXTASKS] = {0};
volatile unsigned int timers_loop[MAX_LOOPTASKS]={0};
