#include<iostream>
using namespace std;

enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stGameResults
{
	short NumberOfRounds;
	short PlayerWinTimes;
	short ComputerWinTimes;
	short DrawTimes;
	enWinner Winner;
	string WinnerName;

};
struct stRoundInfo
{
	short RoundNumber;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner RoundWinner;
	string WinnerName;
};

short RandomNumber(short From, short To)
{
	short RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}
short ReadHowManyRounds()
{
	short NumberOfRounds;

	do
	{
		cout << "How many rounds do you want to play from 1 to 10?";
		cin >> NumberOfRounds;
	} while (NumberOfRounds < 1 || NumberOfRounds>10);

	return NumberOfRounds;
}

enGameChoice PlayerChoice()
{
	int PlayerChoice;

	cout << "\nYour choice:[1]:Rock , [2]:Paper , [3]:Scissors?";
	cin >> PlayerChoice;
	cout << endl;

	return (enGameChoice)PlayerChoice;
}
enGameChoice ComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);

}
string ChoiceName(enGameChoice Choice)
{
	switch (Choice)
	{
	case enGameChoice::Rock:
		return "Rock";
	case enGameChoice::Paper:
		return "Paper";
	case enGameChoice::Scissors:
		return "Scissors";
	}
}
enWinner WhoWonTheRound(stRoundInfo Roundinfo)
{
	if (Roundinfo.PlayerChoice == Roundinfo.ComputerChoice)
		return enWinner::Draw;

	switch (Roundinfo.PlayerChoice)
	{
	case enGameChoice::Rock:
		if (Roundinfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (Roundinfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissors:
		if (Roundinfo.ComputerChoice == enGameChoice::Rock)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player;
}
enWinner WhoWonTheGame(stGameResults GameResults)
{
	if (GameResults.PlayerWinTimes > GameResults.ComputerWinTimes)
		return enWinner::Player;

	else if (GameResults.PlayerWinTimes < GameResults.ComputerWinTimes)
		return enWinner::Computer;

	else
		return enWinner::Draw;
}
string WinnerName(enWinner Winner)
{
	if (Winner == enWinner::Player)
		return "Player";
	else if (Winner == enWinner::Computer)
		return "Computer";
	else
		return "Draw";
}


void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	case enWinner::Draw:
		system("color 6F");
		break;
	}
}



void PrintRoundInfo(stRoundInfo RoundInfo)
{

	cout << "_______Round[" << RoundInfo.RoundNumber << "]__________\n";
	cout << "\nPlayer Choice:" << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice:" << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner:" << RoundInfo.WinnerName << endl;
	cout << "___________________________\n";

	SetWinnerScreenColor(RoundInfo.RoundWinner);

}

stGameResults FillGameResults(short NumberOfRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.NumberOfRounds = NumberOfRounds;
	GameResults.PlayerWinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.Winner = WhoWonTheGame(GameResults);
	GameResults.WinnerName = WinnerName(GameResults.Winner);

	return GameResults;
}

stGameResults PlayGame(short NumberOfRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;

	for (int RoundNumber = 1; RoundNumber <= NumberOfRounds; RoundNumber++)
	{
		cout << "\nRound[" << RoundNumber << "] begins\n";
		RoundInfo.RoundNumber = RoundNumber;
		RoundInfo.PlayerChoice = PlayerChoice();
		RoundInfo.ComputerChoice = ComputerChoice();
		RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enWinner::Player)
			PlayerWinTimes++;
		else if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundInfo(RoundInfo);
	}

	return FillGameResults(NumberOfRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);

}

string Tabs(short NumberOfTabs)
{
	string tabs = "";
	for (int i = 1; i <= NumberOfTabs; i++)
	{
		tabs = tabs = "\t";
	}
	return tabs;
}
void ShowGameOverScreen()
{
	cout << endl << Tabs(2) << "_________________________________________\n\n";
	cout << Tabs(2) << "            +++ G a m e  O v e r +++\n";
	cout << Tabs(2) << "_________________________________________\n\n";
}
void PrintGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "_______________________ [Game Results] _________________\n\n";
	cout << Tabs(2) << "Number Of Rounds:" << GameResults.NumberOfRounds << endl;
	cout << Tabs(2) << "Player Win Times:" << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer Win Times:" << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times:" << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Game Winner:" << GameResults.WinnerName << endl;
	cout << "____________________________________________________________\n\n";

	SetWinnerScreenColor(GameResults.Winner);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		PrintGameResults(GameResults);
		cout << "Do you want to play again? Y/N";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}