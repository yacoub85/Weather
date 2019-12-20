#include <iostream>
#include<string>
#include<fstream>
#include<array>
#include<stdlib.h> 
#include<stdio.h> 
using namespace std;

struct WeatherData
{
	string inOut, time;
	float temperature;
	unsigned short int humidity, moIndex,doorTimer,doorCounter;
	int date;
};

struct WeatherDataDaily
{
	string time;
	float temperature;
	int date;
	unsigned short int doorCounter, minute, sumMinute;
};
//calculet th mogelindex
short int calcMog(float temp, int humi)
{
	short int mogel = 0;

	if (humi > 79 && temp < 15 && temp >= 0)
	{
		// When the temperature drops 1 degree below 15, humidity should increase by 1.7%
		int t = (int)(15 - temp);
		humi = humi - (int)(t * 1.7);

		if (humi >= 78 && humi < 81)
			mogel = 1;
		if (humi >= 81 && humi < 84)
			mogel = 2;
		if (humi >= 84 && humi < 87)
			mogel = 3;
		if (humi >= 87 && humi < 90)
			mogel = 4;
		if (humi >= 90 && humi < 93)
			mogel = 5;
		if (humi >= 93)
			mogel = 6;
	}
	if (humi >= 78 && temp >= 15)
	{
		int t0 = (int)temp - 15;
		humi = humi + (int)(t0 * 1.7);

		if (humi >= 78 && humi < 81)
			mogel = 1;
		if (humi >= 81 && humi < 84)
			mogel = 2;
		if (humi >= 84 && humi < 87)
			mogel = 3;
		if (humi >= 87 && humi < 90)
			mogel = 4;
		if (humi >= 90 && humi < 93)
			mogel = 5;
		if (humi > 93)
			mogel = 6;
	}
	return mogel;


}
//Handling input errors
int checkInput()
{
	int input;
	while (true)
	{
		cin >> input;
		if (cin.fail())
		{
			cout << "Invalid choice try again" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else
		{
			break;
		}
	}

	return input;
}
//Return to the main menu
void returnTomenu()
{
	cout << "\n\nPress Enter to back to the main menu... " << endl;
	//pause displays a message and waits for the user to hit a key
	system("PAUSE");
	//Clearing the Screen
	system("CLS");

}

//Merges sort by date.
void mergeDate(WeatherData arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1; // Middle - left + 1
	int n2 = r - m;		// Right - Middle

	/* create temp arrays */
	WeatherData* L = new WeatherData[n1];	// Left part of array
	WeatherData* R = new WeatherData[n2];	// Right part of array

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i].date <= R[j].date)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortDate(WeatherData arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and r 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSortDate(arr, l, m);
		mergeSortDate(arr, m + 1, r);

		mergeDate(arr, l, m, r);

	}
}
// Merges sort by temperature. 
void mergeTemperature(WeatherData arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1; // Middle - left + 1
	int n2 = r - m;		// Right - Middle

	/* create temp arrays */
	WeatherData* L = new WeatherData[n1];	// Left part of array
	WeatherData* R = new WeatherData[n2];	// Right part of array

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i].temperature >= R[j].temperature)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortTemperature(WeatherData arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and r 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSortTemperature(arr, l, m);
		mergeSortTemperature(arr, m + 1, r);

		mergeTemperature(arr, l, m, r);

	}
}
//Merges sort by humidity.
void mergeHumidity(WeatherData arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1; // Middle - left + 1
	int n2 = r - m;		// Right - Middle

	/* create temp arrays */
	WeatherData* L = new WeatherData[n1];	// Left part of array
	WeatherData* R = new WeatherData[n2];	// Right part of array

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i].humidity <= R[j].humidity)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortHumidity(WeatherData arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and r 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSortHumidity(arr, l, m);
		mergeSortHumidity(arr, m + 1, r);

		mergeHumidity(arr, l, m, r);

	}
}
//Merges sort by risk of mogel.
void mergeMog(WeatherData arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1; // Middle - left + 1
	int n2 = r - m;		// Right - Middle

	/* create temp arrays */
	WeatherData* L = new WeatherData[n1];	// Left part of array
	WeatherData* R = new WeatherData[n2];	// Right part of array

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i].moIndex <= R[j].moIndex)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortMog(WeatherData arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and r 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSortMog(arr, l, m);
		mergeSortMog(arr, m + 1, r);

		mergeMog(arr, l, m, r);

	}
}
//Merges sort by the longest time the balcony door was opened
void mergeDoor(WeatherData arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1; // Middle - left + 1
	int n2 = r - m;		// Right - Middle

	/* create temp arrays */
	WeatherData* L = new WeatherData[n1];	// Left part of array
	WeatherData* R = new WeatherData[n2];	// Right part of array

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i].doorTimer <= R[j].doorTimer)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
void mergeSortDoor(WeatherData arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and r 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSortDoor(arr, l, m);
		mergeSortDoor(arr, m + 1, r);

		mergeDoor(arr, l, m, r);

	}
}

