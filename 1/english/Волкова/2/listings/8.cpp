#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <map>

#define PORT 65100

#define BACKLOG 5
#define BUFFER_SIZE 1000
#define FLAGS 0

// Коллекция для хранения пар значений:
// сокет + идентификатор потока
std::map<int, pthread_t> threads;
// Серверный сокет
int serverSocket;

// Обработчик сигнала прерывания (корректное завершение приложения)
void signalHandler(int sig);
// Обработчик клиентского потока
void* clientExecutor(void* clientSocket);
// Функция считывания строки символов с клиента
int readLine(int socket, char* buffer, int bufferSize, int flags);
// Функция отправки строки символов клиенту
int sendLine(int socket, char* buffer, int flags);
// Корректное закрытие сокета
void closeSocket(int socket);
// Завершение работы клиентского потока
void destroyClient(int socket);

int main(int argc, char** argv) {
	int port = PORT;
	if(argc < 2)
		printf("Using default port: %d.\n", port);
	else
		port = atoi(argv[1]);

	// Создание серверного сокета
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(serverSocket < 0) {
		perror("It's impossible to create socket");
		return 0x1;	
	}
	
	printf("Server socket %d created.\n", serverSocket);

	// Структура, задающая адресные характеристики
	struct sockaddr_in info;
	info.sin_family = AF_INET;
	info.sin_port = htons(port);
	info.sin_addr.s_addr = htonl(INADDR_ANY);

	// Биндим сервер на определенный адрес
	int serverBind  = bind(serverSocket, (struct sockaddr *) &info, sizeof(info));
	if(serverBind < 0) {
		perror("It's impossible to bind socket");
		return 0x2;	
	}

	// Слушаем сокет
	int serverListen = listen(serverSocket, BACKLOG);
	if(serverListen != 0) {
		perror("It's impossible to listen socket");
		return 0x3;
	}

	// Обработка прерывания для корректного завершения приложения
	signal(SIGINT, signalHandler);

	printf("Wait clients.\n");

	while(1) {
		// Ждем подключения клиентов
		int clientSocket = accept(serverSocket, NULL, NULL);
		
		// Пробуем создать поток обработки клиентских сообщений
		pthread_t thread;
		int result = pthread_create(&thread, NULL, clientExecutor, (void *) &clientSocket);	
		if(result) {
			perror("It's impossible to create new thread");
			closeSocket(clientSocket);
		}

		// Добавляем в коллекцию пару значений: сокет + идентификатор потока
		threads.insert(std::pair<int, pthread_t>(clientSocket, thread));
	}

	return 0x0;	
}

void signalHandler(int sig) {
	// Для всех элементов коллекции
	for(std::map<int, pthread_t>::iterator current = threads.begin(); current != threads.end(); ++current) {
		printf("Try to finish client with socket %d\n", current->first);
		// Закрываем клиентские сокеты
		closeSocket(current->first);
		printf("Client socket %d closed.\n", current->first);
	}

	// Закрываем серверный сокет
	closeSocket(serverSocket);
	printf("Server socket %d closed.\n", serverSocket);
	
	exit(0x0);
}

void* clientExecutor(void* socket) {
	int clientSocket = *((int*) socket);

	printf("Client thread with socket %d created.\n", clientSocket);

	char buffer[BUFFER_SIZE];
	while(1) {
		// Ожидаем прибытия строки
		int result = readLine(clientSocket, buffer, BUFFER_SIZE, FLAGS);
		if(result < 0)
			destroyClient(clientSocket);

		if(strlen(buffer) <= 1)
			destroyClient(clientSocket);
			
		printf("Client message: %s\n", buffer);

		// Отправляем строку назад
		result = sendLine(clientSocket, buffer, FLAGS);
		if(result < 0)
			destroyClient(clientSocket);	
	}
}

int readLine(int socket, char* buffer, int bufferSize, int flags) {
	// Очищаем буфер
	bzero(buffer, bufferSize);

	char resolvedSymbol = ' ';
	for(int index = 0; index < BUFFER_SIZE; ++index) {
		// Считываем по одному символу
		int readSize = recv(socket, &resolvedSymbol, 1, flags);
		if(readSize <= 0)
		    return -1;
		else if(resolvedSymbol == '\n')
		    break;
		else if(resolvedSymbol != '\r')
		    buffer[index] = resolvedSymbol;
	}
	
	return 0x0;
}

int sendLine(int socket, char* buffer, int flags) {
	unsigned int length = strlen(buffer);

	// Перед отправкой сообщения добавляем в конец перевод строки
	if(length == 0)
		return -1;
	else if(buffer[length - 1] != '\n') {
		if(length >= BUFFER_SIZE)
			return -1;
		else
			buffer[length] = '\n';
		
	}
	
	length = strlen(buffer);

	// Отправляем строку клиенту
	int result = send(socket, buffer, length, flags);
	return result;
}

void closeSocket(int socket) {
	// Завершение работы сокета
	int socketShutdown = shutdown(socket, SHUT_RDWR);
    	if(socketShutdown != 0)
		perror("It's impossible to shutdown socket");

	// Закрытие сокета
	int socketClose = close(socket);
    	if(socketClose != 0)
		perror("It's impossible to close socket");
}

void destroyClient(int socket) {
	printf("It's impossible to receive message from client or send message to client.\n");
	// Завершение работы сокета
	closeSocket(socket);
	// Удаление пары значений из коллекции по ключю
	threads.erase(socket);
	printf("Client socket %d closed.\n", socket);
	// Завершение работы потока
	pthread_exit(NULL);
}

