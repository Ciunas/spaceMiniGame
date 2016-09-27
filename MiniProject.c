
/***********************************************************************************************
 *	Name Ciunas Low Bennett.
 *	Version 9.0
 *	Mini_Project
 *
 **********************************************************************************************/

#include "fsl_device_registers.h"
#include "board.h"
#include "fsl_debug_console.h"
//#include "gpio.h"
#include "pit_kl26z.h"

//Functions
char char_received();
void fireGuns();
void displayShip();
void initialiseArray();
void hitCheck();

//Variables
unsigned int highScre[3] = {25, 25, 25};
char topGuns[28];
char sideGuns[] = "*";
char sideGunsFire[] = "={";
volatile unsigned long rand_no_X = 0;
volatile unsigned long rand_no_Y1 = 0, rand_no_Y2 = 0, rand_no_Y3 = 0;
char flag = 1;
char flag01 = 0;
char sec = 0 , min = 0,  milsec = 0;
int balance = 0;
int seedTime = 0;
int x_axis = 30, y_axis = 12;
int screenHeight = 21;
int deaths = 0;
char start;
char temp;

int main(void)
{
	hardware_init();														//Initialize the FRDM-KL26Z Board.
	PRINTF("\033[2J");														//Clear screen.
	PRINTF("\033[6;0H"); 													//set cursor to 6,0.
	//Print following to terminal.
	PRINTF("\e[0;31m***************************************************************\n\r");
	PRINTF("***************************************************************\e[1;37m\n\r\n\r");
	PRINTF("\e[1;36mSpace attack game.\r\n\r\n");
	PRINTF("Avoid the gun turrets and see how long you can survive.\r\n\r\n");
	PRINTF("Press any button to start.\e[1;37m\r\n\r\n");
	PRINTF("\e[0;31m***************************************************************\n\r");
	PRINTF("***************************************************************\e[1;37m\n\r\n\r");

	start = GETCHAR();													//Use as a blocking command to display game details.
	PIT_Configure_interrupt_mode(.05); 									//Configure PIT.

	//Main loop.
	while(1){															//Flag is set when ever the PIT interrupt is triggered.
		if(flag == 1){													//If flag = 1 run the function fireGuns().
			fireGuns();
		}
		else if(flag == 2){												//If flag = 2 run the function displayShip().
			displayShip();
		}
		else if(flag == 3){												//If flag = 3 run the function hitCheck().
			hitCheck();
		}
	}
}

//Function to check if ship has been hit then calculate score.
void hitCheck(){
	flag = 0;															//Reset flag to 0.

	//Checks that the top turret did not hit any of the 9 top pieces of the ship.
	for(int i=0; i<=8; i++){
		if(((x_axis/3) - i) == rand_no_X){									//x_rand is where the turret is placed.
			deaths++;													//If ship hit increment the  death count.
		}
	}
	//Checks if the side turrets hit any of the 3 side pieces of the ship.
	for(int i=0; i<=2; i++){
		if(rand_no_Y1 == (y_axis + i) || rand_no_Y2 == (y_axis + i) || rand_no_Y3 == (y_axis + i)){
			deaths++;													//If ship hit increment the  death count.
		}
	}
}

