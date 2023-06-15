#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

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
    std::string on_color;
    std::string off_color;
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

void operator>>(const YAML::Node& node, Steps& steps) {
  steps.value = node["value"].as<int>();
  steps.size = node["size"].as<int>();
  steps.haptic_response = node["haptic_response"].as<bool>();
}

void operator>>(const YAML::Node& node, Pointer& pointer) {
  pointer.minimum = node["minimum"].as<int>();
  pointer.maximum = node["maximum"].as<int>();
  pointer.default_position = node["default_position"].as<int>();
  node["steps"] >> pointer.steps;
}

void operator>>(const YAML::Node& node, Icon& icon) {
  icon.type = node["type"].as<std::string>();
  icon.on_color = node["on_color"].as<std::string>();
  icon.off_color = node["off_color"].as<std::string>();
}

void operator>>(const YAML::Node& node, Signal& signal) {
  signal.move = node["move"].as<std::string>();
  signal.hold = node["hold"].as<std::string>();
}

void operator>>(const YAML::Node& node, Card& card) {
  card.name = node["name"].as<std::string>();
  node["pointer"] >> card.pointer;
  node["icon"] >> card.icon;
  node["signal"] >> card.signal;
}

int main() {
  YAML::Node doc = YAML::LoadFile("config.yaml");

  Card card;
  
  doc["card"] >> card;

  std::cout << "Icon Type: " << card.icon.type << std::endl;

  return 0;
}
