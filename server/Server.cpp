#include "WS2.h"
#include "Client.h"
#include "Message.h"

/* functie de thread */
void dist(std::mutex& mMut, std::mutex& cMut, std::list<Client>& clients, std::list<std::string>& messages, addrinfo* result) {
    // Distribuim fiecare mesaj trimis de catre clienti, si pentru fiecare mesaj, trimitem mesajul tuturor celorlalti clienti
    
    while (true) {
        std::vector<std::string> msgToSend;
        {
            std::lock_guard<std::mutex> lock(mMut);
            if (!messages.empty()) {
                msgToSend.insert(msgToSend.end(), messages.begin(), messages.end());
                messages.clear();
            }
        }
        if (!msgToSend.empty()) {
            for (auto& msgData : msgToSend) {
                std::lock_guard<std::mutex> lock(cMut);
                for (auto it = clients.begin(); it != clients.end(); ++it) {
                    auto& client = *it;
                    auto msg = decodeMessage(msgData);
                    if (client.username != msg.sender) {
                        int bytesSent = send(client.socket, msgData.data(), msgData.size(), 0);
                        if (bytesSent < 0) {
                            if(ws2::error() == WSAENOTSOCK) {
				it = clients.erase(it);
				it--;
				continue;
			    } else {
				std::cerr << "EROARE: Trimiterea mesajului catre clientul " << client.username << " a esuat: " << ws2::strError() << " ";
				std::cerr << "(" << ws2::error() << ")\n";
				closesocket(client.socket);
				freeaddrinfo(result);
				WSACleanup();
				exit(-1);
                            }
                        }
                    }
                }
            }
        }
    }
}

/* functie de thread */
void read(std::mutex& mMut, std::mutex& cMut, std::list<Client>& clients, Client& thisClient, std::list<std::string>& messages, addrinfo* result) {
    // Citim toate mesajele trimise de catre clienti, si le punem intr-un tablou 

    std::vector<char> msgbuf(MSGBUF_LEN);
    int bytesReceived = 0;

    while (bytesReceived >= 0) {
        bytesReceived = recv(thisClient.socket, msgbuf.data(), msgbuf.size(), 0);
        if (bytesReceived < 0) {
            switch (ws2::error()) {
                case WSAECONNRESET:
		    mMut.lock();
                    messages.push_back("Clientul " + thisClient.username + " s-a deconectat");
		    mMut.unlock();
                    closesocket(thisClient.socket);
                    return;
                default:
                    std::cerr << "EROARE: Primirea de date de la clientul " << thisClient.username << " a esuat: " << ws2::strError() << " ";
                    std::cerr << "(" << ws2::error() << ")\n";
                    closesocket(thisClient.socket);
                    clients.erase(std::remove(clients.begin(), clients.end(), thisClient), clients.end());
                    freeaddrinfo(result);
                    WSACleanup();
                    exit(-1);
                    break;
            }
        } else if (bytesReceived > 0) {
            msgbuf[bytesReceived] = 0;
            mMut.lock();
            messages.push_back(std::string(msgbuf.data()));
            mMut.unlock();
        }
    }
}


int main() {
    WSADATA wsaData;
    ws2::startup(wsaData);
    addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Rezolvam adresa serverului cu un port specific
    if (getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result) != 0) {
        std::cerr << "EROARE: Rezolvarea propriei adrese a esuat: " << ws2::strError() << " ";
        std::cerr << "(" << ws2::error() << ")\n";
        WSACleanup();
        return -1;
    }
    // Cream un socket pentru server, socketul fiind un obiect care stabileste legaturi intre calculatoare
    SOCKET lSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (lSocket == INVALID_SOCKET) {
        std::cerr << "EROARE: Crearea socketului a esuat: " << ws2::strError() << " ";
        std::cerr << "(" << ws2::error() << ")\n";
        freeaddrinfo(result);
        WSACleanup();
        return -1;
    }
    // Legam socketul serverului, ca sa poata accepta conexiuni de la clienti
    if (bind(lSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        std::cerr << "EROARE: Legarea socketului a esuat: " << ws2::strError() << " ";
        std::cerr << "(" << ws2::error() << ")\n";
        closesocket(lSocket);
        freeaddrinfo(result);
        WSACleanup();
        return -1;
    }
    // Permitem serverului nostru sa asculte pentru conexiuni de la clienti
    if (listen(lSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "EROARE: Ascultarea socketului a esuat: " << ws2::strError() << " ";
        std::cerr << "(" << ws2::error() << ")\n";
        closesocket(lSocket);
        freeaddrinfo(result);
        WSACleanup();
        return -1;
    }

    bool running = true;
    std::list<Client> clients = {};
    std::list<std::string> messages = {};
    std::mutex mMut, cMut;

    std::cout << "Serverul asteapta conexiuni\n";
    std::thread tOutput(dist, std::ref(mMut), std::ref(cMut), std::ref(clients), std::ref(messages), result);
    tOutput.detach();
    do {
        Client temp;
        temp.socket = accept(lSocket, nullptr, nullptr);
        // Sarim peste socketuri care n-au reusit sa se conecteze
        if (!temp) continue;
        clients.push_back(std::move(temp));
        Client& client = clients.back();
        // Obtinem numele clientului
        {
            std::vector<char> namebuf(MSGBUF_LEN);
            int bytesReceived = recv(client.socket, namebuf.data(), namebuf.size(), 0);
            if (bytesReceived < 0) {
                assert(false && "USERNAME MUST BE PASSED");
            } else if (bytesReceived > 0) {
                namebuf[bytesReceived] = 0;
                client.username = std::string(namebuf.data());
            }
        }
        
        std::thread tInput(read, std::ref(mMut), std::ref(cMut), std::ref(clients), std::ref(client), std::ref(messages), result);
        tInput.detach();
        messages.push_back("S-a conectat clientul " + client.username);
    } while (running);
    closesocket(lSocket);
    freeaddrinfo(result);
    WSACleanup();
    return 0;
}
