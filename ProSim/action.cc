#include "action.hh"

MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const {
    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);

    MyEventAction* eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);

    MyPrimaryGenerator* generator = new MyPrimaryGenerator();
    SetUserAction(generator);
}
