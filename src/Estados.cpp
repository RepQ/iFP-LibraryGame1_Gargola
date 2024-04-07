/************************************************
 * 		ESTADOS.C			*
 ************************************************/

#include <Estados.h>
#include <Demonio.h>
#include <Muros.h>
#include <Fondo.h>
#include <stdio.h>

enum State
{
	ENDGAME = -1,
	INACTIVE,
	ACTIVE
};

const int	ms_Points = 1000;
float		miliseconds;
int		estado;
int		seleccionado;
float		puntuacion;
int		Buttons[6] = {INACTIVE , INACTIVE, INACTIVE, INACTIVE, INACTIVE, INACTIVE};
int		music[2] = {INACTIVE, INACTIVE};
int		soundButtonActive = 0;

static void	soundBox(int button)
{
	if (Buttons[button] == INACTIVE)
	{
		soundButtonActive = 1;
		Buttons[button] = ACTIVE;
	}
	else
		soundButtonActive = 0;
}

static void	musicScreen(int index, int stop)
{
	if (music[index] == INACTIVE)
	{
		NOE_ReproduceMusica(index, 10, 100);
		music[index] = ACTIVE;
	}
	if (music[stop] == ACTIVE)
	{
		music[stop] = INACTIVE;
	}
}

static void	RenderScore(float porcentX, float porcentY, float porcentYtexto, float porcentXtexto)
{
	char	score[100];
	sprintf(score, "%.0f", puntuacion);
	NOE_DibujaSprite(12, NOE_ObtenAnchoPantalla() * porcentX, NOE_ObtenAltoPantalla() * porcentY, -1, -1, 0, 0);
	NOE_DibujaTexto(score, NOE_ObtenAnchoPantalla() * porcentXtexto, NOE_ObtenAltoPantalla() * porcentYtexto, 25, 25, 0);
}

static void	RenderSpriteClick(float porcentX, float porcentY, int anchoSprite, int altoSprite, int button)
{

	if ((NOE_ObtenPosicionRatonX() >= NOE_ObtenAnchoPantalla() * porcentX &&
                   	NOE_ObtenPosicionRatonX() <= NOE_ObtenAnchoPantalla() * porcentX + anchoSprite) &&
                		(NOE_ObtenPosicionRatonY() >= NOE_ObtenAltoPantalla() * porcentY &&
                    			NOE_ObtenPosicionRatonY() <= NOE_ObtenAltoPantalla() * porcentY + altoSprite))
	{
		NOE_DibujaSprite(7, NOE_ObtenAnchoPantalla() * porcentX, NOE_ObtenAltoPantalla() * porcentY, anchoSprite, altoSprite, 0, 0);
		soundBox(button);
	}
	else
	{
		NOE_DibujaSprite(8, NOE_ObtenAnchoPantalla() * porcentX, NOE_ObtenAltoPantalla() * porcentY, anchoSprite, altoSprite, 0, 0);
		Buttons[button] = INACTIVE;
	}
}

static void	Play(float porcentX, float porcentY, int anchoSprite, int altoSprite)
{
	if (NOE_ObtenBotonRatonAbajo(NOE_BOTONRATON_PRINCIPAL) && (estado == 0 || estado == 3) && 
			(NOE_ObtenPosicionRatonX() >= NOE_ObtenAnchoPantalla() * porcentX &&
			NOE_ObtenPosicionRatonX() <= NOE_ObtenAnchoPantalla() * porcentX + anchoSprite) &&
			(NOE_ObtenPosicionRatonY() >= NOE_ObtenAltoPantalla() * porcentY &&
			 NOE_ObtenPosicionRatonY() <= NOE_ObtenAltoPantalla() * porcentY + altoSprite))
	{
		seleccionado = 2;
	}
}

static void	HowToPlay(float porcentX, float porcentY, int anchoSprite, int altoSprite)
{
	if (NOE_ObtenBotonRatonAbajo(NOE_BOTONRATON_PRINCIPAL) && (estado == 0) && 
			(NOE_ObtenPosicionRatonX() >= NOE_ObtenAnchoPantalla() * porcentX &&
			NOE_ObtenPosicionRatonX() <= NOE_ObtenAnchoPantalla() * porcentX + anchoSprite) &&
			(NOE_ObtenPosicionRatonY() >= NOE_ObtenAltoPantalla() * porcentY &&
			 NOE_ObtenPosicionRatonY() <= NOE_ObtenAltoPantalla() * porcentY + altoSprite))
		seleccionado = 1;
}

static void	Menu(float porcentX, float porcentY, int anchoSprite, int altoSprite)
{
	if (NOE_ObtenBotonRatonAbajo(NOE_BOTONRATON_PRINCIPAL) && estado == 1  && 
			(NOE_ObtenPosicionRatonX() >= NOE_ObtenAnchoPantalla() * porcentX &&
			NOE_ObtenPosicionRatonX() <= NOE_ObtenAnchoPantalla() * porcentX + anchoSprite) &&
			(NOE_ObtenPosicionRatonY() >= NOE_ObtenAltoPantalla() * porcentY &&
			 NOE_ObtenPosicionRatonY() <= NOE_ObtenAltoPantalla() * porcentY + altoSprite))
		seleccionado = 0;
}

static void	Return()
{
	if (NOE_ObtenTeclaAbajo(NOE_TECLA_ESCAPE))
	{
		seleccionado = 0;
	}
}

static void	Score()
{
	miliseconds += NOE_ObtenTiempoDesdeActualizacion();
	if (miliseconds >= ms_Points)
	{
		puntuacion += 1;
		miliseconds = 0;
	}
}

