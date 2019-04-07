#include "Linklist.h"

Position::Position(std::string MMSI, double longitude, double latitude, 
        double SOG, double COG, int year, int month, int day, 
        int hour, int minute, int second): MMSI(MMSI), Longitude(longitude), 
        Latitude(latitude), SOG(SOG), COG(COG), Year(year), Month(month)
        , Day(day), Hour(hour), Minute(minute), Second(second){}

Position::Position(){}

Position::~Position(){}


Node::Node()
{
    next = nullptr;
}

Node::Node(Position position) : position(position), next(nullptr){}

Node::~Node()
{
    delete next;
}

Node* Node::get_next()
{
    return next;
}

Position Node::get_position()
{
    return position;
}

Linklist::Linklist()
{
    head = nullptr;
    rear = nullptr;
    length = 0;
}

void Linklist::push_back(Node* node)
{
    if (head == nullptr)
    {
        head = node;
        rear = head;
    }
    else
    {
        rear -> next = node;
        rear = node;
    }
    rear -> next = nullptr;
    ++ length;
}


int Linklist::size()
{
    return length;
}

bool Linklist::is_empty()
{
    return !length;
}

Node* Linklist::get_head()
{
    return head;
}


void Linklist::traverse()
{
    Node* temp = head;
    while (temp != rear)
    {
        std::cout << temp -> get_position().get_longitude() << std::endl;
        temp = temp -> next;
    }
}

// void Linklist::text_rear_display()
// {
//     std::cout << length << std::endl;
//     std::cout << rear -> get_position().getLongitude() << std::endl;
// }

void Linklist::set_head(Node* node)
{
    -- length;
    head = node;
}