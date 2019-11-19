#include <math.h>
#include <list>
#include <cstdlib> 
#include <iostream> 
#include <vector>
#include <unistd.h>
#include "vibes.h"
//#include "Cell.h"
#include "Path.h"
#include <fstream>
#include <unistd.h>
using namespace std;


struct Maze{
	vector<Cell> Content;
	Cell *c_init;
	Cell *c_end;

	Maze(int n=0, int m=0,Cell *c_init_1=NULL,Cell *c_end_1=NULL){
		if(n!=0){
			for(int i=0 ; i<n; i++){
				for(int k=0;k<m;k++){
					Content.push_back(Cell(k,n-1-i));
				}
			}
		}
		if(c_init_1==NULL){
			c_init=&Content[0];
			c_end=&Content[4];
		}
		else{
			c_init=c_init_1;
			c_end=c_end_1;
		}

	}
	void create_maze(){
		Content[1].add_neighb(&Content[0],&Content[2]);
		Content[3].add_neighb(&Content[2],&Content[7]);
		Content[11].add_neighb(&Content[15],&Content[7]);
		Content[14].add_neighb(&Content[15],&Content[10]);
		Content[9].add_neighb(&Content[10],&Content[13]);
		Content[5].add_neighb(&Content[9],&Content[6]);
		Content[12].add_neighb(&Content[13],&Content[8]);
		Content[4].add_neighb(&Content[8]);



	}


	void draw_gate(const Cell *n1, const Cell *n2){
	vibes::drawBox(min(n1->m_x, n2->m_x) + 0.1, max(n1->m_x, n2->m_x) + 0.9,min(n1->m_y, n2->m_y) + 0.1, max(n1->m_y, n2->m_y) + 0.9,"lightGray[lightGray]");
	}


	void display_cell(Cell *cell){

	vibes::drawBox(cell->m_x, cell->m_x + 1, cell->m_y, cell->m_y + 1, "[Black]");
	cell->m_displayed = true;
	for(int i = 0 ; i < cell->m_nb_neighb ; i++)
	{
		if(!cell->m_neighb[i]->m_displayed)
		display_cell(cell->m_neighb[i]);
		draw_gate(cell, cell->m_neighb[i]);
	}
	}

	void display_cell_extrem(Cell *cell){
	vibes::drawPoint(cell->m_x+0.3, cell->m_y + 0.7, 15, "[Red]");
	
	}

	void display(){
		display_cell(c_init);
		display_cell_extrem(c_init);
		display_cell_extrem(c_end);
	}

	
};

///////////////////////////////////////////////////////////////////////////////////// FIN class Maze /////////////////////////////////////////////////////////////////////////////


//Maintenant on gère les fonctions externe pour le path




// je redéfinie les fonction de dessin propres au path.


void display_cell_path(Cell *cell){

vibes::drawPoint(cell->m_x+0.4, cell->m_y + 0.6, 10, "[Green]");


}

// fonction qui permet de dessiner le chemin.
void draw_path(Path *p){
	Path *actual_Path=p;
	//const Cell *actual_Cell= p.get_m_c();
	while(actual_Path->get_m_next()!=NULL){
		display_cell_path((Cell*)actual_Path->get_m_c());
		actual_Path=actual_Path->get_m_next();
	}
	display_cell_path((Cell*)actual_Path->get_m_c());
}

void initialisation(Cell *cell){

	cell->m_displayed = false;
	for(int i = 0 ; i < cell->m_nb_neighb ; i++)
	{
		if(cell->m_neighb[i]->m_displayed)
		initialisation(cell->m_neighb[i]);
		
	}
	}
int search(Cell *cell,Maze *m,int *find){
	cout<<"ok"<<endl;
	cout<< cell->m_x;
	cout<< cell->m_y<<endl;
	cell->m_displayed2 = true;
	
	if(cell==m->c_end){
		*find=true;
	}
	
	
	//cout<<"ok"<<endl;
	//cout<< cell->m_x;
	//cout<< cell->m_y<<endl;
	else{
	for(int i = 0 ; i < cell->m_nb_neighb ; i++)
	{
		//cout<< cell->m_neighb[i]->m_x;
		//cout<< cell->m_neighb[i]->m_y;
		//cout<< cell->m_neighb[i]->m_displayed2<<endl;
		if(!cell->m_neighb[i]->m_displayed2){
			cout<<"ici"<<endl;
			//break;
			
			search(cell->m_neighb[i],m,find);
		}
	
	}
	cout<<*find<<endl;
	return(*find);

	

}
	
	
	//}
//	else{
//		return(false);
//	}
}

