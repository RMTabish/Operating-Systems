#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define MAX_CARS 4
#define MAX_BUSES 1

pthread_mutex_t bridge_mutex;
pthread_cond_t car_cond;
pthread_cond_t bus_cond;

int num_cars_on_bridge = 0;
int num_buses_on_bridge = 0;

void ArriveAtBridge(int dir, int v_type) {
    pthread_mutex_lock(&bridge_mutex);

    if (v_type == 0) { // Car
        while (num_cars_on_bridge + 1 > MAX_CARS || num_buses_on_bridge > 0) {
            pthread_cond_wait(&car_cond, &bridge_mutex);
        }
        num_cars_on_bridge++;
    } else { // Bus
        while ((num_cars_on_bridge + 2 > MAX_CARS || num_buses_on_bridge >= MAX_BUSES) && num_cars_on_bridge > 0) {
            pthread_cond_wait(&bus_cond, &bridge_mutex);
        }
        num_buses_on_bridge++;
    }

    std::cout << "Vehicle (Type: " << v_type << ", Direction: " << dir << ") arrived at the bridge." << std::endl;

    pthread_mutex_unlock(&bridge_mutex);
}

void ExitTheBridge(int v_type) {
    pthread_mutex_lock(&bridge_mutex);

    if (v_type == 0) { // Car
        num_cars_on_bridge--;
        pthread_cond_signal(&car_cond);
    } else { // Bus
        num_buses_on_bridge--;
        pthread_cond_signal(&bus_cond);
        pthread_cond_broadcast(&car_cond);
    }

    std::cout << "Vehicle (Type: " << v_type << ") exited the bridge." << std::endl;

    pthread_mutex_unlock(&bridge_mutex);
}

void* VehicleThread(void* arg) {
    int dir = *((int*)arg);
    int v_type = rand() % 2; // Randomly choose vehicle type (0 for car, 1 for bus)

    ArriveAtBridge(dir, v_type);
    sleep(1); // Simulate crossing the bridge
    ExitTheBridge(v_type);

    pthread_exit(NULL);
}

int main() {
    int num_mins = 5; // User-specified number of minutes

    pthread_mutex_init(&bridge_mutex, NULL);
    pthread_cond_init(&car_cond, NULL);
    pthread_cond_init(&bus_cond, NULL);

    pthread_t threads[10]; // Assuming a maximum of 10 threads

    // Create threads at regular intervals
    for (int i = 0; i < num_mins * 60; i++) {
        int dir = i % 2; // Alternate directions

        pthread_create(&threads[i % 10], NULL, VehicleThread, (void*)&dir);

        sleep(1); // Wait for 1 second before creating the next thread
    }

    // Wait for all threads to finish
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&bridge_mutex);
    pthread_cond_destroy(&car_cond);
    pthread_cond_destroy(&bus_cond);

    return 0;
}
