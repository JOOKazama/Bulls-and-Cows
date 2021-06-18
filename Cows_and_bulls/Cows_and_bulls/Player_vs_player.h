#ifndef PVP_H
#define PVP_H

#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "Functions.h"

void read_saved_games();
void write_saved_games(string msg);
string check_for_continue();
string player_guess(string msg, int& guess, int& player_number, int& player_turns, tuple<int, int>& cows_and_bulls);
void main_logic(int& guess, int& player1_number, int& player2_number, int& player1_turns, int& player2_turns, tuple<int, int>& cows_and_bulls);
void play_game();
void continue_game();

#endif