#include <string>
#include <omp.h>
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
double MagnitnayaPronichObolochki=1;

double graniciVselennoy=42.0e-8;
double alfa=2.5/graniciVselennoy;

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
vektor SteerOttalk(chastica _1, chastica _2, vektor n){ // https://www.desmos.com/calculator/ddxmffkqrj
	vektor F(0,0,0);
	vektor r=_1.pos-_2.pos+n;
	double dist=r.mag();
	// Kakieto koefficienti #
	double A=31.3; // #######
	double B=73.0; // #######
	// ######################
	double M=_1.axis.mag(); // Magnitniy moment chastici
	double q=2e-9; // Dlina volosni v metrah
	double a=2.0*(_1.Radius+q); // Diametr chastici s volosney
	if(dist<_1.Radius*2.0) {F=r*(A*3*u0*(M*M)/(4*pi*(a*a*a*a))*exp(-B*(dist/a-1)));}

	return F;
}
vektor MehSilaDipolya(chastica _1, chastica _2, vektor n){ // https://en.wikipedia.org/wiki/Magnetic_dipole
	vektor F(0,0,0);
	vektor r=_1.pos-_2.pos+n;
	// if (abs(r[0])-graniciVselennoy<0 && abs(r[1])-graniciVselennoy<0 && abs(r[2])-graniciVselennoy<0){
	F=(_2.axis*(_1.axis*r)+_1.axis*(_2.axis*r)+r*(_1.axis*_2.axis)-r*(5*(_1.axis*r)*(_2.axis*r)/pow(r.mag(), 2)))*(3*u0/(4*pi*pow(r.mag(), 5)));
	// }

	return F;
}
vektor MehMomDipolya(chastica _1, chastica _2, vektor n){ // https://en.wikipedia.org/wiki/Magnetic_dipole
	vektor M(0,0,0);
	vektor r=_1.pos-_2.pos+n;
	// if (abs(r[0])-graniciVselennoy<0 && abs(r[1])-graniciVselennoy<0 && abs(r[2])-graniciVselennoy<0){
	vektor B=(r*((_2.axis*r)*3/pow(r.mag(), 5))-_2.axis*(1/pow(r.mag(), 3)))*(u0/(4*pi));
	M(_1.axis, B);
	// } 

	return M;
}
//#################################################################################################################################################################################################################################################################################

//###__Storonnie_Funkcii__#########################################################################################################################################################################################################################################################
vektor NewCoord(vektor _1, int i) {
	vektor a(copysign(1, -_1[0])*(2*graniciVselennoy*MassivDlyaPereschetaPeriudGranic[i*3+0]-abs(_1[0])), copysign(1, -_1[1])*(2*graniciVselennoy*MassivDlyaPereschetaPeriudGranic[i*3+1]-abs(_1[1])), copysign(1, -_1[2])*(2*graniciVselennoy*MassivDlyaPereschetaPeriudGranic[i*3+2]-abs(_1[2])));
	return a;
}
double fRand(double fMin, double fMax) {
	double f=(double)rand()/RAND_MAX;
	return fMin+f*(fMax-fMin);
}
double sqr(double a) {return pow(a, 2);}
//#################################################################################################################################################################################################################################################################################

