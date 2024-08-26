// Red here. I'm making my own version of the game Mastermind.
// TO DO comment everywhere lmao
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <array>

using namespace std;

int decision, hits, blows, turnCount, winCount, lossCount, cheatCheck = 0;
string answer, userAnswer, ap1, ap2, ap3, ap4, ap5, uap1, uap2, uap3, uap4, uap5;

void menu(){
  if(lossCount > 0 || winCount > 0){cout<<endl;}
  if(winCount  > 0){cout<< "Win Count: "<<winCount<<" ";}
  if(lossCount > 0){cout<<"Loss Count: "<<lossCount;}
  cout<<"\nPlease select an option.\n\t1 - Start Game with 4 Numbers\n\t2 - Start Game with 4 Numbers (Duplicates On)\n\t3 - Start Game with 5 Numbers\n\t4 - Start Game with 5 Numbers (Duplicates On)\n\t5 - How to Play\n\t6 - Exit\n\n\t\t> ";
  cin>>decision;
  if(decision >= 8 || decision <= 0 || cin.fail()){
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
	if(userAnswer.length() != 4 || cin.fail() || found != std::string::npos){
	  // TO DO fix crashing if letter
	  cin.clear();
	  cin.ignore(100, '\n');
	  turnCount--;
	  cout<<"\nError: That is not a four digit number.\n";
	}
	if(userAnswer == answer){
	  winCount++;
	  ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear();
	  cout<<"\nCongratulations! You've cracked the code!\n\t1 - Play Again\n\t2 - Return to Menu\n\n\t\t> ";
	  cin>>decision;
	  if(decision != 1 || decision != 2 || cin.fail()){// NO BITCH I DID NOT MEAN && THAT IS AN ENTIRELY DIFFERENT OPERATOR
		cin.clear();
		cin.ignore(100, '\n');
		answer.clear();
		userAnswer.clear();
		system("CLS");
		cout<<"\nError: That choice is unsupported. Returning to main menu.\n";
	  }
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
	  }
	}else{
	  turnCount++;
	  ap1.append(answer,0,1); ap2.append(answer,1,1); ap3.append(answer,2,1); ap4.append(answer,3,1);
	  uap1.append(userAnswer,0,1); uap2.append(userAnswer,1,1); uap3.append(userAnswer,2,1); uap4.append(userAnswer,3,1);
	  int repeatCheck = 0;
	  if(ap1.compare(uap1)   == 0){hits++;}else{
	    if(ap1.compare(uap2) == 0){blows++;  repeatCheck++;}
	    if(ap1.compare(uap3) == 0){blows++;  repeatCheck++;}
	    if(ap1.compare(uap4) == 0){blows++;  repeatCheck++;}
	    if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
	    repeatCheck = 0;
	  }
	  if(ap2.compare(uap2)   == 0){hits++;}else{
	    if(ap2.compare(uap1) == 0){blows++;  repeatCheck++;}
	    if(ap2.compare(uap3) == 0){blows++;  repeatCheck++;}
	    if(ap2.compare(uap4) == 0){blows++;  repeatCheck++;}
	    if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
	    repeatCheck = 0;
	  }
	  if(ap3.compare(uap3)   == 0){hits++;}else{
	    if(ap3.compare(uap1) == 0){blows++;  repeatCheck++;}
	    if(ap3.compare(uap2) == 0){blows++;  repeatCheck++;}
	    if(ap3.compare(uap4) == 0){blows++;  repeatCheck++;}
	    if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
	    repeatCheck = 0;
	  }
	  if(ap4.compare(uap4)   == 0){hits++;}else{
	    if(ap4.compare(uap1) == 0){blows++;  repeatCheck++;}
	    if(ap4.compare(uap2) == 0){blows++;  repeatCheck++;}
	    if(ap4.compare(uap3) == 0){blows++;  repeatCheck++;}
	    if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
	    repeatCheck = 0;
	  }
	  cout<<"\nIncorrect. "<<hits<<" Hits, "<<blows<<" Blows. "<<8 - turnCount<<" guesses remaining.";
	  hits  = 0;
	  blows = 0;
	  ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear();
	}
	if(turnCount == 8 && userAnswer != answer){
	  lossCount++;
	  ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear();
	  cout<<"\n\nYou were unable to guess the answer in time. Oh well!\n\t1 - Retry\n\t2 - Return to Menu\n\n\t\t> ";
	  cin>>decision;
	  if(decision != 1 || decision != 2 || cin.fail()){
		cin.clear();
		cin.ignore(100, '\n');
		answer.clear();
		userAnswer.clear();
		system("CLS");
		cout<<"\nError: That choice is unsupported. Returning to main menu.\n";
	  }
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
	  case 7:{// TO DO make this ultra hard mode for version 1.0?????
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
// i listened to an absurd amount of kero kero bonito while making this :,)