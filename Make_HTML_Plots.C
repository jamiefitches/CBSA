#include "CBSA.h"

void SaveParamTimelines(string RunPeriod, const char * AllRunsList, string OutDir = "HTML/OutFiles"){
  string filenm;
  fstream fileStream;
  Int_t n = 0;
  Int_t NumRuns = 0;
  Int_t NumRuns_Pol_0_PARA = 0;
  Int_t NumRuns_Pol_0_PERP = 0;
  Int_t NumRuns_Pol_45_PARA = 0;
  Int_t NumRuns_Pol_45_PERP = 0;
  Int_t NumRuns_Pol_90_PARA = 0;
  Int_t NumRuns_Pol_90_PERP = 0;
  Int_t NumRuns_Pol_135_PARA = 0;
  Int_t NumRuns_Pol_135_PERP = 0; 
  TGraph * EdgeTimeline_Pol_0_PARA;
  TGraph * SigmaTimeline_Pol_0_PARA;
  TGraph * ChisqTimeline_Pol_0_PARA; 
  TGraph * ThetaTimeline_Pol_0_PARA; 
  TGraph * ThetaRTimeline_Pol_0_PARA; 
  TGraph * SigmaRTimeline_Pol_0_PARA;
  TGraph * EdgeTimeline_Pol_0_PERP;
  TGraph * SigmaTimeline_Pol_0_PERP;
  TGraph * ChisqTimeline_Pol_0_PERP; 
  TGraph * ThetaTimeline_Pol_0_PERP; 
  TGraph * ThetaRTimeline_Pol_0_PERP; 
  TGraph * SigmaRTimeline_Pol_0_PERP;
  TGraph * EdgeTimeline_Pol_45_PARA;
  TGraph * SigmaTimeline_Pol_45_PARA;
  TGraph * ChisqTimeline_Pol_45_PARA; 
  TGraph * ThetaTimeline_Pol_45_PARA; 
  TGraph * ThetaRTimeline_Pol_45_PARA; 
  TGraph * SigmaRTimeline_Pol_45_PARA;
  TGraph * EdgeTimeline_Pol_45_PERP;
  TGraph * SigmaTimeline_Pol_45_PERP;
  TGraph * ChisqTimeline_Pol_45_PERP; 
  TGraph * ThetaTimeline_Pol_45_PERP; 
  TGraph * ThetaRTimeline_Pol_45_PERP; 
  TGraph * SigmaRTimeline_Pol_45_PERP;
  TGraph * EdgeTimeline_Pol_90_PARA;
  TGraph * SigmaTimeline_Pol_90_PARA;
  TGraph * ChisqTimeline_Pol_90_PARA; 
  TGraph * ThetaTimeline_Pol_90_PARA; 
  TGraph * ThetaRTimeline_Pol_90_PARA; 
  TGraph * SigmaRTimeline_Pol_90_PARA;
  TGraph * EdgeTimeline_Pol_90_PERP;
  TGraph * SigmaTimeline_Pol_90_PERP;
  TGraph * ChisqTimeline_Pol_90_PERP; 
  TGraph * ThetaTimeline_Pol_90_PERP; 
  TGraph * ThetaRTimeline_Pol_90_PERP; 
  TGraph * SigmaRTimeline_Pol_90_PERP;
  TGraph * EdgeTimeline_Pol_135_PARA;
  TGraph * SigmaTimeline_Pol_135_PARA;
  TGraph * ChisqTimeline_Pol_135_PARA; 
  TGraph * ThetaTimeline_Pol_135_PARA; 
  TGraph * ThetaRTimeline_Pol_135_PARA; 
  TGraph * SigmaRTimeline_Pol_135_PARA;
  TGraph * EdgeTimeline_Pol_135_PERP;
  TGraph * SigmaTimeline_Pol_135_PERP;
  TGraph * ChisqTimeline_Pol_135_PERP; 
  TGraph * ThetaTimeline_Pol_135_PERP; 
  TGraph * ThetaRTimeline_Pol_135_PERP; 
  TGraph * SigmaRTimeline_Pol_135_PERP;
  Int_t RunNumUpper;
  Int_t RunNumLower;
  string RunSeason;
  string RunYear;
  string RunAltYear;
  string RunSeasonYear;
  string Filename;

  FillRunList(AllRunsList);

  if(RunPeriod == "1/16"){
    RunNumUpper = 20000;
    RunNumLower = 10000;
  }
  if(RunPeriod == "2/16"){
    RunNumUpper = 30000;
    RunNumLower = 20000;
  }
  if(RunPeriod == "1/17"){
    RunNumUpper = 40000;
    RunNumLower = 30000;
  }
  if(RunPeriod == "1/18"){
    RunNumUpper = 50000;
    RunNumLower = 40000;
  }
  if(RunPeriod == "2/18"){
    RunNumUpper = 60000;
    RunNumLower = 50000;
  }
  if(RunPeriod == "1/19"){
    RunNumUpper = 70000;
    RunNumLower = 60000;
  }
  if(RunPeriod == "2/19"){
    RunNumUpper = 80000;
    RunNumLower = 70000;
  }

  for(Int_t i = RunNumLower; i < RunNumUpper; i++){
    filenm = OutDir + "/Run_" + to_string(i) + "/FitParameters.dat";
    fileStream.open(filenm);
    if (fileStream) {
      NumRuns++;
      run current_run = returnRun(to_string(i));
      if(current_run.CrystalOrientation == 0 && current_run.isPara == true){
	NumRuns_Pol_0_PARA++;
      }
      else if(current_run.CrystalOrientation == 0 && current_run.isPara == false){
	NumRuns_Pol_0_PERP++;
      }
      else if(current_run.CrystalOrientation == 45 && current_run.isPara == true){
	NumRuns_Pol_45_PARA++;
      }
      else if(current_run.CrystalOrientation == 45 && current_run.isPara == false){
	NumRuns_Pol_45_PERP++;
      }
      else if(current_run.CrystalOrientation == 90 && current_run.isPara == true){
	NumRuns_Pol_90_PARA++;
      }
      else if(current_run.CrystalOrientation == 90 && current_run.isPara == false){
	NumRuns_Pol_90_PERP++;
      }
      else if(current_run.CrystalOrientation == 135 && current_run.isPara == true){
	NumRuns_Pol_135_PARA++;
      }
      else if(current_run.CrystalOrientation == 135 && current_run.isPara == false){
	NumRuns_Pol_135_PERP++;
      }     
      
    }
    fileStream.close();
  }

  Double_t edge_array_Pol_0_PARA[NumRuns_Pol_0_PARA];
  Double_t sigma_array_Pol_0_PARA[NumRuns_Pol_0_PARA];
  Double_t chisq_array_Pol_0_PARA[NumRuns_Pol_0_PARA];
  Double_t Theta_array_Pol_0_PARA[NumRuns_Pol_0_PARA];
  Double_t ThetaR_array_Pol_0_PARA[NumRuns_Pol_0_PARA];
  Double_t SigmaR_array_Pol_0_PARA[NumRuns_Pol_0_PARA];
  Double_t RunNum_array_Pol_0_PARA[NumRuns_Pol_0_PARA];

  Double_t edge_array_Pol_0_PERP[NumRuns_Pol_0_PERP];
  Double_t sigma_array_Pol_0_PERP[NumRuns_Pol_0_PERP];
  Double_t chisq_array_Pol_0_PERP[NumRuns_Pol_0_PERP];
  Double_t Theta_array_Pol_0_PERP[NumRuns_Pol_0_PERP];
  Double_t ThetaR_array_Pol_0_PERP[NumRuns_Pol_0_PERP];
  Double_t SigmaR_array_Pol_0_PERP[NumRuns_Pol_0_PERP];
  Double_t RunNum_array_Pol_0_PERP[NumRuns_Pol_0_PERP];

  Double_t edge_array_Pol_45_PARA[NumRuns_Pol_45_PARA];
  Double_t sigma_array_Pol_45_PARA[NumRuns_Pol_45_PARA];
  Double_t chisq_array_Pol_45_PARA[NumRuns_Pol_45_PARA];
  Double_t Theta_array_Pol_45_PARA[NumRuns_Pol_45_PARA];
  Double_t ThetaR_array_Pol_45_PARA[NumRuns_Pol_45_PARA];
  Double_t SigmaR_array_Pol_45_PARA[NumRuns_Pol_45_PARA];
  Double_t RunNum_array_Pol_45_PARA[NumRuns_Pol_45_PARA];

  Double_t edge_array_Pol_45_PERP[NumRuns_Pol_45_PERP];
  Double_t sigma_array_Pol_45_PERP[NumRuns_Pol_45_PERP];
  Double_t chisq_array_Pol_45_PERP[NumRuns_Pol_45_PERP];
  Double_t Theta_array_Pol_45_PERP[NumRuns_Pol_45_PERP];
  Double_t ThetaR_array_Pol_45_PERP[NumRuns_Pol_45_PERP];
  Double_t SigmaR_array_Pol_45_PERP[NumRuns_Pol_45_PERP];
  Double_t RunNum_array_Pol_45_PERP[NumRuns_Pol_45_PERP];

  Double_t edge_array_Pol_90_PARA[NumRuns_Pol_90_PARA];
  Double_t sigma_array_Pol_90_PARA[NumRuns_Pol_90_PARA];
  Double_t chisq_array_Pol_90_PARA[NumRuns_Pol_90_PARA];
  Double_t Theta_array_Pol_90_PARA[NumRuns_Pol_90_PARA];
  Double_t ThetaR_array_Pol_90_PARA[NumRuns_Pol_90_PARA];
  Double_t SigmaR_array_Pol_90_PARA[NumRuns_Pol_90_PARA];
  Double_t RunNum_array_Pol_90_PARA[NumRuns_Pol_90_PARA];

  Double_t edge_array_Pol_90_PERP[NumRuns_Pol_90_PERP];
  Double_t sigma_array_Pol_90_PERP[NumRuns_Pol_90_PERP];
  Double_t chisq_array_Pol_90_PERP[NumRuns_Pol_90_PERP];
  Double_t Theta_array_Pol_90_PERP[NumRuns_Pol_90_PERP];
  Double_t ThetaR_array_Pol_90_PERP[NumRuns_Pol_90_PERP];
  Double_t SigmaR_array_Pol_90_PERP[NumRuns_Pol_90_PERP];
  Double_t RunNum_array_Pol_90_PERP[NumRuns_Pol_90_PERP];

  Double_t edge_array_Pol_135_PARA[NumRuns_Pol_135_PARA];
  Double_t sigma_array_Pol_135_PARA[NumRuns_Pol_135_PARA];
  Double_t chisq_array_Pol_135_PARA[NumRuns_Pol_135_PARA];
  Double_t Theta_array_Pol_135_PARA[NumRuns_Pol_135_PARA];
  Double_t ThetaR_array_Pol_135_PARA[NumRuns_Pol_135_PARA];
  Double_t SigmaR_array_Pol_135_PARA[NumRuns_Pol_135_PARA];
  Double_t RunNum_array_Pol_135_PARA[NumRuns_Pol_135_PARA];

  Double_t edge_array_Pol_135_PERP[NumRuns_Pol_135_PERP];
  Double_t sigma_array_Pol_135_PERP[NumRuns_Pol_135_PERP];
  Double_t chisq_array_Pol_135_PERP[NumRuns_Pol_135_PERP];
  Double_t Theta_array_Pol_135_PERP[NumRuns_Pol_135_PERP];
  Double_t ThetaR_array_Pol_135_PERP[NumRuns_Pol_135_PERP];
  Double_t SigmaR_array_Pol_135_PERP[NumRuns_Pol_135_PERP];
  Double_t RunNum_array_Pol_135_PERP[NumRuns_Pol_135_PERP];
  
  Int_t count_0_PARA = 0;
  Int_t count_0_PERP = 0;
  Int_t count_45_PARA = 0;
  Int_t count_45_PERP = 0;
  Int_t count_90_PARA = 0;
  Int_t count_90_PERP = 0;
  Int_t count_135_PARA = 0;
  Int_t count_135_PERP = 0;

  for(Int_t i = RunNumLower; i < RunNumUpper; i++){
    filenm = OutDir + "/Run_" + to_string(i) + "/FitParameters.dat";
    fileStream.open(filenm);
    if (fileStream) {
      run current_run = returnRun(to_string(i));
      if(current_run.CrystalOrientation == 0 && current_run.isPara == true){
	fileStream >> edge_array_Pol_0_PARA[count_0_PARA];
	fileStream >> sigma_array_Pol_0_PARA[count_0_PARA];
	fileStream >> chisq_array_Pol_0_PARA[count_0_PARA];
	fileStream >> Theta_array_Pol_0_PARA[count_0_PARA];
	fileStream >> ThetaR_array_Pol_0_PARA[count_0_PARA];
	fileStream >> SigmaR_array_Pol_0_PARA[count_0_PARA];
	RunNum_array_Pol_0_PARA[count_0_PARA] = i;
	count_0_PARA++;
     }
      else if(current_run.CrystalOrientation == 0 && current_run.isPara == false){
	fileStream >> edge_array_Pol_0_PERP[count_0_PERP];
	fileStream >> sigma_array_Pol_0_PERP[count_0_PERP];
	fileStream >> chisq_array_Pol_0_PERP[count_0_PERP];
	fileStream >> Theta_array_Pol_0_PERP[count_0_PERP];
	fileStream >> ThetaR_array_Pol_0_PERP[count_0_PERP];
	fileStream >> SigmaR_array_Pol_0_PERP[count_0_PERP];
	RunNum_array_Pol_0_PERP[count_0_PERP] = i; 
	count_0_PERP++;
      }
      else if(current_run.CrystalOrientation == 45 && current_run.isPara == true){
	fileStream >> edge_array_Pol_45_PARA[count_45_PARA];
	fileStream >> sigma_array_Pol_45_PARA[count_45_PARA];
	fileStream >> chisq_array_Pol_45_PARA[count_45_PARA];
	fileStream >> Theta_array_Pol_45_PARA[count_45_PARA];
	fileStream >> ThetaR_array_Pol_45_PARA[count_45_PARA];
	fileStream >> SigmaR_array_Pol_45_PARA[count_45_PARA];
	RunNum_array_Pol_45_PARA[count_45_PARA] = i;  
	count_45_PARA++;
      }
      else if(current_run.CrystalOrientation == 45 && current_run.isPara == false){
	fileStream >> edge_array_Pol_45_PERP[count_45_PERP];
	fileStream >> sigma_array_Pol_45_PERP[count_45_PERP];
	fileStream >> chisq_array_Pol_45_PERP[count_45_PERP];
	fileStream >> Theta_array_Pol_45_PERP[count_45_PERP];
	fileStream >> ThetaR_array_Pol_45_PERP[count_45_PERP];
	fileStream >> SigmaR_array_Pol_45_PERP[count_45_PERP];
	RunNum_array_Pol_45_PERP[count_45_PERP] = i; 
	count_45_PERP++;
      }
      else if(current_run.CrystalOrientation == 90 && current_run.isPara == true){
	fileStream >> edge_array_Pol_90_PARA[count_90_PARA];
	fileStream >> sigma_array_Pol_90_PARA[count_90_PARA];
	fileStream >> chisq_array_Pol_90_PARA[count_90_PARA];
	fileStream >> Theta_array_Pol_90_PARA[count_90_PARA];
	fileStream >> ThetaR_array_Pol_90_PARA[count_90_PARA];
	fileStream >> SigmaR_array_Pol_90_PARA[count_90_PARA];
	RunNum_array_Pol_90_PARA[count_90_PARA] = i;
	count_90_PARA++;
      }
      else if(current_run.CrystalOrientation == 90 && current_run.isPara == false){
	fileStream >> edge_array_Pol_90_PERP[count_90_PERP];
	fileStream >> sigma_array_Pol_90_PERP[count_90_PERP];
	fileStream >> chisq_array_Pol_90_PERP[count_90_PERP];
	fileStream >> Theta_array_Pol_90_PERP[count_90_PERP];
	fileStream >> ThetaR_array_Pol_90_PERP[count_90_PERP];
	fileStream >> SigmaR_array_Pol_90_PERP[count_90_PERP];
	RunNum_array_Pol_90_PERP[count_90_PERP] = i; 
	count_90_PERP++;
      }
      else if(current_run.CrystalOrientation == 135 && current_run.isPara == true){
	fileStream >> edge_array_Pol_135_PARA[count_135_PARA];
	fileStream >> sigma_array_Pol_135_PARA[count_135_PARA];
	fileStream >> chisq_array_Pol_135_PARA[count_135_PARA];
	fileStream >> Theta_array_Pol_135_PARA[count_135_PARA];
	fileStream >> ThetaR_array_Pol_135_PARA[count_135_PARA];
	fileStream >> SigmaR_array_Pol_135_PARA[count_135_PARA];
	RunNum_array_Pol_135_PARA[count_135_PARA] = i;
	count_135_PARA++;
      }
      else if(current_run.CrystalOrientation == 135 && current_run.isPara == false){
	fileStream >> edge_array_Pol_135_PERP[count_135_PERP];
	fileStream >> sigma_array_Pol_135_PERP[count_135_PERP];
	fileStream >> chisq_array_Pol_135_PERP[count_135_PERP];
	fileStream >> Theta_array_Pol_135_PERP[count_135_PERP];
	fileStream >> ThetaR_array_Pol_135_PERP[count_135_PERP];
	fileStream >> SigmaR_array_Pol_135_PERP[count_135_PERP];
	RunNum_array_Pol_135_PERP[count_135_PERP] = i;
	count_135_PERP++;
      }    
    }
    fileStream.close();
  }

  EdgeTimeline_Pol_0_PARA = new TGraph(NumRuns_Pol_0_PARA,RunNum_array_Pol_0_PARA,edge_array_Pol_0_PARA);
  EdgeTimeline_Pol_0_PARA -> SetTitle(";Run Number; Edge Position (MeV)");  

  SigmaTimeline_Pol_0_PARA = new TGraph(NumRuns_Pol_0_PARA,RunNum_array_Pol_0_PARA,sigma_array_Pol_0_PARA); 
  SigmaTimeline_Pol_0_PARA -> SetTitle(";Run Number; Sigma");

  ChisqTimeline_Pol_0_PARA = new TGraph(NumRuns_Pol_0_PARA,RunNum_array_Pol_0_PARA,chisq_array_Pol_0_PARA);
  ChisqTimeline_Pol_0_PARA -> SetTitle(";Run Number; Chisq");
   
  ThetaTimeline_Pol_0_PARA = new TGraph(NumRuns_Pol_0_PARA,RunNum_array_Pol_0_PARA,Theta_array_Pol_0_PARA);
  ThetaTimeline_Pol_0_PARA -> SetTitle(";Run Number; Theta");

  ThetaRTimeline_Pol_0_PARA = new TGraph(NumRuns_Pol_0_PARA,RunNum_array_Pol_0_PARA,ThetaR_array_Pol_0_PARA);
  ThetaRTimeline_Pol_0_PARA -> SetTitle(";Run Number; Thetar");

  SigmaRTimeline_Pol_0_PARA = new TGraph(NumRuns_Pol_0_PARA,RunNum_array_Pol_0_PARA,SigmaR_array_Pol_0_PARA);
  SigmaRTimeline_Pol_0_PARA -> SetTitle(";Run Number; Sigmar");
  
  EdgeTimeline_Pol_0_PERP = new TGraph(NumRuns_Pol_0_PERP,RunNum_array_Pol_0_PERP,edge_array_Pol_0_PERP);
  EdgeTimeline_Pol_0_PERP -> SetTitle(";Run Number; Edge Position (MeV)");   

  SigmaTimeline_Pol_0_PERP = new TGraph(NumRuns_Pol_0_PERP,RunNum_array_Pol_0_PERP,sigma_array_Pol_0_PERP); 
  SigmaTimeline_Pol_0_PERP -> SetTitle(";Run Number; Sigma");

  ChisqTimeline_Pol_0_PERP = new TGraph(NumRuns_Pol_0_PERP,RunNum_array_Pol_0_PERP,chisq_array_Pol_0_PERP);
  ChisqTimeline_Pol_0_PERP -> SetTitle(";Run Number; Chisq");
   
  ThetaTimeline_Pol_0_PERP = new TGraph(NumRuns_Pol_0_PERP,RunNum_array_Pol_0_PERP,Theta_array_Pol_0_PERP);
  ThetaTimeline_Pol_0_PERP -> SetTitle(";Run Number; Theta");

  ThetaRTimeline_Pol_0_PERP = new TGraph(NumRuns_Pol_0_PERP,RunNum_array_Pol_0_PERP,ThetaR_array_Pol_0_PERP);
  ThetaRTimeline_Pol_0_PERP -> SetTitle(";Run Number; Thetar");

  SigmaRTimeline_Pol_0_PERP = new TGraph(NumRuns_Pol_0_PERP,RunNum_array_Pol_0_PERP,SigmaR_array_Pol_0_PERP);
  SigmaRTimeline_Pol_0_PERP -> SetTitle(";Run Number; Sigmar");
  
  EdgeTimeline_Pol_45_PARA = new TGraph(NumRuns_Pol_45_PARA,RunNum_array_Pol_45_PARA,edge_array_Pol_45_PARA);
  EdgeTimeline_Pol_45_PARA -> SetTitle(";Run Number; Edge Position (MeV)");  

  SigmaTimeline_Pol_45_PARA = new TGraph(NumRuns_Pol_45_PARA,RunNum_array_Pol_45_PARA,sigma_array_Pol_45_PARA); 
  SigmaTimeline_Pol_45_PARA -> SetTitle(";Run Number; Sigma");

  ChisqTimeline_Pol_45_PARA = new TGraph(NumRuns_Pol_45_PARA,RunNum_array_Pol_45_PARA,chisq_array_Pol_45_PARA);
  ChisqTimeline_Pol_45_PARA -> SetTitle(";Run Number; Chisq");
   
  ThetaTimeline_Pol_45_PARA = new TGraph(NumRuns_Pol_45_PARA,RunNum_array_Pol_45_PARA,Theta_array_Pol_45_PARA);
  ThetaTimeline_Pol_45_PARA -> SetTitle(";Run Number; Theta");

  ThetaRTimeline_Pol_45_PARA = new TGraph(NumRuns_Pol_45_PARA,RunNum_array_Pol_45_PARA,ThetaR_array_Pol_45_PARA);
  ThetaRTimeline_Pol_45_PARA -> SetTitle(";Run Number; Thetar");

  SigmaRTimeline_Pol_45_PARA = new TGraph(NumRuns_Pol_45_PARA,RunNum_array_Pol_45_PARA,SigmaR_array_Pol_45_PARA);
  SigmaRTimeline_Pol_45_PARA -> SetTitle(";Run Number; Sigmar");
  
  EdgeTimeline_Pol_45_PERP = new TGraph(NumRuns_Pol_45_PERP,RunNum_array_Pol_45_PERP,edge_array_Pol_45_PERP);
  EdgeTimeline_Pol_45_PERP -> SetTitle(";Run Number; Edge Position (MeV)");   

  SigmaTimeline_Pol_45_PERP = new TGraph(NumRuns_Pol_45_PERP,RunNum_array_Pol_45_PERP,sigma_array_Pol_45_PERP); 
  SigmaTimeline_Pol_45_PERP -> SetTitle(";Run Number; Sigma");

  ChisqTimeline_Pol_45_PERP = new TGraph(NumRuns_Pol_45_PERP,RunNum_array_Pol_45_PERP,chisq_array_Pol_45_PERP);
  ChisqTimeline_Pol_45_PERP -> SetTitle(";Run Number; Chisq");
   
  ThetaTimeline_Pol_45_PERP = new TGraph(NumRuns_Pol_45_PERP,RunNum_array_Pol_45_PERP,Theta_array_Pol_45_PERP);
  ThetaTimeline_Pol_45_PERP -> SetTitle(";Run Number; Theta");

  ThetaRTimeline_Pol_45_PERP = new TGraph(NumRuns_Pol_45_PERP,RunNum_array_Pol_45_PERP,ThetaR_array_Pol_45_PERP);
  ThetaRTimeline_Pol_45_PERP -> SetTitle(";Run Number; Thetar");

  SigmaRTimeline_Pol_45_PERP = new TGraph(NumRuns_Pol_45_PERP,RunNum_array_Pol_45_PERP,SigmaR_array_Pol_45_PERP);
  SigmaRTimeline_Pol_45_PERP -> SetTitle(";Run Number; Sigmar");

  EdgeTimeline_Pol_90_PARA = new TGraph(NumRuns_Pol_90_PARA,RunNum_array_Pol_90_PARA,edge_array_Pol_90_PARA);
  EdgeTimeline_Pol_90_PARA -> SetTitle(";Run Number; Edge Position (MeV)");  

  SigmaTimeline_Pol_90_PARA = new TGraph(NumRuns_Pol_90_PARA,RunNum_array_Pol_90_PARA,sigma_array_Pol_90_PARA); 
  SigmaTimeline_Pol_90_PARA -> SetTitle(";Run Number; Sigma");

  ChisqTimeline_Pol_90_PARA = new TGraph(NumRuns_Pol_90_PARA,RunNum_array_Pol_90_PARA,chisq_array_Pol_90_PARA);
  ChisqTimeline_Pol_90_PARA -> SetTitle(";Run Number; Chisq");
   
  ThetaTimeline_Pol_90_PARA = new TGraph(NumRuns_Pol_90_PARA,RunNum_array_Pol_90_PARA,Theta_array_Pol_90_PARA);
  ThetaTimeline_Pol_90_PARA -> SetTitle(";Run Number; Theta");

  ThetaRTimeline_Pol_90_PARA = new TGraph(NumRuns_Pol_90_PARA,RunNum_array_Pol_90_PARA,ThetaR_array_Pol_90_PARA);
  ThetaRTimeline_Pol_90_PARA -> SetTitle(";Run Number; Thetar");

  SigmaRTimeline_Pol_90_PARA = new TGraph(NumRuns_Pol_90_PARA,RunNum_array_Pol_90_PARA,SigmaR_array_Pol_90_PARA);
  SigmaRTimeline_Pol_90_PARA -> SetTitle(";Run Number; Sigmar");
  
  EdgeTimeline_Pol_90_PERP = new TGraph(NumRuns_Pol_90_PERP,RunNum_array_Pol_90_PERP,edge_array_Pol_90_PERP);
  EdgeTimeline_Pol_90_PERP -> SetTitle(";Run Number; Edge Position (MeV)");   

  SigmaTimeline_Pol_90_PERP = new TGraph(NumRuns_Pol_90_PERP,RunNum_array_Pol_90_PERP,sigma_array_Pol_90_PERP); 
  SigmaTimeline_Pol_90_PERP -> SetTitle(";Run Number; Sigma");

  ChisqTimeline_Pol_90_PERP = new TGraph(NumRuns_Pol_90_PERP,RunNum_array_Pol_90_PERP,chisq_array_Pol_90_PERP);
  ChisqTimeline_Pol_90_PERP -> SetTitle(";Run Number; Chisq");
   
  ThetaTimeline_Pol_90_PERP = new TGraph(NumRuns_Pol_90_PERP,RunNum_array_Pol_90_PERP,Theta_array_Pol_90_PERP);
  ThetaTimeline_Pol_90_PERP -> SetTitle(";Run Number; Theta");

  ThetaRTimeline_Pol_90_PERP = new TGraph(NumRuns_Pol_90_PERP,RunNum_array_Pol_90_PERP,ThetaR_array_Pol_90_PERP);
  ThetaRTimeline_Pol_90_PERP -> SetTitle(";Run Number; Thetar");

  SigmaRTimeline_Pol_90_PERP = new TGraph(NumRuns_Pol_90_PERP,RunNum_array_Pol_90_PERP,SigmaR_array_Pol_90_PERP);
  SigmaRTimeline_Pol_90_PERP -> SetTitle(";Run Number; Sigmar");
  
  EdgeTimeline_Pol_135_PARA = new TGraph(NumRuns_Pol_135_PARA,RunNum_array_Pol_135_PARA,edge_array_Pol_135_PARA);
  EdgeTimeline_Pol_135_PARA -> SetTitle(";Run Number; Edge Position (MeV)");  

  SigmaTimeline_Pol_135_PARA = new TGraph(NumRuns_Pol_135_PARA,RunNum_array_Pol_135_PARA,sigma_array_Pol_135_PARA); 
  SigmaTimeline_Pol_135_PARA -> SetTitle(";Run Number; Sigma");

  ChisqTimeline_Pol_135_PARA = new TGraph(NumRuns_Pol_135_PARA,RunNum_array_Pol_135_PARA,chisq_array_Pol_135_PARA);
  ChisqTimeline_Pol_135_PARA -> SetTitle(";Run Number; Chisq");
   
  ThetaTimeline_Pol_135_PARA = new TGraph(NumRuns_Pol_135_PARA,RunNum_array_Pol_135_PARA,Theta_array_Pol_135_PARA);
  ThetaTimeline_Pol_135_PARA -> SetTitle(";Run Number; Theta");

  ThetaRTimeline_Pol_135_PARA = new TGraph(NumRuns_Pol_135_PARA,RunNum_array_Pol_135_PARA,ThetaR_array_Pol_135_PARA);
  ThetaRTimeline_Pol_135_PARA -> SetTitle(";Run Number; Thetar");

  SigmaRTimeline_Pol_135_PARA = new TGraph(NumRuns_Pol_135_PARA,RunNum_array_Pol_135_PARA,SigmaR_array_Pol_135_PARA);
  SigmaRTimeline_Pol_135_PARA -> SetTitle(";Run Number; Sigmar");
  
  EdgeTimeline_Pol_135_PERP = new TGraph(NumRuns_Pol_135_PERP,RunNum_array_Pol_135_PERP,edge_array_Pol_135_PERP);
  EdgeTimeline_Pol_135_PERP -> SetTitle(";Run Number; Edge Position (MeV)");   

  SigmaTimeline_Pol_135_PERP = new TGraph(NumRuns_Pol_135_PERP,RunNum_array_Pol_135_PERP,sigma_array_Pol_135_PERP); 
  SigmaTimeline_Pol_135_PERP -> SetTitle(";Run Number; Sigma");

  ChisqTimeline_Pol_135_PERP = new TGraph(NumRuns_Pol_135_PERP,RunNum_array_Pol_135_PERP,chisq_array_Pol_135_PERP);
  ChisqTimeline_Pol_135_PERP -> SetTitle(";Run Number; Chisq");
   
  ThetaTimeline_Pol_135_PERP = new TGraph(NumRuns_Pol_135_PERP,RunNum_array_Pol_135_PERP,Theta_array_Pol_135_PERP);
  ThetaTimeline_Pol_135_PERP -> SetTitle(";Run Number; Theta");

  ThetaRTimeline_Pol_135_PERP = new TGraph(NumRuns_Pol_135_PERP,RunNum_array_Pol_135_PERP,ThetaR_array_Pol_135_PERP);
  ThetaRTimeline_Pol_135_PERP -> SetTitle(";Run Number; Thetar");

  SigmaRTimeline_Pol_135_PERP = new TGraph(NumRuns_Pol_135_PERP,RunNum_array_Pol_135_PERP,SigmaR_array_Pol_135_PERP);
  SigmaRTimeline_Pol_135_PERP -> SetTitle(";Run Number; Sigmar");

   if(RunPeriod[0] == '1'){
     RunSeason = "Spring";
   }
   else if(RunPeriod[0] == '2'){
     RunSeason = "Fall";    
   }
   
   if (RunPeriod[2] == '1'){
     if (RunPeriod[3] == '6'){
       RunYear = "2016";
       RunAltYear = "16";
     }
     if (RunPeriod[3] == '7'){
       RunYear = "2017";
       RunAltYear = "17";
     }
     if (RunPeriod[3] == '8'){
       RunYear = "2018";
       RunAltYear = "18";
     }
     if (RunPeriod[3] == '9'){
       RunYear = "2019";
       RunAltYear = "19";
     }
   }
   else if(RunPeriod[2] =='2'){
     if (RunPeriod[3] == '0'){
       RunYear = "2020";
       RunAltYear = "20";
     }
     if (RunPeriod[3] == '1'){
       RunYear = "2021";
       RunAltYear = "21";
     }
     if (RunPeriod[3] == '2'){
       RunYear = "2022";
       RunAltYear = "22";
     }
     if (RunPeriod[3] == '3'){
       RunYear = "2023";
       RunAltYear = "23";
     }
     if (RunPeriod[3] == '4'){
       RunYear = "2024";
       RunAltYear = "24";
     } 
     if (RunPeriod[3] == '5'){
       RunYear = "2025";
       RunAltYear = "25";
     }
   }

   RunSeasonYear = RunSeason + RunAltYear;

   TCanvas * c2 = new TCanvas("ParameterCanvas", "ParameterCanvas");

   EdgeTimeline_Pol_0_PARA -> Draw("A*");  
   Filename = "HTML/ParameterTimelines/Edge" + RunSeasonYear + "_Pol_0_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaTimeline_Pol_0_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Sigma" + RunSeasonYear + "_Pol_0_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ChisqTimeline_Pol_0_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Chisq" + RunSeasonYear + "_Pol_0_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaTimeline_Pol_0_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Theta" + RunSeasonYear + "_Pol_0_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaRTimeline_Pol_0_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/ThetaR" + RunSeasonYear + "_Pol_0_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaRTimeline_Pol_0_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/SigmaR" + RunSeasonYear + "_Pol_0_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   
   EdgeTimeline_Pol_0_PERP -> Draw("A*");  
   Filename = "HTML/ParameterTimelines/Edge" + RunSeasonYear + "_Pol_0_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaTimeline_Pol_0_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Sigma" + RunSeasonYear + "_Pol_0_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ChisqTimeline_Pol_0_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Chisq" + RunSeasonYear + "_Pol_0_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaTimeline_Pol_0_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Theta" + RunSeasonYear + "_Pol_0_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaRTimeline_Pol_0_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/ThetaR" + RunSeasonYear + "_Pol_0_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaRTimeline_Pol_0_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/SigmaR" + RunSeasonYear + "_Pol_0_PERP.gif";
   c2->SaveAs(Filename.c_str()); 

   EdgeTimeline_Pol_45_PARA -> Draw("A*");  
   Filename = "HTML/ParameterTimelines/Edge" + RunSeasonYear + "_Pol_45_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaTimeline_Pol_45_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Sigma" + RunSeasonYear + "_Pol_45_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ChisqTimeline_Pol_45_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Chisq" + RunSeasonYear + "_Pol_45_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaTimeline_Pol_45_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Theta" + RunSeasonYear + "_Pol_45_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaRTimeline_Pol_45_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/ThetaR" + RunSeasonYear + "_Pol_45_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaRTimeline_Pol_45_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/SigmaR" + RunSeasonYear + "_Pol_45_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   
   EdgeTimeline_Pol_45_PERP -> Draw("A*");  
   Filename = "HTML/ParameterTimelines/Edge" + RunSeasonYear + "_Pol_45_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaTimeline_Pol_45_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Sigma" + RunSeasonYear + "_Pol_45_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ChisqTimeline_Pol_45_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Chisq" + RunSeasonYear + "_Pol_45_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaTimeline_Pol_45_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Theta" + RunSeasonYear + "_Pol_45_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaRTimeline_Pol_45_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/ThetaR" + RunSeasonYear + "_Pol_45_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaRTimeline_Pol_45_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/SigmaR" + RunSeasonYear + "_Pol_45_PERP.gif";
   c2->SaveAs(Filename.c_str());

   EdgeTimeline_Pol_90_PARA -> Draw("A*");  
   Filename = "HTML/ParameterTimelines/Edge" + RunSeasonYear + "_Pol_90_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaTimeline_Pol_90_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Sigma" + RunSeasonYear + "_Pol_90_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ChisqTimeline_Pol_90_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Chisq" + RunSeasonYear + "_Pol_90_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaTimeline_Pol_90_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Theta" + RunSeasonYear + "_Pol_90_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaRTimeline_Pol_90_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/ThetaR" + RunSeasonYear + "_Pol_90_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaRTimeline_Pol_90_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/SigmaR" + RunSeasonYear + "_Pol_90_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   
   EdgeTimeline_Pol_90_PERP -> Draw("A*");  
   Filename = "HTML/ParameterTimelines/Edge" + RunSeasonYear + "_Pol_90_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaTimeline_Pol_90_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Sigma" + RunSeasonYear + "_Pol_90_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ChisqTimeline_Pol_90_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Chisq" + RunSeasonYear + "_Pol_90_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaTimeline_Pol_90_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Theta" + RunSeasonYear + "_Pol_90_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaRTimeline_Pol_90_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/ThetaR" + RunSeasonYear + "_Pol_90_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaRTimeline_Pol_90_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/SigmaR" + RunSeasonYear + "_Pol_90_PERP.gif";
   c2->SaveAs(Filename.c_str()); 

   EdgeTimeline_Pol_135_PARA -> Draw("A*");  
   Filename = "HTML/ParameterTimelines/Edge" + RunSeasonYear + "_Pol_135_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaTimeline_Pol_135_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Sigma" + RunSeasonYear + "_Pol_135_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ChisqTimeline_Pol_135_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Chisq" + RunSeasonYear + "_Pol_135_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaTimeline_Pol_135_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Theta" + RunSeasonYear + "_Pol_135_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaRTimeline_Pol_135_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/ThetaR" + RunSeasonYear + "_Pol_135_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaRTimeline_Pol_135_PARA -> Draw("A*");
   Filename = "HTML/ParameterTimelines/SigmaR" + RunSeasonYear + "_Pol_135_PARA.gif";
   c2->SaveAs(Filename.c_str()); 
   
   EdgeTimeline_Pol_135_PERP -> Draw("A*");  
   Filename = "HTML/ParameterTimelines/Edge" + RunSeasonYear + "_Pol_135_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaTimeline_Pol_135_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Sigma" + RunSeasonYear + "_Pol_135_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ChisqTimeline_Pol_135_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Chisq" + RunSeasonYear + "_Pol_135_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaTimeline_Pol_135_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/Theta" + RunSeasonYear + "_Pol_135_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   ThetaRTimeline_Pol_135_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/ThetaR" + RunSeasonYear + "_Pol_135_PERP.gif";
   c2->SaveAs(Filename.c_str()); 
   SigmaRTimeline_Pol_135_PERP -> Draw("A*");
   Filename = "HTML/ParameterTimelines/SigmaR" + RunSeasonYear + "_Pol_135_PERP.gif";
   c2->SaveAs(Filename.c_str());
} 

