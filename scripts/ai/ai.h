#include "../simulator/objects/train.h"
#include "../simulator/objects/signal.h"

enum Task {
    ACCELERATE,
    DECCELERATE,
    COASTING,
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
    void update();
    void close();
};