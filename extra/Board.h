#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "ooptoolg.h"

/** Repraesentiert ein nxn Schachbrett und erlaubt die Felder
 * farbig zu markieren.
 * row(Zeile)=0, column(Spalte)=0 ist die linke untere Ecke.
 */
class Board {
public:
    Board(int n = 8);
    Board(const Board&) = delete;            // keine Kopien
    Board& operator=(const Board&) = delete; // keine Zuweisung
    ~Board();

    /** Setzt die Groesse n des nxn Schachbretts.
     * Vergisst alle Faerbungen.
     * Man sollte es besser gleich richtig initialisieren
     * mit den passenden Konstruktor.
     * @param n Seitenlaenge des Schachbretts.
     */
    void setSize(int n);

    /** Setzt ein Feld auf die angegebene Farbe.
     * @param row Zeile
     * @param column Spalte
     * @param color Farbe von der SFML-Bibliothek,
     *        Typ sf::Color, Vorgabe weiss
     */
    void setSquare(int row, int column, sf::Color color=sf::Color::White);

    /** Setzt ein Feld auf die Farbe weiss oder schwarz zurueck,
     * je nachdem wo es im Schachbrettmuster ist.
     * Links unten ist schwarz.
     * @param row Zeile
     * @param column Spalte
     */
    void resetSquare(int row, int column);

    /** Setzt das Schachbrett vollstaendig auf schwarz/weiss zurueck,
     * vergisst also alle farbigen Markierungen.
     */
    void reset();

    /** Setzt den Text rechts in der Visualisierung.
     */
    void log(const std::string&);

    /** Zeichnet den aktuellen Zustand auf den Bildschirm.
     */
    void render();

private:
    int n;
    int square_size;
    sf::Color* board;
    Pixels* pixels;
    int logid = -1;
};

#endif