void SavePeakPolTimeline(Int_t Pol_Angle, Bool_t isPara, string RunPeriod, const char * AllRunsList){
  string filenm;
  ifstream fileStream;
  Int_t NumRuns = 0;
  TGraph * PeakPolTimeline;
  Double_t MeanPol;
  Int_t RunNumLow;
  Int_t RunNumHigh;
  string ParaPerp = "";

  FillRunList(AllRunsList);

if(RunPeriod == "1/16"){
    RunNumHigh = 20000;
    RunNumLow = 10000;
  }
  if(RunPeriod == "2/16"){
    RunNumHigh = 30000;
    RunNumLow = 20000;
  }
  if(RunPeriod == "1/17"){
    RunNumHigh = 40000;
    RunNumLow = 30000;
  }
  if(RunPeriod == "1/18"){
    RunNumHigh = 50000;
    RunNumLow = 40000;
  }
  if(RunPeriod == "2/18"){
    RunNumHigh = 60000;
    RunNumLow = 50000;
  }
  if(RunPeriod == "1/19"){
    RunNumHigh = 70000;
    RunNumLow = 60000;
  }
  if(RunPeriod == "2/19"){
    RunNumHigh = 80000;
    RunNumLow = 70000;
  }

  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == Pol_Angle && RunList[i].isPara == isPara){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      NumRuns++;
      cout << NumRuns << endl;
    }
    fileStream.close();
  }
  
  Double_t peak_array[NumRuns];
  Double_t RunNum_array[NumRuns];
  Int_t n = 0;
  
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == Pol_Angle && RunList[i].isPara == isPara){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      cout << filenm << endl;
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      fileStream >> MeanPol;
      fileStream >> peak_array[n];
      RunNum_array[n] = stoi(RunList[i].RunNumber);
      n++; 
      fileStream.close();
    }
  }

  TCanvas * c2 = new TCanvas("PeakPolCanvas", "PeakPolCanvas");

  PeakPolTimeline = new TGraph(NumRuns-1, RunNum_array, peak_array);
  PeakPolTimeline -> Draw("A*");
  PeakPolTimeline -> GetYaxis()->SetRangeUser(0.0,0.5);

  string RunSeason;
  string RunYear;
  string RunAltYear;
  string RunSeasonYear;
  string TimelineTitle;

  if(RunPeriod[0] == '1'){
    RunSeason = "Spring";
  }
  else if(RunPeriod[0] == '2'){
    RunSeason = "Fall";    
  }

  if (RunPeriod[2] == '1'){
    if (RunPeriod[3] == '6'){
      RunYear = "2016";
      RunAltYear = "16";
    }
    if (RunPeriod[3] == '7'){
      RunYear = "2017";
      RunAltYear = "17";
    }
    if (RunPeriod[3] == '8'){
      RunYear = "2018";
      RunAltYear = "18";
    }
    if (RunPeriod[3] == '9'){
      RunYear = "2019";
      RunAltYear = "19";
    }
  }
  else if(RunPeriod[2] =='2'){
    if (RunPeriod[3] == '0'){
      RunYear = "2020";
      RunAltYear = "20";
    }
    if (RunPeriod[3] == '1'){
      RunYear = "2021";
      RunAltYear = "21";
    }
    if (RunPeriod[3] == '2'){
      RunYear = "2022";
      RunAltYear = "22";
    }
    if (RunPeriod[3] == '3'){
      RunYear = "2023";
      RunAltYear = "23";
    }
    if (RunPeriod[3] == '4'){
      RunYear = "2024";
      RunAltYear = "24";
    } 
    if (RunPeriod[3] == '5'){
      RunYear = "2025";
      RunAltYear = "25";
    }
  }

  RunSeasonYear = RunSeason + " " + RunYear;

  if(Pol_Angle == 0){
    TimelineTitle = RunSeasonYear + ", pol_0;Run Number; Peak Polarisation";
    PeakPolTimeline -> SetTitle(TimelineTitle.c_str());
  }
  else if(Pol_Angle == 45){
    TimelineTitle = RunSeasonYear + ", pol_45;Run Number; Peak Polarisation";
    PeakPolTimeline -> SetTitle(TimelineTitle.c_str());
  }
  else if(Pol_Angle == 90){
    TimelineTitle = RunSeasonYear + ", pol_90;Run Number; Peak Polarisation";
    PeakPolTimeline -> SetTitle(TimelineTitle.c_str());
  }
  else if(Pol_Angle == 135){
    TimelineTitle = RunSeasonYear + ", pol_135;Run Number; Peak Polarisation";
    PeakPolTimeline -> SetTitle(TimelineTitle.c_str());
  }  

  if(isPara == true){
    ParaPerp = "_PARA";
  }
  else if(isPara == false){
    ParaPerp = "_PERP";
  }

  string FileName = "HTML/PeakPolTimelines/" + RunSeason + RunAltYear + "_pol" + to_string(Pol_Angle) + ParaPerp + ".gif"; 
  c2->SaveAs(FileName.c_str());  
}

