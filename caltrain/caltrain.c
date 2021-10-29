#include <pthread.h>
#include "caltrain.h"



void
station_init(struct station *station)
{
	// FILL ME IN
    pthread_mutex_init(&station->train_mutex, NULL);
    pthread_cond_init(&station->waiting_train, NULL);
    pthread_cond_init(&station->train_go, NULL);

    station->in_station=0;
    station->available_in_train=0;
    station->move_to_train=0;
}

void
station_load_train(struct station *station, int count)
{
    pthread_mutex_lock(&station->train_mutex);
    //set the available seats
    station->available_in_train=count;
    //check if the train has empty seats and there are passengers in station
    //else will leave
    if (station->available_in_train!=0 && station->in_station!=0) {
        //wake up all waiting passengers
        pthread_cond_broadcast(&station->waiting_train);
        //wait until passengers be on board
        pthread_cond_wait(&station->train_go, &station->train_mutex);
    }
    //train go
    station->available_in_train=0;

    pthread_mutex_unlock(&station->train_mutex);

}

void
station_wait_for_train(struct station *station)
{
	// FILL ME IN
    pthread_mutex_lock(&station->train_mutex);
    //increase people in station
    station->in_station++;
    //check if there is a train w ith empty seats and number of passengers
    //will be in board doesn't exceed time
    while (station->available_in_train == 0 || (station->move_to_train == station->available_in_train)) {
        pthread_cond_wait(&station->waiting_train, &station->train_mutex);
    }
    //increase passengers will be on board
    station->move_to_train++;
    pthread_mutex_unlock(&station->train_mutex);

}

void
station_on_board(struct station *station)
{
	// FILL ME IN
    pthread_mutex_lock(&station->train_mutex);
    station->in_station--;
    station->move_to_train--;
    station->available_in_train--;
    pthread_mutex_unlock(&station->train_mutex);
    //check to signal
    if((station->available_in_train==0 || station->in_station==0) && station->move_to_train==0){
        pthread_cond_signal(&station->train_go);
    }


}
