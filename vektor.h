#include <iostream>
#include <cmath>

using namespace std;

//Класс для реализации векторов:
class vektor{ // http://studlab.com/news/skaljarnoe_i_vektornoe_proizvedenie_vektorov_v_s/2013-07-28-982
	double coords[3]; //Координаты вектора – закрытый массив-член класса:
	public:
	double &operator[](int i){ //Перегрузка оператора [] для индексации объектов:
		int k=i%3;
		return coords[k];
	};
	vektor operator()(double x,double y,double z){ //Перегрузка оператора () для присваивания координатам значений:
		coords[0]=x;
		coords[1]=y;
		coords[2]=z;
		return *this;
	};
	vektor operator()(vektor a,vektor b){ //Перегрузка оператора () для вычисления векторного произведения:
		for(int i=0; i < 3; i++){
			coords[i]=a[i+1]*b[i+2]-a[i+2]*b[i+1];
		};
		return *this;
	};
	double operator*(vektor obj){ //Перегрузка оператора * для вычисления скалярного произведения:
		double res=0;
		for(int i=0; i < 3; i++) {
			res+=coords[i]*obj[i];
		};
		return res;
	};
	vektor operator+(vektor obj){ //Перегрузка оператора + для вычисления суммы векторов:
		vektor vek(0,0,0);
		for(int i=0; i < 3; i++) {
			vek[i]=coords[i]+obj[i];
		};
		return vek;
	};
	vektor operator-(vektor obj){ //Перегрузка оператора - для вычисления разности векторов:
		vektor vek(0,0,0);
		for(int i=0; i < 3; i++) {
			vek[i]=coords[i]-obj[i];
		};
		return vek;
	};
	vektor operator*(double obj){ // Перегрузка оператора * для вычисления произвидения скаляра на вектор:
		vektor vek(0,0,0);
		for(int i=0; i < 3; i++) {
			vek[i]=coords[i]*obj;
		};
		return vek;
	};
	vektor rotate(vektor axs, double angl){ // Функция поворота вектора на некий угол вокруг определённого направления
		double mat[9];

		double mag=axs.mag();
		double a=cos(angl/2.0);
		double b=-(axs[0]/mag)*sin(angl/2.0);
		double c=-(axs[1]/mag)*sin(angl/2.0);
		double d=-(axs[2]/mag)*sin(angl/2.0);

		mat[0]=a*a+b*b-c*c-d*d;
		mat[1]=2*(b*c-a*d);
		mat[2]=2*(b*d+a*c);

		mat[3*1+0]=2*(b*c+a*d);
		mat[3*1+1]=a*a+c*c-b*b-d*d;
		mat[3*1+2]=2*(c*d-a*b);

		mat[3*2+0]=2*(b*d-a*c);
		mat[3*2+1]=2*(c*d+a*b);
		mat[3*2+2]=a*a+d*d-b*b-c*c;

		vektor pom(0,0,0);
		for (int i=0; i <3; i++){
			pom[i]=mat[3*0+i]*coords[0]+mat[3*1+i]*coords[1]+mat[3*2+i]*coords[2];
		}
		return pom;
	}
	double mag(){
		double mag=sqrt(coords[0]*coords[0]+coords[1]*coords[1]+coords[2]*coords[2]);
		return mag;
	};
	double fRand(double fMin, double fMax){
		double f=(double)rand()/RAND_MAX;
		return fMin+f*(fMax-fMin);
	}
	vektor(double x,double y,double z){ //Конструктор с тремя аргументами:
		coords[0]=x;
		coords[1]=y;
		coords[2]=z;
	};
	void show(){ //Метод для отображения координат вектора:
		cout << "(" << coords[0] << ", " << coords[1] << ", " << coords[2]<<")";
	};
	//Конструктор без аргументов:
	vektor(){
		for(int i=0; i<3; i++){
			coords[i]=0;
		}
	};
	vektor(double S){
		coords[0]=fRand(-S,S);
		coords[1]=fRand(-S,S);
		coords[2]=fRand(-S,S);
		double magP=sqrt(pow(coords[0], 2)+pow(coords[1], 2)+pow(coords[2], 2));
		for(int i=0; i<3; i++){
			coords[i]=coords[i]/magP;
		}
	};
};