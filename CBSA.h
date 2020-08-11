#ifndef RUN_H
#define RUN_H

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "TFile.h" 
#include "TTree.h" 
#include "TROOT.h"

class run
{
public:
  string RunNumber; 
  Int_t CrystalOrientation;
  Bool_t isAmo;
  Bool_t isPara;
  string AmoRun;
  run(string Number, Int_t Orientation, Bool_t Para = 1, string AmoR = "");
  
};

vector <run> RunList;

run::run(string Number, Int_t Orientation, Bool_t Para, string AmoR)
{
  RunNumber = Number;
  CrystalOrientation = Orientation;
  isPara = Para;
  AmoRun = AmoR;
  if (Orientation == -1){
    isAmo = 1;
      }
  else{
    isAmo = 0;
  }
  //  RunList.push_back(*this);
}

void FillRunList_Old(string RunListIn){
  string RunNum;
  Int_t PolAngle;
  Bool_t isPara;
  Int_t LastAmoRun;
  string line;

  string RunListFlNameStr = "RunConfig/" + RunListIn;
  const char * RunListFlName = RunListFlNameStr.c_str();

  ifstream RunStream(RunListFlName);

    //While we can still read the file
    while (getline(RunStream, line))
    {
        istringstream iss(line);
        Int_t num; // The number in the line
	cout << "working" << endl;
        //while the iss is a number 
        while ((iss >> num))
        {
	  RunNum = num;
	  iss >> PolAngle;
	  iss >> isPara;
	  iss >> LastAmoRun;
	  cout << "RunNum = " << RunNum << " Angle = " << PolAngle << " Para/Perp = " << isPara << endl;
	  run DataRun(RunNum, PolAngle, isPara);
	  RunList.push_back(DataRun);
            //look at the number
        }
    }
 RunStream.close();
}

void FillRunList(const char * RunListFlName){
  string RunNum;
  Int_t PolAngle;
  Bool_t isPara;
  Int_t LastAmoRun;

  ifstream RunStream;
  RunStream.open(RunListFlName);
 
  string line;
  //While we can still read the file
  while (getline(RunStream, line))
    {
      istringstream iss(line);
      Int_t RunNum; // The number in the line
      //while the iss is a number 
      while ((iss >> RunNum))
	{
	  iss >> PolAngle;
	  iss >> isPara;
	  iss >> LastAmoRun;
	  run DataRun(to_string(RunNum), PolAngle, isPara, to_string(LastAmoRun));
	  RunList.push_back(DataRun);
	  //look at the number
       }
    }
  
  RunStream.close();
}

run returnRun(string RunNum){
  for (int i = 0; i < RunList.size(); i++){
    if (RunList[i].RunNumber == RunNum){
      return(RunList[i]);
    }
  }
  run emptyRun("None", 0, 0);
  return(emptyRun);
}

run GetAmoRun(string RunNum){
  run diRun = returnRun(RunNum);
  Int_t RunNumInt = stoi(RunNum);
  run amoRun("None", 0, 0);
  if (diRun.isAmo == 1){
    cout << "Run " << RunNum << " is an amorphous run" << endl;
    cout << "Returning empty run" << endl;
    return(amoRun); 
  }
  for(Int_t i = RunNumInt-1;  i > 0; i--){
    run NextRun = returnRun(to_string(i));
    if(NextRun.isAmo == 1){
      return(NextRun);
    }
  }
  return(amoRun);
}

run GetAmoRun_FileCheck(string RunNum, string FilePath, string skim){
  run diRun = returnRun(RunNum);
  Int_t RunNumInt = stoi(RunNum); 
  run EmptyRun("None", 0, 0);
  TFile * AmoFile;
  string AmoFileName;
  string FileNameBase = FilePath + "/" + skim + "_0";
  Bool_t UseFutureAmRun = false;
  if (diRun.isAmo == 1){
    cout << "Run " << RunNum << " is an amorphous run" << endl;
    cout << "Returning empty run" << endl;
    return(EmptyRun); 
  }
  for(Int_t i = RunNumInt-1;  i > 0; i--){
    run NextRunLess = returnRun(to_string(i));
    if(i == 1){
      cout << "older amorphous file does not exist" << endl; 
      UseFutureAmRun = true;
    }
    if(NextRunLess.isAmo == 1){
      AmoFileName = FileNameBase + to_string(i) + ".root";
      TFile * rootfile = TFile::Open(AmoFileName.c_str());
      if(rootfile != 0){
	return(NextRunLess);
      }
    }
  }
  if(UseFutureAmRun == true){
    for(Int_t n = RunNumInt + 1; n < RunNumInt + 1000; n++){
      run NextRun = returnRun(to_string(n));
      if(NextRun.isAmo == 1){
	AmoFileName = FileNameBase + to_string(n) + ".root";
	TFile * rootfile = TFile::Open(AmoFileName.c_str());
	if(rootfile != 0){
	  return(NextRun);
	}
      }
    }
  }
  cout << "Could not find amorphous run, returning empty run" << endl;
  return(EmptyRun); 
}

#endif
