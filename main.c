#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LARGO_N 15
#define CANT_USR 100
#define CANT_P 100

//Estructuras
typedef struct {
	char palabra[LARGO_N];
	int largo_palabra;
} cadena;

typedef struct {
	int dia;
	int mes;
	int anio;
} fecha;

typedef struct {
	int hora;
	int min;
} horas;

typedef struct {
	cadena nombre;
	cadena apellido;
	cadena alias;
	int edad;
	int estado;
} usuario;

typedef struct {
	fecha fecha_juego;
	cadena alias;
	int resultado;
	horas hora_juego;
} juegos;

//Funciones del juego en sí
void instrucciones();
void pantalla();
int random_num(int x);
int chequear_lleno();
void generar_nuevo_num();
void inicializar_tab();
void mover_abajo();
void mover_arriba();
void mover_der();
void mover_izq();
void sum_abajo();
void sum_arriba();
void sum_der();
void sum_izq();
int calcular_max();
void jugar();
void ganar_pantalla();
void perder_pantalla();
void pantalla_fin_juego();
int fin();
int movimiento();
void backup_tab();


//Funciones que apuntan a gestionar usuarios y juegos
void Menu_Principal();
void Menu_Gestion();
void Menu_Informes();
int ing_opcion_principal();
int ing_opcion_informe();
cadena ing_nombre();
cadena ing_apellido();
cadena ing_alias();
int ing_edad();
fecha ing_fecha();
horas ing_hora();
int Nro_Usr();
void inicializo_users(usuario users[], int pos);
void inicializo_juegos(juegos games[], int pos);
void Muestro_nombre(usuario users[], int pos);
void Muestro_apellido(usuario users[], int pos);
void Muestro_alias(usuario users[], int pos);
void Muestro_edad(usuario users[], int pos);
void Muestro_alias_j(juegos games[], int pos);
void Muestro_fecha(juegos games[], int pos);
void Muestro_hora(juegos games[], int pos);
void Muestro_resultado(juegos games[], int pos);
void Alta(usuario users[]);
void Baja(usuario users[]);
void listado_usuarios(usuario users[]);
void listado_juegos(juegos games[]);
void ing_ini_juego(juegos games[]);
int comparar_palias(usuario users[], cadena al_ing);
int comparo_ali(cadena c1, usuario users[]);
int comparar_alias(usuario users[], cadena al_ing);

//Variables globales
int puntos=0;
int puntos_anteriores=0;
int tab[4][4];
int btab[4][4];
usuario users[CANT_USR];
int respuesta=0;
int resultado;
int valor=0;
//Principal
int main()
{
    srand(time(NULL));

    usuario users[CANT_USR];

    //inicializo todo el arreglo
    int i;
    for (i=0; i<CANT_USR;i++)
    {
    inicializo_users(users,i);
    }

	juegos games[CANT_P];

	int j;
	for(j=0; j<CANT_P; j++)
	{
		inicializo_juegos(games,j);
	}

    Menu_Principal();
    int ing_op_prin = ing_opcion_principal();

    while(ing_op_prin != 4) //la opcion 4 es salir
	{
		switch(ing_op_prin)
			{
			case 1: //Gestion
				Menu_Gestion();
				int ing_op_ges = ing_opcion_principal();

				switch(ing_op_ges)
					{
						case 1: //Alta user
							Alta(users);
							break;
						case 2:
							Baja(users);
							break;
						case 3:
							printf("Modificar datos.\n");
							printf("Se podra modificar solo la edad del usuario.\n");

							cadena ali_mod = ing_alias();
							int num_ali = comparo_ali(ali_mod, users);

							if(num_ali == 0) {
								int n_edad, aux_ali = comparar_palias(users, ali_mod);
								Muestro_edad(users, aux_ali);
								printf("\nIngrese edad nueva.\n");
								scanf("%d", &n_edad);
								users[aux_ali].edad = n_edad;
							} else {
								printf("El alias ingresado no existe.\n");
							}
								printf("\nPresione cualquier tecla para continuar");
								getchar();
							break;

						case 4:
							Menu_Principal();
							ing_op_prin = ing_opcion_principal();
							break;
					}
			break;

			case 2:
				Menu_Informes();
				int ing_op_info = ing_opcion_informe();

					switch(ing_op_info)
						{
							case 1:
								listado_usuarios(users);
								break;
							case 2:
								listado_juegos(games);
								break;
							/*case 3:
								funcion lista juegos por user
							case 4:
								funcion lista juego por fecha*/
							case 5:
								Menu_Principal();
								ing_op_prin = ing_opcion_principal();
								break;
						}
			break;
			case 3:

				do { ing_ini_juego(games);
				switch(valor) {
					case 1:
					system("clear");
					instrucciones();
					jugar();
					break;
					} } while(valor == 1);
					Menu_Principal();
					ing_op_prin = ing_opcion_principal();
				break;
			}
	}
return 0;
}

