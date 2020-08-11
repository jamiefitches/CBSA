#include "CBSA.h"
#include "unistd.h"   
#include <stdio.h>
#include <iostream> 
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h> 
#include <TMinuit.h>
#include <TH1.h>
#include <TH2.h>
#include <TLine.h>
#include <TSystem.h>
#include <TStyle.h>
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom2.h"
#include "TGraphErrors.h"
#include "TError.h"
#include "TVirtualFitter.h"

using namespace std; 

Double_t fitMin = 6000.0;
Double_t fitMax = 10200.0;
Int_t numVs = 2;
Bool_t isFittable = false;

Double_t GausOnBase(Double_t *, Double_t *);
Double_t efit(const Double_t *);
void fitDataB(char const *fname, char const * RunNum, Double_t beamMeV, Double_t colliDist_m, Double_t colliDia_mm, string OutDir, Bool_t HighChisq, char const * ChPk = "/ChisqPlots/", Char_t *outfile = NULL, Double_t emin = fitMin, Double_t emax = fitMax, Int_t nVec = numVs,Double_t baseline = 1.0, Double_t ff=100.0);
void fitData(char const *fname, char const * RunNum, Char_t *outfile = NULL, Double_t beamMeV = 100, Double_t emin = fitMin, Double_t emax = fitMax, Double_t colliDist_m = 76.0, Double_t colliDia_mm = 5, Int_t nVec = numVs,Double_t baseline = 1.0, Double_t ff=100.0, Bool_t HighChisq = false, Bool_t SaveCanvas = 0, string OutDir = "", char const * EnhDatPol = "/Run_");
void enhFromHuman(Double_t beamMeV = 100, Double_t edgeMeV = 700.0, Double_t spreadMeV = 40.0, Double_t colliDist_m = 76.0, Double_t colliDia_mm = 5, Int_t nVec = numVs);
void parFromHuman(Double_t beamMeV = 100, Double_t edgeMeV = 700.0, Double_t spreadMeV = 40.0, Double_t colliDist_m = 76.0, Double_t colliDia_mm = 5, Int_t nVec = numVs, Double_t *par=NULL);
void enhFromParams(Double_t *par=NULL);
void makeSimEnh(Char_t *outfile = NULL, Double_t sigma=0.01);

enum {
  EDGE_T,
  SIGMA_T,
  CHISQ_T,
  THETA_T,
  THETAR_T,
  SIGMAR_T};

Double_t ThreshOut[7]; 

//Some enumerators and names
enum {      
  THETA,  // [0] theta      main angle responsible for coherent edge cutoffs
  SIGMA,  // [1] sigma      smearing of theta
  THETAR, // [2] thetar     relative angle resonsible for colli cutoffs
  SIGMAR, // [3] sigmar     smearing of colli cutoff angle
  E0MEV,  // [4] beam energy
  NVEC,   // [5] nvec       no of vectors contributing (1-4)
  IVEC};  // [6] ivec[]     array of intensities of vectors up to nvec.

// Some basic consts etc first
// Consts are all UPPER CASE

Bool_t isDataGood = false;

//Approx Form factor is F(g^2) = (q^2 + b^(-2)) ^ -2
//Where b= 111 x Z^(-1/3) (x 925 to get into units of crystal lattice)
const Double_t B = 0.247892436;  //where did I get that ? Timm ?
const Double_t A = 0.03;           //made up for now, need to get the actual no for this later
const Double_t k = 26.5601;        //put in formula for k later (my own stonehenge paper)

const Int_t VECTORS[] = {2,4,6,8,10};  //list of the vectors to be included (022,044);

Int_t counter = 1;

Int_t THETASTEPS = 201;          //no of steps in convoluting with gaussian

//All histograms and related are globals
TH1F *histP = NULL;              //pol
TH1F *histE = NULL;              //enh from calculation

TH1F *histD = NULL;              //enh from data to be fitted

TGraph *graphPvsBase=NULL;       //graphs of chisq and max pol vs baseline
TGraph *graphCvsBase=NULL;       //

 
//these are really just convenient arrays - they don't ever get plotted.
TH1F *weightHist  = NULL;
TH2F *thetaWeight = NULL;
TH2F *thetaPol    = NULL;
TH2F *thetaTtot   = NULL;
TH2F *thetaItot   = NULL;

Int_t    histCount=0;
 
Double_t energy[1000];
Double_t enhancement[1000];
Double_t energyBins[1000];
Int_t    nBins=0;

Double_t fitMinEnergy; //Max and Min energy for using in the fit
Double_t fitMaxEnergy;
Int_t    fitMinBin;    //and corresponding bins   
Int_t    fitMaxBin;
Int_t    verbose=0;
Double_t bestPar[10];
Double_t bestChisq;

TF1     *gausFit;

TCanvas *genCanvas=NULL;
TCanvas *graphCanvas=NULL;

Double_t baseScale[50];
Double_t baseChisq[50];
Double_t basePol[50];
Int_t    baseN=0;
//general one off init things
Bool_t isInit=kFALSE;

void init(){
  gStyle->SetOptStat(kFALSE);
  isInit=kTRUE;
  gausFit=new TF1("gausFit",GausOnBase,0,100,4);
  genCanvas = new TCanvas("genCanvas","genCanvas",50,50,800,1000);
  genCanvas->Divide(1,2);   
  genCanvas->GetPad(1)->SetGridx(1);
  genCanvas->GetPad(1)->SetGridy(1);
  genCanvas->GetPad(2)->SetGridx(1);
  genCanvas->GetPad(2)->SetGridy(1);
}

//fit of a gaussian on a baseline, for gausFit,
Double_t GausOnBase(Double_t *x, Double_t *par) {
  Double_t arg = 0;
  if (par[2] != 0) arg = (x[0] - par[1])/par[2];
   Double_t fitval = par[3] + par[0]*TMath::Exp(-0.5*arg*arg);
   return fitval;
}

//The main customized fitting function which gets called by MINUIT with the current value of the parms.
Double_t efit(const Double_t *parms){
  
  Double_t chisq = 0.0;
  Double_t delta;
  Double_t b1,b2;
  Double_t *par = (Double_t*)parms;

  histE->Reset("ICE");                     //reset the histogram for calculated enhancement
  enhFromParams(par);                      //now call the function to make the enhancement and polarization

  for(int n=fitMinBin+1;n<=fitMaxBin;n++){ //loop over all the required bins in the histogram to work out a chisq
    b1=histE->GetBinContent(n);            //this is the variable which causes the 'nan' problems. 
    if(std::isfinite(b1) == 0){
      chisq+=100;
      continue;
      }
    b2=histD->GetBinContent(n);
    if(std::isfinite(b2) == 0){
      chisq+=100;
      continue;
    }
    delta=(b1-b2);
    if(std::isfinite(delta) == 0){
      chisq+=100;
      continue;
    }
    chisq+=(delta*delta)/b1;               //note - not a proper chisq because its an enhancement
    }
   
  fprintf(stderr,"Chisq: \t%6.2f\t\r",chisq); //print it out as we go

  if(chisq<bestChisq && par[1] < 0.001){                     //in case fit is called more than once, save the best result
    bestChisq=chisq;
    for(int n=0;n<10;n++){
      bestPar[n]=par[n];
    }
    if(verbose){	                   //if verbose, draw every 10th one the canvas to see how it's going
      if(10%(counter++)){

	genCanvas->cd(1);
	histD->SetLineColor(4);
	histD->Draw("HISTP");
	histD->SetMinimum(0.0);
	histD->SetMaximum(6.0);
	genCanvas->cd(1);
	histE->Draw("HIST same");
	
	genCanvas->cd(2);
	histP->Draw("HIST");
	histP->SetMinimum(0);
	histP->SetMaximum(1);
	
	genCanvas->Draw();   
	
	genCanvas->Update();
	gSystem->ProcessEvents();
	counter=1;
      }
    }
  }
  return abs(chisq);                            //This is what MINUIT minimises on
  
}

