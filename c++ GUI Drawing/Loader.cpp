#include "Loader.h"

Loader::Loader(c___GUI_Drawing::DrawPage ^ drawpage,Windows::UI::Xaml::Controls::Canvas ^ canvas, std::vector<Shape*>& shapes) :drawpage(drawpage), canvas(canvas), shapes(shapes)
{
}

Loader::~Loader()
{
}

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


std::string Loader::ConvertString(String ^ winString)
{
	
	std::wstring fooW(winString->Begin());
	std::string fooA(fooW.begin(), fooW.end());
	return fooA;
}

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

void Loader::Build(std::string loadedstring)
{
	std::vector<std::string> lines = StringSplitOnChar(loadedstring, '\n');

	for (unsigned int i = 0; i < lines.size(); i++) { //repeat for each line

		std::vector<std::string> splitline = StringSplitOnChar(lines[i], ' '); //split line into words

		for (unsigned int i = 0; i < splitline.size(); i++) { // check every word for keyword rect or ellip
			if (splitline[i] == "rect") {
				double left = std::stod(splitline[i + 1]);
				double top = std::stod(splitline[i + 2]);
				double width = std::stod(splitline[i + 3]);
				double height = std::stod(splitline[i + 4]);
				int a = std::stoi(splitline[i + 5]);
				int r = std::stoi(splitline[i + 6]);
				int g = std::stoi(splitline[i + 7]);
				int b = std::stoi(splitline[i + 8]);
				Windows::UI::Color color = Windows::UI::ColorHelper::FromArgb(a, r, g, b);

				Windows::UI::Xaml::Shapes::Rectangle ^rect = ref new Shapes::Rectangle();
				rect->AddHandler(UIElement::TappedEvent, ref new Windows::UI::Xaml::Input::TappedEventHandler(drawpage, &c___GUI_Drawing::DrawPage::SelectHandler), true);
				rect->Fill = ref new SolidColorBrush(color);
				canvas->SetLeft(rect, left);
				canvas->SetTop(rect, top);
				rect->Width = width;
				rect->Height = height;
				canvas->Children->Append(rect);

				Rectangle * rectObject = new Rectangle(left, top, color, rect);
				shapes.push_back(rectObject);
				break;// no point in checking further if first keyword is found
			}
			else if (splitline[i] == "ellip") {
				double left = std::stod(splitline[i + 1]);
				double top = std::stod(splitline[i + 2]);
				double width = std::stod(splitline[i + 3]);
				double height = std::stod(splitline[i + 4]);
				int a = std::stoi(splitline[i + 5]);
				int r = std::stoi(splitline[i + 6]);
				int g = std::stoi(splitline[i + 7]);
				int b = std::stoi(splitline[i + 8]);
				Windows::UI::Color color = Windows::UI::ColorHelper::FromArgb(a, r, g, b);

				Windows::UI::Xaml::Shapes::Ellipse ^ellip = ref new Shapes::Ellipse();
				ellip->AddHandler(UIElement::TappedEvent, ref new Windows::UI::Xaml::Input::TappedEventHandler(drawpage, &c___GUI_Drawing::DrawPage::SelectHandler), true);
				ellip->Fill = ref new SolidColorBrush(color);
				canvas->SetLeft(ellip, left);
				canvas->SetTop(ellip, top);
				ellip->Width = width;
				ellip->Height = height;
				canvas->Children->Append(ellip);

				Ellipse * rectObject = new Ellipse(left, top, color, ellip);
				shapes.push_back(rectObject);
				break; // no point in checking further if first keyword is found
			}
			else {

			}
		}
	}
}


