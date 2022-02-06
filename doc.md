### What is T2T?

T2T is a shortened name for "Three dimension to Two dimension".
As the name implies, it is an application that converts 3D coordinates into 2D coordinates.

For example, if you want to project a cube on the screen,

1. A coordinate system is fixed on the ground.
Each vertex of the cube is represented with the coordinate.
For example, there is a cube of which the length of the sides is one.
The coordinates of the vertices of the cube can be expressed as follows.
2. Suppose this was taken with a drone in the air.
The cube becomes a two-dimensional image, and each vertex can be represented by two-dimensional coordinates in the image.
3. Display the image on the display using the coordinates.

（the coordinate of each vertex of the cube）

~~~
(0,0,0)
(1,0,0)
(1,1,0)
(0,1,0)
(0,0,1)
(1,0,1)
(1,1,1)
(0,1,1)
~~~

### Tutorial

Run t2t by typing the following command line from the terminal.

~~~
$ t2t
~~~

There is a text file called cube.txt in the example folder.
This command make t2t read it.

- Click the Open button.
- Then, file selection dialog appears.
- Double-click cube.txt in the example folder.

The contents of cube.txt are displayed in the left half of the window.
This is a program that displays a cube.
Each command is described in a later section.

Click the Run button to see the cube in the right window.

![example cube](example_cube.png)

### Overview of t2t coordinate transformation

The model of t2t is an object on the ground and a drone with a camera that shoots it.
In the explanation here, the terms "ground", "drone", and "camera" will be used.
The ground coordinate system G is a fixed orthonormal coordinate system and satisfies the following conditions.

- Z-axis is vertical.
- X-axis and y-axis are horizontal.
- The coordinate system is a right-handed system.

Let O be the origin of the coordinate system G.

The position of the drone is O'.
The position of the drone is determined by the vector t = OO', connecting the origin O of the ground coordinate system G and O'.

Consider the coordinate system D relative to the camera attached to the drone.

- The origin of the coordinate system D is O'.
Since the size of the camera and drone is ignored, O' is the position of the drone as well as the position of the camera.
- The positive direction of the z-axis of D matches the orientation of the camera.
The x-axis points to the right.
The y-axis points upward.
Therefore, the coordinate system D is a left-handed system.
- When the direction of the camera changes, the coordinate system D also changes.

The image taken by the drone is two-dimensional.
This image can be thought of as an image projected onto the plane S (See the figure below).
In the figure, a straight line connects the point P and O' (camera).
The point P' is the intersection of the straight line and the plane S.
(Actually, an image is generated on the image sensor in the camera, but since the image on the plane S is similar to that, the plane S is used instead of the image sensor).
S has two-dimensional coordinates S (the same letter S is used, but you will be able to distinguish them by context).

![screen](screen.jpg)

T2t calculates the coordinates of the point P in the order of coordinate system G, D, and S.
Based on the coordinate system S, t2t displays an image of the object in the right half window.
However, since t2t can only display line segments, it can only display objects such as cubes that connect vertices with line segments.

### Commands

The left half window of t2t is a text editor.
You can enter the t2t program there.
You can also save it to a file and load it from a file by clicking the "Open" and "Save" buttons, respectively.
The "Close" button closes the window and quits t2t.
The "Run" button runs the program and displays the image in the right half window.

A program is a sequence of statements.
The statements consist of commands and arguments.

~~~
LW (expression)
~~~

