#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main () {
// tworzenie rodzica z procesem potomnym
pid_t pr1 = fork();

//proces potomny
if (pr1 == 0){
    cout << "To jest proces potomny z PID: " << getpid() << endl;
    exit(0); 
// proces rodzica
}else if (pr1 > 0) {
    // getpid() - do odczytu procesu PID
    cout << "To jest proces rodzica z PID: " << getpid() << endl;
    // status - sluzy do weryfikacji koda odpowiedzi po zakonczeniu procesu potomka
    int status; 
    // czekamy na zakonczenie procesa
    wait(&status);
    // makra WIFEXITED() Sprawdza, czy proces zakończył się normalnie
    if (WIFEXITED(status)){
        //WEXITSTATUS() - pobiera kod zakończenia procesu, jeśli zakończył się normalnie.
        cout << "Potomek zakończył się z kodem: " << WEXITSTATUS(status) << endl;
        // WIFSIGNALED() - sprawdza, czy proces zakończył się z powodu sygnału
    } else if (WIFSIGNALED(status)){
        cout << "Proces zakonczyl sie z sygnalem" << endl;
    }
}
return 0;

}


