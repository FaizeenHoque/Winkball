.PHONY: build run dev

build:
	g++ main.cpp -I/usr/include/opencv5 \
		-lopencv_videoio \
		-lopencv_highgui \
		-lopencv_imgproc \
		-lopencv_core \
		-lopencv_xobjdetect \
		-o build/main

run:
	./build/main

dev:
	make build
	make run