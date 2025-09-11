#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ol 120
#define fichero "gnd2"

void clean_stdin();
void cargar(char **, int *);
char cmp(char *x, char *y);
int nlineas();
void mostrar(char **, int *);
void split(char *, char [][ol], int *);
void buscar(char **, int *);
int cmpeq(char t[], char s[]);
int menu();
void ingresar(char **, int *r);
void borrar(char **, int *);
void ordenar(char **, int *);
void guardar(char **, int, int *);

int main(int argc, char *argv[])
{
	int op=0, r, i;
	char **c;

	r=nlineas();

	c=(char **)malloc(r*sizeof(char *));

	for(i=0;i<r;i++)
		*(c+i)=(char *)malloc(ol*sizeof(char));

	cargar(c, &r);

	if(argc<2)
	{

		do
		{
			op=menu();
			switch(op)
			{
				case 0:
					printf("Salimos!\n");
					break;

				case 1:
					buscar(c, &r);
					break;

				case 2:
					mostrar(c, &r);
					break;

				case 3:
					ingresar(c, &r);
					break;

				case 4:
					borrar(c, &r);
					break;
			}

		}while(op!=0);
	}
	else
	{
		if(argc==2 && argv[1][0]=='-' && argv[1][1]=='l')
			mostrar(c, &r);


		if(argc==2 && argv[1][0]=='-' && argv[1][1]=='q')
			buscar(c, &r);


		if(argc==2 && argv[1][1]!='l' && argv[1][1]!='q')
		{
			printf("ayuda: ");
			printf(" -l listar, -q buscar\n");
		}

		if(argc>2)
		{
			printf("ayuda: ");
			printf(" -l listar, -q buscar\n");
		}
	}

	for(i=0;i<r;i++)
		free(*(c+i));
	free(c);

	return 0;
}

char cmp(char *x, char *y)
{
	char a[2][30]; // filas y columnas ó renglones y cantidad de
	int i=0, j=0, k, l, len;	// caracteres por renglon.
	int r=0;

	strcpy(a[0], x);
	strcpy(a[1], y);

	if(strlen(a[0])<strlen(a[1])) len=strlen(a[0]);
	else len=strlen(a[1]);

	k=0, l=0, i=0, j=0;

	do
	{
		if((int)a[j][i]==(int)a[j+1][i] && k==0)
		{
			if(i==len-1)
				if(strlen(a[0])>strlen(a[1])) r=1;
		}
		else k=1;

		if(((int)a[j][i] < (int)a[j+1][i]) && l!=1)	l=1;

		if((int)a[j][i]>(int)a[j+1][i] && l!=1)
		{
			r=1;
			k=1;
		}

		i++;

	}while(i<len && l!=1);

	return r;
}

int nlineas()
{

	FILE *fp;
	int r=0;
	char s[ol];

	fp=fopen(fichero, "a+");
	fclose(fp);

	fp=fopen(fichero, "r");

	while(!feof(fp))
	{
		fgets(s, ol-1, fp);
		r++;
	}

	r-=1;

	fclose(fp);

	return r;
}

void mostrar(char **c, int *r)
{
	int i;

	printf("\n* Agenda de Contactos *\n");

	for(i=0;i<*r;i++)
		printf("%d %s", i+1, *(c+i));
}

void split(char *a, char b[][ol], int *k)
{
    int i = 0, j = 0;
    *k = 0;

    while(a[i] != '\0')
    {
        if(a[i] != ' ')
        {
            b[*k][j] = a[i];
            j++;
        }
        else
        {
            b[*k][j] = '\0';
            j = 0;
            *k += 1;
        }
        i++;
    }

    if(j>0)
    {
        b[*k][j] = '\0';
        *k += 1;
    }
}

void buscar(char **c, int *r)
{
	int i=0, j, k;
	int q = 0;
    int *p = &q;
	char s[ol];
    char list[ol][ol];

	printf("Ingrese un nombre a buscar: ");
	scanf("%[^\n]", s);

	for(i=0;i<*r;i++)
	{
	    split(*(c+i), list, p);

	    for(k=0;k<*p;k++)
	    {
	        j=cmpeq(list[k], s);

			if(j==1)
			{
				printf("%d %s", i+1, *(c+i));
				k=*p;
			}
		}
	}

}