void fitDataB(char const *fname, char const * RunNum, Double_t beamMeV, Double_t colliDist_m, Double_t colliDia_mm, string OutDir, Bool_t HighChisq, char const * ChPk, Char_t *outfile, Double_t emin, Double_t emax, Int_t nVec, Double_t baseline, Double_t ff){
  //Runs the fitData() function over 20 baseline scaling factors to find the one with the best chisq. 
  //Note that nVec is essentially the number of peaks on the enhancement plot

  Double_t minChisq=100.0;
  Int_t minIndex=0;
  baseN=0;
  char ChPkFlNm[200];

  string ChPkSt(ChPk);
  string ChDir = OutDir + ChPkSt;
  char const * ChDirCh = ChDir.c_str();

  strcpy(ChPkFlNm,ChDirCh);
  strcat(ChPkFlNm,RunNum);
  strcat(ChPkFlNm,".root");
  TFile * ChPkFl = new TFile(ChPkFlNm, "RECREATE");

  for(Double_t b = 0.85; b<1.15;b+=0.01,baseN++){
    fitData(fname, RunNum, NULL,beamMeV, emin, emax, colliDist_m, colliDia_mm, nVec, b*baseline, ff, HighChisq);
    cout <<"Fit completed" << endl;
    baseScale[baseN] = b*baseline;
    baseChisq[baseN] = bestChisq/baseScale[baseN];
    basePol[baseN]   = histP->GetBinContent(histP->GetMaximumBin());
  }

  //find best
  for(int n=0;n<baseN;n++){
    if(baseChisq[n] < minChisq){
      minChisq = baseChisq[n];
      minIndex = n;
    }     
      }

  //redo the best one
  cout << "Drawing best fit" << endl;
  fitData(fname, RunNum, outfile,beamMeV, emin, emax, colliDist_m, colliDia_mm, nVec, baseScale[minIndex], ff, HighChisq, 1, OutDir); 

  //make canvas and graphs to show effects of baseline fits
  if(!graphCanvas){
    graphCanvas = new TCanvas("graphCanvas","graphCanvas",50,50,800,1000);
    graphCanvas->Divide(1,2);
    graphCanvas->Draw();
    if(graphPvsBase){
      delete graphPvsBase;
      delete graphCvsBase;
    }
  }
  graphPvsBase = new TGraph(baseN,baseScale,basePol);
  graphCvsBase = new TGraph(baseN,baseScale,baseChisq);
  graphCanvas->cd(1);
  graphCvsBase->Draw("ALP");
  graphCvsBase->GetHistogram()->GetXaxis()->SetTitle("baseline");
  graphCvsBase->GetHistogram()->GetYaxis()->SetTitle("pseudo chisq");
  graphCvsBase->SetMarkerStyle(8);
  graphCvsBase->SetMarkerSize(1.0);
  graphCvsBase->SetTitle("PseudoChisq vs baseline scaling");
  graphCvsBase->Draw("ALP");

  graphCanvas->cd(2);
  graphPvsBase->Draw("ALP");
  graphPvsBase->GetHistogram()->GetXaxis()->SetTitle("baseline");
  graphPvsBase->GetHistogram()->GetYaxis()->SetTitle("Max polarisation");
  graphPvsBase->GetHistogram()->GetYaxis()->SetRangeUser(0.8*graphPvsBase->GetMean(2),1.2*graphPvsBase->GetMean(2));
  graphPvsBase->SetMarkerStyle(8);
  graphPvsBase->SetMarkerSize(1.0);
  graphPvsBase->SetTitle("Peak polarisation vs baseline scaling");
  graphPvsBase->Draw("ALP");

  cout << "Best chisq: "<< minChisq << endl;
  ThreshOut[CHISQ_T] = minChisq;

  string RunNumString(RunNum); 
  string ThresholdStudyOutfile = OutDir + "/FitParameters.dat";
    
  // create and save new .dat file
  if(isFittable == true){
    const char * New_Line = "\n";
    string New_Line_str(New_Line);
    ofstream ThreshFile;
    ThreshFile.open(ThresholdStudyOutfile.c_str());
    ThreshFile  << to_string(ThreshOut[EDGE_T]) + New_Line_str + to_string(ThreshOut[SIGMA_T]) + New_Line_str + to_string(ThreshOut[CHISQ_T]) + New_Line_str + to_string(ThreshOut[THETA_T]) + New_Line_str + to_string(ThreshOut[THETAR_T]) + New_Line_str + to_string(ThreshOut[SIGMAR_T]) + New_Line_str + "first line = fitedge, second line = sigma, third line = chisq, fourth line = theta, fifth line = theta_r, sixth line = sigma_r" + New_Line_str;
  }
  ChPkFl->WriteTObject(graphCanvas);
  
}
  
