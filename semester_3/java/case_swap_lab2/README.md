# case_swap_lab2

A Java console application for processing strings by changing the case of the first letter of each word in the input.

## Task

Develop a console application using the `Character`, `String`, and `StringBuffer`/`StringBuilder` classes. The program reads lines from the standard input until the end of the file using `Scanner` and writes the result to the standard output.

**Variant 21.** Each input line consists of words separated by one or more spaces and punctuation marks. For each input line, change the case of the first letter of every word to the opposite case: uppercase letters become lowercase and lowercase letters become uppercase.

## Example

Input:

```text
Привет, Мир! java Программирование.
HELLO world, JAVA is FUN.
````

Output:

```text
привет, мир! Java программирование.
hELLO World, jAVA Is fUN.
```

## How it works

The program processes the input line character by character and uses a flag to track the beginning of a new word after a space or punctuation mark.

For the first letter of each word, the program uses `Character.isUpperCase`, `Character.toUpperCase`, and `Character.toLowerCase` to change its case. Other characters are copied unchanged into a `StringBuilder`.
