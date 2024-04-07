#include <Demonio.h>
#include <NoEntiendo.hpp>
#include <Muros.h>

Demonio	demonio;
const float	POS_INICIAL_DEMONIO_X = 100.0f;
const float	POS_INICIAL_DEMONIO_Y = 100.0f;
const float	GRAVEDAD_DEMONIO_Y = 0.0035f;
const float	IMPULSO_DEMONIO_Y = -1.2f;
const float	ANCHURA_DEMONIO = 150.0f;
const float	ALTURA_DEMONIO = 150.0f;

const int	ms_Sprite = 70;
const int	ms_Sound = 600;
float		counterSound = 0.f;
float		counterSprite = 0.f;
int		sprite = 0;
int		soundDemonDead = 0;

void	IniciaDemonio()
{
	demonio.posX = POS_INICIAL_DEMONIO_X;
	demonio.posY = POS_INICIAL_DEMONIO_Y;
	demonio.anchura = ANCHURA_DEMONIO;
	demonio.altura = ALTURA_DEMONIO;
	demonio.velocidadY = 0.f;
	demonio.vivo = 1;
}

void	ActualizaDemonio()
{
	demonio.posY += (demonio.velocidadY * NOE_ObtenTiempoDesdeActualizacion());
	demonio.velocidadY += (GRAVEDAD_DEMONIO_Y * NOE_ObtenTiempoDesdeActualizacion());
	
	counterSound += NOE_ObtenTiempoDesdeActualizacion();
	
	if (counterSound >= ms_Sound && demonio.vivo)
	{
		counterSound = 0.f;
		NOE_ReproduceSonido(2, 10, 100);
	}

	if (NOE_ObtenTeclaAbajo(NOE_TECLA_ESPACIO))
		demonio.velocidadY += IMPULSO_DEMONIO_Y;
	
	if (demonio.posY < 0)
	{
		demonio.posY = 0;
		demonio.velocidadY = 0.f;
	}
	else if (demonio.posY > (NOE_ObtenAltoPantalla() - demonio.altura))
	{
		demonio.posY = (NOE_ObtenAltoPantalla() - demonio.altura);
		demonio.velocidadY = 0.f;
	}
	
	if (ChocaConMuro(demonio.posX, demonio.posY, demonio.anchura, demonio.altura))
	{
		NOE_ReproduceSonido(0, 100, 100);
		demonio.vivo = 0;
	}
	else
		demonio.vivo = 1;
}

void	DibujaDemonio()
{
	counterSprite += NOE_ObtenTiempoDesdeActualizacion();
	if (counterSprite >= ms_Sprite)
	{
		counterSprite = 0.f;
		sprite++;
	}
	sprite %= 7;
	NOE_DibujaSprite(sprite, demonio.posX, demonio.posY, demonio.anchura, demonio.altura, false, false);
}

int	EstaVivoDemonio()
{
	if (!demonio.vivo)
		return (0);
	return (1);
}
