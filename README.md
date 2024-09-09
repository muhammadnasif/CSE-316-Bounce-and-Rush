# Bounce and Rush

## Project Overview
Bounce and Rush is a microcontroller-based game inspired by Google Chrome's offline Dinosaur game. It was developed as part of the CSE 316 (Microprocessors, Microcontrollers, and Embedded Systems Sessional) course.

### Key Details
- **Course:** CSE 316
- **Supervisor:** Dr. Atif Hasan Rahman
- **Section:** B2
- **Department:** CSE
- **Date of Submission:** July 30, 2021

## Game Description
This single-player game guides the player through a side-scrolling landscape, avoiding obstacles to achieve a higher score. The game's difficulty increases as the score goes up.

## Components Used
- ATMEGA32 Microcontroller
- 2-4 Decoder (74HC139)
- 4-16 Decoder (74HC154)
- 2x16 LCD Module (LM016L)
- 6x 8x8 LED Matrix
- Resistors (300 ohm)
- SPST Push Buttons

## Features
- Player and obstacles displayed on 6 8x8 LED Matrices
- Score display on LCD
- Two-button control system: jump and restart
- Increasing difficulty with score progression

## Working Principle
The game utilizes an ATMEGA32 microcontroller to interact with other hardware components. The player and obstacles are displayed on the LED matrices, while the score is shown on the LCD. The game continues until the player collides with an obstacle, at which point it can be restarted.

## Circuit Design
The project involves a complex circuit design, including:
- ATMEGA32 connections
- Decoder connections for LED matrix control
- LCD integration

## Challenges Overcome
1. Handling multiple LED matrices for smooth object movement
2. Optimizing delays for fluid gameplay while integrating the LCD
3. Implementing collision detection
4. Efficient use of decoders for LED matrix control


## Contributors
- Student ID: 1705109
- Student ID: 1705111

## Acknowledgements
Special thanks to Dr. Atif Hasan Rahman for supervising this project.

---

For more detailed information, please refer to the full project report.