//Funciones que muestran los distintos menues
void Menu_Principal()
{
	system("clear");
	printf("BIENVENIDO A <<JUEGO 2048>>\n===========================\n");
	printf("Menu Principal\n");
	printf("1.- Gestion de Usuarios\n2.- Informes\n3.- Jugar\n4.- Salir\n");
}

void Menu_Gestion()
{
	system("clear");
	printf("Gestion de Usuarios\n");
	printf("1.- Alta de Usuario\n2.- Baja de Usuario\n3.- Modificar Usuario\n4.- Volver\n");
}

void Menu_Informes()
{
	system("clear");
	printf("Informes\n");
	printf("1.- Lista de usuarios\n2.- Lista de juegos\n3.- Lista de juegos por usuario\n4.- Lista de juegos por fecha\n5.- Volver\n");
}

//Funciones para usarse en los menus, toman la opcion elegida
int ing_opcion_principal() //se usa tambien en gestion
{
	int opcion;
	do {
		printf("Ingrese opcion (1..4)\n");
		scanf("%d", &opcion);
	} while((opcion < 1) || (opcion > 4));
	return (opcion);
}

int ing_opcion_informe()
{
	int opcion;
	do {
		printf("Ingrese opcion (1..5)\n");
		scanf("%d", &opcion);
	} while((opcion < 1) || (opcion > 5));
	return (opcion);
}

//Funciones que inicializan los arreglos
void inicializo_users(usuario users[], int pos)
{
	int x;
	for(x=0; x<LARGO_N; x++)
	{
		users[pos].nombre.palabra[x] = ' ';
		users[pos].apellido.palabra[x] = ' ';
		users[pos].alias.palabra[x] = ' ';
	}
	users[pos].nombre.largo_palabra = 0;
	users[pos].apellido.largo_palabra = 0;
	users[pos].alias.largo_palabra = 0;
	users[pos].edad = 0;
	users[pos].estado = 0;
}

void inicializo_juegos(juegos games[], int pos)
{
	int x;
	for(x=0; x< LARGO_N; x++)
	{
		games[pos].alias.palabra[x] = ' ';
	}
	games[pos].alias.largo_palabra = 0;
	games[pos].fecha_juego.dia = 0;
	games[pos].fecha_juego.mes = 0;
	games[pos].fecha_juego.anio = 0;
	games[pos].hora_juego.hora = 0;
	games[pos].hora_juego.min = 0;
	games[pos].resultado = resultado; //puede ser 0, 1 o -1 (log,nolog,abort)
}

//Esta es una funcion auxiliar, se usa para pedir un numero de referencia para posicionarse en los arreglos.
int Nro_Usr()
{
	int nro_usr;
	do {
		printf("Ingrese Nro. de usuario (1..%d) ",CANT_USR);
        scanf("%d",&nro_usr);

	} while((nro_usr < 1) || (nro_usr > CANT_USR));
	return (nro_usr);
}

//Funciones de ingreso de datos
cadena ing_nombre()
{
	cadena nom;
	int i=0;
	printf("Ingresa nombre de usuario: ");
	while(((nom.palabra[i] = getchar()) != 10) && i <= LARGO_N)
	{
		i++;
	} nom.largo_palabra = i;
	return nom;
}

cadena ing_apellido()
{
	cadena ape;
	int i=0;
	printf("Ingrese apellido del usuario: ");
	while(((ape.palabra[i] = getchar()) != 10) && i <= LARGO_N)
	{
		i++;
	} ape.largo_palabra = i;
	return ape;
}

