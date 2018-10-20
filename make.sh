#!/bin/sh

docker build -t wilcotcpp-make \
	--build-arg USER_ID=$(id -u) \
	--build-arg GROUP_ID=$(id -g) \
	--quiet docker >/dev/null

docker run --rm --privileged -v "$(realpath .)":/app wilcotcpp-make $1
