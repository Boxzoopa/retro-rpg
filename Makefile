default:
	g++ -std=c++17 -o main.exe main.cpp include/cjson/cJSON.c src/*.cpp -lraylib -lgdi32 -lwinmm -Llib -Iinclude
# g++ -std=c++17 -o main.exe main.cpp include/cjson/cJSON.c src -lraylib -lgdi32 -lwinmm -Llib -Iinclude