cadena ing_alias()
{
	getchar();
	cadena alias;
	int i=0;
	printf("Ingrese alias del usuario: ");
	while(((alias.palabra[i] = getchar()) != 10) && i <= LARGO_N)
	{
		i++;
	} alias.largo_palabra = i;
	return alias;
}

int ing_edad()
{
	int anios;
	printf("Ingrese edad del usuario: ");
	scanf("%d", &anios);
	return anios;
}

fecha ing_fecha() //para usar en listado de fecha e inicio juego
{
	fecha fecha_juego;
	printf("Ingrese fecha: ");
	scanf("%d/%d/%d", &fecha_juego.dia, &fecha_juego.mes, &fecha_juego.anio);
	return fecha_juego;
}

horas ing_hora() //se usa para solicitar la hora
{
	horas hora_juego;
	printf("Ingrese la hora actual: ");
	scanf("%d:%d", &hora_juego.hora, &hora_juego.min);
	return hora_juego;
}

//Funcion que verifica si el alias ingresado esta disponible
int comparar_alias(usuario users[], cadena al_ing)
{
	int i, comp = 1;
	for(i=0; i<CANT_USR; i++)
	{
		if(strcmp(users[i].alias.palabra, al_ing.palabra) == 0)
		{
			comp=0;
		}
	} return comp;
}
//Esta funcion basicamente que actua como buscador, busca una cadena dentro de un vector y devuelve su posicion.
int comparar_palias(usuario users[], cadena al_ing)
{
	int i, cpos = 1;
	for(i=0; i<CANT_USR; i++)
	{
		if(strcmp(users[i].alias.palabra, al_ing.palabra) == 0)
		{
			cpos= i;
		}
	} return cpos;
}
//Funciones "Muestro" se usan en los listados
void Muestro_nombre(usuario users[], int pos)
{
	int i;
	printf("\nNombre: ");
	for(i=0; i<users[pos].nombre.largo_palabra; i++)
	{
		printf("%c", users[pos].nombre.palabra[i]);
	}
}

void Muestro_apellido(usuario users[], int pos)
{
	int i;
	printf("\nApellido: ");
	for(i=0; i<users[pos].apellido.largo_palabra; i++)
	{
		printf("%c", users[pos].apellido.palabra[i]);
	}
}

void Muestro_alias(usuario users[], int pos)
{
	int i;
	printf("\nAlias: ");
	for(i=0; i<users[pos].alias.largo_palabra; i++)
	{
		printf("%c", users[pos].alias.palabra[i]);
	}
}

void Muestro_alias_j(juegos games[], int pos)
{
	int i;
	printf("\nAlias: ");
	for(i=0; i<games[pos].alias.largo_palabra; i++)
	{
		printf("%c", games[pos].alias.palabra[i]);
	}
}

void Muestro_edad(usuario users[], int pos)
{
	printf("\nEdad: %d", users[pos].edad);
}

void Muestro_fecha(juegos games[], int pos)
{
	printf("\nFecha: %d/%d/%d", games[pos].fecha_juego.dia, games[pos].fecha_juego.mes, games[pos].fecha_juego.anio);
}

void Muestro_hora(juegos games[], int pos)
{
	printf("\nHora: %d:%d", games[pos].hora_juego.hora, games[pos].hora_juego.min);
}

void Muestro_resultado(juegos games[], int pos)
{
	if(resultado == -1)
	{
		printf("Resultado: Abortado\n");
	} else if(resultado == 0)
		{
			printf("Resultado: No Logrado\n");
		} else {
			printf("Resultado: Logrado\n");
			}
}

