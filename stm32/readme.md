This folder contains STM32 projects.
- The "default_ws" folder is a workspace for the STM32CubeIDE. It contains a single
  project named "default". This contains the default firmware for the STM32F030


## Modify STM32 project ##
To modify, build and program a STM32 project:
- Download and install the [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).
- Start STM32CubeIDE, and select the "default_ws" folder as the workspace
- Select "File"->"Import" from the menu, and select "Existing project into workspace"
- Select the "default" project. In "Options" ensure "Copy project into workspace" is NOT selected
- Import project

This will import the "default" project into the workspace. It should now be possible to build the project, and program the STM32F030.

