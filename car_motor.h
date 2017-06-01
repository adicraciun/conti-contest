#ifndef _CAR_MOTOR_H_
#define _CAR_MOTOR_H_

#include "car_state.h"
#include <thread>
#include <ctime>

//Leds
#define BACK_LIGHT_1 15

//Motors LEFT
#define PWM_1 27
#define PIN_1_1 28 // Connect to IN 1_1
#define PIN_1_2 29 // Connect to IN 1_2

#define PWM_2 23
#define PIN_2_1 24 // Connect to IN 2_1
#define PIN_2_2 25 // Connect to IN 2_2

//Motors RIGHT those go backwards so we correct this by reversing the wires
#define PWM_3 26
#define PIN_3_1 21 // Connect to IN 3_2
#define PIN_3_2 22 // Connect to IN 3_1

#define PWM_4 3
#define PIN_4_1 4 // Connect to IN 4_2
#define PIN_4_2 5 // Connect to IN 4_1

// Pini line follower
const int PIN_FOLLOW_STANGA = 0;
const int PIN_FOLLOW_MIJLOC = 1;
const int PIN_FOLLOW_DREAPTA = 2;

class CarMotor {
private:
    enum TipCorectie {
        STANGA,
        DREAPTA,
        MIJLOC,
        UNKNOWN 
    };

    enum Directie {
        STOP,
        LEFT,
        RIGHT,
        FORWARD,
        BACKWARD
    }
    
    bool is_turning = 0;
    clock_t turn_time;

    CarState* state;
    std::unique_ptr<std::thread> motor_thread;
    void SyncronizeState();
    void SetDirection (int direction);
    void SetSpeedLeft(int speed);
    void SetSpeedRight(int speed);

    TipCorectie GetCorrectionMode();

    int thread_on = 1;

  public:
    CarMotor(CarState* state);
    ~CarMotor();
    void Start();

};

#endif