void ChanPolTimeline(Int_t chan, string RunPeriod, string ChanPolDir = "ChanPolTimelines"){

  string filenm;
  ifstream fileStream;
  Int_t RunNumLow;
  Int_t RunNumHigh;
  Int_t num_0_runs = 0;
  Int_t num_45_runs = 0;
  Int_t num_90_runs = 0;
  Int_t num_135_runs = 0;

  vector <Int_t> Pol_0_RunNums;
  vector <Int_t> Pol_45_RunNums;
  vector <Int_t> Pol_90_RunNums;
  vector <Int_t> Pol_135_RunNums;

  vector <vector<Double_t>> Pol_0;
  vector <vector<Double_t>> Pol_45;
  vector <vector<Double_t>> Pol_90;
  vector <vector<Double_t>> Pol_135;

  if(RunPeriod == "1/16"){
    RunNumHigh = 20000;
    RunNumLow = 10000;
  }
  if(RunPeriod == "2/16"){
    RunNumHigh = 30000;
    RunNumLow = 20000;
  }
  if(RunPeriod == "1/17"){
    RunNumHigh = 40000;
    RunNumLow = 30000;
  }
  if(RunPeriod == "1/18"){
    RunNumHigh = 50000;
    RunNumLow = 40000;
  }
  if(RunPeriod == "2/18"){
    RunNumHigh = 60000;
    RunNumLow = 50000;
  }
  if(RunPeriod == "1/19"){
    RunNumHigh = 70000;
    RunNumLow = 60000;
  }
  if(RunPeriod == "2/19"){
    RunNumHigh = 80000;
    RunNumLow = 70000;
  }

  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 0){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      num_0_runs++;
    }
    fileStream.close();
  }
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 45){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      num_45_runs++;
    }
    fileStream.close();
  }
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 90){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      num_90_runs++;
    }
    fileStream.close();
  }
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 135){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      num_135_runs++;
    }
    fileStream.close();
  }

   for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 0){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/ChanPolVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      vector <Double_t> ChanPolVals;
      Double_t ChanPol;
      for(Int_t chan = 0; chan < 216; chan++){
	fileStream >> ChanPol;
	ChanPolVals.push_back(ChanPol);
      }
      Pol_0.push_back(ChanPolVals);
      Pol_0_RunNums.push_back(stoi(RunList[i].RunNumber));
      
    }
    fileStream.close();
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 45){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/ChanPolVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      vector <Double_t> ChanPolVals;
      Double_t ChanPol;
      for(Int_t chan = 0; chan < 216; chan++){
	fileStream >> ChanPol;
	ChanPolVals.push_back(ChanPol);
      }
      Pol_45.push_back(ChanPolVals);
      Pol_45_RunNums.push_back(stoi(RunList[i].RunNumber));
      
    }
    fileStream.close();
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 90){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/ChanPolVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      vector <Double_t> ChanPolVals;
      Double_t ChanPol;
      for(Int_t chan = 0; chan < 216; chan++){
	fileStream >> ChanPol;
	ChanPolVals.push_back(ChanPol);
      }
      Pol_90.push_back(ChanPolVals);
      Pol_90_RunNums.push_back(stoi(RunList[i].RunNumber));
      
    }
    fileStream.close();
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 135){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/ChanPolVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      vector <Double_t> ChanPolVals;
      Double_t ChanPol;
      for(Int_t chan = 0; chan < 216; chan++){
	fileStream >> ChanPol;
	ChanPolVals.push_back(ChanPol);
      }
      Pol_135.push_back(ChanPolVals);
      Pol_135_RunNums.push_back(stoi(RunList[i].RunNumber));
      
    }
    fileStream.close();
   }

   Double_t runs_135_arr[num_135_runs];
   Double_t runs_90_arr[num_90_runs];
   Double_t runs_45_arr[num_45_runs];
   Double_t runs_0_arr[num_0_runs];
   
   Double_t runs_135_Xarr[num_135_runs];
   Double_t runs_90_Xarr[num_90_runs];
   Double_t runs_45_Xarr[num_45_runs];
   Double_t runs_0_Xarr[num_0_runs];
   
   for(Int_t i = 0; i < num_135_runs; i++){
     runs_135_arr[i] = Pol_135[i][chan];
     runs_135_Xarr[i] = Pol_135_RunNums[i]; 
   }
   for(Int_t i = 0; i < num_90_runs; i++){
     runs_90_arr[i] = Pol_90[i][chan];
     runs_90_Xarr[i] = Pol_90_RunNums[i];
   }
   for(Int_t i = 0; i < num_45_runs; i++){
     runs_45_arr[i] = Pol_45[i][chan];
     runs_45_Xarr[i] = Pol_45_RunNums[i];
   }
   for(Int_t i = 0; i < num_0_runs; i++){
     runs_0_arr[i] = Pol_0[i][chan];
     runs_0_Xarr[i] = Pol_0_RunNums[i];
   }

  TGraph * Pol_135_Timeline = new TGraph(num_135_runs,runs_135_Xarr,runs_135_arr);
  Pol_135_Timeline -> SetNameTitle("Pol_135","Pol_135"); 
  TGraph * Pol_90_Timeline  = new TGraph(num_90_runs,runs_90_Xarr,runs_90_arr);
  Pol_90_Timeline -> SetNameTitle("Pol_90","Pol_90");
  TGraph * Pol_45_Timeline  = new TGraph(num_45_runs,runs_45_Xarr,runs_45_arr);
  Pol_45_Timeline -> SetNameTitle("Pol_45","Pol_45");
  TGraph * Pol_0_Timeline   = new TGraph(num_0_runs,runs_0_Xarr,runs_0_arr);
  Pol_0_Timeline -> SetNameTitle("Pol_0","Pol_0");

  string rootFileName = ChanPolDir + "/CBrem_Channel_" + to_string(chan) + "_Polar_Out.root";
  const char * rootFileNameChar = rootFileName.c_str();
  TFile * OutFile= new TFile(rootFileNameChar,"recreate");

  OutFile -> cd();
  OutFile -> GetList()->Add(Pol_0_Timeline);
  OutFile -> GetList()->Add(Pol_90_Timeline);
  OutFile -> GetList()->Add(Pol_135_Timeline);
  OutFile -> GetList()->Add(Pol_45_Timeline);
  OutFile -> Write();
  OutFile -> Close("R");
}

