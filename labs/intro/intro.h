class Intro {
public:
    Intro() {};
    Intro(float initA) { a = initA; };
    float getA() { return a; }
    void setA(float newA) { a = newA; }

private:
    float a;
};

