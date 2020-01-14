#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define PATH "PATH"
#define PWD "PWD"
#define HOME "HOME"

void fail(const char *const msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}
void fail_errno(const char * const msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void *my_malloc(size_t size)
{
    void *result = malloc(size);
    if (!result)
        fail_errno("Cannot allocate memory with malloc");
    return result;
}

void *my_realloc(void *ptr, size_t size)
{
    void *result = realloc(ptr, size);
    if (!result)
        fail_errno("Cannot re-allocate memory");
    return result;
}

void yyerror(void *scanner, const struct shell * const sh, struct node ** const cmd, char const * const msg)
{
    fprintf (stderr, "Parsing error: %s\n", msg);
}

char *my_strdup(const char * const s) {
    char *result = strdup(s);
    if (!result)
        fail_errno("Cannot allocate memory for strdup");
    return result;
}


void stampaPrompt(){

}

void leggiRiga(){

}
void leggiFile(){

}



/*bool isCd(char *comando){
    return( strncmp(comando, "cd", 2)==0 );
        //fail(strcat("errore: il comando %s non esiste", comando));
}*/

char * pwd(){
    char *cwd;
    cwd = getcwd(NULL, 0); //getcwd() allocates the buffer dynamically using malloc(3) if buf is NULL
    if(cwd==NULL)
        fail_errno("Error work");
    //free(cwd);
    return cwd;
}
void cd(char *path){
    if(path==NULL)
        chdir(HOME);
    if(chdir(path) == -1)
        fail_errno("Error: cannot change working directory");
}

void terminaStringa(char *path){
	char *pos;
	if ((pos=strchr(path, '\n')) != NULL) //se path termina con \n lo sostituisco con '\0'
			*pos = '\0';
}

int main(int argc, char **argv) {
	int MAX=50;
	FILE *stream=stdin;
	int flag=1;
	while(flag){
	    printf("%s $ ", pwd());
	    char *line=my_malloc(MAX*sizeof(char));
	    fgets(line, MAX, stream);
		//printf("FGETS: %s\n", line);
		if(strncmp(line, "cd", 2)==0){
			char *path=my_malloc(strlen(line));
			for(int i=3; i<strlen(line); ++i){
				path[i-3]=line[i];
			}
			terminaStringa(path);
			//printf("PATH E' >%s< $ \n", path);
			cd(path);
			free(path);
	    	//printf("%s $ \n", pwd());
		}else{
		
			char* comand[10]={};
			//char* comand=my_malloc(10*sizeof(char));
			//strcpy(comand,line);
			char* rest = line;
			int i=0;
			do{
				comand[i]=my_malloc(10*sizeof(char));
				sprintf(comand[i], "%s", strtok_r(rest, "|", &rest));
				terminaStringa(comand[i]);
				++i;
			}while(comand[i-1]!=NULL&&i<10);
			for(int i=0; i<10; ++i){
				printf("comand%d = %s\n", i, comand[i]);
				//free(arg[i]);
			}
			printf("LINE = %s\n", line);
			char* arg[10]={};
			//char* comandTemp=my_malloc(10*sizeof(char));
			//strcpy(comandTemp,comand);
			int k=0;
			while(comand[k]!=NULL&&k<5){
				char* rest2 = comand[i];
				++k;
				i=0;
				do{
					arg[i]=my_malloc(10*sizeof(char));
					sprintf(arg[i], "%s", strtok_r(rest2, " ", &rest2));
					terminaStringa(arg[i]);
					++i;
				}while(arg[i-1]!=NULL&&i<10);
				for(int i=0; i<10; ++i){
					printf("arg%d = %s\n", i, arg[i]);
					//free(arg[i]);
				}
			}
			
			//terminaStringa(arg[0]); //se path termina con \n lo sostituisco con '\0'
			/*i=0;
			while(arg[i]!=NULL&&i<9){
			
				if(strncmp(arg[i], "$", 1)==0){
					char *pathvar;
					pathvar = getenv(arg[i]+1);
					if(pathvar==NULL){
						if(setenv(arg[i]+1,"ciao",0)<0)
							fail_errno("Error: cannot set the variable");
						pathvar = getenv(arg[i]+1);
					}
					arg[i]=pathvar;
					printf("1pathvar=%s ",pathvar); printf("Argomento: %s\n", arg[i]);
				}
				
				if(strncmp(arg[i], "<", 1)==0){
				
				}
				if(strncmp(arg[i], ">", 1)==0){
				
				}
				printf("Comando: %s\n", comand[0]);
				//printf("Argomento: %s\n", arg[i]);
				//arg[i] = strtok_r(NULL, " ", &rest2);
				//printf("Argomento: %s\n", arg[i]);
				++i;
			}*/
			//free(arg);
			//free(comand);
		}
		free(line);
	}
    return 0;
}
