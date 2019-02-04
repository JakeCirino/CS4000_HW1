#include <iostream>
#include <omp.h>
using namespace std;

int main(){
    //run loop in parallel printing thread info
    #pragma omp parallel num_threads(8)
    {
        cout << "Hello from thread " << omp_get_thread_num() << "." << endl;
        cout << "This is Jake Cirino's first parallel program" << endl;
        cout << "There are currently " << omp_get_num_threads() << " threads running" << endl << endl;
    }

    return 0;
}