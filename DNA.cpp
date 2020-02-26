#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <math.h>
#include <string>
using namespace std;

// declare all variables globally
float numA = 0, numC = 0, numT = 0, numG = 0;
int sumOfDNA;
int sumBigram;
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
ifstream inputFileStream;
ifstream masterFile;
ofstream outputFile;
float totalDNA;
float aProb, cProb, gProb, tProb;
float aGaussian, cGaussian, tGaussian, gGaussian;

/*
  Collects the name of file from user and returns the file name
  @param masterFile Input file
  @return The name of the file
*/
string inputfile(ifstream& masterFile){
  // prompt user for file name
  cout << "Please enter the name and extension of your file: ";
  cin >> fileName;

  masterFile.open(fileName);
  bool fileExists = true;
  char tryAgain;

  // if file does not exist, continue loop until file exists
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

/*
  Calculatres the number of lines in the file
  @param file The text file user entered
  @return The number of Lines in the text file
*/
int computeTotalLines(string file){
  ifstream inputFileStream;
  inputFileStream.open(file);
  // for every line, increment totalLines variable
  while(getline(inputFileStream, line)){
    totalLines++;
  }
  inputFileStream.close();
  return totalLines;
}

/*
  Calculates the mean of the length of the DNA strings
  @param numLines Total number of lines in the text file
  @param DNASum Total number of DNA characters in the text file
  @return Mean number of DNA in the text file
*/
float calcMean(int numLines, float DNAsum){
  // caluculation to find mean of the length of the DNA strings
  meanNum = DNAsum / numLines;
  return meanNum;
}

/*
  Calculates the variance of the length of the DNA strings in the list
  @param file Passes through text file
  @param mean Uses mean for calculations
  @param lineTotal Uses total number of lines for calculations
  @return Returns calculated variance
*/
float calcVariance(string file, float mean, int lineTotal){
  float tempVar, tempNum;
  ifstream inputFileStream;
  inputFileStream.open(file);
  // iterating through the lines of the file
  while(getline(inputFileStream, line)){
    tempVar += pow((int)line.length() - mean, 2);
  }
  variance = tempVar / (lineTotal - 1);
  return variance;
  inputFileStream.close();
}

/*
  Calculates standard deviation
  @param calculatedVariance Square this value to calculate standard deviation
  @return Standard deviation
*/
float calcStdDev(float calculatedVariance){
  // square vairance to find standard deviation
  stdDev = sqrt(calculatedVariance);
  return stdDev;
}

/*
  Computes Gaussian value using random numbers and probability
  Prints Gaussian value to outputFile
  @return DNA string of 1000 strings calculated from Gaussian value
*/
string calcGaussian(){

  // calculations to compute random values using RAND_MAX function
  float randA = (float) rand() / (float)RAND_MAX;
  float randB = (float) rand() / (float)RAND_MAX;
  float randC = sqrt(-2 * log(randA)) * cos(2 * M_PI * randB);
  float randD = (sqrt(variance) * randC) + meanNum;
  string lineString = "";

  // iterate up  to 1000 times
  for(int i = 0; i < 1000; ++i){
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
  }

  // print Gaussian value to output file
  outputFile << "Gaussian value: " << randD << endl;
  return lineString;
}



int main(int argc, char** argv){

  bool anotherFile = true;
  char processFile;
  char userChoice;

  // check if user wants to continue
  while(anotherFile = true){
    cout << "Would you like to process a file (y/n): ";
    cin >> processFile;
    userChoice = tolower(processFile);
    if(userChoice == 'y'){
      inputfile(masterFile);
      inputFileStream.open(fileName);
      // checks for nucleotides and bigrams and adds to running total
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

        // calculate probablitiy of each nucleotide
        aProb = numA / totalDNA;
        tProb = numT / totalDNA;
        cProb = numC / totalDNA;
        gProb = numG / totalDNA;

        // calls to methods
        computeTotalLines(fileName);
        //calcGaussian();
        calcMean(totalLines, totalDNA);
        calcVariance(fileName, meanNum, totalLines);
        calcStdDev(variance);

        // open output file
        outputFile.open("LenaKhalidi.out", ofstream::app); //| ofstream::trunc);

        // print results to output file
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
        outputFile << "Gaussian distribution: " << calcGaussian() << endl;
        outputFile << endl;
        outputFile << endl;
        outputFile.close();

        cout << endl;
        cout << "Process complete." << endl;
        cout << endl;

        // reset all values for next file
        aa = 0, cc = 0, tt = 0, gg = 0;
        ac = 0, at = 0, ag = 0;
        ca = 0, ct = 0, cg = 0;
        ta = 0, tc = 0, tg = 0;
        ga = 0, gc = 0, gt = 0;
        totalLines = 0;
        sumBigram = 0;
        stdDev = 0;
    }
    // exit program if user does not wish to continue
    else if(userChoice == 'n'){
      exit(1);
    }
    // reprompts user if invalid input
    else{
      cout << "You did not enter a valid input. Please try again." << endl;
      anotherFile = true;
    }
  }
  // close all files
  masterFile.close();
  outputFile.close();
  outputFile.clear();
  return 0;
}
