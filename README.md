# Cafe simulation tool

Provides performing simulation run for given amount of cycles, as well as modifying available menu, employees and tables.

## General information

The program can launch in one of two modes: **simulation mode** and **administrator mode**.

- **Simulation mode** performs a simulation for the given amount of cycles (including available personalization options), prints the log and writes it into the given file.
- **Administrator mode** opens interactive menu, which gives the ability to modify cafe information, such as menu, employees and tables.

## Usage

In order to open the program in **simulation mode**, run:

`Cafe.exe -s [cycles amount] [delay between printing logs in seconds] [customers appearance freuency] [output filename] [menu input file] [employees input file] [tables input file]`

Input files are always stored inside textFiles folder. In order to load them, you simply have to type its name without including folder name.

In order to run the program in **administrator mode**, run:

`Cafe.exe -a [menu file] [employees file] [tables file]`

In this case, all modifications which are made in administrator mode are written into input files.