#ifndef STUDI_H
#define STUDI_H
// Die Header-Datei darf nicht geändert werden

#include <string>

// Eine Studi-Klasse, die einen Studierenden repräsentiert
class Studi {
public:
    Studi();
    Studi(long matnr, std::string vorname, std::string nachname);
    Studi(const Studi &);
    ~Studi();
    long matnr() const;
    std::string vorname() const;
    std::string nachname() const;
    // Akzeptiert nur 7-stellige Matrikelnummern ohne führende Nullen,
    // false wenn nicht akzeptiert (alter Wert bleibt), true sonst
    bool set_matnr(long matnr);
    // Das übergebene Bild wird als Bytearray kopiert in einen eigenen
    // Speicherbereich, vorhandener Speicher wird gelöscht
    void set_image(char *image, int size);

    // get_* ist nur zur Verwendung im Test, nicht ändern
    char *get_image() const { return _image; } 
    int get_image_size() const { return _image_size; }
private:
    long _matnr;
    std::string _vorname;
    std::string _nachname;
    char *_image;
    int _image_size;
};

#endif /* STUDI_H */