//Funcion usada para dar de alta a un usuario, se usa en menu gestion
void Alta(usuario users[])
{
	char confirmar, ch;
	system("clear");
	printf("Ingreso de datos de Usuario.\n");

	int nro_usr = Nro_Usr();
	cadena ali;
	int comparacion, calias;

	if((users[nro_usr-1].nombre.largo_palabra == 0) || users[nro_usr-1].estado == 0)
	{
		ali = ing_alias();
		//aqui es donde se verifica si es valido el alias ingresado
		comparacion = comparar_alias(users,ali);
		calias = comparar_palias(users, ali);

		if((comparacion==0) && (users[calias].estado == 0))
		{		//en esta zona comprobamos en caso de que ya se tenga un registro de ususario previo inactivo, simplemente se deja activo de nuevo
				printf("El usuario esta inactivo\nDar alta nuevamente S/N?\n");
				scanf("%c", &ch);
				if((ch=='S') || (ch=='s'))
				{
					users[nro_usr-1].estado = 1;
				}

		} else if(comparacion==0)
			{
				printf("El Alias ingresado ya existe, elija otro\n");
				printf("Presione cualquier tecla para continuar\n");
				getchar();
			} else
				{
					users[nro_usr-1].alias = ali;
					users[nro_usr-1].nombre = ing_nombre();
					users[nro_usr-1].estado = 1;
					users[nro_usr-1].apellido = ing_apellido();
					users[nro_usr-1].edad = ing_edad();

					getchar();
					printf("\nConfirmar datos S/N?");
					scanf(" %c", &confirmar);

						if(confirmar=='N' || confirmar=='n')
							{
								inicializo_users(users, nro_usr-1);
							} else {
								getchar();
								printf("Presione cualquier tecla para continuar.");
								getchar();
									}
				}
	} else {
		getchar();
		printf("El numero de usuario ya existe, elija otro.\n");
		printf("Presione cualquier tecla para continuar\n");
		getchar();
	}
}
//Funcion usada para dar baja a usuarios en menu gestion
void Baja(usuario users[])
{
    char confirma;
    system("clear");
    printf("\nDar de baja a usuario\n");
    int nro_Usr = Nro_Usr();

    if (users[nro_Usr-1].nombre.largo_palabra!=0)
    {
        getchar();
        printf("\nDatos del usuario nro. %d ",nro_Usr);
        Muestro_alias(users, nro_Usr-1);
        Muestro_nombre(users, nro_Usr-1);
        Muestro_apellido(users, nro_Usr-1);
        Muestro_edad(users, nro_Usr-1);

        printf("\nDesea dejar inactivo al usuario (S/N) ");
        scanf("%c",&confirma);
        if ((confirma == 'S') || (confirma == 's'))
        {
            users[nro_Usr-1].estado=0;
            printf("\nEl usuario ha quedado inactivo");
        } else
			{
				printf("\nNO se dio la baja datos.");

			}
    }
    else
    {
        printf("\nUsuario NO existe");

    }
    getchar();
    printf("\nPresione cualquier tecla para continuar");
    getchar();

}
//Muestra lista de usuarios
void listado_usuarios(usuario users[])
{
    system("clear");
    printf("\nLista de Usuarios\n");

	int i;

	for (i=0;i<CANT_USR;i++)
	{
		if (users[i].alias.largo_palabra!=0 && users[i].estado==1)
		{
			getchar();
			printf("\nDatos del jugador nro. %d ",i+1);
			Muestro_alias(users, i);
			Muestro_nombre(users, i);
			Muestro_apellido(users, i);
			Muestro_edad(users, i);

			printf("\nEstado del jugador: Activo\n");
			printf("\nPresione cualquier tecla para ver siguiente\n");
        }
    }

    printf("\nFin de listado\n");
    printf("\nPresione cualquier tecla para continuar\n");
    getchar();


}
//esta funcion la usamos para evitar que el jugador pueda jugar sin haberse registrado.
int comparo(cadena n1,usuario users[], int nro_usr)
{
    int x;
    int igual = 0;
    if ((n1.largo_palabra != (users[nro_usr-1].alias.largo_palabra)) && ((users[nro_usr-1].alias.largo_palabra != 0) && (users[nro_usr-1].estado == 1)))
    {
        igual = 1;
    }
    else
    {
        for (x=0; x<n1.largo_palabra; x++)
        {
            if (n1.palabra[x] != users[nro_usr-1].alias.palabra[x])
            {
                igual = 1;
                x = n1.largo_palabra;
            }
        }
    }
    return igual;
}
//funcion para comparar dos cadenas. En este caso se usa para los alias.
int comparo_ali(cadena c1, usuario users[]) {
	int x,igual = 0, pos = comparar_palias(users, c1);
	if(c1.largo_palabra == users[pos].alias.largo_palabra) {
		igual = 1;
	} else {
		for(x=0; x<c1.largo_palabra; x++) {
			if(c1.palabra[x] == users[pos].alias.palabra[x]) {
				igual = 1;
				x = c1.largo_palabra;
			}
		}
	}
	return igual;
}

