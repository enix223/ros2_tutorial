.PHONY: runsimplepub runsimplesub

runsimplepub: build
	ros2 run cl_pubsub publisher

runsimplesub: build
	ros2 run cl_pubsub subscriber
