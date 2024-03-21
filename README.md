# Practical Work Repository for ALSDD Module (1CP)
# Solution to TP1: Listes Linéaires Chainées

## Overview
This solution addresses the requirements of Travaux Pratique N°1, focusing on the implementation of linear linked lists to manipulate English words. The TP spans over four weeks, emphasizing collaboration in pairs and adherence to coding standards and documentation.

## Project Structure
- **Project Name**: Nom1_Prenom1_Nom2_Prenom2_Groupe_TP1
- **Development Environment**: Code::Blocks
- **Submission Format**: Compressed folder containing the project
  - Non-compliance with the naming convention may lead to penalties.
- **Coding Standards**: Prioritize code quality, readability, and thorough commenting.

## Objective
The primary goal is to load English words from a provided file into a bidirectional linked list, organizing them by size and alphabetical order. Subsequently, various operations are performed on these words, including syllable decomposition, calculation of word properties (e.g., character count, consonants/vowels, syllable count), and identifying words formed by specific letter sequences.

## Implementation
### Data Structures
- **Syllable Structure**: Represents a syllable within a word.
- **Word Structure**: Stores word attributes and maintains links to related words based on specific characteristics.
- **Auxiliary Structures**: Support various linguistic analyses such as anagrams, lexically close words, word sequences, etc.

### Abstract Machine
- Modular implementation of functions to manipulate words and perform linguistic analyses.
- Integration of modification modules to update word attributes.

### Functionality
- Insertion and deletion of words.
- Menu-driven interface enabling separate execution of five manipulations and display of resulting lists.
- Statistical analysis functionality providing word count and sublist count for each question.

## Program Structure
- **Main Program**: Responsible for I/O and user interaction via a menu.
- **Library Module (.h)**: Contains word manipulation functions in C.

## Conclusion
This TP aims to create a C library facilitating word manipulation, with the main program handling user interaction. The provided solution ensures adherence to coding standards and comprehensive documentation, aiding in understanding and further development.
