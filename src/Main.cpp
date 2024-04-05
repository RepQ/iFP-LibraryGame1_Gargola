#include "NoEntiendo.hpp"
#include <Estados.h>
#include <stdio.h>

int		main()
{
	if (!NOE_Inicia())
		return (1);
	IniciaEstados();
	while (!NOE_ObtenTeclaPulsada(NOE_TECLA_X) && !EsEstadoFinal())
	{
		NOE_LimpiaPantalla(0, 0, 0);
		NOE_Actualiza();
		ActualizaEstado();
		DibujaEstado();
		NOE_MuestraPantalla();
	}

	NOE_ParaMusica();
	NOE_Finaliza();
	return (0);
}