//Function to generate random loaded gun turrets and display them along with unloaded gun turrets to the terminal.
void fireGuns(){
	flag = 0;															//Reset flag to 0.

	switch(flag01){
	case 0:
		initialiseArray();												//Initialize all elements in array to '*'.
		srand(seedTime);												//Seed the random number with seedtime. Seedtime is incremented any time the PIT interrupt happens.
		rand_no_X = rand()%28;											//Modulo with 28 to give a number between 0 and 27.
		topGuns[rand_no_X] = '\\';										//Use random number to input the loaded turret into topGuns[].
		topGuns[rand_no_X+1] = '/';
		break;
	case 1 ... 19:														//Cases 1 to 19 don't change any values.
	break;
	default:															//Default case.
		initialiseArray();												//Initialize all elements in array to '*'.
	}

	PRINTF("\033[0;0H"); 												//set cursor to 0,0.
	PRINTF("\033[2J");													//Clear screen.
	PRINTF("%02d:%02d Deaths:%d\r\n   ", sec, milsec, deaths);			//Print elapsed time and the amount of deaths.
	for(int i = 0; i<28; i++){
		if(i == rand_no_X || i == rand_no_X + 1)
			PRINTF("\e[0;31m %c\e[1;37m",topGuns[i]);					//Print the loaded top guns changing the color to red.
		else
			PRINTF(" %c",topGuns[i]);									//Print the unloaded top guns.
	}

	switch(flag01++){
	case 0:																//Create  random number for turrets only on case one.
		srand(seedTime);												//Seed the random number  with the PIT interrupt.
		rand_no_Y1 = rand()%21;											//Modulo with 21 to give a number between 0 and 20.
		rand_no_Y2 = rand()%21;
		rand_no_Y3 = rand()%21;

		//Print the sideGuns
		for(int j=0; j<screenHeight; j++){
			//If j is equal to any of the random numbers. The loaded turret string is displayed.
			if(j == rand_no_Y1 || j == rand_no_Y2 || j == rand_no_Y3){
				PRINTF("\e[0;31m\r\n%s\e[1;37m",sideGunsFire);
			}
			else{
				PRINTF("\r\n%s",sideGuns);
			}
		}
		break;


	case 1 ... 19:														//Use the same random number for turrets created in case one.
	//Print the sideGuns
	for(int j=0; j<screenHeight; j++){
		//If j is equal to any of the random numbers. The loaded turret string is displayed.
		if(j == rand_no_Y1 || j == rand_no_Y2 || j == rand_no_Y3){
			PRINTF("\e[0;31m\r\n%s\e[1;37m",sideGunsFire);
		}
		//Else the unloaded turret is displayed.
		else{
			PRINTF("\r\n%s",sideGuns);
		}
	}
	break;

	default: 															//Default state
		flag01 = 0;
	}

	if(flag01 >= 19){													//Case flag is reset to zero once is reaches 19.
		flag01 = 0;

	}


}

//Function in initialize topGuns array.
void initialiseArray(){
	for(int i=0; i<=27; i++){											//Load values into topGuns array.
		topGuns[i] = '*';												//Put the character '*' in all the elements of the array.
	}
}

//Function to move and display ship to Terminal.
void displayShip(){
	flag=0;																//Clear the flag.
	PRINTF("\033[0;0H"); 												//Set cursor to 0,0.
	PRINTF("\033[2J");													//Clear screen.
	PRINTF("%02d:%02d Deaths:%d\r\n", sec, milsec, deaths);				//Print time and amount of deaths.
	if(char_received()){												//If character received.
		temp = GETCHAR();												//Read character and put value in temp.

		/*
		 * Read in what command the user enters. W = move ship upwards, S = move ship downwards
		 * D = move ship right, and A =  move ship left.
		 */

		if(temp == 'w'){
			//Subtract one from the y_axis. This move the ship upwards. When ship get's to the top limit of the screen don't move up anymore.
			if(y_axis == 0){
			}
			else{
				y_axis--;
			}
		}
		//Add one to the y_axis. This move the ship downwards. When ship get's to the bottom limit of the screen don't move down anymore.
		else if(temp == 's'){
			if(y_axis == 18){
			}
			else{
				y_axis++;
			}
		}
		//Subtract three from the x_axis. This move the ship to the left. When ship get's to the left limit of the screen don't move left anymore.
		else if(temp == 'a'){
			if(x_axis == 3){
			}
			else{
				x_axis-=3;
			}
		}
		//Add three to the x_axis. This move the ship to the right. When ship get's to the right limit of the screen don't move right anymore.
		else if(temp == 'd'){
			if(x_axis >= 72){
			}
			else{
				x_axis+=3;
			}
		}
	}
	for(int j=0; j<=y_axis; j++){
		PRINTF("\r\n");														//Move courser down the y_axis to where the ship is located.
	}

	/*
	 * Print the Ship.
	 * First the blank space is printed to the top left character of the ship.
	 * x_axis is the value that is used for the placement of the ship. This number needed to be a multiple of three,
	 * because the ship has three levels. By dividing this number by three we have the point of each left hand character
	 * on each level. 1/3 of x_axis gives us the top layer. 2/3 of a_axis gives us the middle layer and 3/3 gives us the bottom layer.
	 * The display color is changed to make it easier to see the ship.
	 */
	for(int i=1; i <= x_axis; i++){											//Loop until i = x_axis.
		PRINTF("  ");
		if(i == x_axis / 3){
			PRINTF("\e[0;35m***   ***\n\r");								//Print the top layer of the ship.
		}
		else if(i == ((x_axis / 3)*2)){
			PRINTF("   ***\n\r");											//Print the middle layer of the ship.
		}
		else if(i == x_axis){
			PRINTF("***   ***\e[1;37m\n\r");								//Print the bottom layer of the ship.
		}
	}
}

