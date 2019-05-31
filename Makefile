
all: OpenMP-QS OpenMP-PSRS OpenMPI-QS OpenMPI-PSRS Vanilla-QS

OpenMP: OpenMP-QS OpenMP-PSRS Vanilla-QS

OpenMPI: OpenMPI-QS OpenMPI-PSRS Vanilla-QS

# OpenMP-QS OpenMP-PSRS 
OpenMP-QS:
	# @cd OpenMP/QS && make Sim
	make Sim -C OpenMP/QS 
OpenMP-PSRS:
	@cd OpenMP/PSRS && make Sim
OpenMPI-QS:
	@cd OpenMPI/QS && make Sim
OpenMPI-PSRS:
	@cd OpenMPI/PSRS && make Sim
Vanilla-QS:
	@cd Vanilla/QS && make Sim

