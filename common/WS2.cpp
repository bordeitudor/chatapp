#include "WS2.h"

namespace ws2 {

std::string strError(const int error)
{
    switch(error) {
    case WSA_INVALID_HANDLE: return "Event handle invalid";
    case WSA_NOT_ENOUGH_MEMORY: return "Memorie insuficienta";
    case WSA_INVALID_PARAMETER: return "Parametru invalid";
    case WSA_OPERATION_ABORTED: return "Operatie oprita";
    case WSA_IO_INCOMPLETE: return "Obiectul-eveniment de intrare/iesire nu este in stare semnalata";
    case WSA_IO_PENDING: return "Operatie de intrare/iesire este in decurs";
    case WSAEINTR: return "Apel de functie interupt";
    case WSAEBADF: return "Handle de fisier invalid";
    case WSAEACCES: return "Acces interzis";
    case WSAEFAULT: return "Adresa invalida";
    case WSAEINVAL: return "Argument invalid";
    case WSAEMFILE: return "Prea multe fisiere deschise!";
    case WSAEWOULDBLOCK: return "Resursa temporar inaccesibila";
    case WSAEINPROGRESS: return "Operatie in decurs";
    case WSAEALREADY: return "Operatie deja in decurs";
    case WSAENOTSOCK: return "Operatie efectuata pe obiect non-socket";
    case WSAEDESTADDRREQ: return "Adresa de destinatie este necesara";
    case WSAEMSGSIZE: return "Mesaj prea lung";
    case WSAEPROTOTYPE: return "Tip de protocol gresit folosit pentru socket";
    case WSAENOPROTOOPT: return "Tip de protocol invalid";
    case WSAEPROTONOSUPPORT: return "Tip de protocol nesuportat";
    case WSAESOCKTNOSUPPORT: return "Tip de socket nesuportat";
    case WSAEOPNOTSUPP: return "Operatie nesuportata";
    case WSAEPFNOSUPPORT: return "Familie de protocol nesuportata";
    case WSAEADDRINUSE: return "Adresa deja este in uz";
    case WSAEADDRNOTAVAIL: return "Adresa nu este valabila";
    case WSAENETDOWN: return "Reteaua a picat";
    case WSAENETUNREACH: return "Reteaua este indisponibila";
    case WSAENETRESET: return "Conexiunea retelei s-a restartat";
    case WSAECONNABORTED: return "Conexiunea retelei a picat";
    case WSAECONNRESET: return "Reteaua s-a inchis";
    case WSAENOBUFS: return "Spatiul de buffer este nul";
    case WSAEISCONN: return "Socketul este deja conectat";
    case WSAENOTCONN: return "Socketul nu este conectat";
    case WSAESHUTDOWN: return "Cererea de trimitere sau primire a datei este inchisa";
    case WSAETOOMANYREFS: return "Prea multe referinte la un obiect kernel";
    case WSAETIMEDOUT: return "Conexiune incheiata pe motiv de time-out";
    case WSAECONNREFUSED: return "Conexiunea s-a refuzat";
    case WSAELOOP: return "Nume imposibil de transpus";
    case WSAENAMETOOLONG: return "Nume prea lung";
    case WSAEHOSTDOWN: return "Gazda a picat";
    case WSAEHOSTUNREACH: return "Nu exista o ruta catre gazda";
    case WSAENOTEMPTY: return "Directorul nu este gol";
    case WSAEPROCLIM: return "Prea multe procese";
    case WSAEUSERS: return "Cota de utilizatori atinsa";
    case WSAEDQUOT: return "Cota de disc atinsa";
    case WSAESTALE: return "Referinta unui handle de fisier nu mai este valabila";
    case WSAEREMOTE: return "Itemul este remote";
    case WSASYSNOTREADY: return "Subsistemul retelei nu este valabil";
    case WSAVERNOTSUPPORTED: return "Discrepanta in librarie si implementare a WS2";
    case WSANOTINITIALISED: return "WS2 nu a fost initializat";
    case WSAEDISCON: return "O inchidere este in decurs";
    case WSAENOMORE: case WSA_E_NO_MORE: return "Nu mai exista rezultate";
    case WSAECANCELLED: return "Apelul a fost anulat";
    case WSAEINVALIDPROCTABLE: return "Tablou de proceduri de apelare invalid";
    case WSAEINVALIDPROVIDER: return "Furnizor de servicii invalid";
    case WSAEPROVIDERFAILEDINIT: return "Initializarea furnizorul de servicii a esuat";
    case WSASYSCALLFAILURE: return "Eroarea apelarii unui apel de sistem";
    case WSASERVICE_NOT_FOUND: return "Serviciu inexistent";
    case WSATYPE_NOT_FOUND: return "Tip de clasa inexistent";
    case WSA_E_CANCELLED: return "Apel anulat";
    case WSAEREFUSED: return "Interogarea bazei de date a fost refuzata";
    case WSAHOST_NOT_FOUND: return "Gazda inexistenta";
    case WSATRY_AGAIN: return "Gazda non-autoritativa inexistenta";
    case WSANO_RECOVERY: return "Eroare catastrofala";
    case WSANO_DATA: return "Date inexistente";
    case WSA_QOS_RECEIVERS: return "Cel putin o rezerva QoS a ajuns";
    case WSA_QOS_SENDERS: return "Cel putin o cale de expediere QoS a ajuns";
    case WSA_QOS_NO_SENDERS: return "Expediatori QoS inexistenti";
    case WSA_QOS_NO_RECEIVERS: return "Primitori QoS inexistenti";
    case WSA_QOS_REQUEST_CONFIRMED: return "Cerere QoS confirmata";
    case WSA_QOS_ADMISSION_FAILURE: return "Admisie QoS esuata din cauza lipsei de resurse";
    case WSA_QOS_POLICY_FAILURE: return "Cererea QoS a fost respinsa pentru ca sistemul de polite nu a putut aloca resursa ceruta in polita existenta";
    case WSA_QOS_BAD_STYLE: return "Stil QoS invalid";
    case WSA_QOS_BAD_OBJECT: return "Object QoS invalid";
    case WSA_QOS_TRAFFIC_CTRL_ERROR: return "Eroare in controlul traficului QoS";
    case WSA_QOS_GENERIC_ERROR: return "Eroare QoS generica";
    case WSA_QOS_ESERVICETYPE: return "Eroare QoS de tip serviciu";
    case WSA_QOS_EFLOWSPEC: return "Eroare QoS flowspec";
    case WSA_QOS_EPROVSPECBUF: return "Buffer QoS de furnizor invalid";
    case WSA_QOS_EFILTERSTYLE: return "Stil QoS de filtru invalid";
    case WSA_QOS_EFILTERTYPE: return "Tip QoS de filtru invalid";
    case WSA_QOS_EFILTERCOUNT: return "Numaratoare incorecta de filtre QoS";
    case WSA_QOS_EOBJLENGTH: return "Lungime de obiect QoS invalida";
    case WSA_QOS_EFLOWCOUNT: return "Numaratoare incorecta de descriptori flow QoS";
    case WSA_QOS_EUNKOWNPSOBJ: return "Obiect QoS necunoscut";
    case WSA_QOS_EPOLICYOBJ: return "Obiect QoS de polita necunoscut";
    case WSA_QOS_EFLOWDESC: return "Descriptor QoS invalid";
    case WSA_QOS_EPSFLOWSPEC: return "Flowspec QoS specific de furnizor invalid sau inconsistent";
    case WSA_QOS_EPSFILTERSPEC: return "Filterspec QoS specific de furnizor invalid";
    case WSA_QOS_ESDMODEOBJ: return "Obiect QoS de tip de decartare al formei invalid";
    case WSA_QOS_ESHAPERATEOBJ: return "Obiect QoS de tip al ratii de formare invalid";
    case WSA_QOS_RESERVED_PETYPE: return "Tip de element de polita QoS rezervat";
    case 0: return "";
    default: assert(false && "WS2 ERROR UNACCOUNTED FOR");
    }
    return "UNREACHABLE";
}

void startup(WSADATA& wsaData)
{
    auto code = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(code != 0) {
	std::cerr << "EROARE: Initializarea networkingului a esuat: " << ws2::strError(code) << "\n";
	exit(-1);
    }
}

void getAddressInfo(const char *name, const char *service, addrinfo& hints, addrinfo** result)
{
    auto code = getaddrinfo(name, service, &hints, result);
    if(code != 0) {
	std::cerr << "EROARE: Cautarea adresei a esuat: " << ws2::strError(code) << "\n";
	exit(-1);
    }
}

SOCKET createSocket(const int family, const int type, const int protocol)
{
    SOCKET result = socket(family, type, protocol);

    if(result == INVALID_SOCKET) {
	std::cerr << "EROARE: Crearea socketului a esuat: " << ws2::strError() << "\n";
        exit(-1);
    }
    
    return result;
}

int connect(const SOCKET socket, const sockaddr *addr, const size_t len)
{
    return ::connect(socket, addr, static_cast<int>(len));
}

void bind(const SOCKET socket, const sockaddr *addr, const size_t len)
{
    auto code = bind(socket, addr, static_cast<int>(len));
    if(code != 0) {
	std::cerr << "EROARE: Atasarea socketului de ascultare a esuat: " << ws2::strError() << "\n";
	exit(-1);
    }
}

void listen(const SOCKET socket, const int maxConnections)
{
    auto code = ::listen(socket, maxConnections);
    if(code != 0) {
	std::cerr << "EROARE: Ascultarea pe socket a esuat: " << ws2::strError() << "\n";
	exit(-1);
    }
}

int error()
{
    return WSAGetLastError();
}

} // namespace ws2
