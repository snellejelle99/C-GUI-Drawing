#ifndef CHANGEGROUPCOLORVISITOR
#define CHANGEGROUPCOLORVISITOR

#include "ShapeVisitor.h"

//ChangeGroupColorVisitor class defenition
class ChangeGroupColorVisitor : public ShapeVisitor
{
public:
	ChangeGroupColorVisitor(Windows::UI::Color newColor);
	~ChangeGroupColorVisitor();
	virtual void Visit(Rectangle* shape);
	virtual void Visit(Ellipse* shape);
private:
	Windows::UI::Color newColor;
};

#endif // ! CHANGEGROUPCOLORVISITOR
