typedef struct
{
	float	posX;
	float	alturaSuperior;
	float	alturaInferior;
	float	anchura;
} Muro;

void	IniciaMuros();
void	ActualizaMuros();
int	ChocaConMuro(float, float, float, float);
float	ObtenVelocidadMuros();
void	DibujaMuros();
