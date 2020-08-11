#include "CBSA.h"

void GenerateFarmLists(string RunPeriod, string FilePath, const char * AllRunsList, string skim){

  const char * New_Line = "\n";
  string New_Line_str(New_Line);
  ofstream FileList;
  ofstream AmFileList;
  ofstream AllRuns;
  ofstream PeriodList;
  Int_t RunNumHigh;
  Int_t RunNumLow;

  
  if(RunPeriod == "1/16"){
    RunNumHigh = 20000;
    RunNumLow = 10000;
  }
  else if(RunPeriod == "2/16"){
    RunNumHigh = 30000;
    RunNumLow = 20000;
  }
  else if(RunPeriod == "1/17"){
    RunNumHigh = 40000;
    RunNumLow = 30000;
  }
  else if(RunPeriod == "1/18"){
    RunNumHigh = 50000;
    RunNumLow = 40000;
  }
  else if(RunPeriod == "2/18"){
    RunNumHigh = 60000;
    RunNumLow = 50000;
  }
  else if(RunPeriod == "1/19"){
    RunNumHigh = 70000;
    RunNumLow = 60000;
  }
  else{
    cout << "Run number is outside defined range, please update code to account for run periods past January 2019" << endl;
  }

  FillRunList(AllRunsList);
  FileList.open("FarmInFiles/FileList");
  AmFileList.open("FarmInFiles/AmFileList");
  AllRuns.open("FarmInFiles/RunList");
  PeriodList.open("FarmInFiles/RunPeriodList");

  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation != -1){
      FileList << FilePath +  "/" + skim + "_0" + RunList[i].RunNumber + ".root" + New_Line_str;
      AmFileList << FilePath + "/" + skim + "_0" + (GetAmoRun(RunList[i].RunNumber)).RunNumber + ".root" + New_Line_str;
      AllRuns << RunList[i].RunNumber + New_Line_str;
      PeriodList << RunPeriod + New_Line_str;
    }
  }
}

string GetRunPeriod(Int_t RunNum){

  string RunPeriod = "";

  if(RunNum >= 10000 && RunNum < 20000){
    RunPeriod = "1/16";
  }
  else if(RunNum >= 20000 && RunNum < 30000){
    RunPeriod = "2/16";
  }
  else if(RunNum >= 30000 && RunNum < 40000){
    RunPeriod = "1/17";
  }
  else if(RunNum >= 40000 && RunNum < 50000){
    RunPeriod = "1/18";
  }
  else if(RunNum >= 50000 && RunNum < 60000){
    RunPeriod = "2/18";
  }
  else if(RunNum >= 60000 && RunNum < 70000){
    RunPeriod = "1/19";
  }
  else{
    cout << "Run number is outside defined range, please update code to account for run periods past January 2019" << endl;
  }
  return(RunPeriod);
 
}

void GenerateFileLists_Custom(const char * runfile, string RunPeriod, string FilePath, const char * AllRunsList, string skim){

  const char * New_Line = "\n";
  string New_Line_str(New_Line);
  ofstream FileList;
  ofstream AmFileList;
  ofstream PeriodList;
  ofstream Run_List;
  string line;

  fstream runfilestream;
  FillRunList(AllRunsList);
  runfilestream.open(runfile);
  
  FileList.open("FarmInFiles/FileList");
  AmFileList.open("FarmInFiles/AmFileList");
  Run_List.open("FarmInFiles/RunList");
  PeriodList.open("FarmInFiles/RunPeriodList");
  
  while(std::getline(runfilestream, line)){
    FileList << FilePath + "/" + skim + "_0" + line + ".root" + New_Line_str;
    AmFileList << FilePath + "/" + skim + "_0" + (GetAmoRun(line)).RunNumber + ".root" + New_Line_str;
    Run_List << line + New_Line_str;
    PeriodList << RunPeriod + New_Line_str;
  }
}

void GenerateFileLists_Range(string FilePath, string skim, const char * AllRunsList, Int_t MinRunNum, Int_t MaxRunNum){

  ofstream FileList;
  ofstream AmFileList;
  ofstream PeriodList;
  ofstream Run_List;

  string FileName;

  FileList.open("FarmInFiles/FileList");
  AmFileList.open("FarmInFiles/AmFileList");
  Run_List.open("FarmInFiles/RunList");
  PeriodList.open("FarmInFiles/RunPeriodList");

  FillRunList(AllRunsList);

  string FileNameBase = FilePath + "/" + skim + "_0";
  Int_t MaxNumRuns = MaxRunNum - MinRunNum + 1;
  for(Int_t RunNum = MinRunNum; RunNum < MaxRunNum; RunNum++){
    if(returnRun(to_string(RunNum)).RunNumber != "None"){
      FileName = FileNameBase + to_string(RunNum) + ".root";
      TFile * rootfile = TFile::Open(FileName.c_str());
      if(rootfile == 0){
	continue;
      }
      rootfile -> Close("R");
      if(returnRun(to_string(RunNum)).CrystalOrientation == -1 ||GetAmoRun(to_string(RunNum)).RunNumber == "None"){
	continue;
      }
      if(GetAmoRun_FileCheck(to_string(RunNum), FilePath, skim).RunNumber == "None"){
	continue;
      }
      FileList << FileNameBase + to_string(RunNum) + ".root" << endl;
      AmFileList << FileNameBase + GetAmoRun_FileCheck(to_string(RunNum), FilePath, skim).RunNumber + ".root" << endl;
      Run_List << to_string(RunNum) << endl;
      PeriodList << GetRunPeriod(RunNum) << endl;
    }
  }
}

  
  
  
  
