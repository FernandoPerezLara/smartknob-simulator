#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

struct Steps {
    int value;
    int size;
    bool haptic_response;
};

struct Cursor {
    int minimum;
    int maximum;
    int default_position;
    Steps steps;
};

struct Icon {
    std::string type;
    std::string on_color;
    std::string off_color;
};

struct Signal {
    std::string move;
    std::string press;
};

struct Card {
    Cursor cursor;
    std::string name;
    Icon icon;
    Signal signal;
};

void operator>>(const YAML::Node& node, Steps& steps) {
  steps.value = node["value"].as<int>();
  steps.size = node["size"].as<int>();
  steps.haptic_response = node["haptic_response"].as<bool>();
}

void operator>>(const YAML::Node& node, Cursor& cursor) {
  cursor.minimum = node["minimum"].as<int>();
  cursor.maximum = node["maximum"].as<int>();
  cursor.default_position = node["default_position"].as<int>();
  node["steps"] >> cursor.steps;
}

void operator>>(const YAML::Node& node, Icon& icon) {
  icon.type = node["type"].as<std::string>();
  icon.on_color = node["on_color"].as<std::string>();
  icon.off_color = node["off_color"].as<std::string>();
}

void operator>>(const YAML::Node& node, Signal& signal) {
  signal.move = node["move"].as<std::string>();
  signal.press = node["press"].as<std::string>();
}

void operator>>(const YAML::Node& node, Card& card) {
  node["cursor"] >> card.cursor;
  card.name = node["name"].as<std::string>();
  node["icon"] >> card.icon;
  node["signal"] >> card.signal;
}

int main() {
  std::ifstream fin("./config.yaml");
  YAML::Node doc = YAML::Load(fin);

  Card card;
  doc["card"] >> card;

  std::cout << "Icon Type: " << card.icon.type << std::endl;

  return 0;
}
