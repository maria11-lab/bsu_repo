# Student Grades Database

### Test 1 - STL (var 1)

A C++ application for processing student grades using STL containers.

The program stores information about subjects, students, and their grades,
then processes queries from an input file.

## Features

- Find excellent students for a specified subject.
- Calculate the average grade of a specified student.
- Find unique `<grade, subject>` pairs.
- Read and process data from `DATA.TXT` and queries from `QUERY.TXT`.
- Handle invalid or empty input files.

## Data Structures

The application uses C++ STL containers:

- `map` — stores subjects and their students;
- `deque` — stores students and their grades;
- `vector` — stores grades for calculating averages;
- `set` — stores unique grade-subject pairs;
- `pair` — represents related data elements.

## Technologies

- C++
- STL
- File I/O