//binarySearch
int binarySearch(WeatherData arr[], int leftIndex, int rightIndex, int x)
{
	while (leftIndex <= rightIndex)
	{
		int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

		if (arr[middleIndex].date == x)
			return middleIndex;

		if (arr[middleIndex].date < x)
			leftIndex = middleIndex + 1;

		if (arr[middleIndex].date > x)
			rightIndex = middleIndex - 1;
	}
	return -1;

}

//print Out
void printOut(WeatherData arr[], int start, int end, string text, int freeChoice)
{

	cout << "\n\n\t" << text << endl;
	cout << "\n\n\t" << "   Date" << "    " << "   inOut" << "   " << "temperature" << "    " << "Humidity" << "     " << "MoIndex" << endl << endl;
	if (start < end)
	{
		for (start; start < end; start++)
		{
			cout << "\t" << arr[start].date << "       " << arr[start].inOut << "	  " << roundf(arr[start].temperature * 100) / 100
				<< "        " << arr[start].humidity << "%" << "\t     " << arr[start].moIndex << endl;
		}
		cout << "\n\n\t........................................................." << endl;
	}
	if (start > end)
	{
		for (start; start > end; start--)
		{
			cout << "\t" << arr[start].date << "       " << arr[start].inOut << "	  " << roundf(arr[start].temperature * 100) / 100
				<< "        " << arr[start].humidity << "%" << "\t     " << arr[start].moIndex << endl;
		}
		cout << "\n\n\t........................................................." << endl;
	}

	if (freeChoice == 1)
	{
		cout << "\n\n\tDo you want print out all days press [1]  or press [0] to back to main menu ";
		int inputDate = checkInput();
		if (inputDate == 1)
		{
			//call the print function
			printOut(arr, 0, 130, "-All days:", 0);
		}
		
	}
	

}
//print Out for Door
void printOutIN(WeatherData arr[], int start, int end, string text, int freeChoice)
{

	cout << "\n\n\t" << text << endl;
	cout << "\n\n\t" << "   Date" << "    " << "   inOut" << "   " << "temperature" << "    " << "Humidity" << "     " << "MoIndex" <<"   Door  " <<" Minutes "<<endl << endl;
	if (start < end)
	{
		for (start; start < end; start++)
		{
			cout << "\t" << arr[start].date << "       " << arr[start].inOut << "	  " << roundf(arr[start].temperature * 100) / 100
				<< "        " << arr[start].humidity << "%" << "\t     " << arr[start].moIndex << "\t     " << arr[start].doorCounter<< "\t     " <<arr[start].doorTimer<<endl;
		}
		cout << "\n\n\t............................................................................" << endl;
	}
	if (start > end)
	{
		for (start; start > end; start--)
		{
			cout << "\t" << arr[start].date << "       " << arr[start].inOut << "	  " << roundf(arr[start].temperature * 100) / 100
				<< "        " << arr[start].humidity << "%" << "\t     " << arr[start].moIndex << "\t     " << arr[start].doorCounter << "\t     " << arr[start].doorTimer << endl;
		}
		cout << "\n\n\t............................................................................." << endl;
	}

	if (freeChoice == 1)
	{
		cout << "\n\n\tDo you want print out all days press [1] or press [0] to back to main menu ";
		int inputDate = checkInput();
		if (inputDate == 1)
		{
			//call the print function
			printOutIN(arr, 0, 130, "-All days:", 0);
		}

	}


}

