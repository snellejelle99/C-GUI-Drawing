//
// DrawPage.xaml.cpp
// Implementation of the DrawPage class
//

#include "pch.h"
#include "DrawPage.xaml.h"
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
using namespace Windows::UI::Xaml::Shapes;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

DrawPage::DrawPage()
{
	InitializeComponent();
}

Windows::UI::Input::PointerPoint ^startPoint;
Windows::UI::Xaml::Shapes::Rectangle ^rect;

void c___GUI_Drawing::DrawPage::canvas_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	startPoint = e->GetCurrentPoint(canvas);

	rect = ref new Rectangle();
	rect->Stroke = ref new SolidColorBrush(Windows::UI::Colors::Red);
	rect->StrokeThickness = 2;
	canvas->SetLeft(rect, startPoint->Position.X);
	canvas->SetTop(rect, startPoint->Position.Y);
	canvas->Children->Append(rect);
}


void c___GUI_Drawing::DrawPage::canvas_PointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if (e->Pointer->IsInContact == false || rect == nullptr)
		return;

	Windows::UI::Input::PointerPoint ^pos = e->GetCurrentPoint(canvas);

	double x = min(pos->Position.X, startPoint->Position.X);
	double y = min(pos->Position.Y, startPoint->Position.Y);

	double w = max(pos->Position.X, startPoint->Position.X) - x;
	double h = max(pos->Position.Y, startPoint->Position.Y) - y;

	rect->Width = w;
	rect->Height = h;

	canvas->SetLeft(rect, x);
	canvas->SetTop(rect, y);
}

void c___GUI_Drawing::DrawPage::canvas_PointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	rect = nullptr;
}

void c___GUI_Drawing::DrawPage::RevertHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}



