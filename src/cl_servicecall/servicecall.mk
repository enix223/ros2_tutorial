.PHONY: runservicecallsrv runservicecallcli

runservicecallsrv: build
	ros2 run cl_servicecall server

runservicecallcli: build
	ros2 run cl_servicecall client
