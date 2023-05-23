#include <iostream>

using namespace std;

class SocioClub{
    private:
        int NumeroSocio;
    public:
        SocioClub(){};
        friend std::ostream & operator<<(std::ostream &O, SocioClub &x){
            O<<"\n Numero de socio: "<<x.NumeroSocio;
            return O;
        }
        friend std::istream & operator>>(std::istream &O, SocioClub &x){
            std::cout<<"\n Numero de socio: ";
            O>>x.NumeroSocio;
            return O;
        }
        bool operator==(SocioClub &x){
        return (NumeroSocio==x.NumeroSocio);
        }
        bool operator!=(SocioClub &x){
        return (NumeroSocio!=x.NumeroSocio);
        }
        bool operator<(SocioClub &x){
            return (NumeroSocio<x.NumeroSocio);
        }
        bool operator>(SocioClub &x){
            return (NumeroSocio>x.NumeroSocio);
        }
        bool operator<=(SocioClub &x){
            return (NumeroSocio<=x.NumeroSocio);
        }
        bool operator>=(SocioClub &x){
            return (NumeroSocio>=x.NumeroSocio);
        }
};

template<class T>
class Arbol;

template<class T>
class nodo{
private:
    T data;
    nodo<T>* izq;
    nodo<T>* der;
public:
    nodo():izq(nullptr), der(nullptr){};
    friend class Arbol<T>;
};

template<class T>
class Arbol{
private:
    nodo<T>* arbol;
public:
    Arbol(): arbol(nullptr){};
    bool vacia()const;
    nodo<T>* localiza(SocioClub,nodo<T>*)const;
    T recupera(nodo<T>*)const;
    void imprime()const;
    void inserta(nodo<T>* pos, SocioClub elem);
    bool elimina(nodo<T>* pos);
    nodo<T>* menor(nodo<T>*);
    nodo<T>* mayor(nodo<T>*);
    bool es_hoja(nodo<T>*);
    void recorrido_preorder();
    void recorrido_inorder();
    void recorrido_postorder();
    void elimina(nodo<T>*,nodo<T>*);
    int altura(nodo<T>*);
    int fact_eq(nodo<T>*);
    void balanceo(nodo<T>*);
    void rot_sim_der(nodo<T>*);
    void rot_sim_izq(nodo<T>*);
    void rot_dbl_der(nodo<T>*);
    void rot_dbl_izq(nodo<T>*);
    nodo<T>* primero()const;
    void muestraAcostado(int,nodo<T>*);
};

template<class T>
void Arbol<T>::muestraAcostado(int nivel,nodo<T>* arbol){
	if(arbol==NULL)
		return;
	muestraAcostado(nivel+1,arbol->der);
	for(int i=0;i<nivel;i++)
		cout<<" | ";
    cout<<arbol->data<<"-"<<endl;
	muestraAcostado(nivel+1,arbol->izq);
}

template<class T>
nodo<T>* Arbol<T>::primero()const{
    if(vacia()){
        return nullptr;
    }
    return arbol;
}

template<class T>
void Arbol<T>::inserta(nodo<T>* arbol, SocioClub elem){
    if(vacia()){
        nodo<T>* aux= new nodo<T>;
        arbol=aux;
    }
    else{
        if(elem<arbol->data){
            inserta(arbol->izq,elem);
        }
        else{
            inserta(arbol->der,elem);
        }
    }
}

template<class T>
nodo<T>* Arbol<T>::localiza(SocioClub elem, nodo<T>* arbol)const{
    if(vacia()){
        return nullptr;
    }
    else{
        if(elem==arbol->data){
            return arbol;
        }
        else if(elem<arbol->data){
            localiza(elem,arbol->izq);
        }
        else{
            localiza(elem,arbol->der);
        }
    }
}

template<class T>
nodo<T>* Arbol<T>::menor(nodo<T>* arbol){
    if(vacia()){
        return nullptr;
    }
    else{
        if(arbol->izq==nullptr){
            return arbol;
        }
        else{
            return menor(arbol->izq);
        }
    }
}

template<class T>
nodo<T>* Arbol<T>::mayor(nodo<T>* arbol){
    if(arbol==nullptr){
        return nullptr;
    }
    else{
        if(arbol->der==nullptr){
            return arbol;
        }
        else{
            return mayor(arbol->der);
        }
    }
}

