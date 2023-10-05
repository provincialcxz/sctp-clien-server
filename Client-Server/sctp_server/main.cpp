#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/sctp.h>
#include <fstream>
#include <future>

const int SERVER_PORT = 8080;
const int MAX_BUFFER_SIZE = 1024;

struct Command 
{
    int commandType;
};

class Server 
{
    int serverSock;
    int clientSock;
public:
    Server() : serverSock(-1), clientSock(-1) {}

    ~Server() { StopServer(); }

    void StartServer() 
    {
        serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);

        if (serverSock == -1) 
        {
            std::cerr << "Не удалось создать сокет" << std::endl;
            exit(1);
        }

        struct sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(SERVER_PORT);

        if (bind(serverSock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) 
        {
            std::cerr << "Ошибка привязки сокета к адресу и порту" << std::endl;
            exit(1);
        }

        std::cout << "Сервер запущен. Ожидание подключения клиента..." << std::endl;

        if (listen(serverSock, 1) < 0) 
        {
            std::cerr << "Ошибка при прослушивании входящих соединений" << std::endl;
            exit(1);
        }

        sockaddr_in clientAddress{};
        socklen_t clientAddressSize = sizeof(clientAddress);

        clientSock = accept(serverSock, (struct sockaddr *)&clientAddress, &clientAddressSize);
        if (clientSock < 0) 
        {
            std::cerr << "Ошибка при принятии входящего соединения" << std::endl;
            exit(1);
        }

        std::cout << "Клиент успешно подключен" << std::endl;
    }

    void StopServer() 
    {
        shutdown(clientSock, 2);
        shutdown(serverSock, 2);
        
        if (clientSock != -1) 
        {
            close(clientSock);
            clientSock = -1;
        }

        if (serverSock != -1) 
        {
            close(serverSock);
            serverSock = -1;
        }
    }

    void recv_send_command() 
    {
        Command command;
        command.commandType = 0;

        while (true) 
        {
            ssize_t bytesRead = sctp_recvmsg(clientSock, &command, sizeof(command), NULL, 0, NULL, NULL);
            if (bytesRead < 0) 
            {
                std::cerr << "Ошибка при приеме команды от клиента" << std::endl;
                break;
            }

            if (bytesRead == 0) 
            {
                break;
            }

            std::cout << "Получена команда: " << command.commandType << std::endl;

            command.commandType++;

            ssize_t bytesSent = sctp_sendmsg(clientSock, &command, sizeof(command), NULL, 0, 0, 0, 0, 0, 0);
            if (bytesSent < 0) 
            {
                std::cerr << "Ошибка при отправке команды клиенту" << std::endl;
                break;
            }
        }
    }

    void send_data() 
    {
        std::ifstream file("/home/erema/Desktop/conspect_socket", std::ios::binary);

        if (!file.is_open()) 
        {
            std::cerr << "Ошибка открытия файла" << std::endl;
            return;
        }

        char buffer[MAX_BUFFER_SIZE];
        while (!file.eof()) 
        {
            std::cout << "Читаем файл" << std::endl;
            file.read(buffer, sizeof(buffer));
            ssize_t bytesSent = sctp_sendmsg(clientSock, buffer, file.gcount(), NULL, 0, 0, 0, 0, 0, 0);
            if (bytesSent < 0) 
            {
                std::cerr << "Ошибка при отправке данных клиенту" << std::endl;
                break;
            }
        }

        std::cout << "Файл отправлен" << std::endl;

        file.close();
    }
};

int main() 
{
    Server server;

    server.StartServer();

    auto command_thread = std::async([&]()
    {
        server.recv_send_command();
    });

    auto data_thread = std::async([&]()
    {
        server.send_data();
    });

    command_thread.get();
    data_thread.get();

    server.StopServer();

    return 0;
}