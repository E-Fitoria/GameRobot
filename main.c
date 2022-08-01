#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#include <dos.h>
#include <DIBUJOS.h>

/* pantalla_carga */

/*Objetos en el campo de batalla*/

/*modena ganar*/
int winx = 10, winy = 450, ancho_win = 20, alto_win = 20;

/*robot*/
int ancho_robot = 15, alto_robot = 38;

/*balas*/
int bala1x = 542-13, bala1y = 21-13, diametro_bala1 = 28;
int bala2x = 46-21, bala2y = 377-21, diametro_bala2 = 37;
int bala3x = 542-18, bala3y = 440-18, diametro_bala3 = 30;

/*Barril rojo y barril en llamas*/
int barrilx =127 , barrily = 48, ancho_barril = 30, alto_barril = 23;

/*Pichinga gasolina*/
int gasolinax = 191, gasolinay = 94, ancho_gasolina = 11, alto_gasolina = 14;

/*fuego*/
int fuegox = 301, fuegoy = 247, ancho_fuego = 53, alto_fuego = 65;

/*Canon 1*/
int canon1x = 1, canon1y = 107, ancho_canon1= 35, alto_canon1 = 36;

/*Variables para mover al robot*/
void *robot;
int bender;



/*Constantes para controlar al robot*/
#define derecha 100
#define izquierda 97
#define arriba 119
#define abajo 115

/*Constantes para limitar pantalla de movimiento*/
#define limitx_izquierda 10
#define limitx_derecha 570
#define limity_arriba 5
#define limity_abajo 432

/*funciones principales*/
void objetosDibujados();
void MovRobot(int, int);
int ColisionObj(int, int, int, int, int, int, int, int);
void Reiniciar(int,int,int,int);
void balas();

/*void dibujarObj(int);
objeto   id
tanque	 1
fuego    2
bomba    3
barril   4
gasolina 5
llave    6
robot    7
canon    8
*/
struct movimientos{
	int x, x2, y, y2;
}m_robot;

int main(int argc, char const *argv[])
{
	int DRIVER = DETECT, mode;
	initgraph(&DRIVER, &mode, "C:\\tc\\TC20\\BIN");

	/*pantalla_carga();*/
	objetosDibujados();
	/*ROBOT*/
	MovRobot(25,20);
	closegraph();
	return 0;
}

void objetosDibujados(){
	setbkcolor(LIGHTGREEN);
	cleardevice();
	dibujarObj(2);
	dibujarObj(3);
	dibujarObj(4);
	dibujarObj(5);
	dibujarObj(7);
	dibujarObj(8);
	dibujarObj(9);
	dibujarObj(10);
	dibujarObj(11);
	balas();
}

int ColisionObj(int x, int y, int ancho_robot, int alto_robot, int x2, int y2, int ancho_objeto, int alto_objeto){

	if(x >(x2 + ancho_objeto)){
		return 0;
	}
	else if((x + ancho_robot) < x2){
		return 0;
	}
	else if(y > (y2 + alto_objeto)){
		return 0;
	}
	else if((y + alto_robot) < y2){
		return 0;
	}
	else{
		return 1; /*si retorna 1 hay colision*/
	}
}

void balas(){

	setcolor(RED);
	setfillstyle(SOLID_FILL,RED);

	circle(542,21,12);
	floodfill(542,21,RED);

	circle(46,377,15);
	floodfill(46,377,RED);

	circle(542,440,12);
	floodfill(542,440,RED);

}

void Reiniciar(int x, int y, int x2, int y2){
	/*Guardar robot*/
	bender = imagesize(x,y,x2,y2);
	robot = malloc(bender);
	getimage(x,y,x2,y2,robot);
}


