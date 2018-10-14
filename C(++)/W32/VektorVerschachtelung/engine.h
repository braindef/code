#ifndef engine_h
#define engine_h

#include <vector>

namespace landev
{
	class engine
	{
	public:
		engine(int countdown);
		//hookChild(engine* child);
		int print();

		std::vector<engine*> children;
		int number;
	};
}

#endif