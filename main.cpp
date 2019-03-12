#include<iostream>
#include<iomanip>
#include<math.h>
#include<conio.h>
#include<stdlib.h>
#define LIM 300

using namespace std;

struct nodo  { int limiteif1;
               int limitesup1;
               double limiteif2;
               double limitesup2;
               int fi;
               int Fj;
               double hi;
               double Hj;
               double yi;
               double yifi;
               double yiyifi;
               struct nodo *ant;
               struct nodo *sgte;};

typedef struct nodo* LISTADOBLE;

struct bidimensional { int limiteif1;
                       int limitesup1;
                       double limiteif2;
                       double limitesup2;
                       int fi;};


void Cuadro(int);
void FormarCuadro(int,int,int);
void Insertar(struct nodo);
int Variables(void);
int Valores(void);
void Posicion(int,int);
void Variacion(int,int);
void Media(int,int);
void Mediana(int,int);
void Moda(int,int);
void FunVariacion(int,int,int);
void Elimina();
int OpcionesVarianza1(int);
int OpcionesVarianza2(int);
void Leyenda(int);
int opc,l,m,s,i,v;
int discreto[LIM];
double continua[LIM];
int regdis[LIM][2];
double regcon[LIM][2];
double cbcont[LIM][LIM];
double suma,suma2;
LISTADOBLE cuadroestadistico=NULL;

int main ()
{
     system("color 4F");
    cout<<" \t \t    ----> PROYECTO DE ESTADISTICA <----"<<endl;
    cout<<"Ernesto Leon PhD"<<endl;
	cout<<"Laura Irene Capo"<<endl;
	cout<<"Daniel Giniebra"<<endl;
	cout<<"Víctor Omar Vento"<<endl<<endl;
    while(1)
    {
        cout<<"   1)ENTRAR DATOS Y AGRUPARLOS"<<endl;
        cout<<"   2)MEDIDAS DE TENDENCIA CENTRAL"<<endl;
        cout<<"   3)MEDIDAS DE DISPERSION"<<endl;
        cout<<"   4)CALCULAR PERCENTIL (no sirve)" <<endl;
        cout<<"   5)Salir"<<endl;
        cin>>opc;
        switch(opc)
        {
        case 1: Cuadro(opc);break;
        case 2: Cuadro(opc);break;
        case 3: Cuadro(opc);break;
        case 4: cout<< "que no sirve "; break;
        case 5: cout<<endl<<"Gracias por usar este programa"<<endl;
                getch();
                exit(1);break;
        }
        cout<<endl;
    }
    cout<<endl;
    return 0;
}

