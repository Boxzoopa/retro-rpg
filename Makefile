

default:
	g++ -std=c++17 -o main.exe main.cpp include/cjson/cJSON.c -lraylib -lgdi32 -lwinmm -Llib -Iinclude