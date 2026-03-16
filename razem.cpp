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
        else{ wynik[prawy] = v[i]; prawy--; }
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
        while(i<=right && v[i] > p){
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

void mymerge(vector<int> &v,int left,int mid,int right,int &ilepor)
{
    int rozm_lewa = mid - left + 1;
    int rozm_prawa = right - mid;

    vector<int> leftv(rozm_lewa),rightv(rozm_prawa);
    for(int i=0;i<rozm_lewa;i++)
    {
        leftv[i] = v[left+i];
    }
    for(int i=0;i<rozm_prawa;i++)
    {
        rightv[i] = v[mid + i + 1];
    }
    int i=0,j=0;
    int k=left;

    //sortowanie i scalanie
    while(i<rozm_lewa && j<rozm_prawa)
    {
        ilepor++;
        if(leftv[i]>=rightv[j])
        {
            v[k] = leftv[i];
            i++;
        }
        else{
            v[k] = rightv[j];
            j++;
        }
        k++;
    }
    //jesli zostaly jakies elementy w jednym z wektorow bo mialy nierowne rozmiary
    while(i<rozm_lewa)
    {
        v[k] = leftv[i];
        i++;
        k++;
    }
    while(j<rozm_prawa)
    {
        v[k] = rightv[j];
        j++;
        k++;
    }
}

void mergesort(vector<int> &v,int left,int right,int &ilescalen,int &ilepor)
{
    //jesli tylko jeden element
    if(left>=right)
    {
        return;
    }
    int mid = left + (right-left)/2;
    mergesort(v,left,mid,ilescalen,ilepor);
    mergesort(v,mid+1,right,ilescalen,ilepor);
    ilescalen++;
    mymerge(v,left,mid,right,ilepor);
}

void shellsort(vector<int> &v,int n,int &liczbaporownan,int &liczbazamian,bool pokaz_przyrost=false)
{
    if(v.size()<=1) return;

    int h = 1;

    while(h < n/3)
        h = 3*h + 1;

    while(h >= 1)
    {
        if(pokaz_przyrost) cout << "Aktualny przyrost h = " << h << endl;

        for(int i = h; i < n; i++)
        {
            int temp = v[i];
            int j = i;
            
            liczbaporownan++;
            while(j >= h && v[j-h] < temp)
            {
                v[j] = v[j-h];
                liczbazamian++;
                j -= h;

                if(j >= h) {
                    liczbaporownan++;
                }
            }
            
            if(j != i) {
                v[j] = temp;
                liczbazamian++; 
            }
        }

        h = h/3;
    }
}

int main(){
    srand(time(0));
    
    int algorytm;
    cout << "Wybierz algorytm:" << endl;
    cout << "1. Quick Sort" << endl;
    cout << "2. Merge Sort" << endl;
    cout << "3. Shell Sort" << endl;
    cout << "Wybor: ";
    cin >> algorytm;

    int tryb;
    cout << "Wybierz tryb pracy programu:" << endl;
    cout << "1. Tryb Demo (Wpisywanie reczne z wypisywaniem na ekran)" << endl;
    cout << "2. Tryb Eksperymentalny (generacja pod wykresy)" << endl;
    cout << "Wybor: ";
    cin >> tryb;
    
    if(tryb==1)
    {
        int n,a;
        vector<int> v;
        cout<<"Podaj ilosc elementow: "<<endl;
        cin>>n;

        if(n <= 0)
        {
            cout<<"Niepoprawna liczba elementow"<<endl;
            return 0;
        }

        for(int i=0;i<n;i++)
        {
            cin>>a;
            v.push_back(a);
        }
        cout<<"Ciag przed posortowaniem: "<<endl;
        for(int i=0;i<n;i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl;
        
        int por = 0, zam_scal = 0;

        clock_t start_time = clock();
        if(algorytm == 1) quicksort(v, 0, v.size()-1, por, zam_scal, true);
        else if(algorytm == 2) mergesort(v, 0, v.size()-1, zam_scal, por);
        else if(algorytm == 3) shellsort(v, n, por, zam_scal, true);
        clock_t end_time = clock();
        
        double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        cout << endl<<"Czas sortowania: " << fixed << setprecision(6) << seconds << " sekundy" << endl;
        
        cout<<endl<<"Ciag po posortowaniu: "<<endl;
        for(int i=0;i<n;i++)
        {
            cout<<v[i]<<" ";
        }

        if(algorytm == 2) cout<<endl<<"liczba porownan: "<<por<<endl<<"liczba scalen: "<<zam_scal<<endl;
        else cout<<endl<<"ile porownan: "<<por<<endl<<"ile zamian: "<<zam_scal<<endl;
    }
    else{
        int wzr_lin[] = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
        
        // Zmienne tablice wykladnicze pod dany algorytm
        int wzr_wykl_quick[] = {10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240, 20480};
        int wzr_wykl_inne[] = {1000,2000,4000,8000,16000,32000,64000,128000,256000,512000};
        int limit_wykl;
        if(algorytm == 1) {
            limit_wykl = 12;
        } else {
            limit_wykl = 10;
        }

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
                    vector<int> v;
                    if(typ==1){v = generujLosowe(wzr_lin[i]);}
                    else if(typ==2){v = generujRosnace(wzr_lin[i]);}
                    else if(typ==3){v = generujMalejace(wzr_lin[i]);}        
                    else if(typ==4){v = generujA_ksztaltne(wzr_lin[i]);}
                    else{v = generujV_ksztaltne(wzr_lin[i]);}

                    int por = 0, zam_scal = 0;
                    
                    clock_t start = clock();
                    if(algorytm == 1) quicksort(v, 0, v.size()-1, por, zam_scal, false);
                    else if(algorytm == 2) mergesort(v, 0, v.size()-1, zam_scal, por);
                    else if(algorytm == 3) shellsort(v, v.size(), por, zam_scal, false);
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

        for(int i=0;i<limit_wykl;i++)
        {
            for(int typ = 1;typ<=5;typ++)
            {
                double czasy[10];
                double suma_czasow = 0;
                
                for(int j=0;j<10;j++)
                {
                    vector<int> v;
                    int rozmiar;
                    if(algorytm == 1) {
                        rozmiar = wzr_wykl_quick[i];
                    } else {
                        rozmiar = wzr_wykl_inne[i];
                    }

                    if(typ==1){v = generujLosowe(rozmiar);}
                    else if(typ==2){v = generujRosnace(rozmiar);}
                    else if(typ==3){v = generujMalejace(rozmiar);}        
                    else if(typ==4){v = generujA_ksztaltne(rozmiar);}
                    else{v = generujV_ksztaltne(rozmiar);}

                    int por = 0, zam_scal = 0;
                    
                    clock_t start = clock();
                    if(algorytm == 1) quicksort(v, 0, v.size()-1, por, zam_scal, false);
                    else if(algorytm == 2) mergesort(v, 0, v.size()-1, zam_scal, por);
                    else if(algorytm == 3) shellsort(v, v.size(), por, zam_scal, false);
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
                
                int rozmiar_wypis;
                if(algorytm == 1) {
                    rozmiar_wypis = wzr_wykl_quick[i];
                } else {
                    rozmiar_wypis = wzr_wykl_inne[i];
                }
                cout << rozmiar_wypis << ";" << nazwaTypu(typ) << ";" << fixed << setprecision(6) << sredni_czas << ";" << odchylenie << endl;
            }
        }
    }
    return 0;
}