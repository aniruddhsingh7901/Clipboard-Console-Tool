#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function to read the contents of a file into a vector of strings
vector<string> readFile(const string& filename) {
  vector<string> lines;
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return lines;
  }
  string line;
  while (getline(file, line)) {
    lines.push_back(line);
  }
  file.close();
  return lines;
}

// Function to write the contents of a vector of strings to a file
void writeFile(const string& filename, const vector<string>& lines) {
  ofstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return;
  }
  for (const string& line : lines) {
    file << line << endl;
  }
  file.close();
}

// Function to perform the cut operation
void cut(vector<string>& lines, int startLine, int startIndex, int endLine, int endIndex) {
  if (startLine > endLine || (startLine == endLine && startIndex > endIndex)) {
    cerr << "Invalid selection range." << endl;
    return;
  }

  string clipText;
  for (int i = startLine; i <= endLine; ++i) {
    clipText += lines[i].substr(startIndex, endIndex - startIndex + 1);
    if (i != endLine) {
      clipText += "\n";
    }
  }

  // Remove the cut text from the lines
  lines.erase(lines.begin() + startLine, lines.begin() + endLine + 1);

  cout << "Cut text: " << clipText << endl;
}

// Function to perform the copy operation
void copy(const vector<string>& lines, int startLine, int startIndex, int endLine, int endIndex) {
  if (startLine > endLine || (startLine == endLine && startIndex > endIndex)) {
    cerr << "Invalid selection range." << endl;
    return;
  }

  string clipText;
  for (int i = startLine; i <= endLine; ++i) {
    clipText += lines[i].substr(startIndex, endIndex - startIndex + 1);
    if (i != endLine) {
      clipText += "\n";
    }
  }

  cout << "Copied text: " << clipText << endl;
}

// Function to perform the paste operation
void paste(vector<string>& lines, int line, int index, const string& clipText) {
  // Insert the copied text at the specified line and index
  lines.insert(lines.begin() + line, clipText);

  // Update line indices after insertion
  for (int i = line + 1; i < lines.size(); ++i) {
    // ... (code to update line numbers)
  }

  cout << "Pasted text." << endl;
}

int main() {
  string filename = "selected.txt";
  vector<string> lines = readFile(filename);

  string clipText; // Stores the most recently cut or copied text

  int choice, startLine, startIndex, endLine, endIndex;

  while (true) {
    cout << "\nClipboard Tool (selected.txt)" << endl;
    cout << "1. Cut" << endl;
    cout << "2. Copy" << endl;
    cout << "3. Paste" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 4) {
      break;
    }

    cout << "Enter start line, start index, end line, end index: ";
    cin >> startLine >> startIndex >> endLine >> endIndex;

    switch (choice) {
      case 1:
        cut(lines, startLine - 1, startIndex - 1, endLine - 1, endIndex - 1);
        clipText = ""; // Clear clipText after cut
        break;
      case 2:
        copy(lines, startLine - 1, startIndex - 1, endLine - 1, endIndex - 1);
        break;
      case 3:
        paste(lines, startLine - 1, startIndex - 1, clipText);
        break;
      default:
        cerr << "Invalid choice. Please enter a number between 1 and 4." << endl;
    }
  }

  // Write modified lines back to file
  writeFile(filename, lines);

  cout << "Exiting Clipboard Tool. Changes saved to " << filename << "." << endl;

  return 0;
}