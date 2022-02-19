#include <iostream>
#include <iomanip>
#include<fstream>
#include <string> 
using namespace std;

void showMainMenu();
void genFile();
void tempStats();
void conTable();
void matrixPlay();
string GenFileName(string, string = "_temps.txt");
string getLastName();
int getOneRandNum(int, int);
int getTempType();
void getMinMaxRange(int&, int&);
int getNumTemps();
void prepInputfile();
void GenStats(string, int);
int getMinValue(int, int);
int getMaxValue(int, int);
void genOutput(string, string, string, string, int, int, int, int, int);
double celToFah(double);
double fahToCel(double);
void conOutput(string, string, string, string, int, int, int, int);
void oneDee(ofstream& outputFile, string);
void oneDeeMultiplication(ofstream& outputFile, string);
void oneDeeAddSub(ofstream& outputFile, string);
void displayArrayToScreen(int, int, int, int matrix[20], ofstream& outputFile);
void twoDee(ofstream& outputFile);

int main()
{
	const int GEN_FILE = 1,
		TEMP_STATS = 2,
		CON_TABLE = 3,
		MATRIX_PLAY = 4,
		QUIT_CHOICE = 5;
	int choice;
	string lName;
	string suffix;

	do
	{
		// Show Main Menu.
		showMainMenu();
		// Get user choice
		cin >> choice;
		// Retry until good entry.
		while (choice < 1 || choice > 5)
		{
			cout << "Please enter a valid menu choice: ";
			cin >> choice;
		}

		// If user does not want to quit, proceed.
		if (choice != 5)
		{
			switch (choice)
			{

			case 1:
				genFile();
				break;

			case 2:
				tempStats();
				break;

			case 3:
				conTable();
				break;

			case 4:
				matrixPlay();
				break;
			}

		}
	} while (choice != 5);
	return 0;
}
//Menu choice genFile and its functions
void showMainMenu()
{
	/*Function: void showMainMenu()
	Description: This fucntion displays the main menu.
	Returns: Nothing
	Notes: n/a
	*/
	cout << "\t\t Temperature Menu \n\n"
		<< "1) Generate random temp file\n"
		<< "2) Determine temp stats\n"
		<< "3) Generate temp conversion file\n"
		<< "4) Matrix Play\n"
		<< "5) Quit\n";
}
void genFile()
{
	/*Function: void genFile()
	Description: This function generates a file that contains temp type, min and max ranges, number of temps to generate, and then generates those random number and sends them to the created file.
	Returns: Nothing
	Notes: n/a
	*/
	ofstream outputFile;
	const int celsius = 2, fahrenheit = 1, returnMainMenu = 3;

	// Get last name.
	string lName = getLastName();
	// Generate File.
	string fileName = GenFileName(lName);
	// Get temptype
	int choice = getTempType();
	// Get Min range.
	int minRange, maxRange;
	getMinMaxRange(minRange, maxRange);
	// Get number of temps to generate.
	int numTemps = getNumTemps();
	// Generates number of temps based on user input between the min and max ranges
	int temps = getOneRandNum(minRange, maxRange);



	outputFile.open(fileName.c_str());
	outputFile << "Last name: " << lName << endl;

	switch (choice)
	{
	case 1:
		outputFile << "Temperature Type: F" << endl;
		break;
	case 2:
		outputFile << "Temperature Type: C" << endl;
		break;
	}
	outputFile << "Minimum range: " << minRange << endl;
	outputFile << "Maximum range: " << maxRange << endl;
	outputFile << "Number of temps generated: " << numTemps << endl;
	cout << "Temps" << endl;
	for (int i = 0; i < numTemps; i++) {
		temps = getOneRandNum(minRange, maxRange);
		outputFile << temps << endl;
	}
	outputFile.close();
	cout << "Info has been sent to " << fileName << endl;


}
string getLastName()
{
	/*Function: string getLastName()
	Description: Gets the users last name.
	Returns: lName
	Notes: n/a
	*/
	string lName;
	cout << "Enter your last name\n";
	cin >> lName;
	for (unsigned int i = 0; i < lName.length(); ++i)
	{
		lName[i] = tolower(lName[i]);
	}
	return lName;
}
int getTempType()
{
	/*Function: int getTempType()
	Description: Gets temp type (fahrenheit or celcius)
	Returns: choice
	Notes: n/a
	*/
	// Get temp typ, retrys if bad selection.
	int choice;
	do {
		cout << "\t\t Choose Temperature Type\n\n"
			<< "1) Fahrenheit\n"
			<< "2) Celsius\n";

		cin >> choice;
		// Verify temptype is Fahrenheit OR celcius, else retry.

		if (choice < 1 || choice > 2)
		{
			cout << "Invalid entry, please try again\n";
		}
	} while (choice < 1 || choice > 2);
	return choice;
}
void getMinMaxRange(int& minRange, int& maxRange)
{
	/*Function: int getMinRange()
	Description: Gets minimum temp range.
	Returns: minRange
	Notes: Gives error message if user input is less than 1
	*/
	// Get min and max ranges, retry until good entry.
	int x;

	do {
		cout << "Enter minimum temperature: ";
		cin >> minRange;

		x = 1;

		if (minRange < 1) // Min range cannot be less than 1
		{
			cout << "Minimum temperature should be greater than or equal to 1; please try again" << endl;
			x = 0;
		}

	} while (!x);

	do
	{
		cout << "Enter maximum temperature: ";
		cin >> maxRange;
		if (minRange > maxRange)
		{
			cout << "Max range cannot be less than min range; please try again" << endl;
		}

	} while (minRange > maxRange);

}
string GenFileName(string lName, string suffix)
{
	/*Function: string GenFileName()
	Description: Used to create the user .txt file.
	Returns: lName + "_temps.txt"
	Notes: Takes lName as an argument and creates the file based on user last name.
	*/
	return lName + suffix;
}
int getNumTemps()
{
	/*
	Function: int getNumTemps()
	Description: This function get the number of random temps from the user that will be generated.
	Returns: numTemps
	Notes: Displays error if numTemps is less than 1. Retrys until good entry.
	*/
	int numTemps;
	do
	{
		cout << "Enter number of temperatures to generate: ";
		cin >> numTemps;
		if (numTemps < 1)
		{
			cout << "Number of temperatures must be greater than or equal to one; please try again" << endl;
		}
	} while (numTemps < 1);
	return numTemps;
}
int getOneRandNum(int minRange, int maxRange)
{
	/*
	Function: int getOneRandNum()
	Description: Generates a random number between the min and max ranges.
	Returns: temps
	Notes: Takes minRange and maxRange as arguments which ensures the random number is inside the two values. Doesnt loop here but in genFile() instead.
	*/
	int temps;

	temps = minRange + rand() % (maxRange - minRange + 1);

	return temps;
}
// Menu choice tempStats and its functions =)
void tempStats()
{
	prepInputfile();
}
void prepInputfile() // Checks to see if user file exists.
{
	/*
	Function: void PrepInputfile()
	Description: This program will find or not find a .txt file that matches the user last name.
	Returns: nothing
	Notes: This function took a lot of time but was really fun to make! It displays "file not found" if user input is incorrect and gives them an option to try again or create a file.
	If user input is correct, the statistics menu will display!
	*/
	ifstream inputFile;
	int choiceA;
	int choiceB;
	string fileName;
	do
	{
		string lName;
		cout << "Enter your last name\n";
		cin >> lName;
		for (unsigned int i = 0; i < lName.length(); ++i)
		{
			lName[i] = tolower(lName[i]);
		}
		fileName = GenFileName(lName);

		inputFile.open(fileName.c_str());
		// File not found options.
		if (!inputFile.good())
		{
			cout << "File not found\n"
				<< "1) Reenter name\n"
				<< "2) Generate File\n";
			cin >> choiceA;
			if (choiceA == 2)
			{
				genFile(); // Lets user create a file if one is not found.
			}
		}
	} while (!inputFile.good());
	inputFile.close();

	// If a file is found display stats menu. 
	cout << "\t\t Statistics Menu\n\n "
		<< "1) Minimum temperature\n"
		<< "2) Maximum temperature\n"
		<< "3) Average temperature\n"
		<< "4) Get all three\n"
		<< "5) Quit\n";

	// Get user choice
	const int MIN_TEMP = 1, MAX_TEMP = 2, AVG_TEMP = 3, ALL_THREE = 4, QUIT = 5;
	cin >> choiceB;
	// Retry until good entry.
	while (choiceB < 1 || choiceB > 5)
	{
		cout << "Please enter a valid menu choice: ";
		cin >> choiceB;
	}
	// If user does not want to quit, proceed.
	if (choiceB != QUIT)
	{
		GenStats(fileName, choiceB);
	}
	while (choiceB != QUIT);
}
void GenStats(string fileName, int choiceB)
{
	/*
	Function: GenStats(string fileName, int choiceB)
	Description: Takes the filename and generates stats .
	Returns: nothing
	Notes: This function by far gave me the most issues. Reading from the file really threw me off since I was only trying to extract only certain info fromthe file
	I did go online tofigure out how to extract only the info I needed in each string (373-389). Without doing this the program wouldnt compile correctly. After
	it reads the randomly generated temps and find the max value and min value.
	*/
	ifstream inputFile;
	inputFile.open(fileName.c_str());
	int minTemp = 2000000;
	int maxTemp = -2000000;
	int avgTemp = 0;
	int count = 0;
	int t;
	string temp;

	getline(inputFile, temp);

	string tempTypeLine;
	getline(inputFile, tempTypeLine);
	string tempTypeStr = tempTypeLine.substr(tempTypeLine.find(": ") + 2); // sends only the info I wanted to display when called in genOutput()

	string minRangeLine;
	getline(inputFile, minRangeLine);
	string minRangeStr = minRangeLine.substr(minRangeLine.find(": ") + 2); // sends only the info I wanted to display when called in genOutput()

	string maxRangeLine;
	getline(inputFile, maxRangeLine);
	string maxRangeStr = maxRangeLine.substr(maxRangeLine.find(": ") + 2); // sends only the info I wanted to display when called in genOutput()

	string numTempsLine;
	getline(inputFile, numTempsLine);
	string numTempsStr = numTempsLine.substr(numTempsLine.find(": ") + 2); // sends only the info I wanted to display when called in genOutput()

	while (inputFile >> t) // used to determine the max and min temps.  Calls  the getMaxValue() and getMinValue functions to do so.
	{
		minTemp = getMinValue(t, minTemp);
		maxTemp = getMaxValue(t, maxTemp);
		avgTemp += t;
		count++;
	}
	avgTemp /= count;
	genOutput(fileName, tempTypeStr, minRangeStr, maxRangeStr, count, minTemp, maxTemp, avgTemp, choiceB);

	main();

}
int getMaxValue(int a, int b)
{
	/*
	Function: getMaxValue()
	Description: Get the max value of the generated numbers
	Returns: The max value ( a or b).
	Notes:So I know it says only one return statement per function, but i thought this was a clever way to get the max value. It just goes down each number in the .txt file and replaces it
	if it finds a greater value. Might change later.
	*/
	if (a > b)
		return a; // Returns a or b to GenStats
	else return b;
}
int getMinValue(int a, int b)
{
	/*
	Function: getMinValue()
	Description: Get the min value of the generated numbers
	Returns: The min value ( a or b).
	Notes: Same as above except if it finds a lower value the previous value will be replaced.
	*/
	if (a < b)
		return a; // Returns a or b to GenStats
	else return b;
}
void genOutput(string fileName, string tempType, string minRange, string maxRange, int numTemps, int minTemp, int maxTemp, int avgTemp, int choice)
{
	/*
	Function: genOutput(string fileName, string tempType, string minRange, string maxRange, int numTemps, int minTemp, int maxTemp, int avgTemp, int choice)
	Description: Outputs the info generated in GenStats(). Asks user how they want to display the information.
	Returns: nothing
	Notes: Pretty basic, easy to make.
	*/
	cout << "1) Print statistics to screen\n"
		<< "2) Send statistics to output file\n"
		<< "3) Do both\n";

	int choiceB;
	cin >> choiceB;
	// Retry until good entry.
	while (choiceB < 1 || choiceB > 3)
	{
		cout << "Please enter a valid menu choice: ";
		cin >> choiceB;
	}

	if (choiceB == 1 || choiceB == 3)
	{
		cout << "File Name: " << fileName << endl;
		cout << "Temp Type: " << tempType << endl;
		cout << "Minimum Range: " << minRange << endl;
		cout << "Maximum Range: " << maxRange << endl;
		cout << "Number of Temperatures: " << numTemps << endl;
		if (choice == 1 || choice == 4)
		{
			cout << "Min Temp: " << minTemp << endl;
		}
		if (choice == 2 || choice == 4)
		{
			cout << "Max Temp: " << maxTemp << endl;
		}
		if (choice == 3 || choice == 4)
		{
			cout << "Avg temp: " << avgTemp << endl;
		}

	}
	if (choiceB == 2 || choiceB == 3)
	{
		ofstream outputFile;
		outputFile.open(("output_" + fileName).c_str());

		outputFile << "File Name: " << fileName << endl;
		outputFile << "Temp Type: " << tempType << endl;
		outputFile << "Minimum Range: " << minRange << endl;
		outputFile << "Maximum Range: " << maxRange << endl;
		outputFile << "Number of Temperatures: " << numTemps << endl;
		if (choice == 1 || choice == 4)
		{
			outputFile << "Min Temp: " << minTemp << endl;
		}
		if (choice == 2 || choice == 4)
		{
			outputFile << "Max Temp: " << maxTemp << endl;
		}
		if (choice == 3 || choice == 4)
		{
			outputFile << "Avg temp: " << avgTemp << endl;
		}
		outputFile.close();
	}

}
// Menu choice conTable and its functions
void conTable()
{
	/*
	Function: void conTable()
	Description: Based on user choice, will display a conversion table from user input file or allow the user to manually enter data to create table.
	Returns: nothing
	*/

	cout << "1) Generate Conversion Table from output file" << endl;
	cout << "2) Manually enter conversion table data" << endl;

	int choice;
	cin >> choice;
	// Retry until good entry.
	while (choice < 1 || choice > 2)
	{
		cout << "Please enter a valid menu choice: ";
		cin >> choice;
	}
	if (choice == 1) // This part I couldnt do. I tried modifying the GenStats code to work with this bu i couldnt get it to run.
	{
		string lName; // Takes last name for file creation.
		cout << "Enter your last name" << endl;
		cin >> lName;
		for (unsigned int i = 0; i < lName.length(); ++i)
		{
			lName[i] = tolower(lName[i]);
		}
		ofstream outputFile;
		string outputFileName = lName + "_conversion.txt";
		outputFile.open(outputFileName.c_str());
		cout << "Creating Conversion Temp File" << outputFileName << endl;

		ifstream inputFile;
		string inputFileName = lName + "_temps.txt";
		inputFile.open(inputFileName.c_str());

		string line;
		char tempType = ' ';
		outputFile << "Conversion Table\n" << endl;
		while (getline(inputFile, line))
		{
			if (line.find("Temperature Type: F") != string::npos)
			{
				tempType = 'F';
			}
			else if (line.find("Temperature Type: C") != string::npos)
			{
				tempType = 'C';
			}
			else if (line.size() > 0 && line[0] >= '0' && line[0] <= '9')
			{
				int temp = stoi(line);
				if (tempType == 'F')
				{
					outputFile << line << ' ' << tempType << " = " << fahToCel(temp) << ' ' << 'C' << endl;
				}
				else if (tempType == 'C')
				{
					outputFile << line << ' ' << tempType << " = " << celToFah(temp) << ' ' << 'F' << endl;
				}
			}
		}
		inputFile.close();
		outputFile.close();

	}
	if (choice == 2) // This choice allows the user to manually enter data to create a conversion table
	{
		double tempChoice, celsius, fahrenheit;
		int numTemps;

		cout << "Select temperature type to enter" << endl;
		cout << "1) Celsius" << endl;
		cout << "2) Fahrenheit" << endl;
		cin >> tempChoice;
		cout << "How many temps would you like to enter" << endl;
		cin >> numTemps;


		while (tempChoice < 1 || tempChoice > 2)
		{
			cout << "Invalid temperture choice; please try again";
			cin >> tempChoice;
		}
		if (tempChoice == 1)
		{
			cout << "Enter temperature in celsius\n" << endl;
			cout << "Celsius\tFahrenheit\n" << endl;
			for (int i = 0; i < numTemps; i++)
			{
				cin >> celsius;
				cin.ignore();
				double fahrenheit = celToFah(celsius);
				cout << celsius << " C\t=\t " << fahrenheit << " F" << endl;
			}
		}
		if (tempChoice == 2)
		{
			cout << "Enter temperature in fahrenheit\n" << endl;
			cout << "Fahrenheit\tCelcius\n" << endl;
			for (int i = 0; i < numTemps; i++)
			{
				cin >> fahrenheit;
				cin.ignore();
				double celsius = fahToCel(fahrenheit);
				cout << fahrenheit << " F\t=\t " << celsius << " C" << endl;
			}
		}

	}
}
double celToFah(double celsius)
{
	/*
	Function: double fahToCel()
	Description: converts celsius to fahrenheit
	Returns: fahrenheit
	Notes:none
	*/
	double fahrenheit;
	fahrenheit = (1.8 * celsius) + 32;
	return fahrenheit;
}
double fahToCel(double fahrenheit)
{
	/*
	Function: double fahToCel()
	Description: converts fahrenheit to celsius
	Returns: celcius
	Notes:none
	*/
	double celsius;
	celsius = (fahrenheit - 32) * 5.0 / 9;
	return celsius;
}
void conOutput(string fileName, string tempType, string minRange, string maxRange, int numTemps, int minTemp, int maxTemp, int avgTemp)
{
	/*
	Function: void ConOutput()
	Description: Its was supposed to send the conversion table to a file but it doesnt work
	Returns: nothing
	Notes: =(
	*/
	cout << fileName << endl;
	cout << tempType << endl;
	for (int i = minTemp; i <= maxTemp; i++)
	{
		cout << i << endl;
	}
}
// Beginning of Final project
void matrixPlay()
{
	/*Function: void matrixPlay()
	Description: This function is used as the starting point for array portion of this project. It will get the output file that all arrays will be stored in and provides
	a menu to choose between 1D and 2D arrays.
	Returns: Nothing
	*/
	int choice;
	string outFile; // Takes last name for file creation.
	cout << "Enter output file" << endl;
	cin >> outFile; // Gets outputfile of user's choice in which all arrays from this program will be sent.
	for (unsigned int i = 0; i < outFile.length(); ++i) // Used to change user input to lower case.
	{
		outFile[i] = tolower(outFile[i]);
	}
	ofstream outputFile;
	string outputFileName = outFile + "_arrays.txt";// Created file will be user's choice + _arrays.txt
	outputFile.open(outputFileName, ios::app);

	cout << "Please choose an option" << endl // Menu to choose 1-D or 2-D array
		<< "1) Work with 1-D matrices" << endl
		<< "2) Work with 2-D matrices" << endl
		<< "3) Return to Main Menu" << endl;
	do
	{
		// Get user choice
		cin >> choice;

		// Retry until good entry.
		while (choice < 1 || choice > 3)
		{
			cout << "Please enter a valid menu choice: " << endl;
			cin >> choice;
		}

		if (choice != 3)
		{
			switch (choice)
			{
			case 1:
				oneDee(outputFile, outputFileName);
				break;

			case 2:
				twoDee(outputFile);
				break;

			}
		}

	} while (choice != 3);
	main();
}
void oneDee(ofstream& outputFile, string outputFileName)
{
	/*Function: void oneDee(ofstream& outputFile)
	Description: The function is home for the 1D array portion. It displays a menu to user asking if they want to multiply or add/substract.
	Returns: Nothing
	*/
	int choice;
	cout << "What would you like to do with your 1-D array? " << endl // Menu that gets user choice of multiplication or addition and substraction. 
		<< "1) Multiply" << endl
		<< "2) Addition or Subtraction" << endl;
	cin >> choice;
	while (choice < 1 || choice > 2)
	{
		cout << "Please enter a valid menu choice: ";
		cin >> choice;
	}
	if (choice == 1)
	{
		oneDeeMultiplication(outputFile, outputFileName);
	}
	if (choice == 2)
	{
		oneDeeAddSub(outputFile, outputFileName);
	}
}
void twoDee(ofstream& outputFile)
{
	/*Function: void twoDee(ofstream& outputFile)
	Description: This function takes in two 2D arrays from text.txt and adds, subtracts, or multiplys based on the token in the file
	Returns: Nothing
	*/
	ifstream inputFile;
	string fileName;

	cout << "Input file name" << endl;
	do
	{
		cin >> fileName;
		for (unsigned int i = 0; i < fileName.length(); ++i)
		{
			fileName[i] = tolower(fileName[i]);
		}
		inputFile.open(fileName.c_str());
		if (!inputFile.good())
		{
			cout << "File not found, Try again" << endl;
		}
	} while (!inputFile.good());

	int matrix[10][10];
	int matrix2[10][10];
	int total[10][10];
	int row = 0;
	int col = 0;
	string token;

	while (inputFile >> row >> col >> token) // reads info from first line of text file. 
	{
		for (int i = 0; i < row; i++) // This for loop gets the value of array 1
		{
			for (int j = 0; j < col; j++)
			{
				int a;
				inputFile >> a;
				matrix[i][j] = a;

			}
		}

		for (int i = 0; i < row; i++) // this for loop get array 2
		{
			for (int j = 0; j < col; j++)
			{
				int b;
				inputFile >> b;
				matrix2[i][j] = b;

			}
		}

		cout << endl << "2D Table" << endl << endl;
		outputFile << endl << "2D Table" << endl << endl;
		// the following 3 if / if else statements read the token and output the respective totals.
		if (token == "+") // add
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					total[i][j] = matrix[i][j] + matrix2[i][j];
					cout << matrix[i][j] << " + " << matrix2[i][j] << " = " << total[i][j] << endl;
					outputFile << matrix[i][j] << " + " << matrix2[i][j] << " = " << total[i][j] << endl;
				}
			}
		}
		else if (token == "-") // subtract
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					total[i][j] = matrix[i][j] - matrix2[i][j];
					cout << matrix[i][j] << " - " << matrix2[i][j] << " = " << total[i][j] << endl;
					outputFile << matrix[i][j] << " - " << matrix2[i][j] << " = " << total[i][j] << endl;
				}
			}
		}
		else if (token == "*") // multiply
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					total[i][j] = matrix[i][j] * matrix2[i][j];
					cout << matrix[i][j] << " * " << matrix2[i][j] << " = " << total[i][j] << endl;
					outputFile << matrix[i][j] << " * " << matrix2[i][j] << " = " << total[i][j] << endl;
				}
			}
		}
	}
	inputFile.close();
	outputFile.close();
	main();
}
void oneDeeMultiplication(ofstream& outputFile, string outputFileName)
{
	/*Function: void oneDeeMultiplication(ofstream& outputFile)
	Description:  In choice one, this function will ask the user for the array size, array contents, and the scalar. In choice two, the inputfile wil be read, displayed to screen and sent to output.
	Returns: Nothing
	*/
	int choice;
	cout << "How would you like to input your matrix information?\n" // Asks user for manual input or upload from file.
		<< "1) Input manually\n"
		<< "2) Upload information from and input file\n" << endl;
	cin >> choice;
	cout << endl << endl;
	while (choice < 1 || choice > 2)
	{
		cout << "Invalid selection, Try again" << endl;
		cin >> choice;
	}
	if (choice == 1)
	{
		const int ARRAY_SIZE = 20;
		int numberOfValues;
		int counter = 0;
		int scaler;
		int matrix[ARRAY_SIZE];
		cout << "Enter the size of the matrix, Cannot be greater than 20" << endl; // Gets size of array and wont allow it to be greater than 20
		cin >> numberOfValues;
		while (numberOfValues < 1 || numberOfValues > 20)
		{
			cout << "Try again" << endl; // Try again 
			cin >> numberOfValues;
		}
		cout << "Enter contents of the matrix" << endl; // User inputs contents of the array. 
		for (counter = 0; counter < numberOfValues; counter++) // Loop used to keep getting input until the numberOfValues entered previously is met.
		{
			cin >> matrix[counter];
		}
		cout << "Enter a number to multiply the matrix by" << endl; // User enters the integer they want the array multiplied by.
		cin >> scaler;
		cout << "\nMatrix Multiplication Table\n" << endl;
		outputFile << "\nMatrix Multiplication Table\n" << endl;
		displayArrayToScreen(numberOfValues, counter, scaler, matrix, outputFile); // The numberOfValues, counter, and scalar are all sent to this funtion which displays it the the screen.

		cout << "Sending Data to Matrix File " << endl;
		outputFile.close(); // Close File
		main();
	}
	if (choice == 2)
	{

		ifstream inputFile;
		string fileName;
		string dataType;
		const int ARRAY_SIZE = 20;
		int scalar = 1;
		int matrix[ARRAY_SIZE];

		cout << "Input file name" << endl;
		do
		{
			cin >> fileName;
			for (unsigned int i = 0; i < fileName.length(); ++i)
			{
				fileName[i] = tolower(fileName[i]);
			}
			inputFile.open(fileName.c_str());
			if (!inputFile.good())
			{
				cout << "File not found, Try again" << endl;
			}
		} while (!inputFile.good());


		cout << "\nMatrix Multiplication Table\n" << endl;
		outputFile << "\nMatrix Multiplication Table\n" << endl;

		int STATE_NONE = 0;
		int STATE_SCALAR = 1;
		int STATE_NUMBERLIST = 2;
		int state = 0;
		int counter = 0;
		string token;

		while (inputFile >> token) // While loop reads the input file to find keywords like Scalar: and Numbers: if Scalar: is found the number after is stored in scaler and in Number: is found							//
		{							// the the contents of the array are stored in matrix[counter]

			if (token == "Scalar:")
			{
				state = STATE_SCALAR;
				counter = 0;
			}
			else if (token == "Numbers:")
			{
				state = STATE_NUMBERLIST;
				counter = 0;
			}
			else if (state == STATE_SCALAR)
			{
				scalar = stoi(token); // Converts token from string to integer allowing scalar to save the number.
			}
			else if (state == STATE_NUMBERLIST)
			{
				matrix[counter] = stoi(token); // Converts token from string to integer allowing matrix[counter] to save the array.
				cout << matrix[counter] << " * " << scalar << " = " << matrix[counter] * scalar << endl; // Outputs to screen
				outputFile << matrix[counter] << " * " << scalar << " = " << matrix[counter] * scalar << endl; // Outputs to outputfile
				counter++;
			}
		}
		cout << "Imported data from " << fileName << " and exported data to " << outputFileName << endl;
		inputFile.close();
		outputFile.close();
		main();
	}
}
void oneDeeAddSub(ofstream& outputFile, string outputFileName)
{
	/*Function: void oneDeeAddSub(ofstream& outputFile)
	Description: The first portion of this function will allow the user to manually input the contents of the array. The second part takes contents from an inputfile.
	Returns: Nothing
	*/
	const int ARRAY_SIZE = 20;
	int counter = 0;
	ifstream inputFile;
	int matrix[ARRAY_SIZE];

	int choice;
	cout << "How would you like to input your matrix information?\n"
		<< "1) Input manually\n" // Manual input
		<< "2) Upload information from and input file\n" << endl; // inputfile
	cin >> choice;
	cout << endl << endl;
	while (choice < 1 || choice > 2)
	{
		cout << "Invalid selection, Try again" << endl; // Error message
		cin >> choice;
	}
	if (choice == 1)
	{
		const int ARRAY_SIZE = 20;
		int sum;
		int diff;
		int numberOfValues;
		int counter = 0;
		int matrix1[ARRAY_SIZE];
		int matrix2[ARRAY_SIZE];
		cout << "Enter the size of the matrix, Cannot be greater than 20" << endl; // User enters size of the array. 
		cin >> numberOfValues;
		while (numberOfValues < 1 || numberOfValues > 20)
		{
			cout << "Try again" << endl; // Asks the try again if number is greater than 20
			cin >> numberOfValues;
		}
		cout << "Enter contents of the matrix 1" << endl; // Takes contents of array 1
		for (counter = 0; counter < numberOfValues; counter++) // loop will stop when number of values is attained
		{
			cin >> matrix1[counter];
		}
		cout << "Enter contents of the matrix 2" << endl; // Takes contents for array 2
		for (counter = 0; counter < numberOfValues; counter++) // loop will stop when number of values is attained
		{
			cin >> matrix2[counter];
		}
		int choice;
		cout << "Choose an option" << endl; // User chooses if they want to add or substract. 
		cout << "1) Addition" << endl;
		cout << "2) Subtraction" << endl;
		cin >> choice;
		while (choice < 1 || choice > 2)
		{
			cout << "Invalid selection, Try again" << endl; // Error message
			cin >> choice;
		}
		if (choice == 1) // Addition
		{
			cout << "\nAddition Table\n" << endl;
			outputFile << "\nAddition Table\n" << endl;
			for (counter = 0; counter < numberOfValues; counter++)
			{
				sum = matrix1[counter] + matrix2[counter]; // array 1 + array 2
				cout << " " << matrix1[counter] << " + " << matrix2[counter] << " = " << sum << endl; // output to screen
				outputFile << " " << matrix1[counter] << " + " << matrix2[counter] << " = " << sum << endl; // output to file
			}

		}
		if (choice == 2) // Subtraction
		{
			cout << "\nSubtraction Table\n" << endl;
			outputFile << "\nSubtraction Table\n" << endl;
			for (counter = 0; counter < numberOfValues; counter++)
			{
				diff = matrix1[counter] - matrix2[counter]; // array 1 - array 2
				cout << " " << matrix1[counter] << " - " << matrix2[counter] << " = " << diff << endl; // output to screen
				outputFile << " " << matrix1[counter] << " - " << matrix2[counter] << " = " << diff << endl; // output to file
			}
		}
		cout << "Sending Data to Matrix File " << endl;
		outputFile.close(); // close file
		main();
	}
	if (choice == 2)
	{
		int STATE_ADD = 0;
		int STATE_SUBT = 1;
		string token;
		string fileName;
		int state;

		cout << "Input file name" << endl;
		do
		{
			cin >> fileName;
			for (unsigned int i = 0; i < fileName.length(); ++i)
			{
				fileName[i] = tolower(fileName[i]);
			}
			inputFile.open(fileName.c_str());
			if (!inputFile.good())
			{
				cout << "File not found, Try again" << endl;
			}
		} while (!inputFile.good());

		cout << "\nAddition/Subtraction Table\n" << endl;
		outputFile << "\nAddition/Subtraction Table\n" << endl;
		for (int counter = 0; counter < ARRAY_SIZE; counter++) // starts the matrix[counter] at 0 .
		{
			matrix[counter] = 0;
		}
		while (inputFile >> token) // reads each line of the inputfile for a token containing either + or - 
		{

			if (token == "+")
			{
				state = STATE_ADD;
				counter = 0;
			}
			else if (token == "-")
			{
				state = STATE_SUBT;
				counter = 0;
			}
			else if (state == STATE_ADD) // if + is found, this will execute and add the array to the prvious array
			{
				int val = stoi(token);
				int sum = val + matrix[counter];
				cout << matrix[counter] << " + " << val << "=" << sum << endl;
				outputFile << matrix[counter] << " + " << val << "=" << sum << endl;
				matrix[counter] = sum;
				counter++;
			}
			else if (state == STATE_SUBT) // if - is found ,this will execute and subtract the array from the previous array
			{
				int val = stoi(token);
				int sum = val - matrix[counter];
				cout << matrix[counter] << " - " << val << "=" << sum << endl;
				outputFile << matrix[counter] << " - " << val << "=" << sum << endl;
				matrix[counter] = sum;
				counter++;
			}
		}
		cout << "Imported data from " << fileName << " and exported data to " << outputFileName << endl;
		inputFile.close();
		outputFile.close();
		main();
	}
}
void displayArrayToScreen(int counter, int numberOfValues, int scaler, int matrix[20], ofstream& outputFile)
{
	/*Function: void displayArrayToScreen(int counter, int numberOfValues, int scaler, int matrix[20], ofstream& outputFile)
	Description: This function displays the 1D multiplication portion to the screen.
	Returns: Nothing
	Notes: I started with this to display the arrays the the screen but eventually found it to be pointless. After completeing the 1D multiplication portion I just started putting the
	cout << and outputFile << in the other funtions. Might remove later.
	*/
	int product;
	for (counter = 0; counter < numberOfValues; counter++)
	{
		product = matrix[counter] * scaler;
		cout << " " << matrix[counter] << " * " << scaler << " = " << product << endl;
		outputFile << " " << matrix[counter] << " * " << scaler << " = " << product << endl;
	}
	cout << "Scaler: " << scaler << endl;
	outputFile << "Scaler: " << scaler << endl;
	cout << "Matrix size: " << numberOfValues << endl;
	outputFile << "Matrix size: " << numberOfValues << endl;
	cout << "\n\n";
	outputFile << "\n\n";
}
