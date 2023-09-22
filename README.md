# Cafe simulation tool

The following project is a command line tool which simulates a system capable of maintaining an example cafe enterprise. Performs simulation run for a given amount of time cycles, as well as modifies available menu, available employees and tables. 

**This is a university project**, which goal was to address the most common issues appearing in object-oriented programming.

## General information

The program can launch in one of two modes: **simulation mode** and **administration mode**.

- **Simulation mode** performs a simulation for a given amount of cycles (including available personalization options), prints the log and writes it into the given file.
- **Administration mode** opens interactive menu, which gives the ability to modify cafe information, such as menu, available employees and tables.

## Usage

In order to open the program in the **simulation mode**, run:

`Cafe.exe -s [cycles amount] [delay between printing logs in seconds] [customers appearance freuency] [output file name] [menu input file] [employees input file] [tables input file]`

Input files are always stored inside `textFiles` folder. In order to load them, you simply have to type its name without including the folder name.

In order to run the program in the **administration mode**, run:

`Cafe.exe -a [menu file] [employees file] [tables file]`

In this case, all modifications which are made in administration mode are written into input files.