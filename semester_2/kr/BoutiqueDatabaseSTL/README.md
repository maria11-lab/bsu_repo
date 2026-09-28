# Boutique Database

### Test 1 - STL (var 3)

A C++ application for processing information about boutiques, cities,
and their opening years using STL containers.

The program loads data from a file and processes queries related to
boutiques and cities.

## Features

- Find a boutique by name and display its city and opening year.
- Count the number of boutiques opened in a specified city.
- Find unique `<city, opening year>` pairs.
- Process input data and queries from text files.
- Handle case-insensitive searches.

## Data Structures

The application uses C++ STL containers:

- `map` — groups boutiques by opening year;
- `vector` — stores boutiques and cities for each year;
- `pair` — represents a city and boutique;
- `set` — stores unique city-year pairs.

## Technologies

- C++
- STL
- File I/O