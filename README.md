# Wing-in-Ground-Effect-Vehicle
## Code for final project in Aerial Vehicle Design class
The program saved on the Arduino during flight worked by receiving height data from the ultrasonic sensor which was used in its PID calculations to set the angle of the servo motor. Then the height and servo angle were saved to the Arduino’s EEPROM. Data was recorded every tenth of a second. A separate Arduino program was used to retrieve the saved data after each flight. A Python program was used to create graphs of the data comparing expected vs actual results.
