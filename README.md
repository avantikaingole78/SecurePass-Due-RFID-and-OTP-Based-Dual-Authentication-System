# SecurePass Duo: RFID and OTP-Based Dual Authentication System

## 📌 Project Overview

**SecurePass Duo** is a dual-authentication-based access control system that combines **RFID card authentication** with **One-Time Password (OTP) verification** to provide an additional layer of security.

The system is developed using the **LPC2148 ARM7 microcontroller**. When a valid RFID card is detected, the system generates an OTP and sends it to the user's registered mobile number through a **GSM M660A module**. The user must enter the received OTP through a 4×4 matrix keypad within a specified time. Only after successful verification is access granted.

The project demonstrates practical implementation of **Embedded C, ARM7 microcontroller, UART communication, RFID, GSM, LCD, keypad.

## 🎯 Objective

The main objective is to develop a secure access-control system using two authentication factors:

1. **RFID Card** – Identifies the authorized user.
2. **OTP** – Provides a time-limited second level of authentication.

This approach reduces the risk of unauthorized access associated with single-factor authentication.

## 🛠️ Hardware Requirements

* LPC2148 ARM7 Microcontroller
* GSM Module (M660A)
* RFID Reader
* RFID Cards
* 16×2 LCD
* 4×4 Matrix Keypad
* RTC (on-chip)
* Switch
* LED/Bulb/DC Motor with L293D circuit

The above hardware components are specified in the project documentation.

## 💻 Software Requirements

* Embedded C
* Keil C Compiler
* Flash Magic

🔄 System Working

The system follows the following sequence:

              START
                |
                v
        Wait for RFID Card
                |
                v
        Read RFID Card Number
                |
                v
        Is Card Valid?
          /            \
        NO              YES
        |                |
        |                v
        |          Generate OTP
        |                |
        |                v
        |       Send OTP through GSM
        |                |
        |                v
        |        Store OTP Time
        |          using RTC
        |                |
        |                v
        |       Enter OTP using
        |          Keypad
        |                |
        |                v
        |       Is OTP Correct
        |        and Within Time?
        |          /          \
       NO            YES
       |              |
       v              v
 Authentication    Authentication
    Failed             Success
       |                |
       v                v
   Wait for RFID    Access Security
       Card             Device

The application initially waits for an RFID card. For a valid card, an OTP is generated and sent to the registered mobile number. The OTP entry is time-limited using RTC information. Incorrect or expired OTP authentication terminates the authentication attempt, while a correct OTP grants access.

## 📡 Communication

### UART

UART communication is used for interfacing the RFID reader and GSM module with the LPC2148. The project documentation specifically specifies **UART1 interrupt** for reading the RFID card number and **UART interrupts** for GSM interfacing.

### GSM

The GSM module is used to send the generated OTP to the user's registered mobile number. GSM communication is performed using AT commands and UART interrupts.

## 🔐 Authentication Process

### Step 1 — RFID Authentication

The user places an RFID card near the RFID reader. The reader transmits the card number to the LPC2148.

### Step 2 — Card Verification

The microcontroller compares the received card information with the valid RFID card information stored in program memory.

### Step 3 — OTP Generation

If the RFID card is valid, the system generates an OTP.

### Step 4 — OTP Transmission

The generated OTP is sent to the user's registered mobile number through the GSM module.

### Step 5 — OTP Entry

The user enters the received OTP using the 4×4 matrix keypad.

### Step 6 — Time Verification

The system checks whether the OTP is entered within the specified time using the RTC.

### Step 7 — Access Control

* **Correct OTP + within time → Access Granted**
* **Wrong OTP → Access Denied**
* **OTP entered after the allowed time → Access Denied**

## 📟 RFID Data

The RFID reader sends **10 bytes of data** when a card is placed near the reader.

For example, for card number `12345678`, the reader output is:

02 31 32 33 34 35 36 37 38 03

The project documentation specifies this RFID data format.

## 🧩 Main Modules

* RFID Reader Interface
* RFID Card Verification
* UART Communication
* GSM Module Interface
* OTP Generation
* OTP Verification
* 4×4 Keypad Interface
* 16×2 LCD Interfac
* Access Control

## 📂 Suggested Project Structure

SecurePass-Duo/
│
├── projectmain.c
├── lcd.c
├── lcd.h
├── delay.c
├── delay.h
├── uart.c
├── uart.h
├── keypad.c
├── keypad.h
├── i2c.c
├── i2c.h
├── README.md
│
└── Documentation/
    └── SecurePass-Duo-Project.pdf

The project documentation also describes separate source/header files for LCD, delay, UART, keypad, and I2C modules.

## ⭐ Key Features

* Dual-factor authentication
* RFID-based user identification
* OTP-based second-level verification
* GSM-based OTP transmission
* RTC-based OTP time validation
* Keypad-based OTP entry
* LCD-based user interface
* UART interrupt-based communication
* Automatic access control

## 🎓 Technologies Used

| Category           | Technology        |
| ------------------ | ----------------- |
| Microcontroller    | LPC2148 ARM7      |
| Programming        | Embedded C        |
| RFID Communication | UART              |
| GSM Communication  | UART              |
| Display            | 16×2 LCD          |
| Input              | 4×4 Matrix Keypad |
| Time Management    | On-chip RTC       |
| GSM Module         | M660A             |
| IDE/Compiler       | Keil C            |
| Programming Tool   | Flash Magic       |

## 🚀 Applications

The concept can be applied to:

* Secure door access systems
* Office access control
* Restricted-area authentication
* Laboratory access
* Industrial security systems
* Electronic security systems

## 👩‍💻 Project Highlights

**Project Name:** SecurePass Duo: RFID and OTP-Based Dual Authentication System

**Controller:** LPC2148 ARM7

**Programming Language:** Embedded C

**Key Protocol:** UART

**Authentication:** RFID + OTP

**My Contribution:** Embedded C programming, peripheral interfacing, UART communication, RFID data handling, GSM communication, OTP verification, and access-control logic.

## 📚 Learning Outcomes

Through this project, I gained practical experience in:

* LPC2148 ARM7 microcontroller programming
* Embedded C programming
* UART communication
* RFID interfacing
* GSM module interfacing
* LCD and keypad interfacing
* Authentication logic

