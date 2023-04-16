#include <pthread.h> 
#include <stdio.h>
#include "caltrain.h" 
 
 
 
void 
station_init(struct station *station) 
{ 
 // FILL ME IN 
   station->numOfPassengers = 0; 
   station->maxCapacity = 0;
   station->currentlyBoarding = 0;
   pthread_mutex_init(&station->stationLock, NULL);
   pthread_cond_init(&station->trainArrival, NULL);
   pthread_cond_init(&station->trainLeave, NULL);
} 
 
void 
station_load_train(struct station *station, int count) 
{ 
   if (count == 0)
      return;
 // FILL ME IN 
   pthread_mutex_lock(&station->stationLock);
   if(station->numOfPassengers == 0)
   {
      pthread_mutex_unlock(&station->stationLock);
      return;
   }
   station->maxCapacity = count;
   pthread_cond_broadcast(&station->trainArrival);
   pthread_cond_wait(&station->trainLeave, &station->stationLock);
   // printf("train left\n");
   pthread_mutex_unlock(&station->stationLock);
} 
 
void 
station_wait_for_train(struct station *station) 
{ 
 // FILL ME IN 
   pthread_mutex_lock(&station->stationLock);
   // passenger enters station
   station->numOfPassengers++;
   // while loop to make sure that no passenger enters train while its full
   // reblocks thread if train is full because of use of broadcast
   while(station->maxCapacity == 0)
   {
      pthread_cond_wait(&station->trainArrival, &station->stationLock);
   }
   // to make sure that every passenger found a seat before train leaves
   station->currentlyBoarding++;
   // to symbolize that a passenger has boarded
   station->numOfPassengers--;
   // to symbolize that a seat has been taken
   station->maxCapacity--;
   // printf("currently in station: %d %d\n", station->maxCapacity, station->numOfPassengers);
   pthread_mutex_unlock(&station->stationLock);
 
} 
 
void 
station_on_board(struct station *station) 
{ 
 // FILL ME IN 
   pthread_mutex_lock(&station->stationLock);
      // passenger found a seat
      station->currentlyBoarding--;
      // printf("currently boarding: %d %d\n", station->currentlyBoarding, station->numOfPassengers);
      // train leaves if every passenger found a seat and theres no more space for another passenger,
      // or if there are no more passengers in the station
      if(station->currentlyBoarding == 0 && station->maxCapacity == 0 || station->numOfPassengers == 0 && station->currentlyBoarding == 0)
         pthread_cond_signal(&station->trainLeave);
   pthread_mutex_unlock(&station->stationLock);
}