void MovRobot(int x, int y){

	/*vidas*/
	int vidas = 4, tecla;
	/* se colocan 4 vidas para que al iniciar el juego solo queden las 3 vidas necesarias */


	int areaBarril, areaGasolina, areaFuego, areaCanon1, areaBala1, areaBala2, areaBala3;
	void *barrilP, *gasolinaP, *fuegoP, *canon1P, *bala1P, *bala2P, *bala3P;

	int fuegoXmov, canon1Xmov;
	int bala1Xmov, bala2Xmov, bala3Xmov;

	int c;

	c = 2;

	bala1Xmov = 0;
	bala2Xmov = 0;
	bala3Xmov = 0;


	areaBala1 = imagesize(bala1x, bala1y, bala1x + diametro_bala1, bala1y + diametro_bala1);
	bala1P = malloc(areaBala1);
	getimage(bala1x, bala1y, bala1x + diametro_bala1, bala1y + diametro_bala1, bala1P);

	areaBala2 = imagesize(bala2x, bala2y, bala2x + diametro_bala2, bala2y + diametro_bala2);
	bala2P = malloc(areaBala2);
	getimage(bala2x, bala2y, bala2x + diametro_bala2, bala2y + diametro_bala2, bala2P);

	areaBala3 = imagesize(bala3x, bala3y, bala3x + diametro_bala3, bala3y + diametro_bala3);
	bala3P = malloc(areaBala3);
	getimage(bala3x, bala3y, bala3x + diametro_bala3, bala3y + diametro_bala3, bala3P);

	areaBarril = imagesize(barrilx, barrily, barrilx + ancho_barril, barrily + alto_barril);
	barrilP = malloc(areaBarril);
	getimage(barrilx, barrily, barrilx + ancho_barril, barrily + alto_barril, barrilP);

	areaGasolina = imagesize(gasolinax, gasolinay, gasolinax + ancho_gasolina, gasolinay + alto_gasolina);
	gasolinaP = malloc(areaGasolina);
	getimage(gasolinax, gasolinay, gasolinax + ancho_gasolina, gasolinay + alto_gasolina, gasolinaP);

	areaFuego = imagesize(fuegox, fuegoy, fuegox + ancho_fuego, fuegoy + alto_fuego);
	fuegoP = malloc(areaFuego);
	getimage(fuegox, fuegoy, fuegox + ancho_fuego, fuegoy + alto_fuego, fuegoP);

	areaCanon1 = imagesize(canon1x, canon1y, canon1x + ancho_canon1, canon1y + alto_canon1);
	canon1P = malloc(areaCanon1);
	getimage(canon1x, canon1y, canon1x + ancho_canon1, canon1y + alto_canon1, canon1P);


	Reiniciar(25,20,39,57);


 while (1) {

	 m_robot.x = x;
	 m_robot.y = y;
	 objetosDibujados();
	 Reiniciar(25,20,39,57);

	 vidas -= 1;

	 bala1Xmov = 0;
	 bala2Xmov = 0;
	 bala3Xmov = 0;

	 putimage(127, 80, barrilP, COPY_PUT);
	 putimage(440, 100, barrilP, COPY_PUT);
	 putimage(227, 110, barrilP, COPY_PUT);
	 putimage(318, 230, barrilP, COPY_PUT);
	 putimage(115, 260, barrilP, COPY_PUT);
	 putimage(423, 290, barrilP, COPY_PUT);
	 putimage(163, 320, barrilP, COPY_PUT);
	 putimage(490, 350, barrilP, COPY_PUT);
	 putimage(200, 380, barrilP, COPY_PUT);

	 putimage(99, 73, gasolinaP, COPY_PUT);
	 putimage(103, 100, gasolinaP, COPY_PUT);
	 putimage(300, 120, gasolinaP, COPY_PUT);
	 putimage(150, 163, gasolinaP, COPY_PUT);
	 putimage(95, 189, gasolinaP, COPY_PUT);
	 putimage(360, 210, gasolinaP, COPY_PUT);
	 putimage(380, 251, gasolinaP, COPY_PUT);
	 putimage(210, 279, gasolinaP, COPY_PUT);





	while(1){

		borrarCorazones(vidas);

		/* correr balas */
		putimage(bala1x-bala1Xmov, bala1y, bala1P, COPY_PUT);
		putimage(bala2x+bala2Xmov, bala2y, bala1P, COPY_PUT);
		putimage(bala3x-bala3Xmov, bala3y, bala1P, COPY_PUT);


		/*Tipo de relleno igual al fondo para utilizarlo con la funcion bar*/
		setfillstyle(SOLID_FILL,LIGHTGREEN);

		if (kbhit()) {
			tecla = getch();
		} else {
			tecla = 0;
		}


		if(tecla == derecha){
			/*Mientras sea menor que 587 para limitar la pantalla de movimiento de la skin en el eje de las x*/
			if(m_robot.x < limitx_derecha){
				m_robot.x+=15;

				putimage(m_robot.x,m_robot.y,robot,COPY_PUT);
				/*Borramos el rastro del robot al moverse a la derecha*/
				bar(m_robot.x-15,m_robot.y,m_robot.x,m_robot.y+37);

			}

		}else if(tecla == izquierda){
			/*Mientras sea meyor que 10 para limitar la pantalla de movimiento de la skin en el eje de las x
			esto se puede sacar o deducir restando con el numero de pixeles que ocupa el bitmap del robot*/
			if(m_robot.x > limitx_izquierda){
				m_robot.x-=15;
				putimage(m_robot.x,m_robot.y,robot,COPY_PUT);
				/*Borramos el rastro del robot al moverse a la izquierda*/
				bar(m_robot.x+15,m_robot.y,m_robot.x+30,m_robot.y+37);

			}
		}else if(tecla == arriba){
			/*Mientras sea meyor que 5 para limitar la pantalla de movimiento de la skin en el eje de las y
			esto se puede sacar o deducir restando con el numero de pixeles que ocupa el bitmap del robot*/
			if(m_robot.y > limity_arriba){
				m_robot.y-=15;
				putimage(m_robot.x,m_robot.y,robot,COPY_PUT);
				/*Borramos el rastro del robot al moverse hacia arriba*/
				bar(m_robot.x,m_robot.y+38,m_robot.x+15,m_robot.y+52);


			}

		}else if(tecla == abajo){

			if(m_robot.y < limity_abajo){
				m_robot.y+=15;
				putimage(m_robot.x,m_robot.y,robot,COPY_PUT);
				/*Borramos el rastro del robot al moverse hacia abajo*/
				bar(m_robot.x,m_robot.y-15,m_robot.x+15,m_robot.y);

			}

		}

		if(ColisionObj(m_robot.x,m_robot.y,ancho_robot,alto_robot,barrilx,barrily,ancho_barril,alto_barril) == 1 ||
			ColisionObj(m_robot.x,m_robot.y,ancho_robot,alto_robot,gasolinax,gasolinay,ancho_gasolina,alto_gasolina) == 1 ||
			ColisionObj(m_robot.x,m_robot.y,ancho_robot,alto_robot,fuegox,fuegoy,ancho_fuego,alto_fuego) == 1 ||
			ColisionObj(m_robot.x,m_robot.y,ancho_robot,alto_robot,canon1x,canon1y,ancho_canon1,alto_canon1) == 1||
			ColisionObj(m_robot.x,m_robot.y,ancho_robot,alto_robot,bala1x-bala1Xmov, bala1y,diametro_bala1, diametro_bala1) ||
			ColisionObj(m_robot.x,m_robot.y,ancho_robot,alto_robot,bala2x+bala2Xmov, bala2y,diametro_bala2, diametro_bala2) ||
			ColisionObj(m_robot.x,m_robot.y,ancho_robot,alto_robot,bala3x-bala3Xmov, bala3y,diametro_bala3, diametro_bala3)){
				/*volver a la posicion inicial*/
				break;
		} else if(ColisionObj(m_robot.x,m_robot.y,ancho_robot,alto_robot, winx, winy, ancho_win, alto_win)) { /*colision con modena Win*/
			setfillstyle(SOLID_FILL, BLUE);
			bar(200,140,450,300);
			delay(4000);
			exit(0);
		}

		if ( ( (bala1x-bala1Xmov) <10 )  ) {
		 c = -2;
	 } else if ( ( (bala1x-bala1Xmov) > 630 ) ) {
		 c = 2;
	 }

		bala1Xmov += c;
		bala2Xmov += c;
		bala3Xmov += c;



		if(tecla == 'x' || vidas == 0){
			free(robot);
			exit(0);
		}

	}
 }
}
