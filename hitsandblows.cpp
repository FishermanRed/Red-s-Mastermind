// RED HERE THIS IS THE TEST BOARD I MADE FOR THE TEST HITS AND BLOWS FUNCTION BECAUSE IT NEEDED ITS OWN THING FOR ME TO GET IT TO WORK

#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <array>

using namespace std;

string makeID(const int len) { //secondary random number gen, generates duplicates too
  static const char ID[] =
    "0123456789";
  string make;
  for (int i = 0; i < 25; ++i) {
    make += ID[rand() % (sizeof(ID) - 1)];
  }
  return make;
}



int main(){
  int hits=0, blows=0;
  string answer     ("6799"); // uncomment below thing and comment the numbers here for random numbers
  string userAnswer ("7677");
  string ap1, ap2, ap3, ap4, uap1, uap2, uap3, uap4;

  //array<int, 10> x{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  //unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  //shuffle(x.begin(), x.end(), default_random_engine(seed));
  //for (int& i : x)answer += to_string(i);
  //answer.resize(4);
  //
  //srand((unsigned)time(NULL));
  //char* ID = new char[makeID(25).length()];
  //for (int i = 0; i < makeID(5).length(); i++)
  //  ID[i - 1] = makeID(5)[i];
  //userAnswer.append(ID);
  //userAnswer.resize(4);

  cout<<answer<<endl;
  cout<<userAnswer<<endl;
  cout<<endl<<"     Answer: ";
  ap1.append(answer,0,1);
  cout<<ap1<<' ';
  ap2.append(answer,1,1);
  cout<<ap2<<' ';
  ap3.append(answer,2,1);
  cout<<ap3<<' ';
  ap4.append(answer,3,1);
  cout<<ap4<<' ';
  cout<<endl<<"User Answer: ";
  uap1.append(userAnswer,0,1);
  cout<<uap1<<' ';
  uap2.append(userAnswer,1,1);
  cout<<uap2<<' ';
  uap3.append(userAnswer,2,1);
  cout<<uap3<<' ';
  uap4.append(userAnswer,3,1);
  cout<<uap4<<' ';
  cout<<endl<<endl;
  
  int repeatCheck=0;
  if(ap1.compare(uap1)==0){cout<<"\tap1 Match!"; hits++;}else{
    if(ap1.compare(uap2)==0){cout<<"\tap1 Close!"; blows++; repeatCheck++;}
    if(ap1.compare(uap3)==0){cout<<"\tap1 Close!"; blows++; repeatCheck++;}
    if(ap1.compare(uap4)==0){cout<<"\tap1 Close!"; blows++; repeatCheck++;}
    if(repeatCheck > 1){cout<<"\trepeatCheck reset 1. Count: "<<repeatCheck; blows = blows - (repeatCheck-1);}
    repeatCheck=0;
  }

  if(ap2.compare(uap2)==0){cout<<"\tap2 Match!"; hits++;}else{
    if(ap2.compare(uap1)==0){cout<<"\tap2 Close!"; blows++; repeatCheck++;}
    if(ap2.compare(uap3)==0){cout<<"\tap2 Close!"; blows++; repeatCheck++;}
    if(ap2.compare(uap4)==0){cout<<"\tap2 Close!"; blows++; repeatCheck++;}
    if(repeatCheck > 1){cout<<"\trepeatCheck reset 2. Count: "<<repeatCheck; blows = blows - (repeatCheck-1);}
    repeatCheck=0;
  }

  if(ap3.compare(uap3)==0){cout<<"\tap3 Match!"; hits++;}else{
    if(ap3.compare(uap1)==0){cout<<"\tap3 Close!"; blows++; repeatCheck++;}
    if(ap3.compare(uap2)==0){cout<<"\tap3 Close!"; blows++; repeatCheck++;}
    if(ap3.compare(uap4)==0){cout<<"\tap3 Close!"; blows++; repeatCheck++;}
    if(repeatCheck > 1){cout<<"\trepeatCheck reset 3. Count: "<<repeatCheck; blows = blows - (repeatCheck-1);}
    repeatCheck=0;
  }
  
  if(ap4.compare(uap4)==0){cout<<"\tap4 Match!"; hits++;}else{
    if(ap4.compare(uap1)==0){cout<<"\tap4 Close!"; blows++; repeatCheck++;}
    if(ap4.compare(uap2)==0){cout<<"\tap4 Close!"; blows++; repeatCheck++;}
    if(ap4.compare(uap3)==0){cout<<"\tap4 Close!"; blows++; repeatCheck++;}
    if(repeatCheck > 1){cout<<"\trepeatCheck reset 4. Count: "<<repeatCheck; blows = blows - (repeatCheck-1);}
    repeatCheck = 0;
  }

  // fuck the commented code below didn't work

  //if(repeatCheck > 1){cout<<"\trepeatCheck reset."; blows = blows - (repeatCheck-1);}
  //if(repeatCheck == 5){blows = 3;}
  //if(repeatCheck >= 6){blows = 4;}
  //if(blows >= 4){}

  //for(int i = 0; i < 4; i++){
  //  int count1 = 1, count2 = 1;
  //  while(i < 4 - 1 && answer[i] == answer[i + 1]){
  //      count1++;
  //      i++;
  //  }
  //  while (i < 4 - 1 && userAnswer[i] == userAnswer[i + 1]) {
  //    count2++;
  //    i++;
  //  }
  //  if(count1 > 1){blows--;}
  //  if(count2 > 1){blows++;}
  //}
  if(hits==4){blows=0;}
  cout<<endl<<hits<<" Hits, "<<blows<<" Blows.\n\n";
  
  return 0;
}