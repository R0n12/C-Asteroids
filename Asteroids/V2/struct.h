 
struct Universe;
struct Asteroids;

struct Universe
{
	int length;
	int numAst;
	int lastID;
	double ET;
	struct Asteroids *ref_ast;
};

struct Asteroids
{	
	int ID;
	int size;
	int steps;
	double X;
	double Y;
	double VX;
	double VY;
	struct Universe *ref_uni;
};