void create_path(Path *p,Maze *m){
	//initialisation:
	Cell *cell=m->c_init;
	initialisation(cell);
	cell->m_displayed=true;
	cell->m_displayed2=true;
	// on commance la recherche
	while(cell!=m->c_end){
		//dans le cas où il n'y a pas à chercher car ya que 2 voisins
		if (cell->m_nb_neighb<=2){
			for(int i = 0 ; i < cell->m_nb_neighb ; i++)
			{
				if(!cell->m_neighb[i]->m_displayed){
					cell=cell->m_neighb[i];
					cell->m_displayed=true;
					cell->m_displayed2=true;
					p->add_to_path(cell);
					//cout<< cell->m_x;
					//cout<< cell->m_y;
					//cout<< cell->m_nb_neighb<<endl;
					break;

				}
		
			}

		}

		else{

			cout<< cell->m_x;
			cout<< cell->m_y<<endl;
			
			cell->m_displayed=true;
			cell->m_displayed2=true;
			for(int i = cell->m_nb_neighb-1 ; i >= 0 ; i--)
			{   
				
				cout<< cell->m_neighb[i]->m_x;
				cout<< cell->m_neighb[i]->m_y<<endl;
				if(!cell->m_neighb[i]->m_displayed){
					
					int find=0;
					if(search(cell->m_neighb[i],m,&find)==1){
						cell=cell->m_neighb[i];
						cell->m_displayed=true;
						p->add_to_path(cell);
						
						cout<< cell->m_x;
						cout<< cell->m_y<<endl;
						cout<<"fini"<<endl;
						
						break;
						

					}

				}


			}
		//break;
		}

	}
	
}

void RO(Cell *cell,Maze *maze,bool &find){
	
	cell->m_displayed = true;
	if(cell==maze->c_end){
		cout<<"ok"<<endl;
		find=true;
		//cell->in_the_path=true;
	}
	int i=0;
	while (i < cell->m_nb_neighb and find==false)
	{
		
		if(!cell->m_neighb[i]->m_displayed){
			
			RO(cell->m_neighb[i],maze,find);
		}
		i=i+1;
		
	}
	if(find){
		
		cell->in_the_path=true;
	}
	}
void update_path(Cell *cell,Path *path){
	cell->m_displayed2 = true;
	if(cell->in_the_path){
		path->add_to_path(cell);
	}
	for(int i = 0 ; i < cell->m_nb_neighb ; i++)
	{
		if(!cell->m_neighb[i]->m_displayed2)
			update_path(cell->m_neighb[i],path);
		
	}
}

void create_path2(Maze *maze,Path *path){
	initialisation(maze->c_end);
	bool find=false;
	RO(maze->c_init,maze,find);
	update_path(maze->c_init,path);
}



///////////////////////////////////////////////////////////////////FONCTION ECRITURE FICHIER/////////////////////////////////////////////////////////////////////////////////////////////////////

void save_maze(const Maze& maze, const string& filename){
		//string filename = "file.txt";
		ofstream ofst(filename); // tentative d’ouverture (constructeur)
		if(!ofst.is_open())cout << "Erreur d’ouverture de " << filename << endl;
		
		else{
		
		ofst << "# Start:"<<endl; // écriture de variables dans le fluxstring 
		ofst<<"(";
		ofst << * maze.c_init;
		ofst<<")"<<endl;
		ofst << "# End:"<<endl; // écriture de variables dans le fluxstring 
		ofst<<"(";
		ofst << * maze.c_end;
		ofst<<")"<<endl;
		ofst << "# Cell:"<<endl; // écriture de variables dans le fluxstring 
		
		for(int i=0; i<maze.Content.size();i++ ){
			ofst<<"(";
			ofst<<maze.Content[i];
			ofst<<")";
			ofst<<maze.Content[i].m_nb_neighb;
			for(int k=0; k<maze.Content[i].m_nb_neighb; k++){
				ofst<<"(";
				ofst<<*maze.Content[i].m_neighb[k];
				ofst<<")";
			}
			ofst<<endl;

		}

		
		}
		ofst.close(); // fermeture du fichier
	}


Maze* read_maze(const string& filename){

	Maze *maze=new Maze();
	int x;
	int y;
	string str="";
	Cell *C=new Cell(0,0);
	char a;
	map<pair<int,int>,Cell*> m_cells;//codes-sources.commentcamarche.net/forum/affich-280469-lecture-fichier-mot-par-mot
	//m_cells[pair<int,int>(5,4)]=
	
	ifstream f(filename); // tentative d’ouverture (constructeur)
	if(!f.is_open()){
		cout << "Erreur d’ouverture de " << filename << endl;
	}
	else{
		while(!f.eof()){
			getline(f,str);
			if (str=="# Start:"){
				f.get(a);
				f.get(a);
				
				x=a-'0';
				f.get(a);
				f.get(a);
				y=a-'0';
				f.get(a);
				maze->c_init=new Cell(x,y);
				cout<<maze->c_init->m_y;
				
			}
			else if(str=="# End:"){
				f.get(a);
				f.get(a);
				
				x=a-'0';
				f.get(a);
				f.get(a);
				y=a-'0';
				f.get(a);
				maze->c_end=new Cell(x,y);
				cout<<maze->c_end->m_y;
				
				}
			else if(str=="# Cell:"){

			}
			
			else{
				


			}
			
			//f >> a >> b; // lecture de variables depuis le flux
			//string str;
			//getline(f, str); // lecture d’une ligne complète
		}
	}
	f.close(); // fermeture du fichier
	return(maze);
}
void traite_ligne(const string ligne, Cell *c)
{
	//cout << ligne << endl;
	char p;
	p = ligne[0];
	c->m_x = static_cast<int>(ligne[1])-48;
	//cout << "c.m_x = " << c.m_x +1 << " l1=" << ligne[1]+1 << endl;
	p = ligne[2];
	c->m_y = static_cast<int>(ligne[3])-48;
	p = ligne[4];
}