void Cuadro(int n)
{

    if(n==2 || n==3)
    {
        l=Valores();
        if(l==0)
        {
            cout<<endl;
            main();
        }
    }
    if(n!=1 || n==6 || n==5)
    {
        m=Variables();
        if(m==0) Cuadro(n);
    }

    if(n==1)
    {
        int mayord=0,menord=999,R,m1,C,R2;

        cout<<endl<<"Ingrese cantidad de datos: ";
        cin>>s;
        cout<<endl;

        for(i=0;i<s;i++)
        {
            cout<<i+1<<": ";cin>>discreto[i];
            if(discreto[i]>mayord) mayord=discreto[i];
            if(discreto[i]<menord) menord=discreto[i];
        }
        cout<<endl;
        R = mayord - menord;

        if(((1 + 3.322*log10(s))-(double)(int)(1 + 3.322*log10(s)))>0.5)
        {
        m1 =(int)(1 + 3.322*log10(s))+1;
        }
        else
        {
            m1 =(int)(1 + 3.322*log10(s));
        }

        
        if(((double)R/m1-(double)(int)(R/m1))>0)
        {
            C=(int)(R/m1)+1;
        }
        else
        {
            C=(int)(R/m1);
        }

        R2=C*m1;

        if((R2-R)!=0)
        {
            if((R2-R)%2==0)
            {
                mayord=mayord+(R2-R)/2;
                menord=menord-(R2-R)/2;
            }
            else
            {
                mayord=mayord+(R2-R)/2;
                menord=menord-((R2-R)/2+1);
            }

        }
        FormarCuadro(menord,m1,C);

    }
    if(n==2 || n==3)
    {
        cout<<endl;
        if(l==1)
        {
            cout<<"Ingrese cantidad de datos: ";
            cin>>s;
            if(m==1)
                for(i=0;i<s;i++)
                {
                    cout<<i+1<<": ";
                    cin>>discreto[i];
                }
            else
                for(i=0;i<s;i++)
                {
                    cout<<i+1<<": ";
                    cin>>continua[i];
                }
            switch(n)
            {
            case 2: Posicion(l,m);break;
            case 3: Variacion(l,m);break;
            }
            cout<<endl;
        }

        else
        {
            LISTADOBLE r;
            struct nodo intervalo;
            opc=0;
            v=0;

            cout<<"Ingrese numero de intervalos: ";
            cin>>s;
            cout<<endl;

            Elimina();

            for(i=0;i<s;i++)
            {
                if(m==1)
                {
                    cout<<"Ingrese intervalo inferior "<<i+1<<": ";
                    cin>>intervalo.limiteif1;
                    cout<<"Ingrese intervalo superior "<<i+1<<": ";
                    cin>>intervalo.limitesup1;
                }
                else
                {
                    cout<<"Ingrese intervalo inferior "<<i+1<<": ";
                    cin>>intervalo.limiteif2;
                    cout<<"Ingrese intervalo superior "<<i+1<<": ";
                    cin>>intervalo.limitesup2;
                }
                cout<<"Ingrese frecuencia absoluta "<<i+1<<": ";
                cin>>intervalo.fi;
                if(m==1) intervalo.yi=(double)(intervalo.limiteif1+intervalo.limitesup1)/2;
                else     intervalo.yi=intervalo.limiteif2+intervalo.limitesup2/2;
                intervalo.yifi=intervalo.yi*intervalo.fi;
                intervalo.yiyifi=intervalo.yifi*intervalo.yi;
                opc=opc+intervalo.fi;
                intervalo.Fj=opc;
                v=opc;
                Insertar(intervalo);
                cout<<endl;
            }

            r=cuadroestadistico;

            cout<<" Intervalos "<<setw(5)<<" fi "<<setw(5)<<" Fj "<<setw(5)<<endl;

            while(r!=NULL)
            {
                if(m==1) cout<<" "<<r->limiteif1<<" - "<<r->limitesup1<<"    ";
                else cout<<" "<<r->limiteif2<<" - "<<r->limitesup2<<"     ";
                cout<<r->fi<<"       "<<r->Fj<<"       "<<endl;
                r=r->sgte;
            }
            switch(n)
            {
            case 2: Posicion(l,m);break;
            case 3: Variacion(l,m);break;
            }
            cout<<endl;

        }

    }

}

int Valores()
{
    cout<<endl;
    while(1)
    {
        cout<<"Que forma de agrupacion de los valores?"<<endl;
        cout<<"1)Valores No Agrupados"<<endl;
        cout<<"2)Valores Agrupados"<<endl;
        cout<<"3)Retornar"<<endl;
        cin>>opc;
        switch(opc)
        {
        case 1: return 1;break;
        case 2: return 2;break;
        case 3: return 0;break;
        }
    }
    cout<<endl;
}

int Variables()
{
    cout<<endl;
    while(1)
    {
        cout<<"Que tipo de variable?"<<endl;
        cout<<"1)Variable Discreta"<<endl;
        cout<<"2)Variable Continua"<<endl;
        cout<<"3)Retornar"<<endl;
        cin>>opc;
        switch(opc)
        {
        case 1: return 1;break;
        case 2: return 2;break;
        case 3: return 0;break;
        }
    }
    cout<<endl;
}

void Posicion(int l, int m)
{
    cout<<endl;
    while(1)
    {
        cout<<"Elija opcion: "<<endl;
        cout<<"1) Media"<<endl;
        cout<<"2) Mediana"<<endl;
        cout<<"3) Moda"<<endl;
        cout<<"4) Retornar"<<endl;
        cin>>opc;
        switch(opc)
        {
        case 1: Media(l,m);break;
        case 2: Mediana(l,m);break;
        case 3: Moda(l,m);break;
        case 4:
                cout<<endl;
                main();break;
        }
    }
    cout<<endl;
}

