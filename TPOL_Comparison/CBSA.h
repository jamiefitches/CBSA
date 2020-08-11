#ifndef RUN_H
#define RUN_H

class run
{
public:
  string RunNumber; 
  Int_t CrystalOrientation;
  Bool_t isAmo;
  Bool_t isPara;
  run(string Number, Int_t Orientation, Bool_t Para = 1);
  
};

vector <run> RunList;

run::run(string Number, Int_t Orientation, Bool_t Para  = 1)
{
  RunNumber = Number;
  CrystalOrientation = Orientation;
  isPara = Para;
  if (Orientation == -1){
    isAmo = 1;
      }
  else{
    isAmo = 0;
  }
  //  RunList.push_back(*this);
}

void FillRunList(){
  string RunNum;
  Int_t PolAngle;
  Bool_t isPara;
  
  ifstream RunNumStream;
  ifstream AngleStream;
  ifstream IsParaStream;

  const char * RunNumFlName = "RunConfig/AllRuns.dat";
  const char * AngleFlName = "RunConfig/RunAngles.dat";
  const char * IsParaFlName = "RunConfig/RunParaPerp.dat";

  RunNumStream.open(RunNumFlName);
  AngleStream.open(AngleFlName);
  IsParaStream.open(IsParaFlName);

  while (RunNumStream.eof() == false){
    RunNumStream >> RunNum;
    AngleStream >> PolAngle;
    IsParaStream >> isPara;
    run DataRun(RunNum, PolAngle, isPara);
    RunList.push_back(DataRun);
  } 
  
  RunNumStream.close();
  AngleStream.close();
  IsParaStream.close();
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

#endif