void GetAllChanTimelines(string RunPeriod, string ChanPolDir = "ChanPolTimeline"){
  for(Int_t i = 0; i < 216; i++){ 
    ChanPolTimeline(i, RunPeriod, ChanPolDir);
    cout << "Finished channel " << i << endl;    
  }
  cout << "Timelines have been generated" << endl;
}

Double_t GetChannelEnergy(Int_t Channel, string RunPeriod){
  Double_t ChannelEnergy;
  Double_t AllChannelEnergies[285]; 
  FILE * efile;
  string efileName;
  string RunSeason;
  string RunYear;
  string RunAltYear;

   if(RunPeriod[0] == '1'){
     RunSeason = "Spring";
   }
   else if(RunPeriod[0] == '2'){
     RunSeason = "Fall";    
   }
   
   if (RunPeriod[2] == '1'){
     if (RunPeriod[3] == '6'){
       RunYear = "2016";
       RunAltYear = "16";
     }
     if (RunPeriod[3] == '7'){
       RunYear = "2017";
       RunAltYear = "17";
     }
     if (RunPeriod[3] == '8'){
       RunYear = "2018";
       RunAltYear = "18";
     }
     if (RunPeriod[3] == '9'){
       RunYear = "2019";
       RunAltYear = "19";
     }
   }
   else if(RunPeriod[2] =='2'){
     if (RunPeriod[3] == '0'){
       RunYear = "2020";
       RunAltYear = "20";
     }
     if (RunPeriod[3] == '1'){
       RunYear = "2021";
       RunAltYear = "21";
     }
     if (RunPeriod[3] == '2'){
       RunYear = "2022";
       RunAltYear = "22";
     }
     if (RunPeriod[3] == '3'){
       RunYear = "2023";
       RunAltYear = "23";
     }
     if (RunPeriod[3] == '4'){
       RunYear = "2024";
       RunAltYear = "24";
     } 
     if (RunPeriod[3] == '5'){
       RunYear = "2025";
       RunAltYear = "25";
     }
   }
   
   efileName = "Efiles/" + RunSeason + RunAltYear + "Efile";
   efile = fopen(efileName.c_str(), "r");

   for(Int_t nbins=1;nbins<285;nbins++){
     if(fscanf(efile,"%lg",&AllChannelEnergies[nbins])==EOF) break; 
   }
   fclose(efile);
   
   ChannelEnergy = AllChannelEnergies[Channel];
   
   return(ChannelEnergy);

}

