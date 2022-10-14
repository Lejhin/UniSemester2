#include <iostream>
#include <vector>

#include "GraphicObject.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "ooptool.h"
#include "ooptoolg.h"
using namespace std;

Pixels pxs(600); // hierauf zeichnen wir

void show(GraphicObject* go, const sf::Color& color) {
    for (int y=0; y < pxs.height(); y+=1) {
        for (int x=0; x < pxs.width(); x+=1) {
            if (go->is_in(x, y)) {
                pxs.set(x, y, color);
            }
        }
    }
}

void hide(GraphicObject* go) {
    for (int y=0; y < pxs.height(); y+=1) {
        for (int x=0; x < pxs.width(); x+=1) {
            if (go->is_in(x, y)) {
                pxs.set(x, y, Schwarz);
            }
        }
    }
}

vector<const sf::Color*> colors = { // colors do not copy ??
    &Rot, &Gruen, &Blau, &Gelb, &Magenta, &Cyan
};
int coloridx = 0;
const sf::Color* next() {
    const sf::Color *ret = colors[coloridx];
    coloridx = (coloridx + 1) % colors.size();
    return ret;
}

int main() {
    pxs.add_text(0, 0, "draw", 22);
    pxs.add_text(0, 20, " GraphicObject's", 20);
    Square square_a(10 , 10 , 100);
    Square square_b(60 , 60 , 50 );
    Square square_c(10 , 120, 100);
    Circle circle_a(175, 60 , 50 );
    Circle circle_b(175, 60 , 25 );
    Circle circle_c(175, 170, 50 );
    Rectangle rect_a(250, 10, 180, 100);
    Rectangle rect_b(280, 40, 120,  70);
    Rectangle rect_c(310, 70,  60,  40);
    Rectangle rect_d(250, 120, 180, 100);
    Rectangle rect_e(280, 120, 120,  70);
    Rectangle rect_f(310, 120,  60,  40);

    pxs.add_text(0, 40, " squares", 20);
    show(&square_a, *next());
    show(&square_b, *next());
    show(&square_c, *next());
    schlafe_ms(1000);
    pxs.add_text(0, 60, " circles", 20);
    show(&circle_a, *next());
    show(&circle_b, *next());
    show(&circle_c, *next());
    schlafe_ms(1000);
    pxs.add_text(0, 80, " rectangles");
    show(&rect_a, *next());
    show(&rect_b, *next());
    show(&rect_c, *next());
    show(&rect_d, *next());
    show(&rect_e, *next());
    show(&rect_f, *next());
    schlafe_ms(3000);
    pxs.add_text(0, 100, "hole", 20);
    pxs.add_text(0, 120, " square");
    hide(&square_b);
    schlafe_ms(1000);
    pxs.add_text(0, 140, " circle");
    hide(&circle_a);
    schlafe_ms(1000);
    pxs.add_text(0, 160, " rectangle");
    hide(&rect_c);
    pxs.add_text(0, 180, "done", 20);
    schlafe_ms(6000);
    pxs.quit();
}
