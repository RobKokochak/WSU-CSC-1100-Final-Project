//==========================================================
//
// Title:      Part Pretenders, v3
// Course:     CSC 1100
// Lab Number: Project 2
// Author:     Rob Kokochak
// Date:       April 25 2021
// Description:
//   
//  This C++ console application reads car parts from an
//  external .txt file, sorts them alphabetically and puts
//  them into an array. It then allows for various processing
//  options on the data via a menu option such as listing the parts, 
//  searching for a part, adding a new part or deletig a part.
//==========================================================

#include <cstdlib> // For several general-purpose functions
#include <fstream> // For file handling
#include <iomanip> // For formatted output
#include <iostream> // For cin, cout, and system
#include <string> // For string data type
using namespace std; // So "std::cout" may be abbreviated to "cout"

//==========================================================
// Constants
//==========================================================

const string INPUT_FILE_NAME = "CarParts.txt";
const int ARRAY_SIZE = 100, COLW1 = 10, COLW2 = 20;

// Function Prototypes

void addPart(string parts[], int &partCount);

int binarySearchParts(string parts[], int arraySize, string key);

void deletePart(string parts[], int &partCount);

void listParts(string parts[], int arraySize);

int menuOption();

void searchParts(string parts[], int arraySize);

void sortParts(string parts[], int arraySize);

//==========================================================
// Function Definitions
//==========================================================

//==========================================================
// addPart
//==========================================================
void addPart(string parts[], int &partCount)
{

  // Declare variables
  string part;

  // Test whether room to add part
  if (partCount == ARRAY_SIZE)
    cout << "No room to add part at this time." << endl;
  else
  {

    // Prompt for and get part
    cout << "Enter the part to add: ";
    cin >> part;

    // Add part
    parts[partCount] = part;
    partCount = partCount + 1;
    cout << "Part '" << part << "' added to list.";

    sortParts(parts, partCount);

  }

}

//==========================================================
// binarySearchParts
//==========================================================
int binarySearchParts(string parts[], int arraySize, string key)
{

  // Declare variables
  int min = 0;
  int index;
  int max = arraySize - 1;

  // Loop to find key
  while (min <= max)
  {

    // Get midpoint of array
    index = (min + max) / 2;

    // Test if key found
    if (parts[index] == key)  // Guess is right on
      return index;
    else if (parts[index] < key)  // Guess is too low
      min = index + 1;
    else
      max = index - 1;

  }

  // Return index
  return -1;

}

//==========================================================
// deletePart
//==========================================================
void deletePart(string parts[], int &partCount)
{

  // Test whether room to add part
  if (partCount == 0)
    cout << "No part to delete at this time." << endl;
    
    else
    {
      int index;
      cout << "Enter a part's index to delete it: ";
      cin >> index;

      // Test validity
      if (index < 0 || index >= partCount)
        cout << "Error: invalid index of " << index << "." << endl;
      else{

        cout << "Part at index " << index << ": '" << parts[index] 
        << "' removed from list." << endl;

      // Delete part
        for (int i = index; i < partCount - 1; i++)
          parts[i] = parts[i + 1];

        partCount = partCount - 1;
    }
  }
}

//==========================================================
// listParts
//==========================================================
void listParts(string parts[], int arraySize)
{

  cout << endl << "Part List" << endl;
  cout << "---------" << endl;

  // Loop to list parts
  for (int i = 0; i < arraySize; i++)
    cout << setw(COLW1) << left << ("Index " + to_string(i) +  ": ") << 
      setw(COLW2) << left << parts[i] << endl;
  cout << endl << "Part count: " << arraySize << endl;

}

//==========================================================
// menuOption
//==========================================================
int menuOption()
{

  // Declare variables
  int option;

  // Show menu and get option
  cout << "\nPart Pretenders Menu" << endl;
  cout << "1 - List car parts" << endl;
  cout << "2 - Search car parts" << endl;
  cout << "3 - Add car part" << endl;
  cout << "4 - Delete car part" << endl;
  cout << "9 - Exit" << endl;
  cout << "\nEnter an option: ";
  cin >> option;
  return option;

}

//==========================================================
// readParts
//==========================================================
int readParts(string parts[])
{

  //declare variables
  ifstream inFile;
  int lineCount = 0;
  string line;

  // Attempt to open file
  inFile.open(INPUT_FILE_NAME);
  if (!inFile.is_open())
  {
    cout << "Error: unable to open file '"
     << INPUT_FILE_NAME << "'." << endl << endl;
  }
  else
  {
    cout << "Reading from file " << "'" << INPUT_FILE_NAME << "' ..." << endl;

    // Populate array parts and update line count
    lineCount = 0;
    for (int i = 0; inFile.good(); i++)
    {
      getline(inFile, line);
      parts[i] = line;
      lineCount = lineCount + 1;
    } 
    cout << lineCount << " line(s) read from file " << "'" << 
      INPUT_FILE_NAME << "'.";

    // return lineCount
    return lineCount;
  }

  // return -1 if file wasn't able to open
  return -1;
}

//==========================================================
// searchParts
//==========================================================
void searchParts(string parts[], int arraySize)
{

  // Declare variables
  string key;
  int index;

  // Prompt
  cout << "\nEnter a part to search for (no spaces): ";
  cin >> key;

  // Perform search
  index = binarySearchParts(parts, arraySize, key);

  // Display Result
  if (index != -1)
    cout << "'" << key << "' found at index "
    << index << "." << endl;
  else
    cout << "'" << key << "' NOT found." << endl;

}

//==========================================================
// sortParts
//==========================================================
void sortParts(string parts[], int arraySize)
{

  // Declare variables
  string value;
  int spot;

  // Loop to test each value
  for (int i = 1; i < arraySize; i++)
  {

    // Loop to find spot to place value
    value = parts[i]; 
    spot = i - 1; 
    while (spot >= 0 && parts[spot] > value)
    {
      parts[spot + 1] = parts[spot];
      spot = spot - 1;
    }

    // Place value in spot
    parts[spot + 1] = value;

  }

  // Print sorted message
  cout << endl << "Parts sorted." << endl;

}

//==========================================================
// main
//==========================================================
int main()
{

  // Show application header
  cout << "Welcome to Part Pretenders" << endl;
  cout << "--------------------------" << endl << endl;

  string parts[ARRAY_SIZE];

  // Populate array parts with items from CarParts.txt
  int partCount = readParts(parts);
  sortParts(parts, partCount);

  // Loop to process options
  int option = menuOption();
  while (option != 9)
  {

    // Handle option
    switch (option)
    {

      // List parts
    case 1:
      listParts(parts, partCount);
      break;

      // Search parts
    case 2:
      searchParts(parts, partCount);
      break;

      // Add part
    case 3:
      addPart(parts, partCount);
      break;

      // Delete part
    case 4:
      deletePart(parts, partCount);
      break;

      // Handle invalid option
    default:
      cout << endl << "Error: unknown option of '" << option
        << "'." << endl;

    }

    // Get next option
    option = menuOption();

  }

  // Show application close
  cout << "\nEnd of Part Pretenders" << endl;

}
