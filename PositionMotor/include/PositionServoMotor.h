#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "Comms.h"
#include "ServoDataMessage.h"

using namespace std;

class PositionServoMotor : public Comms
{
public:
    PositionServoMotor(void) ;
    ~PositionServoMotor(void);
    static PositionServoMotor & GetInstance (void);
    int32_t PositionControl(void);
    int32_t PositionControlAngle(void);
    int32_t Init(void);

private:

    /**
     * Control registers 
     */
    // Unit of servo pulse offset: 0.1ms
    static const int32_t OFFSET_MS    = 3;               
    // Pulse duration for minimum angle of servo
    static const int32_t SERVO_MIN_MS = 5 + OFFSET_MS;     
    // Pulse duration for maximum angle of servo
    static const int32_t SERVO_MAX_MS = 25 + OFFSET_MS;    

    /**
     * Pins I/O
     * GPIO number connected to servo 
     */
    static const int32_t SERVO_PIN    = 1;   

    /**
     * local variable
     */
     bool m_debug ; 


    int32_t map(uint32_t value,uint32_t fromLow,uint32_t fromHigh,uint32_t toLow,uint32_t toHigh);

    int32_t ReceivedData(int32_t sockdf , char *pDataTransmit , int32_t dataSize);


public:
    //initialization function for servo PMW pin
    int32_t Init(int32_t pin);

    //Specific a certain rotation angle (0-180) for the servo
    void RotateAtAngel(int pin, int angle);
    
     //specific the unit for pulse(5-25ms) with specific duration output 
     // by servo pin: 0.1ms
    void PulseMS(int pin, int ms);

};