//se usa al inicio de cada juego
void ing_ini_juego(juegos games[])
{

	system("clear");
	int nro_usr, num_ali;
	cadena ali;

	printf("Iniciando juego...\n");
	ali = ing_alias();
	num_ali = comparo_ali(ali, users);

    //si el resutado de "res" es 1 indica que el usuario no se registro y no podra jugar
		if(num_ali == 0) {
            nro_usr = Nro_Usr();
			games[nro_usr-1].alias = ali;
			games[nro_usr-1].fecha_juego = ing_fecha();
			games[nro_usr-1].hora_juego = ing_hora();
			games[nro_usr-1].resultado = resultado;
			valor = 1;
			getchar();
			printf("Presione cualquier tecla para continuar.");
			getchar();
		} else {
			printf("Numero de usuario o alias no registrados.\n\n");
			printf("Presione cualquier tecla para continuar.");
			getchar();
		}
}
//Muestra lista de juegos
void listado_juegos(juegos games[])
{
	system("clear");
	printf("Lista de juegos\n");

	int i;
	for(i=0; i<CANT_P; i++)
	{
		if(games[i].alias.largo_palabra !=0)
		{
			getchar();
			printf("Juego nro. %d ", i+1);
			Muestro_alias_j(games, i);
			Muestro_fecha(games, i);
			Muestro_hora(games, i);
			Muestro_resultado(games, i);


			printf("Presione cualquier tecla para ver siguiente\n");
		}
	}
	printf("Fin de listado\n");
	printf("Presione cualquier tecla para ver siguiente\n");
	getchar();
}

//Muestra instrucciones de juego.
void instrucciones()
{
    printf("Las instrucciones para jugar 2048 son las siguientes::\n");
    printf("Para mover los bloques ingresa:\nw para mover arriba\na para mover izquierda\nd para mover derecha\ns para mover abajo\ny q para salir del juego.\n");
    printf("Cuando dos blockes con el mismo numero se chocan, se unen sumando sus valores.\nPara ganar se debe formar el numero 2048 en un bloque.\n");
}

//Random inicial
int random_num(int x)
{
    int ini;
	ini=rand()%x + 1;
	return ini;
}

//Chequea si el tablero esta lleno, busca espacios vacios (ceros=0)
int chequear_lleno()
{
    int i,j,aux_lleno=1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(tab[i][j]==0)
			{
				aux_lleno=0;
				break;
			}
		}
	}
	return aux_lleno;
}

//Deberia generar nuevos bloques despues de cada movimiento.
void generar_nuevo_num()
{
    int i,j,y,aux=1;
	if(!chequear_lleno())
	{
		while(aux)
		{
			i=random_num(4);
			j=random_num(4);
			if(tab[i][j]==0)
			{
				y=rand()%10+0;
				if(y<6)
				{
					tab[i][j]=2;
				}
				else
				{
					tab[i][j]=4;
				}
				aux=0;
			}
		}
	}
}

//Inicia el tablero
void inicializar_tab()
{
    int i,j;

    for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			tab[i][j]=0;
        }
	}
	//Esto es para que al inicio tengamos dos bloques.
	i=random_num(3);
	j=random_num(3);
	tab[i][j]=2;
    i=random_num(3);
	j=random_num(3);
	tab[i][j]=2;
	pantalla();
}

//Muestra tablero en pantalla
void pantalla()
{
    printf("\n\t\t\t 2048\n\n");
    printf("\t\t  Creado por Jonathan Melo\n\n");
    printf("  Puntos :: %d\n", puntos);

    int i,j;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            printf("%8d%6c%6c", tab[i][j], '|', ' ');
        }
    }
        printf("\n\n\n");
        printf("\tw\t\t\t\t^\na\ts\td\t\t<\tv\t>\n");
}

//Movimientos posibles
void mover_arriba()
{
    int i,j,k;

    for(i=0;i<4;i++) //Recore todo el arreglo
	{
		for(j=0;j<4;j++)
		{
			if(!tab[i][j]) //Si esta vacio
			{
				for(k=i+1;k<4;k++) //Busca un elemento que no sea cero (0)
				{
					if(tab[k][j])
					{
						tab[i][j]=tab[k][j]; //Mueve el eemento que no es un cero al espacio vacio
						tab[k][j]=0; //Asigna el elemento que no era cero a cero.
						break;
					}
				}
			}
		}
	}
}

