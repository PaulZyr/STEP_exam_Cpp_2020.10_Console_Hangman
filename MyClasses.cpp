#include "MyClasses.h"

// ----- Wordbase -----

Wordbase::Wordbase()
{
	path = "words.wrd";
	ReadFile();
}

void Wordbase::SetPath(string s) { path = s; }
string Wordbase::GetPath() { return path; }

void Wordbase::Delete(int n)
{
	words.erase(words.begin() + n);
}

string Wordbase::Crypt(const string s) const
{
	string tmp = "";
	for (auto c : s) { tmp += c ^ 5; }
	return tmp;
}

void Wordbase::ReadFile()
{
	fstream fin;
	fin.open(path, ios_base::in);
	if (fin.is_open())
	{
		string tmp;
		getline(fin, tmp);
		if (tmp == "$WORDS")
		{
			while (tmp != "#WORDS")
			{
				getline(fin, tmp);
				if (tmp != "#WORDS")
					words.push_back(Crypt(tmp)); //Crypt(tmp)

			}
		}
		else cout << "Wordbase file incorrect!\n";
		fin.close();
	}
	else cout << "No DATABASE!\nCheck file OR Create the New one!\n";
}

void Wordbase::Restart()
{
	words.clear();
	ReadFile();
}

// ----- ChangeWordbase -----

ChangeWordbase::ChangeWordbase() : Wordbase() {}
void ChangeWordbase::AddWord(string s)
{
	if (s.size() >= 25)
		cout << "Too long word!\nCan't add to base!\n";
	else if (s.size() < 7) cout << "Too short word!\nCan't add to base!\n";
	else words.push_back(s);
}
void ChangeWordbase::ChangeWord(string old_s, string new_s)
{
	auto it = FindIterator(old_s);
	if (it != words.end()) *it = new_s;
	else cout << "No such word in the Wordbase!\n";
}
void ChangeWordbase::DeleteWord(string s)
{
	auto it = FindIterator(s);
	if (it != words.end()) words.erase(it);
	else cout << "No such word in the Wordbase!\n";
}
vector<string>::iterator ChangeWordbase::FindIterator(string s)
{
	auto it = words.begin();
	while (it != words.end())
	{
		if (*it == s) return it;
		it++;
	}
	return it;
}
void ChangeWordbase::SaveFile()
{
	fstream fout;
	fout.open(path, ios_base::out);
	fout << "$WORDS" << "\n";
	for (auto w : words)
	{
		fout << Crypt(w) << "\n";
	}
	fout << "#WORDS" << "\n";
	fout.close();
}
void ChangeWordbase::ExportFile(string new_path)
{
	fstream fout;
	fout.open(new_path, ios_base::out);
	fout << "$WORDS" << "\n";
	for (auto w : words)
	{
		fout << w << "\n";
	}
	fout << "#WORDS" << "\n";
	fout.close();
}
void ChangeWordbase::ImportFile(string new_path)
{
	fstream fin;
	fin.open(new_path, ios_base::in);
	if (fin.is_open())
	{
		words.clear();
		string tmp;
		getline(fin, tmp);
		if (tmp == "$WORDS")
		{
			while (tmp != "#WORDS")
			{
				getline(fin, tmp);
				if (tmp != "#WORDS")
					words.push_back(tmp); //Crypt(tmp)

			}
		}
		else cout << "Wordbase file incorrect!\n";
		fin.close();
	}
	else cout << "No DATABASE!\nCheck file OR Create the New one!\n";
}
void ChangeWordbase::Show() const
{
	for (auto w : words) cout << w << " ";
	cout << "\n";
}

// ----- ScreenHangman -----

void ScreenHangman::PrintWord(string s, int n) const
{
	system("CLS");
	int size = s.size() + 6;
	if (size < 15) size = 15;
	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (i == 0 || i == 14 || i == 18) cout << '*';
			else if (j == 0 || j == size - 1) cout << '*';
			else if (i == 2 && (j >= 3 && j < 9)) cout << '=';
			else if ((i > 2 && i < 12) && j == 3) cout << "|";
			else if ((i == 3 || i == 4) && j == 8) cout << "|";
			else if (n > 0 && i == 5 && j == 8) cout << 'o';
			else if (n > 1 && i == 6 && j == 8) cout << "|";
			else if (n > 2 && i == 7 && j == 8) cout << "|";
			else if (n > 3 && i == 6 && j == 7) cout << '/';
			else if (n > 4 && i == 6 && j == 9) cout << '\\';
			else if (n > 5 && i == 8 && j == 7) cout << '/';
			else if (n > 6 && i == 8 && j == 9) cout << '\\';
			else if (i == 12 && (j >= 3 && j < 12)) cout << '=';
			else if (i == 16 && (j > 2 && j < s.size() + 3)) cout << s[j - 3];
			else cout << " ";
		}
		cout << "\n";
	}
}

// ----- Hangman -----

Hangman::Hangman() :Wordbase(), mistakes(0), guess_letters("") {}

void Hangman::AddGuessLetter(char ch)
{
	guess_letters += ch;
}

int Hangman::GetMistakes() { return mistakes; }

bool Hangman::CheckMistakes() { return mistakes < 7; }
bool Hangman::CheckWin()
{
	if (current == guess && mistakes < 7) return true;
	else return false;
}
bool Hangman::CheckWord(char ch)
{
	bool b = false;
	int size = current.size();
	for (int i = 0; i < size; ++i)
	{
		if (current[i] == ch)
		{
			guess[i] = ch;
			b = true;
		}
	}
	if (!b)
	{
		mistakes++;
		return false;
	}
	return true;
}

bool Hangman::SetNewCurrent()
{
	mistakes = 0;
	guess_letters = "";
	if (words.size() > 3)
	{
		srand(time(NULL));
		int n = rand() % (words.size() - 1) + 1;
		current = words[n];
		Delete(n);
		guess = "";
		for (int i = 0; i < current.size(); ++i) guess += ".";
		return true;
	}
	else if (words.size() < 3 && words.size() > 0)
	{
		current = words[0];
		Delete(0);
		guess = "";
		for (int i = 0; i < current.size(); ++i) guess += ".";
		return true;
	}
	else return false;
}

void Hangman::Print()
{
	screen.PrintWord(guess, mistakes);
}
void Hangman::ShowGuessLetters()
{
	for (auto ch : guess_letters) cout << ch;
}
void Hangman::ShowResult(double game_time)
{
	cout << " ----- Results -----\nYou ";
	if (CheckWin()) cout << "WIN!\n";
	else cout << "LOST!\n";
	cout << "Mistakes: " << mistakes << " of 7\n"
		<< "Original Word: " << current << "\n"
		<< "Your result:   " << guess << "\n"
		<< "All your guess letters: ";
	ShowGuessLetters();
	cout << "\nSpent time: " << game_time << " sec.\n";

	system("pause");
}

void Hangman::Show() // for testing
{
	cout << "--------------------\n";
	for (auto w : words)
		cout << w << " ";
	cout << "\n";
}