#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections::Generic;

// Main function that serves as the entry point for the application
[STAThread]
int main(array<String^>^ args) {
    // Enable visual styles for the application
    Application::EnableVisualStyles();

    // Set text rendering to be compatible with the default style
    Application::SetCompatibleTextRenderingDefault(false);

    // Create an instance of the MyForm class (a Windows Form)
    pp::MyForm form;

    // Start the application and run the form
    Application::Run(% form);

    // Return 0 to indicate successful completion
    return 0;
}

// Function to display information about duplicate strings within files
String^ DisplayDuplicateStringsWithinFiles(Dictionary<String^, List<String^>^>^ fileContents) {
    // Initialize a string to store information about duplicate strings
    String^ duplicateStringsWithinFiles = "";

    // Iterate through the fileContents dictionary, where keys are file names and values are lists of strings
    for each (String ^ fileName in fileContents->Keys) {
        // Get the list of strings for the current file
        List<String^>^ strings = fileContents[fileName];

        // Create a dictionary to count occurrences of each string in the file
        Dictionary<String^, int>^ stringCounts = gcnew Dictionary<String^, int>();

        // Iterate through the list of strings in the current file
        for each (String ^ str in strings) {
            // Check if the string is already in the stringCounts dictionary
            if (stringCounts->ContainsKey(str)) {
                // Increment the count if the string is already in the dictionary
                stringCounts[str]++;

                // If the count reaches 2, it's a duplicate
                if (stringCounts[str] == 2) {
                    // Add information about the duplicate string and the file to the result string
                    duplicateStringsWithinFiles += Path::GetFileName(fileName) + " contains multiple instances of: " + str + "\r\n";
                }
            }
            else {
                // If the string is not in the dictionary, add it with a count of 1
                stringCounts[str] = 1;
            }
        }
    }

    // Return the string containing information about duplicate strings
    return duplicateStringsWithinFiles;

}
void pp::MyForm::openButton_Click(System::Object^ sender, System::EventArgs^ e) {
    // Create an OpenFileDialog instance
    OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();

    // Set the filter for file types to only show text files with the .txt extension
    openFileDialog->Filter = "Text Files (*.txt)|*.txt";

    // Allow the user to select multiple files
    openFileDialog->Multiselect = true;

    // Check if the "OK" button is clicked in the file dialog
    if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        // Clear the previous content in the outputTextBox
        outputTextBox->Text = "";

        // Get an array of selected file names
        array<String^>^ fileNames = openFileDialog->FileNames;

        // Check if fewer than two files are selected
        if (fileNames->Length < 2) {
            // Display a message if at least two files are not selected
            outputTextBox->Text = "Please select at least two text files for comparison.";
            return;
        }

        // Create a dictionary to store the contents of selected files
        Dictionary<String^, List<String^>^>^ fileContents = gcnew Dictionary<String^, List<String^>^>();

        // Loop through the selected file names
        for (int i = 0; i < fileNames->Length; i++) {
            String^ fileName = fileNames[i];
            try {
                // Read the content of the file
                StreamReader^ sr = gcnew StreamReader(fileName);
                String^ fileContent = sr->ReadToEnd();
                sr->Close();

                // Split the file content by commas
                array<String^>^ strings = fileContent->Split(',');

                // Create a list to store cleaned and trimmed strings
                List<String^>^ stringList = gcnew List<String^>();
                for each (String ^ str in strings) {
                    // Trim whitespace and remove empty strings
                    String^ trimmedStr = str->Trim();
                    if (!String::IsNullOrEmpty(trimmedStr)) {
                        stringList->Add(trimmedStr);
                    }
                }

                // Add the cleaned string list to the fileContents dictionary
                fileContents[fileName] = stringList;
            }
            catch (IOException^ ex) {
                // Display an error message if there is an issue reading the file
                outputTextBox->Text = "Error reading " + fileName + ": " + ex->Message + "\r\n";
                return;
            }
        }

        // Create a string to store information about duplicate strings
        String^ duplicateStrings = "";

        // Create a dictionary to map each string to the files where it appears
        Dictionary<String^, List<String^>^>^ stringToFileMap = gcnew Dictionary<String^, List<String^>^>();

        // Iterate over the fileContents dictionary
        for each (String ^ fileName in fileContents->Keys) {
            List<String^>^ strings = fileContents[fileName];

            // For each string in a file, add the filename to the stringToFileMap
            for each (String ^ str in strings) {
                if (!stringToFileMap->ContainsKey(str)) {
                    stringToFileMap[str] = gcnew List<String^>();
                }
                if (!stringToFileMap[str]->Contains(Path::GetFileName(fileName))) {
                    stringToFileMap[str]->Add(Path::GetFileName(fileName));
                }
            }
        }

        // Create a string to store information about duplicate strings within files
        String^ duplicateStringsWithinFiles = DisplayDuplicateStringsWithinFiles(fileContents);

        // Display the information about duplicate strings in outputTextBox
        outputTextBox->Text = duplicateStrings;

        // Display the information about duplicate strings within files in outputTextBox1
        outputTextBox1->Text = duplicateStringsWithinFiles;

        // Create a string to store information about missing strings
        String^ missingStrings = "";

        // Create a dictionary to map each missing string to the files where it's missing
        Dictionary<String^, List<String^>^>^ missingStringToFiles = gcnew Dictionary<String^, List<String^>^>();

        // Iterate over the fileContents dictionary
        for each (String ^ fileName in fileContents->Keys) {
            List<String^>^ strings = fileContents[fileName];

            // For each missing string, add the filename to the missingStringToFiles
            for each (String ^ str in strings) {
                if (!missingStringToFiles->ContainsKey(str)) {
                    missingStringToFiles[str] = gcnew List<String^>();
                }
                if (!missingStringToFiles[str]->Contains(Path::GetFileName(fileName))) {
                    missingStringToFiles[str]->Add(Path::GetFileName(fileName));
                }
            }
        }

        // Iterate over missingStringToFiles to generate information about missing strings
        for each (String ^ str in missingStringToFiles->Keys) {
            List<String^>^ filesMissingString = missingStringToFiles[str];

            if (filesMissingString->Count > 1) {
                // Create a list to store unique filenames
                List<String^>^ uniqueFiles = gcnew List<String^>();
                for each (String ^ file in filesMissingString) {
                    if (!uniqueFiles->Contains(file)) {
                        uniqueFiles->Add(file);
                    }
                }

                // Add information about missing strings to the missingStrings string
                missingStrings += "\"" + str + "\" is missing in " + uniqueFiles[0] + " from " + String::Join(", ", uniqueFiles->GetRange(1, uniqueFiles->Count - 1)) + ".\r\n";
            }
        }

        // Display information about missing strings in outputTextBox2
        outputTextBox2->Text = missingStrings;
    }
}



