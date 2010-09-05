default:
	rm *.o && rm *.so* && *.a || true
	#g++ -fPIC -g -c -Wall Vector2D.cpp
	g++ -fPIC -g -c -Wall Entity.cpp
	#g++ -fPIC -g -c -Wall NetworkManager.cpp
	g++ -shared -Wl,-soname,liblol.so -oliblol.so Entity.o -lboost_serialization-mt -lc
	#g++ -Wall -Wextra -shared -g -lboost_serialization -fPIC Entity.cpp Vector2D.cpp
	#g++ -shared -fPIC -oliblol.so *.o
	g++ -Wall -Wextra -g -L. -llol  main.cpp -otest.bin
