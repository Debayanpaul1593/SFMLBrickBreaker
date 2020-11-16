#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
//macros
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 640
#define LATERAL_PADDING 50
#define Y_GAP 10.f
#define X_GAP 10.f
#define BAT_WIDTH 100
#define BAT_HEIGHT 15
#define LS_X 0
#define LS_Y 1

//global vars
int bat_position = (SCREEN_WIDTH / 2) - (BAT_WIDTH / 2);
sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "BRICK BREAKER");
sf::RectangleShape __bat;
sf::CircleShape __ball;
sf::Sound sound;
std::vector<sf::RectangleShape> __v;
float x_dir = -0.5;
float y_dir = -1;
sf::Text __text;
float dt = 0.5;
bool gameOver = false;
int noOfBricks;
bool gameStarted = false;
sf::Sprite brickSprite;
sf::Texture brickTexture;
sf::Texture ballTexture;
sf::SoundBuffer __buffer;
sf::Texture batTexture;
sf::Sound __sound;
std::string message = "";
bool initialised = false;
int lastSwitch = LS_Y;

//method declarations
void setTiles();
sf::RectangleShape getBat();
sf::CircleShape getBall();
void drawAll(sf::RectangleShape bat);
sf::Text getText();
void drawTiles();
void setText();
void initGame();

float getBrickWidth()
{
    int boundary = 2 * LATERAL_PADDING;
    int total_gap = 9 * X_GAP;
    float brick_width = (SCREEN_WIDTH - boundary - total_gap) / 10;
    return brick_width;
}

void render(sf::RectangleShape bat)
{
    window.clear();
    drawAll(bat);
    window.display();
}

void playSound()
{
    if (gameStarted)
    {
        __sound.play();
    }
}

int drawBall()
{
    sf::Vector2f ballPos = __ball.getPosition();
    sf::Vector2f batPos = __bat.getPosition();
    if (ballPos.x <= 0 + 5 || ballPos.x >= 1024 - 10)
    {
        x_dir = x_dir * -1;
        lastSwitch = LS_X;
        playSound();
    }

    if (ballPos.y <= 0 + 5)
    {
        y_dir = y_dir * -1;
        lastSwitch = LS_Y;
        playSound();
    }

    if (ballPos.y >= 640 - 10)
    {
        message = "Game Over! Press space to continue!";
        initialised = false;
        gameOver = true;
    }

    if (ballPos.y >= batPos.y - 20 && ballPos.x >= batPos.x && ballPos.x <= batPos.x + 100)
    {
        y_dir = y_dir * -1;
        lastSwitch = LS_Y;
        playSound();
    }

    for (std::size_t i = 0; i < __v.size(); i++)
    {
        sf::Vector2f brPos = __v.at(i).getPosition();

        if (ballPos.x > brPos.x && ballPos.x < brPos.x + 70)
        {
            float cond1 = std::abs(brPos.y - ballPos.y);
            float cond2 = std::abs(ballPos.y - (brPos.y + 30));
            if ((cond1<=1 && cond1>=0) || (cond2<=1 && cond2>=0))
            {
                y_dir = y_dir * -1;
                __v.erase(__v.begin() + i);
                noOfBricks = noOfBricks - 1;
                playSound();
                break;
            }
        }else if (ballPos.y > brPos.y && ballPos.y < brPos.y + 30)
        {
            float cond1 = std::abs(brPos.x - ballPos.x);
            float cond2 = std::abs(ballPos.x - (brPos.x + 70));
            if ((cond1<=5.25 && cond1>=0.25) || cond2<=5.25 && cond2>=0.25)
            {
                x_dir = x_dir * -1;
                __v.erase(__v.begin() + i);
                noOfBricks = noOfBricks - 1;
                playSound();
                break;
            }
        }
    }

    if (gameStarted)
    {
        __ball.move(sf::Vector2f(dt * x_dir, dt * y_dir));
    }
    window.draw(__ball);

    if (noOfBricks == 0)
    {
        message = "Congratulations! Level Completed!";
        gameOver = true;
    }

    if (gameOver)
    {
        setText();
        initGame();
    }
    return 0;
}

void drawAll(sf::RectangleShape bat)
{
    drawTiles();
    window.draw(bat);
    drawBall();
}

void drawTiles()
{

    for (std::size_t i = 0; i < __v.size(); ++i)
    {
        sf::RectangleShape brick = __v[i];
        brick.setTexture(&brickTexture);
        window.draw(brick);
    }
}

