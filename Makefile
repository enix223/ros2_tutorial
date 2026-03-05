.PHONY: build

build:
	colcon build

include src/cl_pubsub/pubsub.mk
include src/cl_action/action.mk
include src/cl_parameter/parameter.mk
include src/cl_servicecall/servicecall.mk
