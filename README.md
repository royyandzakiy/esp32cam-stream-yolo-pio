# ESP32-CAM Object Detection with YOLOv3

This project uses an ESP32-CAM to stream video and detect objects like cats and birds using YOLOv3 and OpenCV in Python.

---

## Quick Start

### 1. Set Up ESP32-CAM
1. Install **PlatformIO** in VSCode.
2. Open the `src/credentials.h` file and add your Wi-Fi details:
   ```cpp
   #define WIFI_SSID_CREDENTIALS "your_wifi_ssid"
   #define WIFI_PASS_CREDENTIALS "your_wifi_password"
   ```

3. Connect your ESP32-CAM to your computer and upload the code using PlatformIO.

4. After uploading, open the Serial Monitor (Ctrl+Alt+S) to see the ESP32-CAM's IP address.

### 2. Run Python Script
1. Install Python dependencies:
    ```bash
    pip install opencv-python numpy
    ```

2. Download [yolov3.weights](https://pjreddie.com/darknet/yolo/), place inside `python_scripts/yolov3.weights` (for this project, I use the YOLOv3-320)
    
    ![](docs/yolov3-weights.png)

2. Open python_script/streaming_detection.py and update the url with your ESP32-CAM's IP:
    ```python
    url = 'http://192.168.1.100/cam-hi.jpg'
    ```
3. Run the script:
    ```bash
    python streaming_detection.py
    ```

## Project Structure
- `src/main.cpp`: ESP32-CAM code for streaming.
- `python_script/streaming_detection.py`: Python script for object detection.
- `python_script/yolov3.cfg`: YOLOv3 configuration file.
- `python_script/yolov3.weights`: YOLOv3 pre-trained weights.
- `python_script/coco.names`: List of object classes.

## Troubleshooting
- ESP32-CAM not connecting to Wi-Fi: Check Wi-Fi credentials and power supply.
- Python script errors: Ensure OpenCV and NumPy are installed:
    ```bash
    pip install opencv-python numpy
    ```