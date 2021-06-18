#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <tuple>
#include <string>
using namespace std;

static string file_name = "SavedGames.txt";

bool check_number(int number);
tuple<int, int> check_cows_and_bulls(int guess, int player_number);
void user_input(string input_msg, int& number);

#endif