void Variacion(int l,int m)
{
    cout<<endl;
    while(1)
    {
        cout<<"Elija opcion: "<<endl;
        cout<<"1) Varianza"<<endl;
        cout<<"2) Desviacion Estandar"<<endl;
        cout<<"3) Coeficiente de Variacion"<<endl;
        cout<<"4) Retornar"<<endl;
        cin>>opc;
        switch(opc)
        {
        case 1: FunVariacion(l,m,1);break;
        case 2: FunVariacion(l,m,2);break;
        case 3: FunVariacion(l,m,3);break;
        case 4:
                cout<<endl;
                main();break;
        }
    }
    cout<<endl;
}

void Media(int l,int m)
{
    suma=0;
    LISTADOBLE r;
    cout<<endl;
    if(l==1)
    {
        for(i=0;i<s;i++)
        {
            if(m==1) suma=suma+(double)discreto[i];
            else suma=suma+continua[i];
        }
        Leyenda(2);
        cout<<" Media = "<<suma/s<<endl;
    }
    else
    {
        v=0;
        r=cuadroestadistico;
        while(r!=NULL)
        {
            if(m==1) suma=suma+r->fi*(r->limiteif1+r->limitesup1)/2;
            else suma=suma+r->fi*(r->limiteif2+r->limitesup2)/2;
            v=v+r->fi;
            r=r->sgte;
        }
        Leyenda(3);
        
        cout<<" Media = "<<suma/v<<endl;

    }
    cout<<endl;
}

void Mediana(int l,int m)
{
    cout<<endl;

    if(l==1)
    {
        if(s%2!=0)
        {
            Leyenda(4);
            if(m==1) cout<<" Mediana = "<<discreto[(s+1)/2]<<endl;
            else cout<<" Mediana = "<<continua[(s+1)/2]<<endl;
        }

        else
        {
            Leyenda(5);
            cout<<" (n+1)/2 = "<<(s+1)/2<<endl<<endl;
            if(m==1)
            {
               cout<<" Mediana = "<<(double)(discreto[(s/2)-1]+discreto[((s+2)/2)-1])/2<<endl;
            }
            else
            {
                cout<<" Mediana = "<<(continua[(s/2)-1]+continua[((s+2)/2)-1])/2<<endl;
            }
        }
    }
    else
    {
        double Antes=0,Despues=0,Li,C,n,Me;
        LISTADOBLE r,p;

        n=(double)v/2;
        r=cuadroestadistico;

        while(r!=NULL)
        {
            if((r->ant==NULL || (r->ant)->Fj<n) && r->Fj>=n) p=r;
            r=r->sgte;
        }

        if(p->ant!=NULL) Antes=(double)(p->ant)->Fj;
        Despues=(double)p->Fj;

        if(m==1)
        {
            Li=(double)p->limiteif1;
            C=(double)(p->limitesup1-p->limiteif1);
        }
        else
        {
            Li=(double)p->limiteif2;
            C=(double)(p->limitesup2-p->limiteif2);
        }
        Leyenda(6);
                if(m==1) cout<<" IMe = <"<<p->limiteif1<<" - "<<p->limitesup1<<"]"<<endl<<endl;
        else cout<<" IMe = <"<<p->limiteif2<<" - "<<p->limitesup2<<"]"<<endl<<endl;

        Me=Li+C*((n-Antes)/(Despues-Antes));

        cout<<" Mediana = "<<Me<<endl<<endl;

    }
    cout<<endl;
}

