#ifndef PVC_H
#define PVC_H

#include <algorithm>
#include <ctime>
#include "Functions.h"

int random_number();
string second_player_guess(string msg, int& guess, int& player_number, int& player_turns, tuple<int, int>& cows_and_bulls);
string third_player_guess(int& player_number, int& player_turns, tuple<int, int>& cows_and_bulls);
void play_computer();

#endif