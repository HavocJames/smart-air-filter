
# INTRODUCTION
The presence of dust in homes, offices, and other human environments is unavoidable. In fact, according to the Environmental Protection Agency, indoor air can be 2 to 5 times more polluted than outdoor air. This airborne pollution contributes to minor annoyances such as itchy eyes, sneezing, and headaches to human beings. Worst still, it can be a significant contributing factor to severe allergies & life-threatening asthma. To solve this problem, a working air purification system will address this issue. we want to leverage the advantages of sensors and make the air purifier smarter. Instead of the conventional way that turning on the air purifier the whole day, but with the use of "microcontroller” and "sensor” to operate only if the presence of dust reaches a certain level of awareness, this could save a lot of electricity and also keep the room, apartment, not only clean the air pollutants in the room but also monitors the quality of air been purified at the particular instant of time. Air Pollution is an increasing problem in the 21st Century. It is one of the main causes of climate change and it can cause a lot more problems in the future. 
Hence, we decided to design an air purifier that can be installed in any room of your house, in the ICU of a Hospital, or in college for that matter. By using some basic sensors with our air purifier, the power consumption becomes less hence it is a very important element.
# BLOCK DIAGRAM
![BLOCK DIAGRAM](https://github.com/HavocJames/smart-air-filter/assets/124689464/ed26c013-0de2-4423-9c63-2f821fcadd4d)
 * Power Supply
Provides electrical power to all components in the system, ensuring they have the required voltage and current to operate effectively. Arduino Uno (ATMEGA328P): Acts as the brain of the system, responsible for controlling and coordinating the various components. It processes data from the sensors, executes instructions, and controls the display, fan, and other actuators.
 * Gas Sensor MQ-135
Detects gases such as ammonia, nitrogen oxides, and carbon dioxide, which are commonly found in air pollution. It measures the concentration of these gases and provides data to the Arduino for analysis.
 * Gas Sensor MQ-3
Specifically designed to detect alcohol vapor in the air. It is commonly used in breathalyzer devices and can be incorporated into the smart air filter system to identify alcohol-related air pollution.
 * Gas Sensor MQ-9
Detects flammable gases like methane, propane, and butane. It provides data on the presence and concentration of these gases, allowing the system to respond accordingly to ensure safety.
 * Optical Dust Sensor (GP2Y1010AUOF)
Measures the concentration of suspended particles in the air. It utilizes a light-emitting diode (LED) and a photodetector to calculate the density of dust particles, providing the system with data on air quality
 * Inlet Fan
Draws air from the surrounding environment into the filter system. It creates an airflow that carries pollutants toward the filters for purification.
 * Relay
Acts as a switch controlled by the Arduino to regulate the power supply to the fan and other components. It allows the Arduino to turn on or off the fan based on the air quality readings or user commands.
 * DC Module
A power regulation module that ensures a stable and consistent power supply for the system. It converts the input voltage from the power supply to the required voltage levels for various components.
 * ESP-8266
An IoT module that provides Wi-Fi connectivity to the system. It allows the smart air filter to connect to the internet, enabling remote control, data transmission, and integration with other smart devices or cloud platforms.
 * LCD Display
Presents information to the user in a visual format. It can show real-time air quality readings, filter status, mode selection options, and other relevant information. The Arduino sends data
to the display for it to be shown to the user.
 * Internet (IoT)
Represents the connectivity to the internet facilitated by the ESP-8266 module. It allows the smart air filter to communicate with remote servers or applications, providing access to real-time data, remote control, and integration with other smart systems
# CIRCUIT DIAGRAM
![CIRCUIT DIAGRAM](https://github.com/HavocJames/smart-air-filter/assets/124689464/bc7bf3dd-3a34-41e1-ad09-c0822aa683d7)
# COMPONENTS LIST
* MQ-9
* MQ-135
* MQ-138
* GP2Y1010AUOF
 12c adapter module
* 16x2 LCD module
* Arduino UNO
* Power supply
* Esp8266
* Relay module
* Capacitor 220µF
* Resistor 150Ω
# WORKING ON THE CIRCUIT
The system contains three fans with three types of filters suited for three different types of pollutants.
Arduino and sensors are placed in different compartments in the system. The array of sensors can sense various physical, biological, and chemical pollutants. Sensors are constantly used for checking pollutants. When sensed one or more pollutants, the sensor gives the signal to Arduino.
The received signal is analyzed based on the programming to produce the data on what types of pollutants are present. The Arduino sends a signal to the relay to turn on the fan/fans of the type of filter required. Once the sensors sense there are no pollutants present, Arduino turns off the relay to stop the filtration.
# OUTPUT
The system not only identifies and filters pollutants based on their chemical, physical, and biological components but also provides advanced features. It continuously monitors the air, analyzes pollutants, and activates the appropriate filters for removal.
This comprehensive approach ensures effective pollution detection and filtration, leading to improved air quality and a healthier environment. Additionally, the system displays the analyzed data on an LCD display, providing real-time information about the air composition. 
Furthermore, the data is uploaded to a cloud platform such as ThingSpeak, enabling users from anywhere in the world to access and monitor the air quality data remotely. This feature enhances user convenience and facilitates better understanding and management of air pollution levels.
![PRODUCT CLOSED](https://github.com/HavocJames/smart-air-filter/assets/124689464/bb43fada-b797-4b9a-8612-4eccfe4fcccb)
![OPEN FILTER](https://github.com/HavocJames/smart-air-filter/assets/124689464/453250fd-27c6-432a-a379-da86843574d9)

https://github.com/HavocJames/smart-air-filter/assets/124689464/af3bdf20-267e-4e7f-8fb5-a5fa1b79639e

# BIBLIOGRAPHY
* https://lastminuteengineers.com/one-channel-relay-module-arduinotutorial/
* https://cgrant.medium.com/using-the-esp8266-wifi-module-with-arduinouno-publishing-to-thingspeak-99fc77122e82
* https://www.alldatasheet.com/
* https://www.arduino.cc/
* https://en.m.wikipedia.org/wiki/Arduino_Uno
* https://thingspeak.com/
* https://www.mathworks.com/products/thingspeak.html
* https://projecthub.arduino.cc/abid_hossain/d527c8ec-b750-4c14-a531-b26104333084
* https://www.hackster.io/mircemk/diy-air-quality-monitor-with-sharpgp2y1010au0f-sensor-7b0262
