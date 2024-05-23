#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996) 

#define BUFLEN 512
#define PORT 8888
#define WIDTH 1024
#define HEIGHT 1024

void displayerNameInput(sf::RenderWindow& window, std::string& playerName);
void checkPlayerWin(int board[3][3], sf::RenderWindow& window);

bool hasGameEnded = false;

class UDPServer {
public:
    UDPServer() {
        // initialise winsock
        cout << "Initialising Winsock...\n";
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            cout << "Failed. Error Code: " << WSAGetLastError() << "\n";
            exit(0);
        }
        cout << "Initialised.\n";

        // create a socket
        if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
            cout << "Could not create socket: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }
        cout << "Socket created.\n";

        // prepare the sockaddr_in structure
        server.sin_family = AF_INET; // AF_INET = IPv4 addresses
        server.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY = localhost
        server.sin_port = htons(PORT); // htons = host to network short

        // bind
        if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
            cout << "Bind failed with error code: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }
        cout << "Bind done.\n";
    }

    ~UDPServer() {
        closesocket(server_socket);
        WSACleanup();
    }

    void start() {

        sf::ContextSettings settings;
        settings.depthBits = 24;
        sf::RenderWindow window(sf::VideoMode(1024, 1024, 32), "Enter your name", sf::Style::Titlebar | sf::Style::Close, settings);
        window.setFramerateLimit(20);
        glewExperimental = GL_TRUE;
        glewInit();

        bool isConnected = false;
        int localIsX = 0, isX = 0;
        int board[3][3] = {};

        std::string playerName;

        displayerNameInput(window, playerName);

        if (playerName.empty())
            playerName = "Player";

        printf("Hello, %s!\n", playerName.c_str());

        window.create(sf::VideoMode(WIDTH, HEIGHT), "Tic Tac Toe Server Side", sf::Style::Titlebar | sf::Style::Close, settings);
        window.setFramerateLimit(20);

        u_long mode = 1;
        if (ioctlsocket(server_socket, FIONBIO, &mode) != NO_ERROR) {
            cout << "ioctlsocket() failed with error code: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }

        while (!exitRequested && window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type ==
                    sf::Event::Closed)
                    window.close();
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (int i = 0; i < 3; i++)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(0, HEIGHT * i / 3)),
                    sf::Vertex(sf::Vector2f(1024, HEIGHT * i / 3))
                };
                window.draw(line, 2, sf::Lines);

                sf::Vertex line2[] =
                {
                    sf::Vertex(sf::Vector2f(WIDTH * i / 3, 0)),
                    sf::Vertex(sf::Vector2f(WIDTH * i / 3, HEIGHT))
                };
                window.draw(line2, 2, sf::Lines);
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[i][j] == 1)
                    {
                        sf::Vertex line[] =
                        {
                            sf::Vertex(sf::Vector2f(WIDTH * i / 3, HEIGHT * j / 3)),
                            sf::Vertex(sf::Vector2f(WIDTH * i / 3 + WIDTH / 3, HEIGHT * j / 3 + HEIGHT / 3))
                        };
                        window.draw(line, 2, sf::Lines);

                        sf::Vertex line2[] =
                        {
                            sf::Vertex(sf::Vector2f(WIDTH * i / 3 + WIDTH / 3, HEIGHT * j / 3)),
                            sf::Vertex(sf::Vector2f(WIDTH * i / 3, WIDTH * j / 3 + HEIGHT / 3))
                        };
                        window.draw(line2, 2, sf::Lines);
                    }
                    else if (board[i][j] == 2)
                    {
                        sf::CircleShape circle((WIDTH + HEIGHT) * 0.5 / 6);
                        circle.setPosition(WIDTH * i / 3, HEIGHT * j / 3);
                        window.draw(circle);
                    }
                }
            }

            fd_set readSet;
            FD_ZERO(&readSet);
            FD_SET(server_socket, &readSet);

            timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 0;

            int selectResult = select(server_socket + 1, &readSet, NULL, NULL, &timeout); // UDP select call
            if (selectResult == SOCKET_ERROR) {
                cout << "select() failed with error code: " << WSAGetLastError() << "\n";
                exit(EXIT_FAILURE);
            }
            else if (selectResult > 0) {
                if (FD_ISSET(server_socket, &readSet)) {
                    // Data is available, receive it
                    char message[BUFLEN] = {};
                    int slen = sizeof(sockaddr_in);
                    int message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen);
                    if (message_len == SOCKET_ERROR) {
                        cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
                        exit(EXIT_FAILURE);
                    }

                    // Process received data...
                    cout << "Received packet from " << inet_ntoa(client.sin_addr) << " " << ntohs(client.sin_port) << "\n";
                    cout << "Data: " << message << "\n";

                    // Process the received message and update game state...
                    if (!isConnected)
                    {
                    	isConnected = true;
                        continue;
					}
                    if (localIsX == 0)
                    {
                        isX = 1;
                        localIsX = -1;
                    }
                    board[message[message_len - 3] - '0'][message[message_len - 1] - '0'] = isX == 1 ? 1 : 2;

                    isX *= -1;
                }
            }
            char message[BUFLEN];

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !hasGameEnded && isX == localIsX)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = mousePos.x / (WIDTH / 3);
                int y = mousePos.y / (HEIGHT / 3);

                if (board[x][y] == 0)
                {
                    if (isX == 0)
                    {
                        isX = 1;
                        localIsX = 1;
                    }

                    board[x][y] = isX == 1 ? 1 : 2;
                    printf("board[%d][%d] = %d\n", x, y, board[x][y]);
                    isX *= -1;

                    // Send the updated game state to the client
                    sprintf(message, "%s: %d %d", playerName.c_str(), x, y);
                    if (sendto(server_socket, message, strlen(message), 0, (sockaddr*)&client,
                        sizeof(sockaddr_in)) == SOCKET_ERROR)
                    {
                        cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
                    }
                }
            }
            checkPlayerWin(board, window);
            window.display();

        }
    }

