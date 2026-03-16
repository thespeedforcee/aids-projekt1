#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <chrono>

using namespace std;

long long porownania = 0;
long long zamiany = 0;

//generatory

vector<int> Generatorlosowe(int n){
	vector<int> tab(n);
	for (int i = 0; i < n; i++){
		tab[i] = rand()%100000;
	}
	return tab;
}

vector<int> GeneratorR(int n){
	vector<int> tab = Generatorlosowe(n);
	sort(tab.begin(), tab.end());
	return tab;
}

vector<int> GeneratorM(int n){
	vector<int> tab = Generatorlosowe(n);
	sort(tab.begin(), tab.end(), greater<int>());
	return tab;
}

vector<int> GeneratorA(int n){
	vector<int> tab = Generatorlosowe(n);
	sort(tab.begin(), tab.end());
	vector<int> tab2(n);
	int lewa = 0, prawa = n - 1;
	for (int i = 0; i < n; i++){
		if (i%2 == 0){
			tab2[lewa++] = tab[i];
		}
		else {
			tab2[prawa--] = tab[i];
		}
	}
	return tab2;
}

vector<int> GeneratorV(int n){
	vector<int> tab = Generatorlosowe(n);
	sort(tab.begin(), tab.end(), greater<int>());
	vector<int> tab2(n);
	int lewa = 0, prawa = n - 1;
	for (int i = 0; i < n; i++){
		if (i%2 == 0){
			tab2[lewa++] = tab[i];
		}
		else {
			tab2[prawa--] = tab[i];
		}
	}
	return tab2;
}

//algorytmy

void shellSortKnuth(vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return;

    int gap = 1;
    while (gap < n / 3) {
        gap = 3 * gap + 1;
    }

    while (gap >= 1) {
        if (n <= 12) {
            cout << "Aktualny przyrost: " << gap << endl;
        }

        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap) {
                porownania++; 
                if (arr[j - gap] < temp) { 
                    arr[j] = arr[j - gap];
                    zamiany++; 
                    j -= gap;
                } else {
                    break; 
                }
            }
            arr[j] = temp;
        }
        gap /= 3;
    }
}

int partition(vector<int>& tab, int low, int high, bool demo){
    int pivot = tab[low];
    if (demo) cout << "Pivot: " << pivot << " (zakres " << low << "-" << high << ")" << endl;
    int i = low;
    for (int j = low + 1; j <= high; j++){
        porownania++;
        if (tab[j] >= pivot){
            i++;
            swap(tab[i], tab[j]);
            zamiany++;
        }
    }
    swap(tab[low], tab[i]);
    zamiany++;
    return i;
}

void quicksortiter(vector<int>& tab){
	int n = tab.size();
    if (n < 2) return;
    bool demo = (n <= 12);
    stack<int> s;
    s.push(0);
    s.push(n-1);
    while (!s.empty()){
        int high = s.top();
        s.pop();
        int low = s.top();
        s.pop();
        int p_index = partition(tab, low, high, demo);
        if (p_index - 1 > low){
            s.push(low);
            s.push(p_index - 1);
        }
        if (p_index + 1 < high){
            s.push(p_index + 1);
            s.push(high);
        }
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int smallest = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n){
        porownania++;
        if (arr[l] < arr[smallest]){
            smallest = l;
        }
    }
    if (r < n){
        porownania++;
        if (arr[r] < arr[smallest]){
            smallest = r;
        }
    }
    if (smallest != i){
        swap(arr[i], arr[smallest]);
        zamiany++;
        heapify(arr, n, smallest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        zamiany++;
        heapify(arr, i, 0);
    }
}

void wyswietl(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

void wykonajEksperyment(string nazwaAlg, int typAlg, vector<int> n_values, string nazwaTypuDanych) {
    cout << "\n" << nazwaAlg << " dla danych: " << nazwaTypuDanych << endl;
    cout << "n\tSredni Czas [s]\tOdchylenie Std." << endl;

    for (int n : n_values) {
        vector<double> czasy;
        for (int proba = 0; proba < 10; proba++) {
            vector<int> dane;

            if (nazwaTypuDanych == "Losowe") dane = Generatorlosowe(n);
            else if (nazwaTypuDanych == "Rosnace") dane = GeneratorR(n);
            else if (nazwaTypuDanych == "Malejace") dane = GeneratorM(n);
            else if (nazwaTypuDanych == "A-ksztaltne") dane = GeneratorA(n);
            else dane = GeneratorV(n);

            porownania = 0; zamiany = 0;

            auto start = chrono::high_resolution_clock::now();
            
            if (typAlg == 1) shellSortKnuth(dane);
            else if (typAlg == 2) heapSort(dane);
            else if (typAlg == 3) quicksortiter(dane);

            auto stop = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = stop - start;
            czasy.push_back(diff.count());
        }

        double suma = 0;
        for (double t : czasy) suma += t;
        double srednia = suma / 10.0;

        double wariancja = 0;
        for (double t : czasy) wariancja += pow(t - srednia, 2);
        double odchylenie = sqrt(wariancja / 10.0);

        cout << n << "\t" << fixed << setprecision(8) << srednia << "\t" << odchylenie << endl;
    }
}

int main() {
	system("chcp 1250");
    srand(time(NULL));
    
    vector<int> n_liniowe = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    vector<int> n_wykladnicze = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000};

	string nazwyAlgorytmow[] = {
        "Shell Sort", "Heap Sort", "Quick Sort Iteracyjny"
    };

    string typyDanych[] = {
        "Losowe", "Rosnace", "Malejace", "A-ksztaltne", "V-ksztaltne"
    };
	
	//wzrosty liniowe   
    for (int alg = 1; alg <= 3; alg++) {
        for (const string& typ : typyDanych) {
            wykonajEksperyment(nazwyAlgorytmow[alg-1], alg, n_liniowe, typ);
        }
    }

    //wykladnicze
    for (int alg = 1; alg <= 3; alg++) {
        for (const string& typ : typyDanych) {
            wykonajEksperyment(nazwyAlgorytmow[alg-1], alg, n_wykladnicze, typ);
        }
    }

    cout << "\nKoniec pomiarow." << endl;
    return 0;
}
