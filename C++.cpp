 

#include <iostream>
#include <string>
using namespace std;
enum enChoice{Stone=1,Peper=2,Scissors=3};
enum enWinner{Player=1,Computer=2,Draw=3};
struct stRoundResults
{
	enChoice PlayerChoice;
	enChoice ComputerChoice;
	enWinner RoundWinner;
};
struct stGameResults
{
	short GameRounds;
	short PlayerWonTimes;
	short ComputerWonTimes;
	short DrawTimes;
	enWinner FinalWinner;
};
int RandomNumber(int From,int To)
{
	return rand() % (To - From + 1) + From;
}
enWinner CheckRoundWinner(stRoundResults RoundResults)
{
	if (RoundResults.ComputerChoice == RoundResults.PlayerChoice)
		return enWinner::Draw;
	
	switch (RoundResults.PlayerChoice)
	{
	case enChoice::Peper:
		if (RoundResults.ComputerChoice == enChoice::Scissors)
			return enWinner::Computer;
		else
			return enWinner::Player;
		break;
	case enChoice::Scissors:
		if (RoundResults.ComputerChoice == enChoice::Peper)
			return enWinner::Player;
		else
			return enWinner::Computer;
		break;
	case enChoice::Stone:
		if (RoundResults.ComputerChoice == enChoice::Peper)
			return enWinner::Computer;
		else
			enWinner::Player;
		break;
	}
	
}
void GetRoundResults(short Choice,stRoundResults& Results)
{
	Results.ComputerChoice = (enChoice)RandomNumber(1,3);
	Results.PlayerChoice = (enChoice)Choice;
	Results.RoundWinner = CheckRoundWinner(Results);
}
string GetPlayerChoice(stRoundResults Results)
{
	if (Results.PlayerChoice == Stone)
		return "Stone";
	else if (Results.PlayerChoice == Peper)
		return "Paper";
	else
		return "Scissors";
}
string GetComputerChoice(stRoundResults Results)
{
	if (Results.ComputerChoice == Peper)
		return "Paper";
	else if (Results.ComputerChoice == Stone)
		return "Stone";
	else
		return "Scissors";
}
string GetRoundWinner(stRoundResults Results) 
{
	if (Results.RoundWinner == Computer)
		return "Computer";
	else if (Results.RoundWinner == Player)
		return "Player";
	else
		return "Draw";
}
void ShowRoundResults(short RoundNumber,stRoundResults Results)
{
	cout  << endl;
	cout << "------------ Round [" << RoundNumber << "] ------------\n";
	cout << "Player Choice:" << GetPlayerChoice(Results) << "\n";
	cout << "Computer Choice:" << GetComputerChoice(Results) << "\n";
	cout << "Round Winner:" << GetRoundWinner(Results) << "\n";
	cout << "------------------------------------\n";
}
void PlayRound(int RoundNumber,stRoundResults& Results)
{
	short Choice;
	do
	{
		cout << endl;
		cout << "Round [" << RoundNumber << "] begins:\n";
		cout << "Your choice [1]Stone ,[2]Paper ,[3]Scissors?\n";
		cin >> Choice;
	} while (Choice < 1 || Choice>3);
	GetRoundResults(Choice, Results);
}
short AskHowManyRounds()
{
	short Rounds;
	do {
		cout << "How many Rounds you want to play?[1-10]\n";
		cin >> Rounds;
	} while (Rounds>10||Rounds<1);
	return Rounds;
}
void ShowGameOverScreen()
{
	cout << "\n\n---------------------------------------\n";
	cout << "\t\t\t+++ GAME OVER +++\t\t\t\n";
	cout << "---------------------------------------\n";
}
enWinner GetFinalWinner(stGameResults Results)
{
	if (Results.ComputerWonTimes == Results.PlayerWonTimes)
		return enWinner::Draw;
	else if (Results.ComputerWonTimes > Results.PlayerWonTimes)
		return enWinner::Computer;
	else
		return enWinner::Player;
}
string GetFinalWinnerName(stGameResults Results)
{
	if (Results.ComputerWonTimes == Results.PlayerWonTimes)
		return "No One";
	else if (Results.ComputerWonTimes > Results.PlayerWonTimes)
		return "Computer";
	else
		return"Player";
}
stGameResults CalculateGameResults(short GameRounds,short DrawTimes,short ComputerWinTimes,short PlayerWinTimes)
{
	stGameResults Results;
	Results.ComputerWonTimes = ComputerWinTimes;
	Results.DrawTimes = DrawTimes;
	Results.PlayerWonTimes = PlayerWinTimes;
	Results.GameRounds = GameRounds;
	Results.FinalWinner = GetFinalWinner(Results);
	return Results;
}
void ShowGameResultsScreen(stGameResults Results)
{
	cout << "\n--------------[GAME RESULTS]--------------\n";
	cout << "Game Rounds:" << Results.GameRounds << endl;
	cout << "Player Won Times:" << Results.PlayerWonTimes << endl;
	cout << "Computer Won Times:" << Results.ComputerWonTimes << endl;
	cout << "Draw Times:" << Results.DrawTimes << endl;
	cout << "Final Winner:" << GetFinalWinnerName(Results) << endl;
	cout << "------------------------------------------\n";
	if (GetFinalWinner(Results) == Draw)
		system("color 6F");
	else if (GetFinalWinner(Results) == Player)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
		

}
void StartGame()
{
	bool WantToPlayAgain = true;
	short Rounds = 0;
	short DrawTimes = 0, ComputerWinTimes = 0, PlayerWinTimes = 0;
	stRoundResults RoundResults;
	stGameResults GameResults;
	do
	{
		Rounds = AskHowManyRounds();
		for (int i = 1;i <= Rounds;i++)
		{
			PlayRound(i, RoundResults);
			ShowRoundResults(i, RoundResults);
			if (RoundResults.RoundWinner == Draw)
			{
				DrawTimes++;
				system("color 6F");
			}
			else if (RoundResults.RoundWinner == Computer)
			{
				ComputerWinTimes++;
				system("color 4F");
				cout << "\a";
			}
				
			else
			{
				PlayerWinTimes++;
				system("color 2F");
			}
				
		}
		GameResults = CalculateGameResults(Rounds,DrawTimes,ComputerWinTimes,PlayerWinTimes);
		ShowGameOverScreen();
		ShowGameResultsScreen(GameResults);
		cout << endl;
		cout << "Do you want to play again? [1]Yes ,[2]No\n";
		cin >> WantToPlayAgain;

		//clear the screen
		system("cls");
		system("color 0F");
	} while (WantToPlayAgain==1);
}
int main()
{
	 
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}

 