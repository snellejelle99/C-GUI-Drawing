#include "ChangeColorCommand.h"



ChangeColorCommand::ChangeColorCommand(Shape & shape, Windows::UI::Color color) : shape(shape), color(color)
{

}


ChangeColorCommand::~ChangeColorCommand()
{
}
