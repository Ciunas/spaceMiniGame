# spaceMiniGame
Programmed using the freescale FRDMKL26Z microcontroller.
C program to implement a game using the PIT interrupt to control screen refresh, and control of the objects.
The user can move  a ship using the characters'w' 'a' 'd' and 's'. These commands move the ship upwards, down,
left and right. A timer is used to signal the end of the game. The program has three main functions that run one after
another. The PIT interrupt is used to increment a variable balance, this controls when each function is used and how many
times the function will be called.
FireGuns this displays the guns and shows the user which guns are going to be fired. The location of the guns is generated
randomly the first time the fireguns() function is called. The user must avoid these or else the death count will increment
by one.  In the second function displayShip() a ship is displayed on the screen. The user
moves this out of the way of the  turrets using the control buttons. In the third function the values of the random guns
and the value of the ship parts are compared. If one of them matches then the death count is incremented.
The program resets balance to 0 after it has run the hitCheck() function.
The game runs for one minute. After this time has run out the users high scores are displayed. The top three
scores are displayed. And the user is asked to press any button if they want to play again.