string to_string_with_precision(const Double_t a_value, const int n = 6)
{
    ostringstream out;
    out.precision(n);
    out << fixed << a_value;
    return(out.str());
}

void SaveChanTimeline(Int_t chan, Int_t pol, string RunPeriod, string ChanPolDir =  "ChanPolTimeline"){
  Double_t ChanEnergy;
  string ChanEnergyStr;
  TGraph *ChanPol;

  string RunSeason;
  string RunYear;
  string RunAltYear;
  string RunSeasonYear;

  if(RunPeriod[0] == '1'){
    RunSeason = "Spring";
  }
  else if(RunPeriod[0] == '2'){
    RunSeason = "Fall";    
  }

  if (RunPeriod[2] == '1'){
    if (RunPeriod[3] == '6'){
      RunYear = "2016";
      RunAltYear = "16";
    }
    if (RunPeriod[3] == '7'){
      RunYear = "2017";
      RunAltYear = "17";
    }
    if (RunPeriod[3] == '8'){
      RunYear = "2018";
      RunAltYear = "18";
    }
    if (RunPeriod[3] == '9'){
      RunYear = "2019";
      RunAltYear = "19";
    }
  }
  else if(RunPeriod[2] =='2'){
    if (RunPeriod[3] == '0'){
      RunYear = "2020";
      RunAltYear = "20";
    }
    if (RunPeriod[3] == '1'){
      RunYear = "2021";
      RunAltYear = "21";
    }
    if (RunPeriod[3] == '2'){
      RunYear = "2022";
      RunAltYear = "22";
    }
    if (RunPeriod[3] == '3'){
      RunYear = "2023";
      RunAltYear = "23";
    }
    if (RunPeriod[3] == '4'){
      RunYear = "2024";
      RunAltYear = "24";
    } 
    if (RunPeriod[3] == '5'){
      RunYear = "2025";
      RunAltYear = "25";
    }
  }

  RunSeasonYear = RunSeason  + RunAltYear;

  string imgDir =  "HTML/PolarTimelines_" + RunSeasonYear + "/";
  string rootfileName = ChanPolDir + "/CBrem_Channel_" + to_string(chan) + "_Polar_Out.root";
  const char * rootfileNameChar = rootfileName.c_str();
  cout << "Root file name = " << rootfileNameChar << endl;
  TFile *rootfile = TFile::Open(rootfileNameChar);
  string PolOrientation;

  ChanEnergy = GetChannelEnergy(chan, RunPeriod);
  ChanEnergyStr = to_string_with_precision(ChanEnergy, 3);
  string Pol_0_Labels_string = "Pol_0 Polarisation Timeline, Photon Energy = " + ChanEnergyStr + " GeV;Run number;Polarisation;";
  string Pol_45_Labels_string = "Pol_45 Polarisation Timeline, Photon Energy = " + ChanEnergyStr + " GeV;Run number;Polarisation;";
  string Pol_90_Labels_string = "Pol_90 Polarisation Timeline, Photon Energy = " + ChanEnergyStr + " GeV;Run number;Polarisation;";
  string Pol_135_Labels_string = "Pol_135 Polarisation Timeline, Photon Energy = " + ChanEnergyStr + " GeV;Run number;Polarisation;";
  const char * Pol_0_Labels = Pol_0_Labels_string.c_str();
  const char * Pol_45_Labels = Pol_45_Labels_string.c_str();
  const char * Pol_90_Labels = Pol_90_Labels_string.c_str();
  const char * Pol_135_Labels = Pol_135_Labels_string.c_str();

  if(pol == 0){
    ChanPol = (TGraph*)rootfile->Get("Pol_0");
    ChanPol->SetTitle(Pol_0_Labels);
    ChanPol -> GetHistogram() -> SetMaximum(0.4);
    ChanPol -> GetHistogram() -> SetMinimum(0.0);
    PolOrientation = "Pol_0";
  }
  else if(pol == 45){
    ChanPol = (TGraph*)rootfile->Get("Pol_45");
    ChanPol->SetTitle(Pol_45_Labels);
    ChanPol -> GetHistogram() -> SetMaximum(0.4);
    ChanPol -> GetHistogram() -> SetMinimum(0.0);
    PolOrientation = "Pol_45";
  }
  else if(pol == 90){
    ChanPol = (TGraph*)rootfile->Get("Pol_90");
    ChanPol->SetTitle(Pol_90_Labels);
    ChanPol -> GetHistogram() -> SetMaximum(0.4);
    ChanPol -> GetHistogram() -> SetMinimum(0.0);
    PolOrientation = "Pol_90";
  }
  else if(pol == 135){
    ChanPol = (TGraph*)rootfile->Get("Pol_135"); 
    ChanPol->SetTitle(Pol_135_Labels);
    ChanPol -> GetHistogram() -> SetMaximum(0.4);
    ChanPol -> GetHistogram() -> SetMinimum(0.0);
    PolOrientation = "Pol_135";
  }
  string filename =  PolOrientation + "_Chan_" + to_string(chan) + ".gif";
  TCanvas * c2 = new TCanvas("PolarCanvas", "PolarCanvas");
  ChanPol-> Draw("A*");
  c2->SaveAs((imgDir + filename).c_str());
  cout << "Saved " << imgDir + filename << endl;
  rootfile -> Close("R");
  gROOT -> CloseFiles();
}

