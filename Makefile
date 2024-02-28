OPTIMIZATION_LVL=-O

engine : bin/obj/main.o bin/obj/collider.o bin/obj/physObj.o bin/obj/vector.o | objDir
	g++ -g ${OPTIMIZATION_LVL} -o bin/engine bin/obj/*

binDir:
	mkdir -p bin

objDir: binDir
	mkdir -p bin/obj

insidePoints : bin/obj/collider.o bin/obj/vector.o bin/obj/insidePoints.o | objDir
	g++ -g ${OPTIMIZATION_LVL} -o bin/testInsidePoints bin/obj/insidePoints.o bin/obj/vector.o bin/obj/collider.o

closestPoint : bin/obj/collider.o bin/obj/vector.o bin/obj/closestPoint.o | objDir
	g++ -g ${OPTIMIZATION_LVL} -o bin/testClosestPoint bin/obj/closestPoint.o bin/obj/vector.o bin/obj/collider.o

bin/obj/closestPoint.o : tests/closestPoint.cpp include/geometry.h include/collider.h | objDir
	g++ -g ${OPTIMIZATION_LVL} -c tests/closestPoint.cpp -o bin/obj/closestPoint.o

bin/obj/insidePoints.o : tests/insidePoints.cpp include/geometry.h include/collider.h | objDir
	g++ -g ${OPTIMIZATION_LVL} -c tests/insidePoints.cpp -o bin/obj/insidePoints.o

bin/obj/vector.o : src/vector.cpp include/geometry.h | objDir
	g++ -g ${OPTIMIZATION_LVL} -c src/vector.cpp -o bin/obj/vector.o

bin/obj/main.o : main.cpp include/physSpace.h | objDir
	g++ -g ${OPTIMIZATION_LVL} -c main.cpp -o bin/obj/main.o

bin/obj/collider.o : src/collider.cpp include/collider.h include/geometry.h | objDir
	g++ -g ${OPTIMIZATION_LVL} -c src/collider.cpp -o bin/obj/collider.o

bin/obj/physObj.o : src/physObj.cpp include/collider.h include/geometry.h include/physObj.h | objDir
	g++ -g ${OPTIMIZATION_LVL} -c src/physObj.cpp -o bin/obj/physObj.o

clean :
	rm bin/obj/* bin/test* bin/engine

cleanObjs :
	rm bin/obj/*