template<class T>
bool Arbol<T>::es_hoja(nodo<T>* arbol){
    if(arbol==nullptr){
        return false;
    }
    else if(arbol->izq==nullptr && arbol->der==nullptr){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
void Arbol<T>::recorrido_preorder(){
    if(vacia()){
        return;
    }
    cout<<arbol->data;
    recorrido_preorder(arbol->izq);
    recorrido_preorder(arbol->der);
}

template<class T>
void Arbol<T>::recorrido_inorder(){
    if(vacia()){
        return;
    }
    recorrido_inorder(arbol->izq);
    cout<<arbol->data;
    recorrido_inorder(arbol->der);
}

template<class T>
void Arbol<T>::recorrido_postorder(){
    if(vacia()){
        return;
    }
    recorrido_postorder(arbol->izq);
    recorrido_postorder(arbol->der);
    cout<<arbol->data;
}

template<class T>
void Arbol<T>::elimina(nodo<T>* pos,nodo<T>* arbol){
    nodo<T>* pos_reemplazo= new nodo<T>;
    if(vacia() || pos==nullptr){
        cout<<"Arbol o posicion se encuentra vacia"<<endl;
        return;
    }
    else if(es_hoja(arbol)){
        arbol=nullptr;
    }
    else{
        if(arbol->izq!=nullptr){
            pos_reemplazo=mayor(arbol->izq);
        }
        else{
            pos_reemplazo=menor(arbol->der);
        }
        arbol->data=pos_reemplazo->data;
        elimina(pos_reemplazo,arbol);
    }
}

template<class T>
int Arbol<T>::altura(nodo<T>* arbol){
    if(vacia()){
        return 0;
    }
    else{
        int alt_izq=altura(arbol->izq);
        int alt_der=altura(arbol->der);
        if(alt_izq>alt_der){
            return alt_izq+1;
        }
        return alt_der+1;
    }
}

template<class T>
int Arbol<T>::fact_eq(nodo<T>* arbol){
    if(vacia()){
        return 0;
    }
    return altura(arbol->der)-altura(arbol->izq);
}

template<class T>
void Arbol<T>::balanceo(nodo<T>* arbol){
    if(fact_eq(arbol)<-1){
        if(fact_eq(arbol->izq)==-1){
            rot_sim_der(arbol);
        }
        else{
            rot_dob_der(arbol);
        }
    return;
    }
    else{
        if(fact_eq(arbol)>1){
            if(fact_eq(arbol->izq)==1){
                rot_sim_izq(arbol);
            }
            else{
                rot_dob_izq(arbol);
            }
        }
    }
}

template<class T>
void Arbol<T>::rot_sim_der(nodo<T>* arbol){
    nodo<T>* aux1= new nodo<T>;
    nodo<T>* aux2= new nodo<T>;
    aux1=arbol->izq;
    aux2=arbol->izq->der;

    arbol->izq=aux2;
    aux1->der=arbol;
    arbol=aux1;
}

template<class T>
void Arbol<T>::rot_sim_izq(nodo<T>* arbol){
    nodo<T>* aux1= new nodo<T>;
    nodo<T>* aux2= new nodo<T>;
    aux1=arbol->der;
    aux2=arbol->der->izq;

    arbol->der=aux2;
    aux1->izq=arbol;
    arbol=aux1;
}

template<class T>
void Arbol<T>::rot_dbl_der(nodo<T>* arbol){
    nodo<T>* aux1= new nodo<T>;
    nodo<T>* aux2= new nodo<T>;
    nodo<T>* aux3= new nodo<T>;
    nodo<T>* aux4= new nodo<T>;
    aux1=arbol->izq;
    aux2=aux1->der;
    aux3=aux2->izq;
    aux4=aux2->der;

    arbol->izq=aux4;
    aux1->der=aux3;
    aux2->izq=aux1;
    arbol=aux2;
}

template<class T>
void Arbol<T>::rot_dbl_izq(nodo<T>* arbol){
    nodo<T>* aux1= new nodo<T>;
    nodo<T>* aux2= new nodo<T>;
    nodo<T>* aux3= new nodo<T>;
    nodo<T>* aux4= new nodo<T>;
    aux1=arbol->der;
    aux2=aux1->izq;
    aux3=aux2->der;
    aux4=aux2->izq;

    arbol->der=aux4;
    aux1->izq=aux3;
    aux2->der=aux1;
    arbol=aux2;
}

template<class T>
T Arbol<T>::recupera(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){
    }
    else{
        return pos->data;
    }
}

template<class T>
bool Arbol<T>::vacia()const{
    if(arbol==nullptr){
        return true;
    }
    return false;
}

void menu(){
    std::cout<<"------Menu Socios------"<<std::endl;
    std::cout<<"1. Registrar nuevo socio"<<std::endl;
    std::cout<<"2. Dar de baja socio"<<std::endl;
    std::cout<<"3. Reporte de datos de socios"<<std::endl;
    std::cout<<"4. Busqueda de socio"<<std::endl;
    std::cout<<"5. Total socios registrados"<<std::endl;
    std::cout<<"6. Salir"<<std::endl;
    std::cout<<"Opcion: ";
}

int main()
{
    Arbol<SocioClub> miarbol;
    SocioClub socio,elem,elem1;
    int opc;
    do{
        system("cls");
        menu();
        cin>>opc;
        switch(opc){
             case 1:
                cout<<"\nRegistrar datos de nuevo socio: \n";
                cin>>socio;
                miarbol.inserta(miarbol.primero(), socio);
                miarbol.muestraAcostado(0,miarbol.primero());
                cout<<"\nSocio agregado correctamente. . .\n\n";
                system("pause");
                break;
           /* case 2:
                if(milista.vacia()){
                    cout<<"\nLa lista se encuentra vacia. . .\n\n";
                }
                else{
                cout<<"\nDatos de socio a dar de baja: \n";
                cin>>socio;
                milista.elimina(milista.localiza(socio));
                }
                system("pause");
                break;
            case 3:
                cout<<"\nDatos de socios registrados: "<<endl;
                milista.imprime();
                cout<<"\n";
                system("pause");
                break;
            case 4:
                if(!milista.vacia()){
                    std::cout<<"\nProporcione los datos de socio a buscar\n"<<std::endl;
                    std::cout<<" Nombre de socio: ";
                    std::cin>>temp;
                    elem.setNombre(temp);
                    std::cout<<" Domicilio de socio: ";
                    std::cin>>temp;
                    elem.setDomicilio(temp);
                    if(milista.localiza(elem)){
                        elem1=milista.recupera(milista.localiza(elem));
                        std::cout<<"\nSocio encontrado\n"<<elem1<<std::endl<<std::endl;
                    }
                    else{
                        std::cout<<"\nSocio no encontrado\n"<<std::endl;
                    }
                }else{
                    std::cout<<"\nLa lista se encuentra vacia. . .\n"<<std::endl;
                }
                system("pause");
                break;

            case 5:
                milista.contador();
                system("pause");
                break;*/
            default:
                cout<<"\nSaliendo . . .\n";



        }



    }
    while(opc!=6);
    return 0;
}
