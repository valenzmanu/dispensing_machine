#include "motor_utils.h"
#include "sensors_utils.h"

#define PRODUCT_CAPACITY_1 3
#define PRODUCT_CAPACITY_2 3

int is_running_1 = 0;
int is_running_2 = 0;

int product_lane = 1;
int product_count = 0;

void setup()
{
  // INIT SERIAL
  Serial.begin(9600);

  // MOTOR 1 CONFIG
  pinMode(MOTOR_1_PUL_PIN, OUTPUT);
  pinMode(MOTOR_1_DIR_PIN, OUTPUT);
  pinMode(MOTOR_1_ENA_PIN, OUTPUT);
  digitalWrite(MOTOR_1_ENA_PIN, HIGH);
  digitalWrite(MOTOR_1_DIR_PIN, LOW);

  // MOTOR 2 CONFIG
  pinMode(MOTOR_2_PUL_PIN, OUTPUT);
  pinMode(MOTOR_2_DIR_PIN, OUTPUT);
  pinMode(MOTOR_2_ENA_PIN, OUTPUT);
  digitalWrite(MOTOR_2_ENA_PIN, HIGH);
  digitalWrite(MOTOR_2_DIR_PIN, LOW);

  // INPUT BUTTON CONFIG
  pinMode(INPUT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(FALL_SENSOR_1_PIN, INPUT_PULLUP);
  pinMode(FALL_SENSOR_2_PIN, INPUT_PULLUP);
}

void loop()
{
  int button_state = digitalRead(INPUT_BUTTON_PIN);
  int fall_sensor_1 = digitalRead(FALL_SENSOR_1_PIN);
  int fall_sensor_2 = digitalRead(FALL_SENSOR_2_PIN);

  Serial.print("button_state: ");
  Serial.print(button_state);
  Serial.print(" fall_sensor_1: ");
  Serial.print(fall_sensor_1);
  Serial.print(" fall_sensor_2: ");
  Serial.print(fall_sensor_2);
  Serial.print(" is_running_1: ");
  Serial.print(is_running_1);
  Serial.print(" is_running_2: ");
  Serial.print(is_running_2);
  Serial.print(" product_count: ");
  Serial.print(product_count);
  Serial.print(" product_lane: ");
  Serial.println(product_lane);

  if (button_state == LOW && !is_running_1 && product_lane == 1)
  {
    is_running_1 = 1;
    move_motor(1);
    product_count++;
  }
  else if (button_state == LOW && !is_running_1 && !is_running_2 && product_lane == 2)
  {
    is_running_2 = 2;
    move_motor(2);
    product_count++;
  }

  if (product_lane == 1 && product_count >= PRODUCT_CAPACITY_1)
  {
    product_lane = 2;
    product_count = 0;
  }
  else if (product_lane == 2 && product_count >= PRODUCT_CAPACITY_2 && !is_running_1)
  {
    product_lane = 0;
    product_count = 0;
  }

  if (fall_sensor_1 == FALL_SENSOR_1_ACTIVE)
  {
    is_running_1 = 0;
    stop_motor(1);
  }
  else if (fall_sensor_2 == FALL_SENSOR_2_ACTIVE)
  {
    is_running_2 = 0;
    stop_motor(2);
  }
}