void Moda(int l,int m)
{

    cout<<endl;

    if(l==1)
    {
        int band=0,j,mayor=2,cont,temp1;
        double temp2;
        Leyenda(7);
        if(m==1)
        {
            for(i=0;i<s;i++)
                for(j=s-1;j>i;j--)
                {
                    if(discreto[j-1]>discreto[j])
                    {
                        temp1=discreto[j-1];
                        discreto[j-1]=discreto[j];
                        discreto[j]=temp1;
                    }
                }
            temp1=-1;
            for(i=0;i<s;i++)
            {
                cont=1;
                for(j=0;j<s;j++)
                    if(discreto[i]==discreto[j] && i!=j) cont++;
                if(cont>mayor) mayor=cont;
            }
            for(i=0;i<s;i++)
            {
                cont=1;
                for(j=0;j<s;j++)
                    if(discreto[i]==discreto[j] && i!=j) cont++;
                if(cont==mayor && temp1!=discreto[i])
                {
                    cout<<" La moda es = "<<discreto[i]<<" ya que se repite "<<mayor<<" veces"<<endl;
                    temp1=discreto[i];
                    band=1;
                }
            }
        }
        else
        {
            for(i=0;i<s;i++)
                for(j=s-1;j>i;j--)
                {
                    if(continua[j-1]>continua[j])
                    {
                        temp2=continua[j-1];
                        continua[j-1]=continua[j];
                        continua[j]=temp2;
                    }
                }
            temp2=-1;
            for(i=0;i<s;i++)
            {
                cont=1;
                for(j=0;j<s;j++)
                    if(continua[i]==continua[j] && i!=j) cont++;
                if(cont>mayor) mayor=cont;
            }
            for(i=0;i<s;i++)
            {
                cont=1;
                for(j=0;j<s;j++)
                    if(continua[i]==continua[j] && i!=j) cont++;
                if(cont==mayor && temp2!=continua[i])
                {
                    cout<<" La moda es = "<<continua[i]<<" ya que se repite "<<mayor<<" veces"<<endl;
                    temp2=continua[i];
                    band=1;
                }
            }

        }
        if(band==0) cout<<" No hay moda"<<endl;
    }
    else
    {
        double Antes=0,Despues=0,Li,C,Mo;
        LISTADOBLE r,p;

        r=cuadroestadistico;

        while(r!=NULL)
        {
            if(r->fi>Antes)
            {
                Antes=(double)r->fi;
                p=r;
            }
            r=r->sgte;
        }

        Leyenda(8);
        if(p->ant!=NULL) Antes=(double)(p->ant)->fi;
        if(p->sgte!=NULL)Despues=(double)(p->sgte)->fi;

        if(m==1)
        {
            Li=(double)p->limiteif1;
            C=(double)(p->limitesup1-p->limiteif1);
        }
        else
        {
            Li=(double)p->limiteif2;
            C=(double)(p->limitesup2-p->limiteif2);
        }
        
       
        if(m==1) cout<<"<"<<p->limiteif1<<" - "<<p->limitesup1<<"]"<<endl<<endl;
        else cout<<"<"<<p->limiteif2<<" - "<<p->limitesup2<<"]"<<endl<<endl;

      

        Mo=Li+C*((Despues)/(Despues+Antes));

        cout<<" Moda = "<<Mo<<endl<<endl;
    }
    cout<<endl;
}

void FunVariacion(int l,int m,int t)
{
    int d;
    double media,varianza;
    double desv;
    LISTADOBLE r;

    suma=0;

    if(l==1)
    {
        d=OpcionesVarianza1(d);

        if(d==1 || d==2 || d==3 || d==4 || d==5)
        {
            for(i=0;i<s;i++)
            {
                if(m==1) suma=suma+(double)discreto[i];
                else     suma=suma+continua[i];
            }

            media=suma/s;

          
            cout<<" Media = "<<media<<endl<<endl;
        }

        suma=0;

        if(d==1 || d==3 || d==5)
        {
            for(i=0;i<s;i++)
            {
                if(m==1) suma=suma+((double)discreto[i]-media)*((double)discreto[i]-media);
                else     suma=suma+(continua[i]-media)*(continua[i]-media);
            }

       
            if(d==5)
            {
           
                cout<<" Varianza = "<<suma/s-1<<endl<<endl;
                varianza=suma/s-1;
            }
            else
            {
            
                cout<<" Varianza = "<<suma/s<<endl<<endl;
                varianza=suma/s;
            }
        }
        if(d==2 || d==4)
        {
            for(i=0;i<s;i++)
            {
                if(m==1) suma=suma+((double)discreto[i])*((double)discreto[i]);
                else     suma=suma+(continua[i])*(continua[i]);
            }
                 
            cout<<" Varianza = "<<suma/s-media*media<<endl<<endl;
            varianza=suma/s-media*media;

        }
        if(d==6)
        {
            suma2=0;

            for(i=0;i<s;i++)
            {
                if(m==1) suma=suma+((double)discreto[i])*((double)discreto[i]);
                else     suma=suma+(continua[i])*(continua[i]);
            }

            for(i=0;i<s;i++)
            {
                if(m==1) suma2=suma2+(double)discreto[i];
                else     suma2=suma2+continua[i];
            }

            suma2=suma2*suma2;
            cout<<" Varianza = "<<(suma-suma2/s)/s-1<<endl<<endl;
            varianza=(suma-suma2/s)/s-1;
        }

    }
    else
    {
        d=OpcionesVarianza2(d);
        suma=0;
        v=0;

        r=cuadroestadistico;

        while(r!=NULL)
        {
            v=v+r->fi;
            r=r->sgte;
        }

        if(d==1 || d==2 || d==3 || d==4)
        {
            r=cuadroestadistico;

            while(r!=NULL)
            {
                suma=suma+(r->yifi);
                r=r->sgte;
            }

            media=suma/v;

            cout<<" Media = "<<media<<endl<<endl;
        }

        suma=0;

        if(d==1 || d==3)
        {
            r=cuadroestadistico;

            while(r!=NULL)
            {
                suma=suma+(r->yi-media)*(r->yi-media)*r->fi;
                r=r->sgte;
            }

            cout<<" Varianza = "<<suma/v<<endl<<endl;
            varianza=suma/v;

        }

        if(d==2 || d==4)
        {
            r=cuadroestadistico;

            while(r!=NULL)
            {
                suma=suma+(r->yiyifi);
                r=r->sgte;
            }
                cout<<" Varianza = "<<suma/v-media*media<<endl<<endl;
                varianza=suma/v-media*media;

        }

        if(d==5)
        {
            suma2=0;
            r=cuadroestadistico;

            while(r!=NULL)
            {
                suma=suma+r->yiyifi;
                suma2=suma2+r->yifi;
                r=r->sgte;
            }

            suma2=suma2*suma2;
            cout<<" Varianza = "<<(suma-suma2/v)/(v-1)<<endl<<endl;
            varianza=(suma-suma2/v)/(v-1);
        }
    }
    if(t>1)
    {
        cout<<" Desviacion Estandar = "<<sqrt(suma/s)<<endl<<endl;
        desv=sqrt(suma/s);
    }
    if(t>2)
    {
        cout<<" Coeficiente de Variacion (%) = "<<(desv/s)*100<<endl<<endl;
    }
    cout<<endl;
}

