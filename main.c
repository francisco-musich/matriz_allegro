
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>      //Printf
#include <stdint.h> 

//#include "BackEnd.h"


//Defines internos necesarios


#define FPS 60.0
#define BLOCK_SIZE 50      
#define FILASCONBORDEJUEGO 16
#define COLUMNASCONBORDE 16
#define FILASCONBORDE 20

#define DEBUG 1


#define false 0
#define true 1

enum {LIBRE,BLOQUEADO,NO_BLOQUEADO};
enum {ROJO=1,VERDE,AMARILLO,AZUL,NARANJA,ROSA,VIOLETA};



typedef struct {
  int i;
  int j;
} position_t;

typedef struct {
  unsigned int color;
  unsigned int LED;
  int estado;
  unsigned int figuras;
  position_t next_position;
} puntito_t;

void Generar_marco(void);
void print_matriz(void);
void dis_juego(void);

puntito_t matriz_de_juego[FILASCONBORDE][COLUMNASCONBORDE];



    ALLEGRO_DISPLAY * display = NULL; //Creo un puntero a mi display
    
    ALLEGRO_BITMAP*rojo=NULL;
    ALLEGRO_BITMAP*verde=NULL;
    ALLEGRO_BITMAP*naranja=NULL;
    ALLEGRO_BITMAP*amarillo=NULL;
    ALLEGRO_BITMAP*azul=NULL;
    ALLEGRO_BITMAP*rosa=NULL;
    ALLEGRO_BITMAP*violeta=NULL;
    ALLEGRO_EVENT_QUEUE  *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    

int main (void)
{
   //inicilizar todo
    Generar_marco();
    (matriz_de_juego[8][8]).color = AMARILLO;
    (matriz_de_juego[10][10]).color = ROJO;
    if(!al_init()) 
    { 
	printf("failed to initialize allegro!\n");
	return -1;
    }
    
    //Inicializo cola de eventos
    event_queue = al_create_event_queue();
    
    timer = al_create_timer(0.25);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
    
    if(!event_queue) {
		printf("failed to create event_queue!\n");
		al_destroy_timer(timer);
                return -1;                
	}
    //Inicializo teclado
    if(!al_install_keyboard()) {
		printf("failed to initialize the keyboard!\n");
                al_destroy_event_queue(event_queue);
                al_destroy_timer(timer);
		return -1;
	}
    
    //Inicializo imagenes
    if(!al_init_image_addon()) { // ADDON necesario para manejo de imagenes 
		printf("failed to initialize image addon !\n");
                al_destroy_event_queue(event_queue);
                al_destroy_timer(timer);
		return -1;
	}
    
    
    //registro fuentes de eventos
    printf("hasta aca bien");
    //al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    printf("eventos bien");
    dis_juego();
   //while principal
/*    while(running)
    {
        switch(estado)
        {
        case JUGANDO:
            dis_juego();
            break;
        case PAUSA:
            dis_pausa();
            break;
        case MENU:
            dis_menu();
            break;
        case SETTINGS:
            dis_settings();
            break;
        case DIFICULTAD:
            dis_dificultad;
            break;
        case HIGHSCORE:
            dis_highscore();
            break;
        }
    }*/
    
}

