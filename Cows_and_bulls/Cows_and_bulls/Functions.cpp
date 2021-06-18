#include "Functions.h"

bool check_number(int number)	//Проверява дали въведеното число е правилно.
{
	if (number < 1000 || number > 9999)
	{
		cout << "The number was not bigger than 1000 or smaller than 9999. Try again! \n";
		return false;
	}

	else
	{
		int digits[4];
		int count_digits = 3;

		while (number > 0)				    //
		{                                   //
			int digit = number % 10;        // Разделяне на числото на цифри и записването им в масив.
			number /= 10;                   //
			digits[count_digits] = digit;   //
			count_digits--;                 //
		}									//

		for (int i = 0; i < 3; ++i)												//
		{																		//
			for (int j = i + 1; j < 4; ++j)										//				
			{																	//	
				if (digits[i] == digits[j])										//
				{																// Проверка за дупликати.
					cout << "There were duplicate numbers. Try again! \n";		//
					return false;												//			
				}																//
			}																	//	
		}																		//

		return true;
	}
}

tuple<int, int> check_cows_and_bulls(int guess, int player_number)	//Служи за изчисляване на cows и на bulls.
{
	int guess_digits[4];
	int player_number_digits[4];
	int count_guess_digits = 3, count_player_number_digits = 3, cows = 0, bulls = 0;

	while (guess > 0)
	{
		int digit = guess % 10;
		guess /= 10;
		guess_digits[count_guess_digits] = digit;
		count_guess_digits--;
	}

	while (player_number > 0)
	{
		int digit = player_number % 10;
		player_number /= 10;
		player_number_digits[count_player_number_digits] = digit;
		count_player_number_digits--;
	}

	for (int i = 0; i < 4; i++)													//
	{																			// Изчисляване на bulls.
		if (guess_digits[i] == player_number_digits[i]) { bulls++; }			//
	}																			//

	for (int i = 0; i < 4; ++i)															//
	{																					//
		for (int j = 0; j < 4; ++j)														//	
		{																				// Изчисляване на cows.
			if (guess_digits[i] == player_number_digits[j] && i != j) { cows++; }		//
		}																				//
	}																					//

	return make_tuple(cows, bulls);
}

void user_input(string input_msg, int& number) //Служи за въвеждане на информация от потребителя.
{
	cout << input_msg;
	cin >> number;

	while (check_number(number) == false)	//Проверява дали въведеното е коректно.
	{
		cout << input_msg;
		cin >> number;
	}
}