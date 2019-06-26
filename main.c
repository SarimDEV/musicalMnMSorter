#include "EV3_FileIO.c"
#include "PC_FileIO.c"

int colourTracking()
{
	int red = 0, green = 0, blue = 0;
	getColorRGB(S1,red,green,blue);

	if(red >= 25 && red <= 40 && green >= 30 && green <= 50 && blue >= 5 && blue <= 15)
	{
		return 3;
	}
	else if(red >= 40 && red <= 65 && green >= 15 && green <= 35 && ((blue >= 5 && blue <= 20) || blue >= 80 && blue <= 95))
	{
		return 5;
	}
	else if(red >= 65 && red <= 80 && green >= 20 && green <= 40 && ((blue >= 5 && blue <= 20) || blue >= 80 && blue <= 95))
	{
		return 0;
	}
	else if(red >= 15 && red <= 45 && green >= 20 && green <= 40 && blue >= 20 && blue <= 40)
	{
		return 2;
	}
	else if(red >= 60 && red <= 85 && green >= 35 && green <= 55 && blue >= 5 && blue <= 20)
	{
		return 4;
	}
	else if(red >= 25 && red <= 40 && green >= 20 && green <= 30 && blue >= 5 && blue <= 20)
	{
		return 7;
	}
	else
	{
		return 9;
	}
}

void inputColoursToFile(int colour, TFileHandle &fout)
{
	writeLongPC(fout, colour);
	writeEndlPC(fout);
}


void musicPlayer(TFileHandle &fin)
{
	int currentColour = 0;
	while(readIntPC(fin, currentColour))
	{
		if(currentColour ==  3)
		{
			playSoundFile("C.rsf");
		}
		else if(currentColour == 2)
		{
			playSoundFile("D.rsf");
		}
		else if(currentColour == 4)
		{
			playSoundFile("E.rsf");
		}
		else if(currentColour == 5)
		{
			playSoundFile("G.rsf");
		}
		else if(currentColour == 0)
		{
			playSoundFile("F.rsf");
		}
		else
		{
			playSoundFile("A.rsf");
		}
		sleep(600);
	}
}

void botRotationSingleSort(int colour, int colourtosort)
{
	//Positive is clockwise
	//Negative is CCW
	int rotationamt = 0, speed = 10;
	if(colour == colourtosort) // RED
	{
		rotationamt = 60;
	}
	if(nMotorEncoder[motorB] < rotationamt)
	{
		motor[motorB] = speed;
		while(nMotorEncoder[motorB] < rotationamt && SensorValue[S2] == 0){}
		motor[motorB] = 0;
	}
	else if(nMotorEncoder[motorB] > rotationamt)
	{
		motor[motorB] = -1*speed;
		while(nMotorEncoder[motorB] > rotationamt && SensorValue[S2] == 0){}
		motor[motorB] = 0;
	}
}

void botRotationFullSort(int colour)
{
	//Positive is clockwise
	//Negative is CCW
	int rotationamt = 0, speed = 10;
	if(colour == 5) // RED
	{
		rotationamt = 0;
	}
	else if(colour == 2) // BLUE
	{
		rotationamt = 60;
	}
	else if(colour == 4) // YELLOW
	{
		rotationamt = 120;
	}
	else if(colour == 3) // Green
	{
		rotationamt = 180;
	}
	else if(colour == 7) // BROWN
	{
		rotationamt = -120;
	}
	else if(colour == 0) // ORANGE
	{
		rotationamt = -60;
	}
	if(nMotorEncoder[motorB] < rotationamt)
	{
		motor[motorB] = speed;
		while(nMotorEncoder[motorB] < rotationamt && SensorValue[S2] == 0){}
		motor[motorB] = 0;
	}
	else if(nMotorEncoder[motorB] > rotationamt)
	{
		motor[motorB] = -1*speed;
		while(nMotorEncoder[motorB] > rotationamt && SensorValue[S2] == 0){}
		motor[motorB] = 0;
	}
}

void botRotationXmasSort(int colour)
{
	//Positive is clockwise
	//Negative is CCW
	int rotationamt = 0, speed = 10;
	if(colour == 5) // RED
	{
		rotationamt = 60;
	}
	else if(colour == 3) // GREEN
	{
		rotationamt = -60;
	}
	if(nMotorEncoder[motorB] < rotationamt)
	{
		motor[motorB] = speed;
		while(nMotorEncoder[motorB] < rotationamt && SensorValue[S2] == 0){}
		motor[motorB] = 0;
	}
	else if(nMotorEncoder[motorB] > rotationamt)
	{
		motor[motorB] = -1*speed;
		while(nMotorEncoder[motorB] > rotationamt && SensorValue[S2] == 0){}
		motor[motorB] = 0;
	}
}

