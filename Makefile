default: 
	g++ -O2 -Wall -oNoisyHunter.bin -Isrc/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window src/*.cpp

debug: 
	g++ -g -Wall -oNoisyHunter.bin -Isrc/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window src/*.cpp

clang:
	clang++ -O2 -Wall -oNoisyHunter.bin -Isrc/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window src/*.cpp

clang-debug:
	clang++ -g -Wall -oNoisyHunter.bin -Isrc/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window src/*.cpp
