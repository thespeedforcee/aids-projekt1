#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>

using namespace std;

long long porownania = 0;
long long zamiany = 0;

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

void quicksortiter(vector<int>& tab, int n){
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

void uruchomSortowanie(string nazwa, void (*sortFunc)(vector<int>&), vector<int> dane) {
    porownania = 0;
    zamiany = 0;
    int n = dane.size();

    if (n <= 12) {
        cout << "\n" << nazwa << " tryb demonstracyjny"<< endl;
        cout << "Wejscie: "; wyswietl(dane);
    }

    clock_t start = clock();
    sortFunc(dane);
    clock_t stop = clock();

    if (n <= 12) {
        cout << "Wyjscie: "; wyswietl(dane);
    }

    cout << nazwa << " Czas: " << (double)(stop - start) / CLOCKS_PER_SEC 
         << "s, Porownania: " << porownania << ", Zamiany: " << zamiany << endl;
}

void qsort_wrapper(vector<int>& arr) {
    quicksortiter(arr, arr.size());
}

int main() {
    system("chcp 1250");
    srand(time(NULL));

    int n;
    cout << "Podaj liczbe elementow n: ";
    cin >> n;

    vector<int> dane_wejsciowe;
    if (n <= 12) {
        for (int i = 0; i < n; i++) {
            int liczba;
            cout << "Podaj liczbe " << i + 1 << ": ";
            cin >> liczba;
            dane_wejsciowe.push_back(liczba);
        }
    } else {
        for (int i = 0; i < n; i++) dane_wejsciowe.push_back(rand() % 1000);
        cout << "Wygenerowano " << n << " losowych liczb." << endl;
    }

    uruchomSortowanie("Shell Sort", shellSortKnuth, dane_wejsciowe);
    uruchomSortowanie("Quick Sort Iteracyjny", qsort_wrapper, dane_wejsciowe);
    uruchomSortowanie("Heap Sort", heapSort, dane_wejsciowe);

    return 0;
}
