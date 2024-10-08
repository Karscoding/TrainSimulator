#include "../simulator/objects/train.h"

enum Task {
    ACCELERATE,
    DECCELERATE,
    EMERGENCY,
    SHUNTING,
    PASSENGER_STOP,
    WAITING,
};

class AI {
private:
    bool running = false;
    int currentTask = Task::ACCELERATE;

public:
    float targetSpeed;
    Train *train;

    AI(Train *train, float targetSpeed);
    void run();
    void close();
};