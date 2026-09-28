# Finance Directory

### Test 1 - STL (var 12)

A C++ application for storing and processing financial activity records.

Each record contains an activity type, starting amount, percentage, and service
cost. The application loads records from a file and provides several operations
for searching, sorting, adding, and saving data.

## Features

- Load financial activity records from a file.
- Find records by percentage.
- Search activities by type prefix.
- Find activities by type and sort them by starting amount and percentage.
- Display records grouped by activity type.
- Add new financial activity records.
- Save processed data to a file.
- Handle invalid input records.

## Data Structures

The application uses C++ STL containers:

- `map` — groups activities by type;
- `multimap` — indexes activities by percentage;
- `vector` — stores activities within each type;
- `algorithm` — used for sorting;
- `string` and `fstream` — used for data processing and file I/O.

## Technologies

- C++
- STL
- File I/O