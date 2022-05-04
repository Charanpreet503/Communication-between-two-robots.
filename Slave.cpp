#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

int m1a = 2;
int m1b = 3;
int m2a = 4;
int m2b = 5;

RF24 radio(7, 8);

const byte address[] = "rover";
const char *data = "";
char val;

void setup()
{
    pinMode(m1a, OUTPUT); // Digital pin 10 set as output Pin
    pinMode(m1b, OUTPUT); // Digital pin 11 set as output Pin
    pinMode(m2a, OUTPUT); // Digital pin 12 set as output Pin
    pinMode(m2b, OUTPUT); // Digital pin 13 set as output Pin
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MAX);
    radio.startListening();
}

void loop()
{
    while (radio.available())
    {
        radio.read(&val, sizeof(val));

        if (val == 'F') // Forward
        {
            forward();
            radio.read(&val, sizeof(val));
        }
        else if (val == 'B') // Backward
        {
            backward();
            radio.read(&val, sizeof(val));
        }

        else if (val == 'L') // Left
        {
            left();
            radio.read(&val, sizeof(val));
        }
        else if (val == 'R') // Right
        {
            right();
            radio.read(&val, sizeof(val));
        }

        else if (val == 'S') // Stop
        {
            stop();
            radio.read(&val, sizeof(val));
        }
    }
}

/**
 * @brief Function to move rover in forward direction
 *
 */
void forward()
{
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}

/**
 * @brief Function to move rover in backward direction
 *
 */
void backward()
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
}

/**
 * @brief Function to move rover in right direction
 *
 */
void right()
{
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}

/**
 * @brief Function to move rover in left direction
 *
 */
void left()
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}

/**
 * @brief Function to moke the robot stop
 *
 */
void stop()
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}
