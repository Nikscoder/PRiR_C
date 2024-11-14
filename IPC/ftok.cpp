#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#define COMMON_FILE_NAME "ftok.txt"

using namespace std;
int main(){

struct dane_osobowe {
    char imie[30];
    char nazwisko[30];
    int wiek;
};

struct dane_osobowe_msgbuf{
    long mtype; //rodzaj komunikatu, musi byc > 0
    struct dane_osobowe osoba_info; 
};
dane_osobowe_msgbuf user1 = {5, {"user1", "X", 12}};
dane_osobowe_msgbuf user2 = {2, {"user2", "Y", 20}};

size_t msgsz = sizeof(struct dane_osobowe);
//create an identifier key
key_t key = ftok(COMMON_FILE_NAME, 'A');
cout << "Key: " << key << endl;

//create message queue
int msgid = msgget(key, 0666 | IPC_CREAT);
int i=10;
while (i>0){
    cout <<" Sending..." << endl;
    msgsnd(msgid, &user1, msgsz, 0);
    msgsnd(msgid, &user2, msgsz, 0);
    //sleep(5);
    cout << "user1: "<< &user1 << endl;
    cout << "user2: "<< &user2 << endl;

    //zmienna do przechowywania odebranej wiadomosci
    dane_osobowe_msgbuf received_message; 

    //odbieranie komunikatu o typie 5
    msgrcv(msgid, &received_message, msgsz, 0, 0);

    cout << "Received for: " << received_message.osoba_info.imie << ", "
     << received_message.osoba_info.nazwisko << ", "
     << received_message.osoba_info.wiek << endl;
     i--;
     cout << "i = "<< i << endl;
    }
//usuniecie kolejki
msgctl(msgid, IPC_RMID, NULL);
}
