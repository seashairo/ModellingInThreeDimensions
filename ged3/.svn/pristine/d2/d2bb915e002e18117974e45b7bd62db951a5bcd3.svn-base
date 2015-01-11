---------------------------------------------------------------------------
                CSC3049 - Aspects of Game Engine Development
	  		 The Team That Does Stuff
Nathan Sullivan - Timothy O'Neill - Huy Vu LeChris Wilson - Stewart Reaney
---------------------------------------------------------------------------

Within this demo there are several sub-demos, each showing a different part
of what we worked on during this project. Due to the wide nature of the 
project there are a rather large number of controls, and little explanation
within the application itself. 
Listed below are what I believe to be the complete list of controls within 
this application, both useful and non-useful. It should be noted that some
of these controls may not still be functional after the time of writing.

---------------------------------------------------------------------------
			----- Scene Changes -----
	 The following keys change the scene to another sub-demo

F1 - The main scene. A fish tank with water, terrain, fish, skybox, etc.
F2 - An AI display. Set up to show off most ofthe main AI behaviours.
F3 - A further AI display. Set up to show off the "avoid" behaviour.
F4 - Yet another AI display. Set up to show off formational movement.
F5 - Sound testing.
F6 - Parralax Occlusion Mapping.

---------------------------------------------------------------------------
			----- Camera Controls -----

			    ----- Position -----
W - Move forward along the Z axis 		                       (+Z)
S - Move backwards along the Z axis 		                       (-Z)
D - Move right along the X axis 				       (+X)
A - Move left along the X axis 					       (-X)
Q - Move up along the Y axis					       (+Y)
E - Move down along the Y axis					       (-Y)

			    ----- Rotation -----
Left Arrow - Rotate CCW around the Y axis			       (-Y)
Right Arrow - Rotate CW around the Y axis			       (+Y)
Down Arrow - Rotate CCW around the X axis			       (-X)
Up Arrow - Rotate CW around the X axis				       (+X)
, - Rotate CW around the Z axis					       (+Z)
. - Rotate CCW around the Z axis				       (-Z)

			      ----- Other -----
Z - Toggle relative movement
By default this option is TRUE. While true, when the camera's movement
controls are used, the camera will move relative to its current rotation.
That is to say, if you press W, you will always move forwards, the 
direction in which the camera is currently facing.
If this option is FALSE, then when W is pressed, the camera will simply 
move in a positive direction along the Z axis, which may or may not be the 
same direction the camera is facing.

X - Toggle relative rotation
By default this option is FALSE. While false, the camera will move in a 
predictable way. If you press the Left Arrow, you will look left. When this
option is TRUE, weird things happen and I'm not sure exactly why. But its
here if you want to try it out.

P - Output current camera position to console

---------------------------------------------------------------------------

			  ----- Entity Controls -----

			 ----- Keyboard Movement -----
     Controlled entities will move relative to their current rotation.
U - Move selected entit[y/ies] forward along the Z axis 	       (+Z)
J - Move selected entit[y/ies] backwards along the Z axis	       (-Z)
H - Rotate selected entit[y/ies] CCW around the Y axis 	       	       (+Y)
K - Rotate selected entit[y/ies] CW around the Y axis	       	       (-Y)
Y - Rotate selected entit[y/ies] CW around the X axis 	       	       (+X)
I - Rotate selected entit[y/ies] CCW around the X axis	       	       (-X)

		      ----- Mouse Movement & Selection -----
Left Click - Select an entity in the world. Any currently selected entities
will be unselected.
Not all entities will be able to be selected like this. For example, the 
glass in scene F1 can not be moved, but if you can click on a fish, you can
assume control.

Shift + Left Click - Select multiple entities in the world. By holding
shift when you click, other entities will not be unselected.

Right Click - Move all currently selected entities to the point where the
mouse cursor intersects with the imaginary plane at Y=1

F - Cycles through available entity formations
None -> Line -> Column -> FlyingV -> Wedge -> None

			     ----- Control Groups -----

Ctrl + 1 - Put the currently selected entities into group 1
Ctrl + 2 - Put the currently selected entities into group 2
Ctrl + 3 - Put the currently selected entities into group 3

1 - Unselect any currently selected entities and select group 1
2 - Unselect any currently selected entities and select group 2
3 - Unselect any currently selected entities and select group 3

Shift + 1 - Add group 1 to the currently selected entities
Shift + 2 - Add group 2 to the currently selected entities
Shift + 3 - Add group 3 to the currently selected entities

---------------------------------------------------------------------------

				 ----- Other -----

Space - Toggles wireframe mode

N - Sets Trigger1
M - Sets Trigger2

---------------------------------------------------------------------------

				----- Notes -----

In demo 5 (the sound one) the three sound are quite quiet. If you cannot
hear them there are several solutions. You can turn up your volume, you can
move closer to the entity you are playing the sound from (using the
controls above), or you can wallow in despair because it's broken.

---------------------------------------------------------------------------