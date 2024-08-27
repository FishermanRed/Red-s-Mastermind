// Red here. I'm making my own version of the game Mastermind.
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <array>

using namespace std;

int decision, hits, blows, invalid, turnCount, winCount, lossCount, eCount, newCheck = 0, earlyCheck = 0, gAcheck = 0, gBcheck = 0, gCcheck = 0, gDcheck = 0, cheatCheck = 0;
string answer, userAnswer, ap1, ap2, ap3, ap4, ap5, uap1, uap2, uap3, uap4, uap5;

string makeUA(const int len){ //secondary random number gen, generates duplicates too
  static const char UA[] =
  "0123456789987654321001234567899876543210"
  "AAAAaaaaBBBBbbbbCCCCccccDDDDddddEEEEeeeeFFFFffff";
  string make;
  for (int i = 0; i < 25; ++i){
    make += UA[rand() % (sizeof(UA) - 1)];
  }
  return make;
}

void menu(){
  if(lossCount > 0 || winCount > 0){cout<<endl;}
  if(winCount  > 0){cout<<"Win Count: "<<winCount<<" ";}
  if(eCount    > 0){cout<<"Unfair Win Count: "<<eCount<<" ";}
  if(lossCount > 0){cout<<"Loss Count: "<<lossCount;}
  cout<<"\nPlease select an option.\n\t1 - Start Game with 4 Numbers\n\t2 - Start Game with 4 Numbers (Duplicates Enabled)\n\t3 - Start Game with 5 Numbers\n\t4 - Start Game with 5 Numbers (Duplicates Enabled)\n\t5 - How to Play\n\t6 - Exit\n";
  if(earlyCheck == 1 || gAcheck == 1 || gBcheck == 1 || gCcheck == 1 || gDcheck == 1){
    if(newCheck == 0){cout<<"\t7 - [NEW] Unfair Mode\n\t8 - [NEW] About Unfair Mode\n"; newCheck = 1;}
    else cout<<"\t7 - Unfair Mode\n\t8 - About Unfair Mode\n";
  }
  cout<<"\n\t\t> ";
  cin>>decision;
  if(decision >= 9 || decision < 0 || cin.fail()){
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
  array<int, 10> x{0,1,2,3,4,5,6,7,8,9};
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
      cin.clear();
      cin.ignore(100, '\n');
      turnCount--;
      cout<<"\nError: That is not a four digit number. ";
      invalid = 1;
    }
    if(userAnswer == answer){
      winCount++;
      gAcheck = 1;
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
      try{
        ap1.append(answer,0,1); ap2.append(answer,1,1); ap3.append(answer,2,1); ap4.append(answer,3,1);
        uap1.append(userAnswer,0,1); uap2.append(userAnswer,1,1); uap3.append(userAnswer,2,1); uap4.append(userAnswer,3,1);
      }catch(const out_of_range& oor){}
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
      if(invalid == 1){cout<<8 - turnCount<<" guesses remaining."; invalid = 0;}
      else{cout<<"\nIncorrect. "<<hits<<" Hits, "<<blows<<" Blows. "<<8 - turnCount<<" guesses remaining.";}
      hits  = 0;
      blows = 0;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear();
    }
    if(turnCount == 8 && userAnswer != answer){
      lossCount++;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear();
      cout<<"\n\nYou were unable to guess the answer in time. Oh well!\nThe answer was "<<answer<<"\n\n\t1 - Retry\n\t2 - Return to Menu\n\n\t\t> ";
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

void gameB(){
  turnCount = 0;
  array<int, 20> x{0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
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
      cin.clear();
      cin.ignore(100, '\n');
      turnCount--;
      cout<<"\nError: That is not a four digit number. ";
      invalid = 1;
    }
    if(userAnswer == answer){
      winCount++;
      gBcheck = 1;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear();
      cout<<"\nCongratulations! You've cracked the code!\n\t1 - Play Again\n\t2 - Return to Menu\n\n\t\t> ";
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
          gameB();
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
      try{
        ap1.append(answer,0,1); ap2.append(answer,1,1); ap3.append(answer,2,1); ap4.append(answer,3,1);
        uap1.append(userAnswer,0,1); uap2.append(userAnswer,1,1); uap3.append(userAnswer,2,1); uap4.append(userAnswer,3,1);
      }catch(const out_of_range& oor){}
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
      if(invalid == 1){cout<<8 - turnCount<<" guesses remaining."; invalid = 0;}
      else{cout<<"\nIncorrect. "<<hits<<" Hits, "<<blows<<" Blows. "<<8 - turnCount<<" guesses remaining.";}
      hits  = 0;
      blows = 0;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear();
    }
    if(turnCount == 8 && userAnswer != answer){
      lossCount++;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear();
      cout<<"\n\nYou were unable to guess the answer in time. Oh well!\nThe answer was "<<answer<<"\n\n\t1 - Retry\n\t2 - Return to Menu\n\n\t\t> ";
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

void gameC(){
  turnCount = 0;
  array<int, 10> x{0,1,2,3,4,5,6,7,8,9};
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(x.begin(), x.end(), default_random_engine(seed));
  for (int& i: x)answer += to_string(i);
  answer.resize(5);
  
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
    if(userAnswer.length() != 5 || cin.fail() || found != std::string::npos){
      cin.clear();
      cin.ignore(100, '\n');
      turnCount--;
      cout<<"\nError: That is not a five digit number. ";
      invalid = 1;
    }
    if(userAnswer == answer){
      winCount++;
      gCcheck = 1;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); ap5.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear(); uap5.clear();
      cout<<"\nCongratulations! You've cracked the code!\n\t1 - Play Again\n\t2 - Return to Menu\n\n\t\t> ";
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
          gameC();
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
      try{
        ap1.append(answer,0,1); ap2.append(answer,1,1); ap3.append(answer,2,1); ap4.append(answer,3,1); ap5.append(answer,4,1);
        uap1.append(userAnswer,0,1); uap2.append(userAnswer,1,1); uap3.append(userAnswer,2,1); uap4.append(userAnswer,3,1); uap5.append(userAnswer,4,1);
      }catch(const out_of_range& oor){}
      int repeatCheck = 0;
      if(ap1.compare(uap1)   == 0){hits++;}else{
        if(ap1.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap1.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap1.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(ap1.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap2.compare(uap2)   == 0){hits++;}else{
        if(ap2.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap2.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap2.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(ap2.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap3.compare(uap3)   == 0){hits++;}else{
        if(ap3.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap3.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap3.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(ap3.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap4.compare(uap4)   == 0){hits++;}else{
        if(ap4.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap4.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap4.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap4.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap5.compare(uap5)   == 0){hits++;}else{
        if(ap5.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap5.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap5.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap5.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(invalid == 1){cout<<8 - turnCount<<" guesses remaining."; invalid = 0;}
      else{cout<<"\nIncorrect. "<<hits<<" Hits, "<<blows<<" Blows. "<<8 - turnCount<<" guesses remaining.";}
      hits  = 0;
      blows = 0;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); ap5.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear(); uap5.clear();
    }
    if(turnCount == 8 && userAnswer != answer){
      lossCount++;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); ap5.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear(); uap5.clear();
      cout<<"\n\nYou were unable to guess the answer in time. Oh well!\nThe answer was "<<answer<<"\n\n\t1 - Retry\n\t2 - Return to Menu\n\n\t\t> ";
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

void gameD(){
  turnCount = 0;
  array<int, 20> x{0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  shuffle(x.begin(), x.end(), default_random_engine(seed));
  for (int& i: x)answer += to_string(i);
  answer.resize(5);
  
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
    if(userAnswer.length() != 5 || cin.fail() || found != std::string::npos){
      cin.clear();
      cin.ignore(100, '\n');
      turnCount--;
      cout<<"\nError: That is not a five digit number. ";
      invalid = 1;
    }
    if(userAnswer == answer){
      winCount++;
      gDcheck = 1;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); ap5.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear(); uap5.clear();
      cout<<"\nCongratulations! You've cracked the code!\n\t1 - Play Again\n\t2 - Return to Menu\n\n\t\t> ";
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
          gameD();
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
      try{
        ap1.append(answer,0,1); ap2.append(answer,1,1); ap3.append(answer,2,1); ap4.append(answer,3,1); ap5.append(answer,4,1);
        uap1.append(userAnswer,0,1); uap2.append(userAnswer,1,1); uap3.append(userAnswer,2,1); uap4.append(userAnswer,3,1); uap5.append(userAnswer,4,1);
      }catch(const out_of_range& oor){}
      int repeatCheck = 0;
      if(ap1.compare(uap1)   == 0){hits++;}else{
        if(ap1.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap1.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap1.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(ap1.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap2.compare(uap2)   == 0){hits++;}else{
        if(ap2.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap2.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap2.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(ap2.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap3.compare(uap3)   == 0){hits++;}else{
        if(ap3.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap3.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap3.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(ap3.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap4.compare(uap4)   == 0){hits++;}else{
        if(ap4.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap4.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap4.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap4.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap5.compare(uap5)   == 0){hits++;}else{
        if(ap5.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap5.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap5.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap5.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(invalid == 1){cout<<8 - turnCount<<" guesses remaining."; invalid = 0;}
      else{cout<<"\nIncorrect. "<<hits<<" Hits, "<<blows<<" Blows. "<<8 - turnCount<<" guesses remaining.";}
      hits  = 0;
      blows = 0;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); ap5.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear(); uap5.clear();
    }
    if(turnCount == 8 && userAnswer != answer){
      lossCount++;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); ap5.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear(); uap5.clear();
      cout<<"\n\nYou were unable to guess the answer in time. Oh well!\nThe answer was "<<answer<<"\n\n\t1 - Retry\n\t2 - Return to Menu\n\n\t\t> ";
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

void gameE(){
  turnCount = 0;
  srand((unsigned)time(NULL));
  char* UA = new char[makeUA(25).length()];
  for (int i = 0; i < makeUA(5).length(); i++)
    UA[i - 1] = makeUA(10)[i];
  answer.append(UA);
  answer.resize(5);

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
    size_t found = userAnswer.find_first_not_of("1234567890AaBbCcDdEeFf");
    if(userAnswer.length() != 5 || cin.fail() || found != std::string::npos){
      cin.clear();
      cin.ignore(100, '\n');
      hits = 0; blows = 0;
      turnCount--;
      cout<<"\nError: That is not a valid answer. ";
      invalid = 1;
    }
    if(userAnswer == answer){
      eCount++;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); ap5.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear(); uap5.clear();
      cout<<"\nCongratulations! You've cracked the code!\n\t1 - Play Again\n\t2 - Return to Menu\n\n\t\t> ";
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
          gameD();
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
      try{
        ap1.append(answer,0,1); ap2.append(answer,1,1); ap3.append(answer,2,1); ap4.append(answer,3,1); ap5.append(answer,4,1);
        uap1.append(userAnswer,0,1); uap2.append(userAnswer,1,1); uap3.append(userAnswer,2,1); uap4.append(userAnswer,3,1); uap5.append(userAnswer,4,1);
      }catch(const out_of_range& oor){}
      int repeatCheck = 0;
      if(ap1.compare(uap1)   == 0){hits++;}else{
        if(ap1.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap1.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap1.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(ap1.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap2.compare(uap2)   == 0){hits++;}else{
        if(ap2.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap2.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap2.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(ap2.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap3.compare(uap3)   == 0){hits++;}else{
        if(ap3.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap3.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap3.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(ap3.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap4.compare(uap4)   == 0){hits++;}else{
        if(ap4.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap4.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap4.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap4.compare(uap5) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(ap5.compare(uap5)   == 0){hits++;}else{
        if(ap5.compare(uap1) == 0){blows++;  repeatCheck++;}
        if(ap5.compare(uap2) == 0){blows++;  repeatCheck++;}
        if(ap5.compare(uap3) == 0){blows++;  repeatCheck++;}
        if(ap5.compare(uap4) == 0){blows++;  repeatCheck++;}
        if(repeatCheck > 1){blows = blows - (repeatCheck - 1);}
        repeatCheck = 0;
      }
      if(invalid == 1){cout<<8 - turnCount<<" guesses remaining."; invalid = 0;}
      else{cout<<"\nIncorrect. "<<hits<<" Hits, "<<blows<<" Blows. "<<8 - turnCount<<" guesses remaining.";}
      hits  = 0;
      blows = 0;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); ap5.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear(); uap5.clear();
    }
    if(turnCount == 8 && userAnswer != answer){
      lossCount++;
      ap1.clear(); ap2.clear(); ap3.clear(); ap4.clear(); ap5.clear(); uap1.clear(); uap2.clear(); uap3.clear(); uap4.clear(); uap5.clear();
      cout<<"\n\nYou were unable to guess the answer in time. Oh well!\nThe answer was "<<answer<<"\n\n\t1 - Retry\n\t2 - Return to Menu\n\n\t\t> ";
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
        gameB();
        break;
      }
      case 3:{
        gameC();
        break;
      }
      case 4:{
        gameD();
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
        if(gAcheck == 1 && gBcheck == 1 && gCcheck == 1 && gDcheck == 1 && winCount >= 5){
          gameE();
        }else{cout<<"\nUnfair Mode has not been unlocked yet. Win once in each other gamemode, and win 5 games total.\n"; earlyCheck = 1;}
        break;
      }
      case 8:{
        cout<<"\nUnfair Mode is different from every other gamemode. Not only does it generate\nthe answer entirely differently, but it now also includes letters A through\nF, uppercase and lowercase. Not to mention the chances of duplicates are much\nhigher, and aren't restricted. Each answer is 5 characters long. Uppercase\nletters will not be blows for lowercase letters. Good luck.\n";
        earlyCheck = 1;
        break;
      }
      case 0:{
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