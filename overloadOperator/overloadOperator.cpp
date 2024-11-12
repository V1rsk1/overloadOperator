#include <iostream>
using namespace std;

class Time {
    int sec;
    int min;
    int hour;

    void normal() {
        while (sec >= 60) {
            sec -= 60;
            min++;
        }
        while (sec < 0) {
            sec += 60;
            min--;
        }

        while (min >= 60) {
            min -= 60;
            hour++;
        }
        while (min < 0) {
            min += 60;
            hour--;
        }

        if (hour >= 24) hour %= 24;
        if (hour < 0) hour = 0;
    }

public:
    Time() : sec{ 0 }, min{ 0 }, hour{ 0 } {}
    Time(int secc, int minn, int hourr) : sec{ secc }, min{ minn }, hour{ hourr } {
        normal();
    }

    // Копирующий конструктор
    Time(const Time& other) : sec{ other.sec }, min{ other.min }, hour{ other.hour } {}

    // Оператор копирующего присваивания
    Time& operator=(const Time& other) {
        if (this != &other) {
            sec = other.sec;
            min = other.min;
            hour = other.hour;
        }
        return *this;
    }

    friend const Time operator++(Time& tiime) {
        ++tiime.sec;
        tiime.normal();
        return tiime;
    }

    friend Time operator-(const Time& tiime1, const Time& tiime2) {
        Time result;
        result.sec = tiime1.sec - tiime2.sec;
        result.min = tiime1.min - tiime2.min;
        result.hour = tiime1.hour - tiime2.hour;
        result.normal();
        return result;
    }

    bool operator==(const Time& tiime) const {
        return (hour == tiime.hour && min == tiime.min && sec == tiime.sec);
    }
    bool operator!=(const Time& tiime) const {
        return !(*this == tiime);
    }
    bool operator>(const Time& tiime) const {
        return (hour > tiime.hour) ||
            (hour == tiime.hour && min > tiime.min) ||
            (hour == tiime.hour && min == tiime.min && sec > tiime.sec);
    }
    bool operator<(const Time& tiime) const {
        return !(*this > tiime || *this == tiime);
    }

    friend ostream& operator<<(ostream& output, const Time& tiime) {
        output << (tiime.hour < 10 ? "0" : "") << tiime.hour << ":"
            << (tiime.min < 10 ? "0" : "") << tiime.min << ":"
            << (tiime.sec < 10 ? "0" : "") << tiime.sec;
        return output;
    }

    friend istream& operator>>(istream& input, Time& tiime) {
        input >> tiime.hour;
        input.ignore(1);
        input >> tiime.min;
        input.ignore(1);
        input >> tiime.sec;
        tiime.normal();
        return input;
    }

    Time& operator+=(int secc) {
        sec += secc;
        normal();
        return *this;
    }

    Time& operator-=(int secc) {
        sec -= secc;
        normal();
        return *this;
    }

    void operator()(int h, int m, int s) {
        hour = h;
        min = m;
        sec = s;
        normal();
    }

    Time(Time&& timee) noexcept : sec{ timee.sec }, min{ timee.min }, hour{ timee.hour } {
        timee.sec = timee.min = timee.hour = 0;
    }

    Time& operator=(Time&& timee) noexcept {
        if (this != &timee) {
            sec = timee.sec;
            min = timee.min;
            hour = timee.hour;
            timee.sec = timee.min = timee.hour = 0;
        }
        return *this;
    }
};

int main() {
    Time t(1, 4, 6);
    ++t;
    cout << t << endl;

    Time t2(0, 3, 7);
    cout << t - t2 << endl;

    bool a = t > t2, b = t < t2, c = t2 == t, d = t != t2;
    (a) ? cout << "t > t2 = true" << endl : cout << "t > t2 = false" << endl;
    (b) ? cout << "t < t2= true" << endl : cout << "t > t2 = false" << endl;
    (c) ? cout << "t == t2 = true" << endl : cout << "t == t2 = false" << endl;
    (d) ? cout << "t != t2 = true" << endl : cout << "t != t2 = false" << endl;

    t -= 2;
    t2 += 7;
    cout << t << " " << t2 << endl;

    return 0;
}
