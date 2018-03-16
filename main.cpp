#include <iostream>
using namespace std;
#include <stdio.h>

#include <stdlib.h>		/*malloc()*/
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define MAX	1000
string DiaNLateX[]={
       "Domingo",          //0
       "Lunes",            //1
       "Martes",           //2
       "Mi\\'{e}rcoles",   //3
       "Jueves",           //4
       "Viernes",          //5
       "S\\'abado"         //6
};
string MesNLateX[]={
       "Enero",
       "Febrero",
       "Marzo",
       "Abril",
       "Mayo",
       "Junio",
       "Julio",
       "Agosto",
       "Septiembre",
       "Octrubre",
       "Noviembre",
"Diciembre"};
struct myFecha{
       int d, m, a;
};

struct fechaFAT12{
	unsigned dia : 5;
	unsigned mes : 4;
	unsigned anio: 7;
}__attribute__((packed));
typedef struct fechaFAT12 FechaFAT12;

struct fecha{
	int d;
	int m;
	int a;
};

struct archivo{
	char name[12];
	FechaFAT12 fechF12;
};//end struct archivo

string DIA[]={"Domingo","Lunes","Martes","Mi\\'ercoles",
               "Jueves","Viernes","S\\'abado"};
string MES[]={"enero","febrero","marzo","abril","mayo","junio"};

string get_nombre_dia(int);
void get_fecha(FechaFAT12 *,fecha *);
int algoritmo(fecha *F);
int inicio_mes(int mes, int anio);  //Se usa en algoritmo()
void fecha2FechaFAT2(fecha *,FechaFAT12 *);

/**
 * Colocar en el arreglo name el nombre de archivo 
   de acuerdo con el formado FAT12. Por ejemplo:
   SETUP.BIN deber\'a ``convertirse'' a 'SETUP    BIN'
 */
void convert_name2FAT12(string filename,char name[MAX]);
void fill_archivo(string stringNombreDArchivo,
                  struct fecha *fechaPt,
				  struct archivo *archivoPt);

int main(int argc, char** argv) {
#ifdef PRUEBAS_ANTERIORES
	FechaFAT12 fF;fF.dia=7;fF.mes=3;//fF.anio=0b1010101;
	fF.anio=2018-1980;
	
	fecha f;
	get_fecha(&fF,&f);
//	cout<<DIA[algoritmo(&f)]<<" "<<f.d<<" de "<<MES[f.m-1]
//	    <<" de "<<f.a<<endl;
	for(f.d=1;f.d<=31;f.d++){
		cout<<DIA[algoritmo(&f)]<<" "<<f.d<<" de "<<MES[f.m-1]
	    <<" de "<<f.a<<endl;
	}
	f.d--;
	string str=DIA[algoritmo(&f)];
	cout<<str<<" "<<f.d<<endl;
	if(str==DIA[6]){
		cout<<DIA[6]<<endl;
	}else{
		cout<<"????"<<endl;
	}
	string filen="documdocumdocum.doc";
	char buftmp[MAX];
	cout<<filen<<endl;
	convert_name2FAT12(filen,buftmp);
	for(int i=0;i<12;i++)
	  cout<<buftmp[i];
	cout<<endl<<endl;
	
	filen="file.doc";
	cout<<filen<<endl;
	convert_name2FAT12(filen,buftmp);
	for(int i=0;i<12;i++)
	  cout<<buftmp[i];
	cout<<endl<<endl;
	
	
	filen="file.docx";
	cout<<filen<<endl;
	convert_name2FAT12(filen,buftmp);
	for(int i=0;i<12;i++)
	  cout<<buftmp[i];
	cout<<endl<<endl;
	
	filen="filefilefilefile.doc";
	cout<<filen<<endl;
	convert_name2FAT12(filen,buftmp);
	for(int i=0;i<12;i++)
	  cout<<buftmp[i];
	cout<<endl<<endl;
	
	filen="filefilefilefile.docx";
	cout<<filen<<endl;
	convert_name2FAT12(filen,buftmp);
	for(int i=0;i<12;i++)
	  cout<<buftmp[i];
	cout<<endl<<endl;
	
	filen="filefilefilefile.d";
	cout<<filen<<endl;
	convert_name2FAT12(filen,buftmp);
	for(int i=0;i<12;i++)
	  cout<<buftmp[i];
	cout<<endl<<endl;
#endif /*PRUEBAS_ANTERIORES*/
	string file_name="data_source.txt";
	struct fecha *hoy=(struct fecha*)malloc(sizeof(struct fecha));
	hoy->d=14;hoy->m=3;hoy->a=2018;
	struct archivo archivo1;
	fill_archivo(file_name,hoy,&archivo1);
	printf("Nombre del archivo:%s\n",file_name.c_str());
	for(int i=0;i<12;i++){
		printf("%c",archivo1.name[i]);
	}
	printf("\n");
	struct fecha fechaObtenida;
	get_fecha(&(archivo1.fechF12),&fechaObtenida);
	cout<<DIA[algoritmo(&fechaObtenida)]<<" "
	    <<fechaObtenida.d<<" de "<<MES[fechaObtenida.m-1]
	    <<" de "<<fechaObtenida.a<<endl;
	
	return 0;
}//end main()

