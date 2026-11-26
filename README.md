# CO3009: Microprocessors - Microcontrollers Course Project
## Two-Road Traffic Light System on XNUCLEO-F103RB

**University:** Ho Chi Minh City University of Technology (HCMUT - VNU-HCM)  
**Academic Year:** Semester 261 (2026 - 2027)

### Team Members
| No. | Full Name | Student ID |
|:---:|:---|:---:|
| 1 | Nguyễn Trọng Hiếu | 2452333 |
| 2 | Huỳnh Trí Đức | 2452269 |
| 3 | Nguyễn Lê Nhật Huy | 2452394 |

## 1. Project Description

This project implements a two-road traffic light control system using the **XNUCLEO-F103RB** development board with the STM32F103RB microcontroller.

The system simulates a traffic intersection consisting of two roads, where each road is controlled by an independent traffic light. The system supports three operating modes, allowing automatic traffic management, manual control, and adjustment of traffic-light durations.

The system provides three operating modes:

- **Automatic Mode:** Controls the traffic lights using a predefined sequence. The two roads take turns having the right of way through Red, Green, and Amber phases. The system automatically switches between traffic-light states according to their configured durations.

- **Manual Mode:** Allows users to manually change between four predefined traffic-light combinations using a push button. This mode provides direct control over the traffic lights without following the automatic timing sequence.

- **Timing Adjustment Mode:** Allows users to select and adjust the Red, Amber, and Green durations using push buttons. The system maintains the relationship `Red = Amber + Green` when the timing values are saved.

The project also includes the following features:

- **Cooperative Scheduler:** Manages and executes multiple application tasks, allowing different system functions to run periodically without relying on a blocking execution flow.

- **Software Timers:** Provide timing mechanisms for traffic-light transitions, periodic tasks, and other time-dependent operations.

- **Button Handling:** Implements software-based button debouncing, single-press detection, and long-press detection to ensure reliable user input.

- **DHT20 Sensor:** Measures environmental temperature and humidity and provides the readings to the application.

- **I2C LCD:** Displays the current operating mode, traffic-light states, countdown values, temperature, and humidity.

## 2. Hardware Requirements

The following hardware components are used in this project:

| Component           | Description                |
| ------------------- | -------------------------- |
| Development board   | XNUCLEO-F103RB             |
| Microcontroller     | STM32F103RB                |
| Traffic lights      | Two traffic-light modules  |
| Push buttons        | Four external push buttons |
| Environment sensor  | DHT20                      |
| Display             | I2C LCD                    |
| On-board button     | USER button (B1)           |
| On-board LED        | LD2                        |

## 3. Folder Structure

The repository is organized as follows:

```text
CO3009_2452333_2452269_2452394/
│
├── CO3009_TrafficLight/
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── button.h
│   │   │   ├── dht20.h
│   │   │   ├── fsm_automatic.h
│   │   │   ├── fsm_manual.h
│   │   │   ├── fsm_tuning.h
│   │   │   ├── global.h
│   │   │   ├── lcd.h
│   │   │   ├── main.h
│   │   │   ├── scheduler.h
│   │   │   ├── software_timer.h
│   │   │   └── traffic_light.h
│   │   │
│   │   ├── Src/
│   │   │   ├── button.c
│   │   │   ├── dht20.c
│   │   │   ├── fsm_automatic.c
│   │   │   ├── fsm_manual.c
│   │   │   ├── fsm_tuning.c
│   │   │   ├── global.c
│   │   │   ├── lcd.c
│   │   │   ├── main.c
│   │   │   ├── scheduler.c
│   │   │   ├── software_timer.c
│   │   │   └── traffic_light.c
│   │   │
│   │   └── Startup/
│   │
│   ├── Drivers/
│   │   ├── CMSIS/
│   │   └── STM32F1xx_HAL_Driver/
│   │
│   ├── .settings/
│   ├── .cproject
│   ├── .mxproject
│   ├── .project
│   ├── CO3009_TrafficLight.ioc
│   └── STM32F103RBTX_FLASH.ld
│
└── README.md
```

