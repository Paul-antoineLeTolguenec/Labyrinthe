#include <math.h>
#include <list>
#include <cstdlib> 
#include <iostream> 
#include <vector>
#include <unistd.h>

using namespace std ;
 class Cell{
 public:
 	Cell(int x, int y );
 	void add_neighb(Cell *c, int k=0);
 	void add_neighb(Cell *c1, Cell *c2, int k=0);
 	friend ostream& operator<<(ostream& stream, const Cell& C);
 	friend istream& operator>>(istream& stream, Cell* C);
 	
 	

 	int m_nb_neighb=0;
 	Cell **m_neighb=nullptr;
 	int m_x;
 	int m_y;
 	bool m_displayed=false;
 	bool m_displayed2=false;
 	bool in_the_path=false;
 };

