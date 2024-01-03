# Use an Ubuntu base image
FROM ubuntu:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the contents of your project to the container
COPY . .

# Install build dependencies, Python, pip, Meson, and Ninja
RUN apt-get update && \
    apt-get install -y build-essential python3 python3-pip && \
    pip3 install meson ninja

# Run Meson to configure the build
RUN meson setup builddir

# Change to the build directory
WORKDIR /app/builddir

# Build the project
RUN ninja

# Install the library system-wide
RUN ninja install

# Set the entry point for the container
ENTRYPOINT ["/bin/bash"]
