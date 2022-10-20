#ifndef OOPTOOLG_H
#define OOPTOOLG_H

#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

//#include <SFML/Graphics.hpp>
#include"C:\opt\msys\mingw64\include\SFML\Graphics.hpp"
/** @file
 * @brief Graphische Unterstützung für Objektorientierte Programmierung (OOP)
 * und Algorithmen und Datenstrukturen
 * Hilfsroutinen und Hilfsklassen für einfache Graphiken und Animationen
 * Verwendung: Beide Quell-Dateien ooptoolg.(h|cpp) in das Projekt kopieren,
 * als Bibliotheken -lsfml-graphics -lsfml-window -lsfml-system hinzufügen
 * und -pthread einstellen
 */

// TODO: Pimpl für common canvas tasks including render thread

/** Anzeige von Pixelgraphiken und Animationen in einer
 * Zeichenfläche (Canvas) in der Dimension 800x400.
 * Links oben ist (0, 0).
 */
class Canvas {
public:
    Canvas();
    ~Canvas();
    // all public methods can be called anytime and are properly protected
    /** Fügt Kreis mit linker oberer Position (x, y) und angegebenem Radius
     * sowie Farbe hinzu.
     * @param x x-Position der linken oberen Ecke der Bounding Box
     * @param y y-Position der linken oberen Ecke der Bounding Box
     * @param radius Radius
     * @param color Farbe, eine beliebige Farbe vom Typ sf::Color
     * @return handle, um Objekt für Manipulation zu referenzieren
     */
    int add_circle(int x = 0, int y = 0, int radius = 50,
                   sf::Color color = sf::Color::White);
    /** Fügt Kreis mit Mittelpunkt (x, y) und angegebenem Radius
     * sowie Farbe hinzu.
     * @param x Mittelpunkt x-Position
     * @param y Mittelpunkt y-Position
     * @param radius Radius
     * @param color Farbe, eine beliebige Farbe vom Typ sf::Color
     * @return handle, um Objekt für Manipulation zu referenzieren
     */
    int add_circle_center(int x = 50, int y = 50, int radius = 50,
                          sf::Color color = sf::Color::White) {
        return add_circle(x - radius, y - radius, radius, color);
    }
    /** Fügt Linie hinzu ab Position (x, y) bis Position (tox, toy)
     * sowie Farbe hinzu.
     * @param x Anfang x-Position
     * @param y Anfang y-Position
     * @param tox Ende x-Position
     * @param toy Ende y-Position
     * @param color Farbe, eine beliebige Farbe vom Typ sf::Color
     * @param width Breite der Linie
     * @return handle, um Objekt für Manipulation zu referenzieren
     */
    int add_line(int x = 0, int y = 0, int tox = 100, int toy = 100,
                 sf::Color color = sf::Color::White, int width = 3);
    /** Fügt Rechteck mit linker oberer Position (x, y) und
     * Breite width und Höhe height sowie Farbe hinzu.
     * @param x x-Position
     * @param y y-Position
     * @param width Breite des Rechtecks
     * @param height Höhe des Rechtecks
     * @param color Farbe, eine beliebige Farbe vom Typ sf::Color
     * @return handle, um Objekt für Manipulation zu referenzieren
     */
    int add_rectangle(int x = 0, int y = 0, int width = 100, int height = 50,
                      sf::Color color = sf::Color::White);
    /** Fügt Text mit linker oberer Position (x, y) der Bounding Box
     * und angegebenem Text hinzu, die Höhe eines Zeichens
     * ist px die Füllfarbe wie angegeben.
     * @param x x-Position
     * @param y y-Position
     * @param text Nullterminierter String, der geschrieben wird
     * @param px Fontgröße in Pixel (nicht pt)
     * @param color Farbe, eine beliebige Farbe vom Typ sf::Color
     * @return handle, um Objekt für Manipulation zu referenzieren
     */
    int add_text(int x = 0, int y = 0, const char* text = "X",
                 int px = 18, /* font size in pixel, not pt */
                 sf::Color color = sf::Color::White);
    /** Fügt Text mit linker oberer Position (x, y) der Bounding Box
     * und angegebenem Text hinzu, die Höhe eines Zeichens
     * ist px die Füllfarbe wie angegeben.
     * @param x x-Position
     * @param y y-Position
     * @param text C++-String, der geschrieben wird
     * @param px Fontgröße in Pixel (nicht pt)
     * @param color Farbe, eine beliebige Farbe vom Typ sf::Color
     * @return handle, um Objekt für Manipulation zu referenzieren
     */
    int add_text(int x = 0, int y = 0, const std::string& text = "X",
                 int px = 18, /* font size in pixel, not pt */
                 sf::Color color = sf::Color::White) {
        return add_text(x, y, text.c_str(), px, color);
    }
    /** Ändert Text des Texts
     * @param id das Handle des Text-Objekts
     * @param text Nullterminierter String, der eingesetzt werden soll
     * @return true, gdw es existiert ein Text-Objekt mit id
     */
    bool change_text(int id, const char* text);
    /** Ändert Text des Texts
     * @param id das Handle des Text-Objekts
     * @param text C++-String, der eingesetzt werden soll
     * @return true, gdw es existiert ein Text-Objekt mit id
     */
    bool change_text(int id, const std::string& text) {
        return change_text(id, text.c_str());
    }
    // int add_polyline?
    /** setzt Objekt mit id auf Position x, y
     * @param id das Handle des Objekts
     * @param x x-Position
     * @param y y-Position
     * @return true gdw es existiert ein Objekt mit id
     */
    bool move_to(int id, int x, int y);
    /** verschiebt Objekt mit id um dx, dy
     * @param id das Handle des Objekts
     * @param dx delta der x-Position
     * @param dy delta der y-Position
     * @return true gdw es existiert ein Objekt mit id
     */
    bool move_by(int id, int dx, int dy);
    /** liest x-Position von Objekt mit id
     * @param id das Handle des Objekts
     * @return x-Position, wenn ein Objekt mit id existiert, sonst -1
     */
    int get_posx(int id);
    /** liest x-Position von Objekt mit id
     * @param id das Handle des Objekts
     * @return x-Position, wenn ein Objekt mit id existiert, sonst -1
     */
    int get_posy(int id);
    /** Test, ob man noch zeichnet
     * @return true gdw man noch zeichnet
     */
    bool is_alive() const {
        return should_render;
    }
    /** Löscht alle Objekte auf der Zeichenfläche
     */
    void clear();
    /** Beendet die Zeichnung, Canvas kann nicht länger bedient werden,
     * das Programm kann beendet werden
     * @param ms schlafe vorher maximal ms Millisekunden
     */
    void quit(int ms = 0);

private:
    void main_loop(); // blocking, used in a thread started in constructor
    void handle_events();
    void render();
    // render size 800x400 that is ok even for ancient screens (800x600), but
    // supports aspect ratio 2:1, which is ok for modern laptops (16:9) and
    // hires users who can maximize the tiny window.
    // Available bitmap views are 800x400, 400x200 and 200x100.
    const int DEFAULT_WIDTH = 800;
    const int DEFAULT_HEIGHT = 400;
    const std::string DEFAULT_TITLE = "OOPToolG";
    sf::RenderWindow* window;
    sf::Font ascii_font; // simple free bitmap font
    std::map<int, std::shared_ptr<sf::Shape>> shapes;
    int nextfree_shape = 1; // -> 2, 3,   ...; may wrap
    std::map<int, sf::Text> texts;
    int nextfree_text = -1; // -> -2, -3, ...; may wrap
    std::atomic<bool> should_render;
    std::thread render_thread;
    // guards everything used in render
    // needed! We allow asynchronuous calls from C++ program (not just events)
    std::mutex render_lock;
};

