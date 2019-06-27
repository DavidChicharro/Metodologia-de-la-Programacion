#ifndef MONT
#define MONT

using namespace std;

class SkyLine{
private:
	double *abscisas; 		// abscisas[i] > abscisas[i-1]
	double *alturas;		// alturas[i]>=0 && alturas[n-1] == 0
	int n;					// tamaño de los vectores anteriores

	void Crea ();
	void Destruye ();
	void Redimensiona ();

public:
	SkyLine ();
	~SkyLine ();
	void SetEdificios (double abscisa1, double abscisa2, double altura);
	SkyLine & operator=(const SkyLine &otro_skyline);
	SkyLine operator+(const SkyLine &skyline_suma);

	friend ostream& operator<<(ostream &flujo, const SkyLine &skyline);
	friend istream& operator>>(istream &flujo, const SkyLine &skyline);
};

ostream& operator<<(ostream &flujo, const SkyLine &skyline);
istream& operator>>(istream &flujo, SkyLine &skyline);

int Salvar (char *nombre_fich, const SkyLine &skyline);

#endif