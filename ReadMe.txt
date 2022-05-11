INFO6017 Artificial Intelligence Project 4
Evan Sinasac - 1081418

Built and run in Visual Studios Community 2019 in Debug in x64.  The BMPLoader does not read the bitmaps correctly when run in Release (It reads them in black and white with no colour).  


CONTROLS		(Some leftover controls from Project 3 and graphics are still accessible)
WASD			- Move Camera
QE			- Raise/Lower Camera
Mouse			- Aim Camera
1-0			- Graphics effects (leftovers from code I built off of)
P			- Reset FBO resolution (Press whenever re-sizing the window)
B			- Show Debug Normals
M			- Make Meshes Wireframe
Space			- Static Cam Position (leftovers from code I built off of, not useful, really should've removed it)
KEYPAD 1/2/3		- Gatherer movement speed multiplier

A.I.
Fuzzy Logic Entities use Fuzzy Logic to determine which of its 5 sensors to use and the appropriate steering vector based on which sensor is most important and detecting a collision.  The fuzzy logic is based on the weight of each sensor, and whether or not the sensor is detecting an obstacle or another vehicle.  Sensors are placed in front of the vehicle, 30° left and right of the forward sensor, and 60° left and right of the forward sensor (5 sensors total).  I initally had the sensors using Fuzzy Logic to determine which obstacle is most important to dodge, but then I re-read the instructions and now they simply return whether or not they are detecting an object.  I left the Fuzzy Logic deciding process in, now it just returns 1 or 0 after though.


Thank you, enjoy!  :)

Video Demo: https://youtu.be/rx_m0dwoxww
 