#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int shared_speed = 0;
pthread_mutex_t speed_mutex;

// the sensor (thread 1)
void* sensor_routine(void* arg) {
    for(int i = 0; i < 5; i++) {
        sleep(1); // fetching new data in one second

        pthread_mutex_lock(&speed_mutex);

        shared_speed += 20; // new speed data
        printf("[Sensor] Fetched speed data: %d km/h\n", shared_speed);

        pthread_mutex_unlock(&speed_mutex);
    }
    return NULL;
}

// the controller (thread 2)
void* controller_routine(void* arg) {
    for(int i = 0; i < 5; i++) {
        sleep(1); // sync with sensor

        pthread_mutex_lock(&speed_mutex);

        int current_speed = shared_speed;
        printf("[Controller] Read speed from sensor: %d km/h\n", current_speed);

        pthread_mutex_unlock(&speed_mutex);
    }
    return NULL;
}

int main() {
    pthread_t sensor_tid, controller_tid;

    pthread_mutex_init(&speed_mutex, NULL);

    printf("[System] Initializing middleware threads...\n");

    pthread_create(&sensor_tid, NULL, sensor_routine, NULL);

    pthread_create(&controller_tid, NULL, controller_routine, NULL);

    pthread_join(sensor_tid, NULL);
    pthread_join(controller_tid, NULL);

    pthread_mutex_destroy(&speed_mutex);
    printf("[System] Program terminated.\n");

    return 0;
}