void fitData(char const *fname, char const * RunNum, Char_t *outfile, Double_t beamMeV, Double_t emin, Double_t emax, Double_t colliDist_m, Double_t colliDia_mm, Int_t nVec, Double_t baseline, Double_t ff, Bool_t HighChisq, Bool_t SaveCanvas, string OutDir, char const * EnhDatPol){
  //read in a file to the global data histogram then fit it
  //file should be of the form Egamma, Enhancement
  //if file begins -L if will be interpreted as a list of files eg -Lmyfilelist

  FILE *fp=NULL;
  Char_t line[250];
  Double_t diff1,diff2,diff3, diff4, scalefac,fitedge;
  Char_t name[30];
  Double_t lowmean=100000000.0;
  Double_t par[10];
  ROOT::Math::Minimizer* min;
  Char_t filename[200];
  Char_t tempname[200];
  Char_t plane[8];
  Double_t theta;
  Double_t lowPolLimit;
  Double_t highPolLimit;
  Double_t pol;
  char EnhDatPolFlNm[200];

  fitMinEnergy = emin;                                  //push these to globals
  fitMaxEnergy = emax;
  
  if(!isInit) init();                                   // init anything if needed

  strcpy(filename,fname);
  
  if((fp=fopen(filename,"r"))==NULL){
    cout << "Error, couldn't open " << filename << endl;
    return;
  }
  cout << "Opened " << filename << endl;
    
  nBins=0;
  while(fgets(line,200,fp)){                         //read all the data points
    if((line[0] == '*')||(line[0] == '#')) continue; //skip comments    
    sscanf(line,"%lg%lg",&energy[nBins],&enhancement[nBins]);
    nBins++;
  }
  if(ff<100.0){
    cout << "Applying ff: " << endl;
    for(int n=0;n<nBins;n++){                        //a fudge factor to adjust the sharp to make the inc part more line the amo data/ 
      cout << enhancement[n] << "    ";
      enhancement[n]*=(TMath::Power(energy[n]/beamMeV,ff));
      cout << enhancement[n] << "    " << endl;
    }
  }
  fclose(fp);
    
  for(int b=0;b<nBins-1;b++){                      //make some bin edges half way between the energy values.
      energyBins[b+1]=0.5*(energy[b]+energy[b+1]);
  }
  //and the top and bottom have width of the adjacent bin
  energyBins[0]     = energyBins[1]       - (energyBins[2]      - energyBins[1]);
  energyBins[nBins] = energyBins[nBins-1] + (energyBins[nBins-1]- energyBins[nBins-2]);
  
  //Now make any required histograms if neccessary
  histE        = new TH1F("Enhancement", "Enhancement;Energy (MeV)",nBins,energyBins);
  histP        = new TH1F("Polarization", "Polarization;Energy (MeV);Deg. of Pol.",nBins,energyBins);
  histD        = new TH1F("EnhancementData", "EnhancementData;Energy (MeV)",nBins,energyBins);
  
  histE->SetMinimum(0);
  histD->SetMinimum(0);
  histP->SetMinimum(0);
  histP->SetMaximum(1);
  histD->SetMarkerStyle(20);
  histD->SetMarkerSize(0.7);
  histD->GetXaxis()->SetNdivisions(20);
  histE->GetXaxis()->SetNdivisions(20);
  histP->GetXaxis()->SetNdivisions(20);
  histP->GetYaxis()->SetNdivisions(20);
  
  
  //Find the max and min bins for the fit range
  fitMinBin=histD->FindBin(fitMinEnergy);
  fitMaxBin=histD->FindBin(fitMaxEnergy);
  
  //fill the histD with the enhancement
  for(int n=0;n<nBins;n++){
    histD->SetBinContent(n+1,enhancement[n]);
  }
  //Get rid of zeros
  for(int n=1;n<=nBins-1;n++){
    if(histD->GetBinContent(n)<0.1)histD->SetBinContent(n,histD->GetBinContent(n+1));
  }
  //Get rid of zeros 2nd pass
  for(int n=1;n<=nBins-1;n++){
    if(histD->GetBinContent(n)<0.1)histD->SetBinContent(n,histD->GetBinContent(n+1));
  }
  //  Get rid of spikes up and down
  for(int n=2;n<=nBins-1;n++){
    diff1=(histD->GetBinContent(n)-histD->GetBinContent(n-1))/histD->GetBinContent(n-1);
    diff2=(histD->GetBinContent(n)-histD->GetBinContent(n+1))/histD->GetBinContent(n+1);
    if (((fabs(diff1)>0.1)&&(fabs(diff2)>0.1))&&(fabs(diff1-diff2)<0.3)){
      histD->SetBinContent(n,0.5*(histD->GetBinContent(n-1)+histD->GetBinContent(n+1)));
    }
  }
  //  Get rid of spikes up and down 2nd pass
  if(HighChisq == true){
   for(int n=2;n<=nBins-1;n++){
    diff1=(histD->GetBinContent(n)-histD->GetBinContent(n-1))/histD->GetBinContent(n-1);
    diff2=(histD->GetBinContent(n)-histD->GetBinContent(n+1))/histD->GetBinContent(n+1);
    diff3 =(histD->GetBinContent(n)-histD->GetBinContent(n+2))/histD->GetBinContent(n+2);
    if ((fabs(diff1)>1.0)||(fabs(diff2)>1.0)){
      if (fabs(diff1-diff2)<0.3){  
	histD->SetBinContent(n,0.5*(histD->GetBinContent(n-1)+histD->GetBinContent(n+1)));
      }
      else if(fabs(diff1-diff3)<0.3){
	histD->SetBinContent(n,0.5*(histD->GetBinContent(n-1)+histD->GetBinContent(n+2)));
      }
      else if(fabs(diff1-diff4)<0.3){
	histD->SetBinContent(n,0.5*(histD->GetBinContent(n-1)+histD->GetBinContent(n+3)));
      }
      else{
	histD->SetBinContent(n, histD->GetBinContent(n-1));
	}
    }
   }
}
  
  if(!strstr(filename,".sim")){    //if not simulated
    // find a reasonable minumum spot to set to 1 for the baseline.
    // the lowest 5 channel mean between 0.2 and 0.95 of the range
    lowmean=1000000.0;
    for(int n=fitMinBin;n<=(int)(0.9*(float)nBins);n++){
      if((histD->Integral(n-2,n+2)<lowmean)){
	lowmean=histD->Integral(n-2,n+2);
      }
    }

    cout<<"lowmean: "<<lowmean<<endl;
 
    histD->Scale(5.0*baseline/(lowmean));            //scale the hist to try and put the incoherent part at 1
  }
  genCanvas->cd(1);                                //if you think the lowest point is 
  
  histD->SetMaximum(1.2*histD->GetMaximum());
  histD->SetMinimum(0.0);

  //Count number of steep lines joining data points and total line length, reject run file completely if either are too high
  Double_t diff;
  Int_t NumSteepLines = 0;
  Double_t line_length = 0;
  for(int n = 0; n <= nBins-1;n++){
    diff = (histD->GetBinContent(n) - histD->GetBinContent(n+1))/histD->GetBinContent(n+1);
    if(fabs(diff)>0.15){
      NumSteepLines++;
    }
  }
  for(int n = 0; n <= nBins-1;n++){
    line_length += fabs((histD->GetBinContent(n) - histD->GetBinContent(n+1)));
  }
  if(NumSteepLines > 26 || line_length > 50){
    cout << "Data is too erratic, fit not possible, " << NumSteepLines << " steep lines and total line length " << line_length << endl;
    NumSteepLines = 0;
    line_length = 0;
    bestChisq = 300;
    return;
  } 
  else{
    cout << "Data is fittable" << endl;
    isDataGood = true;
  }
  //line length threshold = 50, Num Steep threshold = 26
  
  histD->Draw("HISTP");
  //Now try to make some guesses at the initial parameters
  gausFit->SetRange(histD->GetBinCenter(histD->GetMaximumBin()),histD->GetBinCenter(histD->GetMaximumBin())+100.0);
  gausFit->SetParameter(1,histD->GetBinCenter(histD->GetMaximumBin()));
  gausFit->SetParameter(2,10.0);
  gausFit->SetParameter(3,1.0);
   
  histD->Fit(gausFit,"rN");
  lowmean=0.0;
  //Get the edge from the derivative of whatever quickie function is fitted 
  //Note that GetMaximumBin() finds the bin with the highest content value
  histD->GetXaxis()->SetRange(8000,9000);
  for(float d = histD->GetBinCenter(histD->GetMaximumBin());d < histD->GetBinCenter(histD->GetMaximumBin()+100.0);d+=0.1){  //starting from bin corresponding to peak value, ending at 100 bins past this point   
    if(gausFit->Derivative(d)<lowmean && d > 8768 && d < 8806){
      lowmean=gausFit->Derivative(d);
      fitedge=d; 
    }
  }
  histD->GetXaxis()->SetRange(5707,11375);

  cout << "edge from derivative of cheapo fit = " << fitedge << " MeV" << endl;
  
  if(outfile){    //if outfile contains "draw"
    if(strstr(outfile,"draw")){              //just show fit and exit
      gausFit->Draw("same");
    }
  }
    
  //Now we have enough information to set the basic parameters
  parFromHuman(beamMeV,fitedge,gausFit->GetParameter(2),colliDist_m,colliDia_mm,nVec,par);
 
  //set the intensities
  for(int v=0;v<par[NVEC];v++){                                                       //give the vectors intensities
    par[IVEC+v] = histD->GetMaximum()*2.0/(TMath::Power((Double_t)VECTORS[v],2.0));   //tailing off as 1/VECTORS[v]^2
    cout << IVEC+v << "  v   " << par[IVEC+v] << endl; //
  }
  cout << "par[IVEC]= "<< par[IVEC]<<endl; 
  
  enhFromParams(par); //This seems to be where the program crashes. Possibly due to infinities in par array?
  
  //Redo the intensities according to a the calc / data ratio
  scalefac=histD->GetMaximum()/histE->GetMaximum();
  for(int v=0;v<par[NVEC];v++){                                                       //give the vectors intensities
    par[IVEC+v]*=scalefac;
    }
  enhFromParams(par);
  histE->SetLineColor(2);
  histE->Draw("HIST same");
  
  genCanvas->cd(2);
  histP->SetLineColor(2);
  histP->Draw("HIST");
  
  genCanvas->Update();
  gSystem->ProcessEvents();
  gSystem->Sleep(500);
  
  if(outfile){                               //if outfile contains "draw"
    if(strstr(outfile,"draw")){              //just show fit and exit
      return;
    }
  }

  min = ROOT::Math::Factory::CreateMinimizer("Minuit", "Combined");
  
  // set tolerance , etc...
  min->SetMaxFunctionCalls(1000000); // for Minuit/Minuit2 
  min->SetMaxIterations(10000);  // for GSL 
  min->SetTolerance(0.0001);
  min->SetPrintLevel(1);

  ROOT::Math::Functor ft(&efit,IVEC+nVec);     
  min->SetFunction(ft);
   
  //Now set the variables
  min->SetLimitedVariable(THETA,   "Theta",   0.0033,      0.00003,  0.0031, 0.0037);
  min->SetLimitedVariable(SIGMA,   "Sigma",   0.00003,  0.0000005,  0,  0.0001);
  min->SetLimitedVariable(THETAR,  "Thetar",  par[THETAR],     par[THETAR]/100.0, 0.95*par[THETAR], 1.05*par[THETAR]);
  min->SetLimitedVariable(SIGMAR,  "Sigmar",  0.1, 0.001, 0.03, 0.35);
  min->SetFixedVariable(E0MEV,     "E0MeV",   par[E0MEV]);     //no of vectors
  min->SetFixedVariable(NVEC,      "Nvec",    par[NVEC]);      //no of vectors
  for(int n=0;n<nVec;n++){
    sprintf(name,"Vec0%d%d", VECTORS[n],VECTORS[n]);
    min->SetLimitedVariable(n+IVEC, name, par[n+IVEC], par[n+IVEC]/100.0,0.0,10*par[n+IVEC]); 
  }
    
  verbose=1;             //make it show the fit as it's improving
  bestChisq=100000.00;   //set this high for starters
  
  min->Minimize(); 
  
  genCanvas->cd(1);
  enhFromParams(bestPar);
  histD->Draw("HISTP");
  histE->SetLineColor(2);
  histE->Draw("HIST same");
  
  genCanvas->cd(2);
  histP->SetLineColor(2);
  histP->Draw("HIST");
  
  cout << "1bestChisq: " << bestChisq << endl;

  if(SaveCanvas == 1 && isDataGood == false){
    cout << "GIF will not be saved, data too erratic" << endl;
  }
  if (SaveCanvas == 1 && isDataGood == true){
    cout << "Saving Canvas" << endl;
    string EnhDatPolSt(EnhDatPol);
    string OutF = OutDir + EnhDatPolSt;           
    const char * OutFchar = OutF.c_str();
    strcpy(EnhDatPolFlNm,OutFchar); 
    strcat(EnhDatPolFlNm,RunNum);
    strcat(EnhDatPolFlNm,".root");
    TFile * EnhDatPolFl = new TFile(EnhDatPolFlNm, "RECREATE");
    EnhDatPolFl->WriteTObject(genCanvas);
    EnhDatPolFl -> cd();
    histD -> Write();
    histE -> Write();
    histP -> Write();
    cout << "saved pol/fit as " << EnhDatPolFlNm << endl;
    isFittable = true;

    ThreshOut[EDGE_T] = fitedge;
    ThreshOut[SIGMA] = bestPar[1]; 
    ThreshOut[SIGMAR_T] =bestPar[SIGMAR];
    ThreshOut[THETA_T] =bestPar[THETA];
    ThreshOut[THETAR_T] =bestPar[THETAR];

  }  

  if(outfile!=NULL){
    //open output file
    cout << "Outfile exists" << endl;
    fp=fopen(outfile,"w");
    
    //Now write comments,  parameters etc
    fprintf(fp,"#Pol table based on enhancement in %s\n",filename);
    fprintf(fp,"#THETA,  // [0] theta      main angle responsible for coherent edge cutoffs\n");
    fprintf(fp,"#SIGMA,  // [1] sigma      smearing of theta\n");
    fprintf(fp,"#THETAR, // [2] thetar     relative angle resonsible for colli cutoffs\n");
    fprintf(fp,"#SIGMAR, // [3] sigmar     smearing of colli cutoff angle\n");
    fprintf(fp,"#E0MEV,  // [4] beam energy\n");
    fprintf(fp,"#NVEC,   // [5] nvec       no of vectors contributing (1-4)\n");
    fprintf(fp,"#IVEC};  // [6] ivec[]     array of intensities of vectors up to nvec.\n");

    fprintf(fp,"Parameters: ");
    for(int n=0;n<10;n++){
      fprintf(fp,"%lf ",bestPar[n]);
    }
    fprintf(fp,"\n");
    fclose(fp);
  }
}

