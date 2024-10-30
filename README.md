# Arduino OV7670 Face Recognition Client/Server

This repository contains a client/server program that uses the Arduino OV7670 camera module for face recognition. The client captures an image and sends it to the server, which processes the image to recognize faces and returns the result to the client.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Authors](#authors)
- [License](#license)

## Overview
The project consists of a client program that captures images using the Arduino OV7670 camera module and sends them to a server. The server processes the images to recognize faces and sends back the recognition results to the client, which displays whether the face was recognized or not.

## Features
- **Image Capture**: Captures images using the Arduino OV7670 camera module.
- **Client/Server Communication**: Sends captured images from the client to the server for processing.
- **Face Recognition**: The server processes the images to recognize faces.
- **Result Display**: The client displays whether the face was recognized or not.

## Prerequisites
- **Arduino Board**: Compatible with the OV7670 camera module.
- **OV7670 Camera Module**: For capturing images.
- **C Compiler**: For compiling the client and server programs.
- **Python**: For running face recognition scripts.

## Installation
1. **Clone the repository**:
   ```sh
   git clone https://github.com/yourusername/arduino-ov7670-face-recognition.git
   cd arduino-ov7670-face-recognition
   ```

2. **Compile the client and server programs**:
   ```sh
   gcc -o client src/client.c
   gcc -o server src/server.c
   ```

3. **Set up the Arduino**:
   - Connect the OV7670 camera module to the Arduino board.
   - Upload the appropriate sketch to the Arduino for capturing images.

## Usage
1. **Start the server**:
   ```sh
   ./server
   ```

2. **Run the client**:
   ```sh
   ./client
   ```

3. **Capture and send image**:
   - The client captures an image using the OV7670 camera module and sends it to the server.
   - The server processes the image and sends back the recognition result.
   - The client displays whether the face was recognized or not.

## Code Structure
- **`src/client.c`**: Contains the client program logic for capturing and sending images.
- **`src/server.c`**: Contains the server program logic for receiving images and performing face recognition.
- **`autorizados.txt`**: List of authorized individuals for face recognition.

## Authors
- Mateus Talzzia Diogo
- Paulo Vinicius Martimiano de Oliveira
- Rafael Mont’Alverne de Souza

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
