//definition

#include "ClassTemplate.h"

landev::ClassTemplate::ClassTemplate()
{
	ClassTemplate(0,0);
}

landev::ClassTemplate::ClassTemplate(int x, int y)
{
	this->x=x;
	this->y=y;
}

landev::ClassTemplate::X()
{
	return this->x;
}

landev::ClassTemplate::Y()
{
	return this->y;
}