#pragma once

class IEvent 
{
public:	
	virtual  const char* getName() = 0;
	virtual ~IEvent() = default;
};   

//passive data