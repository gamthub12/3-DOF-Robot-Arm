# 3-DOF Robot Arm

This project implements a 3-DOF robotic arm using 3 RC servos for the joints and 1 servo for the gripper. The system is controlled via an Arduino firmware and a Qt-based desktop application.

## Features
- **Arduino Firmware**: Handles servo control and communication with the desktop application.
- **Qt Application**: Provides a graphical interface for controlling the robotic arm, including:
  - Manual control of each joint and the gripper.
  - Automatic movement through predefined points.
  - Real-time display of joint angles and end-effector coordinates.
- **COM Port Communication**: Connects to the Arduino via a serial COM port.

## Requirements
- **Hardware**:
  - Arduino board.
  - 3 RC servos for the joints.
  - 1 RC servo for the gripper.
- **Software**:
  - Qt Creator with the `QSerialPort` module installed.
  - Arduino IDE for uploading the firmware.

## Setup Instructions
1. **Hardware Setup**:
   - Connect the servos to the Arduino as specified in the firmware code.
   - Connect the Arduino to your computer via a USB cable.

2. **Firmware Upload**:
   - Open the `Code Arduino/code_servo.ino` file in the Arduino IDE.
   - Select the correct board and COM port.
   - Upload the firmware to the Arduino.

3. **Qt Application**:
   - Open the `Code Qt/CanhTayRobot.pro` file in Qt Creator.
   - Build and run the project.
   - Ensure the `QSerialPort` module is installed in your Qt environment.

4. **Running the Application**:
   - Launch the Qt application.
   - Select the appropriate COM port for the Arduino.
   - Click "Kết Nối" to connect to the robotic arm.
   - Use the interface to control the arm manually or execute automated movements.

## Usage
- **Manual Control**:
  - Use the buttons to move each joint (J1, J2, J3) and the gripper.
  - Adjust the speed using the slider.
- **Automatic Control**:
  - Add points to the movement sequence using the "Thêm" button.
  - Start the automatic sequence with the "Bắt Đầu" button.
  - Clear the sequence with the "Xóa" button.
- **Home Position**:
  - Return the arm to its home position using the "Home" button.

## Notes
- Ensure the Arduino is connected to the correct COM port before starting the application.
- The application requires the `QSerialPort` module to communicate with the Arduino.

## Screenshot
![Robot Arm Interface](https://github.com/user-attachments/assets/9bfe18c6-e4e7-4c41-a0a0-ba9893df9c9d)

## License
tranthien22203@gmail.com