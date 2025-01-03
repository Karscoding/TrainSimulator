#include "../simulator/objects/train.h"
#include "../simulator/objects/signal.h"

enum Task {
    ACCELERATE,
    DECCELERATE_TO_LIMIT,
    DECCELERATE_TO_STOP_FOR_SIGNAL,
    DECCELERATE_TO_STOP_FOR_STATION,
    COASTING,
    EMERGENCY,
    RECOVERY, // Recovering from Emergency Stop
    SHUNTING,
    PASSENGER_STOP,
    WAITING,
    THINKING,
};

class AI {
private:
    bool running = false;
    int currentTask = Task::THINKING;
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