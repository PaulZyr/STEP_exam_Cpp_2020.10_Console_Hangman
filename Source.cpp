#include "Header.h"
#include <iostream>

using namespace std;

void Welcome()
{
	cout << "\n\n     **************************\n"
		<< "     *   Welcome to HANGMAN.  *\n"
		<< "     *  --------------------  *\n"
		<< "     *       GOOD LUCK!       *\n"
		<< "     **************************\n\n";
}

void Menu()
{
	int q = -1;
	while (q != 0)
	{
		cout << "--- Main menu ---\n"
			<< " 1 - Play Game;\n"
			<< " 0 - Exit;\n";
		cin >> q; cin.ignore();
		switch (q)
		{
		case 1: PlayGame(); break;
		case 0: break;
		case 333: ChangeBase(); break;
		default: cout << "Wrong Input! Try better!\n";
		}
	}
}

void PlayGame()
{
	Hangman* hangman = new Hangman;
	Timer game_time;
	int q = -1;
	while (q != 0)
	{
		char ch;
		// play
		bool first = true, good_guess = false;;
		if (hangman->SetNewCurrent())
		{
			game_time.ResetTimePoint();
			while (hangman->CheckMistakes())
			{
				hangman->Print();
				if (!first)
				{
					cout << "Your last GUESS was ";
					if (good_guess) cout << "GOOD!\n";
					else cout << "BAD!\n";
					cout << "Your letters: ";
					hangman->ShowGuessLetters();
					cout << "\n";
				}
				else first = false;
				cout << "Mistakes: " << hangman->GetMistakes() << "\n";
				cout << "Your next letter: ";
				cin >> ch;
				ch = toupper(ch);
				hangman->AddGuessLetter(ch);
				good_guess = hangman->CheckWord(ch);

				if (!hangman->CheckMistakes() || hangman->CheckWin())
				{
					system("CLS");
					cout << "  ****************\n"
						<< "  *  GAME OVER!  *\n"
						<< "  ****************\n";
					hangman->ShowResult(game_time.Elapsed());
					break;
				}
			}
			// ask play again
			system("CLS");
			cout << "1 - Play again;\n"
				<< "0 - Return;\n";
			cin >> q; cin.ignore();
			switch (q)
			{
			case 1: break;
			case 0: break;
			default: cout << "Wrong Input! Try better!\n";
			}
		}
		else
		{
			cout << "Word List is EMPTY\n"
				<< "Do you want to reload ALL words again?\n"
				<< "Yes(1) or NO(0): ";
			cin >> q; cin.ignore();
			if (q == 1) hangman->Restart();
			else break;
		}
	}
}

void AddWord(ChangeWordbase* change)
{
	cout << "Input new word: ";
	string s;
	cin >> s;
	change->AddWord(s);
}
void ChangeWord(ChangeWordbase* change)
{
	cout << "Input word to change: ";
	string s_old, s_new;
	cin >> s_old;
	cout << "Input new word: ";
	cin >> s_new;
	change->ChangeWord(s_old, s_new);
}
void DeleteWord(ChangeWordbase* change)
{
	cout << "Input word to delete: ";
	string s;
	cin >> s;
	change->DeleteWord(s);
}
void ImportWordbase(ChangeWordbase* change)
{
	cout << "Input filepath to import: ";
	string s;
	cin >> s;
	change->ImportFile(s);
}
void ExportWordbase(ChangeWordbase* change)
{
	cout << "Input filepath to export: ";
	string s;
	cin >> s;
	change->ExportFile(s);
}

void ChangeBase()
{
	ChangeWordbase* change = new ChangeWordbase;
	int q = -1;
	while (q != 0)
	{
		cout << "   --- Change menu ---\n"
			<< " 1 - Add new word to the Wordbase\n"
			<< " 2 - Change WORD in the Wordbase\n"
			<< " 3 - Delete word from the Wordbase\n"
			<< " 4 - Show Wordbase\n"
			<< " 5 - Save Wordbase\n"
			<< " 6 - Import Wordbase\n"
			<< " 7 - Export Wordbase\n"
			<< " 0 - Return\n";
		cin >> q; cin.ignore();
		switch (q)
		{
		case 1: AddWord(change); break;
		case 2: ChangeWord(change); break;
		case 3: DeleteWord(change); break;
		case 4: change->Show(); break;
		case 5: change->SaveFile(); break;
		case 6: ImportWordbase(change);  break;
		case 7: ExportWordbase(change); break;
		case 0: break;
		default: cout << "Wrong Input! Try better!\n";
		}
	}
}