/**obtener los campos de la struct fecha a partir de los campos 
  *de la struc FechaFAT12.
  */
void get_fecha(FechaFAT12 *f_FAT12,fecha *fechaPt){
	fechaPt->d=f_FAT12->dia;
	fechaPt->m=f_FAT12->mes;
	fechaPt->a=f_FAT12->anio+1980;
}

/**
  La funci\'on algoritmo fue proporcionada por
  Jose Luis <secondnames>
*/
int algoritmo(fecha *F){
    int t, inM;
    inM=inicio_mes(F->m,F->a);
    t= ((F->a-1)*365+((F->a-1)/4-3*((F->a-1)/100+1)/4)%7+inM+F->d%7)%7;
    return t;
    }

/**
  La funci\'on algoritmo fue proporcionada por
  Jose Luis <secondnames>
*/
int inicio_mes(int mes, int anio)
{
    if (anio%4!=0){
    switch(mes)
    {
               case 1:
                    return 0;
               case 2:
                    return 3;
               case 3:
                    return 3;
               case 4:
                    return 6;
               case 5:
                    return 1;
               case 6:
                    return 4;
               case 7:
                    return 6;
               case 8:
                    return 2;
               case 9:
                    return 5;
               case 10:
                    return 0;
               case 11:
                    return 3;
               case 12:
                    return 5;
               }
    }else
    {
         switch(mes)
         {
               case 1:
                    return 0;
               case 2:
                    return 3;
               case 3:
                    return 4;
               case 4:
                    return 0;
               case 5:
                    return 2;
               case 6:
                    return 5;
               case 7:
                    return 0;
               case 8:
                    return 3;
               case 9:
                    return 6;
               case 10:
                    return 1;
               case 11:
                    return 4;
               case 12:
                    return 6;
               }
         }
}


void convert_name2FAT12(string filename,char name[MAX]){
  char tmp[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
  cout<<"filename.length()="<<filename.length()<<endl;
  int i=0;
  //Obtenemos el sufijo como los char despu\'es del punto
  while((filename[i]!='.')&&(i<filename.length())){
//  	tmp[i]=filename[i];
  	i++;
  }
  string sufijo=filename.substr(i+1,filename.length()-1);
  i=0;
  while((filename[i]!='.')&&(i<8)){
  	tmp[i]=filename[i];
  	i++;
  }
  string prefijo=filename.substr(0,i);
  
//  cout<<prefijo<<endl;
//  cout<<sufijo<<endl;
  int j=9;
  while((j<12)&&(j-9<sufijo.length())){
  	tmp[j]=sufijo[j-9];
  	j++;
  }
  
//  cout<<endl;
  for(int k=0;k<12;k++){
//    cout<<tmp[k];
    name[k]=tmp[k];
  }
//  cout<<endl;
}

void fecha2FechaFAT2(fecha *fecha_ptr,FechaFAT12 *FechaFAT12_ptr){
	FechaFAT12_ptr->dia=fecha_ptr->d;
	FechaFAT12_ptr->mes=fecha_ptr->m;
	FechaFAT12_ptr->anio=fecha_ptr->a-1980;
}

/**Cumplimentar los datos de la estructura archivo a 
   partir de la informaci\'on proporcionada con los 
   par\'ametros stringNombreDArchivo y fechaPt.
*/
void fill_archivo(string stringNombreDArchivo,
                  struct fecha *fechaPt,
				  struct archivo *archivoPt){
  	// Ejercicio 2018.03.14	
  	char array[MAX];
	convert_name2FAT12(stringNombreDArchivo,array);
	for(int i=0;i<12;i++){
		archivoPt->name[i]=array[i];
	}									
	fecha2FechaFAT2(fechaPt,&archivoPt->fechF12);
}

















