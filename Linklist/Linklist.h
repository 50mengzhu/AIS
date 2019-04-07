#include "../Position/Position.hpp"
#include <iostream>

class Linklist;

class Node
{
friend class Linklist;
// friend class process;
private:
    Position position;
    Node*    next;
public:
    Node();
    ~Node();
    Node(Position position);

    Position get_position();
    Node* get_next();
};

class Linklist
{
private:
   Node* head;
   Node* rear;
   int   length;

public: 
    void push_back(Node* node);
    Linklist();
    bool is_empty();
    Node* get_head();

    void traverse();
    // void text_rear_display();
    void set_head(Node* node);

    int size();
};
