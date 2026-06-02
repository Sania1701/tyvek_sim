#include "action.hh" 
#include "RunAction.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
    auto runAction = new RunAction();
    SetUserAction(runAction);
    
    MyPrimaryGenerator *generator = new MyPrimaryGenerator(runAction);
    SetUserAction(generator);
}
