#include <SFML/Config.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include "Shapes/Sphere.hpp"
#include "Plot/Plot.hpp"
#include "Common/ErrorHandle.hpp"
#include "Vector/Vector.hpp"

int main()
{
    constexpr unsigned int WINDOW_WIDTH         = 2048;
    constexpr unsigned int WINDOW_HEIGHT        = 1024;

    constexpr unsigned int BIG_PLOT_SIZE        = 500;
    constexpr unsigned int SMALL_PLOT_SIZE      = 250;

    constexpr unsigned int BIG_PLOT_MARGIN      = (WINDOW_HEIGHT -   BIG_PLOT_SIZE) / 2;
    constexpr unsigned int SMALL_PLOT_MARGIN    = (WINDOW_HEIGHT - SMALL_PLOT_SIZE) / 2;

    const sf::Color PlotBGColor  (249, 248, 247);
    const sf::Color PlotPlotColor(149, 148, 147);
    const sf::Color PlotGridColor( 49,  48,  47);

    constexpr unsigned int ScaleX = 100;
    constexpr unsigned int ScaleY = 100;
    const sf::Vector2f OriginOffset(ScaleX >> 1, ScaleY >> 1);

    sf::RenderWindow Window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        // sf::VideoMode(),
        "System Coproordinations (SysCopro)"
    );

    SysCopro::Plot BigPlot(
        sf::Vector2f(BIG_PLOT_MARGIN, BIG_PLOT_MARGIN), 
        sf::Vector2f(BIG_PLOT_MARGIN + BIG_PLOT_SIZE, BIG_PLOT_MARGIN + BIG_PLOT_SIZE), 
        PlotBGColor, 
        PlotGridColor,
        ScaleX,
        ScaleY,
        OriginOffset
    );

    SysCopro::Plot SmallPlot(
        sf::Vector2f(WINDOW_WIDTH - SMALL_PLOT_MARGIN - SMALL_PLOT_SIZE, SMALL_PLOT_MARGIN), 
        sf::Vector2f(WINDOW_WIDTH - SMALL_PLOT_MARGIN, SMALL_PLOT_MARGIN + SMALL_PLOT_SIZE), 
        PlotBGColor, 
        PlotGridColor,
        ScaleX,
        ScaleY,
        OriginOffset
    );

    
    SysCopro::Vector3f Light1(10 * 20, 10 * 20, 10 * 20);
    SysCopro::Vector3f Light2(10 * 20, 10 * 20, 10 * 20);
    SysCopro::Vector3f Viewer1(0, 0, 100);
    SysCopro::Vector3f Viewer2(0, 0, 100); 

    SysCopro::Vector2f Vector1(20, 0);
    SysCopro::Vector2f Vector2(20, 0);
    
    //ПОПКА (БУМ БУМ БУМ?) - 
    //roflanEbalo - 
    //ПЕДИК, ЧТО ЗА ХУЙНЮ ТЫ НАПИСАЛ? - 
    //Я ХОЧУ В БАЙКААААААЛ - 
    //Я НЕ ЗНАЮ, Я НЕ ЗНАЮ, Я НЕ ЗНАЮ, ПОЧЕМУ НЕОЧЕВИДНО???
    
    constexpr float ROTATE_ANGLE_COEF = 0.5;

    sf::Clock Clock;

    Window.setFramerateLimit(20);

    while (Window.isOpen())
    {
        sf::Event Event;
        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed) {
                Window.close();
            }
            if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Left) {
                    BigPlot.MoveLeft();
                }
                if (Event.key.code == sf::Keyboard::Right) {
                    BigPlot.MoveRight();
                }
                if (Event.key.code == sf::Keyboard::Up) {
                    BigPlot.MoveUp();
                }
                if (Event.key.code == sf::Keyboard::Down) {
                    BigPlot.MoveDown();
                }
            }
        }

        Window.clear();

        ERROR_HANDLE(BigPlot.   PrintSysCopro      (Window));
        ERROR_HANDLE(SmallPlot. PrintSysCopro      (Window));
        // ERROR_HANDLE(BigPlot.   PrintPlot       (Window, std::tan, PlotPlotColor));
        // ERROR_HANDLE(SmallPlot. PrintPlot       (Window, std::tan, PlotPlotColor));
        // ERROR_HANDLE(BigPlot.   PrintPlot       (Window, std::sin, PlotPlotColor));
        // ERROR_HANDLE(SmallPlot. PrintPlot       (Window, std::sin, PlotPlotColor));
        
        ERROR_HANDLE(BigPlot.  PrintSphere(Window, SysCopro::Sphere(20), Light1, Viewer1));
        ERROR_HANDLE(SmallPlot.PrintSphere(Window, SysCopro::Sphere(20), Light2, Viewer2));

        float RotateAngle = ROTATE_ANGLE_COEF * Clock.getElapsedTime().asSeconds();
        ERROR_HANDLE(SysCopro::TransformVector(Light1, SysCopro::Transform::ROTATE_CLKWISE,  SysCopro::Axis::Z, RotateAngle));
        ERROR_HANDLE(SysCopro::TransformVector(Light2, SysCopro::Transform::ROTATE_CCLKWISE, SysCopro::Axis::Z, RotateAngle));
        
        
        ERROR_HANDLE(BigPlot.  PrintVector(Window, SysCopro::Vector2f(Light1.x, Light1.y), PlotPlotColor));
        ERROR_HANDLE(SmallPlot.PrintVector(Window, SysCopro::Vector2f(Light1.x, Light1.y), PlotPlotColor));
        
        // RotateAngle = ROTATE_ANGLE_COEF * Clock.getElapsedTime().asSeconds();

        // ERROR_HANDLE(SysCopro::TransformVector(Vector1, SysCopro::Transform::ROTATE_CLKWISE,  RotateAngle));
        // ERROR_HANDLE(SysCopro::TransformVector(Vector2, SysCopro::Transform::ROTATE_CCLKWISE, RotateAngle));


        Window.display();

        Clock.restart();
    }

    return 0;
}