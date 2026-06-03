#include "action.hh" 
#include "generator.hh"
//#include "runaction.hh"
MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
   // auto runAction = new MyRunAction();
  //  SetUserAction(runAction);
  
  
    
   // MyPrimaryGenerator *generator = new MyPrimaryGenerator(runAction);
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);
    
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);
    
}
