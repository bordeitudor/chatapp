Un program simplu CLI de transmis mesaje intre clienti prin intermediul unui server.\
\
Programul este compatibil doar cu Windows, deoarece se foloseste de API-ul [Winsock2](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/) pentru networking.\
Scris in C++17 si realizat ca tema pentru ora de Informatica.

# Cum functioneaza
## Clientul
* Se conecteaza la server prin intrarea adresei serverului si intrarea unui nume de utilizator.
* Poate scrie un mesaj prin tastatura, mesaj care este trimis catre server.
* Citeste fiecare mesaj trimis de catre server.
## Serverul
* Citeste un mesaj de la un client, si distribuie acelasi mesaj tuturor clientilor cu exceptia celui care a trimis mesajul.
* Poate trimite mesaje de unul singur, mesaje care sunt ulterior distribuite tuturor clientilor. (ex: mesajul de deconectare al clientului)
# Necesitati pentru build
[GNU make v3.81](https://gnuwin32.sourceforge.net/packages/make.htm)\
[clang v18.1.8](https://github.com/llvm/llvm-project/releases/tag/llvmorg-18.1.8)

# Demonstratie
<video src="./docs/demonstratie.mp4"></video>