void mover_abajo()
{
    int i,j,k;

    for(i=0;i<4;i++)
	{
		for(j=3;j>=0;j--)
		{
			if(!tab[j][i])
			{
				for(k=j-1;k>=0;k--)
				{
					if(tab[k][i])
					{
						tab[j][i]=tab[k][i];
						tab[k][i]=0;
						break;
					}
				}
            }
        }
    }
}

void mover_izq()
{
    int i,j,k;

    for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(!tab[i][j])
			{
				for(k=j+1;k<4;k++)
				{
					if(tab[i][k])
					{
						tab[i][j]=tab[i][k];
						tab[i][k]=0;
						break;
					}
				}
			}

		}
	}
}

void mover_der()
{
    int i,j,k;

    for(i=0;i<4;i++)
	{
		for(j=3;j>=0;j--)
		{
			if(!tab[i][j])
			{
				for(k=j-1;k>=0;k--)
				{
					if(tab[i][k])
					{
						tab[i][j]=tab[i][k];
						tab[i][k]=0;
						break;
					}
				}
			}
		}
	}
}

//Calculo para cada movimiento
void sum_arriba()
{
    int i,j;

    for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			if(tab[j][i] && tab[j][i]==tab[j+1][i] )            //Chequea que el bloque no sea un cero y
						{                                       //que el bloque adyasente sea igual
							tab[j][i]=tab[j][i] + tab[j+1][i];  //agrega como primer elemento o lo duplica
							tab[j+1][i]=0;                      //pone a cero
							puntos+=tab[j][i];
							puntos_anteriores+=tab[j][i];
						}
		}
	}
}

void sum_abajo()
{
    int i,j;

    for(i=0;i<4;i++)
	{
		for(j=3;j>0;j--)
		{
					if(tab[j][i] && tab[j][i]==tab[j-1][i])
					{
						tab[j][i]=tab[j][i] + tab[j-1][i];
						tab[j-1][i]=0;
						puntos+=tab[j][i];
						puntos_anteriores+=tab[j][i];
					}
		}
	}
}

void sum_izq()
{
    int i,j;

    for(i=0;i<4;i++)
	{
		for(j=0;j<3;j++)
		{
			if(tab[i][j] && tab[i][j]==tab[i][j+1])
						{
							tab[i][j]=tab[i][j] + tab[i][j+1];
							tab[i][j+1]=0;
							puntos+=tab[i][j];
							puntos_anteriores+=tab[i][j];
						}
		}
	}
}

void sum_der()
{
    int i,j;

    for(i=0;i<4;i++)
	{
		for(j=3;j>0;j--)
		{
			if(tab[i][j] && tab[i][j]==tab[i][j-1])
			{
				tab[i][j]=tab[i][j] + tab[i][j-1];
				tab[i][j-1]=0;
				puntos=puntos + tab[i][j];
				puntos_anteriores+=tab[i][j];
			}
		}
	}
}

//Calcula si se logro el valor maximo (2048)
int calcular_max()
{
    int i,j;
	int max=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(tab[i][j]>max)
			{
				max=tab[i][j];
			}
		}
	}
	return max;
}