void enhFromHuman(Double_t beamMeV, Double_t edgeMeV, Double_t spreadMeV, Double_t colliDist_m, Double_t colliDia_mm, Int_t nVec){
  Double_t par[10];
  parFromHuman(beamMeV,edgeMeV,spreadMeV,colliDist_m,colliDia_mm,nVec,par);
  enhFromParams(par);                                                         //call the function to make the enh and pol
}
  
void parFromHuman(Double_t beamMeV, Double_t edgeMeV, Double_t spreadMeV, Double_t colliDist_m, Double_t colliDia_mm, Int_t nVec, Double_t *par){

  //takes some physical quantities and makes them into parameters, then calls the 
  //enhFromParams function. 
  
  
  //  Double_t par[10];                                                       //array of parameters
  Int_t g = 2;                                                                //variables used in CLAS note
  Double_t E0 = beamMeV;
  Double_t Eg = edgeMeV;
  
  
  par[THETA]  = k/(g*E0*E0*((1/Eg)-(1/E0)));                                  //theta from edge and beam energy
  par[SIGMA]  = (par[THETA]-(k/(g*E0*E0*((1/(Eg-spreadMeV))-(1/E0)))))/3.0;   //spread in theta from spread in edge 
  par[THETAR] = E0*0.001*colliDia_mm/colliDist_m;                             //cut from collimator
  par[SIGMAR] = par[THETAR]*par[SIGMA]/par[THETA];                            //smear in above same fractional sigma as above
  par[E0MEV]  = E0;                                                           //beam energy
  par[NVEC]   = (Double_t)nVec;                                               //no of harmonics
  
  for(int v=0;v<par[NVEC];v++){                                               //give the vectors intensities
    par[IVEC+v] = 2.0/(Double_t)VECTORS[v];                                   //tailing off as 1/VECTORS[v]
  }
}  
  