void dis_juego(void)
{   //INICIALIZO DISPLAY Y BITMAPS
    
    verde = al_load_bitmap("verde.png");
    if(!verde)
    {
        printf ("failed to load verde!\n");
        al_destroy_event_queue(event_queue);
       
        al_destroy_bitmap(verde);
        al_destroy_timer(timer);
        return -1;
    }
    
    rojo = al_load_bitmap ("rojo.png");
    if(!rojo)
    {
        printf ("failed to create rojo!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_bitmap(rojo);
        al_destroy_bitmap(verde);
        al_destroy_timer(timer);
        return -1;
    }
    amarillo = al_load_bitmap("amarillo.png");
    if(!amarillo)
    {
        printf ("failed to create amarillo!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_bitmap(rojo);
        al_destroy_bitmap(verde);
        al_destroy_bitmap(amarillo);
        al_destroy_timer(timer);
        return -1;
    }
    azul = al_load_bitmap("azul.png");
    if(!azul)
    {
        printf ("failed to create azul!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_bitmap(rojo);
        al_destroy_bitmap(verde);
        al_destroy_bitmap(amarillo);
        al_destroy_bitmap(azul);
        al_destroy_timer(timer);
        return -1;
    }
    /*naranja = al_load_bitmap("naran.png");
    if(!naranja);
    {
        printf ("failed to create naranja!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_bitmap(rojo);
        al_destroy_bitmap(verde);
        al_destroy_bitmap(amarillo);
        al_destroy_bitmap(azul);
        al_destroy_bitmap(naranja);
        al_destroy_timer(timer);
        return -1;
    }*/
    rosa= al_load_bitmap("rosa.png");
    if(!rosa)
    {
        printf ("failed to create rosa!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_bitmap(rojo);
        al_destroy_bitmap(verde);
        al_destroy_bitmap(amarillo);
        al_destroy_bitmap(azul);
        al_destroy_bitmap(naranja);
        al_destroy_bitmap(rosa);
        al_destroy_timer(timer);
        return -1;
    }
    violeta = al_load_bitmap("violeta.png");
    if(!violeta)
    {
        printf ("failed to create rosa!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_bitmap(rojo);
        al_destroy_bitmap(verde);
        al_destroy_bitmap(amarillo);
        al_destroy_bitmap(azul);
        al_destroy_bitmap(naranja);
        al_destroy_bitmap(rosa);
        al_destroy_bitmap(violeta);
        al_destroy_timer(timer);
        return -1;
    }
    display = al_create_display((COLUMNASCONBORDE*BLOCK_SIZE),(FILASCONBORDE*BLOCK_SIZE));
    int redraw = 1;
   if(!display) 
   {
	printf("failed to create display!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_bitmap(rojo);
        al_destroy_bitmap(verde);
        al_destroy_bitmap(amarillo);
        al_destroy_bitmap(azul);
        al_destroy_bitmap(naranja);
        al_destroy_bitmap(rosa);
        al_destroy_bitmap(violeta);
        al_destroy_timer(timer);
        al_destroy_display(display);
	return -1;
    }

    
   al_clear_to_color(al_map_rgb(255,255,255)); //Hace clear del backbuffer del diplay al color RGB 255,255,255 (blanco)
           al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
    
   int jogando =1; //NO ES LA MISMA DEL MAIN, ME SIRVE PARA SABER SI CAMBIO DE PANTALLA 
    //IDEA PARA ESTADO JUEGO
    while(jogando)  
	{
		ALLEGRO_EVENT ev;
		if( al_get_next_event(event_queue, &ev) ) //Toma un evento de la cola
		{ 
			if(ev.type == ALLEGRO_EVENT_TIMER) 
				redraw = true;

			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                        {
                            //*(pevento++)= pausa;
                            printf("pausa");
                            jogando = 0;
                        }
                            
                        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
                        {
                            switch (ev.keyboard.keycode)
                            {
                            case ALLEGRO_KEY_DOWN:
                                ///*(pevento++)= bajar;   
                                printf("Bajar");
                                break;
                            case ALLEGRO_KEY_W:
                                (matriz_de_juego[11][11]).color= AZUL;
                                printf("girar");
                                break;
                            case ALLEGRO_KEY_RIGHT:
                               /// *(pevento++)= mover_der;
                                printf("right");
                                break;
                            case ALLEGRO_KEY_LEFT:
                              //  *(pevento++)=mover_izq;
                                printf("left");
                                break;
                            case ALLEGRO_KEY_UP:
                              //  *(pevento++)= girar;
                                printf("girar");
                                break;
                            case ALLEGRO_KEY_ESCAPE:
                              //  *(pevento++)=pausa;
                                printf("pausa");
                                jogando = 0;    //se que cambio de estado entonces apago el while, asi puedo cambiar de pantalla
                                
                                
                                break; 
                            }
                        }

		}
 
		if(redraw /*&& al_is_event_queue_empty(event_queue)*/) 
		{
			redraw = false;
			print_matriz();
		}
	  
	}
    al_destroy_display(display); 
     al_destroy_bitmap(rojo);
        al_destroy_bitmap(verde);
        al_destroy_bitmap(amarillo);
        al_destroy_bitmap(azul);
        al_destroy_bitmap(naranja);
        al_destroy_bitmap(rosa);
        al_destroy_bitmap(violeta);
        al_destroy_timer(timer);
    al_stop_timer(timer);
 
}



void print_matriz(void)
{
    int i;   
    int j;    
    for (i=4 ; i < FILASCONBORDEJUEGO ; i++) 
        {
        for (j=0;j<COLUMNASCONBORDE;j++){
            
            if((i==(FILASCONBORDEJUEGO-1))||(j==0)||(j==(COLUMNASCONBORDE-1)))
            {
                //IMPRIMIR BLOQUE DE MARCO
                {    al_draw_scaled_bitmap(violeta,
                                        0,0, al_get_bitmap_width(violeta),al_get_bitmap_height(violeta),
                                        (j*BLOCK_SIZE),(i*BLOCK_SIZE),BLOCK_SIZE,BLOCK_SIZE, 0);
                al_flip_display();
                }
            }
            else
            {
                switch((matriz_de_juego[i][j]).color)
                {
                case ROJO:
                    //imprimir bloque rojo
                    {
                al_draw_scaled_bitmap(rojo,
                                        0,0, al_get_bitmap_width(rojo),al_get_bitmap_height(rojo),
                                        (j*BLOCK_SIZE),(i*BLOCK_SIZE),BLOCK_SIZE,BLOCK_SIZE, 0);
                al_flip_display();
                }
                    break;
                case VERDE:
                    //IMP VERDE
                {
                    al_draw_scaled_bitmap(verde,
                                        0,0, al_get_bitmap_width(verde),al_get_bitmap_height(verde),
                                        (j*BLOCK_SIZE),(i*BLOCK_SIZE),BLOCK_SIZE,BLOCK_SIZE, 0);
                al_flip_display();
                }
                    break;
                case AMARILLO:
                    //imp AMA
                {  al_draw_scaled_bitmap(amarillo,
                                        0,0, al_get_bitmap_width(amarillo),al_get_bitmap_height(amarillo),
                                        (j*BLOCK_SIZE),(i*BLOCK_SIZE),BLOCK_SIZE,BLOCK_SIZE, 0);
                al_flip_display();
                }
                    break;
                case AZUL:
                    //imp AZUL
                {   al_draw_scaled_bitmap(azul,
                                        0,0, al_get_bitmap_width(azul),al_get_bitmap_height(azul),
                                        (j*BLOCK_SIZE),(i*BLOCK_SIZE),BLOCK_SIZE,BLOCK_SIZE, 0);
                al_flip_display();
                }
                    break;
                case NARANJA:
                    //imp naranja
                {   al_draw_scaled_bitmap(naranja,
                                        0,0, al_get_bitmap_width(naranja),al_get_bitmap_height(naranja),
                                        (j*BLOCK_SIZE),(i*BLOCK_SIZE),BLOCK_SIZE,BLOCK_SIZE, 0);
                al_flip_display();
                }
                    break;
                case ROSA:
                    //imp rosa
                {   al_draw_scaled_bitmap(rosa,
                                        0,0, al_get_bitmap_width(rosa),al_get_bitmap_height(rosa),
                                        (j*BLOCK_SIZE),(i*BLOCK_SIZE),BLOCK_SIZE,BLOCK_SIZE, 0);
                al_flip_display();
                }
                    break;
                case VIOLETA:
                    //imp violeta
                {    al_draw_scaled_bitmap(violeta,
                                        0,0, al_get_bitmap_width(violeta),al_get_bitmap_height(violeta),
                                        (j*BLOCK_SIZE),(i*BLOCK_SIZE),BLOCK_SIZE,BLOCK_SIZE, 0);
                al_flip_display();
                }
                    break;
                            
                }
            }
        
            
            
        }
    }


}
    
void Generar_marco(void) 
{
    int i,j;
    for(i=0;i<FILASCONBORDE;i++)
        for(j=0;j<COLUMNASCONBORDE;j++)
            matriz_de_juego[i][j].estado=LIBRE;

    for(i=0;i<FILASCONBORDE;i++)
        matriz_de_juego[i][0].estado=BLOQUEADO;

    for(i=0;i<FILASCONBORDE;i++)
        matriz_de_juego[i][COLUMNASCONBORDE-1].estado=BLOQUEADO;

    //Por un tema de lógica se complica poner este borde ver lleno_fila()
    //Que salga por frontEnd nomas
    //for(j=0;j<COLUMNASCONBORDE;j++)  
      //  matriz_de_juego[0][j].estado=BLOQUEADO;

    for(j=0;j<COLUMNASCONBORDE;j++)
        matriz_de_juego[FILASCONBORDE-1][j].estado=BLOQUEADO;
    
    #if PRINT
  for(i=0;i<FILASCONBORDE;i++) //Imprime el marco
    {
        printf("\n");
        for(j=0;j<COLUMNASCONBORDE;j++)
        {
          if(matriz_de_juego[i][j].estado==BLOQUEADO)
              printf("|*|");
            else 
              printf("   ");
        }
    }
  printf("\n\n");
#endif
}

