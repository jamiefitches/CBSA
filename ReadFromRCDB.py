# import RCDB
from rcdb.provider import RCDBProvider

# connect to DB
db = RCDBProvider("mysql://rcdb@hallddb.jlab.org/rcdb")

label = input("Please enter run list label:\n")

MinRunNum = input("Please enter min run number:\n")

MaxRunNum = input("Please enter max run number:\n")

# select values with query
table = db.select_values(['polarization_angle', 'polarization_direction'], "@is_production", run_min=MinRunNum, run_max=MaxRunNum)

####################################################

f = open("RunConfig/%s_RunInfo.dat" % (label), "w")

f.write("#Run Angle Plane")
f.write("\n")
for row in table:
    print row[0], row[1], row[2]
    if row[2] == "PARA":
        PolDir = 1
    elif row[2] == "PERP":
        PolDir = 0
    else:
        PolDir = -1
        
    f.write("%d %d %d" % (row[0], row[1], PolDir))
    f.write("\n")

f.close()