void enhFromParams(Double_t *par){
  //make an enhancement and corresponding polarization from some the parameters as defined in the CLAS note.
  //this function is can be called stand alone, but will also be called many times from the fitting function

  Double_t xd[10];
  Double_t xc[10];
  Double_t Q[10];
  Double_t cohContrib;
  Double_t cohTotal;
  Double_t phiTotal;
  Double_t etotal;
  Double_t ptotal;
  Double_t x=0.0;
  Int_t    g=0;
  Double_t weight=0.0;
  Double_t weightSum=0.0;
  Double_t polSum=0.0;
  Double_t phi,chi,cd;
  Double_t amo;
  Int_t jbin=0;
 
  // if needed, make some hists
  if(!histE){
    histE        = new TH1F("Enhancement", "Enhancement",  1000, 0, par[E0MEV]);
    histP        = new TH1F("Polarization", "Polarization",1000, 0, par[E0MEV]);
    histE->SetMinimum(0);
    histP->SetMinimum(0);
    histP->SetMaximum(1);
  }    

  if(!thetaPol){
    weightHist   = new TH1F("weightHist",  "weightHist", THETASTEPS+1, 0, THETASTEPS+1 );
    thetaWeight  = new TH2F("thetaWeight", "thetaWeight",histE->GetNbinsX(), histE->GetXaxis()->GetXbins()->GetArray(), THETASTEPS+1,0, THETASTEPS+1);
    thetaPol     = new TH2F("thetaPol",    "thetaPol",   histE->GetNbinsX(), histE->GetXaxis()->GetXbins()->GetArray(), THETASTEPS+1,0, THETASTEPS+1);
    thetaItot    = new TH2F("thetaItot",   "thetaItot",  histE->GetNbinsX(), histE->GetXaxis()->GetXbins()->GetArray(), THETASTEPS+1,0, THETASTEPS+1);
  }

  //reset them all for fresh filling
  histE->Reset("ICE");
  histP->Reset("ICE");
  thetaPol->Reset("ICE");
  thetaItot->Reset("ICE");
  weightHist->Reset("ICE");
  thetaWeight->Reset("ICE");

  for(Double_t j=par[THETA]-3.0*par[SIGMA];j<=par[THETA]+3.001*par[SIGMA];j+=(6.0*par[SIGMA])/THETASTEPS){
    
    weight=TMath::Gaus(j,par[THETA],par[SIGMA]);   //get the weight from the gaussian
    weightSum+=weight; //add to sum
    
    //find the discontinuity for each vector. This for structure appears to cause the crash
    for(int v=0;v<par[NVEC];v++){
      g=VECTORS[v];
      xd[v]=1.0/((k/(g*par[E0MEV]*j))+1.0);
      Q[v]=(1.0-xd[v])/xd[v];
      xc[v]=xd[v]/(1+((par[THETAR]*par[THETAR])*(1-xd[v])));
    }
    

    //loop over all bins in the histogram
    for(int bin=1;bin<=histE->GetNbinsX();bin++){
      x=histE->GetBinCenter(bin)/par[E0MEV];       //find the value of the bin
      amo=1/x;                                     //assume amo = inc = 1/x over regio of interest
      
      cohTotal=0.0;
      phiTotal=0.0;
      
      //loop over all the vectors
      for(int v=0;v<par[NVEC];v++){
	if(x>xd[v]) continue;                      //only do up to x_dg
	 
	//work out chi and phi
	phi=(2*Q[v]*Q[v]*x*x)/((1-x)*(1+((1-x)*(1-x))-((4*Q[v]*Q[v]*x*x/(1-x))*(((1-x)/(Q[v]*x))-1))));
	chi=((Q[v]*Q[v]*x)/(1-x))*(1+((1-x)*(1-x))-((4*Q[v]*Q[v]*x*x/(1-x))*(((1-x)/(Q[v]*x))-1)));
	cd=0.5*(1+TMath::Erf((x-xc[v])/(TMath::Sqrt(2)*par[SIGMAR])));

	cohContrib = cd*par[IVEC+v]*chi;	         //get coherent contrib for the vector
	cohTotal  += cohContrib;	                 //add to the total and update the phi total
	phiTotal  += cohContrib*phi;

      }
      if(cohTotal>0.0) {
	phiTotal/=cohTotal;                              //divide by the cohTotal to get the weighted mean phi
      }

      etotal=(amo+cohTotal)/amo;                         //enhancement and pol totals
      ptotal=phiTotal*cohTotal;

      histE->Fill(x*par[E0MEV],weight*etotal);           //add the weighted contribution to the enhancement
      
      thetaPol->Fill(x*par[E0MEV],jbin,ptotal);          //keep the pol for this x,theta coord
      thetaItot->Fill(x*par[E0MEV],jbin,cohTotal+amo);   //keep the total intensity for this x,theta coord
    }

    weightHist->Fill(jbin,weight);                       //save the weight for this theta point
    jbin++;
  }
  
  histE->Scale(1.0/weightSum);                           //normalize the sum of the weighted enhancements
  
  for(int bin=1; bin<=histP->GetNbinsX(); bin++){        //loop over each x bin, adding the weighted contribs from each theta pos
    weightSum=0.0;
    polSum=0.0;
    
    for(int jb=1;jb<=weightHist->GetNbinsX();jb++){
      weight=weightHist->GetBinContent(jb);
      polSum+=thetaPol->GetBinContent(bin,jb)*weight;
      weightSum+=thetaItot->GetBinContent(bin,jb)*weight;
    }
    polSum/=weightSum;
    histP->Fill(histP->GetBinCenter(bin),polSum);
  } 
}