static void	Retry(float porcentX, float porcentY, int anchoSprite, int altoSprite)
{
	if (NOE_ObtenBotonRatonAbajo(NOE_BOTONRATON_PRINCIPAL) && (estado == 3) && 
			(NOE_ObtenPosicionRatonX() >= NOE_ObtenAnchoPantalla() * porcentX &&
			NOE_ObtenPosicionRatonX() <= NOE_ObtenAnchoPantalla() * porcentX + anchoSprite) &&
			(NOE_ObtenPosicionRatonY() >= NOE_ObtenAltoPantalla() * porcentY &&
			 NOE_ObtenPosicionRatonY() <= NOE_ObtenAltoPantalla() * porcentY + altoSprite))
	{
		IniciaEstados();
		seleccionado = 2;
	}
}

static void	QuitGame1(float porcentX, float porcentY, int anchoSprite, int altoSprite)
{
	if (NOE_ObtenBotonRatonAbajo(NOE_BOTONRATON_PRINCIPAL) && (estado == 3) && 
			(NOE_ObtenPosicionRatonX() >= NOE_ObtenAnchoPantalla() * porcentX &&
			NOE_ObtenPosicionRatonX() <= NOE_ObtenAnchoPantalla() * porcentX + anchoSprite) &&
			(NOE_ObtenPosicionRatonY() >= NOE_ObtenAltoPantalla() * porcentY &&
			 NOE_ObtenPosicionRatonY() <= NOE_ObtenAltoPantalla() * porcentY + altoSprite))
		seleccionado = 4;
}

static void	QuitGame2(float porcentX, float porcentY, int anchoSprite, int altoSprite)
{
	if (NOE_ObtenBotonRatonAbajo(NOE_BOTONRATON_PRINCIPAL) && (estado == 0) && 
			(NOE_ObtenPosicionRatonX() >= NOE_ObtenAnchoPantalla() * porcentX &&
			NOE_ObtenPosicionRatonX() <= NOE_ObtenAnchoPantalla() * porcentX + anchoSprite) &&
			(NOE_ObtenPosicionRatonY() >= NOE_ObtenAltoPantalla() * porcentY &&
			 NOE_ObtenPosicionRatonY() <= NOE_ObtenAltoPantalla() * porcentY + altoSprite))
		seleccionado = 4;
}

void	IniciaEstados()
{
	miliseconds = 0;
	IniciaFondo();
	IniciaDemonio();
	IniciaMuros();
	estado = 0;
	seleccionado = 0;
	puntuacion = 0.0f;
}

void	ActualizaEstado()
{
	Play(0.3f, 0.66f, 234, 65);
	HowToPlay(0.55f, 0.66f, 234, 65);
	Menu(0.05f, 0.86f, 234, 65);
	Retry(0.3f, 0.66f, 250, 65);
	QuitGame1(0.55f, 0.66f, 250, 65);
	QuitGame2(0.42f, 0.8f, 250, 65);
	Return();
	if (soundButtonActive)
		NOE_ReproduceSonido(1, 20, 100);
	switch(seleccionado)
	{
		case 0:
			IniciaEstados();
			estado = 0;
			musicScreen(0, 1);
			break ;
		case 1:
			estado = 1;
			break ;
		case 2:
			ActualizaFondo();
			ActualizaDemonio();
			ActualizaMuros();
			Score();
			estado = 2;
			if (!EstaVivoDemonio())
				seleccionado = 3;
			musicScreen(1, 0);
			break ;
		case 3:
			estado = 3;
			musicScreen(0, 1);
			break ;
		case 4:
			estado = ENDGAME;
			break ;
	}
}

void	DibujaEstado()
{
	switch(estado)
	{
		case 0:
			NOE_DibujaDecorado(0);
			RenderSpriteClick(0.3f, 0.66f, 234, 65, 0);
			NOE_DibujaTexto("PLAY", NOE_ObtenAnchoPantalla() * 0.35f, NOE_ObtenAltoPantalla() * 0.69f, 25, 25, 0);
			RenderSpriteClick(0.55f, 0.66f, 234, 65, 1);
			NOE_DibujaTexto("HOW TO PLAY", NOE_ObtenAnchoPantalla() * 0.58f, NOE_ObtenAltoPantalla() * 0.69f, 15, 25, 0);
			RenderSpriteClick(0.42f, 0.8f, 234, 65, 5);
			NOE_DibujaTexto("EXIT", NOE_ObtenAnchoPantalla() * 0.48f, NOE_ObtenAltoPantalla() * 0.83f, 15, 25, 0);
			break ;
		case 1:
			NOE_DibujaDecorado(1);
			RenderSpriteClick(0.05f, 0.86f, 234, 65, 2);
			NOE_DibujaTexto("MENU", NOE_ObtenAnchoPantalla() * 0.1f, NOE_ObtenAltoPantalla() * 0.89f, 25, 25, 0);
			break ;
		case 2:	
			NOE_DibujaDecorado(2);
			DibujaFondo();
			DibujaDemonio();
			DibujaMuros();
			RenderScore(0.8f, 0.01f, 0.02f, 0.9f);
			break ;
		case 3:
			NOE_DibujaDecorado(0);
			RenderSpriteClick(0.3f, 0.66f, 250, 65, 3);
			NOE_DibujaTexto("RETRY", NOE_ObtenAnchoPantalla() * 0.32f, NOE_ObtenAltoPantalla() * 0.69f, 25, 25, 0);
			RenderSpriteClick(0.55f, 0.66f, 234, 65, 4);
			NOE_DibujaTexto("EXIT", NOE_ObtenAnchoPantalla() * 0.58f, NOE_ObtenAltoPantalla() * 0.69f, 25, 25, 0);
			break ;
	}
}

int	EsEstadoFinal()
{
	if (estado == ENDGAME)
		return (1);
	return (0);
}
