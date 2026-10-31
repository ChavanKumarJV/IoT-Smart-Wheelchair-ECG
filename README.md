# 🩺 IoT-Based Smart Wheelchair with Real-Time ECG Telemetry & Bluetooth Navigation

### 📌 Project Overview
Designed and engineered a cost-effective, dual-system assistive mobility and biomedical monitoring prototype created to enhance independence and cardiac safety for physically challenged patients. The architecture combines a responsive **Bluetooth-controlled motorized drivetrain** with a high-precision **Electrocardiogram (ECG) bio-telemetry pipeline** for continuous, real-time cardiac waveform acquisition and vital tracking while on the move.

---

### ❤️ High-Precision ECG & Biomedical Telemetry
* **Real-Time Cardiac Waveform Acquisition:** Captures live electrical activity of the heart (P-QRS-T complex) via surface electrodes and analog front-end signal conditioning, converting raw millivolt bio-potentials into clean digital telemetry streams.
* **Motion-Artifact & Noise Filtering:** Engineered to maintain clean ECG signal fidelity and accurate BPM extraction even in the presence of DC motor EMI and mechanical chassis vibrations.
* **Lead-Off Detection & Instant Alerting:** Continuously monitors electrode skin contact integrity and flags abnormal heart-rate thresholds or arrhythmia indicators in real time to prevent medical emergencies during transit.

---

### ♿ Assistive Mobility & Embedded Control
* **Low-Latency Bluetooth Navigation:** Wireless serial command interface allows smooth, zero-strain directional control (Forward, Reverse, Pivot Left/Right, Emergency Stop) directly from a smartphone interface.
* **Concurrent Multi-Tasking Firmware:** Embedded C++ control loop handles real-time ADC sampling for the ECG subsystem alongside high-current H-Bridge motor actuation without blocking navigation commands.

---

### 🛠️ Hardware & Tech Stack
* **Microcontroller & Firmware:** Arduino Architecture, Embedded C/C++
* **Biomedical Sensing:** ECG Analog Front-End Sensor Module (AD8232), 3-Lead Biopotential Electrodes
* **Wireless & IoT Interface:** HC-05 / Bluetooth Serial Telemetry & Navigation Module
* **Drivetrain & Power:** Dual H-Bridge Motor Driver, High-Torque DC Gear Motors, Regulated Split-Rail Power Supply

---

### Demo



https://github.com/user-attachments/assets/2fc7f208-9429-4054-8c12-cf9317a2bcaa

