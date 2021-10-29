#include <pthread.h>

struct station {
	// FILL ME IN
	pthread_mutex_t train_mutex;
	pthread_cond_t waiting_train;
	pthread_cond_t train_go;
	//number of people in station
	int in_station;
	//available seats in train
	int available_in_train;
	//passengers on board
	int move_to_train;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);