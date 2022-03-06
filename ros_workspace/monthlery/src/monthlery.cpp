#include "controller/controllerSetup.hpp"
#include <iostream>
#include <string>

using namespace std;

const int vertAxis = 1;
const int horAxis = 0;

const int upButton = 3;
const int downButton = 0;
const int leftArmButton = 1;
const int rightArmButton = 2;
const int activateButton = 5;
const int releaseButton = 4;

const string defaultCommand = "cd /home/julien/Documents/Intech/TechTheTime-LowLevel && sudo ./shell /dev/ttyACM0 ";

/* int64_t armId = 0;
std::array<int, 6> armsAngle = {0, 0, 0, 0, 0, 0}; // Angles par défauts

const int step = 10;
const int maxUp = 50;
const int maxDown = -50; */

void callShell(string order, int ticks)
{
    (void) order; (void) ticks;
    string cmd = defaultCommand + order + " " + to_string(ticks);
    system(cmd.data());
}

int main()
{
    system("sudo ls");

    Binder binder = Binder();

    binder.BindAxis(horAxis, [&](int, int value) {
        if (value > 1000) {
            cout << "rotate right" << endl;
            callShell("rotate", +15);
        }
        else if (value < -1000) {
            cout << "rotate left" << endl;
            callShell("rotate", -15);
        }
        else {
            cout << "stop" << endl;
            
        }
    });
    binder.BindAxis(vertAxis, [&](int, int value) {
        if (value > 1000) {
            cout << "move backward" << endl;
            callShell("translate", +15);
        }
        else if (value < -1000) {
            cout << "move forward" << endl;
            callShell("translate", -15);
        }
        else {
            cout << "stop" << endl;

        }
    });

    /* binder.BindButton(upButton, [&](int, bool state)
                      {
        if (state) {
            if (armsAngle[armId] < maxUp) {
                armsAngle[armId] += step;
                cout << "move arm " << armId << " to : " << armsAngle[armId] << endl;
                commClient->send(OrderCodes::MOVE_ARM, 0, armId, armsAngle[armId]);
            }
        } });
    binder.BindButton(downButton, [&](int, bool state)
                      {
        if (state) {
            if (armsAngle[armId] > maxDown) {
                armsAngle[armId] -= step;
                cout << "move arm " << armId << " to : " << armsAngle[armId] << endl;
                commClient->send(OrderCodes::MOVE_ARM, 0, armId, armsAngle[armId]);
            }
        } });

    binder.BindButton(leftArmButton, [&](int, bool state)
                      {
        if (state) {
            armId = (armId + 1) % 6;
        } });
    binder.BindButton(rightArmButton, [&](int, bool state)
                      {
        if (state) {
            armId = (armId + 5) % 6;
        } });

    binder.BindButton(activateButton, [&](int, bool state)
                      {
        if (state) {
            cout << "activate pump " << armId << endl;
            commClient->send(OrderCodes::ACTIVATE_PUMP, 0, armId, 0);
        } });
    binder.BindButton(releaseButton, [&](int, bool state)
                      {
        if (state) {
            cout << "release pump " << armId << endl;
            commClient->send(OrderCodes::RELEASE_PUMP, 0, armId, 0);
        } }); */

    ControllerSetup controller = ControllerSetup(binder);
    controller.run(false);
}