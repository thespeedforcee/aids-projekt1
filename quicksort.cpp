#include <iostream>
#include<vector>
#include<ctime>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
//generacja typu danych
vector<int> generujLosowe(int n) {
    vector<int> v(n);
    for(int i = 0; i < n; i++) v[i] = rand() % 100000;
    return v;
}

vector<int> generujRosnace(int n) {
    vector<int> v = generujLosowe(n);
    sort(v.begin(), v.end()); 
    return v;
}

vector<int> generujMalejace(int n) {
    vector<int> v = generujLosowe(n);
    sort(v.rbegin(), v.rend()); 
    return v;
}

vector<int> generujA_ksztaltne(int n) {
    vector<int> v = generujRosnace(n);
    vector<int> wynik(n);
    int lewy = 0, prawy = n - 1;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) { wynik[lewy] = v[i]; lewy++;}
        else{ wynik[prawy] = v[i]; prawy--;}
    }
    return wynik;
}

vector<int> generujV_ksztaltne(int n) {
    vector<int> v = generujMalejace(n);
    vector<int> wynik(n);
    int lewy = 0, prawy = n - 1;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) { wynik[lewy] = v[i]; lewy++; }
        else           { wynik[prawy] = v[i]; prawy--; }
    }
    return wynik;
}

string nazwaTypu(int typ) {
    if(typ == 1) return "Losowe";
    if(typ == 2) return "Rosnace";
    if(typ == 3) return "Malejace";
    if(typ == 4) return "A-ksztaltne";
    if(typ == 5) return "V-ksztaltne";
    return "";
}

void quicksort(vector<int> & v, int left, int right,int &ilepor,int &ilezam,bool pokaz_pivot=false)
{
    if(right<=left){return;}
    int p = v[left];
    if(pokaz_pivot) cout<<"wartosc pivota: "<<p<<endl;

    int i=left,j=right;

    while(i <= j)
    {
        ilepor++;
        while(i <= right && v[i] > p){
            i++;
            ilepor++;
        }

        ilepor++;
        while(j>=left && v[j] < p){
            j--;
            ilepor++;
        }

        if( i <= j){
            swap(v[i], v[j]);
            ilezam++;
            i++;
            j--;
        }
    }

    if(j > left){
        quicksort(v, left, j,ilepor,ilezam,pokaz_pivot);
    }
    if(i < right){
        quicksort(v, i, right,ilepor,ilezam,pokaz_pivot);
    }

}

int main(){
    srand(time(0));
    int tryb;
    cout << "Wybierz tryb pracy programu:" << endl;
    cout << "1. Tryb Demo (Wpisywanie reczne z wypisywaniem na ekran)" << endl;
    cout << "2. Tryb Eksperymentalny (generacja pod wykresy)" << endl;
    cout << "Wybor: ";
    cin >> tryb;
    if(tryb==1)
    {
        vector<int> vec;
        cout<<"Podaj ilosc elementow: "<<endl;
        int n,a;
        cin>>n;
        if(n <= 0)
        {
            cout<<"Niepoprawna liczba elementow"<<endl;
            return 0;
        }
        for(int i=0;i<n;i++)
        {
            cin>>a;
            vec.push_back(a);
        }
        cout<<"Ciag przed posortowaniem: "<<endl;
        for(int i=0;i<n;i++)
        {
            cout<<vec[i]<<" ";
        }
        cout<<endl;
        int ilepor = 0,ilezam = 0;

        clock_t start_time = clock();
        quicksort(vec, 0, vec.size()-1,ilepor,ilezam,true);
        clock_t end_time = clock();
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        cout << endl<<"Czas sortowania: " << fixed << setprecision(6) << seconds << " sekundy" << endl;
        cout<<endl<<"Ciag po posortowaniu: "<<endl;
        for(int i = 0; i < vec.size(); i++){
            cout << vec[i] << " ";
        }

        cout<<endl<<"ile porownan: "<<ilepor<<endl<<"ile zamian: "<<ilezam<<endl;
        
    }
    else{
        int wzr_lin[] = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
        int wzr_wykl[] = {10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240, 20480};

        cout<<"Dla wzrostu liniowego: "<<endl;
        cout << "Rozmiar;Typ;Czas[s];Odchylenie" << endl;
        for(int i=0;i<10;i++)
        {
            for(int typ = 1;typ<=5;typ++)
            {
                double czasy[10];
                double suma_czasow = 0;
                
                for(int j=0;j<10;j++)
                {
                    vector<int> vec;
                    if(typ==1){vec = generujLosowe(wzr_lin[i]);}
                    else if(typ==2){vec = generujRosnace(wzr_lin[i]);}
                    else if(typ==3){vec = generujMalejace(wzr_lin[i]);}        
                    else if(typ==4){vec = generujA_ksztaltne(wzr_lin[i]);}
                    else{vec = generujV_ksztaltne(wzr_lin[i]);}

                    int por = 0, zam = 0;
                    
                    clock_t start = clock();
                    quicksort(vec, 0,vec.size()-1, por, zam,false);
                    clock_t end = clock();

                    double sekundy = (double)(end - start) / CLOCKS_PER_SEC;
                    czasy[j] = sekundy;
                    suma_czasow += sekundy;
                }
                double sredni_czas = suma_czasow / 10.0;
                
                // odchylenie standardowe
                double wariancja = 0;
                for(int p = 0; p < 10; p++) {
                    wariancja += pow(czasy[p] - sredni_czas, 2);
                }
                double odchylenie = sqrt(wariancja / 10.0);
                
                cout << wzr_lin[i] << ";" << nazwaTypu(typ) << ";" << fixed << setprecision(6) << sredni_czas << ";" << odchylenie << endl;
            }
        }

        cout<<"Dla wzrostu wykladniczego: "<<endl;
        cout << "Rozmiar;Typ;Czas[s];Odchylenie" << endl;

        for(int i=0;i<12;i++)
        {
            for(int typ = 1;typ<=5;typ++)
            {
                double czasy[10];
                double suma_czasow = 0;
                
                for(int j=0;j<10;j++)
                {
                    vector<int> vec;
                    if(typ==1){vec = generujLosowe(wzr_wykl[i]);}
                    else if(typ==2){vec = generujRosnace(wzr_wykl[i]);}
                    else if(typ==3){vec = generujMalejace(wzr_wykl[i]);}        
                    else if(typ==4){vec = generujA_ksztaltne(wzr_wykl[i]);}
                    else{vec = generujV_ksztaltne(wzr_wykl[i]);}

                    int por = 0, zam = 0;
                    
                    clock_t start = clock();
                    quicksort(vec, 0,vec.size()-1, por, zam,false);
                    clock_t end = clock();

                    double sekundy = (double)(end - start) / CLOCKS_PER_SEC;
                    czasy[j] = sekundy;
                    suma_czasow += sekundy;
                }
                double sredni_czas = suma_czasow / 10.0;
                
                // odchylenie standardowe
                double wariancja = 0;
                for(int p = 0; p < 10; p++) {
                    wariancja += pow(czasy[p] - sredni_czas, 2);
                }
                double odchylenie = sqrt(wariancja / 10.0);

                cout << wzr_wykl[i] << ";" << nazwaTypu(typ) << ";" << fixed << setprecision(6) << sredni_czas << ";" << odchylenie << endl;
            }
        }
    }
    return 0;
}