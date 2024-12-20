# Veterinary-Appointment-Management-System
My final project for the IPC144 course. It is a C project for veterinary appointment management.

Overview
This project is a C-based application for managing veterinary appointments and patient records. It allows staff to handle pet owner information, schedule appointments, and organize clinic operations efficiently. The application demonstrates robust file handling, user interface design, and structured data management using arrays and structs.

Features
- Patient Management:
  Add, edit, and remove patient records.
  Search patients by ID or phone number.
  Display patient details in form or table format.
- Appointment Management:
  Schedule new appointments for patients.
  View all appointments or filter by specific dates.
  Remove canceled appointments.
- File Handling:
  Import patient and appointment data from external files.
  Save patient and appointment data for persistent storage.
- User-Friendly Menus:
  Intuitive menus for managing patients and appointments.

How It Works
- Patient Records:
Patient records include an ID, name, and phone information.
- Appointments:
Appointments are organized by date and time, with availability based on a 30-minute interval.
- File Integration:
Data is imported from files (patientData.txt, appointmentData.txt) at startup and saved after updates.
- Key Concepts Practiced
  Structured Data: Implementing structs for Patient, Appointment, Date, and Time management.
  File I/O: Reading from and writing to files to persist data.
  Modular Programming: Organizing code into headers (clinic.h, core.h) and separating functionality into modules.
  Dynamic Menus: Interactive user-driven menus for data manipulation.

Project Structure
- Headers:
  clinic.h: Defines core structures and functions for managing appointments and patient records.
  core.h: Utility functions for user input and interface handling.
- Source File:
  a1ms3.c: The main entry point for the application.
