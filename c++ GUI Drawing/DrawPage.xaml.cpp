//
// DrawPage.xaml.cpp
// Implementation of the DrawPage class
//

#include "pch.h"
#include "DrawPage.xaml.h"

//saver singleton
#include "Saver.h"

//loader/builder
#include "Loader.h"

//shapes
#include "Shape.h"
#include "Rectangle.h"
#include "Ellipse.h"

//decorators
#include "RedBorderDecorator.h"
#include "BlueBorderDecorator.h"
#include "NoBorderDecorator.h"

//commands
#include "Command.h"
#include "ChangeColorCommand.h"
#include "ChangeGroupColorCommand.h"
#include "AddRectangleCommand.h"
#include "AddEllipseCommand.h"
#include "DeleteCommand.h"
#include "GroupCommand.h"
#include "MoveCommand.h"
#include "MoveGroupCommand.h"

//commandstack
#include "CommandStack.h"

//#include <cmath>

using namespace c___GUI_Drawing;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
//using namespace Windows::UI::Xaml::Shapes;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

enum SelectedElem { rectangle, ellipse, cssingle, csgroup, smove, gmove, group, del, none };

// global initialization of required variables for creating shapes
Windows::UI::Input::PointerPoint ^startPoint;
Windows::UI::Xaml::Shapes::Rectangle ^rect;
Windows::UI::Xaml::Shapes::Ellipse ^ellip;
Shape* selectedShape = nullptr;

Windows::UI::Color selectedColor; // currently selected color
SelectedElem sElem = none; // currently selected shape (default none)

//list of shapes
std::vector<Shape*> shapes;

//commandstack
CMDStack commandStack = CMDStack();

//loader for loading files only set to other than null if used
Loader * loader = nullptr;

DrawPage::DrawPage()
{
	InitializeComponent();
}

void c___GUI_Drawing::DrawPage::canvas_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// returns if shape or move is not selected
	if (sElem == cssingle || sElem == csgroup || sElem == group || sElem == del || sElem == none) return;

	startPoint = e->GetCurrentPoint(canvas);

	// create shape with selected variables
	if (sElem == rectangle)
	{
		rect = ref new Shapes::Rectangle();
		rect->AddHandler(UIElement::TappedEvent, ref new TappedEventHandler(this, &DrawPage::SelectHandler), true);
		rect->AddHandler(UIElement::PointerEnteredEvent, ref new PointerEventHandler(this, &DrawPage::PointerEnterHandler), true);
		rect->AddHandler(UIElement::PointerExitedEvent, ref new PointerEventHandler(this, &DrawPage::PointerLeaveHandler), true);
		rect->Fill = ref new SolidColorBrush(selectedColor);
		rect->StrokeThickness = 5.0;
		canvas->SetLeft(rect, startPoint->Position.X);
		canvas->SetTop(rect, startPoint->Position.Y);
		canvas->Children->Append(rect);
	}
	else if (sElem == ellipse)
	{
		ellip = ref new Shapes::Ellipse();
		ellip->AddHandler(UIElement::TappedEvent, ref new TappedEventHandler(this, &DrawPage::SelectHandler), true);
		ellip->AddHandler(UIElement::PointerEnteredEvent, ref new PointerEventHandler(this, &DrawPage::PointerEnterHandler), true);
		ellip->AddHandler(UIElement::PointerExitedEvent, ref new PointerEventHandler(this, &DrawPage::PointerLeaveHandler), true);
		ellip->Fill = ref new SolidColorBrush(selectedColor);
		ellip->StrokeThickness = 5.0;
		canvas->SetLeft(ellip, startPoint->Position.X);
		canvas->SetTop(ellip, startPoint->Position.Y);
		canvas->Children->Append(ellip);
	}
	else if (sElem == smove) //for creating single move commands, returns when no shape is selected.
	{
		if (selectedShape == nullptr) return;

		Command* cmd = new MoveCommand(canvas, selectedShape, startPoint->Position.X, startPoint->Position.Y);
		commandStack.Add(cmd);

		selectedShape = nullptr;
	}
	else if (sElem == gmove) //for creating group move commands, returns when no shape is selected
	{
		if (selectedShape == nullptr) return;

		Command* cmd = new MoveGroupCommand(canvas, selectedShape, startPoint->Position.X, startPoint->Position.Y);
		commandStack.Add(cmd);

		selectedShape = nullptr;
	}
}

