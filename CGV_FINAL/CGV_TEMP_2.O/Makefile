GRL  = -lGL -lGLU -lglut -lsoil2 -I/usr/local/include/soil2/
OBJS = build/CITY.o  build/MYUTILITY.o build/BUILDING.o build/CAMERA.o build/ROAD.o build/MOTION.o build/FLAG.o build/ALL.o build/MENU.o build/XPLORE.o build/CONTROLS.o build/run.o

all: build build/hello

build:
	mkdir -p build

build/hello: $(OBJS)
	g++ $(OBJS) -o build/hello $(GRL)

build/CITY.o: ./src/CITY.cpp
	g++ -c ./src/CITY.cpp -o build/CITY.o $(GRL)

build/MYUTILITY.o: ./src/MYUTILITY.cpp
	g++ -c ./src/MYUTILITY.cpp -o build/MYUTILITY.o $(GRL)

build/BUILDING.o: ./src/BUILDING.cpp
	g++ -c ./src/BUILDING.cpp -o build/BUILDING.o $(GRL)

build/CAMERA.o: ./src/CAMERA.cpp
	g++ -c ./src/CAMERA.cpp -o build/CAMERA.o $(GRL)

build/ROAD.o: ./src/ROAD.cpp
	g++ -c ./src/ROAD.cpp -o build/ROAD.o $(GRL)

build/MOTION.o: ./src/MOTION.cpp
	g++ -c ./src/MOTION.cpp -o build/MOTION.o $(GRL)

build/FLAG.o: ./src/FLAG.cpp
	g++ -c ./src/FLAG.cpp -o build/FLAG.o $(GRL)

build/MENU.o: ./src/MENU.cpp
	g++ -c ./src/MENU.cpp -o build/MENU.o $(GRL)

build/XPLORE.o: ./src/XPLORE.cpp
	g++ -c ./src/XPLORE.cpp -o build/XPLORE.o $(GRL)

build/CONTROLS.o: ./src/CONTROLS.cpp
	g++ -c ./src/CONTROLS.cpp -o build/CONTROLS.o $(GRL)

build/run.o: ./src/run.cpp
	g++ -c ./src/run.cpp -o build/run.o $(GRL)

build/ALL.o: ./src/ALL.cpp
	g++ -c ./src/ALL.cpp -o build/ALL.o $(GRL)

	

clean:
	rm -rf build/*
