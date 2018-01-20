#include <iostream>
#include "vektor.h"
#include <cmath>
#include <random>

using namespace std;
default_random_engine generator;
normal_distribution<double> distribution(0, 1);

//###__Fundomental_Postoyannie__###################################################################################################################################################################################################################################################
double PI=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989;

//#################################################################################################################################################################################################################################################################################

class chastica{public:
//###__Inicializaciya__############################################################################################################################################################################################################################################################		
	double GraniciVselennoy=7.3e-8;
	double Vyazkost=2.15e-3; // Paskal*sekunda
	double KT=273.16*1.38e-23; // 1.38e-23
	double U0=4e-7*PI; // Genri/metr
	double TimE=1.0e-10; // sekund

	double Radius=6.66e-9; // metrov
	double Radius3=Radius*Radius*Radius;

	double Plotnost=5000.0; // kilogramm/metr^3
	double Obyom=4.0/3.0*PI*Radius3; // metrov^3
	double Massa=Obyom*Plotnost; // kilogramm
	double MagMom=4.78e5*Obyom; // Amper*metr^2 ((namagnichenost' nasisheniya=4.78*10^5 Amper/metr))

	vektor pos;
	vektor forse;

	vektor axis;
	vektor moment;

	chastica(double _x,double _y,double _z, double _al,double _be,double _ga){
		pos[0]=_x;
		pos[1]=_y;
		pos[2]=_z;
		forse[0]=0;
		forse[1]=0;
		forse[2]=0;

		axis[0]=_al;
		axis[1]=_be;
		axis[2]=_ga;
		moment[0]=0;
		moment[1]=0;
		moment[2]=0;
	};
	chastica(){
		pos[0]=fRand(-1,1);
		pos[1]=fRand(-1,1);
		pos[2]=fRand(-1,1);
		forse[0]=0;
		forse[1]=0;
		forse[2]=0;

		axis[0]=fRand(-1,1);
		axis[1]=fRand(-1,1);
		axis[2]=fRand(-1,1);
		axis[0]=fRand(-1,1);
		axis[1]=fRand(-1,1);
		axis[2]=fRand(-1,1);
		moment[0]=0;
		moment[1]=0;
		moment[2]=0;

		double magP=pos.mag();
		double magA=axis.mag();
		for(int i=0; i<3; i++){
			pos[i]=pos[i]/magP;
			axis[i]=axis[i]/magA*MagMom;
		}
	};
//#################################################################################################################################################################################################################################################################################	

//###__Algoritm_bezInercionnoy_dinamiki__##########################################################################################################################################################################################################################################	
	void Kinematika(){ // https://www.desmos.com/calculator/bhjmf8p0pf
		pos=pos+forse*(TimE/(6.0*PI*Radius*Vyazkost))+StahostSmeshLin();
		

		vektor DeltaAlfa=moment*(TimE/(8.0*PI*pow(Radius, 3)*Vyazkost))+StahostSmeshVrash();
		axis=axis.rotate(DeltaAlfa, DeltaAlfa.mag());

		PorvrkaGrani();
	}
//#################################################################################################################################################################################################################################################################################	

//###__Storonnie_funkcii__#########################################################################################################################################################################################################################################################	
	double fRand(double fMin, double fMax){
		double f=(double)rand()/RAND_MAX;
		return fMin+f*(fMax-fMin);
	}
	double Gauss(double matOjit, double disp){
		return distribution(generator);
	}
	void PorvrkaGrani(){
		if (pos[0]>GraniciVselennoy){pos=vektor(pos[0]-2*GraniciVselennoy, pos[1], pos[2]);}
		else if (pos[0]<-GraniciVselennoy ){pos=vektor(pos[0]+2*GraniciVselennoy, pos[1], pos[2]);}
		
		if (pos[1]>GraniciVselennoy) {pos=vektor(pos[0], pos[1]-2*GraniciVselennoy, pos[2]);}
		else if (pos[1]<-GraniciVselennoy) {pos=vektor(pos[0], pos[1]+2*GraniciVselennoy, pos[2]);}
		
		if (pos[2]>GraniciVselennoy) {pos=vektor(pos[0], pos[1], pos[2]-2*GraniciVselennoy);}
		else if (pos[2]<-GraniciVselennoy) {pos=vektor(pos[0], pos[1], pos[2]+2*GraniciVselennoy);}
	}
	vektor StahostSmeshLin(){
		vektor pom(1);
		// pom.show();
		double difuz=KT/(6.0*PI*Radius*Vyazkost);
		// cout<<difuz<<" ";
		difuz=(pow(2*difuz*TimE, .5)*Gauss(0, 1));
		pom=pom*difuz;
		// pom.show();
		// cout<<" "<<difuz<<endl;

		return pom;
	}
	vektor StahostSmeshVrash(){
		vektor pom;
		double difuz=KT/(8.0*PI*pow(Radius, 3)*Vyazkost);
		pom=pom*(pow(2*difuz*TimE, .5)*Gauss(0, 1));

		return pom;
	}
//#################################################################################################################################################################################################################################################################################
};