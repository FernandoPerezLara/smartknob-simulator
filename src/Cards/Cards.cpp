#include "Cards.h"

void Cards::load_file(const std::string& filename) {
  YAML::Node file = YAML::LoadFile(filename);

  file["cards"] >> items;
}

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

void operator>>(const YAML::Node& node, Items& cards) {
  for (std::size_t i = 0; i < node.size(); i++) {
    Card card;

    node[i] >> card;
    cards.push_back(card);
  }
}
