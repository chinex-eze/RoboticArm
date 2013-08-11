#ifndef Robot_Lib_h
#define Robot_Lib_h

#include <avr/io.h> 

#define SHOULDER OCR1A
#define ELBOW OCR1B
#define GRIP OCR1C
#define BASE OCR3A
#define WRIST OCR3B

#define ANG_BASE_MAX 38800
#define ANG_BASE_MID 37300
#define ANG_BASE_MIN 35600

#define ANG_SHOULDER_MAX 37600
#define ANG_SHOULDER_MID 36800
#define ANG_SHOULDER_MIN 36000

#define ANG_ELBOW_MIN 36800
#define ANG_ELBOW_MID 37000
#define ANG_ELBOW_MAX 38400


#define ANG_WRIST_MAX 37000
#define ANG_WRIST_MID 37800
#define ANG_WRIST_MIN 38600


#define ANG_GRIP_MAX 37400
#define ANG_GRIP_MIN 35400

#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3
#define BUTTON5 4

typedef enum {  GRIP_MODE, SHOULDER_MODE, ELBOW_MODE } t_Mode;


void init(void); 
void init_positions(void); 
void basic_delay(int duration); 
void init_buttons(void); 
void process_mode(int mode); 
void change_mode(); 

#endif
