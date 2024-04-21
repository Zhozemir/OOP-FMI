#include <iostream>
class ExcludedPoints {

private:

    void copyFrom(const ExcludedPoints&);
    void free();
    void resize(unsigned);

    int16_t* excludedPoints;
    uint16_t capacity;
    uint16_t size;

public:

    ExcludedPoints();
    ExcludedPoints(const ExcludedPoints&);
    ExcludedPoints& operator=(const ExcludedPoints&);
    ~ExcludedPoints();

    bool isExcluded(int16_t) const;
    unsigned getSize() const;
    void excludePoint(int16_t);

    void serialize(std::ofstream& ofs) const;
    void deserialize(std::ifstream& ifs);

};