int main()
{
	cout << "\n\tPlease Wait...";
	
	WeatherData* tempArr = new WeatherData[3800];// temporary inside and Outside array
	WeatherData* arrIn = new WeatherData[130]; //   inside main array
	WeatherData* arrOut = new WeatherData[130];//   Outside main array

	WeatherDataDaily* arrAllIn = new WeatherDataDaily[164444];//all insides temperatures 


	//declare variables to use it temporary to save values in array
	string temporaryYear  = "0", * pTemporaryYear  = &temporaryYear;
	string temporaryMonth = "0", * pTemporaryMonth = &temporaryMonth;
	string temporaryDay   = "0", * pTemporaryDay   = &temporaryDay;

	
	string temporary = "0", * pTemporary = &temporary;

	float inTempSum = 0, outTempSum = 0;
	int   inHumiSum = 0, outHumiSum = 0;

	//declare new counters to use it to fill the main array
	int inCount = 0, outCount = 0, doorCounter = 0, x = 0, i = 0;


	//reading from file and saving data in temporary array then to main arrays
	ifstream text("tempdata4.txt");
	if (text.is_open())
	{
		unsigned  int currentDay = 0;
		unsigned  int checkDate = 0;

		while (!text.eof())
		{
			//first time reading from the file
			if (i == 0 && x == 0)
			{
				// read date fram the file
				getline(text, *pTemporaryYear, '-');
				getline(text, *pTemporaryMonth, '-');
				getline(text, *pTemporaryDay, ' ');
				// save date in temporary array
				tempArr[i].date = (stoi(*pTemporaryYear) * 10000) + (stoi(*pTemporaryMonth) * 100) + (stoi(*pTemporaryDay));
				// read time fram the file and save it in temporary array
				getline(text, tempArr[i].time, ',');
				//read and save sensor place
				getline(text, tempArr[i].inOut, ',');
				//read and save temperature
				getline(text, *pTemporary, ',');
				tempArr[i].temperature = stof(*pTemporary);
				//read and save humidity
				getline(text, *pTemporary);
				tempArr[i].humidity = stoi(*pTemporary);
				//set the same date  for both current day and check date 
				currentDay = tempArr[i].date;
				checkDate = tempArr[i].date;

				i++;
			}
			//continuing reading from the file
			if (i != 0)
			{
				//read date and check if it is same day or it is new day
				getline(text, *pTemporaryYear, '-');
				getline(text, *pTemporaryMonth, '-');
				getline(text, *pTemporaryDay, ' ');
				checkDate = (stoi(*pTemporaryYear) * 10000) + (stoi(*pTemporaryMonth) * 100) + (stoi(*pTemporaryDay));

				//if the current reading of date is same the last reading of date
				if (checkDate == currentDay)
				{
					//save date in array
					tempArr[i].date = currentDay;
					//read time and ather data and save it in temporary array
					getline(text, tempArr[i].time, ',');
					getline(text, tempArr[i].inOut, ',');
					getline(text, *pTemporary, ',');
					tempArr[i].temperature = stof(*pTemporary);
					getline(text, *pTemporary);
					tempArr[i].humidity = stoi(*pTemporary);
					i++;
				}
				//if the current reading of date is not same the last reading of date 
				if (checkDate != currentDay)
				{
					//Read fram temporary array by location of sensor and calc sum of the temperatures and Humidity

					//Internal sensor
					for (int j = 0; j < i; j++)
					{
						if (tempArr[j].inOut == "Inne")
						{
							inCount++;//counter to save all information in separate array
							inTempSum += tempArr[j].temperature;
							inHumiSum += tempArr[j].humidity;

							//save all Internal sensor readings in separate array to analyse it then 
							arrAllIn[doorCounter].date = tempArr[j].date;
							arrAllIn[doorCounter].time= tempArr[j].time;
							arrAllIn[doorCounter].temperature = tempArr[j].temperature;
							doorCounter++;
						}
						//external sensor
						if (tempArr[j].inOut == "Ute")
						{
							outCount++;
							outTempSum += tempArr[j].temperature;
							outHumiSum += tempArr[j].humidity;
						}
						//After finish the calculating, save all the results in main arrays
						if (j == (i - 1))
						{
							// Save Average of the internal temperatures and Humidity in the main array	
							arrIn[x].temperature = (inTempSum / inCount);
							arrIn[x].temperature = (inTempSum / inCount);
							arrIn[x].humidity = (inHumiSum / inCount);
							arrIn[x].inOut = "Inne";
							arrIn[x].date = currentDay;
							//calc the mogelIndex  by caling its function and svae it in the main array
							arrIn[x].moIndex = calcMog(inTempSum / inCount, inHumiSum / inCount);

							//Save Average of the external temperatures and Humidity in the main array
							arrOut[x].temperature = (outTempSum / outCount);
							arrOut[x].humidity = (outHumiSum / outCount);
							arrOut[x].inOut = "Ute";
							arrOut[x].date = currentDay;
							//calc the mogelIndex  by caling its function and svae it in the main array
							arrOut[x].moIndex = calcMog(outTempSum / outCount, outHumiSum / outCount);
							x++;

							//Set the beginning from the next day
							currentDay = checkDate;
							//Reset counters
							i = 0;
							inCount = 0; outCount = 0;
							inTempSum = 0; outTempSum = 0;
							inHumiSum = 0; outHumiSum = 0;
						}
					}
					//beginning read new date
					if (i == 0 && x != 0)
					{
						tempArr[i].date = currentDay;
						getline(text, tempArr[i].time, ',');
						getline(text, tempArr[i].inOut, ',');
						getline(text, *pTemporary, ',');
						tempArr[i].temperature = stof(*pTemporary);
						getline(text, *pTemporary);
						tempArr[i].humidity = stoi(*pTemporary);

						i++;
					}
				}
			}
		}
	}
		
	
	int index = 0;
	float n = 0; float* pN = &n;
	int j = 0;
	int today = 0;
	int yesterday = 0;
	doorCounter = 0;
	int inCountr = 0;
	int sumMinute = 0; int minute = 0;
	short int indexMini = 0, indexMax = 0;
	float miniTemp = 0, maxTemp = 0;

	//analyze temperature changes and draw conclusions
	for (int i = 0; i < 164444; i++)
	{
		if (i == 0)
		{
			today = arrAllIn[0].date;
			yesterday = arrAllIn[0].date;
		}
		//calc the difference between current and next reading of temperature
		*pN = arrAllIn[i].temperature - arrAllIn[i + 1].temperature;

		//if the difference is more than 0,3 degrees that's mean is something happened and caused this 
		//big difference in temperature 
		if (*pN >= 0.3 && i != 164444)
		{
			doorCounter++;
			//minute++;
			sumMinute++;

			i++;
			*pN = (arrAllIn[i].temperature) - (arrAllIn[i + 1].temperature);

			while (*pN >= 0.01 && i != 164444)
			{
				//minute++;
				sumMinute++;
				

				i++;
				*pN = arrAllIn[i].temperature - arrAllIn[i + 1].temperature;
			}

		}

		today = arrAllIn[i].date;
		if (today != yesterday)
		{

			//save results in the main array
			arrIn[j].doorCounter = doorCounter;
			arrIn[j].doorTimer = sumMinute;

			//cout << "Door Counter= " << arrIn[j].doorCounter << "   Door Timer = " << arrIn[j].doorTimer << endl;

			j++;
			yesterday = arrAllIn[i].date;
			doorCounter = 0;
			sumMinute = 0;
		}
	}
	

	//print out the menu selection:
	index = 0;
	int inputDate = 0;
	//int* inputDate = new int;
	bool loop = true;
	while (loop)
	{
		
		short int choice1, choice2, choice3, choice4;
		system("CLS");////Clearing the Screen
		cout << "\n\tvälj: " << endl;
		cout << "\t[1] Inomhus" << endl;
		cout << "\t[2] Utomhus" << endl;
		cout << "\t[3] Temperaturen som skiljer sig mest och minst" << endl;
		cout << "\t[4] Exit" << endl;

		choice1 = checkInput();
		system("CLS");////Clearing the Screen
		switch (choice1)
		{
		case 1:
			cout << "\n\t[Inomhus]\n";
			cout << "\t\tvنlj: " << endl;
			cout << "\t\t   [1] Medeltemperatur fِr valt datum" << endl;
			cout << "\t\t   [2] Sortering av varmast till kallaste dagen" << endl;
			cout << "\t\t   [3] Sortering av torrast till fuktigaste dagen" << endl;
			cout << "\t\t   [4] Sortering av minst till störst risk av mِgel" << endl;
			cout << "\t\t   [5] Skriva ut doors öppnings information" << endl;
			cout << "\t\t   [6] Sortering av längst tid var dorren öppnad" << endl;
			cout << "\t\t   [7] Back to main menu" << endl;

			choice2 = checkInput();
			switch (choice2)
			{
				
			case 1:
				//sort by date
				mergeSortDate(arrIn, 0, 129);
				system("CLS");//Clearing the Screen
				cout << "\n\tEnter the date [YYYYMMDD] to view the details:";
				inputDate = checkInput();
				//call the search function
				index = binarySearch(arrIn, 0, 130, inputDate);

				if (index != -1)
				{
					//call the print function
					printOutIN(arrIn, index, index + 1, "-Medeltemperatur:", 1);
				}
				else
				{
					//call the print function
					printOutIN(arrIn, 0, 0, "Can't find! Please enter another date!", 1);
				}

				returnTomenu();
				break;

			case 2:
				//Sortering av varmast till kallaste dagen
				system("CLS");//Clearing the Screen

				//call the sort function
				mergeSortTemperature(arrIn, 0, 129);

				//call the print function
				printOut(arrIn, 0, 5, "-Varmast dagen:", 0);
				//call the print function
				printOut(arrIn, 129, 124, "-Kallaste dagen:", 1);

				returnTomenu();
				break;
			case 3:
				// sorting by humidity
				system("CLS");//Clearing the Screen

				mergeSortHumidity(arrIn, 0, 129);
				//call the print function
				printOut(arrIn, 0, 5, "-torrast till fuktigaste:", 0);
				//call the print function
				printOut(arrIn, 129, 124, "-fuktigaste till  torrast:", 1);

				returnTomenu();
				break;

			case 4:
				//sorting by mogelIndex
				system("CLS");//Clearing the Screen
				mergeSortMog(arrIn, 0, 129);

				//call the print function
				printOut(arrIn, 0, 5, "-minst till stِrst risk av mِgel:", 0);
				//call the print function
				printOut(arrIn, 129, 124, "-stِrst till minst risk av mِgel:", 1);

				//printOut(arrIn, 0,130, "Sortering av minst till stِrst risk av mِgel");
				returnTomenu();
				break;
			case 5:
				//print out doors information
				system("CLS");//Clearing the Screen
				cout << "\n\tEnter the date [YYYYMMDD] to view the details:";
				inputDate = checkInput();
				cout << endl << endl;

				//search
				for (int i = 0; i < 164444; i++)
				{

					if (inputDate == arrAllIn[i].date)
					{
						while (i != 164444)
						{
							//check the difference between current  temperatureand the next
							*pN = arrAllIn[i].temperature - arrAllIn[i + 1].temperature;

							//if the difference is more than 0,3 degrees that's mean is something happened and caused this 
							//big difference in temperature 
							if (*pN >= 0.3 && i != 164444)
							{
								doorCounter++;
								minute++;
								sumMinute++;

								cout << arrAllIn[i].date << "   " << arrAllIn[i].time << "   " << arrAllIn[i].temperature << endl;
								cout << arrAllIn[i + 1].date << "   " << arrAllIn[i + 1].time << "   " << arrAllIn[i + 1].temperature << endl;

								i++;
								*pN = (arrAllIn[i].temperature) - (arrAllIn[i + 1].temperature);

								//until the temperature get stabile
								while (*pN >= 0.01 && i != 164444)
								{
									minute++;
									sumMinute++;
									cout << arrAllIn[i + 1].date << "   " << arrAllIn[i + 1].time << "   " << arrAllIn[i + 1].temperature << endl;

									i++;
									*pN = arrAllIn[i].temperature - arrAllIn[i + 1].temperature;
								}

								cout << "--------------------------[" << minute << " min]" << endl;
								minute = 0;
							}

							today = arrAllIn[i].date;
							if (inputDate != today)
							{
								//bring the index number for the inputs date from arrOut
								index = binarySearch(arrOut, 0, 129, inputDate);
								cout << "........................................................................................" << endl;
								cout << "The door opened: " << doorCounter << " times for [" << sumMinute << "] minutes and avregeTempIn["
									<< roundf(arrIn[index].temperature*100)/100 << "]  avregeTempOut[" << roundf(arrOut[index].temperature*100)/100 << "]" << endl;
								cout << "........................................................................................" << endl;

								doorCounter = 0;
								sumMinute = 0;

								//stop searching
								i = 164444;
								break;
							}

							i++;
						}

					}
				}
				returnTomenu();
				break;
			
			break;
			case 6:
				//sorting by longest time the balcony door was opened
				system("CLS");//Clearing the Screen
				//call sort function
				mergeSortDoor(arrIn, 0, 129);
				//call the print function
				printOutIN(arrIn, 129, 124, "-Längst tid för öppning dörren :", 1);

				returnTomenu();
				break;

		case 7:
			
			break;
		default:
			cout << "your choice is not ixest" << endl;
			returnTomenu();
			break;
		}
		break;

		case 2:
			cout << "\n\t[Utomhus]\n";

			cout << "\t\tvنlj: " << endl;
			cout << "\t\t   [1] Medeltemperatur fِr valt datum" << endl;
			cout << "\t\t   [2] Sortering av varmast till kallaste dagen" << endl;
			cout << "\t\t   [3] Sortering av torrast till fuktigaste dagen" << endl;
			cout << "\t\t   [4] Sortering av minst till stِrst risk av mِgel" << endl;
			cout << "\t\t   [5] Datum för meteorologisk Hِst" << endl;
			cout << "\t\t   [6] Datum för meteorologisk Vinter" << endl;
			cout << "\t\t   [7] Back to main menu" << endl;

			choice3 = checkInput();
			switch (choice3)
			{
				//int index;
			case 1:
				//sort by date
				mergeSortDate(arrOut, 0, 129);
				system("CLS");//Clearing the Screen
				cout << "\n\tEnter the date [YYYYMMDD] to view the details:";
				inputDate = checkInput();
				//call the search function
				index = binarySearch(arrOut, 0, 129, inputDate);

				if (index != -1)
				{
					//call the print function
					printOut(arrOut, index, index + 1, "-Medeltemperatur:", 1);
				}
				else
				{
					printOut(arrOut, 0, 0, "Can't find! Please enter another date!", 1);
					//cout << "Can't find [" << inputDate << "] Please enter another date!  " << endl;
				}				

				returnTomenu();
				break;

			case 2:

				//Sortering av varmast till kallaste dagen
				system("CLS");//Clearing the Screen

				//call the sort function
				mergeSortTemperature(arrOut, 0, 129);

				//call the print function
				printOut(arrOut, 0, 5, "-Varmast dagen:", 0);
				//call the print function
				printOut(arrOut, 129, 124, "-Kallaste dagen:", 1);

				returnTomenu();
				break;

			case 3:
				// sorting by humidity
				system("CLS");//Clearing the Screen

				mergeSortHumidity(arrOut, 0, 129);
				//call the print function
				printOut(arrOut, 0, 5, "-torrast till fuktigaste:", 0);
				//call the print function
				printOut(arrOut, 129, 124, "-fuktigaste till  torrast:", 1);

				returnTomenu();
				break;

			case 4:
				//sorting by mogelIndex
				system("CLS");//Clearing the Screen
				mergeSortMog(arrOut, 0, 129);

				//call the print function
				printOut(arrOut, 0, 5, "-minst till störst risk av mögel:", 0);
				//call the print function
				printOut(arrOut, 129, 124, "-störst till minst risk av mögel:", 1);

				returnTomenu();
				break;
			case 5:
				//Algorithm for Meteorological Autumn
				system("CLS");//Clearing the Screen
				//sort by date
				mergeSortDate(arrOut, 0, 129);
				for (int i = 0; i < 130 - 5; i++)
				{
					if (arrOut[i].temperature < 10 && arrOut[i].temperature >= 0)
					{
						if (arrOut[i].temperature > arrOut[i + 1].temperature)
						{
							i++;
							if (arrOut[i].temperature > arrOut[i + 1].temperature)
							{
								i++;
								if (arrOut[i].temperature > arrOut[i + 1].temperature)
								{
									i++;
									if (arrOut[i].temperature > arrOut[i + 1].temperature)
									{
										cout << "\n\t\tDatum fِr meteorologisk hِst نr : " << arrOut[i - 3].date << endl;
										break;
									}
								}

							}
						}
					}
					if (i==124)
					{
						cout << "\t\tNo autumn this year!" << endl;
					}
				}
				
				returnTomenu();
				break;
			case 6:
				//Algorithm for meteorological winter
				system("CLS");//Clearing the Screen
				//sort by date
				mergeSortDate(arrOut, 0, 129);

				for (int i = 0; i < 130 - 5; i++)
				{
					if (arrOut[i].temperature < 0)
					{
						if (arrOut[i + 1].temperature < 0)
						{
							i++;
							if (arrOut[i + 1].temperature < 0)
							{
								i++;
								if (arrOut[i + 1].temperature < 0)
								{
									i++;
									if (arrOut[i + 1].temperature < 0)
									{

										cout << "\n\t\tVinter: " << arrOut[i - 3].date << endl;
										break;//don't continue search
									}
								}

							}
						}
					}
					if (i == 124)
					{
						cout << "\t\tNo winter this year!" << endl;
					}
				}
				
				returnTomenu();
				break;
			case 7:
				break;

			default:
				cout << "your choice is not ixest" << endl;
				returnTomenu();
				break;
			}
			break;
		case 3:
			//find the bigger and the smallest difference between insides and outsides temperature

			//sort by date
			mergeSortDate(arrIn, 0, 129);
			mergeSortDate(arrOut, 0, 129);

			//find the differences and save the results
			for (int i = 0; i < 130; i++)
			{
				if (arrIn[i].temperature > arrOut[i].temperature)
				{
					*pN = arrIn[i].temperature - arrOut[i].temperature;
				}
				else
				{
					*pN = arrOut[i].temperature - arrIn[i].temperature;
				}

				if (i == 0)
				{
					miniTemp = *pN;
					maxTemp = *pN;
				}

				if (*pN >= maxTemp)
				{
					maxTemp = *pN;
					indexMax = i;
				}
				if (*pN <= miniTemp)
				{
					miniTemp = *pN;
					indexMini = i;
				}

			}
			//print out the results
			cout << "\n\t[" << arrIn[indexMini].date << "] " << "  miniDiffTemp : " << miniTemp << "     tempOut = " << arrOut[indexMini].temperature << "    tempIn = " << arrIn[indexMini].temperature << endl;
			cout << "\n\t[" << arrIn[indexMax].date << "] " << "  maxDiffTemp  : " << maxTemp << "      tempOut = " << arrOut[indexMax].temperature << "     tempIn = " << arrIn[indexMax].temperature << endl;
			returnTomenu();
			break;
		case 4:
			//Exit
			loop = false;
			break;
		default:
			//If user enter a choice does not exist
			cout << "your choice is not ixest" << endl;
			returnTomenu();
			break;
		}
	}
	//rensa heap
	delete[]tempArr;
	delete[]arrIn;
	delete[]arrOut;
	delete[]arrAllIn;

}


