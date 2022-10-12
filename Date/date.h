#ifndef DATE_H
#define DATE_H



class date{
    private:
        int day;
        int month;
        int year;
        void normalisieren();
    public:
        date(int day, int month, int year);
        void add_day(int day);
        void print() const;

};



#endif