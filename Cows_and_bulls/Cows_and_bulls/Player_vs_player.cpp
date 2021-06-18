#include "Player_vs_player.h"

string end_of_game = "End of game! \n\n";
string player1_wins = "Player 1 wins! \n\n";
string player2_wins = "Player 2 wins! \n\n";
string player1 = "Player 1";
string player2 = "Player 2";
string secret1 = "Player 1 secret number: ";
string secret2 = "Player 2 secret number: ";
string p1_secret = "Player 1 secret";
string p2_secret = "Player 2 secret";
string p2_enter = "Player 2, please enter your secret number: ";
string not1 = "Not!";

void read_saved_games()	//Служи за показване на изиграните игри.
{
	string line;
	ifstream file(file_name);

	if (file.is_open())
	{
		while (getline(file, line)) { cout << line << '\n'; }
		file.close();
	}

	else { "There was a problem when reading from file!"; }
}

void write_saved_games(string msg)	//Служи за запазване на информация за игрите.
{
	ofstream file(file_name, ios::app);

	if (file.is_open()) { file << msg; }
	else { "There was a problem when writing to file!"; }

	file.close();
}

string check_for_continue() //Проверка дали предишната игра е завършена (ако не е, то тя се продължава).
{
	string line;
	int count_first = 0, count_last = 0;
	ifstream file(file_name);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line == "------------------------------------------------------------------------- ") { count_first++; }	// Служи за да се провери дали
			else if (line == "End of game! ") { count_last++; }																// последната игра е завършена.
		}

		file.close();
	}

	if (count_first == count_last) { return "Start!"; }
	else { return "Continue!"; }
}

string player_guess(string msg, int& guess, int& player_number, int& player_turns, tuple<int, int>& cows_and_bulls) //Функцията, която се вика когато някой от играчите трябва да отгатва.
{
	string line;
	user_input(msg + " take your guess: ", guess);	//Въвеждане на числото.
	cows_and_bulls = check_cows_and_bulls(guess, player_number);	//Изчисляване на cows и на bulls.

	line = msg + " Turn " + to_string(player_turns) + " / Cows: " + to_string(get<0>(cows_and_bulls)) + " Bulls: " + to_string(get<1>(cows_and_bulls));	//Извеждане на информацията за cows и аз bulls.
	cout << line;
	write_saved_games(line);

	line = "\n";
	cout << line;
	write_saved_games(line);
	player_turns++;	//Редът на играча се обновява.

	if (get<1>(cows_and_bulls) == 4) { return "Wins!"; }	//Ако bulls = 4 то играчът печели.
	else { return not1; }
}

void main_logic(int& guess, int& player1_number, int& player2_number, int& player1_turns, int& player2_turns, tuple<int, int>& cows_and_bulls)	//Главната функция за играта.
{
	string line;

	while (get<1>(cows_and_bulls) != 4) //Докато няма победител (4 bulls) се извикват и двата играча да отгатват.
	{
		if (player_guess(player1, guess, player2_number, player1_turns, cows_and_bulls) != not1)
		{
			cout << player1_wins;	//Извежда се играчът победител.
			write_saved_games(player1_wins);	//Запазва се победителят.
			break;
		}

		if (player_guess(player2, guess, player1_number, player2_turns, cows_and_bulls) != not1)
		{
			cout << player2_wins;
			write_saved_games(player2_wins);
			break;
		}
	}
}

