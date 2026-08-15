# Physiological Signal Analysis for Emotion Detection

A full-stack data ingestion and machine learning pipeline designed to capture, process, and classify real-time physiological signals for emotion detection. This project bridges low-level hardware sensor data with high-level predictive modeling, focusing on continuous data synchronization and pipeline optimization.

The core objective of this project was to transition from fragmented data collection and training scripts into a unified, production-ready execution environment capable of handling live hardware data streams.

## System Evolution and Architecture

The project underwent a significant architectural redesign between **Version 1.0** and **Version 2.0** to improve system scalability, maintainability, and data flow.

### Version 1.0: Fragmented Pipeline

The initial architecture relied on a modular but heavily fragmented ecosystem:

* **Hardware Interface:** Basic sensor polling via `sensor_control.ino`.
* **Data Processing:** Split across **5 distinct, sequentially dependent Python scripts**:

  * `load_data.py`
  * `preprocess_data.py`
  * `features.py`
  * `baseline_training_model.py`
  * `baseline_pred.py`
* **Limitation:** Required manual data staging and script execution at each step of the pipeline, creating bottlenecks for real-time inference.

### Version 2.0: Unified Production Executable (Current)

The software backend was entirely refactored to eliminate modular fragmentation and enable continuous integration.

* **Hardware-to-Software Bridging:** Deployed an optimized Arduino serial I/O protocol (`data_read_script.ino`) synchronized with a dedicated Python data-recording script (`data_record_logging.py`). This enables reliable, low-latency signal logging without dropped frames.
* **Pipeline Consolidation:** The **5 individual processing and training scripts** from V1.0 were consolidated into a single cohesive execution framework (`main.py`). This unified script handles data ingestion, formatting, feature extraction, and predictive inference autonomously.
* **Predictive Inference:** Leverages **Scikit-Learn** for predictive modeling, utilizing supervised learning algorithms to classify distinct emotional states based on extracted continuous physiological features.

## Tech Stack

* **Languages:** Python, C/C++ (Arduino)
* **Machine Learning:** Scikit-Learn, NumPy, Pandas
* **Hardware Interface:** PySerial, Arduino, Biosensors
* **Architecture:** End-to-end data pipelines, real-time telemetry, serial I/O synchronization

## Setup and Execution

### Hardware Setup

1. Navigate to the `ESA_V_2.0/` directory.
2. Flash your Arduino microcontroller with `data_read_script.ino` to begin broadcasting sensor telemetry over the Serial port.
3. Connect the target hardware via USB and note the assigned COM port.

### Software Execution

1. Install the required Python dependencies:

   ```bash
   pip install scikit-learn pandas numpy pyserial
   ```

2. Initiate the real-time continuous data ingestion pipeline:

   ```bash
   python ESA_V_2.0/data_record_logging.py
   ```

3. Run the unified machine learning pipeline for feature extraction and model prediction:

   ```bash
   python ESA_V_2.0/main.py
   ```

## Pipeline Overview

```text
Physiological Sensors
        │
        ▼
Arduino Microcontroller
        │
        │ Serial Telemetry
        ▼
data_record_logging.py
        │
        ▼
Continuous Data Ingestion
        │
        ▼
main.py
        │
        ├── Data Formatting
        ├── Feature Extraction
        ├── Model Inference
        │
        ▼
Emotion Classification
```