void makeSimEnh(Char_t *outfile, Double_t sigma){
  Char_t filename[128];
  sprintf(filename,"%s.sim",outfile);
  FILE *fp=fopen(filename,"w");
  int bins=histE->GetNbinsX();
  Float_t energy,enh;
  TDatime *t=new TDatime();
  TRandom *r=new TRandom(t->GetTime());
  
  for(int n=1; n<=bins; n++){
    energy = histE->GetBinCenter(n);
    enh    = (Float_t)r->Gaus(histE->GetBinContent(n),sigma*histE->GetBinContent(n));
    fprintf(fp,"%5.2f %3.2f\n", energy,enh);
  }
}

Double_t GetMaxPol(run Current_Run, string OutDir){
  string run_number = Current_Run.RunNumber;
  string rootfile_name = OutDir + "/Run_" + run_number + ".root";
  TFile *rootfile = TFile::Open(rootfile_name.c_str());
  TH1F *PolHist = (TH1F*)rootfile->Get("Polarization");
  Int_t binmax = PolHist -> GetMaximumBin();
  Double_t PeakVal = PolHist -> GetBinContent(binmax);
  rootfile -> Close("R");
  return(PeakVal);
}

Double_t GetMaxPol_NumOnly(string run_number, string OutDir){
  string rootfile_name = OutDir + "/Run_" + run_number + ".root";
  TFile *rootfile = TFile::Open(rootfile_name.c_str());
  TH1F *PolHist = (TH1F*)rootfile->Get("Polarization");
  Int_t binmax = PolHist -> GetMaximumBin();
  Double_t PeakVal = PolHist -> GetBinContent(binmax);
  rootfile -> Close("R");
  return(PeakVal);
}

void WritePolOutFile(string rootfile_name, string RunNum, string OutDir){
  const char * rootfile_name_char = rootfile_name.c_str();
  TFile *rootfile = TFile::Open(rootfile_name_char);
  TH1F *PolHist = (TH1F*)rootfile->Get("Polarization");
  string PolFlName = OutDir + "/ChanPolVals.dat";
  string New_Line = "\n";
  ofstream Pol_Out_File;
  Pol_Out_File.open(PolFlName.c_str());
  for(Int_t chan = 0; chan < 216; chan++){
    Pol_Out_File <<  PolHist -> GetBinContent(chan) << New_Line;
    }
  Pol_Out_File.close();
}

Double_t GetMeanInRange(run Current_Run, string OutDir){
  Int_t MinBin;
  Int_t MaxBin;
  Int_t MinBin_En;
  Int_t MaxBin_En;
  Double_t Mean_Pol = 0;
  Int_t numChan;
  Double_t TotalFluxInRange;
  Double_t ChanFlux;

  string run_number = Current_Run.RunNumber;
  string rootfile_name = OutDir + "/Run_" + run_number + ".root";
  TFile * rootfile = TFile::Open(rootfile_name.c_str());
  TH1F * PolHist = (TH1F*)rootfile->Get("Polarization");
  TH1F * EnHist = (TH1F*)rootfile->Get("Enhancement");

  MinBin = PolHist -> FindBin(8200.0);
  MaxBin = PolHist -> FindBin(8800.0);
  MinBin_En = EnHist -> FindBin(8200.0);
  MaxBin_En = EnHist -> FindBin(8800.0);

  TotalFluxInRange = 0;
  for(Int_t numChanEn = MinBin_En; numChanEn < MaxBin_En +1; ++numChanEn){ 
    TotalFluxInRange += EnHist -> GetBinContent(numChanEn) + 1;
  }

  for(numChan = MinBin; numChan < MaxBin + 1; numChan++){
    ChanFlux = EnHist -> GetBinContent(numChan) + 1;
    Mean_Pol +=  (ChanFlux/TotalFluxInRange)*(PolHist -> GetBinContent(numChan));
  }
  rootfile -> Close("R");
  return(Mean_Pol);
}

Double_t GetMeanInRange_NumOnly(string run_number, string OutDir){
  Int_t MinBin;
  Int_t MaxBin;
  Int_t MinBin_En;
  Int_t MaxBin_En;
  Double_t Mean_Pol = 0;
  Int_t numChan;
  Double_t TotalFluxInRange;
  Double_t ChanFlux;

  string rootfile_name = OutDir + "/Run_" + run_number + ".root";
  TFile * rootfile = TFile::Open(rootfile_name.c_str());
  TH1F * PolHist = (TH1F*)rootfile->Get("Polarization");
  TH1F * EnHist = (TH1F*)rootfile->Get("Enhancement");

  MinBin = PolHist -> FindBin(8200.0);
  MaxBin = PolHist -> FindBin(8800.0);
  MinBin_En = EnHist -> FindBin(8200.0);
  MaxBin_En = EnHist -> FindBin(8800.0);

  TotalFluxInRange = 0;
  for(Int_t numChanEn = MinBin_En; numChanEn < MaxBin_En +1; ++numChanEn){ 
    TotalFluxInRange += EnHist -> GetBinContent(numChanEn) + 1;
  }

  for(numChan = MinBin; numChan < MaxBin + 1; numChan++){
    ChanFlux = EnHist -> GetBinContent(numChan) + 1;
    Mean_Pol +=  (ChanFlux/TotalFluxInRange)*(PolHist -> GetBinContent(numChan));
  }
  rootfile -> Close("R");
  return(Mean_Pol);
}