### Main Source Files

The main application is implemented in the `Core` directory, which contains the header files and source files responsible for different system functionalities.

| File               | Description |
| ------------------ | ------------------------------------------------------------------------- |
| `main.c`           | Initializes the microcontroller peripherals and scheduler, then registers the system tasks. |
| `scheduler.c`      | Implements task management, scheduling, updating, and dispatching. |
| `software_timer.c` | Provides software timers used by the application. |
| `button.c`         | Handles button reading, debouncing, single-press detection, and long-press detection. |
| `traffic_light.c`  | Controls the traffic-light modules and their corresponding LED states. |
| `fsm_automatic.c` | Implements the Automatic Mode state machine and predefined traffic-light sequence. |
| `fsm_manual.c`    | Implements the Manual Mode state machine and manual traffic-light combinations. |
| `fsm_tuning.c`    | Implements the Timing Adjustment Mode and duration configuration. |
| `global.c`         | Defines shared variables and global application states. |
| `dht20.c`          | Handles communication with the DHT20 temperature and humidity sensor. |
| `lcd.c`            | Handles LCD initialization, communication, and display updates. |

### Project Configuration and Drivers

- **`Drivers/CMSIS/`:** Contains the CMSIS files required for the ARM Cortex-M processor and STM32 microcontroller.
- **`Drivers/STM32F1xx_HAL_Driver/`:** Contains the STM32 Hardware Abstraction Layer (HAL) drivers used to access the microcontroller peripherals.
- **`CO3009_TrafficLight.ioc`:** STM32CubeMX configuration file containing the project's peripheral and pin configuration.
- **`STM32F103RBTX_FLASH.ld`:** Linker script defining the memory layout used when building the firmware.

## 4. Build and Flash

### 4.1 Software Requirements

The following software and hardware are required to build and run the project:

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- STM32CubeProgrammer or the ST-LINK software components installed with STM32CubeIDE.
- USB connection to the XNUCLEO-F103RB development board.
- ST-LINK debugger/programmer (integrated into the development board).

### 4.2 Clone the Repository

Open a terminal and run the following command:

```bash
git clone https://github.com/jynnguyen/CO3009_2452333_2452269_2452394.git
```

Navigate to the cloned repository:

```bash
cd CO3009_2452333_2452269_2452394
```

### 4.3 Open the Project in STM32CubeIDE

1. Launch **STM32CubeIDE**.
2. Select **File → Open Projects from File System**.
3. Click **Directory** and select the `CO3009_TrafficLight` folder inside the cloned repository.
4. Click **Finish** to import the project.
5. Wait for STM32CubeIDE to finish indexing and loading the project.
6. Make sure the project appears in the Project Explorer.

### 4.4 Build the Project

1. Select the `CO3009_TrafficLight` project in Project Explorer.
2. Select **Project → Build Project**, or press `Ctrl + B`.
3. Wait for the compilation process to finish.
4. Check the Console and Problems views for compilation errors.
5. If the build completes successfully, the generated firmware files will be available in the project's build output directory.

### 4.5 Flash the Firmware

1. Connect the XNUCLEO-F103RB board to the computer using its ST-LINK USB connection.
2. Make sure the board is powered on and detected by STM32CubeIDE.
3. Select the `CO3009_TrafficLight` project.
4. Click **Run → Run** to build and flash the firmware.
5. If prompted, select the ST-LINK debug probe.
6. Wait for the programming process to complete.
7. After programming finishes, the application should start running on the board.

## 5. How to Operate the System

After the firmware is successfully flashed, the system starts in **Automatic Mode**.

Users can interact with the system through four external push buttons and the on-board USER button (B1).

### 5.1 Button Functions

The following table summarizes the functions of each button in the three operating modes:

