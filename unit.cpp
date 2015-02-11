#include "unit.h"

using namespace std;


Unit::Unit(){
	r=0;
	c=0;
	hp=300;
	dir= up;
	rank= infantry;
	dead= false;
	tla= "xxx";
	}// default constructor.  set r,c to 0, hp to INFANTRYHP, dir to up, rank to infantry, dead to false, tla to "xxx"

Unit::Unit(int ir,int ic,int ihp,Dir idir,Rank irank,
	     bool idead, string itla){
			r=ir;
			if (r < 0 || r> ROWS-1) exit(3);
			c=ic;
			if (c < 0 || c> COLS-1) exit(3);
			hp=ihp;
			if (hp<0) exit(3);
			dir=idir;
			if (dir != up || dir!=dn || dir!=lt || dir!=rt) exit(3);
			rank=irank;
			if (rank!=crown || rank!= knight || rank!= archer || rank!= infantry) exit(3);
			dead=idead;
			if (hp == 0) dead = true;
			tla=itla;

	}//check for errors, exit if any found

int Unit::getR(){
		return r;
	}
int Unit::getC(){
		return c;
	}
int Unit::getHp(){
		return hp;
	}
Dir Unit::getDir(){
		return dir;
	}
Rank Unit::getRank(){
		return rank;
	}
bool Unit::getDead(){
		return dead;
	}
string Unit::getTla(){
		return tla;
	}
void Unit::Turn(Dir newDir){
		switch(newDir){
			case up: dir=up; break;	
			case dn: dir=dn; break;	
			case lt: dir=lt; break;	
			case rt: dir=rt; break;	
			case none: dir=none; break;	
}   
}
void Unit::Move(int dist){
	switch(dir){
		case up: r-=dist; break;
		case dn: r+=dist; break;
		case lt: c-=dist; break;
		case rt: c+=dist; break;
		case none: break;
}   
}
int Unit::Attack(){
	int hits = 0;
	getHp();
	
	int numrolls;
	numrolls = getHp(); 
	for (int i = 0; i <numrolls; i++){
		int roll = rand()%6+1;
	if (getRank() == archer){
	if (roll == 1 || roll ==2){
		hits += 1;

	}
}
	else{
	if(roll == 3 || roll == 4 || roll ==5){
		hits += 1;
}
}
}   
	return hits;
}
void Unit::Suffer(int hits){
	if (getRank() == infantry || getRank()== archer){ 
		hp-=hits;
		if(hp<=0){
		hp=0;
		dead=true;
}
}
	else{
		if(getRank() == knight || getRank() == crown){
			hp= hits/2;
			if(hp<=0){
				hp=0;
				dead = true;
			}
		}
	}
}   
void Unit::Place(int minR,int maxR, int minC,int maxC, SitRep sitrep){ 
		for(int i = minR; i >=minR; i++){
			for(int j = minC; j <= minC; j++){
				if(sitrep.thing[i][j].what == space){
				r = i;
				c = j;
					sitrep.thing[i][j].what = unit;
				}
					
			}
		}
}												 
Action Unit::Recommendation(SitRep s){
		
Action a;
int tr,tc;
tr=r;
tc=c;
switch(dir){
case up:tr--; break;
case dn:tr++; break;
case lt:tc--; break;
case rt:tc++; break;
case none: exit(1); break;
}
if(tr>=0 && tr<ROWS && tc<COLS){
	if(s.thing[tr][tc].what==unit){
		if(s.thing[tr][tc].tla!=tla){
			a.action=attack;
			a.ar=tr;
			a.ac=tc;
			return a;
} 
		else if (s.nearestEnemy.dirFor==dir){
					  a.action= fwd;
					  a.maxDist=1;
					  return a;
				  }
		
return a;
}
}
	a.action=turn;
	a.dir=s.nearestEnemy.dirFor;
	return a;
}