void SaveChanTimelines(string RunPeriod, const char * AllRunsList, string ChanPolDir =  "ChanPolTimelines", Int_t NumChans = 215){
  FillRunList(AllRunsList);
  cout << "Making channel timelines..." << endl;
  GetAllChanTimelines(RunPeriod, ChanPolDir);
  cout << "Saving channel timeline gifs..." << endl;
  for (Int_t chan = 0; chan < NumChans +1; chan++){
    cout << "Saving channel " << chan << " hists" << endl;
    SaveChanTimeline(chan, 0, RunPeriod, ChanPolDir);
    SaveChanTimeline(chan, 45, RunPeriod, ChanPolDir);
    SaveChanTimeline(chan, 90, RunPeriod, ChanPolDir);
    SaveChanTimeline(chan, 135, RunPeriod, ChanPolDir);
  }
  cout << "Timeline gifs saved" << endl;
}

TGraph * meanPolPlot_135;
TGraph * meanPolPlot_90;
TGraph * meanPolPlot_45;
TGraph * meanPolPlot_0;

void PlotMeanPol(Int_t pol_angle, const char * AllRunsList, string RunPeriod = "1/17"){
  Double_t meanVals_135[300];
  Double_t meanVals_90[300];
  Double_t meanVals_45[300];
  Double_t meanVals_0[300];
  Double_t runs_135_Xarr[300];
  Double_t runs_90_Xarr[300];
  Double_t runs_45_Xarr[300];
  Double_t runs_0_Xarr[300];
  Int_t num_135runs = 0;
  Int_t num_90runs = 0;
  Int_t num_45runs = 0;
  Int_t num_0runs = 0;
  Int_t RunNumLow;
  Int_t RunNumHigh;
  ifstream fileStream;
  string filenm;
  Double_t peak;

  FillRunList(const char * AllRunsList);

  if(RunPeriod == "1/16"){
    RunNumHigh = 20000;
    RunNumLow = 10000;
  }
  if(RunPeriod == "2/16"){
    RunNumHigh = 30000;
    RunNumLow = 20000;
  }
  if(RunPeriod == "1/17"){
    RunNumHigh = 40000;
    RunNumLow = 30000;
  }
  if(RunPeriod == "1/18"){
    RunNumHigh = 50000;
    RunNumLow = 40000;
  }
  if(RunPeriod == "2/18"){
    RunNumHigh = 60000;
    RunNumLow = 50000;
  }
  if(RunPeriod == "1/19"){
    RunNumHigh = 70000;
    RunNumLow = 60000;
  }
  if(RunPeriod == "2/19"){
    RunNumHigh = 80000;
    RunNumLow = 70000;
  }
  
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 0){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      
      fileStream >> meanVals_0[num_0runs];
      fileStream >> peak;
      runs_0_Xarr[num_0runs] = stoi(RunList[i].RunNumber);
      num_0runs++; 
      fileStream.close();
    }
    else if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 45){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      
      fileStream >> meanVals_45[num_45runs];
      fileStream >> peak;
      runs_45_Xarr[num_45runs] = stoi(RunList[i].RunNumber);
      num_45runs++; 
      fileStream.close();
    }
    else if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 90){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      
      fileStream >> meanVals_90[num_90runs];
      fileStream >> peak;
      runs_90_Xarr[num_90runs] = stoi(RunList[i].RunNumber);
      num_90runs++; 
      fileStream.close();
    }
    else if(stoi(RunList[i].RunNumber) > RunNumLow && stoi(RunList[i].RunNumber) < RunNumHigh  && RunList[i].CrystalOrientation == 135){
      filenm = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/MeanPeakVals.dat";
      fileStream.open(filenm);
      if(!fileStream){
	continue;
      }
      
      fileStream >> meanVals_135[num_135runs];
      fileStream >> peak;
      runs_135_Xarr[num_135runs] = stoi(RunList[i].RunNumber);
      num_135runs++; 
      fileStream.close();
    }
  }
 
  meanPolPlot_135 = new TGraph(num_135runs, runs_135_Xarr, meanVals_135);
  meanPolPlot_90 = new TGraph(num_90runs, runs_90_Xarr, meanVals_90);
  meanPolPlot_45 = new TGraph(num_45runs, runs_45_Xarr, meanVals_45);
  meanPolPlot_0 = new TGraph(num_0runs, runs_0_Xarr, meanVals_0);

  if(pol_angle == 0){
    meanPolPlot_0 -> SetMarkerStyle(21);
    meanPolPlot_0 -> SetTitle("Mean_Pol_0");
    meanPolPlot_0 -> GetHistogram() -> SetMaximum(0.4);
    meanPolPlot_0 -> GetHistogram() -> SetMinimum(0.0);
    meanPolPlot_0 -> Draw("AP");
  } 
  if(pol_angle == 45){
    meanPolPlot_45 -> SetMarkerStyle(21);
    meanPolPlot_45 -> SetTitle("Mean_Pol_45");
    meanPolPlot_45 -> GetHistogram() -> SetMaximum(0.4);
    meanPolPlot_45 -> GetHistogram() -> SetMinimum(0.0);
    meanPolPlot_45 -> Draw("AP");
  } 
  if(pol_angle == 90){
    meanPolPlot_90 -> SetMarkerStyle(21);
    meanPolPlot_90 -> SetTitle("Mean_Pol_90");
    meanPolPlot_90 -> GetHistogram() -> SetMaximum(0.4);
    meanPolPlot_90 -> GetHistogram() -> SetMinimum(0.0);
    meanPolPlot_90 -> Draw("AP");
  } 
  if(pol_angle == 135){
    meanPolPlot_135 -> SetMarkerStyle(21);
    meanPolPlot_135 -> SetTitle("Mean_Pol_135");
    meanPolPlot_135 -> GetHistogram() -> SetMaximum(0.4);
    meanPolPlot_135 -> GetHistogram() -> SetMinimum(0.0);
    meanPolPlot_135 -> Draw("AP");
  } 
}