void c___GUI_Drawing::DrawPage::canvas_PointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// returns when no modification to the shape needs to be done
	if (e->Pointer->IsInContact == false || (rect == nullptr && ellip == nullptr))
		return;

	// updates shape with new variables
	Windows::UI::Input::PointerPoint ^pos = e->GetCurrentPoint(canvas);

	double x = min(pos->Position.X, startPoint->Position.X);
	double y = min(pos->Position.Y, startPoint->Position.Y);

	double w = max(pos->Position.X, startPoint->Position.X) - x;
	double h = max(pos->Position.Y, startPoint->Position.Y) - y;

	if (sElem == rectangle)
	{
		rect->Width = w;
		rect->Height = h;

		canvas->SetLeft(rect, x);
		canvas->SetTop(rect, y);
	}
	else if (sElem == ellipse)
	{
		ellip->Width = w;
		ellip->Height = h;

		canvas->SetLeft(ellip, x);
		canvas->SetTop(ellip, y);
	}
}

void c___GUI_Drawing::DrawPage::canvas_PointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// returns if shape is not selected
	if (sElem == cssingle || sElem == csgroup || sElem == smove || sElem == gmove || sElem == group || sElem == del || sElem == none) return;

	// define cmd object and add it to the commandstack
	Command* cmd = nullptr;

	if (sElem == rectangle)
	{
		cmd = new AddRectangleCommand(canvas, shapes, rect, selectedColor);
	}
	else if (sElem == ellipse)
	{
		cmd = new AddEllipseCommand(canvas, shapes, ellip, selectedColor);
	}

	commandStack.Add(cmd);
	cmd = nullptr;


	rect = nullptr;
	ellip = nullptr;
}

//method for handling the user UI input and switching between elements.
void c___GUI_Drawing::DrawPage::ObjectToggle(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	DrawPage::RectangleSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	DrawPage::EllipseSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	DrawPage::ColorSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	DrawPage::MoveleSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	DrawPage::GroupSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	DrawPage::DeleteSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);

	if (sender->Equals(RectangleSelect))
	{
		sElem = rectangle;
		DrawPage::RectangleSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(EllipseSelect))
	{
		sElem = ellipse;
		DrawPage::EllipseSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(ColorSelect))
	{
		sElem = none;
	}
	else if (sender->Equals(CSSingle))
	{
		sElem = cssingle;
		DrawPage::ColorSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(CSGroup))
	{
		sElem = csgroup;
		DrawPage::ColorSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(MoveleSelect))
	{
		sElem = none;
	}
	else if (sender->Equals(MSingle))
	{
		sElem = smove;
		DrawPage::MoveleSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(MGroup))
	{
		sElem = gmove;
		DrawPage::MoveleSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(GroupSelect))
	{
		sElem = group;
		DrawPage::GroupSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(DeleteSelect))
	{
		sElem = del;
		DrawPage::DeleteSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else
	{
		sElem = none;
	}

	selectedShape = nullptr;
}

//method for switching currently selected color
void c___GUI_Drawing::DrawPage::ColorPicker_ColorChanged(Windows::UI::Xaml::Controls::ColorPicker^ sender, Windows::UI::Xaml::Controls::ColorChangedEventArgs^ args)
{
	selectedColor = sender->Color;
}

//method for handling the undo button
void c___GUI_Drawing::DrawPage::UndoHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	commandStack.Undo();
}

