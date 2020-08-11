# CBSA

This software, available at https://github.com/jamiefitches/CBSA, calculates beam polarisation from the parameters of a spectrum enhancement fit, using the technique documented in the following reference;

K. Livingston. Polarization from Coherent Bremsstrahlung Enhancement, CLAS Note 2011-02, CLAS Collaboration Jefferson Lab, 2011.
http://nuclear.gla.ac.uk/~kl/cbsa/FittingCoherentBrem.pdf

Before using this program, the folliwing directories must be created in the 'CBSA' folder:

/HTML/

/HTML/OutFiles/

/HTML/ParameterTimelines/

/HTML/PeakPolTimelines/

/HTML/RhoComparisons/

/HTML/PolarTimelines_<season><year>/ (e.g. PolarTimelines_Spring18, etc)
 
/ChanPolTimelines/

/TPOL_Comparison/RunConfig/

/TPOL_Comparison/Efiles/

/TPOL_Comparison/<season>_<year>_pol_<radiator_orientation>_FitOut/ (e.g. Spring_18_pol_0_FitOut)
 
/FarmInFiles/

/RunConfig/

Note that where there are options for <season>, <year> and <radiator_orientation>, the user will need to specify these based on the data sets under study. 

Also note that the naming convention used for <season> is that Spring = Jan-Jun and Fall = Jul-Dec. 

Information about which runs belong to which period can be found at https://halldweb.jlab.org/wiki/index.php/Run_Periods

Next, the correct run configurations need to be extracted from the RCDB database. This is done from the command line using;

./ReadFromRCDB <label> <min run> <max run> 
 
Where <min run> and <max run> define the range of all required diamond and amorphous run files and <label> specifies the name of the run config file.

To calculate enhancement and fit a single run, simply start ROOT and execute the following command;

.x AnalyseRun.C(A, B, C, D, E, F)

Where,

A = coherent run filename

B = incoherent (i.e. amorphous radiator) run filename

C = coherent run number in string format

D = run period (e.g. "1/17" for Jan-Jun 2017, "2/18" for Jul-Dec 2018, etc)

E = run config file

F = skim name

Note that the user must create the directory 'HTML/OutFiles/Run_<Run number>' prior to starting the program. All output files will be dumped in this directory.

Also note that input skim files must contain a tagged photon energy branch. The 'AnalyseRun.C' script assumes this branch is titled 'BeamEnergy' at line 988, so this line will need to be modified if the input skims photon energy branch has a different name. 

To calculate the enhancement only, start ROOT and use the commands;

.L AnalyseRun.C

AnalyseRun_Enhancement_Only(A, B, C, D, E) 

Where,

A = coherent run filename

B = incoherent (i.e. amorphous radiator) run filename

C = coherent run number in string format

D = run period (e.g. "1/17" for spring 2017, "2/18" for fall 18, etc)

E = skim name

To fit enhancement data only, start ROOT and use the commands;

.L AnalyseRun.C

AnalyseRun_Fit_Only(A, B, C, D) 

Where,

A = coherent run number in string format

B = photon beam energy

C = collimator distance

D = collimator diameter

Farm scripts are also provided for analysing a larger number of files. Before using this script, argument lists must be created. This can be achieved using the following ROOT commands;

.L GenerateFarmLists.C

GenerateFileLists_Range(A, B, C, D, E)

Where,

A = path to input run files

B = skim name

c = run config file

D = minimum run number

E = maximum run number

This will create the files 'FileList', 'AmFileList', 'RunList' and 'RunPeriodList' in the 'FarmInFiles' directory. The farm script is then run from the command line using;

./Farm_Submission FarmInFiles/FileList FarmInFiles/AmFileList FarmInFiles/RunList FarmInFiles/RunPeriodList <run config file> <skim name>
 
This automatically creates output directories for each run in 'HTML/OutFiles'. 

To calculate enhancements only, the following must be executed from the command line;  

./Farm_Enhancement_Submission FarmInFiles/FileList FarmInFiles/AmFileList FarmInFiles/RunList FarmInFiles/RunPeriodList <skim name>

And for fitting only, use the following;

./Farm_Fit_Submission FarmInFiles/RunList <beam energy> <collimator distance> <collimator diameter>

This program is also able to generate a HTML page, displaying all enhancement fits and polarisation profiles for a specified run period in a convenient format, in addition to channel polarisation, peak polarisation and fit parameter timelines. First, start ROOT and execute the command;

.x Make_HTML_Plots.C(run_period) 

This creates all plots required for the HTML and saves them in the necessary locations. The HTML is then generated using the ROOT command;

.x MakeHTML.C(run_period)

Note that all HTML scripts will be located in the 'HTML' directory. 
 
