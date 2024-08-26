// Red here. I'm making my own version of the game Mastermind.

#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <array>

using namespace std;

int decision, hits, blows, turnCount, winCount, loseCount, cheatCheck = 1;
string answer, userAnswer;

void menu(){
  if(loseCount > 0 or winCount >0){cout<<endl;}
  if(winCount  > 0){cout<< "Win Count: "<<winCount<<" ";}
  if(loseCount > 0){cout<<"Lose Count: "<<loseCount;}
  cout<<"\nPlease select an option.\n\t1 - Start Game with 4 Numbers\n\t2 - Start Game with 4 Numbers (Duplicates On)\n\t3 - Start Game with 5 Numbers\n\t4 - Start Game with 5 Numbers (Duplicates On)\n\t5 - How to Play\n\t6 - Exit\n\n\t\t> ";
  cin>>decision;
  if(decision >= 8 or decision <= 0 or cin.fail()){
	cin.clear();
	cin.ignore(100, '\n');
	system("CLS");
	cout<<"\nError: That choice is unsupported.\n";
	menu();
  }
  system("CLS");
}

void gameA(){
  turnCount = 0;
  array<int, 10> x{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(x.begin(), x.end(), default_random_engine(seed));
  for (int& i: x)answer += to_string(i);
  answer.resize(4);
  
  system("CLS");
  if(cheatCheck == 1){cout<<"The answer is "<<answer<<".";}
  cout<<"\nType \"00\" to return to the menu.";
  do{
	cout<<"\n\nWhat is your guess?\n\n\t> ";
	cin>>userAnswer;
	if(userAnswer == "00"){
	  answer.clear();
	  userAnswer.clear();
	  system("CLS");
	  cout<<"\nWelcome to Red's Mastermind.\n";
	  break;
	}
	size_t found = userAnswer.find_first_not_of("1234567890");
	if(userAnswer.length() != 4 or cin.fail() or found != std::string::npos){	
	  cin.clear();
	  cin.ignore(100, '\n');
	  turnCount--;
	  cout<<"\nError: That is not a four digit number.\n";
	}
	if(userAnswer == answer){
	  cout<<"\nCongratulations! You've cracked the code!\n\t1 - Play Again\n\t2 - Return to Menu\n\t3 - Print Results\n\n\t\t> ";
	  winCount++;
	  cin>>decision;
	  switch(decision){
		case 1:{
		  answer.clear();
		  userAnswer.clear();
		  system("CLS");
		  gameA();
		  break;
		}
		case 2:{
		  answer.clear();
		  userAnswer.clear();
		  system("CLS");
		  cout<<"\nWelcome to Red's Mastermind.\n";
		  break;
		}
		case 3:{
		  answer.clear();
		  userAnswer.clear();
		  system("CLS");
		  cout<<"\nComing Soon!\n";
		  break;
		}
	  }
	}else{
	  turnCount++;
	  cout<<"\nIncorrect. "<<hits<<" Hits, "<<blows<<" Blows. "<<8 - turnCount<<" guesses remaining.";
	}
	if(turnCount == 8 && userAnswer != answer){
	  loseCount++;
	  cout<<"\n\nYou were unable to guess the answer in time. Oh well!\n\t1 - Retry\n\t2 - Return to Menu\n\t3 - Print Results\n\n\t\t> ";
	  cin>>decision;
	  switch(decision){
		case 1:{
		  answer.clear();
		  userAnswer.clear();
		  system("CLS");
		  gameA();
		  break;
		}
		case 2:{
		  answer.clear();
		  userAnswer.clear();
		  system("CLS");
		  cout<<"\nWelcome to Red's Mastermind.\n";
		  break;
		}
		case 3:{
		  answer.clear();
		  userAnswer.clear();
		  system("CLS");
		  cout<<"\nComing Soon!\n";
		  break;
		}
	  }
	}
  }while(answer != "");
}

int main(){
  cout<<"\nWelcome to Red's Mastermind.\n";
  do{
	menu();
	switch(decision){
	  case 1:{
		gameA();
		break;
	  }
	  case 2:{
		cout<<"\nTest!\n";
		break;
	  }
	  case 3:{
		cout<<"\nTest!\n";
		break;
	  }
	  case 4:{
		cout<<"\nTest!\n";
		break;
	  }
	  case 5:{
		cout<<"\nThe main goal of Mastermind is to guess my number. Each digit is from 0 to 9.\nIf duplicates are on, each number will only be duplicated once. You will get\n8 tries before the game ends. A \"Hit\" is when you have a digit and its spot\ncorrect in the answer. A \"Blow\" is when you have a correct digit in the wrong\nspot in the answer.\n";
		break;
	  }
	  case 6:{
		system("CLS");
		cout<<"\n\nThank you for playing!\n\nExiting...\n\n";
		return 0;
		break;
	  }
	  case 7:{
		if(cheatCheck == 0){
		  cout<<"\nCheat Show Answer: Enabled.\n";
		  cheatCheck++;
		}else{
		  cout<<"\nCheat Show Answer: Disabled.\n";
		  cheatCheck--;
		}
		break;
	  }
	}
  }while(answer.empty());
}