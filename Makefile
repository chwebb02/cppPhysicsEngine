engine : bin/obj/main.o bin/obj/collider.o bin/obj/physObj.o bin/obj/vector.o
	g++ -g -o bin/engine bin/obj/*

insidePoints : bin/obj/collider.o bin/obj/vector.o bin/obj/insidePoints.o
	g++ -g -o bin/testInsidePoints bin/obj/insidePoints.o bin/obj/vector.o bin/obj/collider.o

closestPoint : bin/obj/collider.o bin/obj/vector.o bin/obj/closestPoint.o
	g++ -g -o bin/testClosestPoint bin/obj/closestPoint.o bin/obj/vector.o bin/obj/collider.o

bin/obj/closestPoint.o : tests/closestPoint.cpp include/geometry.h include/collider.h
	g++ -g -c tests/closestPoint.cpp -o bin/obj/closestPoint.o

bin/obj/insidePoints.o : tests/insidePoints.cpp include/geometry.h include/collider.h
	g++ -g -c tests/insidePoints.cpp -o bin/obj/insidePoints.o

bin/obj/vector.o : src/vector.cpp include/geometry.h
	g++ -g -c src/vector.cpp -o bin/obj/vector.o

bin/obj/main.o : main.cpp include/physSpace.h
	g++ -g -c main.cpp -o bin/obj/main.o

bin/obj/collider.o : src/collider.cpp include/collider.h include/geometry.h
	g++ -g -c src/collider.cpp -o bin/obj/collider.o

bin/obj/physObj.o : src/physObj.cpp include/collider.h include/geometry.h include/physObj.h
	g++ -g -c src/physObj.cpp -o bin/obj/physObj.o

clean :
	rm bin/obj/* bin/test* bin/engine

cleanObjs :
	rm bin/obj/*