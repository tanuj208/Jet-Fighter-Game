Jet Fighter Game
=========================

# Introduction:
In this game, we are controlling a plane and our aim is to shoot enemy islands situated at some places (directed by the arrow) and meanwhile gaining bonus score by shooting down parachutes or by going through smoke rings. We must also escape from the attack of enemy islands and make sure our life and fuel doesn't gets over

# Controls:
- W and S to move plane forward and backward respectively
- A and D to tilt (roll) the plane
- Q and E to rotate (yaw) the plane
- Up and Down arrow keys to pitch the plane
- Left mouse click to fire missiles
- Right mouse click or B button to drop bombs
- V to change camera
- T, R and Y to perform different stunts
- In helicopter view, hover around to see the plane from different directions and scroll to zoom in and out

# Instructions to run the game:

- `mkdir build`
- `cd build`
- `cmake ../`
- `make all -j 4`

# Features in Details:
❖ Plane : ​ Black-grey colored plane. Can fire missiles and drop
bombs. Moves with a speed according to pressing keys. Have an
upper limit to speed. Air drag acts on the plane. Plane can move
up to a certain extent.
❖ Missiles : ​ Go in the direction plane is facing when it fired themissile and go in the straight line.
❖ Bombs :​ Go in vertically downward direction (gravity acts on it).
Also has the speed in horizontal direction same as the speed of
plane.
❖ Volcano :​ Destroys the plane if plane comes closer to it. Cannot
be destroyed.
❖ Mountains :​ Has no effect in game. Only for view.
❖ Water :​ If plane enters water, it is destroyed.
❖ Parachutes :​ Comes at random time. Can be destroyed using
missiles and bombs. If destroyed, gives bonus points to player.
❖ Smoke rings :​ Comes at random time. If plane goes through
this, then player gets bonus points.
❖ Checkpoint :​ Player needs to complete 5 checkpoints in order to
win the game. Each checkpoint has an enemy cannon. Complete
the checkpoint gives some score to the player.
❖ Cannon :​ Present at each checkpoint. Active only for the current
checkpoint. Can be destroyed by missiles and bombs. Fires
missiles towards the player’s plane. Reduces some hp of the
plane if hits.
❖ Fuel :​ Plane has limited fuel capacity. Reduces each time plane
moves forward or backward but remains same if plane is still in
air.
❖ HP :​ Plane has limited hit points. Reduces if plane comes in
contact with water or comes close to volcano or gets hit by
cannon missile.
❖ Dashboard :​ Shows plane status. Bottom left shows hp (green)
and fuel (red). Bottom middle shows score. Bottom right shows
compass (Red pointer for direction plane is facing and vertically
upwards is north direction). Top right shows altimeter and top left
shows speedometer.❖ Powerups :​ Red powerup for filling the fuel tank of plane and
green one to increase the plane’s hp.
❖ Camera Views :​ Have 5 camera views ->
➢ Follow Cam : ​ Camera follows the plane.
➢ First-person view :​ View the pilot of the plane sees.
➢ Top view :​ Viewing the plane from the top.
➢ Tower view :​ Viewing the plane from a tower (from an
angle).
➢ Helicopter View : ​ On hovering the mouse, plane can be
seen with different angles. On scrolling, zoom-in and out
can be performed.
❖ Stunts :
➢ Barrel roll :​ Plane rolls (one complete revolution) while
moving.
➢ Looping-the-loop :​ Plane pitches (one complete
revolution) while moving.
➢ Roll in spiral :​ Plane rolls (one complete revolution) as
well as moves in a spiral trajectory.
❖ Sound effects :​ Have some sound effects when plane is
moving, when launches missile or bomb and when missile/bomb
hits a parachute/checkpoint.