//method for handling the redo button
void c___GUI_Drawing::DrawPage::RedoHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	commandStack.Redo();
}

//Method that with a decorator pattern draws a border around the child and parent shapes when the group tool is selected
void c___GUI_Drawing::DrawPage::PointerEnterHandler(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if (sElem != group) return; //return when group tool isn't selected

	Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender); //cast sender to wpf shape

	//loop through all elements in the shapes vector, if shape isn't found loop through the children of the elements in shapes vector.
	for (Shape* s : shapes)
	{
		//if shape is found that is the sender grab all its parents and children and draw with a decorator a border
		if (s->CheckShape(shape) == true)
		{
			std::vector<BlueBorderDecorator> children;
			std::vector<RedBorderDecorator> parents;

			for (Shape* c : s->GetSubShapes())
			{
				BlueBorderDecorator bbd = BlueBorderDecorator(c);
				children.push_back(bbd);
			}

			for (Shape* c : s->GetAllParents())
			{
				RedBorderDecorator rbd = RedBorderDecorator(c);
				parents.push_back(rbd);
			}

			for (BlueBorderDecorator bbd : children)
			{
				bbd.Draw();
			}

			for (RedBorderDecorator rbd : parents)
			{
				rbd.Draw();
			}
			return;
		}
		else
		{
			std::vector<Shape*> sshapes = s->GetSubShapes();
			for (Shape* s : sshapes)
			{
				//if shape is found that is the sender grab all its parents and children and draw with a decorator a border
				if (s->CheckShape(shape) == true)
				{
					std::vector<BlueBorderDecorator> children;
					std::vector<RedBorderDecorator> parents;

					for (Shape* c : s->GetSubShapes())
					{
						BlueBorderDecorator bbd = BlueBorderDecorator(c);
						children.push_back(bbd);
					}

					for (Shape* c : s->GetAllParents())
					{
						RedBorderDecorator rbd = RedBorderDecorator(c);
						parents.push_back(rbd);
					}

					for (BlueBorderDecorator bbd : children)
					{
						bbd.Draw();
					}

					for (RedBorderDecorator rbd : parents)
					{
						rbd.Draw();
					}
					return;
				}
			}
		}
	}
}

//method that removes borders when the pointer leaves a wpf element.
void c___GUI_Drawing::DrawPage::PointerLeaveHandler(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if (sElem != group) return; // return if group tool isn't selected

	Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

	//loop through all elements in the shapes vector, if shape isn't found loop through the children of the elements in shapes vector.
	for (Shape* s : shapes)
	{
		//if shape is found that is the sender grab all its parents and children and remove with a decorator the borders
		if (s->CheckShape(shape) == true)
		{
			std::vector<NoBorderDecorator> children;
			std::vector<NoBorderDecorator> parents;

			for (Shape* c : s->GetSubShapes())
			{
				NoBorderDecorator nbd = NoBorderDecorator(c);
				children.push_back(nbd);
			}

			for (Shape* c : s->GetAllParents())
			{
				NoBorderDecorator nbd = NoBorderDecorator(c);
				parents.push_back(nbd);
			}

			for (NoBorderDecorator nbd : children)
			{
				nbd.Draw();
			}

			for (NoBorderDecorator nbd : parents)
			{
				nbd.Draw();
			}
			return;
		}
		else
		{
			std::vector<Shape*> sshapes = s->GetSubShapes();
			for (Shape* s : sshapes)
			{
				//if shape is found that is the sender grab all its parents and children and remove with a decorator the borders
				if (s->CheckShape(shape) == true)
				{
					std::vector<NoBorderDecorator> children;
					std::vector<NoBorderDecorator> parents;

					for (Shape* c : s->GetSubShapes())
					{
						NoBorderDecorator nbd = NoBorderDecorator(c);
						children.push_back(nbd);
					}

					for (Shape* c : s->GetAllParents())
					{
						NoBorderDecorator nbd = NoBorderDecorator(c);
						parents.push_back(nbd);
					}

					for (NoBorderDecorator nbd : children)
					{
						nbd.Draw();
					}

					for (NoBorderDecorator nbd : parents)
					{
						nbd.Draw();
					}
					return;
				}
			}
		}
	}
}