Sets the thickness of the line segment (the diameter of the pen in cairo's user space).
The default is 2.

~~~
MT (expression, expression, expression)
~~~

Determine the position of the "current point" in the 3D space.
"MT" means "Move To".
The three arguments are the coordinates of that point.

"Expression" is expressed by the sum, difference, product, quotient, unary minus, parentheses, numbers and variables.
The value of the expression is calculated as a floating point (double type of C).

~~~
LT (expression, expression, expression)
~~~

Draw a straight line from the current position to the position of the argument.
"LT" means "Line To".

~~~
FC (expression, expression, expression)
~~~

Set the foreground color.
The arguments are RGB in order and are values ​​from 0 to 1.

~~~
BC (expression, expression, expression)
~~~

Set the background color.
The arguments are RGB in order and are values ​​from 0 to 1.
This command clears all the shapes and fills the entire drawing area with the background color.
Therefore, the background color should be set before other drawings.

~~~
ST (expression, expression, expression)
~~~

Set the vector t.
T is a vector from the origin O of the coordinate system G to the position O' of the drone.

"ST" means "Set T".
The default is (10,10,10).

~~~
UT (expression)
~~~

Raise the drone vertically.
That is, the z coordinate of t increases by the value of the argument.
If the argument is negative, the drone is down.

"UT" means "Up T".

~~~
RT (expression)
~~~

Rotate the drone in the horizontal plane around the intersection of the vertical straight line passing through the origin O of the ground coordinate system
 and the horizontal plane including the drone.
The direction of rotation from the x-axis to the y-axis is positive.
The argument is the angle of rotation, and is measured with degree.
The direction of the drone changes as it rotates.
However, since the camera remains fixed to the drone, the orientation of the camera with respect to the drone does not change.
For example, if the drone is facing the origin O, the drone is facing O even after RT is executed.

"RT" means "Rotate T".

~~~
ZT (expression)
~~~

Bring the drone closer to the origin with the argument as a magnification.
More precisely, the scalar multiplication of the reciprocal of the argument is performed for t.
For example, if the argument is 2, the length of t is halved without changing its direction.
Therefore, the drone approaches the origin O (Zoom In).
When the argument is 1/2, the leength of t is doubled (Zoom Out).
The argument must be positive.
If a negative argument is given, the command is ignored (t is not changed).

"Z T" means "Zoom T in".

~~~
IC
~~~

The camera should be oriented toward the origin of the coordinate system G on the ground.
That is,

- The z-axis of coordinate system D is set toward O.
- The y-axis is on the plane created by the vector in the vertical direction with respect to the ground and the z-axis, and its direction is upward (facing the opposite side of the ground).
- The x-axis points horizontally.

"IC" means "Initialize the direction of the Camera".

~~~
LU (expression)
~~~

Rotate the camera upwards.
If the argument is negative, it will rotate to face down.
The argument is the angle of rotation with degrees.

"LU" means "Look Up".

~~~
LR (expression)
~~~

Rotate the camera to the right.
If the argument is negative, it will rotate to the left.
The argument is the angle of rotation with degrees.

"LR" means "Look Right".

~~~
SD (expression)
~~~

Set the distance d from the camera to the plane S (the screen).
The default is 3.

"SD" means "Set D".

~~~
AD (expression)
~~~

Add the value of the argument to the distance from the camera to the plane S.
This makes the figure on the screen smaller.

"AD" means "Add D".

~~~
DM (expression)
~~~

Enlarge the image on the screen.
Specifically, in the plane coordinates of the plane (screen) S, multiply the x-coordinate and y-coordinate by the argument values.
Default value is 72.

"DM" means "Display Magnification".

~~~
SC
~~~

Output the codes to the standard output.
When it outputs MT or LT, it adds the argument (coordinates of the coordinate system G) and the coordinates converted into two-dimensional coordinates on the plane S.

"SC" means "Show Codes".

~~~
HC
~~~

Stop output of the code to the standard output.

"HC" means "Hide Codes".




# variables

Variables start with an alphabetic character and are followed by alphanumerics and underscores.
The variables are of type double.

~~~
Variable name = expression
~~~

Assignments to variables are statements.

# Expressions

Expressions are represented by arithmetic operations of variables and numbers.
The operations include:

- addition
- subtraction
- multiplication
- division
- unary minus
- brackets

There are also built-in functions.

~~~
SIN (expression)
COS (expression)
~~~

These return the values of trigonometric functions.
The argument expression represents an angle measured with degree.

The result value of the expression is of C double type.
The numbers "1" and "1.0" are both processed as double type 1.0.