void setText()
{

    sf::Font font;
    if (!font.loadFromFile("src/res/fonts/SourceCodePro-Bold.ttf"))
    {
        std::cout << "Could not load font!" << std::endl;
        return;
    }

    __text.setFont(font);
    // set the string to display
    __text.setString(message);

    // set the character size
    __text.setCharacterSize(24); // in pixels, not points!
    __text.setPosition(350, 250);
    // set the color
    __text.setFillColor(sf::Color::Red);
    __text.setStyle(sf::Text::Bold);
    window.draw(__text);
}

sf::CircleShape getBall()
{
    sf::CircleShape ball(10.f);
    //ball.setFillColor(sf::Color::Yellow);
    ball.setPosition(bat_position + 140, SCREEN_HEIGHT - 25 - BAT_HEIGHT);
    ball.setTexture(&ballTexture);
    return ball;
}

sf::RectangleShape getBat()
{
    sf::RectangleShape bat;
    bat.setSize(sf::Vector2f(BAT_WIDTH, BAT_HEIGHT));
    //bat.setOutlineColor(sf::Color::Red);
    //bat.setFillColor(sf::Color::Blue);
    bat.setPosition(bat_position, SCREEN_HEIGHT - 20);
    bat.setTexture(&batTexture);
    //bat.setOutlineThickness(1.f);
    bat.move(sf::Vector2f(100.f, 0));
    return bat;
}

void setTiles()
{
    if (!brickTexture.loadFromFile("src/res/imgs/tile_modern.jpg"))
    {
        std::cout << "Could not load texture!" << std::endl;
        system("pause");
    }
    std::vector<sf::RectangleShape> v;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            sf::RectangleShape rect;
            float bw = getBrickWidth();
            rect.setSize(sf::Vector2f(70, 30));
            rect.setPosition((i * (bw + 2 * X_GAP)) + LATERAL_PADDING, (j * (30 + 2 * Y_GAP)) + Y_GAP);
            v.push_back(rect);
        }
    }
    __v = v;
    noOfBricks = __v.size();
}

void handlePress(sf::Keyboard::Key key, bool isPressed)
{
    sf::Vector2f batPos = __bat.getPosition();
    switch (key)
    {
    case sf::Keyboard::Left:
        if (isPressed)
        {

            if (batPos.x > 2)
            {
                __bat.move(sf::Vector2f(-20, 0));
            }

            if (!gameStarted && __ball.getPosition().x >= 50)
            {
                __ball.move(sf::Vector2f(-20, 0));
            }
        }
        break;
    case sf::Keyboard::Right:
        if (isPressed)
        {
            if (batPos.x < 922)
            {
                __bat.move(sf::Vector2f(+20, 0));
            }

            if (!gameStarted && __ball.getPosition().x < 957)
            {
                __ball.move(sf::Vector2f(+20, 0));
            }
        }
        break;
    case sf::Keyboard::Space:
        if (isPressed && !gameStarted)
        {
            gameStarted = true;
            gameOver = false;
        }

        /*if(gameOver){
            __ball = getBall();
            gameOver = false;
            gameStarted = false;
        }*/
        break;
    default:
        break;
    }
}

void processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            handlePress(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            handlePress(event.key.code, false);
            break;
        }
    }
}

int loadResources()
{
    //load texture for ball
    if (!ballTexture.loadFromFile("src/res/imgs/ball_texture.jpeg"))
    {
        std::cout << "Could not load ball texture!" << std::endl;
        return 1;
    }

    //load texture for bat
    if (!batTexture.loadFromFile("src/res/imgs/wood_plywood.jpg"))
    {
        std::cout << "Could not load bat texture" << std::endl;
        return 1;
    }

    //load sound effect
    if (!__buffer.loadFromFile("src/res/sounds/ping_pong.wav"))
    {
        std::cout << "Could not load Sound File" << std::endl;
        return 1;
    }

    __sound.setBuffer(__buffer);
    return 0;
}

void initGame()
{
    if (!initialised)
    {
        gameStarted = false;
        setTiles();
        __bat = getBat();
        __ball = getBall();
        initialised = true;
    }
}

int main()
{
    loadResources();
    initGame();
    //sf::Vector2i winPos = window.getPosition();
    while (window.isOpen())
    {
        processEvents();
        render(__bat);
    }

    return 0;
}