int main(int argc, char** argv) {
	chastica Chastici[42];
	int chisloChastic=sizeof(Chastici)/sizeof(Chastici[0]);
	graniciVselennoy=Chastici[0].Radius/pow(0.1*3/(4*pi*chisloChastic), 1.0/3.0);
	alfa=2.5/graniciVselennoy;

	system("rmdir /s /q D:\\pomoina");
	system("mkdir D:\\pomoina");
	ofstream titulOut("D:\\pomoina\\Boobles.txt");
	double chisloIteraciy=2E5;
	titulOut<<graniciVselennoy<<" "<<chisloIteraciy<<"\n";
	titulOut.close();
//###__Raspologayu_chastici_v_prostranstve__######################################################################################################################################################################################################################################
	// #pragma omp parallel for 

	// double kord=graniciVselennoy/4;
	// Chastici[0].GraniciVselennoy=graniciVselennoy;
	// Chastici[0].TimE=Time;
	// Chastici[0].pos=vektor(kord, 0, 0);

	// Chastici[1].GraniciVselennoy=graniciVselennoy;
	// Chastici[1].TimE=Time;
	// Chastici[1].pos=vektor(-kord, 0, 0);

	for(int i=0; i<chisloChastic; i++) {
		Chastici[i].GraniciVselennoy=graniciVselennoy;
		Chastici[i].TimE=Time;
		Chastici[i].pos=vektor(fRand(-(graniciVselennoy-1E-9), graniciVselennoy-1E-9), fRand(-(graniciVselennoy-1E-9), graniciVselennoy-1E-9), fRand(-(graniciVselennoy-1E-9), graniciVselennoy-1E-9));
		int j=i;
		while (j>0) {
			j=i;
			for(int k=0; k<i; k++) {
				double r=vektor(Chastici[i].pos-Chastici[k].pos).mag();
				if(r<=Chastici[i].Radius*3) {
					Chastici[i].pos=vektor(fRand(-(graniciVselennoy-1E-9), graniciVselennoy-1E-9), fRand(-(graniciVselennoy-1E-9), graniciVselennoy-1E-9), fRand(-(graniciVselennoy-1E-9), graniciVselennoy-1E-9));
				} else {j--;}
			}
		}
	}
//#################################################################################################################################################################################################################################################################################	
	// ofstream fout("output.txt", ios_base::app);
//###__Osnovnoy_algoritm_modelirovaniya__##########################################################################################################################################################################################################################################
	for(int AAA=0; AAA<chisloIteraciy; AAA++) {
		int kakChastoPropuskat=1;
		time_t seconds=time(NULL);

		if(AAA%100==0) {cout<<AAA<<" vot shas mi zdes\n";}

		#pragma omp parallel for 
			for(int I=0; I<chisloChastic; I++) {
				string adress="D:\\pomoina\\output"+to_string(I)+".txt";
				ofstream fout(adress, ios_base::app);

				vektor forse(0,0,0);
				vektor moment(0,0,0);

				chastica odna=Chastici[I];
				moment=moment+VneshPole(odna);
				for(int J=0; J<chisloChastic; J++) {
					//+++++ Realizuyu Zdes Summi Evalda ++++++++++++++++++++++++++++++++++++
					chastica drugaya=Chastici[J];
					int PredelSumm=3;

					for(int X=-PredelSumm; X<PredelSumm+1; X++) {
						int pom1=(int)sqrt(sqr(PredelSumm)-sqr(X));
						for(int Y=-pom1; Y<pom1+1; Y++) {
							int pom2=(int)sqrt(sqr(PredelSumm)-sqr(X)-sqr(Y));
							for(int Z=-pom2; Z<pom2+1; Z++) {
								vektor n(X*graniciVselennoy*2, Y*graniciVselennoy*2, Z*graniciVselennoy*2);
								double magN=n.mag();

								if(magN!=0 || J!=I) {
									forse=forse+MehSilaDipolya(odna, drugaya, n)+SteerOttalk(odna, drugaya, n);
									moment=moment+MehMomDipolya(odna, drugaya, n);
								}
							}
						}
					}
					//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				}
				odna.forse=forse;
				odna.moment=moment;

				// if(AAA%500==0) {
				// 	cout<<"\n"<<forse.mag()<<" "<<moment.mag()<<"\t"<<AAA<<"\n\n";
				// }

				// if(AAA%kakChastoPropuskat==0) {}
				fout<<odna.pos[0]<<" "<<odna.pos[1]<<" "<<odna.pos[2]<<" | "<<odna.axis[0]<<" "<<odna.axis[1]<<" "<<odna.axis[2]<<"\n";
				fout.close();
				odna.Kinematika();
				Chastici[I]=odna;

			}
		// cout<<time(NULL)-seconds<<endl;
	}
//#################################################################################################################################################################################################################################################################################	
	system("shutdown now");
	// system("pause");
	return 0;
};