//void CalculateEnhancement(const char * diFile, const char * amFile, const char * Selector, const char * EnhOut , const char * efile, const char * RunNum, string OutDir, const char * AllRunsList, const char){
//void CalculateEnhancement(const char * diFile, const char * amFile, const char * Selector, const char * EnhOut , const char * efile, const char * RunNum, string OutDir, const char * AllRunsList, const char * SkimName){
void CalculateEnhancement(const char * diFile, const char * amFile, const char * Selector, const char * EnhOut , const char * efile, const char * RunNum, string OutDir, const char * SkimName){
  Double_t ecentreArray[276];
  Double_t ebinArray[276];
  Int_t nbins;
  Char_t efname[128];
  const char * Files[2];
  TH1F * enhHist; 
  TH1I * amoHist;
  TH1I * DiHist;
  TH1 * BeamE[2];
  TTree * Trees[2];
  FILE * fp;
  FILE * fl; 
  TFile * outFile;
  string tree_name;
  
  string SkimName_St = SkimName;
  tree_name = SkimName_St + "_Tree";
  tree_name.erase(0, 5);

  Trees[0] = 0; 
  Trees[1] = 0;
  
  Files[0] = diFile;
  Files[1] = amFile;

  TString RootFile; 

  string SelectorString(Selector);
  // FillRunList(AllRunsList);

  if(SelectorString == "DSelector_Spring16.C+"){
    RootFile = "Spring16.root";
  }
  if(SelectorString == "DSelector_Fall16.C+"){
    RootFile = "Fall16.root";
  }
  if(SelectorString == "DSelector_Spring17.C+"){
    RootFile = "Spring17.root";
  }
  if(SelectorString == "DSelector_Spring18.C+"){
    RootFile = "Spring18.root";
  }
  if(SelectorString == "DSelector_Fall18.C+"){
    RootFile = "Fall18.root";
  }
  if(SelectorString == "DSelector_Spring19.C+"){
    RootFile = "Spring19.root";
  }
  if(SelectorString == "DSelector_Fall19.C+"){
    RootFile = "Fall19.root";
  }
  if(SelectorString == "DSelector_Spring20.C+"){
    RootFile = "Spring20.root";
  }
  if(SelectorString == "DSelector_Fall20.C+"){
    RootFile = "Fall20.root";
  }
  if(SelectorString == "DSelector_Spring21.C+"){
    RootFile = "Spring21.root";
  }
  if(SelectorString == "DSelector_Fall21.C+"){
    RootFile = "Fall21.root";
  }
  if(SelectorString == "DSelector_Spring22.C+"){
    RootFile = "Spring22.root";
  }
  if(SelectorString == "DSelector_Fall22.C+"){
    RootFile = "Fall22.root";
  }
  if(SelectorString == "DSelector_Spring23.C+"){
    RootFile = "Spring23.root";
  }
  if(SelectorString == "DSelector_Fall23.C+"){
    RootFile = "Fall23.root";
  }
  if(SelectorString == "DSelector_Spring24.C+"){
    RootFile = "Spring24.root";
  }
  if(SelectorString == "DSelector_Fall24.C+"){
    RootFile = "Fall24.root";
  }
  if(SelectorString == "DSelector_Spring25.C+"){
    RootFile = "Spring25.root";
  }
  if(SelectorString == "DSelector_Fall25.C+"){
    RootFile = "Fall25.root";
  }

  fl = fopen(efile,"r");
  for(nbins=1;nbins<285;nbins++){
    if(fscanf(fl,"%lg",&ecentreArray[nbins])==EOF) break; //fills ecentreArray with data from efile.
  }
  fclose(fl);
  
  for(int n=1;n<nbins-1;n++){
    ebinArray[n]=0.5*(ecentreArray[n]+ecentreArray[n+1]);
  }
  ebinArray[0]=ebinArray[1]-(ebinArray[2]-ebinArray[1]);
  ebinArray[nbins-1]=ebinArray[nbins-2]+(ebinArray[nbins-2]-ebinArray[nbins-3]);
  outFile = new TFile(EnhOut, "RECREATE");
  outFile->cd();
  enhHist = new TH1F("hEnh", "Enhancement", 275, ebinArray);
  amoHist = new TH1I("AmoSpec", "Amorphous Spectrum", 275, ebinArray);
  DiHist = new TH1I("DiSpec", "Diamond Spectrum", 275, ebinArray);

  gROOT->ProcessLine(".x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C");
  for(int n = 0; n<2; n++){
    TFile *_file0 = TFile::Open(Files[n]);
    _file0->GetObject(tree_name.c_str(), Trees[n]);
    Trees[n]->Process(Selector);
    TFile *_file1 = TFile::Open(RootFile);
    _file1->GetObject("BeamEnergy", BeamE[n]);
  }
  string RunSt(RunNum);
  
  string AmoSpecFlNm = OutDir + "/AmoSpec_" + RunSt + ".root";
  TFile *AmoSpecFile = new TFile(AmoSpecFlNm.c_str(),"RECREATE");
  AmoSpecFile->cd();
  amoHist->Add(BeamE[1]);
  amoHist->Write();
  
  string DiSpecFlNm = OutDir + "/DiSpec_" + RunSt + ".root";
  TFile *DiSpecFile = new TFile(DiSpecFlNm.c_str(),"RECREATE");
  DiSpecFile ->cd();
  DiHist ->Add(BeamE[0]);
  DiHist->Write();

  string EnhFlNm = OutDir + "/EnhPlots_" + RunSt + ".root";
  TFile *EnhFile = new TFile(EnhFlNm.c_str(),"RECREATE");
  EnhFile ->cd();
  enhHist->Add(BeamE[0]);
  enhHist->Divide(BeamE[1]);
  enhHist->Write();

  outFile->cd();

  sprintf(efname,"%s.dat",EnhOut);
  fp = fopen(efname,"w");
  fprintf(fp,"#Ecenter(MeV) Enhancement(Arb units)\n");
  for(int n=1;n<=enhHist->GetNbinsX();n++){
    fprintf(fp,"%6.1f\t%5.3f\n",1000.0*enhHist->GetBinCenter(n),enhHist->GetBinContent(n));
  }
  fclose(fp);
}

//void PlotAndFitEnh(const char * kpkmFileName, const char * AmFlNm, string OutDir, Double_t Beam_Energy, string RunNumber, string RunPeriod, const char * AllRunsList){
void PlotAndFitEnh(const char * kpkmFileName, const char * AmFlNm, string OutDir, Double_t Beam_Energy, string RunNumber, string RunPeriod, const char * AllRunsList, const char * SkimName){
  Double_t edge;
  Double_t sigma;
  Double_t chisq;
  Double_t MeanPol;
  Double_t PeakPol;
  Double_t OldChisq;
  const char * binEfl;
  fstream fileStream;
  string RunSeason;
  string RunYear;
  string RunAltYear;
  string SlNmSt;
  string binEflSt;

  string EnhOutDir = OutDir + "/EnhOut";
  string filenm = OutDir + "/FitParameters.dat";     
  string EnhOutDatSt = EnhOutDir + ".dat";
  const char * SlNm; 
  FillRunList(AllRunsList);

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

   SlNmSt = "DSelector_" + RunSeason + RunAltYear + ".C+";
   binEflSt =  "Efiles/" + RunSeason + RunAltYear + "Efile";
   SlNm = SlNmSt.c_str();
   binEfl = binEflSt.c_str();

  run Run = returnRun(RunNumber);
   
  //CalculateEnhancement(kpkmFileName, AmFlNm, SlNm, EnhOutDir.c_str(), binEfl, RunNumber.c_str(), OutDir, AllRunsList);
  CalculateEnhancement(kpkmFileName, AmFlNm, SlNm, EnhOutDir.c_str(), binEfl, RunNumber.c_str(), OutDir, SkimName);
  cout << "Enhancement Calculated" << endl;
  fitDataB(EnhOutDatSt.c_str(), RunNumber.c_str(), Beam_Energy, 76.0, 5.0, OutDir , false);

  fileStream.open(filenm);
  if (fileStream) {
    fileStream >> edge;
    fileStream >> sigma;
    fileStream >> chisq;
  }
  fileStream.close();  
  if(chisq > 10){
    OldChisq = chisq;
    fitDataB(EnhOutDatSt.c_str(), RunNumber.c_str(), Beam_Energy, 76.0, 5.0, OutDir , true);
    fileStream.open(filenm);
    if (fileStream) {
      fileStream >> edge;
      fileStream >> sigma;
      fileStream >> chisq;
    }
    fileStream.close();
    if(chisq > OldChisq){
      fitDataB(EnhOutDatSt.c_str(), RunNumber.c_str(), Beam_Energy, 76.0, 5.0, OutDir , false);
    }
  } 
  if(isFittable == true){
    MeanPol = GetMeanInRange(Run, OutDir);
    PeakPol = GetMaxPol(Run, OutDir);
    const char * New_Line = "\n";
    string New_Line_str(New_Line);
    ofstream MeanPeakFile;
    MeanPeakFile.open(OutDir + "/MeanPeakVals.dat");
    MeanPeakFile << to_string(MeanPol) + New_Line_str;
    MeanPeakFile << PeakPol;  
  }  
}

