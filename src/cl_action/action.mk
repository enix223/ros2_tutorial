.PHONY: runactionsrv runactioncli

runactionsrv: build
	ros2 run cl_action server

runactioncli: build
	ros2 run cl_action client