TGraphErrors * RhoMeasurements_0;
TGraphErrors * RhoMeasurements_45;
TGraphErrors * RhoMeasurements_90;
TGraphErrors * RhoMeasurements_135;

void PlotRhoPolar(Int_t polOr){

  TFile * RhoFile;
  TTree * RhoTree;
  Int_t run_num;
  Double_t direction;
  Double_t psigma;
  Double_t psigma_err; 

  RhoMeasurements_0 = new TGraphErrors();
  RhoMeasurements_45 = new TGraphErrors();
  RhoMeasurements_90 = new TGraphErrors();
  RhoMeasurements_135 = new TGraphErrors();

  RhoMeasurements_0 -> GetXaxis() -> SetRangeUser(30200, 31200);
  RhoMeasurements_45 -> GetXaxis() -> SetRangeUser(30200, 31200);
  RhoMeasurements_90 -> GetXaxis() -> SetRangeUser(30200, 31200);
  RhoMeasurements_135 -> GetXaxis() -> SetRangeUser(30200, 31200);

  RhoFile = TFile::Open("RhoDataSpring17.root");
  RhoTree = (TTree*)RhoFile->Get("tree");

  RhoTree -> SetBranchAddress("run", &run_num);
  RhoTree -> SetBranchAddress("direction", &direction);
  RhoTree -> SetBranchAddress("psigma", &psigma);
  RhoTree -> SetBranchAddress("psigma_err", &psigma_err);

  Long64_t nentries = RhoTree -> GetEntries();

  for(int i=0; i<nentries;i++){
    if(RhoTree -> GetEntry(i) < 1) continue;
    if(run_num == 0 || psigma == 0) continue;
    if(direction == 0){
      RhoMeasurements_0 -> SetPoint(i, run_num, abs((1/0.9)*psigma));
      RhoMeasurements_0 -> SetPointError(i, 0, psigma_err);
    }
    if(direction == 45){
      RhoMeasurements_45 -> SetPoint(i, run_num, abs((1/0.9)*psigma));
      RhoMeasurements_45 -> SetPointError(i, 0, psigma_err);
    }
    if(direction == 90){
      RhoMeasurements_90 -> SetPoint(i, run_num, abs((1/0.9)*psigma));
      RhoMeasurements_90 -> SetPointError(i, 0, psigma_err);
    }
    if(direction == 135){
      RhoMeasurements_135 -> SetPoint(i, run_num, abs((1/0.9)*psigma));
      RhoMeasurements_135 -> SetPointError(i, 0, psigma_err);
    }
  }

  RhoMeasurements_0 -> GetXaxis() -> SetRangeUser(30200, 31200);
  RhoMeasurements_45 -> GetXaxis() -> SetRangeUser(30200, 31200);
  RhoMeasurements_90 -> GetXaxis() -> SetRangeUser(30200, 31200);
  RhoMeasurements_135 -> GetXaxis() -> SetRangeUser(30200, 31200);

  if(polOr == 0){
    RhoMeasurements_0 -> SetMarkerStyle(21);
    RhoMeasurements_0 -> SetMarkerColor(kRed);
    RhoMeasurements_0 -> Draw("P");
  } 
  if(polOr == 45){
    RhoMeasurements_45 -> SetMarkerStyle(21);
    RhoMeasurements_45 -> SetMarkerColor(kRed);
    RhoMeasurements_45 -> Draw("P");
  } 
  if(polOr == 90){
    RhoMeasurements_90 -> SetMarkerStyle(21);
    RhoMeasurements_90 -> SetMarkerColor(kRed);
    RhoMeasurements_90 -> Draw("P");
  } 
  if(polOr == 135){
    RhoMeasurements_135 -> SetMarkerStyle(21);
    RhoMeasurements_135 -> SetMarkerColor(kRed);
    RhoMeasurements_135 -> Draw("P");
  } 
}

