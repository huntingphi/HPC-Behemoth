all: OpenMP-QS OpenMP-PSRS OpenMPI-QS OpenMPI-PSRS Vanilla-QS
# OpenMP-QS OpenMP-PSRS 
OpenMP-QS:
	@cd OpenMP/QS && make Sim >> Sim-OpenMP-QS.csv
OpenMP-PSRS:
	@cd OpenMP/PSRS && make Sim >> Sim-OpenMP-PSRS.csv
OpenMPI-QS:
	@cd OpenMPI/QS && make Sim >> Sim-OpenMPI-QS.csv
OpenMPI-PSRS:
	@cd OpenMPI/PSRS && make Sim >> Sim-OpenMPI-PSRS.csv
Vanilla-QS:
	@cd Vanilla/QS && make Sim >> Sim-Vanilla-QS.csv

