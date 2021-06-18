#include "Player_vs_player.h"
#include "Player_vs_computer.h"

void main_menu();
int sub_menu();

int main()
{
	ios_base::sync_with_stdio(false);
	main_menu(); //��������� �� ��������� �� ������ ����.
}

void main_menu()
{
	system("CLS");
	cout << "Choose your option: \n"
		<< "1 -> Play against another player (PVP). \n"
		<< "2 -> Play against the computer. \n"
		<< "3 -> View previously played games. \n";

	int option;
	cin >> option;	//�������� �� ���� �� �������.

	switch (option)
	{
		case 1:
			system("CLS");
			if(check_for_continue() == "Start!") play_game(); //��� ���� ����������� ���� �� ������� ����.
			else continue_game(); //��� ��� ���������� ����, �� �� �� ����������.
			sub_menu(); //��������� �� ���������.
			break;

		case 2:
			system("CLS");
			play_computer(); //��������� �� ���� ����� ���������.
			sub_menu();
			break;

		case 3:
			system("CLS");
			read_saved_games(); //��������� �� �������� ����.
			sub_menu();
			break;
	}
}

int sub_menu()
{
	cout << "Return to menu(1) or exit the application(2)? ";
	int option;
	cin >> option;

	switch (option)
	{
		case 1:
			main_menu();
			break;

		case 2:
			return 0;
			break;
	}

	return 0;
}