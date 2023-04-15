Game Mechanics

Enemies
Flanker.h


Weapons:
Basic cannons on port and starboard of ship
Higher spread, more damaging cannon at stern of ship

Collectible items

Movement and transformations
Physical movement: Airship and enemies
Parametric movement: Crew movement between workstations, enemy orbit point (point moves parametrically, enemy chases it physically).


Collision Detection:
Bullets and enemies
Bullets and airship segments
CollisionBox and Collidable classes allow collision behaviours to be defined
as easily as adding a case for the desired type to an overriden HandleCollisionEvent() function. 


UI: 
Gui, GuiElement, GuiState. Reacts to state ofand allows for control of airship and crew


Advanced method:
Enemy HomeInOnPoint(glm::vec3 target_position, glm::vec3 target_velocity, double delta_time) Function
This function takes in a desired destination point and final velocity, and modifies the enemy acceleration to achieve them. It does this by finding the "minimum braking distance" for the x and y components, which determines whether to accelerate or deaccelerate. Can be used to stop on points, pursue targets, and stop on points with relative positions and velocities to targets (i.e. "go to the point +3 in the x dir from the target. Arrive there with a speed equal to target speed"). 

Bonus:
Airship are assigned to workstations to indirectly control airship functionality like guns. Work speed (fire rate) and crew movement speed depend on crew health. Crew take damage with the ship.