RoboticArm
==========

  							
								ROBOTIC ARM PROJECT DESCRIPTION		
THE HARDWARE - ROBOTIC ARM 
The robotic arm is made up of five servo motors - the shoulder, the elbow, the wrist, the gripper and the 
base. The whole set up is controlled by an AVR ATmega128 microcontroller in an Olimex AVR-MT128 development 
board. The gripper is a HiTEC HS422 servo while the base, the shoulder, the elbow and wrist are controlled 
with a HiTEC HS-5745 servo. 

The servos are couple such that they form an "arm" figure. 

USAGE: 
When the robot is started each of the arms go to a default position. These positions are termed mid for 
each of the motors. 

The robot has three modes: the grip, shoulder and elbow modes. The default mode is the grip mode. When 
active, each of the mode is displayed on the LCD to enable the user know exactly what mode, it is at 
all times. The middle button is used to change the modes. Internally, the AVR-MT128 keeps tract of the 
modes in an enum (enumerator) data structure. Using a switch case statement, the AVR ATmega128 
microcontroller is able to determine what codes to run for each mode. Internally, each of the buttons are 
known as BUTTON1 - BUTTON5. 

THE GRIP MODE: 
When in the grip mode, the LED is off. The left button is used to open the grip while the right button is 
used to close it. The grip does not close completely so that the serevo is not damaged. It does not open 
completely as well for the same reason. The LCD displays "GRIP MODE" at this time. 

THE SHOULDER MODE: 
In this mode the LED is on. The right and left buttons are used to rotate base of the robot right and left 
respectively. The top button is used to move the shoulder forward and backward respectively. 

THE ELBOW MODE: 
The LED is on as well. The right and left bottons are used to control the base just like in the previous 
mode. The top and bottom buttons are used to lift the arm up and down respectively. 

In each of these modes, except in the gripper mode, the wrist of the robot is controlled using a simpler 
method of adding or subtracting it's angle depending on wether the arm is going up or down. This is done 
in order to keep the wrist and the load it is carrying on a horizontal level at all times. The user does 
not have control of the gripper. 

Also, the servos are programmed to move really slowly. This is because the use case simulates a robot used 
for handling explosive chemicals for testing purposes. Each of the servos are not able to exceed a particular 
limit. Internally, the limits are termed MAX and MIN e.g. ANG_WRIST_MAX. 
