# Test 1 - STL 

## Task

Develop a C++ application for processing hotel information stored in text
files using STL containers.

The input data describes hotels located in different cities and their
star ratings. The program loads the data into an associative container
and processes queries from a separate input file.

## Description

The program supports the following queries:

- Find all hotels located in a specified city and display their star ratings.
- Determine the number of cities containing a specified hotel.
- Find all unique `city — star rating` pairs.

The application reads data from `DATA.TXT` and processes queries from
`QUERY.TXT`. It also handles missing or empty input files.

## Data Structures

The solution uses C++ STL containers:

- `map` — stores cities and their hotels;
- `vector` — stores hotels and their star ratings;
- `pair` — represents a hotel and its star rating;
- `set` — stores unique city and star-rating pairs.

## Technologies

- C++
- STL
- File I/O

