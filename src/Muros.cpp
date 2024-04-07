#include <NoEntiendo.hpp>
#include <Muros.h>
#include <stdio.h>

const int	MAX_MUROS = 10;
const float	SEPARACION_MUROS_X = 500;
const float	MIN_ALTURA_HUECO_MURO = 200;
const float	MAX_ALTURA_HUECO_MURO = 500;
const float	VELOCIDAD_MUROS_X = 0.5f;

Muro muros[MAX_MUROS];

void	IniciaMuros()
{
	Muro	*ptr;
	int	i;
	float	pos_x;

	pos_x = NOE_ObtenAnchoPantalla();
	i = 0;
	ptr = muros;
	while (i++ < MAX_MUROS)
	{
		float	tamanioHueco;
		tamanioHueco = NOE_ObtenNumeroAleatorio(MIN_ALTURA_HUECO_MURO, MAX_ALTURA_HUECO_MURO);
		ptr->posX = pos_x;
		ptr->anchura = 50;
		ptr->alturaSuperior = NOE_ObtenNumeroAleatorio(100, NOE_ObtenAltoPantalla() - 100 - tamanioHueco);
		ptr->alturaInferior = ptr->alturaSuperior + tamanioHueco; 
		pos_x += ptr->anchura + SEPARACION_MUROS_X;
		ptr++;
	}
}

void	ActualizaMuros()
{
	Muro	*ptr;
	int	i;
	int	j;
	float	max_posx;

	i = 0;
	max_posx = 0;
	ptr = muros;
	while (i++ < MAX_MUROS)
	{
		float	tamanioHueco;
		tamanioHueco = NOE_ObtenNumeroAleatorio(MIN_ALTURA_HUECO_MURO, MAX_ALTURA_HUECO_MURO);
		ptr->posX = (ptr->posX) - (VELOCIDAD_MUROS_X * NOE_ObtenTiempoDesdeActualizacion());
		if ((ptr->posX + ptr->anchura) < 0)
		{
			j = -1;
			while (++j < MAX_MUROS)
				if (muros[j].posX > max_posx)
					max_posx = muros[j].posX;
			ptr->posX = max_posx + ptr->anchura + SEPARACION_MUROS_X;
			ptr->alturaSuperior = NOE_ObtenNumeroAleatorio(100, NOE_ObtenAltoPantalla() - 100 - tamanioHueco);
			ptr->alturaInferior = ptr->alturaSuperior + tamanioHueco; 
		}
		ptr++;
	}
	
}

int	ChocaConMuro(float posX, float posY, float ancho, float alto)
{
	Muro	*ptr;
	int	i;
	int	colision;

	i = 0;
	ptr = muros;
	colision = 0;
	while (i++ < MAX_MUROS)
	{
		if (((posX + ancho) >= ptr->posX + 10 && (posX + ancho) <= (ptr->posX + ptr->anchura)) ||((posX >= ptr->posX) && (posX <= ptr->posX + ptr->anchura - 20))
			|| ((posX <= ptr->posX) && ((posX + ancho) >= ((ptr->posX + ptr->anchura)))))
		{
			if ((posY <= ptr->alturaSuperior - 85) || ((posY + alto) >= (ptr->alturaInferior + 50)))
				return (1);
			else
				colision = 0;
		}
		else
			colision = 0;
		ptr++;
	}
	return (colision);
}

float	ObtenVelocidadMuros()
{
	return (VELOCIDAD_MUROS_X);
}

void	DibujaMuros()
{
	Muro	*ptr;
	int	i;
	float	alturaS;
	float	alturaI;

	i = 0;
	ptr = muros;
	while (i++ < MAX_MUROS)
	{
		alturaS = ptr->alturaSuperior - 62;
		alturaI = ptr->alturaInferior;
		NOE_DibujaSprite(
				11,
				ptr->posX,
				alturaS,
				ptr->anchura,
				-1,
				0,
				0
				);

		NOE_DibujaSprite(
				10, 
				ptr->posX, 
				ptr->alturaInferior, 
				ptr->anchura, 
				-1, 
				0, 
				0
				);
		while (alturaS >= -50)
		{
			alturaS -= 58;
			NOE_DibujaSprite(
					9,
					ptr->posX,
					alturaS,
					ptr->anchura,
					-1,
					0,
					0);
		}
		while (alturaI <= NOE_ObtenAltoPantalla())
		{
			alturaI += 58;
			NOE_DibujaSprite(
					9,
					ptr->posX,
					alturaI,
					ptr->anchura,
					-1,
					0,
					0);
		}
		ptr++;
	}
}
