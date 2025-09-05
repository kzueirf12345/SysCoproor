#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include "Plot/Plot.hpp"
#include "Common/ErrorHandle.hpp"

int main()
{
    constexpr unsigned int WINDOW_WIDTH         = 2000;
    constexpr unsigned int WINDOW_HEIGHT        = 1000;

    constexpr unsigned int BIG_PLOT_SIZE        = 500;
    constexpr unsigned int SMALL_PLOT_SIZE      = 250;

    constexpr unsigned int BIG_PLOT_MARGIN      = (WINDOW_HEIGHT - BIG_PLOT_SIZE) / 2;
    constexpr unsigned int SMALL_PLOT_MARGIN    = (WINDOW_HEIGHT - SMALL_PLOT_SIZE) / 2;

    const sf::Color PlotBGColor  (249, 248, 247);
    const sf::Color PlotPlotColor(149, 148, 147);
    const sf::Color PlotGridColor( 49,  48,  47);

    constexpr unsigned int ScaleX = 10;
    constexpr unsigned int ScaleY = 10;
    const sf::Vector2f OriginOffset(ScaleX >> 1, ScaleY >> 1);

    sf::RenderWindow Window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        // sf::VideoMode(),
        "System Coproordinations (SysCopro)"
        // sf::Style::Default
    );

    SysCopro::Plot BigPlot(
        sf::Vector2f(BIG_PLOT_MARGIN, BIG_PLOT_MARGIN), 
        sf::Vector2f(BIG_PLOT_MARGIN + BIG_PLOT_SIZE, BIG_PLOT_MARGIN + BIG_PLOT_SIZE), 
        PlotBGColor, 
        PlotGridColor,
        PlotPlotColor,
        ScaleX,
        ScaleY,
        OriginOffset,
        std::tan
    );

    SysCopro::Plot SmallPlot(
        sf::Vector2f(WINDOW_WIDTH - SMALL_PLOT_MARGIN - SMALL_PLOT_SIZE, SMALL_PLOT_MARGIN), 
        sf::Vector2f(WINDOW_WIDTH - SMALL_PLOT_MARGIN, SMALL_PLOT_MARGIN + SMALL_PLOT_SIZE), 
        PlotBGColor, 
        PlotGridColor,
        PlotPlotColor,
        ScaleX,
        ScaleY,
        OriginOffset,
        std::tan
    );

    while (Window.isOpen())
    {
        sf::Event Event;
        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                Window.close();
        }

        Window.clear();

        ERROR_HANDLE(BigPlot.Print(Window));
        ERROR_HANDLE(SmallPlot.Print(Window));

        Window.display();
    }

    return 0;
}