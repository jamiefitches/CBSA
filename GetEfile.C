#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"

TH1F *HodoEnergy;
TH1F *MicroEnergy;
TH2F *HodoChanVTime;
TH2F *MicroChanVTime;

TFile *rootFile;

Long64_t i=0;
const int HCHAN=233;
const int MCHAN=104;

//Declaration of leaves types
UShort_t        nadc;
ULong64_t       eventnum;
Bool_t          isFiducial;
UShort_t        rocid[32];
UShort_t        slot[32];
UShort_t        channel[32];
UInt_t          itrigger[32];
ULong64_t       w_integral[32];
UShort_t        w_max[32];
UShort_t        w_min[32];
UShort_t        w_samp1[32];
UShort_t        sector[32];
Double_t        phi[32];
UShort_t        ntpol;
UShort_t        waveform[3200];
Double_t        PSenergy_lhit;
Double_t        PSenergy_rhit;
Double_t        PSCtime_lhit;
Double_t        PSCtime_rhit;
Double_t        PStime_lhit;
Double_t        PStime_rhit;
UShort_t        ntagh;
Bool_t          TAGH_DBeam[19]; 
Double_t        TAGHenergy[19];
Double_t        TAGHtime[19];
UInt_t          TAGHcounter[19];
UShort_t        ntagm;
Bool_t          TAGM_DBeam[23];
Double_t        TAGMenergy[23];
Double_t        TAGMtime[23];
UInt_t          TAGMcolumn[23];

void GetEfile(const char *infile, const char * Efile){

  Char_t hname[128]; 
  Char_t htitle[128];
  FILE *fp;

  int     prevcolumn = 0;
  Float_t prevtime   = 0.0;
  
  HodoEnergy     = new TH1F("HodoEnergy",     "HodoEnergy",     HCHAN,0,HCHAN);
  MicroEnergy    = new TH1F("MicroEnergy",    "MicroEnergy",    MCHAN,0,MCHAN);
  HodoChanVTime  = new TH2F("HodoChanVTime",  "HodoChanVTime",  HCHAN,0,HCHAN,201,-100,100.0);
  MicroChanVTime = new TH2F("MicroChanVTime", "MicroChanVTime", MCHAN,0,MCHAN,201,-100,100.0);

  TFile *fl = TFile::Open(infile);
  TTree *TPOL_tree = (TTree*)fl->Get("TPOL_tree");
  
  // Set branch addresses.
  TPOL_tree->SetBranchAddress("nadc",&nadc);
  TPOL_tree->SetBranchAddress("eventnum",&eventnum);
  TPOL_tree->SetBranchAddress("isFiducial",&isFiducial);
  TPOL_tree->SetBranchAddress("rocid",rocid);
  TPOL_tree->SetBranchAddress("slot",slot);
  TPOL_tree->SetBranchAddress("channel",channel);
  TPOL_tree->SetBranchAddress("itrigger",itrigger);
  TPOL_tree->SetBranchAddress("w_integral",w_integral);
  TPOL_tree->SetBranchAddress("w_max",w_max);
  TPOL_tree->SetBranchAddress("w_min",w_min);
  TPOL_tree->SetBranchAddress("w_samp1",w_samp1);
  TPOL_tree->SetBranchAddress("sector",sector);
  TPOL_tree->SetBranchAddress("phi",phi);
  TPOL_tree->SetBranchAddress("ntpol",&ntpol);
  TPOL_tree->SetBranchAddress("waveform",waveform);
  TPOL_tree->SetBranchAddress("PSenergy_lhit",&PSenergy_lhit);
  TPOL_tree->SetBranchAddress("PSenergy_rhit",&PSenergy_rhit);
  TPOL_tree->SetBranchAddress("PSCtime_lhit",&PSCtime_lhit);
  TPOL_tree->SetBranchAddress("PSCtime_rhit",&PSCtime_rhit);
  TPOL_tree->SetBranchAddress("PStime_lhit",&PStime_lhit);
  TPOL_tree->SetBranchAddress("PStime_rhit",&PStime_rhit);
  TPOL_tree->SetBranchAddress("ntagh",&ntagh);
  TPOL_tree->SetBranchAddress("TAGH_DBeam",TAGH_DBeam);
  TPOL_tree->SetBranchAddress("TAGHenergy",TAGHenergy);
  TPOL_tree->SetBranchAddress("TAGHtime",TAGHtime);
  TPOL_tree->SetBranchAddress("TAGHcounter",TAGHcounter);
  TPOL_tree->SetBranchAddress("ntagm",&ntagm);
  TPOL_tree->SetBranchAddress("TAGM_DBeam",TAGM_DBeam);
  TPOL_tree->SetBranchAddress("TAGMenergy",TAGMenergy);
  TPOL_tree->SetBranchAddress("TAGMtime",TAGMtime);
  TPOL_tree->SetBranchAddress("TAGMcolumn",TAGMcolumn);
    
  Long64_t nentries = TPOL_tree->GetEntries();

  Int_t numLarge = 0;
  Int_t numSmall = 0;
  
  for (int i=0; i<nentries;i++) {
    if(TPOL_tree->GetEntry(i)<1)continue;
    for (int n=0;n<ntagm;n++){
      if(TAGMenergy[n] < 9 && TAGMenergy[n] > 7.8){
	MicroEnergy->SetBinContent(TAGMcolumn[n],TAGMenergy[n]);
	MicroChanVTime->Fill(TAGMcolumn[n],TAGMtime[n]);
      }
    }
    if(TPOL_tree->GetEntry(i)<1)continue;
    for (int n=0;n<ntagh;n++){
      if((TAGHenergy[n] < 12 && TAGHenergy[n] >  8.85)||(TAGHenergy[n] < 7.91 && TAGHenergy[n] > 5.0)){
	HodoEnergy->SetBinContent(TAGHcounter[n],TAGHenergy[n]);
	HodoChanVTime->Fill(TAGHcounter[n],TAGHtime[n]);
      }
    }
  }
  fl->Close();
  fp = fopen(Efile,"w");

  vector<Double_t> EnergyArray;
  //print out all the energies in unsorted mode
  for(int n=1;n<=HodoEnergy->GetNbinsX();n++){
    if(HodoEnergy->GetBinContent(n)>0.0) EnergyArray.push_back(HodoEnergy->GetBinContent(n));
  }
  for(int n=1;n<=MicroEnergy->GetNbinsX();n++){
    if(MicroEnergy->GetBinContent(n)>0.0) EnergyArray.push_back(MicroEnergy->GetBinContent(n));
  }
  
  sort(EnergyArray.begin(), EnergyArray.end()); 
  EnergyArray.erase( unique( EnergyArray.begin(), EnergyArray.end() ), EnergyArray.end() );
  cout<< "number of bins: "<< EnergyArray.size()<<endl;

   for(int n =0; n<EnergyArray.size(); n++){
     fprintf(fp,"%5.3f ", EnergyArray[n]);
     fprintf(fp,"\n");
  }
   fprintf(fp,"\"");
   fclose(fp);
}
