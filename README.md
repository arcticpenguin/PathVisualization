# Path Visualization

This is a tool developed for visualizing the paths which the users traveled through in virtual environments. 
It can read the specified log data files generated from VR programs and produce the path visualization for one or more trials.

## Dev Tools/Env
- C++
- SFML
- TGUI
- Visual Studio 2013

## Data
- Data file title: e.g., "... Subject0 Condition1 1 Trial1 0 2015_4_16 11_3_34"
  - `Subject[#]`: Subject number 0, 1, 2, ...
  - `Condition[#1] [#2]`: 
    - [#1] Condition sequence [1, 8]: The order of the condition that occurred in the experiment.
    - [#2] Condition index [1, 8]: The index of the condition. 
      - See table 2 in the [paper](http://www.mifeng.name/assets/projects/hapticchairio/feng2016initial.pdf).
      - 0 - NONE, 1 - MW, TBD.

## Future Goals
- Web-platform