void SaveRhoComparison(Int_t pol_angle, const char * AllRunsList){
  TCanvas * c2 = new TCanvas("RhoComparisonCanvas", "RhoComparisonCanvas");
  FillRunList(const char * AllRunsList);
  PlotMeanPol(pol_angle);
  PlotRhoPolar(pol_angle);
  auto legend = new TLegend(0.1,0.1,0.48,0.3);
  legend->SetHeader("Mean Pol Data","C");
  if(pol_angle == 0){
    legend->AddEntry(RhoMeasurements_0,"Rho Measurements","P");
    legend->AddEntry(meanPolPlot_0,"Fit Predictions","P");
  }
  if(pol_angle == 45){
    legend->AddEntry(RhoMeasurements_45,"Rho Measurements","P");
    legend->AddEntry(meanPolPlot_45,"Fit Predictions","P");
  }  
  if(pol_angle == 90){
    legend->AddEntry(RhoMeasurements_90,"Rho Measurements","P");
    legend->AddEntry(meanPolPlot_90,"Fit Predictions","P");
  }
  if(pol_angle == 135){
    legend->AddEntry(RhoMeasurements_135,"Rho Measurements","P");
    legend->AddEntry(meanPolPlot_135,"Fit Predictions","P");
  } 

  legend->Draw(); 
  string filename = "HTML/RhoComparisons/pol_" + to_string(pol_angle) + ".gif";
  c2->SaveAs(filename.c_str());  
} 

void Make_HTML_Plots(string RunPeriod, const char * AllRunsList){
  FillRunList(AllRunsList);
  SaveParamTimelines(RunPeriod);
  SavePeakPolTimeline(0, true, RunPeriod);
  SavePeakPolTimeline(0, false, RunPeriod);
  SavePeakPolTimeline(45, true, RunPeriod);
  SavePeakPolTimeline(45, false, RunPeriod);
  SavePeakPolTimeline(90, true, RunPeriod);
  SavePeakPolTimeline(90, false, RunPeriod);
  SavePeakPolTimeline(135, true, RunPeriod);
  SavePeakPolTimeline(135, false, RunPeriod);
  SaveChanTimelines(RunPeriod);
}
