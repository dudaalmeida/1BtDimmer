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
float i = 0.5;
float T;

void rise();
void fall();
void trn();
void blink();

int main() {
    blue = 1;
    orange = 0;
    btn.rise(&rise);
    btn.fall(&fall);
}

void rise(){
    on=1;
    b.attach(&trn, 1);
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
        if(state == RISE && i == 1.0){  // Alcançou o MAX
            state = MAX;
            printf("STATE: MAX\n");
        }else if(state == FALL && i == 0.0){  // Alcançou o MIN
            state = MIN;
            printf("STATE: MIN\n");
        }else{
            
            if(state == RISE || state == UP){  // Ainda não alcançou i==0
                state = RISE;
                printf("STATE: RISE\n");
                i += 0.05;
            }
            
            if(state == FALL || state == DOWN){  //Ainda não alcançou i==1
                state = FALL;
                printf("STATE: FALL\n");
                i -= 0.05;
            }
        }
        
        if(i >= 1){                          // Já alcançou/passou o MAX
            state = MAX;
            printf("STATE: MAX\n");
            i = 1;
        }
        
        if (i <= 0){                         // á alcançou/passou o MIN
            state = MIN;
            printf("STATE: MIN\n");
            i = 0;
        }
        led = i;
        printf("Intensidade: %f\n", i);
        printf("--------------------------------------------------\n");
        t.attach(&trn, 1);
        b.attach(&blink, 0.2);
    }
}

void blink(){
    
    T = 0.2;
    
    if(state == RISE) blue = !blue;
    if(state == FALL) orange = !orange;
    
    t.attach(&blink,T);
    
}