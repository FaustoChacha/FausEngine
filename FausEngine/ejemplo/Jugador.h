#ifndef JUGADOR
#define JUGADOR

#include "../Motor/Headers/FsMaths.h"
#include"../Motor/Headers/FsCamera.h"
#include"../Motor/Headers/FsMesh.h"
#include"../Motor/Headers/FsCollider.h"
#include"../Motor/Headers/FsLight.h"

#include"../ejemplo/UserGame.h"

#include<cmath>

using namespace FausEngine;

class Jugador
{
public:
	Jugador();
	void ControlFPS(float, float);
	void ControlTPS(float, float);
	void Control2D(float, float);
	void CamaraFPS(float dt, float t);
	void CamaraTPS(float dt, float t);
	void OrbitarLuz(float offsetX, float offsetY, float dt, float t, float vel);
	void SetColorLuz(FsVector3 color);
	void SetNumVidas(int);
	int GetNumVidas();
	void Init(bool&);
	void Update(bool, float, float, bool);
	FsCollider GetCollider();
	~Jugador();

	std::unique_ptr<FsTransform> transform;
	//FsTransform* transform;

private:
	std::unique_ptr<UserGame> gameReference;
	//UserGame* gameReference;
	int numeroVidas;

	FsMesh mallaJugador;
	FsCollider collider;
	FsPointLight luzPuntual;

	FsMesh mallaLuzOrbital;
	FsVector3 coloresVida[3];
	
	FsVector3 posInicialPlayer;
	bool *colision, saltar=false;
	float timpoSalto, poderSalto=22;
	int contadorTeclaEspacio=0;
};



#endif // !JUGADOR

