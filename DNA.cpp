#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
using namespace std;

// declare all variables globally
// declare nucloetides
int numA = 0, numC = 0, numT = 0, numG = 0;
// declare vairable for sum
int sumOfDNA;
int sumBigram;
// declare necleotide bigrams
int aa = 0, cc = 0, tt = 0, gg = 0;
int ac = 0, at = 0, ag = 0;
int ca = 0, ct = 0, cg = 0;
int ta = 0, tc = 0, tg = 0;
int ga = 0, gc = 0, gt = 0;
char dna, dna1;
ifstream file;
ifstream masterFile;
ofstream outputFile;
ofstream outFile;
string fileName;
string line;
int numLines;


void inputfile(ifstream& masterFile){
  cout << "Please enter the name and extension of your file: ";
  cin >> fileName;
  masterFile.open(fileName);
  bool fileExists = true;
  char tryAgain;

  while(!masterFile){
    fileExists = false;
    cout << endl << ("The file does not exist. ");
    cout << ("Would you like to try again? (y/n) ");
    cin >> tryAgain;
    if(tolower(tryAgain) == 'y'){
      cout << ("Please enter the file you would like to open: ");
      ifstream file;
      cin >> fileName;
      masterFile.open(fileName);
      if(masterFile){
        break;
      }
    }
    else {
      exit(1);
    }

  }
}

int readFile(ifstream& file){
  while(getline(file,line)){
    numLines++;
  }
  cout << "readFile working..." << endl;
  cout << "Number of Lines: " << numLines << endl;
  return numLines;
}

int computeSum(string fileName, int numberOfLines){
  while(numberOfLines > 0){
    for(int i = 0; i < line.length(); ++i){
      dna = tolower(line[i]);
      dna1 = tolower(line[i+1]);
      // check for bigrams
      if(dna == 'a'){
        numA++;
        if(dna1 == 'a'){
          aa++;
          sumBigram++;
        }
        else if(dna1 == 'c'){
          ac++;
          sumBigram++;
        }
        else if(dna1 == 't'){
          at++;
          sumBigram++;
        }
        else if(dna1 == 'g'){
          ag++;
          sumBigram++;
        }
      }
      if(dna == 't'){
        numT++;
        if(dna1 == 'a'){
          ta++;
          sumBigram++;
        }
        else if(dna1 == 't'){
          tc++;
          sumBigram++;
        }
        else if(dna1 == 't'){
          tt++;
          sumBigram++;
        }
        else if(dna1 == 'g'){
          tg++;
          sumBigram++;
        }
      }

      if(dna == 'c'){
        numC++;
        if(dna1 == 'a'){
          ca++;
          sumBigram++;
        }
        else if(dna1 == 'c'){
          cc++;
          sumBigram++;
        }
        else if(dna1 == 't'){
          ct++;
          sumBigram++;
        }
        else if(dna1 == 'g'){
          cg++;
          sumBigram++;
        }
      }
      if(dna == 'g'){
        numG++;
        if(dna1 == 'a'){
          ga++;
          sumBigram++;
        }
        else if(dna1 == 't'){
          gc++;
          sumBigram++;
        }
        else if(dna1 == 't'){
          gt++;
          sumBigram++;
        }
        else if(dna1 == 'g'){
          gg++;
          sumBigram++;
        }
      }
    }
   }
  cout << "computing sum..";
  cout << "num of bigrams: " << sumBigram << endl;
}

// string outputFile(ofstream& outputFile){
//   outputFile.open("LenaKhalidi.out");
//   outputFile << "Lena Khalidi" << endl;
//   outputFile << "Assignment1: DNA" << endl;
//   outputFile << "Student ID: 002315903" << endl;
//  }




int main(int argc, char** argv){

  inputfile(masterFile);
  readFile(masterFile);
  //computeSum(fileName);
  cout << "now computing sum" << endl;
  computeSum(fileName, numLines);
  //outputFile(outFile);

  outFile.close();


}