void traite_ligne_neigh(const string ligne, Cell *c, map<pair<int, int>,Cell*> &map_cells)
{
	//cout << ligne << endl;
	
	char p;
	p = ligne[0];
	c->m_x = static_cast<int>(ligne[1])-48;
	//cout << "c.m_x = " << c.m_x +1 << " l1=" << ligne[1]+1 << endl;
	p = ligne[2];
	c->m_y = static_cast<int>(ligne[3])-48;
	p = ligne[4];
	//c->m_nb_neighb = static_cast<int>(ligne[5])-48;
	int nb_vois = static_cast<int>(ligne[5])-48;
	for(int i=0; i<nb_vois; i++)
	{
		Cell *pcn = new Cell(0,0);
		pcn->m_x = static_cast<int>(ligne[7+5*i])-48;
		pcn->m_y = static_cast<int>(ligne[7+5*i+2])-48;
		pair<int, int> key(pcn->m_x, pcn->m_y);
		if (map_cells.find(key)==map_cells.end())
		{
			map_cells[key] = pcn;  //si la clé n'existe pas, on la rajoute
		}
		/*cout << "la cellule c" << endl;
		cout << c->m_nb_neighb << endl;
		cout << c->m_x << " et " << c->m_y << endl;
		cout << "adresse c = " << c << endl; 
		cout << "la cellule pcn" << endl;
		cout << pcn->m_nb_neighb << endl;
		cout << pcn->m_x << " et " << pcn->m_y << endl;
		cout << "adresse pcn = " << pcn << endl;*/
		else
		{
			pcn = map_cells[key];
		}
		c->add_neighb(pcn);
	}
	
}

Maze read_maze2(const string &file_name)
{
	Maze newMaze;
	ifstream ifst(file_name);
	if (!ifst.is_open())
	{
		cout << "erreur" << endl;
	}
	else
	{
		map<pair<int, int>, Cell*> m_cells;
		pair<int, int> keyStart;
		pair<int, int> keyEnd;
		int cpt = 0;
		string ligne;
		while(getline(ifst, ligne))
		{
			
			if (cpt == 1) //cellule de départ
			{
				Cell *pc = new Cell(0,0);
				//ifst >> c;
				traite_ligne(ligne, pc);
				keyStart.first = pc->m_x; 
				keyStart.second = pc->m_y;
				//m_cells[keyStart] = pc;
				//newMaze.cellStart = pc;
			} 
			if (cpt == 3) //cellule d'arrivée
			{
				Cell *pc = new Cell(0,0);
				//ifst >> c;
				traite_ligne(ligne, pc);
				keyEnd.first = pc->m_x; 
				keyEnd.second = pc->m_y;
				//m_cells[keyEnd] = pc;
				//newMaze.cellEnd = pc;
			}
			if (cpt>4)
			{
				Cell *pc = new Cell(0,0);
				traite_ligne_neigh(ligne, pc, m_cells);
				
				pair<int, int> key(pc->m_x, pc->m_y);
				if (m_cells.find(key)==m_cells.end())
				{
					m_cells[key] = pc;	//la clé n'existe pas
				}
			}
			cpt++;
		}
		newMaze.c_init = m_cells[keyStart];
		newMaze.c_end= m_cells[keyEnd];
	}
	ifst.close();
	return newMaze;
}


//////////////////////////////////////////////////////////////////////////////MAIN/////////////////////////////////////////////////////////////////////////////////////
int main(){
	vibes::beginDrawing();
	vibes::newFigure("Jam");
	vibes::setFigureProperties("Jam",vibesParams("x", 100, "y", 100, "width", 400, "height", 400));
	vibes::axisLimits(-0.5, 8.5, -0.5, 8.5);
	

	//Maze M=Maze(4,4);
	//M.create_maze();




// on ecrit dans un fichier 
	//save_maze(M,"txt_maze");
	Maze M=read_maze2("laby8x8.txt");


	//Maze M=read_maze2("txt_maze");

	// on affiche le Maze;
	M.display();
	Path path=Path(M.c_init);
	//chemin à suivre pour vérifier si tout marche.
	create_path2(&M,&path);
	
	
	draw_path(&path);
	
}




