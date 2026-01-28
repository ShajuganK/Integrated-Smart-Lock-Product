#  KnoxKey – Smart Door Lock with Knock & Keypad Authentication

##  Project Overview

**KnoxKey** is a **product-oriented smart door lock system** developed as an extension of the *Secret Door Lock with Knock Pattern Recognition* project during **Complementary Semester 2**. The system introduces a **dual-layer authentication mechanism** by combining **knock-pattern recognition** with **keypad-based password entry**, significantly enhancing security and usability for real-world applications.

Unlike the earlier prototype-focused implementation, this phase emphasized **complete product development**, including **schematic design, PCB layout, enclosure considerations, and hardware validation**, transforming the concept into a deployable embedded product.

---

##  Objectives

* Design a dual-authentication smart door lock system
* Integrate knock-based and keypad-based access control
* Develop a compact and reliable PCB-based hardware solution
* Implement user-configurable reset and reprogramming modes
* Ensure robustness against noise, false triggers, and misuse

---

##  System Working Principle

1. The system remains in a locked state by default
2. User authentication can be performed using:

   * **Knock Pattern Recognition**, or
   * **Keypad Password Entry**
3. Knock signals are captured via a piezoelectric sensor and filtered to suppress noise
4. Keypad inputs are scanned and validated by the microcontroller
5. The authentication logic verifies:

   * Timing pattern for knocks, or
   * Correct password sequence from keypad
6. Upon successful authentication:

   * The relay/solenoid lock is actuated to unlock the door
   * System status is displayed on the I2C LCD
7. A **reset/configuration mode** allows authorized users to update knock patterns and passwords

---

##  Key Features

* Dual authentication: knock pattern + keypad password
* User-configurable reset mode for knock pattern and password
* Piezoelectric knock sensing with noise filtering
* Custom-designed PCB for compact and reliable operation
* I2C-based 16×2 LCD for system status and user guidance
* Relay/solenoid-based electronic locking mechanism
* LED indicators for operational feedback
* Designed with scalability and product reliability in mind

---

##  Product Design & Development Approach

1. **System Architecture Design**

   * Defined authentication flow and system states
   * Designed modular firmware structure

2. **Schematic & PCB Design**

   * Developed schematics using EasyEDA
   * Designed a compact PCB optimized for reliability

3. **Firmware Development**

   * Implemented Embedded C firmware on ATmega328P
   * Integrated knock detection, keypad scanning, and control logic

4. **Simulation & Verification**

   * Validated circuit operation using Proteus
   * Verified logic and timing behavior

5. **Hardware Assembly & Testing**

   * Assembled PCB and integrated components
   * Tested locking mechanism and reset functionality

---

##  Technologies, Tools & Components

###  Hardware Components

| Category         | Description                         |
| ---------------- | ----------------------------------- |
| Microcontroller  | ATmega328P                          |
| Sensors & Inputs | Piezoelectric sensor, Matrix keypad |
| Display          | 16×2 LCD (I2C interface)            |
| Output Devices   | Relay / Solenoid lock, LEDs         |

###  Software & Firmware

| Category          | Description                  |
| ----------------- | ---------------------------- |
| Programming       | Embedded C                   |
| Development Style | Bare-metal embedded firmware |

###  Design & Simulation Tools

| Tool    | Purpose                           |
| ------- | --------------------------------- |
| EasyEDA | Schematic and PCB design          |
| Proteus | Circuit simulation and validation |

###  Interfaces

| Interface | Purpose                                     |
| --------- | ------------------------------------------- |
| I2C       | LCD communication                           |
| GPIO      | Sensor input, keypad scanning, lock control |

---

##  Academic Context

| Item         | Details                                           |
| ------------ | ------------------------------------------------- |
| Course       | Product Design Project (Complementary Semester 2) |
| Project Type | Hardware Product Development                      |
| Product Name | KnoxKey                                           |

---

##  Learning Outcomes

* End-to-end embedded product development experience
* Practical knowledge of PCB design and hardware integration
* Design of multi-input authentication systems
* Firmware structuring for real-world embedded products
* Understanding of product reliability and scalability considerations

---

##  Conclusion

KnoxKey represents a transition from **academic prototyping to product-level embedded system design**. By integrating dual authentication mechanisms with custom PCB development, the project demonstrates practical readiness for real-world smart lock and access control applications.

---

##  Author

**Shajugan Kulashankar**
Electrical & Electronics Engineering Undergraduate
University of Peradeniya, Sri Lanka

---

## Project mates
**Shadhurshan Navaratnam**
Electrical & Electronics Engineering Undergraduate
University of Peradeniya, Sri Lanka

**Sharukshan Niranjan**
Electrical & Electronics Engineering Undergraduate
University of Peradeniya, Sri Lanka

---

##  Supervisors

**Dr. Isuru Dasanayake**
Senior Lecturer, Department of Electrical & Electronic Engineering
University of Peradeniya, Sri Lanka

* B.Sc.Eng. Electrical and Electronic Engineering, University of Peradeniya, Sri Lanka. 2006
* M.S. Systems Science and Mathematics, Washington University in St. Louis, St. Louis, MO. 2009
* Ph.D. Electrical Engineering, Washington University in St. Louis, St. Louis, MO. 2013
* Email: [isuru.dasanayake@eng.pdn.ac.lk](mailto:isuru.dasanayake@eng.pdn.ac.lk)

**Dr. Sudheera Navaratne**
Senior Lecturer, Department of Electrical & Electronic Engineering
University of Peradeniya, Sri Lanka

* B.Sc. (Engineering) in Electrical and Electronic Engineering, University of Peradeniya, Sri Lanka (August 2007) - First class Honor
* M.Sc. in Electrical and Computer Engineering Technology, Purdue University, USA (Fall 2012)
* Ph.D. in Electrical and Computer Engineering Technology, Purdue University, USA (Spring 2013 –Fall 2016)
* Email: [sudheera@eng.pdn.ac.lk](mailto:sudheera@eng.pdn.ac.lk)

---

##  License

This project is developed **strictly for academic and educational purposes** at the **University of Peradeniya, Sri Lanka**.
Unauthorized commercial use or reproduction without proper acknowledgment is not permitted.

---



