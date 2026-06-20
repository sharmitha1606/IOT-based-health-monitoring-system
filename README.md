# IOT-based-health-monitoring-system
Real-time IoT healthcare monitoring solution using ESP32, ECG, SpO₂, heart rate, and temperature sensors with cloud-based remote monitoring and emergency alert features.

Cloud-Integrated IoT Based Health Monitoring System

Overview

This project presents a cloud-enabled IoT healthcare monitoring system designed to continuously track vital health parameters in real time. The system utilizes an ESP32 microcontroller integrated with multiple biomedical sensors to measure heart rate, blood oxygen saturation (SpO₂), body temperature, and ECG signals. The collected data is displayed locally and uploaded to the cloud for remote monitoring.

Features

- Real-time monitoring of:
  - Heart Rate (BPM)
  - Blood Oxygen Saturation (SpO₂)
  - Body Temperature
  - ECG Signal
- Wireless data transmission using Wi-Fi
- Remote monitoring through the Blynk Cloud platform
- Emergency alert system using touch sensor, buzzer, and LED
- Local LCD display for instant patient information
- Low-cost and scalable healthcare solution

Hardware Components

- ESP32 Development Board
- MAX30100 Pulse Oximeter Sensor
- LM35 Temperature Sensor
- ECG Sensor Module
- Capacitive Touch Sensor
- 16x2 LCD Display
- Buzzer
- LED Indicators
- Power Supply

System Architecture

The system consists of three layers:

1. Sensing Layer

- MAX30100 for SpO₂ and Heart Rate
- LM35 for Temperature
- ECG Sensor for cardiac signal monitoring
- Touch Sensor for emergency assistance requests

2. Processing Layer

- ESP32 collects, processes, and manages sensor data.
- LCD displays real-time readings.
- LED and buzzer provide emergency alerts.

3. Cloud Layer

- Sensor data is transmitted via Wi-Fi.
- Blynk Cloud stores and visualizes health data.
- Caregivers can monitor patient health remotely using the Blynk mobile application.

Working Principle

1. ESP32 initializes all connected sensors.
2. Vital health parameters are continuously measured.
3. Sensor readings are displayed on the LCD.
4. Data is uploaded to the Blynk cloud platform.
5. Caregivers can access real-time health information remotely.
6. If the touch sensor is activated, the buzzer and LED generate an emergency alert.

Applications

- Remote Patient Monitoring
- Elderly Care Systems
- Home Healthcare
- Rural Healthcare Services
- Chronic Disease Management
- Telemedicine Solutions

Results

The system achieved high monitoring accuracy:

Parameter| Accuracy
Body Temperature| 99.425%
SpO₂| 99.446%
Heart Rate| 99.282%

Future Enhancements

- AI/ML-based anomaly detection
- Data encryption and enhanced security
- Multi-patient monitoring support
- Mobile notifications and SMS alerts
- Integration with hospital management systems

Technologies Used

- ESP32
- Arduino IDE
- Blynk IoT Platform
- Wi-Fi Communication
- Embedded C/C++
- IoT Cloud Computing

Authors

- Sharmitha S
- Kamalnath M L
- Shibin Raj D

Supervisor

Sathishkumar T

License

This project is developed for academic and research purposes.
