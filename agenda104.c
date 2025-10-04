#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ol 120
#define fichero "gnd2"

void clean_stdin(void);
char cmp(char *x, char *y);
int nlineas(void);
void mostrar(char **, int *);
void split(char *, char [][ol], int *);
int cmpeq(char t[], char s[]);
int menu(void);
void ingresar(int *r);
void borrar(char **, int *);
void ordenar(char **, int *);
char **cargar(char **, int *r);
void guardar(char **, int, int *);
int contains_ci(const char *hay, const char *needle);
void afinar(char **c, int *indices, int temp_count);
void buscar_add(char **c, int *r);

int main(int argc, char *argv[])
{
	int op=0, r, i;
	char **c = NULL;

	r=nlineas();

	c=(char **)malloc(r * sizeof(char *));
	for(i=0;i<r;i++)
		c[i] = (char *)malloc(ol * sizeof(char));

	c=cargar(c, &r);

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
					buscar_add(c, &r);
					break;
				case 2:
					mostrar(c, &r);
					break;
				case 3:
					ingresar(&r);
					c=cargar(c, &r);
					ordenar(c, &r);
					c=cargar(c, &r);
					break;
				case 4:
					borrar(c, &r);
					break;
			}
		} while(op!=0);
	}
	else
	{
		if(argc==2 && argv[1][0]=='-' && argv[1][1]=='l')
			mostrar(c, &r);

		if(argc==2 && argv[1][0]=='-' && argv[1][1]=='q')
			buscar_add(c, &r);

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
		free(c[i]);
	free(c);

	return 0;
}

char cmp(char *x, char *y)
{
	int i=0, len;
	int r=0;

	len=strlen(x)<strlen(y)? strlen(x): strlen(y);

	for(i=0;i<len;i++)
	{
		if(x[i]==y[i])
		{
			if(i==len-1)
			{
				if(strlen(x)>strlen(y)) r=1;
			}
		}
		else if(x[i]<y[i])
		{
			break;
		}
		else
		{
			r=1;
			break;
		}
	}

	return r;
}

int nlineas(void)
{
	FILE *fp;
	int r=0;
	char s[ol];

	fp=fopen(fichero, "a+");
	if(!fp)
	{
		perror("fopen");
		return 0;
	}
	fclose(fp);

	fp=fopen(fichero, "r");
	if(!fp) return 0;

	while(fgets(s, sizeof s, fp) != NULL)
		r++;

	fclose(fp);

	return r;
}

void mostrar(char **c, int *r)
{
	int i;

	printf("\n* Agenda de Contactos *\n");

	for(i=0;i<*r;i++)
		printf("%d %s", i+1, c[i]);
}

void split(char *a, char b[][ol], int *k)
{
	int i=0, j=0;
	*k=0;

	while(a[i]!='\0')
	{
		if(a[i]!=' ')
		{
			b[*k][j]=a[i];
			j++;
		}
		else
		{
			b[*k][j]='\0';
			j=0;
			*k+=1;
		}
		i++;
	}

	if(j>0)
	{
		b[*k][j]='\0';
		*k+=1;
	}
}

void buscar(char **c, int *r)
{
	int i=0, j, k;
	int q = 0;
	int *p=&q;
	char s[ol];
	char list[ol][ol];

	printf("Ingrese un nombre a buscar: ");
	if(!fgets(s, sizeof s, stdin)) return;
	s[strcspn(s, "\n")] = '\0';

	for(i=0;i<*r;i++)
	{
		split(c[i], list, p);

		for(k=0;k<*p;k++)
		{
			j=cmpeq(list[k], s);

			if(j==1)
			{
				printf("%d %s", i+1, c[i]);
				k=*p;
			}
		}
	}
}

int cmpeq(char t[], char s[])
{
	int i=0, cp=0, fd=0, eq=0, len;

	if(strlen(s)<strlen(t)) len=strlen(s);
	else len=strlen(t);

	i=0;
	do
	{
		if((int)tolower((unsigned char)s[i])==(int)tolower((unsigned char)t[i]) && cp==0)
		{
			if(i==len-1)
				if(strlen(t)>=strlen(s))
					eq=1;
		}
		else cp=1;

		if(!((int)tolower((unsigned char)t[i])==(int)tolower((unsigned char)s[i])) && fd!=1)
		{
			eq=0;
			fd=1;
		}

		i++;

	}while(i<len && fd!=1);

	return eq;
}

int menu(void)
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

		if(scanf("%d", &op)!=1) op = -1;
		clean_stdin();

	}while(op<0 || op>4);

	return op;
}

void ingresar(int *r)
{
	int m=0;
	char b[ol];
	FILE *fp;

	fp=fopen(fichero, "a+");
	if(!fp)
	{
		perror("fopen");
		return;
	}

	do
	{
		if(m>0) printf("Tamaño inadmisible!\n");

		printf("Ingrese el nombre, un espacio y\n");
		printf("el telefono de contacto con guiones: ");

		if(!fgets(b, sizeof b, stdin))
		{
			fclose(fp);
			return;
		}

		b[strcspn(b, "\n")]='\0';
		strcat(b, "\n");
		m=strlen(b)+1;
	}while(m<10 || m>ol);

	fputs(b, fp);
	fclose(fp);

	*r+=1;
}

