#ifndef MYEVENTACTION_HH
#define MYEVENTACTION_HH

#include "G4UserEventAction.hh"
#include <fstream>

class MyEventAction : public G4UserEventAction {
public:
  MyEventAction();
  virtual ~MyEventAction();
  
  virtual void BeginOfEventAction(const G4Event* event) override;
  virtual void EndOfEventAction(const G4Event* event) override;
  
private:
  std::ofstream fOutputFile;
};

#endif
