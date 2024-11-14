#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // for struct sockaddr_in
#include <arpa/inet.h>
#include <unistd.h>


using namespace std;
/* example of struct sockaddr_in
struct in_addr {
    unsigned long s_addr;
};

struct sockaddr_in {
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};
*/

int main(void) { 
    int size;
    int so;
    struct sockaddr_in server_addr;
    const char* server_ip = "127.0.0.1";
    int server_port = 8080;
    char buffer[1024];

    // tworzenie gniazda
    so = socket(PF_INET, SOCK_STREAM, 0);
    if (so<0){
        cerr << "Bład przy tworzeniu gniazda" << endl;
        return 1;
    }

    //konfiguracja adresu serwera
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    //Laczenie z serwerem
    if (connect(so, (struct sockaddr*)&server_addr, sizeof(sockaddr_in)) < 0) {
        cerr << "Nie mozna polaczyc sie z serwerem!" << endl;
        close(so);
        return 1;
    }

    cout << "Udalo sie polaczyc z serwerem ! " << endl; 

    // wysylanie wiadomosci do serwera 
    const char* message = "Czesc, serwer !";
    if (write(so, message, strlen(message)) < 0){
        cerr << "Blad przy wyslaniu wiadomosci !" << endl;
        close(so);
        return 1;
    }

    //Odbieranie wiadomosci od serwera
    memset(buffer, 0, sizeof(buffer));
    int bytes_received = read(so, buffer, sizeof(buffer)-1);
    if (bytes_received < 0) {
        cerr << "Blad przy odebraniu odpowiedzi" << endl;

    } else {
        cout << "Odpowiedz od serwera: " << buffer << endl;
    }

    close(so);
    return 0;
}
