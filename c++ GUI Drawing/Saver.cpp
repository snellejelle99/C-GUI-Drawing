#include "Saver.h"

#include "pch.h"



// Global static pointer used to ensure a single instance of the class.
Saver* Saver::instance = nullptr;

Saver::Saver()
{
}

Saver::~Saver()
{
}

Saver * Saver::GetSaver()
{
	if (!instance) instance = new Saver();
	return instance;
}

void Saver::SetPath()
{

}

int Saver::SaveCanvas(std::vector<Shape*>shapes)
{
	//try {
	if (saveFile == nullptr) {

		//make savepicker object
		FileSavePicker^ savePicker = ref new FileSavePicker();
		savePicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;

		//add preferred extensions
		auto plainTextExtensions = ref new Platform::Collections::Vector<String^>();
		plainTextExtensions->Append(".txt");
		savePicker->FileTypeChoices->Insert("Plain Text", plainTextExtensions);
		savePicker->SuggestedFileName = "New Document";

		//deploy savepicker and retrieve file
		create_task(savePicker->PickSaveFileAsync()).then([this, shapes](StorageFile^ file)
		{
			if (file != nullptr)
			{
				//save chosen file in singleton for later use
				saveFile = file;

				// Prevent updates to the remote version of the file until we finish making changes and call CompleteUpdatesAsync.
				CachedFileManager::DeferUpdates(file);
				// write to file
				create_task(FileIO::WriteTextAsync(file, shapes[0]->ToString())).then([this, file]()
				{
					// Let Windows know that we're finished changing the file so the other app can update the remote version of the file.
					// Completing updates may require Windows to ask for user input.
					create_task(CachedFileManager::CompleteUpdatesAsync(file)).then([this, file](FileUpdateStatus status)
					{
						if (status == FileUpdateStatus::Complete)
						{
							//OutputTextBlock->Text = "File " + file->Name + " was saved.";
						}
						else
						{
							//OutputTextBlock->Text = "File " + file->Name + " couldn't be saved.";
						}
					});
				});
			}
			else
			{
				//OutputTextBlock->Text = "Operation cancelled.";
			}
		});

	}
	else
	{
		//retrieve file from singleton
		StorageFile^ file = saveFile;

		// Prevent updates to the remote version of the file until we finish making changes and call CompleteUpdatesAsync.
		CachedFileManager::DeferUpdates(file);
		// write to file
		create_task(FileIO::WriteTextAsync(file, "xxxxxxxxxxx")).then([this, file]()
		{
			// Let Windows know that we're finished changing the file so the other app can update the remote version of the file.
			// Completing updates may require Windows to ask for user input.
			create_task(CachedFileManager::CompleteUpdatesAsync(file)).then([this, file](FileUpdateStatus status)
			{
				if (status == FileUpdateStatus::Complete)
				{
					//OutputTextBlock->Text = "File " + file->Name + " was saved.";
				}
				else
				{
					//OutputTextBlock->Text = "File " + file->Name + " couldn't be saved.";
				}
			});
		});
	}
	/*}catch(Exception^ e)
	{
		return 0;
	}*/

	return 1;
}