//method that handles the creation of commands based on the currently selected element
void c___GUI_Drawing::DrawPage::SelectHandler(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	//returns if shape is selected
	if (sElem == rectangle || sElem == ellipse) return;

	if (sElem == cssingle)
	{
		Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

		for (Shape* s : shapes)
		{
			if (s->CheckShape(shape) == true)
			{
				Command* cmd = new ChangeColorCommand(s, selectedColor);
				commandStack.Add(cmd);
				return;
			}
			else
			{
				std::vector<Shape*> sshapes = s->GetSubShapes();
				for (Shape* s : sshapes)
				{
					if (s->CheckShape(shape) == true)
					{
						Command* cmd = new ChangeColorCommand(s, selectedColor);
						commandStack.Add(cmd);
						return;
					}
				}
			}
		}
	}
	if (sElem == csgroup)
	{
		Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

		for (Shape* s : shapes)
		{
			if (s->CheckShape(shape) == true)
			{
				Command* cmd = new ChangeGroupColorCommand(s, selectedColor);
				commandStack.Add(cmd);
				return;
			}
			else
			{
				std::vector<Shape*> sshapes = s->GetSubShapes();
				for (Shape* s : sshapes)
				{
					if (s->CheckShape(shape) == true)
					{
						Command* cmd = new ChangeGroupColorCommand(s, selectedColor);
						commandStack.Add(cmd);
						return;
					}
				}
			}
		}
	}
	else if (sElem == smove || sElem == gmove)
	{
		if (selectedShape == nullptr)
		{
			Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

			for (Shape* s : shapes)
			{
				if (s->CheckShape(shape) == true)
				{
					selectedShape = s;
					return;
				}
				else
				{
					std::vector<Shape*> sshapes = s->GetSubShapes();
					for (Shape* s : sshapes)
					{
						if (s->CheckShape(shape) == true)
						{
							selectedShape = s;
							return;
						}
					}
				}
			}
		}
	}
	else if (sElem == group)
	{
		Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

		for (Shape* s : shapes)
		{
			if (s->CheckShape(shape) == true)
			{
				if (selectedShape != nullptr)
				{
					Command* cmd = new GroupCommand(s, selectedShape, shapes);
					commandStack.Add(cmd);
					selectedShape = nullptr;
				}
				else selectedShape = s;
				return;
			}
			else
			{
				std::vector<Shape*> sshapes = s->GetSubShapes();
				for (Shape* s : sshapes)
				{
					if (s->CheckShape(shape) == true)
					{
						if (selectedShape != nullptr)
						{
							Command* cmd = new GroupCommand(s, selectedShape, shapes);
							commandStack.Add(cmd);
							selectedShape = nullptr;
						}
						else selectedShape = s;
						return;
					}
				}
			}
		}
	}
	else if (sElem == del)
	{
		Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

		for (Shape* s : shapes)
		{
			if (s->CheckShape(shape) == true)
			{
				Command* cmd = new DeleteCommand(canvas, s, shapes);
				commandStack.Add(cmd);
				return;
			}
			else
			{
				std::vector<Shape*> sshapes = s->GetSubShapes();
				for (Shape* s : sshapes)
				{
					if (s->CheckShape(shape) == true)
					{
						Command* cmd = new DeleteCommand(canvas, s, shapes);
						commandStack.Add(cmd);
						return;
					}
				}
			}
		}
	}
}

//method for handeling the save button
void c___GUI_Drawing::DrawPage::SaveHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Saver::GetSaver()->SaveCanvas(shapes);
}

//method for handling the load button
void c___GUI_Drawing::DrawPage::LoadHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{	
	loader = new Loader(this, canvas, shapes);
	loader->LoadFile();	
}
