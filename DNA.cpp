#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <math.h>
using namespace std;

// declare all variables globally
// declare nucloetides
float numA = 0, numC = 0, numT = 0, numG = 0;
// declare vairable for sum
int sumOfDNA;
int sumBigram;
// declare necleotide bigrams
string fileName;
string line;
float totalLines;
float aa = 0, cc = 0, tt = 0, gg = 0;
float ac = 0, at = 0, ag = 0;
float ca = 0, ct = 0, cg = 0;
float ta = 0, tc = 0, tg = 0;
float ga = 0, gc = 0, gt = 0;
char dna, dna1;
float randA = 0 , randB = 0 , randC = 0, randD = 0;
float variance = 0, meanNum = 0, stdDev = 0;
ifstream file;
ifstream masterFile;
ofstream outputFile;
float totalDNA;
float aProb, cProb, gProb, tProb;
float aGaussian, cGaussian, tGaussian, gGaussian;
string lineString = "";


string inputfile(ifstream& masterFile){
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
        continue;
      }
    }
    else {
      exit(1);
    }

  }
  masterFile.close();
  return fileName;
}

int computeTotalLines(string file){
  ifstream inputFileStream;
  inputFileStream.open(file);
  while(getline(inputFileStream, line)){
    totalLines++;
  }
  inputFileStream.close();
  return totalLines;
}

float calcMean(int numLines, float DNAsum){
  meanNum = DNAsum / numLines;
  return meanNum;
}

float calcVariance(string file, float mean, int lineTotal){
  float tempVar, tempNum;
  ifstream inputFileStream;
  inputFileStream.open(file);
  while(getline(inputFileStream, line)){
    tempVar += pow((int)line.length() - mean, 2);
  }
  variance = tempVar / (lineTotal - 1);
  return variance;
  inputFileStream.close();
}

float calcStdDev(float calculatedVariance){
  stdDev = sqrt(calculatedVariance);
  return stdDev;
}

float calcGaussian(){
  float randA = (float) rand() / (float)RAND_MAX;
  float randB = (float) rand() / (float)RAND_MAX;
  float randC = sqrt(-2 * log(randA)) * cos(2 * M_PI * randB);
  float randD = sqrt(variance) * randC + meanNum;
  return randD;
}



int main(int argc, char** argv){
  outputFile.clear();
  ifstream inputFileStream;
  inputFileStream.open(fileName);
  bool anotherFile = true;
  char processFile;
  char userChoice;

  while(anotherFile = true){
    cout << "Would you like to process a file (y/n): ";
    cin >> processFile;
    userChoice = tolower(processFile);
    if(userChoice == 'y'){
        inputfile(masterFile);
        while(getline(inputFileStream, line)) {
           for (int i = 0; i < line.length(); i++){

             dna = tolower(line[i]);
             dna1 = tolower(line[i+1]);
             if(dna == 'a') {
               totalDNA++;
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
             if(dna == 'c'){
               totalDNA++;
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
             if(dna == 't') {
               totalDNA++;
               numT++;
               if(dna1 == 'a'){
                 ta++;
                 sumBigram++;
               }
               else if(dna1 == 'c'){
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
             if(dna == 'g') {
               totalDNA++;
               numG++;
               if(dna1 == 'a'){
                 ga++;
                 sumBigram++;
               }
               else if(dna1 == 'c'){
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

        computeTotalLines(fileName);
        calcGaussian();
        calcMean(totalLines, totalDNA);
        calcVariance(fileName, meanNum, totalLines);
        calcStdDev(variance);

        aProb = numA / totalDNA;
        tProb = numT / totalDNA;
        cProb = numC / totalDNA;
        gProb = numG / totalDNA;

        outputFile.open("LenaKhalidi.out");
        outputFile << "Lena Khalidi" << endl;
        outputFile << "Assignment1: DNA" << endl;
        outputFile << "Student ID: 002315903" << endl;
        outputFile << endl;
        outputFile << "Total Lines: " << totalLines << endl;
        outputFile << endl;
        outputFile << "Total Nucleotides: " << totalDNA << endl;
        outputFile << endl;
        outputFile << "The mean of the length of the DNA strings: " << meanNum << endl;
        outputFile << endl;
        outputFile << "The variance of the DNA strings: " << variance << endl;
        outputFile << endl;
        outputFile << "The standard deviation of the DNA string: " << stdDev << endl;
        outputFile << endl;
        outputFile << "Relative probability of each nucleotide: " << endl;
        outputFile << "A:               " << aProb << endl;
        outputFile << "T:               " << tProb << endl;
        outputFile << "C:               " << cProb << endl;
        outputFile << "G:               " << gProb << endl;
        outputFile << endl;
        outputFile << "Relative probability of each nucleotide bigram: " << endl;
        outputFile << "AA:               " << aa/sumBigram << endl;
        outputFile << "AC:               " << ac/sumBigram << endl;
        outputFile << "AG:               " << ag/sumBigram << endl;
        outputFile << "CA:               " << ca/sumBigram << endl;
        outputFile << "CC:               " << cc/sumBigram << endl;
        outputFile << "CT:               " << ct/sumBigram << endl;
        outputFile << "CG:               " << cg/sumBigram << endl;
        outputFile << "TA:               " << ta/sumBigram << endl;
        outputFile << "TC:               " << tc/sumBigram << endl;
        outputFile << "TT:               " << tt/sumBigram << endl;
        outputFile << "TC:               " << tc/sumBigram << endl;
        outputFile << "TG:               " << tg/sumBigram << endl;
        outputFile << "GA:               " << ga/sumBigram << endl;
        outputFile << "GC:               " << gc/sumBigram << endl;
        outputFile << "GT:               " << gt/sumBigram << endl;
        outputFile << "GG:               " << gg/sumBigram << endl;
        outputFile << endl;
        outputFile << endl;
        outputFile << "Gaussian values: " << calcGaussian();


        for(int i = 0; i < 1000; ++i){
          randD = calcGaussian();

          aGaussian = randD * aProb;
          cGaussian = randD * cProb;
          tGaussian = randD * tProb;
          gGaussian = randD * gProb;


          for(int j = 0; j < aGaussian; ++j){
            lineString += "a";
          }
          for(int k = 0; k < cGaussian; ++k){
            lineString += "c";
          }
          for(int l = 0; l < tGaussian; ++l){
            lineString += "t";
          }
          for(int m = 0; m < gGaussian; ++m){
            lineString += "g";
          }
          outputFile << lineString << endl;
        }
        cout << endl;
        cout << "Process complete." << endl;
        cout << endl;
    }
    else if(userChoice == 'n'){
      exit(1);
    }
    else{
      cout << "You did not enter a valid input. Please try again." << endl;
      anotherFile = true;
    }

  }

  aa = 0, cc = 0, tt = 0, gg = 0;
  ac = 0, at = 0, ag = 0;
  ca = 0, ct = 0, cg = 0;
  ta = 0, tc = 0, tg = 0;
  ga = 0, gc = 0, gt = 0;



  // print results
  //cout << "Mean of the length of the DNA string: ";


masterFile.close();
outputFile.close();
return 0;

}