int cmpeq(char t[], char s[])
{
	int i=0, cp=0, fd=0, eq=0, len;	// caracteres por renglon.

	if(strlen(s)<strlen(t)) len=strlen(s);
	else len=strlen(t);

	i=0;
	do
	{
		if((int)s[i]==(int)t[i] && cp==0)
		{
			if(i==len-1) // ultimo car. comparable es igual
				if(strlen(t)>=strlen(s))
					eq=1; // tons. defino por tamaño!
		}
		else cp=1; // ya no volver a entrar.

		if(!((int)t[i]==(int)s[i]) && fd!=1) // define
		{				// al primer diferente
			eq=0; // son diferentes
			fd=1; // definido!
		}

		i++;

	}while(i<len && fd!=1);

	return eq;
}

int menu()
{
	int op;

	do
	{
		printf("\n* Agenda de Contactos *\n");
		printf("Salir.................: 0\n");
		printf("Buscar................: 1\n");
		printf("Listar................: 2\n");
		printf("Nuevo.................: 3\n");
		printf("Borrar................: 4\n");
		printf("Opcion................: ");

		scanf("%d", &op);
		clean_stdin();

	}while(op<0 || op>4);

	return op;
}

void ingresar(char **c, int *r)
{
	int m=0;
	char b[ol];
	FILE *fp;

	fp=fopen(fichero, "a+");

	do
	{
		if(m>0) 	printf("Tamaño inadmisible!\n");

		printf("Ingrese el nombre, un espacio y\n");
		printf("el telefono de contacto con guiones: ");
		scanf("%[^\n]", b);
		clean_stdin();
		strcat(b, "\n");
		m=strlen(b)+1;
	}while(m<10 || m>ol);

	fputs(b, fp);

	fclose(fp);

	*r+=1; // inc nlineas() -> *r

	ordenar(c, r);
}


void borrar(char **c, int *r)
{
	int p=0;
	char b[ol];
	char a;

	mostrar(c, r);

	do
	{
		printf("Ingrese el id del contacto a borrar: ");
		scanf("%d", &p);
	}while(p<0 || p>*r);

	a=getchar();

	if(p!=0)	guardar(c, p, r);

	cargar(c, r);
}


void ordenar(char **c, int *r)
{
	int i, w, jl, il, rl;
	char b[ol];

	cargar(c, r);

	w=0; // ordenar de menor a mayor
	jl=0;
	while(jl<*r-1)	// renglones
	{
		il=0;
		while(il<*r-1)	// renglones
		{
			rl=cmp(*(c+il), *(c+il+1));
			if(rl==1) // ==0, ya está de menor a mayor
			{	// ==1, debe ordenarse aún!
				if(w==0)  w=1;
				strcpy(b, *(c+il));
				strcpy(*(c+il), *(c+il+1));
				strcpy(*(c+il+1), b);
			}
			il++;
		}
		jl++;
		w=0;
	}

	guardar(c, 0, r); // escribimos los registros ordenados
}

void cargar(char **c, int *r)
{
	int i=0;
	char s[ol];
	FILE *fp;

	for(i=0;i<*r;i++)
		free(*(c+i));

	*r=nlineas();

	c=(char **)realloc(c, *r*sizeof(char *));
	for(i=0;i<*r;i++)
		*(c+i)=(char *)malloc(ol*sizeof(char));


	fp=fopen(fichero, "r");

	i=0;
	while(!feof(fp))
	{

		fgets(s, ol-1, fp);

		if(i<*r)
		{
			strcpy(*(c+i), s);
			i++;
		}
	}

	fclose(fp);
}

void guardar(char **c, int p, int *r)
{
	int i, q;	// p==0, solo guarda
	FILE *fp;	// p!=0 elimina el registro indicado com p
	if(p!=0)	*r-=1;

	// eliminamos el archivo original
	fp=fopen(fichero, "w");
	fclose(fp);

	fp=fopen(fichero, "a+");

	if(p==0)
	{
		for(i=0;i<*r;i++)
			fputs(*(c+i), fp);
	}
	else
	{
		q=0;
		for(i=0;i<*r;i++)
		{
			if(p-1!=i && q==0)
				fputs(*(c+i), fp);
			else q=1;

			if(q==1)	fputs(*(c+i+1), fp);
		}
	}

	fclose(fp);
}

void clean_stdin()
{
	char c;

	do
	{
		c=getchar();

	}while(c!='\n' && c!='\0');
}

