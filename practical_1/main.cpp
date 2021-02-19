#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

//controls
const Keyboard::Key controls[5] =
{
    Keyboard::W,    //player 1 up
    Keyboard::S,    //player 1 down
    Keyboard::Up,   //player 1 up
    Keyboard::Down,  //player 1 down
    Keyboard::P    //player/cpu swap
};
const Vector2f paddleSize(25.0f, 100.0f);
const float ballRadius = 10.0f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.0f;

//ball stuff
Vector2f ballVelocity;
bool server = false;

CircleShape ball;
RectangleShape paddles[2];

//game window
sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pong");

//cpu/player swap
bool cpu = true;

//score
int score1, score2;

//font
Font font;
Text text;

void Load()
{
    //Set size and origin of paddles
    for (auto& p : paddles)
    {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.0f);
    }
    //Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);
    //reset paddle position
    paddles[0].setPosition(15 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
    //reset ball position
    ball.setPosition( -ballRadius+gameWidth/2, -ballRadius+gameHeight / 2);
    //ball velocity
    ballVelocity = { (server ? 100.0f : -100.0f),60.0f };

    //score
    score1 = 0;
    score2 = 0;

    //load font
    font.loadFromFile("res/Champagne & Limousines.ttf");
    //set text
    text.setFont(font);
    text.setColor(Color::White);
    //score text
    text.setString(to_string(score1) + " - " + to_string(score2));
    //set size
    text.setCharacterSize(24);
    //set position
    text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}

void Reset() 
{
    //score text
    text.setString(to_string(score1) + " - " + to_string(score2));
    //center score
    text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
    //switch server
    server = !server;
    //reset paddle position
    paddles[0].setPosition(15 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
    //reset ball position
    ball.setPosition(-ballRadius + gameWidth / 2, -ballRadius + gameHeight / 2);
    //ball velocity
    ballVelocity = { (server ? 100.0f : -100.0f),60.0f };
}

void Update(RenderWindow& window)
{
    //reset clock, recalculate delta time
    static Clock clock;
    float dt = clock.restart().asSeconds();
    //check and consume events
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
            return;
        }
    }

    //Quit Via Esc Key
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        window.close();
    }

    //cpu/player
    if (Keyboard::isKeyPressed(controls[4])) 
    {
        cpu = !cpu;
    }

    //handle puddle movement
    float direction = 0.0f;
    float direction2 = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(0, paddleSpeed * direction  * dt);

    //second paddle
    //player
    if (!cpu) {
        if (Keyboard::isKeyPressed(controls[2])) {
            direction2-=0.5f;
        }
        if (Keyboard::isKeyPressed(controls[3])) {
            direction2+=0.5f;
        }
    }
    else 
    {
        if (ball.getPosition().x > gameWidth/(2*ballVelocity.x) && ballVelocity.x>0) {
            if (ball.getPosition().y > paddles[1].getPosition().y - paddleSize.y / 4) {
                direction2++;
            }
            if (ball.getPosition().y < paddles[1].getPosition().y + paddleSize.y / 4) {
                direction2--;
            }
        }
    }
    paddles[1].move(0, direction2* paddleSpeed* dt);

    //ball movement
    ball.move(ballVelocity * dt);

    //check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    //bottom wall
    if (by > gameHeight)
    {
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, -10);
    }
    //top wall
    else if (by < 0)
    {
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, 10);
    }
    //right wall
    else if (bx > gameWidth) 
    {
        score1++;
        Reset();
    }
    //left wall
    else if (bx < 0) 
    {
        score2++;
        Reset();
    }
    //paddle collision
    else if (bx<paddleSize.x && 
        by>paddles[0].getPosition().y - (paddleSize.y * 0.5f) &&
        by<paddles[0].getPosition().y + (paddleSize.y * 0.5f)) {

        //bounce off left paddle
        ballVelocity.x *= -1.0f;
        ballVelocity.y *= 1.0f;
        ball.move(10,0);
    }
    else if (bx>-paddleSize.x-10+gameWidth &&
        by>paddles[1].getPosition().y - (paddleSize.y * 0.5f) &&
        by < paddles[1].getPosition().y + (paddleSize.y * 0.5f)){

        //bounce off right paddle
        ballVelocity.x *= -1.0f;
        ballVelocity.y *= 1.0f;
        ball.move(-10, 0);
    }
}

void Render()
{
    //Draw everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
    window.draw(text);
}

int main(){
  //enable vertical sync
    window.setVerticalSyncEnabled(true);

    //load
    Load();

    while (window.isOpen()) {
        window.clear();

        Update(window);
        Render();

        window.display();
    }
  return 0;
}