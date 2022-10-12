all: linux

irix:
	@-mkdir -p plugins/Irix
	@cd VCOLLIDE && make -s irix
	@cd src && make -s irix
	@cd geometry && make -i -s irix
	@cd systems && make -i -s irix
	@cd simulators && make -i -s irix
	@cd actuators && make -i -s irix 

linux:
	@-mkdir -p plugins/Linux
	@cd VCOLLIDE && make -s linux
	@cd src && make -s linux
	@cd geometry && make -i -s linux
	@cd systems && make -i -s linux
	@cd simulators && make -i -s linux
	@cd actuators && make -i -s linux

clean:
	@cd VCOLLIDE && make -i clean
	@cd src	&& make -i clean
	@cd actuators &&	make -i clean
	@cd geometry && make -i clean
	@cd plugins && make -i clean
	@cd sdfastObjs && make -i clean
	@cd simulators && make -i clean
	@cd systems && make -i clean