private:
    WSADATA wsa{};
    SOCKET server_socket = 0;
    sockaddr_in server{}, client{};
    bool exitRequested = false;
};

int main() {
    system("title UDP Server");

    MoveWindow(GetConsoleWindow(), 650, 50, 500, 500, true);

    UDPServer udpServer;

    udpServer.start();
}

void checkPlayerWin(int board[3][3], sf::RenderWindow& window)
{
    const int WIN_LINE_THICKNESS = 50;
    sf::Vertex line[2] = {
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::White),
        sf::Vertex(sf::Vector2f(0, 0), sf::Color::White)
    };

    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] != 0)
            {
                line[0] = sf::Vertex(sf::Vector2f(WIDTH * (i + 0.5) / 3, 0), sf::Color::Red);
                line[1] = sf::Vertex(sf::Vector2f(WIDTH * (i + 0.5) / 3, HEIGHT), sf::Color::Red);
                hasGameEnded = true;
            }
        }

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] != 0)
            {
                line[0] = sf::Vertex(sf::Vector2f(0, HEIGHT * (i + 0.5) / 3), sf::Color::Red);
                line[1] = sf::Vertex(sf::Vector2f(WIDTH, HEIGHT * (i + 0.5) / 3), sf::Color::Red);
                hasGameEnded = true;
            }
        }
    }

    if (board[1][1] != 0)
    {
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        {
            line[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Red);
            line[1] = sf::Vertex(sf::Vector2f(WIDTH, HEIGHT), sf::Color::Red);
            hasGameEnded = true;
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        {
            line[0] = sf::Vertex(sf::Vector2f(WIDTH, 0), sf::Color::Red);
            line[1] = sf::Vertex(sf::Vector2f(0, HEIGHT), sf::Color::Red);
            hasGameEnded = true;
        }
    }

    if (hasGameEnded)
    {
        window.draw(line, 2, sf::Lines);
        printf("Game has ended\n");
    }
}

void displayerNameInput(sf::RenderWindow& window, std::string& playerName)
{
    sf::Font font;
    font.loadFromFile("Fonts/Arial.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setString("Enter your name: ");
    text.setPosition(10, 10);

    sf::Text name;
    name.setFont(font);
    name.setCharacterSize(24);
    name.setFillColor(sf::Color::White);
    name.setPosition(10, 40);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8 && !playerName.empty())
                    playerName.pop_back();
                else if (event.text.unicode < 128)
                    playerName += static_cast<char>(event.text.unicode);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
                break;
        }

        name.setString(playerName);
        window.clear();
        window.draw(text);
        window.draw(name);
        window.display();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
            break;
    }
}