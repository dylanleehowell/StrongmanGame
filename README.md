# Strongman Game
An implementation of the Strongman Game from the fair/carnival using a force sensor and lights controlled by an Arduino Uno.

![](images 1.png?raw=true)

## Parts list:
* Arduino Uno
* Prototyping board
* Various LEDs
* Various resistors
* Flexiforce Pressure Sensor
* 12V, 500 mA, DC power supply

## Operation:
* Force Sensor
    * Gives a large resistance when no force is applied 
    * Resistance decreases based on force applied.
    * Voltage Divider circuit is utilized to read this sensor
* LEDs
    * The LEDs light up to show how much force was applied
    * Getting the max force causes all LEDs to illuminate and displays an animation
    * When no force is applied, they cycle through an animation
* Arduino Uno
    * Controlls everything
