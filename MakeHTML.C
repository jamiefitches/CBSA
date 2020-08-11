#include "CBSA.h"


void MakeHTML(string RunPeriod, const char * AllRunsList, const char * HTMLname = "HTML/allpass0CP.html"){

  ifstream CheckStream;
  ofstream OutFl;
  const char * New_Line = "\n";
  string ParFileName; 
  string line;
  string New_Line_str(New_Line);
  Int_t counter = 0;
  Int_t RunNumMax;
  Int_t RunNumMin; 
  string RunSeason;
  string RunYear;
  string AltYear;

  FillRunList(AllRunsList);
  OutFl.open(HTMLname);
  
  OutFl << "<h3>Gluex Polarization/Enhancement Fits</h3>" + New_Line_str + "<h4>Hover the cursor over a run to display data</h4>" + New_Line_str + "<html>" + New_Line_str + "<head>" + New_Line_str + "<title>CBrem</title>" + New_Line_str + "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">" + New_Line_str + "<style type=\"text/css\">" + New_Line_str + "body" + New_Line_str + "{" + New_Line_str + "  <!-- background: url(main/img/watta2.gif) no-repeat fixed center ;-->"  + New_Line_str + "background-color: #2a4781 ;"  + New_Line_str + "   background-color: #363345 ;"  + New_Line_str + "   background-position: 200 160;" + New_Line_str + "   color: #CCFFFF;"+ New_Line_str +"}"+ New_Line_str + New_Line_str + ".mytable" + New_Line_str + "{" + New_Line_str + "font-family: Verdana, Arial, Helvetica, sans-serif;" + New_Line_str + "font-size: 9pt;"  + New_Line_str + "font-style: normal;" + New_Line_str + "color: #DDFFFF;" + New_Line_str + "}" + New_Line_str + "</style>" + New_Line_str + "<script>"  + New_Line_str + "function show(img)" + New_Line_str + "{" + New_Line_str + "var pic=img;" + New_Line_str + "top.showframe.document.images.pic1.src=pic;"  + New_Line_str + "}" + New_Line_str + "</script>"  + New_Line_str + "</head>" + New_Line_str + "<table border=\"0\">" + New_Line_str;

  if(RunPeriod == "1/16"){
    RunNumMax = 20000;
    RunNumMin = 10000;
  }
  else if(RunPeriod == "2/16"){
    RunNumMax = 30000;
    RunNumMin = 20000;
  }
  else if(RunPeriod == "1/17"){
    RunNumMax = 40000;
    RunNumMin = 30000;
  }
  else if(RunPeriod == "1/18"){
    RunNumMax = 50000;
    RunNumMin = 40000;
  }
  else if(RunPeriod == "2/18"){
    RunNumMax = 60000;
    RunNumMin = 50000;
  }
  else if(RunPeriod == "1/19"){
    RunNumMax = 70000;
    RunNumMin = 60000;
  }
  else if(RunPeriod == "2/19"){
    RunNumMax = 80000;
    RunNumMin = 70000;
  }
  else{
    cout << "Invalid run period" << endl;
  }
  
  if(RunPeriod[0] == '1'){
    RunSeason = "Spring";
  }
  else if(RunPeriod[0] == '2'){
    RunSeason = "Fall";    
  }

  if (RunPeriod[2] == '1'){
    if (RunPeriod[3] == '6'){
      RunYear = "2016";
      AltYear = "16";
    }
    if (RunPeriod[3] == '7'){
      RunYear = "2017";
      AltYear = "17";
    }
    if (RunPeriod[3] == '8'){
      RunYear = "2018";
      AltYear = "18";
    }
    if (RunPeriod[3] == '9'){
      RunYear = "2019";
      AltYear = "19";
    }
  }
  else if(RunPeriod[2] =='2'){
    if (RunPeriod[3] == '0'){
      RunYear = "2020";
      AltYear = "20";
    }
    if (RunPeriod[3] == '1'){
      RunYear = "2021";
      AltYear = "21";
    }
    if (RunPeriod[3] == '2'){
      RunYear = "2022";
      AltYear = "22";
    }
    if (RunPeriod[3] == '3'){
      RunYear = "2023";
      AltYear = "23";
    }
    if (RunPeriod[3] == '4'){
      RunYear = "2024";
      AltYear = "24";
    } 
    if (RunPeriod[3] == '5'){
      RunYear = "2025";
      AltYear = "25";
    }
  }

  ifstream param_out;
  string OutFileName;
  
  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear + ", Polar_0 , PARA: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str;
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) >= RunNumMin && stoi(RunList[i].RunNumber) < RunNumMax  && RunList[i].CrystalOrientation == 0 && RunList[i].isPara == true){
      OutFileName = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/FitParameters.dat";
      param_out.open(OutFileName.c_str());
      if(param_out){
	OutFl << "<td  onmouseover=\"show('OutFiles/Run_" + RunList[i].RunNumber + "/Run_" + RunList[i].RunNumber + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Run_" + RunList[i].RunNumber + "</FONT></td>" + New_Line_str;
	counter++;
	if(counter == 9){
	  counter = 0;
	  OutFl << "<tr>" + New_Line_str;
	}
      }
      param_out.close();
    }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear + ", Polar_0 , PERP: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str;
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) >= RunNumMin && stoi(RunList[i].RunNumber) < RunNumMax  && RunList[i].CrystalOrientation == 0 && RunList[i].isPara == false){
      OutFileName = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/FitParameters.dat";
      param_out.open(OutFileName.c_str());
      if(param_out){
	OutFl << "<td  onmouseover=\"show('OutFiles/Run_" + RunList[i].RunNumber + "/Run_" + RunList[i].RunNumber + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Run_" + RunList[i].RunNumber + "</FONT></td>" + New_Line_str;
	counter++;
	if(counter == 9){
	  counter = 0;
	  OutFl << "<tr>" + New_Line_str;
	}
      }
      param_out.close();
    }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear + ", Polar_45 , PARA: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str;
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) >= RunNumMin && stoi(RunList[i].RunNumber) < RunNumMax  && RunList[i].CrystalOrientation == 45 && RunList[i].isPara == true){
      OutFileName = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/FitParameters.dat";
      param_out.open(OutFileName.c_str());
      if(param_out){
	OutFl << "<td  onmouseover=\"show('OutFiles/Run_" + RunList[i].RunNumber + "/Run_" + RunList[i].RunNumber + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Run_" + RunList[i].RunNumber + "</FONT></td>" + New_Line_str;
	counter++;
	if(counter == 9){
	  counter = 0;
	  OutFl << "<tr>" + New_Line_str;
	}
      }
      param_out.close();
    }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear + ", Polar_45 , PERP: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str;
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) >= RunNumMin && stoi(RunList[i].RunNumber) < RunNumMax  && RunList[i].CrystalOrientation == 45 && RunList[i].isPara == false){
      OutFileName = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/FitParameters.dat";
      param_out.open(OutFileName.c_str());
      if(param_out){
	OutFl << "<td  onmouseover=\"show('OutFiles/Run_" + RunList[i].RunNumber + "/Run_" + RunList[i].RunNumber + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Run_" + RunList[i].RunNumber + "</FONT></td>" + New_Line_str;
	counter++;
	if(counter == 9){
	  counter = 0;
	  OutFl << "<tr>" + New_Line_str;
	}
      }
      param_out.close();
    }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear + ", Polar_90 , PARA: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str;
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) >= RunNumMin && stoi(RunList[i].RunNumber) < RunNumMax  && RunList[i].CrystalOrientation == 90 && RunList[i].isPara == true){
      OutFileName = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/FitParameters.dat";
      param_out.open(OutFileName.c_str());
      if(param_out){
	OutFl << "<td  onmouseover=\"show('OutFiles/Run_" + RunList[i].RunNumber + "/Run_" + RunList[i].RunNumber + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Run_" + RunList[i].RunNumber + "</FONT></td>" + New_Line_str;
	counter++;
	if(counter == 9){
	  counter = 0;
	  OutFl << "<tr>" + New_Line_str;
	}
      }
      param_out.close();
    }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear + ", Polar_90 , PERP: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str;
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) >= RunNumMin && stoi(RunList[i].RunNumber) < RunNumMax  && RunList[i].CrystalOrientation == 90 && RunList[i].isPara == false){
      OutFileName = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/FitParameters.dat";
      param_out.open(OutFileName.c_str());
      if(param_out){
	OutFl << "<td  onmouseover=\"show('OutFiles/Run_" + RunList[i].RunNumber + "/Run_" + RunList[i].RunNumber + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Run_" + RunList[i].RunNumber + "</FONT></td>" + New_Line_str;
	counter++;
	if(counter == 9){
	  counter = 0;
	  OutFl << "<tr>" + New_Line_str;
	}
      }
      param_out.close();
    }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear + ", Polar_135 , PARA: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str;
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) >= RunNumMin && stoi(RunList[i].RunNumber) < RunNumMax  && RunList[i].CrystalOrientation == 135 && RunList[i].isPara == true){
      OutFileName = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/FitParameters.dat";
      param_out.open(OutFileName.c_str());
      if(param_out){
	OutFl << "<td  onmouseover=\"show('OutFiles/Run_" + RunList[i].RunNumber + "/Run_" + RunList[i].RunNumber + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Run_" + RunList[i].RunNumber + "</FONT></td>" + New_Line_str;
	counter++;
	if(counter == 9){
	  counter = 0;
	  OutFl << "<tr>" + New_Line_str;
	}
      }
      param_out.close();
    }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear + ", Polar_135 , PERP: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str;
  for(Int_t i = 0; i < RunList.size(); i++){
    if(stoi(RunList[i].RunNumber) >= RunNumMin && stoi(RunList[i].RunNumber) < RunNumMax  && RunList[i].CrystalOrientation == 135 && RunList[i].isPara == false){
      OutFileName = "HTML/OutFiles/Run_" + RunList[i].RunNumber + "/FitParameters.dat";
      param_out.open(OutFileName.c_str());
      if(param_out){
	OutFl << "<td  onmouseover=\"show('OutFiles/Run_" + RunList[i].RunNumber + "/Run_" + RunList[i].RunNumber + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Run_" + RunList[i].RunNumber + "</FONT></td>" + New_Line_str;
	counter++;
	if(counter == 9){
	  counter = 0;
	  OutFl << "<tr>" + New_Line_str;
	}
      }
      param_out.close();
    }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear +", Channel Polarisation Timelines, Polar_0: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str; 
  for(Int_t channel = 1; channel < 216; channel++){
    OutFl <<  "<td  onmouseover=\"show('PolarTimelines_" + RunSeason + AltYear + "/Pol_0_Chan_" + to_string(channel) + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Channel_" + to_string(channel) + "</FONT></td>" + New_Line_str;
    counter++;
    if(counter == 9){
	counter = 0;
	OutFl << "<tr>" + New_Line_str;
      }
  }
  counter = 0;


  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear +", Channel Polarisation Timelines, Polar_45: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str; 
  for(Int_t channel = 1; channel < 216; channel++){
    OutFl << "<td  onmouseover=\"show('PolarTimelines_" + RunSeason + AltYear + "/Pol_45_Chan_" + to_string(channel) + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Channel_" + to_string(channel) + "</FONT></td>" + New_Line_str;
    counter++;
    if(counter == 9){
	counter = 0;
	OutFl << "<tr>" + New_Line_str;
      }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear +", Channel Polarisation Timelines, Polar_90: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str; 
  for(Int_t channel = 1; channel < 216; channel++){
    OutFl << "<td  onmouseover=\"show('PolarTimelines_" + RunSeason + AltYear + "/Pol_90_Chan_" + to_string(channel) + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Channel_" + to_string(channel) + "</FONT></td>" + New_Line_str;
    counter++;
    if(counter == 9){
	counter = 0;
	OutFl << "<tr>" + New_Line_str;
      }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear +", Channel Polarisation Timelines, Polar_135: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str; 
  for(Int_t channel = 1; channel < 216; channel++){
    OutFl << "<td  onmouseover=\"show('PolarTimelines_" + RunSeason + AltYear + "/Pol_135_Chan_" + to_string(channel) + ".gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Channel_" + to_string(channel) + "</FONT></td>" + New_Line_str;
    counter++;
    if(counter == 9){
	counter = 0;
	OutFl << "<tr>" + New_Line_str;
      }
  }
  counter = 0;

  OutFl << "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>"  + RunSeason + " " + RunYear + ", Chi Squared Timelines: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Chisq" + RunSeason + AltYear + "_Pol_0_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Chisq" + RunSeason + AltYear + "_Pol_0_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PERP, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Chisq" + RunSeason + AltYear + "_Pol_45_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Chisq" + RunSeason + AltYear + "_Pol_45_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PERP, </FONT></td>"  + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Chisq" + RunSeason + AltYear + "_Pol_90_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PARA, </FONT></td_Pol_90_PARA>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Chisq" + RunSeason + AltYear + "_Pol_90_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PERP, </FONT></td>"+ New_Line_str +  "<td  onmouseover=\"show('ParameterTimelines/Chisq" + RunSeason + AltYear + "_Pol_135_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Chisq" + RunSeason + AltYear + "_Pol_135_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PERP, </FONT></td>"  + New_Line_str + "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>"  + RunSeason + " " + RunYear + ", Coherent Edge Timelines: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Edge" + RunSeason + AltYear + "_Pol_0_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Edge" + RunSeason + AltYear + "_Pol_0_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PERP, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Edge" + RunSeason + AltYear + "_Pol_45_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Edge" + RunSeason + AltYear + "_Pol_45_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PERP, </FONT></td>"  + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Edge" + RunSeason + AltYear + "_Pol_90_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PARA, </FONT></td_Pol_90_PARA>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Edge" + RunSeason + AltYear + "_Pol_90_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PERP, </FONT></td>"+ New_Line_str +  "<td  onmouseover=\"show('ParameterTimelines/Edge" + RunSeason + AltYear + "_Pol_135_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Edge" + RunSeason + AltYear + "_Pol_135_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PERP, </FONT></td>"  + New_Line_str + "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>"  + RunSeason + " " + RunYear + ", Sigma Timelines: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Sigma" + RunSeason + AltYear + "_Pol_0_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Sigma" + RunSeason + AltYear + "_Pol_0_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PERP, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Sigma" + RunSeason + AltYear + "_Pol_45_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Sigma" + RunSeason + AltYear + "_Pol_45_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PERP, </FONT></td>"  + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Sigma" + RunSeason + AltYear + "_Pol_90_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PARA, </FONT></td_Pol_90_PARA>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Sigma" + RunSeason + AltYear + "_Pol_90_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PERP, </FONT></td>"+ New_Line_str +  "<td  onmouseover=\"show('ParameterTimelines/Sigma" + RunSeason + AltYear + "_Pol_135_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Sigma" + RunSeason + AltYear + "_Pol_135_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PERP, </FONT></td>"  + New_Line_str  + "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>"  + RunSeason + " " + RunYear + ", Theta Timelines: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Theta" + RunSeason + AltYear + "_Pol_0_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Theta" + RunSeason + AltYear + "_Pol_0_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PERP, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Theta" + RunSeason + AltYear + "_Pol_45_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Theta" + RunSeason + AltYear + "_Pol_45_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PERP, </FONT></td>"  + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Theta" + RunSeason + AltYear + "_Pol_90_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PARA, </FONT></td_Pol_90_PARA>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Theta" + RunSeason + AltYear + "_Pol_90_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PERP, </FONT></td>"+ New_Line_str +  "<td  onmouseover=\"show('ParameterTimelines/Theta" + RunSeason + AltYear + "_Pol_135_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/Theta" + RunSeason + AltYear + "_Pol_135_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PERP, </FONT></td>"  + New_Line_str  + "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>"  + RunSeason + " " + RunYear + ", Theta_r Timelines: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/ThetaR" + RunSeason + AltYear + "_Pol_0_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/ThetaR" + RunSeason + AltYear + "_Pol_0_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PERP, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/ThetaR" + RunSeason + AltYear + "_Pol_45_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/ThetaR" + RunSeason + AltYear + "_Pol_45_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PERP, </FONT></td>"  + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/ThetaR" + RunSeason + AltYear + "_Pol_90_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PARA, </FONT></td_Pol_90_PARA>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/ThetaR" + RunSeason + AltYear + "_Pol_90_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PERP, </FONT></td>"+ New_Line_str +  "<td  onmouseover=\"show('ParameterTimelines/ThetaR" + RunSeason + AltYear + "_Pol_135_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/ThetaR" + RunSeason + AltYear + "_Pol_135_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PERP, </FONT></td>"  + New_Line_str  + "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>"  + RunSeason + " " + RunYear + ", Sigma_r Timelines: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/SigmaR" + RunSeason + AltYear + "_Pol_0_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/SigmaR" + RunSeason + AltYear + "_Pol_0_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PERP, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/SigmaR" + RunSeason + AltYear + "_Pol_45_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/SigmaR" + RunSeason + AltYear + "_Pol_45_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PERP, </FONT></td>"  + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/SigmaR" + RunSeason + AltYear + "_Pol_90_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PARA, </FONT></td_Pol_90_PARA>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/SigmaR" + RunSeason + AltYear + "_Pol_90_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PERP, </FONT></td>"+ New_Line_str +  "<td  onmouseover=\"show('ParameterTimelines/SigmaR" + RunSeason + AltYear + "_Pol_135_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PARA, </FONT></td>" + New_Line_str + "<td  onmouseover=\"show('ParameterTimelines/SigmaR" + RunSeason + AltYear + "_Pol_135_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PERP, </FONT></td>"  + New_Line_str + "<tr><th align=\"left\" colspan=\"7\"><FONT SIZE=3>" + RunSeason + " " + RunYear + ", Peak Polarisation Timelines: </FONT></td></tr>" + New_Line_str + "<tr>" + New_Line_str + "<td  onmouseover=\"show('PeakPolTimelines/" + RunSeason + AltYear + "_pol0_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PARA, </FONT></td>" +  New_Line_str + + "<td  onmouseover=\"show('PeakPolTimelines/" + RunSeason + AltYear + "_pol0_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_0_PERP, </FONT></td>" +  New_Line_str + "<td  onmouseover=\"show('PeakPolTimelines/" + RunSeason + AltYear + "_pol45_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PARA, </FONT></td>" +  New_Line_str + "<td  onmouseover=\"show('PeakPolTimelines/" + RunSeason + AltYear + "_pol45_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_45_PERP, </FONT></td>" +  New_Line_str + "<td  onmouseover=\"show('PeakPolTimelines/" + RunSeason + AltYear + "_pol90_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PARA, </FONT></td>" +  New_Line_str + "<td  onmouseover=\"show('PeakPolTimelines/" + RunSeason + AltYear + "_pol90_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_90_PERP, </FONT></td>" +  New_Line_str + "<td  onmouseover=\"show('PeakPolTimelines/" + RunSeason + AltYear + "_pol135_PARA.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PARA, </FONT></td>" +  New_Line_str + "<td  onmouseover=\"show('PeakPolTimelines/" + RunSeason + AltYear + "_pol135_PERP.gif'); this.style.backgroundColor='#7c0416';\" onmouseout=\"this.style.backgroundColor='#363345';\"><FONT SIZE=2>Pol_135_PERP, </FONT></td>" + New_Line_str + "</table>" + New_Line_str + "</body>" + New_Line_str + "</html>";

  OutFl.close();
}

