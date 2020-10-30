#ifndef MY_CLASSES_H
#define MY_CLASSES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>

using namespace std;

class Wordbase
{
protected:
	vector<string> words;
	string path;
public:
	Wordbase();

	void SetPath(string s);
	string GetPath();

	void Delete(int n);

	string Crypt(const string s) const;

	void ReadFile();
	void Restart();
};

class ChangeWordbase : public Wordbase
{
public:
	ChangeWordbase();
	void AddWord(string s);
	void ChangeWord(string old_s, string new_s);
	void DeleteWord(string s);
	vector<string>::iterator FindIterator(string s);
	void SaveFile();
	void ExportFile(string new_path);
	void ImportFile(string new_path);
	void Show() const;
};

class ScreenHangman
{
public:
	void PrintWord(string s, int n) const;
};

class Hangman : public Wordbase
{
	string current;
	string guess;
	int mistakes;
	ScreenHangman screen;
	string guess_letters;
public:
	Hangman();

	void AddGuessLetter(char ch);

	int GetMistakes();

	bool CheckMistakes();
	bool CheckWin();
	bool CheckWord(char ch);

	bool SetNewCurrent();

	void Print();
	void ShowGuessLetters();
	void ShowResult(double game_time);

	void Show();
};

class Timer
{
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
	std::chrono::time_point<clock_t> start_point;
public:
	Timer() :start_point(clock_t::now()) {}
	
	void ResetTimePoint() { start_point = clock_t::now(); }

	double Elapsed() const
	{
		return chrono::duration_cast<second_t>(clock_t::now() - start_point).count();
	}
};

#endif // !MY_CLASSES_H