void play_game()	//Функцията за нова игра.
{
	int player1_number = 0, player2_number = 0, player1_turns = 1, player2_turns = 1, guess = 0;
	tuple<int, int> cows_and_bulls;
	time_t get_time = time(0);
	struct tm current_time;
	localtime_s(&current_time, &get_time);
	string line;

	user_input("Player 1, please enter your secret number: ", player1_number);	//Играч 1 въвежда своето тайно число.
	system("CLS");

	line = "------------------------------------------------------------------------- \n\n";
	write_saved_games(line);

	line = string("Time: ") + to_string(1900 + current_time.tm_year)	//Времето, когато е започната играта.
		+ string(" / ") + to_string(current_time.tm_mon)
		+ string(" / ") + to_string(current_time.tm_mday)
		+ string(" / ") + to_string(current_time.tm_hour) + string(":") + to_string(current_time.tm_min) + string(":") + to_string(current_time.tm_sec) + string("\n\n");

	write_saved_games(line);	//Запазване на времето във файла.

	line = secret1 + to_string(player1_number) + string("\n");
	write_saved_games(line); 	//Запазва се тайното число на играча във файла.

	user_input(p2_enter, player2_number); //Играч 2 въвежда своето тайно число.
	system("CLS");

	line = secret2 + to_string(player2_number) + string("\n");
	write_saved_games(line);	//Запазва се тайното число на играча във файла.

	line = "\n";
	write_saved_games(line);

	main_logic(guess, player1_number, player2_number, player1_turns, player2_turns, cows_and_bulls);	//Извикване на главната функцията.

	write_saved_games(end_of_game);	//Запазва се ред показващ края на играта.
}

void continue_game()	//Функцията за продължаване на играта.
{
	int player1_number = 0, player2_number = 0, player1_turns = 1, player2_turns = 1, guess = 0;
	string line;
	vector<string> lines;	//Вектор за запазване на редовете на файла за игрите.
	tuple<int, int> cows_and_bulls;
	ifstream file(file_name);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (!line.empty())
			{
				if (line.substr(0, 15) == p1_secret) { player1_number = stoi(line.substr(24, 27)); }	//Задаване на тайното число за играч 1.
				if (line.substr(0, 15) == p2_secret) { player2_number = stoi(line.substr(24, 27)); }	//Задаване на тайното число за играч 2.
				lines.emplace_back(line + "\n");
			}

		}
		file.close();
	}

	line = lines.back();	//Последният ред на файла.

	if (line.substr(0, 15) == p1_secret)	//Ако е въведено само тайното число на играч 1.
	{
		player2_number = 0;

		user_input(p2_enter, player2_number);
		system("CLS");

		line = secret2 + to_string(player2_number);
		write_saved_games(line);

		line = "\n";
		write_saved_games(line);

		main_logic(guess, player1_number, player2_number, player1_turns, player2_turns, cows_and_bulls);

		write_saved_games(end_of_game);
	}

	if (line.substr(0, 15) == p2_secret)	//Ако са въведени тайните числа и на двата играча.
	{
		line = "\n";
		write_saved_games(line);

		main_logic(guess, player1_number, player2_number, player1_turns, player2_turns, cows_and_bulls);

		write_saved_games(end_of_game);
	}

	if (line.substr(0, 13) == "Player 1 Turn")	//Ако последно играч 1 е отгатвал.
	{
		player1_turns = (line.at(14) - '0') + 1;	//Изчисляване на редът на играч 1.
		player2_turns = player1_turns;	//Изчисляване на редът на играч 2.

		while (get<1>(cows_and_bulls) != 4)
		{
			if (player_guess(player2, guess, player1_number, player2_turns, cows_and_bulls) != not1)
			{
				cout << player2_wins;
				write_saved_games(player2_wins);
				break;
			}

			if (player_guess(player1, guess, player2_number, player1_turns, cows_and_bulls) != not1)
			{
				cout << player1_wins;
				write_saved_games(player1_wins);
				break;
			}
		}

		write_saved_games(end_of_game);

	}

	if (line.substr(0, 13) == "Player 2 Turn")	//Ако последно играч 2 е отгатвал.
	{
		player2_turns = (line.at(14) - '0') + 1;
		player1_turns = player2_turns;

		main_logic(guess, player1_number, player2_number, player1_turns, player2_turns, cows_and_bulls);	

		write_saved_games(end_of_game);
	}
}