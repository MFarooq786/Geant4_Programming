#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "SensitiveDetector.hh"

class MyRunAction;

class MyEventAction : public G4UserEventAction {
public:
    MyEventAction(MyRunAction* runAction);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event* event) override;
    virtual void EndOfEventAction(const G4Event* event) override;

private:
    MyRunAction* fRunAction;
};

#endif
