#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <winsock2.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

#define SERVER "127.0.0.1"  // or "localhost" - ip address of UDP server
#define BUFLEN 512  // max length of answer
#define PORT 8888  // the port on which to listen for incoming data
#define WIDTH 1024
#define HEIGHT 1024

void displayerNameInput(sf::RenderWindow& window, std::string& playerName);
void checkPlayerWin(int board[3][3], sf::RenderWindow& window);

bool hasGameEnded = false;

class UDPClient
{
public:
    UDPClient()
    {
        // initialise winsock
        cout << "Initialising Winsock...\n";
        if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
        {
            cout << "Failed. Error Code: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }
        cout << "Initialised.\n";

        // create socket
        if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
        {
            cout << "socket() failed with error code: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }

        // setup address structure
        memset((char*)&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        server.sin_addr.S_un.S_addr = inet_addr(SERVER);
    }

    ~UDPClient()
    {
        closesocket(client_socket);
        WSACleanup();
    }

    void start()
    {
        sf::ContextSettings settings;
        settings.depthBits = 24;
        sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Enter your name", sf::Style::Default, settings);
        window.setFramerateLimit(20);
        glewExperimental = GL_TRUE;
        glewInit();

        // info shared between client and server
        int board[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
        int localIsX = 0, isX = 0;

        std::string playerName;
        displayerNameInput(window, playerName);

        if (playerName.empty())
        {
            playerName = "Player";
        }

        printf("Hello %s\n", playerName.c_str());

        window.create(sf::VideoMode(WIDTH, HEIGHT), "Tic Tac Toe Client Side", sf::Style::Titlebar | sf::Style::Close, settings);
        window.setFramerateLimit(20);

        u_long mode = 1;
        if (ioctlsocket(client_socket, FIONBIO, &mode) != NO_ERROR)
        {
            cout << "ioctlsocket() failed with error code: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }

        // Send the player's name to make the client known to the server
        sendto(client_socket, playerName.c_str(), playerName.length(), 0, (sockaddr*)&server, sizeof(sockaddr_in));

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
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
            FD_SET(client_socket, &readSet);

            timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 0;

            int selectResult = select(client_socket + 1, &readSet, NULL, NULL, &timeout);
            if (selectResult == SOCKET_ERROR)
            {
                cout << "select() failed with error code: " << WSAGetLastError() << "\n";
                exit(EXIT_FAILURE);
            }
            else if (selectResult > 0)
            {
                if (FD_ISSET(client_socket, &readSet))
                {
                    // Data is available, receive it
                    char answer[BUFLEN] = {};
                    int slen = sizeof(sockaddr_in);
                    int answer_length = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen);
                    if (answer_length == SOCKET_ERROR)
                    {
                        cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
                        exit(EXIT_FAILURE);
                    }

                    // Process received data...
                    cout << "Received: " << answer << "from " << inet_ntoa(server.sin_addr) << ":" << ntohs(server.sin_port) << "\n";
                    if (localIsX == 0)
                    {
                        isX = 1;
	                    localIsX = -1;
                    }
                    board[answer[answer_length - 3] - '0'][answer[answer_length - 1] - '0'] = isX == 1 ? 1 : 2;

                    isX *= -1;
                }
            }
            printf("isX: %d\n", isX);
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
                    isX *= -1;

                    // Send the updated game state to the server
                    sprintf(message, "%s: %d %d", playerName.c_str(), x, y);
                    if (sendto(client_socket, message, strlen(message), 0, (sockaddr*)&server,
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
    WSADATA ws;
    SOCKET client_socket;
    sockaddr_in server;
};

int main()
{
    system("title UDP Client");

    MoveWindow(GetConsoleWindow(), 50, 50, 500, 500, true);

    UDPClient udpClient;
    udpClient.start();
}

void checkPlayerWin(int board[3][3], sf::RenderWindow& window)
{
    const int WIN_LINE_THICKNESS = 10;
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