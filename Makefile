engine : bin/obj/main.o bin/obj/collider.o bin/obj/physObj.o bin/obj/vector.o
	g++ -g -o bin/engine bin/obj/*


bin/obj/vector.o : src/vector.cpp include/geometry.h
	g++ -g -c src/vector.cpp -o bin/obj/vector.o

bin/obj/main.o : main.cpp include/physSpace.h
	g++ -g -c main.cpp -o bin/obj/main.o

bin/obj/collider.o : src/collider.cpp include/collider.h include/geometry.h
	g++ -g -c src/collider.cpp -o bin/obj/collider.o

bin/obj/physObj.o : src/physObj.cpp include/collider.h include/geometry.h include/physObj.h
	g++ -g -c src/physObj.cpp -o bin/obj/physObj.o

clean :
	rm bin/obj/* && rm bin/engine