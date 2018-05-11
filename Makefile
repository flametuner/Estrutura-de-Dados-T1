trabed: main.cpp linked_list.h linked_list.cpp linked_queue.h linked_queue.cpp track_queue.h track_queue.cpp vehicle.h vehicle.cpp semaphore.h
	g++ -o trabed -std=c++11 *.cpp
clean:
	rm trabed
