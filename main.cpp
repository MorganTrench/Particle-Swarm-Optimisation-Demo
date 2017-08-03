#include <SFML/Graphics.hpp>
#include <math.h>
#include <algorithm>    // std::max
#include <iostream>

int main() {
    // Initialization
    int width = 800; float xdim = 2.0;
    int height = 600; float ydim = 2.0;
    sf::Image heatmap;
    heatmap.create(800, 600, sf::Color::White);
    float ** fitness = new float*[width];
    for (int i = 0; i < width; i++)
        fitness[i] = new float[height];

    // Calculate Grids 
    for (int i=0; i < width; i+=1){
        for (int j=0; j < height; j+=1){
            // Calculate coordinates
            float x = xdim * float(i-width/2) / float(width);
            float y = ydim * float(j-height/2) / float(height);

            // Calculate Fitness
            fitness[i][j] = x * exp(-(x*x + y*y)) / 0.42888194248;
            // Check Bounds
            float fit = fitness[i][j];
            if (fit > 1) {fit = 1;}
            if (fit < -1) {fit = -1;}

            // Calculate RGB Values
            // https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/HSV-RGB-comparison.svg/600px-HSV-RGB-comparison.svg.png
            // std::cout << fit << "-";
            fit = (fit + 1)/2; // Rescale to colour function domain
            // std::cout << fit << std::endl;
            sf::Color color(0, 255, 0);
            if ((fit > 0) && (fit <= 0.25)) {
                fit = (fit)/0.25;
                color.r = (uint8_t) 0;
                color.g = (uint8_t) fmin(255, fit*255);
                color.b = (uint8_t) 255;
            } else if ((fit > 0.25) && (fit <= 0.5)) {
                fit = 1 - (fit - 0.25)/0.25;
                color.r = (uint8_t) 0;
                color.g = (uint8_t) 255;
                color.b = (uint8_t) fmin(255, fit*255);
            } else if ((fit > 0.5) && (fit <= 0.75)) {
                fit = (fit - 0.5)/0.25;
                color.r = (uint8_t) fmin(255, fit*255);
                color.g = (uint8_t) 255;
                color.b = (uint8_t) 0;
            } else if ((fit > 0.75) && (fit <= 1)) {
                fit = 1 - (fit - 0.75)/0.25;
                color.r = (uint8_t) 255;
                color.g = (uint8_t) fmin(255, fit*255);
                color.b = (uint8_t) 0;
            }
            heatmap.setPixel(i, j, color);
        }
    }
    heatmap.saveToFile("result.png");
    sf::Texture heatTex;
    heatTex.create(width, height);
    heatTex.update(heatmap);
    // define a 120x50 rectangle
    sf::RectangleShape rectangle(sf::Vector2f(0, 0));
    // change the size to 100x100
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setTexture(&heatTex, true);

    // Temp
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RenderWindow window(sf::VideoMode(width, height), "PSO");
    while (window.isOpen())
    {
        // Input Handling
        sf::Event event;
        // Check Exit
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear the previous frame
        window.clear();

        // Update particles

        
        // Draw things....
        window.draw(rectangle);
        window.draw(circle);

        // Draw new frame
        window.display();
    }

    return 0;
}