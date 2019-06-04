#include "Loader.h"

Loader::Loader(c___GUI_Drawing::DrawPage ^ drawpage,Windows::UI::Xaml::Controls::Canvas ^ canvas, std::vector<Shape*>& shapes) :drawpage(drawpage), canvas(canvas), shapes(shapes)
{
}

Loader::~Loader()
{
}

//open a file picker and load a selected text file
void Loader::LoadFile()
{
	FileOpenPicker^ openPicker = ref new FileOpenPicker();
	openPicker->ViewMode = PickerViewMode::Thumbnail;
	openPicker->SuggestedStartLocation = PickerLocationId::PicturesLibrary;
	openPicker->FileTypeFilter->Append(".TXT");
	openPicker->FileTypeFilter->Append(".txt");


	create_task(openPicker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file)
		{
			create_task(FileIO::ReadTextAsync(file)).then([this, file](task<String^> task)
			{
				try
				{
					String^ fileContent = task.get();
					Build(ConvertString(fileContent));

					
					//rootPage->NotifyUser("The following text was read from '" + file->Name + "':\n" + fileContent, NotifyType::StatusMessage);
				}
				catch (COMException^ ex)
				{
					if (ex->HResult == HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION))
					{
						//rootPage->NotifyUser("File could not be decoded as Unicode.", NotifyType::ErrorMessage);
					}
					else
					{
						//rootPage->HandleIoException(ex, "Error reading from '" + file->Name + "'");
					}
				}
			});
		}
		else
		{
			//OutputTextBlock->Text = "Operation cancelled.";
		}
	});

}

//convert a windows unicode string to a c++ ascii string
std::string Loader::ConvertString(String ^ winString)
{
	
	std::wstring fooW(winString->Begin());
	std::string fooA(fooW.begin(), fooW.end());
	return fooA;
}

//split a given string on a given character. returns a list of substrings
std::vector<std::string> Loader::StringSplitOnChar(std::string string, char token)
{
	std::vector<std::string> result;
	std::string temp;
	int markbegin = 0;
	int markend = 0;

	for (unsigned int i = 0; i <= string.length(); ++i) {		
		if (string[i] == token || i == string.length()) {
			markend = i;
			result.push_back(string.substr(markbegin, markend - markbegin));
			markbegin = (i + 1);
		}
	}
	return result;
}

