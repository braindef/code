#include "stdafx.h"
#include "engine.h"
#include "stdio.h"
#include <vector>


landev::engine::engine(int countdown)
{
	number=countdown;
	landev::engine::print();
	for(int i=0; i<countdown; i++)
		if(countdown>0)
			children.push_back(new engine(countdown-1));
}

//		hookChild(engine* child);

int landev::engine::print()
{
	printf("%d ", number);
	return 0;
}
