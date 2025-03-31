# M-ary Search Algorithm

## Project Overview
This project implements an M-ary search algorithm, a generalized version of binary search that divides the sorted list into m approximately equal parts and continues searching in one of these parts. The process repeats until the key is found or determined to be absent.

## Technologies Used
- **Backend:** C

## Features
- Input of a Sorted Key Sequence (K)
  - The user can enter an ordered sequence of integer keys from a file or standard input.
- Generation of a Sorted Key Sequence (K)
  - The program can generate a sorted list of k random integer keys within a specified range.
- Search for a Key in the Sequence (K) Using M-ary Search
  - The user provides a key and an m value, and the program performs an M-ary search.
- Optimized Search for Multiple Keys (P) in K Using M-ary Search
  - The user inputs a sorted sequence P of p keys, and the program searches for each key in K.
- Performance Evaluation of M-ary Search for Single Keys
  - The program generates a sequence of keys within a given range and calculates the average number of steps needed for searching.
  - Evaluation is performed for m values in the range [2-6].
- Performance Evaluation of Optimized M-ary Search for Multiple Keys
  - Similar to the previous evaluation, but for multiple keys instead of single key searches.

## Performance Analysis
The program evaluates the performance of M-ary search by measuring the average number of search steps for different values of m. Results are displayed for m values from 2 to 6.
