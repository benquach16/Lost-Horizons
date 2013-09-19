#ifndef _TRIGGER_H_
#define _TRIGGER_H_


//triggers are a level design mission element
//when an object enters the trigger area, we do another mission element
//such as complete objective or spawn enemy ships etc
class Trigger
{
public:
	Trigger();
	~Trigger();
	void run();
protected:

};


#endif
