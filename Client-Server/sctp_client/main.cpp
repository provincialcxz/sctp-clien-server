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

struct Command {
    int commandType;
};

class Client 
{
    int clientSock;
public:
    Client() : clientSock(-1) {}

    ~Client() { StopClient(); }

    void StartClient() {
        clientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);

        if (clientSock == -1) 
        {
            std::cerr << "Не удалось создать сокет" << std::endl;
            exit(1);
        }

        struct sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(SERVER_PORT);

        if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) <= 0) 
        {
            std::cerr << "Неверный IP адрес" << std::endl;
            exit(1);
        }

        if (connect(clientSock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) 
        {
            std::cerr << "Ошибка соединения с сервером" << std::endl;
            exit(1);
        }

        std::cout << "Соединение с сервером успешно установлено" << std::endl;
    }

    void send_recv_command() 
    {
        Command command;
        command.commandType = 0;

        while (true) 
        {
            ssize_t bytesSent = sctp_sendmsg(clientSock, &command, sizeof(command), NULL, 0, 0, 0, 0, 0, 0);
            if (bytesSent < 0) 
            {
                std::cerr << "Ошибка при отправке команды серверу" << std::endl;
                break;
            }

            ssize_t bytesRead = sctp_recvmsg(clientSock, &command, sizeof(command), NULL, 0, NULL, NULL);
            if (bytesRead < 0) 
            {
                std::cerr << "Ошибка при приеме команды от сервера" << std::endl;
                break;
            }

            if (bytesRead == 0) 
            {
                break;
            }

            std::cout << "Получена команда: " << command.commandType << std::endl;

            command.commandType++;

            sleep(1);
        }
    }

    void recv_data() 
    {
        std::ofstream file("received_data.txt", std::ios::binary);

        if (!file.is_open()) 
        {
            std::cerr << "Ошибка открытия файла" << std::endl;
            return;
        }

        char buffer[MAX_BUFFER_SIZE];
        ssize_t bytesRead;

        while (true) 
        {
            bytesRead = sctp_recvmsg(clientSock, buffer, sizeof(buffer), NULL, 0, NULL, NULL);
            if (bytesRead < 0) 
            {
                std::cerr << "Ошибка при приеме данных от сервера" << std::endl;
                break;
            }

            if (bytesRead == 0) 
            {
                break;
            }

            std::cout << "Пишем файл" << std::endl;

            file.write(buffer, bytesRead);
        }

        std::cout << "Файл получен" << std::endl;

        file.close();
    }

    void StopClient() 
    {
        shutdown(clientSock, 2);

        if (clientSock != -1) 
        {
            close(clientSock);
            clientSock = -1;
        }
    }
};

int main() 
{
    Client client;

    client.StartClient();

    auto command_thread = std::async([&]()
    {
        client.send_recv_command();
    });

    auto data_thread = std::async([&]() 
    {
        client.recv_data();
    });

    command_thread.get();
    data_thread.get();

    client.StopClient();

    return 0;
}