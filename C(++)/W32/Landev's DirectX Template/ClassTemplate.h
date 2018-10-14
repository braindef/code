//Deklaration

#ifndef ClassTemplate_h
#define ClassTemplate_h

namespace landev 
{
	class ClassTemplate
	{
	public:
		int X();
		int Y();
	//private:
		ClassTemplate();
		ClassTemplate(int x, int y);
		//~ClassTemplate();
		int x,y;
	};
}


#endif
