all: OpenMP-QS OpenMP-PSRS OpenMPI-QS OpenMPI-PSRS Vanilla-QS
# OpenMP-QS OpenMP-PSRS 
OpenMP-QS:
	@cd OpenMP/QS && make Sim
OpenMP-PSRS:
	@cd OpenMP/PSRS && make Sim
OpenMPI-QS:
	@cd OpenMPI/QS && make Sim
OpenMPI-PSRS:
	@cd OpenMPI/PSRS && make Sim
Vanilla-QS:
	@cd Vanilla/QS && make Sim