//Funcion que realiza las jugadas
void jugar()
{
	char op,ch;
	inicializar_tab();
	printf("Ingresa tu movimiento: ");
	scanf("%c", &op);

	while((op=='w' || op=='a' || op=='s' || op=='d' || op=='q'))
	{

	switch(op)
	{
		case 'w': //arriba
			backup_tab();
			puntos_anteriores=0;
			mover_arriba();
			sum_arriba();
			mover_arriba();

				if(chequear_lleno())
				{
					respuesta= -1;
					break;
				} else if(movimiento())
					{
						generar_nuevo_num();
						system("clear");
						pantalla();

						break;
					} else
						{
							respuesta= 0;
							break;
						}
			break;
		case 's': //abajo
			backup_tab();
			puntos_anteriores=0;
			mover_abajo();
			sum_abajo();
			mover_abajo();

				if(chequear_lleno())
				{
					respuesta= -1;
					break;
				} else if(movimiento())
					{
						generar_nuevo_num();
						system("clear");
						pantalla();
						break;
					} else
						{
							respuesta= 0;
							break;
						}
			break;
		case 'a': //izquierda
			backup_tab();
			puntos_anteriores=0;
			mover_izq();
			sum_izq();
			mover_izq();

				if(chequear_lleno())
				{
					respuesta= -1;
					break;
				} else if(movimiento())
					{
						generar_nuevo_num();
						system("clear");
						pantalla();
						break;
					} else
						{
							respuesta= 0;
							break;
						}
			break;
		case 'd': //derecha
			backup_tab();
			puntos_anteriores=0;
			mover_der();
			sum_der();
			mover_der();

				if(chequear_lleno())
				{
					respuesta= -1;
					break;
				} else if(movimiento())
					{
						generar_nuevo_num();
						system("clear");
						pantalla();
						break;
					} else
						{
							respuesta= 0;
							break;
						}
			break;
		case 'q':
			printf("Esta seguro que decea salir del juego?\nPreciona -Y- para salir o -N- para continuar\n");

			getchar();
			ch=getchar();
				if(ch=='y')
				{
					pantalla_fin_juego();
					resultado= -1;
					break;
				} else {
					pantalla();
						}
			break;
    }

    //Control si se logro 2048
	int buscar_max=calcular_max();
	if(buscar_max==2048) //Preguntamos si se logro 2048
	{
		ganar_pantalla(); //Si se logro 2048 mostramos mensaje, ganaste.
		resultado = 1;
		break;
	}
		if(chequear_lleno()) //Se pregunta si esta lleno el tablero
		{
            if(fin()) //Preguntamos si esta lleno, si no quedan mas jugadas
			{
				perder_pantalla(); //Si no quedan mas jugadas mostramos mensaje, perdiste
				resultado = 0;
				break;
			}
		}
            printf("Ingresa tu movimiento: ");
            op=getchar();

		while((op!='w' && op!='s'  && op!='d'  && op!='a' && op!='q')) //Controlamos si se presiona una tecla no valida
		{
            scanf("%c", &op);
		}
	}
}

int movimiento()
{
	int i,j,k=0;
		for(i=0; i<4; i++)
		{
			for(j=0; j<4; j++)
			{
				if(btab[i][j]!=tab[i][j])
				{
					k=1;
					break;
				}
			}
		} return k;
}

void backup_tab()
{
	int i,j;
	for(i=0; i<4; i++)
	{
		for(j=0; j<4;j++)
		{
			btab[i][j]=tab[i][j];
		}
	}
}

void pantalla_fin_juego() {

    system("clear");
    printf("Tu puntuacion final es: %d\n", puntos);
    printf("Gracias por jugar\nHasta la proxima.\n\n\n");
    exit(0);
}

//Muestra mensaje cuando se gana
void ganar_pantalla()
{
    char opc;
	printf("\t\t\tHAS GANADO!!!\n\n");
	printf("Tu puntuacion es: %d\n\n", puntos);
	printf("Quieres seguir jugando???\n");
	printf("s/n\n\n");

    getchar();
    opc=getchar();

	while(opc=='n')
        {
            pantalla_fin_juego();
            break;
        }
            while(opc !='n')
                {
                    jugar();
                }
}

//Muestra mensaje cuando se pierde
void perder_pantalla()
{
    char opc;
    system("clear");
	printf("\t\t\tHAS PERDIDO!!!\n\n");
	printf("Tu puntuacion final es: %d\n\n", puntos);
	printf("Quieres seguir jugando???\n");
	printf("s/n\n\n");

	getchar();
    opc=getchar();

	while(opc=='n')
        {
            pantalla_fin_juego();
            break;
        }
            while(opc !='n')
                {
                    jugar();
                }
}

//Controla si se lleno el tablero buscando si ya no quedan movimientos posibles.
int fin()
{
    int i,j,aux=1;

		for(i=0;i<4;i++)
		{
			for(j=0;j<3;j++)
			{
				if(tab[i][j]==tab[i][j+1])
				{
					aux=0;
					break;
				}
			}
			if(aux==0)
			{
				break;
			}
		}
		if(aux==1)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					if(tab[i][j]==tab[i+1][j])
					{
						aux=0;
						break;
					}
				}
				if(aux==0)
				{
					break;
				}
			}
		}

	return aux;
 }



