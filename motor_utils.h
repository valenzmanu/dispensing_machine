#define MOTOR_1_PUL_PIN 3
#define MOTOR_1_DIR_PIN 6
#define MOTOR_1_ENA_PIN 5

#define MOTOR_2_PUL_PIN 9
#define MOTOR_2_DIR_PIN 10
#define MOTOR_2_ENA_PIN 11

void move_motor(int motor_number)
{
    if (motor_number == 1)
    {
        analogWrite(MOTOR_1_PUL_PIN, 127);
    }
    else if (motor_number == 2)
    {
        analogWrite(MOTOR_2_PUL_PIN, 127);
    }
}

void stop_motor(int motor_number)
{
    if (motor_number == 1)
    {
        digitalWrite(MOTOR_1_PUL_PIN, LOW);
    }
    else if (motor_number == 2)
    {
        digitalWrite(MOTOR_2_PUL_PIN, LOW);
    }
}
