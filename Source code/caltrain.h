#include <pthread.h>

struct station {
	// FILL ME IN
	int numOfPassengers;
	int maxCapacity;
	int currentlyBoarding;
	pthread_mutex_t stationLock;
 	pthread_cond_t trainArrival;
 	pthread_cond_t trainLeave;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);