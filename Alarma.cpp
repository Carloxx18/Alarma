#include <iostream>	
#include <stdlib.h>
#include <fstream>

using namespace std;

struct ALARMA
{
	char id[10]="";
	char nombre[20]="";
	char hora[10]="";
};

void agregar_alarma(){
	ofstream archivo_alarma ("alarmas.dat", ios::app);
	ALARMA alarma;

	cin.ignore();
	cout<<"Ingrese el ID de la alarma: "<<endl;
	cin.getline(alarma.id,10);

	cout<<"Ingrese el nombre de la alarma: "<<endl;
	cin.getline(alarma.nombre,20);

	cout<<"Ingrese la hora de la alarma: "<<endl;
	cin.getline(alarma.hora,10);
	
	archivo_alarma.write((char *)&alarma,sizeof(alarma));
	
	
	archivo_alarma.close();
	
}
//----------------------------------------------------------------------------
void ver_alarmas(){
	
	system("cls");
	struct ALARMA alarma;
	
	ifstream ver_archivo("alarmas.dat");
	ver_archivo.read((char *)&alarma,sizeof (alarma));
	
	cout<<"\t\t__________________________ALARMAS_________________________"<<endl<<endl;
	while(ver_archivo&& !ver_archivo.eof()){
	
	cout<<"\t\t"<<alarma.id<<"  "<<alarma.nombre<<"  "<<alarma.hora<<endl;
	ver_archivo.read((char *)&alarma,sizeof (alarma));
	}
}
//-------------------------------------------------------------------------
int alarmalocalizada(string buscarid){
	struct ALARMA alarma;
	int counter = 0;
	string bufferid;
	
	ifstream ver_archivo("alarmas.dat");
	ver_archivo.read((char *)&alarma,sizeof (alarma));
	
	while(ver_archivo && !ver_archivo.eof()){
		counter++;
		bufferid=alarma.id;
		if(buscarid==bufferid){
			cout<<"alarma encontrada: "<<alarma.nombre<<endl;
			cout<<"Presione cualquir tecla para continuar"<<endl;
			return counter;
		}
		ver_archivo.read((char *)&alarma,sizeof (alarma));
	}
	ver_archivo.close();
	return 0;
}
//------------------------------------------------------------------------------
bool cambiaralarma(int ubicacion){
	
	try{
		struct ALARMA alarma;
		cin.ignore();
	cout<<"Ingrese el ID de la alarma: "<<endl;
	cin.getline(alarma.id,10);

	cout<<"Ingrese el nombre de la alarma: "<<endl;
	cin.getline(alarma.nombre,20);

	cout<<"Ingrese la hora de la alarma: "<<endl;
	cin.getline(alarma.hora,10);
	
	fstream modificararchivo("alarmas.dat");
	modificararchivo.seekp((ubicacion-1) * sizeof (alarma),ios::beg);
	modificararchivo.write((char *)&alarma,sizeof (alarma));
	modificararchivo.close();
	return true;
	
	}catch(exception e){
		cout<<"ERROR"<<e.what();
		return false;
	}
}
//----------------------------------------------------------------------------
void modificar_alarma(){
	char buscarid[10];
	int ubicacion=0;
	system("cls");
	
	ver_alarmas();
	cin.ignore();
	cout<<endl<<"Ingrese el id de la alarma que desea modificar: "<<endl;
	cin.getline(buscarid,10);
	
	ubicacion=alarmalocalizada(buscarid);
	if(ubicacion>0){
		if(cambiaralarma(ubicacion))
			cout<<"La alarma se modifico de manera correcta"<<endl;
		}else{
			cout<<"La alarma no existe"<<endl;
		}
	}
//---------------------------------------------------------------------------
	void eliminar_alarma(){
		struct ALARMA alarma;
		system("cls");
		ver_alarmas();
		char bufferid[10];
		cin.ignore();

		cout<<"Ingrese el Id de la alarma que desea eliminar"<<endl;
		cin.getline(bufferid,10);

		if (alarmalocalizada(bufferid))
		{
			fstream alarmalectura("alarmas.dat");
			ofstream alarmaescritura("auxalarmas.dat");
			alarmalectura.read((char *) &alarma,sizeof(alarma));
			string buscarid=bufferid;
			while(alarmalectura && !alarmalectura.eof()){
				if (alarma.id==buscarid)
				{
					
				}else{
					alarmaescritura.write((char *) & alarma,sizeof(alarma));
				}
				alarmalectura.read((char *) &alarma,sizeof(alarma));
			}
			alarmaescritura.close();
			alarmalectura.close();
			remove ("alarmas.dat");
			rename("auxalarmas.dat","alarmas.dat");
		}else{
			cout<<"No se ha encontrado la alarma: "<< bufferid<<endl;
		}
		
	}
//---------------------------------------------------------------------------
	void menu(){
		int opc;
	cout<<"\t\t---------------MENU---------------"<<endl;
	cout<<"1-Agregar alarma"<<endl;
	cout<<"2-Mostrar alarmas"<<endl;
	cout<<"3-Modificar alarma"<<endl;
	cout<<"4-Eliminar alarma"<<endl;
	cout<<"5-Salir"<<endl;
	cin>>opc;
	system("cls");
	switch (opc){
		case 1:agregar_alarma();break;
		case 2:ver_alarmas();break;
		case 3:modificar_alarma();break;
		case 4: eliminar_alarma();break;
		case 5:exit (-1); ;break;

	default:
	system("cls");
      cout<<"OPCION INESXISTENTE"<<endl;
     
	}
	}
//---------------------------------------------------------------------------
int main(){
	int b;
	menu();
	cout<<"\n";
	cout<<"--------------------------------------------"<<endl;
	cout<<"Desea reazlizar otra accion"<<endl;
			cout<<"1-si"<<endl;
			cout<<"2-no"<<endl;	
			cin>> b;
			if (b==1)
			{
			system("cls");
			return	main();
			}else{
				exit (-1);
			}
	return 0;
}