int modeSelection(int &colourToSort)
{
	int mode = 0;
	while(mode == 0)
	{
		if(getButtonPress(buttonLeft) == 1)
		{
			mode = 1; //Full Sort
			while(getButtonPress(buttonLeft) == 1){}
		}
		else if(getButtonPress(buttonRight) == 1)
		{
			while(getButtonPress(buttonRight) == 1){}
			mode = 2; //1 Colour Sort
			displayString(5, "Right: Red");
			displayString(6, "Left: Blue");
			displayString(7, "Up: Orange");
			displayString(8, "Down: Yellow");
			displayString(9, "Enter: Green");
			displayString(10, "Touch: Brown");
			while(colourToSort == -1)
			{
				if(getButtonPress(buttonRight) == 1)
				{
					colourToSort = 5;
				}
				else if(getButtonPress(buttonLeft) == 1)
				{
					colourToSort = 2;
				}
				else if(getButtonPress(buttonUp) == 1)
				{
					colourToSort = 0;
				}
				else if(getButtonPress(buttonDown) == 1)
				{
					colourToSort = 4;
				}
				else if(getButtonPress(buttonEnter) == 1)
				{
					colourToSort = 3;
				}
				else if(SensorValue[S2] == 1)
				{
					colourToSort = 7;
					while(SensorValue[S2] == 1){}
				}
				while(getButtonPress(buttonAny) == 1){}
			}
		}
		else if(getButtonPress(buttonEnter) == 1)
		{
			mode = 3;
			while(getButtonPress(buttonRight) == 1){}
		}
		else if(getButtonPress(buttonUp) == 1)
		{
			mode = 4;
			while(getButtonPress(buttonUp) == 1){}
		}
	}
	return mode;
}

void secretMode()
{
		displayString (6, "Playing SICKO MODE...");
		playSoundFile("Part1.rsf");
		playSoundFile("Part2.rsf");
		playSoundFile("Part3.rsf");
		playSoundFile("Part5.rsf");
		playSoundFile("Part6.rsf");
		sleep(38000);
		eraseDisplay();

}

void displayColours(int colour, int &red, int &blue, int &green, int &yellow, int &brown, int &orange, int &total)
{
	total++;

	if (colour == 2)
	{
		blue++;
	}

	else if (colour == 3)
	{
		green++;
	}

	else if (colour == 4)
	{
		yellow++;
	}

	else if (colour == 5)
	{
		red++;
	}

	else if (colour == 7)
	{
		brown++;
	}

	else if (colour == 0)
	{
		orange++;
	}

	displayString(3,"Blue: %d", blue);
	displayString(4,"Green: %d", green);
	displayString(5,"Yellow: %d", yellow);
	displayString(6,"Red: %d", red);
	displayString(7,"Brown: %d", brown);
	displayString(8,"Orange: %d", orange);
	displayString(10, "Total: %d", total);
}

task main()
{
	SensorType[S1] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S1] = modeEV3Color_RGB_Raw;
	wait1Msec(50);
	SensorType[S2] = sensorEV3_Touch;

	TFileHandle fout;
	word fileSize = 210;
	bool fileOkay = openWritePC(fout, "colourmusic.txt", fileSize);

	int red = 0, blue = 0, green = 0, yellow = 0, brown = 0, orange = 0;
	int total = 0;

	displayString(2, "   Welcome to the M&M sorter!");
	displayString(9, "              M ");
	drawEllipse(25, 80, 145, 20);

	wait1Msec(3000);
	eraseDisplay();
	int colourToSort = -1, mode = 0;

	displayString(1, "Press Left for Full Sort");
	displayString(2, "Press Right for Single Sort");
	displayString(3, "Press Enter for Christmas Sort");
	displayString(4, "Press Up for SeCrEt MoDe!");

	mode = modeSelection(colourToSort);

	eraseDisplay();

	if(mode == 1 || mode == 2 || mode == 3)
	{
		time1[T1] = 0;
		motor[motorD] = 75;
		while(SensorValue[S2] == 0 && time1[T1] < 17000)
		{

			motor[motorA] = -10;
			while(nMotorEncoder[motorA] > -220 && SensorValue[S2] == 0){}
			motor[motorA] = 10;
			while(nMotorEncoder[motorA] < -55 && SensorValue[S2] == 0){}
			motor[motorA] = 0;
			wait1Msec(500);
			int colour = colourTracking();
			wait1Msec(500);
			displayString(1,"the colour is: %d", colour);
			if(colour != 9)
			{
				clearTimer(T1);
				if(mode == 1)
				{
					botRotationFullSort(colour);
				}
				else if(mode == 2)
				{
					botRotationSingleSort(colour, colourToSort);
				}
				else
				{
					botRotationXmasSort(colour);
				}
				inputColoursToFile(colour, fout);
				displayColours(colour, red, blue, green, yellow, brown, orange, total);
				motor[motorA] = 10;
				while(nMotorEncoder[motorA] < 0 && SensorValue[S2] == 0){}
			}
	}

	motor[motorD] = 0;
	motor[motorA] = 10;
	while(nMotorEncoder[motorA] < 5 && SensorValue[S2])
	{}
	motor[motorA] = 0;

	if(nMotorEncoder[motorB] < 0)
	{
		motor[motorB] = 10;
		while(nMotorEncoder[motorB] < 0 && SensorValue[S2] == 0){}
		motor[motorB] = 0;
	}
	else if(nMotorEncoder[motorB] > 0)
	{
		motor[motorB] = -10;
		while(nMotorEncoder[motorB] > 0 && SensorValue[S2] == 0){}
		motor[motorB] = 0;
	}

	motor[motorB] = 0;

	TFileHandle fin;
	closeFilePC(fout);

	bool fileOkay1 = openReadPC(fin, "colourmusic.txt");
	musicPlayer(fin);
	}
	else if(mode == 4)
	{
		secretMode();
	}

}
