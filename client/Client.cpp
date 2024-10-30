#include <conio.h>
#include <regex>
#include "WS2.h"
#include "Message.h"

void eatch(const int n = 1)
{
    for(int i = 0; i < n; ++i) {
	std::cout << "\b \b";
    }
}

/* functie de thread */
void readMsg(SOCKET& socket, const std::string& username, const std::string& input, addrinfo *result)
{   
    // Citim fiecare mesaj trimis de catre server, care include mesajele proprii ale serverului si toate mesajele trimise de catre alti clienti
    std::vector<char> msgbuf(MSGBUF_LEN);
    
    while(true) {
	int bytesReceived = recv(socket, msgbuf.data(), msgbuf.size(), 0);

	if(bytesReceived < 0) {
	    switch(ws2::error()) {
	    case WSAECONNRESET:
		std::cout << "\nServerul s-a inchis\n";
		break;
	    default:
		std::cerr << "EROARE: Primirea mesajului a esuat: " << ws2::strError() << " ";
		std::cerr << "(" << ws2::error() << ")\n";
		break;
	    }

	    closesocket(socket);
	    freeaddrinfo(result);
	    WSACleanup();
	    exit(-1);
	} else if(bytesReceived > 0) {
	    msgbuf[bytesReceived] = 0;

	    Message msg = decodeMessage(std::string(msgbuf.data()));

	    std::string ioData = username + ": " + input;
	    size_t sz = username.size() + input.size() + 2;
	    
	    eatch(sz);
	    
	    if(msg.client) {
		std::cout << msg.sender << ": " << msg.content << "\n";
	    } else {
		std::cout << msgbuf.data() << "\n";
	    }

	    std::cout << ioData;
	}
    }
}

/* functie de thread */
void sendMsg(std::mutex& mut, SOCKET& socket, std::string& msg, bool& msgFinished, addrinfo *result)
{
    // Trimitem mesajul finalizat catre server
    std::lock_guard<std::mutex> lg(mut);

    while(true) {
	if(msgFinished) {
	    int bytesSent = send(socket, msg.data(), msg.size(), 0);
	    if(bytesSent < 0) {
		std::cerr << "EROARE: Trimiterea mesajului a esuat: " << ws2::strError() << " ";
		std::cerr << "(" << bytesSent << ")\n";

		closesocket(socket);
		freeaddrinfo(result);
		WSACleanup();
		exit(-1);
	    }

	    msg.clear();
	    msgFinished = false;
	}
    }
}

int main(int argc, char **argv)
{
    // Initializam interfata de intrare-iesire in retea
    WSADATA wsaData;
    ws2::startup(wsaData);

    // Citim adresa ip a serverului
    std::string address;


    while(address.empty()) {
	std::cout << "Adresa serverului: ";
	std::getline(std::cin, address);

	// Regexul e luat de pe internet, e pentru verificarea validitatii intrarii
	std::regex regex("^(localhost|((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)))$");
	if(!std::regex_search(address, regex)) {
	    std::cout << "Adresa invalida!\n";
	    address.clear();
	}
    }
    
    std::string username;


    while(username.empty()) {
	std::cout << "Numele de utilizator: ";
	std::getline(std::cin, username);

	std::regex regex("[a-zA-Z0-9_]");
	if(!std::regex_search(username, regex)) {
	    std::cout << "Nume invalid!\n";
	    username.clear();
	}
    }
    
    
    if(address == "localhost") {
	address = "127.0.0.1";
    }
    
    std::string port = DEFAULT_PORT;
    
    auto addrName = [&]() {
	return (address + ":" + port);
    };
    
    addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_protocol = IPPROTO_TCP;
    
    if (getaddrinfo(address.data(), DEFAULT_PORT, &hints, &result) != 0) {
	std::cerr << "EROARE: Rezolvarea adresei gazdei " << addrName() << " a esuat: " << ws2::strError() << " ";
	std::cerr << "(" << ws2::error() << ")\n";
	WSACleanup();
	return -1;
    }

    SOCKET cSocket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
    if(cSocket == INVALID_SOCKET) {
	std::cerr << "EROARE: Crearea socketului a esuat: " << ws2::strError() << " ";
	std::cerr << "(" << ws2::error() << ")\n";
	freeaddrinfo(result);
	WSACleanup();
	return -1;
    }

    size_t tries = 0;
    std::cout << "Se asteapta conexiunea cu adresa " << addrName() << " (" << tries << ")";
    while(true) {
	for(addrinfo *node = result; node; node = node->ai_next) {
	    auto connectCode = ws2::connect(cSocket, result->ai_addr, result->ai_addrlen);

	    if(connectCode == SOCKET_ERROR) {

		switch(ws2::error()) {
		case WSAECONNREFUSED:
		    break;
		default:
		    std::cerr << "EROARE: Conectarea cu adresa " << addrName() << " a esuat: " << ws2::strError() << " ";
		    std::cerr << "(" << ws2::error() << ")\n";

		    freeaddrinfo(result);
		    closesocket(cSocket);
		    WSACleanup();
		    exit(-1);
		    break;
		}
		
	    } else {
		goto _connected;
	    }
	}
	std::string oldTriesString = "(" + std::to_string(tries) + ")";
	eatch(oldTriesString.size());
	std::cout << "(" << ++tries << ")";
    }
 _connected:
    std::cout << "\n";
    std::cout << "Conectarea cu adresa " << addrName() << " a reusit\n";

    bool msgFinished = false;
    std::string msg = "";
    std::string input = "";
    std::mutex mSendMsg;

    // Trimitem numele nostru serverului
    {
	auto bytesSent = send(cSocket, username.data(), username.size(), 0);
	if(bytesSent <= 0) {
	    assert(false && "COULDNT SEND USERNAME");
	}
    }
    
    std::thread tSendMsg(sendMsg, std::ref(mSendMsg), std::ref(cSocket), std::ref(msg), std::ref(msgFinished), result);
    tSendMsg.detach();

    std::thread tReadMsg(readMsg, std::ref(cSocket), std::ref(username), std::ref(input), result);
    tReadMsg.detach();
    
    do {
	std::cout << username << ": ";
	for(int ch = _getch(); ch != '\r'; ch = _getch()) {
	    if(ch == '\b') {
		if(!input.empty()) {
		    input = input.substr(0, input.size()-1);
		    std::cout << "\b \b";
		}
	    } else {
		input += static_cast<char>(ch);
		std::cout << static_cast<char>(ch);
	    }
	}
	std::cout << "\n";
	msg = "@" + username + "," + input;
	input.clear();
	msgFinished = true;
    } while(true);
    
    closesocket(cSocket);
    freeaddrinfo(result);
    WSACleanup();
    return 0;
}