| Button     | Automatic Mode         | Manual Mode                                 | Timing Adjustment Mode           |
| ---------- | ---------------------- | ------------------------------------------- | -------------------------------- |
| BTN1 (D7)  | Switch to Manual Mode  | Switch to Timing Adjustment Mode            | Return to Automatic Mode         |
| BTN2 (D8)  | No operation           | Move to the next traffic-light combination | Select Red, Amber, or Green       |
| BTN3 (D9)  | No operation           | No operation                                | Increase the selected duration   |
| BTN4 (D10) | No operation           | No operation                                | Decrease the selected duration   |
| USER (B1)  | No operation           | No operation                                | Save the adjusted timing values  |

### 5.2 Automatic Mode

Automatic Mode is the default operating mode when the system starts.

- The two roads follow a predefined traffic-light sequence.
- Each road takes turns having the right of way.
- The traffic lights automatically transition between Red, Green, and Amber according to the configured durations.
- The LCD displays the current operating mode, traffic-light states, and countdown values.
- Temperature and humidity readings from the DHT20 sensor are also displayed.
- No button operation is required during normal operation.

Press **BTN1 (D7)** to switch from Automatic Mode to Manual Mode.

### 5.3 Manual Mode

Manual Mode allows users to control the traffic lights by selecting one of four predefined combinations.

1. Press **BTN1 (D7)** while in Automatic Mode to enter Manual Mode.
2. Press **BTN2 (D8)** to move to the next traffic-light combination.
3. The system cycles through the following combinations:

   | Combination | Road 1 | Road 2 |
   |:-----------:|:------:|:------:|
   | 1           | Red    | Green  |
   | 2           | Red    | Amber  |
   | 3           | Green  | Red    |
   | 4           | Amber  | Red    |

4. After the fourth combination, pressing BTN2 again returns to the first combination.
5. Press **BTN1 (D7)** again to enter Timing Adjustment Mode.

### 5.4 Timing Adjustment Mode

Timing Adjustment Mode allows users to configure the durations of the Red, Amber, and Green traffic-light phases.

The adjustment process is performed using BTN2, BTN3, and BTN4, while the USER button (B1) is used to save the configured values.

1. Press **BTN1 (D7)** from Manual Mode to enter Timing Adjustment Mode.
2. Press **BTN2 (D8)** to select the duration to adjust. The selection follows this order:

   `Red → Amber → Green → Red`

3. Press **BTN3 (D9)** to increase the selected duration.
4. Press **BTN4 (D10)** to decrease the selected duration.
5. Holding BTN3 or BTN4 changes the selected value repeatedly.
6. Press the **USER button (B1)** to save the adjusted timing values.

When the values are saved, the system synchronizes the timing values to maintain the following relationship:

`Red = Amber + Green`

7. Press **BTN1 (D7)** to return to Automatic Mode.

**Note:** Changes made in Timing Adjustment Mode are temporary until the USER button is pressed. Leaving the mode without saving does not apply those temporary changes.

## 6. Display Information

The I2C LCD provides information about the system while it is running.

The displayed information includes:

- **Operating Mode:** Indicates whether the system is currently in Automatic Mode, Manual Mode, or Timing Adjustment Mode.
- **Traffic-Light States:** Shows the current Red, Green, and Amber states of the two roads.
- **Countdown Values:** Displays the remaining time for the current traffic-light phases.
- **Temperature:** Displays the temperature measured by the DHT20 sensor in degrees Celsius (°C).
- **Humidity:** Displays the humidity measured by the DHT20 sensor as a percentage (%).

The LCD is refreshed periodically to keep the displayed information updated, while the DHT20 measurement task runs in the background.

## 7. Repository and Demonstration

**GitHub Repository:** [CO3009_2452333_2452269_2452394](https://github.com/jynnguyen/CO3009_2452333_2452269_2452394)

**Demo Video:** [Watch the Project Demonstration](https://drive.google.com/file/d/1pLs2iafUXlqeuN1k_tuZhojt-0vvnFrA/view)

---

**CO3009 – Microprocessors and Microcontrollers**  
Ho Chi Minh City University of Technology (HCMUT - VNU-HCM)  
Academic Year 2026 - 2027