void borrar(char **c, int *r)
{
	int p=0;

	mostrar(c, r);

	do
	{
		printf("Ingrese el id del contacto a borrar: ");
		if(scanf("%d", &p)!=1) p=0;
		clean_stdin();
	}while(p<0 || p>*r);

	if(p!=0)
		guardar(c, p, r);

	c=cargar(c, r);
}

void ordenar(char **c, int *r)
{
	int w, jl, il, rl;
	char b[ol];

	w=0;
	jl=0;
	while(jl<*r-1)
	{
		il=0;
		while(il<*r-1)
		{
			rl = cmp(c[il], c[il+1]);
			if(rl==1)
			{
				if(w==0) w=1;
				strcpy(b, c[il]);
				strcpy(c[il], c[il+1]);
				strcpy(c[il+1], b);
			}
			il++;
		}
		jl++;
		w=0;
	}

	guardar(c, 0, r);
}

char **cargar(char **c, int *r)
{
	int i=0;
	char s[ol];
	FILE *fp;

	if(c != NULL)
		for(i=0;i<*r;i++)
			free(c[i]);

	*r=nlineas();

	c=(char **)realloc(c, (*r)*sizeof(char *));
	if(c==NULL && *r>0)
	{
		perror("realloc");
		exit(1);
	}

	for(i=0;i<*r;i++)
		c[i] = (char *)malloc(ol*sizeof(char));

	fp=fopen(fichero, "r");
	if(!fp) return c;

	i=0;
	while(fgets(s, ol, fp)!=NULL && i<*r)
	{
		strcpy(c[i], s);
		i++;
	}

	fclose(fp);
	return c;
}

void guardar(char **c, int p, int *r)
{
	int i, q;
	FILE *fp;
	if(p!=0) *r-=1;

	fp=fopen(fichero, "w");

	if(!fp)
	{
		perror("fopen");
		return;
	}
	fclose(fp);

	fp=fopen(fichero, "a+");

	if(!fp)
	{
		perror("fopen");
		return;
	}

	if(p==0)
	{
		for(i=0;i<*r;i++)
			fputs(c[i], fp);
	}
	else
	{
		q=0;
		for(i=0;i<*r;i++)
		{
			if(p-1!=i && q==0)
				fputs(c[i], fp);
			else q=1;
				if(q==1)
					fputs(c[i+1], fp);
		}
	}

	fclose(fp);
}

void clean_stdin(void)
{
	int c;
	do
	{
		c=getchar();
	}while(c!='\n' && c!=EOF);
}

int contains_ci(const char *hay, const char *needle)
{
	if(!hay || !needle) return 0;
	size_t nl = strlen(needle);
	if(nl == 0) return 1;

	for(; *hay; hay++)
	{
		size_t i = 0;
		while(i < nl && hay[i] && tolower((unsigned char)hay[i]) == tolower((unsigned char)needle[i])) {
			i++;
		}
		if(i == nl) return 1;
	}
	return 0;
}

void afinar(char **c, int *indices, int temp_count)
{
	int op=1;
	char s2[ol];
	int *cur=NULL;
	int cur_count=temp_count;

	cur=malloc(temp_count * sizeof(int));
	for(int i=0;i<temp_count;i++)
		cur[i]=indices[i];

	while(op!=0 && cur_count>0)
	{
		do{
			printf("\n* busqueda adicional *\n");
			printf("Afina.................: 1\n");
			printf("Volver................: 0\n");
			printf("Opción................: ");
			if(scanf("%d", &op)!=1)
				op=0;
			clean_stdin();
		}while(op!=0 && op!=1);

		if(op==1)
		{
			printf("Ingrese el siguiente texto a buscar: ");
			if(!fgets(s2, sizeof s2, stdin)) break;
			s2[strcspn(s2, "\n")] = '\0';

			int *next = NULL, next_count = 0;
			for(int i=0;i<cur_count;i++)
				if(contains_ci(c[cur[i]], s2))
				{
					next = realloc(next, (next_count+1)*sizeof(int));
					next[next_count++] = cur[i];
				}

			if(next_count==0)
			{
				printf("No se encontraron coincidencias al afinar.\n");
				free(next);
			}
			else
			{
				for(int j=0;j<next_count;j++)
					printf("%d %s", next[j]+1, c[next[j]]);
				free(cur);
				cur=next;
				cur_count=next_count;
			}
		}
	}

	free(cur);
}

void buscar_add(char **c, int *r)
{
	char s1[ol];
	int *indices = NULL;
	int temp_count = 0;

	printf("Ingrese un nombre a buscar: ");
	if(!fgets(s1, sizeof s1, stdin)) return;
	s1[strcspn(s1, "\n")] = '\0';

	for(int i=0;i<*r;i++)
	{
		if(contains_ci(c[i], s1))
		{
			indices=realloc(indices, (temp_count+1)*sizeof(int));
			indices[temp_count++] = i;
		}
	}

	if(temp_count==0)
	{
		printf("No se encontraron resultados para \"%s\"\n", s1);
		free(indices);
		return;
	}

	for(int j=0;j<temp_count;j++)
		printf("%d %s", indices[j]+1, c[indices[j]]);

	afinar(c, indices, temp_count);

	free(indices);
}
