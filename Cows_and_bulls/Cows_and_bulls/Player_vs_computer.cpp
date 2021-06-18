#include "Player_vs_computer.h"

int random_number()	//Генериране на случайно число.
{
	int array_numbers[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	random_shuffle(begin(array_numbers), end(array_numbers));
	int final_array[4] = { array_numbers[0], array_numbers[1], array_numbers[2], array_numbers[3] };
	int number = 0;

	for (int& value : final_array) { number = 10 * number + value; }

	return number;
}

string second_player_guess(string msg, int& guess, int& player_number, int& player_turns, tuple<int, int>& cows_and_bulls)	//Служи за проверка дали потребителят печели.
{
	user_input(msg + " take your guess: ", guess);
	cows_and_bulls = check_cows_and_bulls(guess, player_number);	//Извква се функция за проверка на броя на cows и на bulls и се запазва в tuple.

	cout << msg + " Turn " << player_turns << " / Cows: " << get<0>(cows_and_bulls) << " Bulls: " << get<1>(cows_and_bulls);
	player_turns++;
	cout << "\n";

	if (get<1>(cows_and_bulls) == 4) { return "Wins!"; }
	else { return "Not!"; }
}

string third_player_guess(int& player_number, int& player_turns, tuple<int, int>& cows_and_bulls) //Служи за проверка дали компютърът печели.
{
	int guess = random_number();
	cows_and_bulls = check_cows_and_bulls(guess, player_number);

	cout << "Computer Turn " << player_turns << " / Cows: " << get<0>(cows_and_bulls) << " Bulls: " << get<1>(cows_and_bulls);
	player_turns++;
	cout << "\n";

	if (get<0>(cows_and_bulls) == 4) { return "Wins!"; }
	else { return "Not!"; }
}

void play_computer()	//Фукнцията, която се извиква при избор на игра срещу компютъра.
{
	ios_base::sync_with_stdio(false);

	srand((unsigned int)time(0));
	int player_number = 0, computer_number = 0, player_turns = 1, computer_turns = 1, guess = 0;
	tuple<int, int> cows_and_bulls;

	user_input("Please enter your secret number: ", player_number);
	computer_number = random_number();	//Тайното число на компютъра.

	while (get<1>(cows_and_bulls) != 4)	//Докато няма победител (4 bulls) се извикват и потребителя и компютъра да отгатват.
	{
		if (second_player_guess("Player", guess, computer_number, player_turns, cows_and_bulls) != "Not!")
		{
			cout << "The player wins! \n\n";
			break;
		}

		if (third_player_guess(player_number, computer_turns, cows_and_bulls) != "Not!")
		{
			cout << "The computer wins! \n\n";
			break;
		}
	}
}