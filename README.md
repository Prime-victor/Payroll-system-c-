# Payroll System in -C-

## Overview
This payroll system is a command-line application written in C that allows for managing employee records, calculating payroll, and generating reports. It uses file handling to store data persistently in a binary file, making it a lightweight and efficient system for small-scale use.

---

## Features
1. **Add Employee**
   - Input details such as Employee ID, Name, Basic Salary, Overtime Hours, and Leaves.
   - Employee records are stored in a binary file (`employees.dat`).

2. **Display Employees**
   - View all employee records in a tabular format.
   - Displays details such as Employee ID, Name, Basic Salary, Overtime Hours, and Leaves.

3. **Process Payroll**
   - Calculates payroll for each employee:
     - **Gross Salary** = Basic Salary + (Overtime Hours × $50/hour).
     - **Deductions** = Leaves × (Basic Salary / 30).
     - **Net Salary** = Gross Salary – Deductions.
   - Updates deductions directly in the file.

4. **Generate Report**
   - Displays the Net Salary for all employees in a concise report format.

5. **Persistent Storage**
   - All employee data is stored in a binary file, ensuring data is retained even after the program exits.

---

## How to Use
### Compilation
1. Save the program code in a file, e.g., `payroll_system.c`.
2. Compile the program using the GCC compiler:
   ```bash
   gcc payroll_system.c -o payroll_system
   ```

### Running the Program
1. Run the compiled program:
   ```bash
   ./payroll_system
   ```
2. Follow the on-screen menu to navigate through the system:
   - Add new employees.
   - Display the list of employees.
   - Process payroll calculations.
   - Generate payroll reports.

---

## File Structure
- **employees.dat**: A binary file that stores all employee records.
  - Each record contains:
    - Employee ID
    - Name
    - Basic Salary
    - Overtime Hours
    - Number of Leaves
    - Deductions

---

## Code Highlights
### Key Functions
1. **File Handling**:
   - Uses `fwrite` and `fread` for efficient binary file operations.
   - Ensures data persistence for employee records.

2. **Payroll Calculations**:
   - Dynamically calculates Gross Salary, Deductions, and Net Salary based on employee data.

3. **Command-Line Interface (CLI)**:
   - Interactive menu-driven UI for ease of use.

### Utility Functions
- `pauseScreen`: Pauses the program until the user presses Enter.
- `clearScreen`: Clears the terminal for better readability.
- `employeeExists`: Checks for duplicate Employee IDs to avoid conflicts.

---

## Example Usage
### Adding an Employee
- Input:
  ```
  Enter Employee ID: 101
  Enter Employee Name: John Doe
  Enter Basic Salary: 5000
  Enter Overtime Hours: 10
  Enter Number of Leaves: 2
  ```
- Output:
  ```
  Employee added successfully!
  ```

### Processing Payroll
- Output:
  ```
  ID: 101 | Name: John Doe
  Gross Salary: 5500.00 | Deductions: 333.33 | Net Salary: 5166.67
  ```

---

## Limitations
- The system does not support advanced taxation rules or multi-tier salary structures.
- No role-based access; all users can perform all actions.
- Designed for single-user access.

---

## Future Enhancements
- Add support for:
  - Taxation and benefits.
  - Role-based access control (e.g., Admin, HR).
  - Exporting reports to text or CSV files.
  
---

## Contact
For questions or feedback, reach out to me.

