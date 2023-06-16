#ifndef Cards_h
#define Cards_h

#include "string"
#include "yaml-cpp/yaml.h"

struct Steps {
    int value;
    int size;
    bool haptic_response;
};

struct Pointer {
    int minimum;
    int maximum;
    int default_position;
    Steps steps;
};

struct Icon {
    std::string type;
    std::string color_on;
    std::string color_off;
};

struct Signal {
    std::string move;
    std::string hold;
};

struct Card {
    std::string name;
    Pointer pointer;
    Icon icon;
    Signal signal;
};

typedef std::vector<Card> Items;

void operator>>(const YAML::Node& node, Steps& steps);
void operator>>(const YAML::Node& node, Pointer& pointer);
void operator>>(const YAML::Node& node, Icon& icon);
void operator>>(const YAML::Node& node, Signal& signal);
void operator>>(const YAML::Node& node, Card& card);
void operator>>(const YAML::Node& node, Items& cards);

class Cards {
  public:
    void load_file(const std::string& filename);

    Items items;
};

#endif
