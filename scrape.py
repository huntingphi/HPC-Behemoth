import csv
import glob
import os
os.chdir("/home/jethro/MPI_DATA")

qsf = open("DATA1","w+")
psrsf = open("DATA2", "w+")
openMPIPsrsTitle = "OpenMPI-PSRS"
openMPPsrsTitle = "OpenMP-PSRS"
openMPIQSTitle = "OpenMPI-QS"
openMPQSTitle = "OpenMP-QS"
algo = ""
algo1 = ""
algo2 = ""

for file in glob.glob("*.csv"):
    # print(file)
    with open(file) as csvfile:
        print(file)
        readCSV = csv.reader(csvfile, delimiter=',')
        runningAverageQS, runningAveragePSRS = 0,0
        first = True;
        b,c = "",""
        i,j = 0,0
        for row in readCSV:
            if first:
                b, c = row[1], row[2]
                first = False
            algo = row[0]
            if algo == openMPIPsrsTitle or algo == openMPPsrsTitle:
                algo1 = algo
                runningAveragePSRS += float(row[3])
                i+=1
            elif algo == openMPIQSTitle or algo == openMPQSTitle:
                algo2 = algo
                runningAverageQS += float(row[3])
                j+=1
            # else:
                # raise Exception("Invalid Algo Name!")
            
        runningAveragePSRS /= i
        runningAverageQS /= j

        psrsf.write(algo1+","+b+","+c+","+str(runningAveragePSRS)+"\n")
        qsf.write(algo2+","+b+","+c+","+str(runningAverageQS)+"\n")

    
