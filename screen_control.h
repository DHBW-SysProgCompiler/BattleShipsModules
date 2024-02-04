#ifndef SCREENCONTROL_H
#define SCREENCONTROL_H

#include <stdint.h>

void init();
void clear_screen();
void printc(char);
void print(char[], uint32_t);

#endif