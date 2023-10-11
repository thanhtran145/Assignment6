// Name: Thanh Tran
// Date: 10/10/2023
// Desciption: Chapter 6 - Assignments 6

//Credit:
//Joe Bryant& Erik Santana 
//Saul Merino & John Kim 
//Otoniel Torres Bernal
//Christian Hernandez

#include<iostream>
#include"input.h"
#include <fstream>
#include "MyBagTemplate.h"
#include "Course.h"

using namespace std;

// Function Prototypes
void Application();

// Main Function
int main()
{
	// Main Menu and Options
	do
	{
		system("cls");
		cout << "\n\tCMPR131 Chapter 6: non-template and template Container by Thanh Tran (10/10/2023)";
		cout << "\n\t" << string(100, char(205));
		cout << "\n\t\t1> Non-template MyBag container of int";
		cout << "\n\t\t2> Template MyBag<double> container";
		cout << "\n\t\t3> Application using MyBag container";
		cout << "\n\t" << string(100, char(196));
		cout << "\n\t\t0> Exit";
		cout << "\n\t" << string(100, char(205));

		switch (inputInteger("\n\t\tOption: ", 0, 3))
		{
		case 0: exit(1); break;
		case 1: break;
		case 2: break;
		case 3: Application(); break;
		default: cout << "\t\tERROR - Invalid option."; break;
		}
		cout << "\n";
		system("pause");
	} while (true);

	return EXIT_SUCCESS;
}

//Precondition: NA
//Postcondition: Display the menu for option 3
void Application()
{
	vector<Course> courses;
	int num_courses = 0;
	string file_name = "";

	do
	{
		system("cls");
		cout << "\n\t\t 3) Courses using MyBags of integers, strings, doubles, and chars";
		cout << "\n\t\t" << string(70, char(196));
		cout << "\n\t\t\t1> Specify the number of courses";
		cout << "\n\t\t\t2> Read in data file and insert into courses";
		cout << "\n\t\t\t3> Search for a student record from a course";
		cout << "\n\t\t\t4> Remove a student record from a course";
		cout << "\n\t\t\t5> Display course(s)";
		cout << "\n\t\t\t0> Return";
		cout << "\n\t\t" << string(70, char(196));

		switch (inputInteger("\n\t\t\tOption: ", 0, 5))
		{
			case 1: 
			{
				num_courses = inputInteger("\n\t\t\t1> Enter the number of courses: ", true);

				courses.clear();
				courses.reserve(num_courses);

				cout << "\n\t\t\t" << num_courses << " Course(s) has been created.\n";
			}
				break;

			case 2: 
			{
				if (num_courses == 0)
				{
					cout << "\n\t\t\tERROR: number of courses has not been assigned.\n";
					break;
				}

				for (int i = 0; i < num_courses; i++)
				{
					while (true)
					{
						file_name = inputString("\n\t\t\t2> Enter a data file name for course[" + to_string(i) + "] (STOP - return): ", false);

						if (toUpper(file_name) == "STOP")
						{
							break;
						}

						ifstream file;
						file.open(file_name);

						if (file.fail())
						{
							cout << "\n\t\t\tERROR: file, " + file_name + ", cannot be found. Please re-specify..\n";
							continue;
						}
						else
						{
							string course_name;

							getline(file, course_name);
							courses.push_back(Course(course_name));

							string id;
							string name;
							double score;

							while (!file.eof())
							{
								getline(file, id, ',');
								getline(file, name, ',');
								file >> score;

								// Clear the leading white-spaces
								string cleaned_name = removeLeadingTrailingSpaces(name);
								
								int ID = stoi(id);
								courses[i].addStudent(ID, cleaned_name, score);
							}

							break;
						}
					}

					cout << "\n\t\t\tData from file, " + file_name +", has been read and stored into Courses[" + to_string(i)+ "].\n";
				}

			}
				break;

			case 3:
			{
				if (num_courses == 0)
				{
					cout << "\n\t\t\tERROR: number of courses has not been assigned.\n";
					break;
				}

				if (courses.empty())
				{
					cout << "\n\t\tERROR: No data file has been read and stored into Courses.\n";
					break;
				}

				cout << "\n\n\t\t\t3> Search by";
				cout << "\n\t\t\t" << string(40, char(196));
				cout << "\n\t\t\t  1. ID Number";
				cout << "\n\t\t\t  2. Name";
				cout << "\n\t\t\t  0. return";
				cout << "\n\t\t\t" << string(40, char(196));
				switch (inputInteger("\n\t\t\tOption: ", 0, 2))
				{
					case 1:
					{
						// Search by Student ID
						int searchID = inputInteger("\n\t\tEnter the student ID to search: ");
						int index = 0;

						bool studentFound = false;

						for (int i = 0; i < courses.size(); i++)
						{
							if (courses[i].getStudentIDs().search(searchID))
							{
								studentFound = true;
								index = i;
							}
						}

						if (!studentFound) 
						{
							cout << "\n\t\tStudent with ID " << searchID << " not found in any course.\n";
						}
						else 
						{
							cout << "\n\t\tID: " << searchID << " has been found in Course : " << courses[index].getName() << "\n";
						}
					}
					break;

					case 2:
					{
						// Search by Student Name
						string searchName = inputString("\n\t\tEnter the student name to search: ", true);

						bool studentFound = false;
						int index = 0;

						for (int i = 0; i < courses.size(); i++)
						{
							if (courses[i].getStudentNames().search(searchName))
							{
								studentFound = true;
								index = i;
							}
						}

						if (!studentFound)
						{
							cout << "\n\t\tStudent with name " << searchName << " not found in any course.\n";
						}
						else
						{
							cout << "\n\t\tID: " << searchName << " has been found in Course : " << courses[index].getName() << "\n";
						}
					}
					break;

					case 0: return;
				}
	
			}
				break;

			case 4: break;

			case 5: 
			{
				if (num_courses == 0)
				{
					cout << "\n\t\t\tERROR: number of courses has not been assigned.\n";
					break;
				}

				if (courses.empty())
				{
					cout << "\n\t\tERROR: No data file has been read and stored into Courses.\n";
					break;
				}

				cout << "\n\n\t\tCourse(s)";
				cout << "\n\t\t" << string(70, char(196));
				cout << "\n\t\t1. Display individual course";
				cout << "\n\t\t2. Display all courses";
				cout << "\n\t\t0. return";
				cout << "\n\t\t" << string(70, char(196));
				
				switch (inputInteger("\n\t\tOption: ", 0, 2))
				{
					case 1: 
					{
						int size = courses.size() - 1;

						// Display individual course
						int courseIndex = inputInteger("\n\t\tEnter the index of the course to display: ", 0, size);
							
						if (courseIndex >= 0 && courseIndex < courses.size()) 
						{
							courses[courseIndex].displayCourse();
						}

						break;
					}
					case 2: 
					{
						for (size_t i = 0; i < courses.size(); i++)
						{
							courses[i].displayCourse();
							cout << endl;
						}
					}
						break;
				}
			}
				break;
		case 0: return;
		default: cout << "\t\tERROR - Invalid option."; break;
		}
		cout << "\n";
		system("pause");
	} while (true);

}