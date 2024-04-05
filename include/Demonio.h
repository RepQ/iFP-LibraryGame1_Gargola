/************************************************
 * 		DEMONIO . H			*
 ************************************************/
#include <NoEntiendo.hpp>

typedef struct
{
	float	posX;
	float	posY;
	float	anchura;
	float	altura;
	float	velocidadY;
	int	vivo;
} Demonio;

void	IniciaDemonio();
void	ActualizaDemonio();
int	EstaVivoDemonio();
void	DibujaDemonio();