//build the loaded string into objects and add items to canvas and shapes list
void Loader::Build(std::string loadedstring)
{	

	//split loaded string into lines
	std::vector<std::string> lines = StringSplitOnChar(loadedstring, '\n');

	//indentcount and hierarchy vector for building correct hierarchy
	int currentIndentCount = 0;
	std::vector<std::tuple<int, Shape*>> hierarchyQueue = std::vector<std::tuple<int, Shape*>>();

	for (unsigned int i = 0; i < lines.size()-1; i++) //repeat for each line
	{ 

		std::vector<std::string> splitline = StringSplitOnChar(lines[i], ' '); //split line into words

		int indentCount = 0;
		Shape* object = nullptr;

		for (unsigned int i = 0; i < splitline.size(); i++) { // check every word for keyword rect or ellip
			object == nullptr; //reset object

			if (splitline[i] == "rect") {
				//get all info regarding rectangle parameters from strings
				double left = std::stod(splitline[i + 1]);
				double top = std::stod(splitline[i + 2]);
				double width = std::stod(splitline[i + 3]);
				double height = std::stod(splitline[i + 4]);
				int a = std::stoi(splitline[i + 5]);
				int r = std::stoi(splitline[i + 6]);
				int g = std::stoi(splitline[i + 7]);
				int b = std::stoi(splitline[i + 8]);
				Windows::UI::Color color = Windows::UI::ColorHelper::FromArgb(a, r, g, b);

				//create windows shape object and add click and hover handlers
				Windows::UI::Xaml::Shapes::Rectangle ^rect = ref new Shapes::Rectangle();
				rect->AddHandler(UIElement::TappedEvent, ref new Windows::UI::Xaml::Input::TappedEventHandler(drawpage, &c___GUI_Drawing::DrawPage::SelectHandler), true);
				rect->AddHandler(UIElement::PointerEnteredEvent, ref new Windows::UI::Xaml::Input::PointerEventHandler(drawpage, &c___GUI_Drawing::DrawPage::PointerEnterHandler), true);
				rect->AddHandler(UIElement::PointerExitedEvent, ref new Windows::UI::Xaml::Input::PointerEventHandler(drawpage, &c___GUI_Drawing::DrawPage::PointerLeaveHandler), true);
				rect->Fill = ref new SolidColorBrush(color);
				rect->StrokeThickness = 5.0;
				canvas->SetLeft(rect, left);
				canvas->SetTop(rect, top);
				rect->Width = width;
				rect->Height = height;
				canvas->Children->Append(rect);

				object = new Rectangle(left, top, color, rect);
				if (indentCount == 0)shapes.push_back(object); //only add if not subshape
				break;// no point in checking further if first keyword is found
			}
			else if (splitline[i] == "ellip") {
				//get all info regarding ellipse parameters from strings
				double left = std::stod(splitline[i + 1]);
				double top = std::stod(splitline[i + 2]);
				double width = std::stod(splitline[i + 3]);
				double height = std::stod(splitline[i + 4]);
				int a = std::stoi(splitline[i + 5]);
				int r = std::stoi(splitline[i + 6]);
				int g = std::stoi(splitline[i + 7]);
				int b = std::stoi(splitline[i + 8]);
				Windows::UI::Color color = Windows::UI::ColorHelper::FromArgb(a, r, g, b);

				//create windows shape object and add click and hover handlers
				Windows::UI::Xaml::Shapes::Ellipse ^ellip = ref new Shapes::Ellipse();
				ellip->AddHandler(UIElement::TappedEvent, ref new Windows::UI::Xaml::Input::TappedEventHandler(drawpage, &c___GUI_Drawing::DrawPage::SelectHandler), true);
				ellip->AddHandler(UIElement::PointerEnteredEvent, ref new Windows::UI::Xaml::Input::PointerEventHandler(drawpage, &c___GUI_Drawing::DrawPage::PointerEnterHandler), true);
				ellip->AddHandler(UIElement::PointerExitedEvent, ref new Windows::UI::Xaml::Input::PointerEventHandler(drawpage, &c___GUI_Drawing::DrawPage::PointerLeaveHandler), true);
				ellip->Fill = ref new SolidColorBrush(color);
				ellip->StrokeThickness = 5.0;
				canvas->SetLeft(ellip, left);
				canvas->SetTop(ellip, top);
				ellip->Width = width;
				ellip->Height = height;
				canvas->Children->Append(ellip);

				object = new Ellipse(left, top, color, ellip);
				if(indentCount == 0)shapes.push_back(object); //only add if not subshape
				break; // no point in checking further if first keyword is found
			}
			else //if its not a keyword then its an indent
			{
				indentCount++;
			}						
		}

		if (indentCount == 0) //if indents are 0 empty hierarchy because this is a new primary node
		{
			hierarchyQueue = std::vector<std::tuple<int, Shape*>>(); //empty hierachy tree
			hierarchyQueue.push_back(std::tuple<int, Shape*>(indentCount, object));
			currentIndentCount = 0;
		}
		else if (indentCount > currentIndentCount) //inf indents are higher than last time. increase 1 step in the hierarchy
		{
			std::get<1>(hierarchyQueue[currentIndentCount])->AddSubShape(object);
			hierarchyQueue.push_back(std::tuple<int, Shape*>(indentCount, object)); //add to hierarchy
			currentIndentCount++;
		}
		else //we are decreasing in the hierachy to the last common node
		{
			hierarchyQueue.erase(hierarchyQueue.begin() + indentCount, hierarchyQueue.end()); //erase back untill the last common parent
			hierarchyQueue.push_back(std::tuple<int, Shape*>(indentCount, object)); //add new object to hierarchy
			std::get<1>(hierarchyQueue[indentCount - 1])->AddSubShape(object);
			currentIndentCount = indentCount;
		}
	}
}


