#include <NoEntiendo.hpp>
#include <Fondo.h>


const int	MAX_ELEMENTOS_FONDO = 8;
const int	NUM_TIPOS_ELEMENTO_FONDO = 2;
const int	SEPARACION_NUBES = 150;
const int	SEPARACION_CASTILLO = 50;
const int	ANCHO_NUBES = 500;
const int	ANCHO_CASTILLO = 1000;
const float	VELOCIDAD_NUBES = 0.08f;
const float	VELOCIDAD_CASTILLO = 0.02f;

enum fondo
{
	NUBES = 1,
	CASTILLO
};

ElementoFondo	elementosFondo[MAX_ELEMENTOS_FONDO];

void	IniciaFondo()
{
	ElementoFondo	*ptr;
	int	i;
	int	desfaseX_castillo;
	int	desfaseX_nubes;

	i = 0;
	ptr = elementosFondo;
	desfaseX_castillo = NOE_ObtenAnchoPantalla() / 2;
	desfaseX_nubes = NOE_ObtenNumeroAleatorio(0, NOE_ObtenAnchoPantalla());
	while (i++ < MAX_ELEMENTOS_FONDO)
	{
		ptr->tipo = NOE_ObtenNumeroAleatorio(1, NUM_TIPOS_ELEMENTO_FONDO);
		if (ptr->tipo == NUBES)
		{
			ptr->posX = desfaseX_nubes;
			ptr->posY = NOE_ObtenNumeroAleatorio(0, NOE_ObtenAltoPantalla() - 300);
			desfaseX_nubes += ANCHO_NUBES + SEPARACION_NUBES;
		}
		else if (ptr->tipo == CASTILLO)
		{
			ptr->posX = desfaseX_castillo;
			ptr->posY = NOE_ObtenNumeroAleatorio(NOE_ObtenAltoPantalla() - 260, NOE_ObtenAltoPantalla() - 160);
			desfaseX_castillo += ANCHO_CASTILLO + SEPARACION_CASTILLO;
		}
		ptr++;
	}
}

void	ActualizaFondo()
{
	ElementoFondo	*ptr;
	int	i;
	int	j;
	float	max_posx_nubes;
	float	max_posx_castillo;

	i = 0;
	max_posx_nubes = 0;
	max_posx_castillo = 0;
	ptr = elementosFondo;
	while (i++ < MAX_ELEMENTOS_FONDO)
	{
		if (ptr->tipo == NUBES)
		{
			ptr->posX = (ptr->posX) - VELOCIDAD_NUBES * NOE_ObtenTiempoDesdeActualizacion();
			if ((ptr->posX + ANCHO_NUBES) < 0)
			{
				j = -1;
				while (++j < MAX_ELEMENTOS_FONDO)
					if (elementosFondo[j].posX > max_posx_nubes && elementosFondo[j].tipo == 1)
						max_posx_nubes = elementosFondo[j].posX;
				if (max_posx_nubes + ANCHO_NUBES < NOE_ObtenAnchoPantalla())
					ptr->posX = max_posx_nubes + ANCHO_NUBES + (NOE_ObtenAnchoPantalla() - max_posx_nubes);
				else
					ptr->posX = max_posx_nubes + ANCHO_NUBES + SEPARACION_NUBES;
				ptr->posY = NOE_ObtenNumeroAleatorio(0, NOE_ObtenAltoPantalla() - 300);
			}
			ptr++;
		}
		else if (ptr->tipo == CASTILLO)
		{
			ptr->posX = (ptr->posX) - VELOCIDAD_CASTILLO * NOE_ObtenTiempoDesdeActualizacion();
			if ((ptr->posX + ANCHO_CASTILLO) < 0)
			{
				j = -1;
				while (++j < MAX_ELEMENTOS_FONDO)
					if (elementosFondo[j].posX > max_posx_castillo && elementosFondo[j].tipo != 1)
						max_posx_castillo = elementosFondo[j].posX;
				ptr->posX = max_posx_castillo + ANCHO_CASTILLO + SEPARACION_CASTILLO;
			}
			ptr++;
		}
	}
}

void	DibujaFondo()
{
	ElementoFondo	*ptr;
	int	i;

	i = 0;
	ptr = elementosFondo;
	while (i++ < MAX_ELEMENTOS_FONDO)
	{
		if (ptr->tipo == 2)
			NOE_DibujaSprite(16,
					ptr->posX,
					ptr->posY,
					-1,
					-1,
					0,
					0);
		ptr++;
	}
	i = 0;
	ptr = elementosFondo;
	while (i++ < MAX_ELEMENTOS_FONDO)
	{
		if (ptr->tipo == 1)
			NOE_DibujaSprite(13,
					ptr->posX,
					ptr->posY,
					-1,
					-1,
					0,
					0
					);
		ptr++;
	}
}
