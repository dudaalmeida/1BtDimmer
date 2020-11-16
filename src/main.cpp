#include "mbed.h"

DigitalOut orange (p5);
DigitalOut blue (p6);
InterruptIn btn (p7);
PwmOut led (p9);
Timeout t,b;
int c=0;

enum states{DOWN, UP, FALL, MIN, RISE, MAX};
int state = UP;
int on;
float i;
float T;

int main() {
    blue = 1;
    orange = 0;
    i = 0.5;
    btn.rise(&rise);
    btn.fall(&fall);
    led = i;
}

void rise();
void fall();
void trn();
void blink();

void rise(){
    on=1;
    tempo();
    b.attach(&trn, 1)
}

void fall(){
    printf("Button release\n");
    on = 0;
    if(state == UP || state == MAX || (state == FALL && i > 0.0)){
        orange = 1;
        blue = 0;
        state = DOWN;
        printf("STATE: DOWN\n");
    }else if(state == DOWN || state == MIN || (state == RISE && i < 1.0)){
        orange = 0;
        blue = 1;
        state = UP;
        printf("STATE: UP\n");
    }
}

void trn(){
    if(on){
        if(state == RISE && i == 1.0){
            state = MAX;
            printf("STATE: MAX\n");
        }else if(state == FALL && i = 0.0){
            state = MIN;
            printf("STATE: MIN\n");
        }else{
            
            if(state == RISE || state == UP){
                state = RISE;
                
            }
            
            if(state == FALL || state == DOWN){
                state = FALL;
                
            }
            
            
            
        }
    }
}