//Function to display your final score.
void finalDisplay(){
	PRINTF("\033[0;0H"); 													//Set cursor to 0,0.
	PRINTF("\033[2J");														//Clear screen.
	PRINTF("\n\n\nCongratulations you finished the game\n\r\n\r");			//Display to terminal.

	if(deaths < highScre[0]){
		//Update high scores.
		highScre[2] = highScre[1];
		highScre[1] = highScre[0];
		highScre[0] = deaths;
		//Display to terminal if new highest score.
		PRINTF("New High Score you died the least amount. %d lives lost.\n\r\n\r",highScre[0]);
		PRINTF("\e[0;31m***************************************************************\e[1;37m\n\r\n\r");
	}
	else if(deaths < highScre[1]){
		//Update high scores.
		highScre[2] = highScre[1];
		highScre[1] = deaths;
		//Display to terminal if second highest score.
		PRINTF("New high Score second place %d lives lost.\n\r\n\r",highScre[1]);
		PRINTF("\e[0;31m***************************************************************\e[1;37m\n\r\n\r");
	}
	else if (deaths < highScre[2]){
		//Update high scores.
		highScre[2] = deaths;
		//Display to terminal if third highest score.
		PRINTF("New high Score third place % lives lost.\n\r\n\r",highScre[3]);
		PRINTF("\e[0;31m***************************************************************\e[1;37m\n\r\n\r");
	}
	else{
		//Display to terminal if no new high score.
		PRINTF("Bad luck you did not get a new high Score.\n\r\n\r");
		PRINTF("\e[0;31m***************************************************************\e[1;37m\n\r\n\r");
	}

	//Print the game top scores.
	PRINTF("All Time High Scores.\n\r\n\r");
	PRINTF("\e[1;32m1st:    %d lives lost.\n\r",highScre[0]);
	PRINTF("2nd:    %d lives lost.\n\r",highScre[1]);
	PRINTF("3rd:    %d lives lost.\e[1;37m\n\r\n\r",highScre[2]);
	PRINTF("\e[0;31m***************************************************************\e[1;37m\n\r");
	PRINTF("Press any button to restart the game\n\r\n\r");

	/*
	Makes the game display the leader board until the player presses any button to restart the game.
	 */
	while(1){
		if(char_received()){												//Waits for a character to be entered.
			deaths = 0;														//Reset deaths to 0 when game restarted.
			return;
		}
	}
}


//Interrupt Service Routine for PIT
void PIT_IRQHandler()
{
	seedTime++;																//Increment seedTime. Used with rand to create a random number for the gun turret location
	PIT_TFLG0 = 0x01ul;														//Clear flag.
	milsec += 5;															//Pre-increment milsec by 5.
	if(milsec == 100){														//If milsec reaches 100 reset to 0.
		milsec = 0;
		if(++sec == 60){													//Update seconds and reset if equal to 60.
			finalDisplay();													//Game is finished display the leader board.
			sec = 0;
		}
	}
	/*
	Increment balance, this is used to change between the 3 main functions. 1st display the turret location, then display
	ship finally check if the ship has been hit.
	 */
	balance++;
	if (balance >=0 && balance <= 18){										//If balance less than 19 flag = 1;
		flag = 1;
	}
	else if(balance >=19 && balance <= 58){									//If balance 19 and 58  flag = 2;
		flag = 2;
	}

	else{
		flag = 3;															//Any other values of balance  flag = 3.
		if(balance == 59){													//When balance reaches 59 reset to -1.
			balance = -1;
		}
	}
}


//Function to determine if the UART has received a character.
//Returns a 1 if the UART receive buffer contains a character.
char char_received()
{
	if(UART0_S1 & 0x20)
		return 1;
	else
		return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