void FormarCuadro(int menord,int m1, int C)
{
    struct nodo intervalo;
    LISTADOBLE r;

    for(i=0;i<m1;i++)
    {
        intervalo.limiteif1=menord+C*i;
        intervalo.limitesup1=menord+C*(i+1);
        intervalo.fi=0;
        intervalo.hi=0;
        Insertar(intervalo);
    }

    for(i=0;i<s;i++)
    {
        r=cuadroestadistico;
        while(r!=NULL)
        {
            if(discreto[i]>=r->limiteif1 && discreto[i]<r->limitesup1)
            {
                r->fi=r->fi+1;
                r->hi=(double)r->fi*100/s;
            }
            r=r->sgte;
        }
    }

    r=cuadroestadistico;

    cout<<" Intervalos "<<setw(5)<<" fi "<<setw(5)<<" hi% "<<endl<<endl;

    while(r!=NULL)
    {
        cout<<" "<<r->limiteif1<<" - "<<r->limitesup1<<setw(5)<<" "<<r->fi<<setw(5)<<" "<<r->hi<<endl;
        r=r->sgte;
    }

    Elimina();

}

void Insertar(struct nodo intervalo)
{
    LISTADOBLE p,r;
    p=new(struct nodo);
    *p=intervalo;
    p->sgte=NULL;
    if(cuadroestadistico==NULL)
    {
        p->ant=NULL;
        cuadroestadistico=p;
    }
    else
    {
        r=cuadroestadistico;
        while(r->sgte!=NULL) r=r->sgte;
        r->sgte=p;
        p->ant=r;
    }
}

void Elimina()
{
    LISTADOBLE p;

    while(cuadroestadistico!=NULL)
    {
        p=cuadroestadistico;
        cuadroestadistico=cuadroestadistico->sgte;
        delete(p);
    }
    cuadroestadistico=NULL;
}

int OpcionesVarianza1(int v)
{
    cout<<endl;
    cout<<"Marque 1 para calcular varianza"<<endl;
    cin>>v;
    switch(v)
    {
    case 1: return 1;break;
    }
}

int OpcionesVarianza2(int v)
{
    cout<<endl;
    cout<<"Marque 1 para calcular varianza"<<endl;
    cin>>v;
    switch(v)
    {
    case 1: return 1;break;
    
    }
}

void Leyenda(int n)
{
    
}