/** Anzeige von Pixelgraphiken und Animationen in einer
 * Zeichenfläche mit unterschiedlichen Dimension Breite <= 600.
 * Aspect Ratio ist immer 3:2, Höhe wird berechnet.
 * Die Default-Anzeigefläge ist immer 800x400, davon sind 200 rechts
 * reserviert für Text. Jede Breite wird auf 600x400 skaliert.
 * Es sollten als Breiten nur 600, 300, 150, 120, 75, 60 oder 30
 * genommen werden, woraus sich die folgenden Auflösungen ergeben:
 *    600x400, 300x200, 150x100, 120x80, 75x50, 60x40, 30x20
 * Links oben ist (0, 0).
 */
class Pixels { // ToDo maybe; extract common to Canvas
public:
    Pixels(int w = 600);
    ~Pixels();
    int width() const {
        return _width;
    }
    int height() const {
        return _height;
    }
    bool set(int x, int y, sf::Color color = sf::Color::White);
    bool clear(int x, int y) {
        return set(x, y, sf::Color::Black);
    }
    /** Fügt Text mit linker oberer Position (x, y) der rechten
     * Box ab width*3/4 bis Ende (range also width/4, height)
     * und angegebenem Text hinzu, die Höhe eines Zeichens
     * ist px, die Füllfarbe wie angegeben.
     * @param x x-Position zwischen 0 und width/4
     * @param y y-Position
     * @param text Nullterminierter String, der angezeigt wird
     * @param px Fontgröße in Pixel (nicht pt)
     * @param color Farbe, eine beliebige Farbe vom Typ sf::Color
     * @return handle, um Objekt für Manipulation zu referenzieren
     */
    int add_text(int x = 0, int y = 0, const char* text = "X",
                 int px = 18, /* font size in pixel, not pt*/
                 sf::Color color = sf::Color::White);
    /** Fügt Text mit linker oberer Position (x, y) der rechten
     * Box ab width*3/4 bis Ende (range also width/4, height)
     * und angegebenem Text hinzu, die Höhe eines Zeichens
     * ist px, die Füllfarbe wie angegeben.
     * @param x x-Position zwischen 0 und width/4
     * @param y y-Position
     * @param text C++String, der angezeigt wird
     * @param px Fontgröße in Pixel (nicht pt)
     * @param color Farbe, eine beliebige Farbe vom Typ sf::Color
     * @return handle, um Objekt für Manipulation zu referenzieren
     */
    int add_text(int x = 0, int y = 0, const std::string& text = "X",
                 int px = 18, /* font size in pixel, not pt*/
                 sf::Color color = sf::Color::White) {
        return add_text(x, y, text.c_str(), px, color);
    }
    /** Ändert Text des Texts
     * @param id das Handle des Text-Objekts
     * @param text Nullterminierter String, der angezeigt wird
     * @return true, gdw es existiert ein Text-Objekt mit id
     */
    bool change_text(int id, const char* text);
    /** Ändert Text des Texts
     * @param id das Handle des Text-Objekts
     * @param text C++-String, der angezeigt wird
     * @return true, gdw es existiert ein Text-Objekt mit id
     */
    bool change_text(int id, const std::string& text) {
        return change_text(id, text.c_str());
    }
    /** Test, ob man noch zeichnet
     * @return true gdw man noch zeichnet
     */
    bool is_alive() const {
        return should_render;
    }
    /** Löscht alle Pixel auf der Zeichenfläche (aber nicht die Texte)
     */
    void clear();
    /** Löscht alle Pixel auf der Pixelfläche und die Texte
     */
    void clear_all();
    /** Beendet die Zeichnung, Canvas kann nicht länger bedient werden,
     * das Programm kann beendet werden
     * @param ms schlafe vorher maximal ms Millisekunden
     */
    void quit(int ms = 0);

private:
    void main_loop(); // blocking, used in a thread started in constructor
    void handle_events();
    void render();
    const int DEFAULT_WIDTH = 800;
    const int DEFAULT_HEIGHT = 400;
    const std::string DEFAULT_TITLE = "OOPToolP";
    sf::RenderWindow* window;
    sf::Font ascii_font;
    int _width, _height, _factor;
    sf::Image bitmap;
    sf::Texture texture;
    sf::Sprite sprite;
    std::map<int, sf::Text> texts;
    int nextfree_text = -1; // -> -2, -3, ...; may wrap
    std::atomic<bool> should_render;
    std::thread render_thread;
    // guards everything used in render
    // needed! We allow asynchronuous calls from C++ program (not just events)
    std::mutex render_lock;
    void setScaledPixel(int x, int y, sf::Color color);
};

// vordefinierte einfache Farben, jede sf::Color ist ok
extern const sf::Color Schwarz;
extern const sf::Color Weiss;
extern const sf::Color Rot;
extern const sf::Color Gruen;
extern const sf::Color Blau;
extern const sf::Color Gelb;
extern const sf::Color Magenta;
extern const sf::Color Cyan;

#endif
