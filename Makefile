.PHONY: build

build:
	colcon build

include src/cl_pubsub/pubsub.mk
include src/cl_servicecall/servicecall.mk