void Save_EP_Plots(string RunFileSt, string OutDir, string RunNum){ 
  string gifFlName = ""; 
  TCanvas * Plots; 
  TFile * RunFile = TFile::Open(RunFileSt.c_str());
  RunFile -> GetObject("genCanvas", Plots);
  gifFlName = "/Run_" + RunNum;
  gifFlName += ".gif";
  Plots->Draw();
  Plots ->SaveAs((OutDir + gifFlName).c_str());
  RunFile -> Close("R");
  cout << "Enhancement/pol canvas saved" << endl;
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
    cout << "Run number is outside defined range, please modify code to account for newer run periods" << endl;
  }
  return(RunPeriod);
 
}

void AnalyseRun_Fit_Only(string RunNumber, Double_t Beam_Energy, Double_t CollDist, Double_t CollDiam){

  string OutDir;
  string EnhOutDir;
  string EnhOutDatSt;
  string filenm;
  string FitFile;
  Double_t edge;
  Double_t sigma;
  Double_t chisq;
  Double_t MeanPol;
  Double_t PeakPol;
  Double_t OldChisq;
  fstream fileStream;

  OutDir = "HTML/OutFiles/Run_" + RunNumber; 
  filenm = OutDir + "/FitParameters.dat";     
  EnhOutDir = OutDir + "/EnhOut";
  EnhOutDatSt = EnhOutDir + ".dat";

  fitDataB(EnhOutDatSt.c_str(), RunNumber.c_str(), Beam_Energy, CollDist, CollDiam, OutDir , false);

  fileStream.open(filenm);
  if (fileStream) {
    fileStream >> edge;
    fileStream >> sigma;
    fileStream >> chisq;
  }
  fileStream.close();  
  if(chisq > 10){
    OldChisq = chisq;
    fitDataB(EnhOutDatSt.c_str(), RunNumber.c_str(), Beam_Energy, CollDist, CollDiam, OutDir , true);
    fileStream.open(filenm);
    if (fileStream) {
      fileStream >> edge;
      fileStream >> sigma;
      fileStream >> chisq;
    }
    fileStream.close();
    if(chisq > OldChisq){
      fitDataB(EnhOutDatSt.c_str(), RunNumber.c_str(), Beam_Energy, CollDist, CollDiam, OutDir , false);
    }
  } 
  if(isFittable == true){
    MeanPol = GetMeanInRange_NumOnly(RunNumber, OutDir);
    PeakPol = GetMaxPol_NumOnly(RunNumber, OutDir);
    const char * New_Line = "\n";
    string New_Line_str(New_Line);
    ofstream MeanPeakFile;
    MeanPeakFile.open(OutDir + "/MeanPeakVals.dat");
    MeanPeakFile << to_string(MeanPol) + New_Line_str;
    MeanPeakFile << PeakPol;  
  }

  FitFile = OutDir + "/Run_" + RunNumber + ".root";
  Save_EP_Plots(FitFile, OutDir, RunNumber); //Save Enhancement/Polarisation plots to HTML dir using Save_EP_Plots
  WritePolOutFile(FitFile, RunNumber, OutDir);

}

void AnalyseRun_Enhancement_Only(const char * DiFlNm, const char * AmFlNm, string RunNumber, string RunPeriod, const char * SkimName){

  const char * SlNm;
  const char * binEfl;
  string binEflSt;
  string OutDir;
  string SlNmSt; 
  string RunSeason;
  string RunYear;
  string RunAltYear;
  string EnhOutDir;
  string EnhOutDatSt;

  OutDir = "HTML/OutFiles/Run_" + RunNumber;
  EnhOutDir = OutDir + "/EnhOut";
  EnhOutDatSt = EnhOutDir + ".dat"; 
  
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
   SlNmSt = "DSelector_" + RunSeason + RunAltYear + ".C+";
   binEflSt =  "Efiles/" + RunSeason + RunAltYear + "Efile";
   SlNm = SlNmSt.c_str();
   binEfl = binEflSt.c_str();
   CalculateEnhancement(DiFlNm, AmFlNm, SlNm, EnhOutDir.c_str(), binEfl, RunNumber.c_str(), OutDir, SkimName);
   cout << "Enhancement Calculated" << endl;

}

//void AnalyseRun(string DiFile, string AmFileString, string RunNum, string RunPeriod, const char * AllRunsList){
void AnalyseRun(string DiFile, string AmFileString, string RunNum, string RunPeriod, const char * AllRunsList, const char * SkimName){
  string FitFile;
  Double_t BeamEnergy;
  string OutDir;

  FillRunList(AllRunsList);
  OutDir = "HTML/OutFiles/Run_" + RunNum;
  if (RunPeriod =="1/16"){
    BeamEnergy = 12000;
  }
  else if (RunPeriod =="2/16"){
    BeamEnergy = 12000;
  }
  else if (RunPeriod =="1/17"){
    BeamEnergy = 11700;
  }
  else if (RunPeriod =="1/18"){
    BeamEnergy = 11700;
  }
  else if (RunPeriod =="2/18"){
    BeamEnergy = 11700;
  }
   else if (RunPeriod =="1/19"){
    BeamEnergy = 11600;
  }
  else if (RunPeriod =="2/19"){
    BeamEnergy = 11300;
  }
  else{
    cout << "Invalid run period entered" << endl;
    return;
  }
  PlotAndFitEnh(DiFile.c_str(), AmFileString.c_str(), OutDir, BeamEnergy, RunNum, RunPeriod, AllRunsList, SkimName);
  if(isFittable == false){
    cout << "Data is not fittable" << endl;
    return;
  }
  FitFile = OutDir + "/Run_" + RunNum + ".root";
  Save_EP_Plots(FitFile, OutDir, RunNum); //Save Enhancement/Polarisation plots to HTML dir using Save_EP_Plots
  WritePolOutFile(FitFile, RunNum, OutDir);
}  
