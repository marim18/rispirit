#ifndef RISPIRIT_INVENTORY_H
#define RISPIRIT_INVENTORY_H
class Inventory{
public:
    void DrawInv(sf::RenderWindow& window,std::string& curentstate);
    Inventory();
    bool menu = false;
    tgui::Gui Igui;
};

#endif //RISPIRIT_INVENTORY_H
