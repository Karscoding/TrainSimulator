#include "../simulator/objects/train.h"
#include "../simulator/objects/signal.h"

enum Task {
    ACCELERATE,
    DECCELERATE_TO_LIMIT,
    DECCELERATE_TO_STOP,
    COASTING,
    EMERGENCY,
    RECOVERY, // Recovering from Emergency Stop
    SHUNTING,
    PASSENGER_STOP,
    WAITING,
};

class AI {
private:
    bool running = false;
    int currentTask = Task::WAITING;
    int brakeFactor;

public:
    float maxSpeed;
    Train *train;

    AI(Train *train, float targetSpeed);
    void run();
    void update();
    void decideTask();
    void doTask();
    void close();
};