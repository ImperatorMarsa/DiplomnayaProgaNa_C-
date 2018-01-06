#include <cmath>
#include <iostream>
#include <ctime>
#include <fstream>
#include "chastica.h"

using namespace std;

//###__Fundomental_Postoyannie__###################################################################################################################################################################################################################################################
double pi=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989;
double Time=1.0e-10; // sekund
double kT=273.16*1.38e-23; // 1.38e-23
double u0=4.0e-7*pi; // Genri/metr

double graniciVselennoy=7.3e-8;

double MassivDlyaPereschetaPeriudGranic[]={0.0,0.0,0.0, 0.0,0.0,1.0, 0.0,1.0,0.0, 0.0,1.0,1.0, 1.0,0.0,0.0, 1.0,0.0,1.0, 1.0,1.0,0.0, 1.0,1.0,1.0};
//#################################################################################################################################################################################################################################################################################

//###__Sili_Deystvuyushie_V_Sisteme__##############################################################################################################################################################################################################################################
vektor VneshPole(chastica _1){
	vektor M(0,0,0);
	double H=73E3; // Amper/metr
	vektor B(H*u0,0,0);
	M(_1.axis, B);

	return M;
}
vektor SteerOttalk(chastica _1, chastica _2){ // https://www.desmos.com/calculator/ddxmffkqrj
	vektor F(0,0,0);
	vektor pom=_1.pos-_2.pos;
	double dist=pom.mag();
	// Kakieto koefficienti #
	double A=31.3; // #######
	double B=73.0; // #######
	// ######################
	double M=_1.axis.mag(); // Magnitniy moment chastici
	double q=2e-9; // Dlina volosni v metrah
	double a=2.0*(_1.Radius+q); // Diametr chastici s volosney
	if (dist<_1.Radius*2.0){
		double buf=A*3*u0*(M*M)/(4*pi*(a*a*a*a))*exp(-B*(dist/a-1));
		F=pom*buf;
	}

	return F;
}
vektor MehSilaDipolya(chastica _1, chastica _2){ // https://en.wikipedia.org/wiki/Magnetic_dipole
	vektor F(0,0,0);
	vektor r=_1.pos-_2.pos;
	if (abs(r[0])-graniciVselennoy<0 && abs(r[1])-graniciVselennoy<0 && abs(r[2])-graniciVselennoy<0){
		F=(_2.axis*(_1.axis*r)+_1.axis*(_2.axis*r)+r*(_1.axis*_2.axis)-r*(5*(_1.axis*r)*(_2.axis*r)/pow(r.mag(), 2)))*(3*u0/(4*pi*pow(r.mag(), 5)));
	}

	return F;
}
vektor MehMomDipolya(chastica _1, chastica _2){ // https://en.wikipedia.org/wiki/Magnetic_dipole
	vektor M(0,0,0);
	vektor r=_1.pos-_2.pos;
	if (abs(r[0])-graniciVselennoy<0 && abs(r[1])-graniciVselennoy<0 && abs(r[2])-graniciVselennoy<0){
		vektor B=(r*((_2.axis*r)*3/pow(r.mag(), 5))-_2.axis*(1/pow(r.mag(), 3)))*(u0/(4*pi));
		M(_1.axis, B);
	} 

	return M;
}
//#################################################################################################################################################################################################################################################################################

//###__Storonnie_Funkcii__#########################################################################################################################################################################################################################################################
vektor NewCoord(vektor _1, int i){
	vektor a(copysign(1, -_1[0])*(2*graniciVselennoy*MassivDlyaPereschetaPeriudGranic[i*3+0]-abs(_1[0])), copysign(1, -_1[1])*(2*graniciVselennoy*MassivDlyaPereschetaPeriudGranic[i*3+1]-abs(_1[1])), copysign(1, -_1[2])*(2*graniciVselennoy*MassivDlyaPereschetaPeriudGranic[i*3+2]-abs(_1[2])));
	return a;
}
//#################################################################################################################################################################################################################################################################################

int main(int argc, char** argv) {
	chastica Chastici[64];
	int chisloChastic=sizeof(Chastici)/sizeof(Chastici[0]);
	graniciVselennoy=Chastici[0].Radius/pow(0.1*3/(4*pi*chisloChastic), 1.0/3.0);

	ofstream fout("output.txt");
	double chisloIteraciy=1E5;
	fout<<graniciVselennoy<<" "<<chisloIteraciy<<"\n";
	fout.close();
//###__Raspologayu_chastici_v_prostranstve__######################################################################################################################################################################################################################################
	double chisloChasticNaOs=pow(chisloChastic, 1.0/3.0)/2;
	double shtuk=graniciVselennoy/chisloChasticNaOs;
	int schetchik=0;
	cout<<shtuk<<" "<<chisloChasticNaOs<<endl;
	for(double i=-chisloChasticNaOs; i<chisloChasticNaOs; i++){
		for(double j=-chisloChasticNaOs; j<chisloChasticNaOs; j++){
			for(double k=-chisloChasticNaOs; k<chisloChasticNaOs; k++){
				Chastici[schetchik].GraniciVselennoy=graniciVselennoy;
				Chastici[schetchik].pos=vektor(shtuk*i+shtuk*0.5, shtuk*j+shtuk*0.5, shtuk*k+shtuk*0.5);
				schetchik++;
			}
		}
	}
//#################################################################################################################################################################################################################################################################################	

//###__Osnovnoy_algoritm_modelirovaniya__##########################################################################################################################################################################################################################################
	for(int AAA=0; AAA<chisloIteraciy; AAA++){
		int kakChastoPropuskat=10;

		time_t seconds=time(NULL);
		ofstream fout("output.txt", ios_base::app);
		if(AAA%100==0){cout<<AAA<<" vot shas mi zdes\n";}
		for(int I=0; I<chisloChastic; I++){
			vektor forse(0,0,0);
			vektor moment(0,0,0);

			chastica odna=Chastici[I];
			moment=moment+VneshPole(odna);
			for(int J=0; J<chisloChastic; J++){
				if(I==J) {continue;}
				for(int A=0; A<8; A++){
					chastica drugaya=Chastici[J];
					drugaya.pos=NewCoord(drugaya.pos, A);
					forse=forse+SteerOttalk(odna, drugaya)+MehSilaDipolya(odna, drugaya);
					moment=moment+MehMomDipolya(odna, drugaya);
				}
			}
			odna.forse=forse;
			odna.moment=moment;
			fout<<odna.pos[0]<<" "<<odna.pos[1]<<" "<<odna.pos[2]<<" | "<<odna.axis[0]<<" "<<odna.axis[1]<<" "<<odna.axis[2]<<" $ ";
			odna.Kinematika();
			Chastici[I]=odna;
		}
		fout<<"\n";
		fout.close();
		// cout<<time(NULL)-seconds<<endl;
	}
//#################################################################################################################################################################################################################################################################################	
	// system("pause");
	return 0;
};